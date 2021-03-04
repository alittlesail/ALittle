
#include "RtpManager.h"
#include "SipSchedule.h"

void RtpManager::HandleRtpDisconnect(unsigned int route_id)
{
	auto it = m_module_map_info.find(route_id);
	if (it == m_module_map_info.end())
	{
		CARP_ERROR("route_id(" << route_id << ") is not exist!!!!!");
		return;
	}
	RtpInfo& info = it->second;

	// 处理通话信息
	for (auto& pair : info.call_id_map_port)
		m_schedule->GetSip().StopCall(pair.first, "HandleRtpDisconnect");

	// 删除信息
	m_module_map_info.erase(it);
}

void RtpManager::SetRtpResource(unsigned int route_id
	, const std::vector<std::string>& client_ip_list
	, const std::string& remote_ip
	, const std::string& inner_ip
	, int min_port, int max_port)
{
	auto it = m_module_map_info.find(route_id);
	if (it != m_module_map_info.end())
	{
		CARP_ERROR("route_id(" << route_id << ") is already exist!!!!!");
		return;
	}

	auto& info = m_module_map_info[route_id];

	// 增加RTP信息
	info.client_ip_list = client_ip_list;
	info.remote_ip = remote_ip;
	info.inner_ip = inner_ip;
	info.min_port = min_port;
	info.max_port = max_port;

	info.cur_port = info.min_port;
	info.total_count = info.max_port - info.min_port + 1;
	info.use_count = 0;

	CARP_INFO("new rtp:" << info.min_port << "," << info.max_port);
}

void HandleRtp2SipTransClientResultMessage(ModuleReceiverPtr sender, const Protocol::Rtp2SipTransClientResult& msg)
{
	C2PSipSystem::C2PCallInfoMap::iterator it = g_C2PSipSystem.m_call_map.find(msg.call_id);
	if (it == g_C2PSipSystem.m_call_map.end()) return;

	if (!it->second->c_account || !it->second->c_account->sender) return;

	Protocol::Sip2CenterCallInDetail result_msg;
	result_msg.account_id = it->second->c_account->account_id;
	result_msg.call_id = it->second->c_call_id;
	result_msg.from_number = it->second->c_from_number;
	result_msg.to_number = it->second->c_to_number;

	result_msg.c_rtp_ip = it->second->GetClientRtpIpByISP(it->second->c_account->isp);
	result_msg.c_rtp_port = it->second->c_rtp_port;
	result_msg.client_id = it->second->c_client_id;
	result_msg.ssrc = it->second->c_ssrc;
	result_msg.audio_number = it->second->c_audio_number;
	result_msg.sequence_number = msg.sequence_number;
	result_msg.timestamp = msg.timestamp;
	it->second->c_account->sender->Send(result_msg, 0, 0);
}

unsigned int RtpManager::UseRtp(const std::string& call_id
	, unsigned int client_id
	, unsigned int ssrc
	, const std::string& target_remote_rtp_ip
	, int target_remote_rtp_port
	, std::vector<std::string>& client_rtp_ip_list
	, int& client_rtp_port
	, std::string& remote_rtp_ip
	, int& remote_rtp_port
	, int& remote_rtcp_port
	, std::string& inner_rtp_ip
	, int& inner_rtp_port)
{
	// 先找到利用率最低的那个Rtp
	float min = 2.0f;
	auto target_it = m_module_map_info.end();
	for (auto it = m_module_map_info.begin(); it != m_module_map_info.end(); ++it)
	{
		if (it->second.total_count <= 0 || it->second.total_count - it->second.use_count < 4) continue;
		const float rate = static_cast<float>(it->second.use_count) / static_cast<float>(it->second.total_count);
		if (rate < min)
		{
			target_it = it;
			min = rate;
		}
	}

	// 检查是否有找到
	if (target_it == m_module_map_info.end()) return 0;

	// 个数添加
	target_it->second.use_count += 4;

	// 获取新的端口
	int first_port = 0;
	if (!target_it->second.idle_list.empty())
	{
		first_port = target_it->second.idle_list.front();
		target_it->second.idle_list.pop_front();
	}
	else
	{
		first_port = target_it->second.cur_port;
		target_it->second.cur_port += 4;
	}

	// 把呼叫保存起来
	target_it->second.call_id_map_port[call_id] = first_port;

	// 设置返回值
	client_rtp_ip_list = target_it->second.client_ip_list;
	remote_rtp_ip = target_it->second.remote_ip;
	inner_rtp_ip = target_it->second.inner_ip;
	remote_rtp_port = first_port;
	remote_rtcp_port = first_port + 1;
	client_rtp_port = first_port + 2;
	inner_rtp_port = first_port + 3;

	return target_it->first;
}

void RtpManager::ReleaseRtp( const std::string& call_id )
{
	RtpManager::ModuleMapInfo::iterator it, end = g_RtpManager.m_module_map_info.end();
	for (it = g_RtpManager.m_module_map_info.begin(); it != end; ++it)
	{
		CallIDMapPort::iterator call_it = it->second.callid_map_port.find(call_id);
		if (call_it == it->second.callid_map_port.end()) continue;

		int first_port = call_it->second;
		it->second.callid_map_port.erase(call_it);

		it->second.use_count -= 4;
		it->second.idle_list.push_back(first_port);

		Protocol::Sip2RtpRelease msg;
		msg.first_port = first_port;
		it->first->Send(msg, 0, 0);
		break;
	}
}

// RTP 语音识别到关机，挂断等语音，那么通知挂断
void HandleRtp2SipInviteResultMessage(ModuleReceiverPtr sender, const Protocol::Rtp2SipInviteResult& msg)
{
	// ALITTLE_PRINT_FUNC;

	C2PSipSystem::C2PCallInfoMap::iterator it = g_C2PSipSystem.m_call_map.find(msg.call_id);
	if (it == g_C2PSipSystem.m_call_map.end()) return;

	// 如果是普通呼叫，那么就发送给客户端
	if (it->second->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		if (it->second->c_account)
		{
			Protocol::Sip2CenterInviteResult result_msg;
			result_msg.account_id = it->second->c_account->account_id;
			result_msg.call_id = it->second->c_call_id;
			result_msg.reason = msg.reason;
			it->second->c_account->sender->Send(result_msg, 0, 0);
		}
	}
	else if (it->second->c_call_type == C2PCallInfo::CALLTYPE_MARKET)
	{
		it->second->c_match_reason = msg.reason;
		g_C2PSipSystem.StopCall(it->second, STRING_2_UTF8("HandleRtp2SipInviteResultMessage:RTP 语音识别到关机，挂断等语音，那么通知挂断"));
	}
	else if (it->second->c_call_type == C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_MARKET)
	{
		it->second->c_match_reason = msg.reason;
		g_C2PSipSystem.StopCall(it->second, STRING_2_UTF8("HandleRtp2SipInviteResultMessage:RTP 语音识别到关机，挂断等语音，那么通知挂断"));
	}
	else if (it->second->c_call_type == C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_NORMAL)
	{
		it->second->c_match_reason = msg.reason;
		g_C2PSipSystem.StopCall(it->second, STRING_2_UTF8("HandleRtp2SipInviteResultMessage:RTP 语音识别到关机，挂断等语音，那么通知挂断"));
	}
}

void RtpManager::RegisterToScript()
{
	ALITTLE_PRINT_FUNC;

	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipInviteResultMessage);
	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipTransClientResultMessage);
	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipResourceMessage);
	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipDtmfMessage);
	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipYuYinStopedMessage);
	AppDelegate::center_server->RegisterModuleMessageHandle(HandleRtp2SipRecognizeResultMessage);
}
