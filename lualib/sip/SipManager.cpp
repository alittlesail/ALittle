
#include "SipSystem/C2PSipSystem.h"
#include "SipSystem/C2PCallInfo.h"

#include "CommonInclude.h"
#include "Schedule/ScheduleManager.h"
#include "Rtp/RtpManager.h"
#include "Interface/InterfaceManager.h"
#include "Ims/ImsManager.h"
#include <ALittleBase/Utility/PhoneHCode.h>

#include <math.h>

#include "PSipClient.h"
#include "PRtp.h"
#include "SipType.h"

namespace ALittle
{

bool C2PSipSystem::s_first_register = true;

C2PSipSystem::C2PSipSystem()
{ }

C2PSipSystem::~C2PSipSystem() {}

C2PSipSystem& C2PSipSystem::Instance()
{
	static C2PSipSystem instance;
	return instance;
}

void C2PSipSystem::Setup()
{
	ALITTLE_PRINT_FUNC;

	// 获取是否需要一开始的时候注册全部号码
	s_first_register = (GET_CONFIG_STRING("first_register_all", "true") != "false");

	ALITTLE_INFO("s_first_register:" << (int)s_first_register);

	std::string register_info = GET_CONFIG_STRING("register_info", "");		// SIP的账号密码
	std::vector<std::string> register_info_list;
	Utility::SplitString(register_info, ";", register_info_list);
	for (unsigned int i = 0; i < register_info_list.size(); ++i)
	{
		std::vector<std::string> info_list;
		Utility::SplitString(register_info_list[i], ",", info_list);
		if (info_list.size() != 3)
		{
			ALITTLE_ERROR("splite by , error:" << register_info_list[i] << STRING_2_UTF8(", usage: 显示名,鉴权用户名,鉴权密码"));
			continue;
		}

		if (m_number_map_info.find(info_list[0]) != m_number_map_info.end()) continue;

		RegisterNumberInfoPtr info = RegisterNumberInfoPtr(new RegisterNumberInfo);
		m_number_map_info[info_list[0]] = info;
		m_number_list.push_back(info);

		info->show_account = info_list[0];
		info->account = info_list[1];
		info->password = info_list[2];
		info->last_resgiter_time = 0;
	}

	m_targetsip.register_show_name = (GET_CONFIG_STRING("register_show_name", "true") != "false");	// 默认注册的时候使用注册名
	m_targetsip.register_interval = GET_CONFIG_INT("register_interval", 900);	// 默认30分钟注册一次
	m_targetsip.register_expires = GET_CONFIG_STRING("register_expires", "3600");	// 默认30分钟注册一次
	m_targetsip.add_register_count = 0;
	m_targetsip.check_register_interval = 0;
	CalcCheckRegister();

	m_targetsip.target_sip_domain = GET_CONFIG_STRING("target_sip_domain", "");		// SIP的代理域名

	m_targetsip.xianlu_name = GET_CONFIG_STRING("xianlu_name", "");			// 总线路名
	m_targetsip.xianlu_subname = GET_CONFIG_STRING("xianlu_subname", "");	// 子线路名

	m_targetsip.target_sip_ip = GET_CONFIG_STRING("target_sip_ip", "");		// 对接SIP的IP
	m_targetsip.target_sip_port = GET_CONFIG_STRING("target_sip_port", "");	// 对接SIP的端口

	m_targetsip.audio_number = GET_CONFIG_STRING("audio_number", "");		// 语音编码编号
	m_targetsip.audio_name = GET_CONFIG_STRING("audio_name", "");			// 语音编码名字

	m_targetsip.support_100rel = (GET_CONFIG_STRING("support_100rel", "false") == "true");	// 是否支持100rel

	m_targetsip.dianxin_weight = GET_CONFIG_DOUBLE("dianxin_weight", 0);	// 电信权重
	m_targetsip.yidong_weight = GET_CONFIG_DOUBLE("yidong_weight", 0);		// 移动权重
	m_targetsip.liantong_weight = GET_CONFIG_DOUBLE("liantong_weight", 0);	// 联通权重
	m_targetsip.fixed_weight = GET_CONFIG_DOUBLE("fixed_weight", 0);		// 固话权重

	m_targetsip.fixed_range_or_ab = GET_CONFIG_INT("fixed_range_or_ab", 1);	// 大于0表示正选，小于或等于0表示反选
	Utility::SplitString(GET_CONFIG_STRING("fixed_list", ""), "|", m_targetsip.fixed_list);	// 固话和手机区号范围(如果不填，表示全部范围，如果有填标示指定范围)
	for (unsigned int i = 0; i < m_targetsip.fixed_list.size(); ++i)
		m_targetsip.fixed_map[m_targetsip.fixed_list[i]] = true;

	m_targetsip.max_call = GET_CONFIG_INT("max_call", 0);					// 线路最大的数量
	m_targetsip.use_call = 0;

	m_targetsip.callin_pre = GET_CONFIG_STRING("callin_pre", "");					// 呼入前缀
	m_targetsip.callout_pre = GET_CONFIG_STRING("callout_pre", "");					// 呼出前缀
	std::string callout_pre_list = GET_CONFIG_STRING("callout_pre_list", "");
	std::vector<std::string> callout_pre_list_list;
	Utility::SplitString(callout_pre_list, ";", callout_pre_list_list);
	for (unsigned int i = 0; i < callout_pre_list_list.size(); ++i)
	{
		std::vector<std::string> callout_pre;
		Utility::SplitString(callout_pre_list_list[i], ",", callout_pre);
		if (callout_pre.size() == 2)
			m_targetsip.callout_pre_map[callout_pre[0]] = callout_pre[1];
	}

	m_targetsip.callout_mobile_pre = GET_CONFIG_STRING("callout_mobile_pre", "");	// 呼出的是时候手机号是否加前缀
	m_targetsip.callout_mobile_area = GET_CONFIG_STRING("callout_mobile_area", "");	// 添加前缀的区域

	m_targetsip.call_time_unit = GET_CONFIG_INT("call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.call_count_unit = GET_CONFIG_INT("call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.dx_call_time_unit = GET_CONFIG_INT("dx_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.dx_call_count_unit = GET_CONFIG_INT("dx_call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.lt_call_time_unit = GET_CONFIG_INT("lt_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.lt_call_count_unit = GET_CONFIG_INT("lt_call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.yd_call_time_unit = GET_CONFIG_INT("yd_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.yd_call_count_unit = GET_CONFIG_INT("yd_call_count_unit", 0);		// 单位时间次数限制

	// 获取同一个主显是否只能打一个电话号码
	m_targetsip.only_one_call = 0;
	std::string only_one_call = GET_CONFIG_STRING("only_one_call", "false");
	if (only_one_call == "true")
		m_targetsip.only_one_call = 1;
	else if (only_one_call != "false")
		m_targetsip.only_one_call = Utility::FormateToInt(only_one_call.c_str());
	ALITTLE_INFO("call_time_unit:" << m_targetsip.call_time_unit << ", call_count_unit:" << m_targetsip.call_count_unit << ", only_one_call:" << m_targetsip.only_one_call);
	ALITTLE_INFO("dx_call_time_unit:" << m_targetsip.dx_call_time_unit << ", dx_call_count_unit:" << m_targetsip.dx_call_count_unit);
	ALITTLE_INFO("lt_call_time_unit:" << m_targetsip.lt_call_time_unit << ", lt_call_count_unit:" << m_targetsip.lt_call_count_unit);
	ALITTLE_INFO("yd_call_time_unit:" << m_targetsip.yd_call_time_unit << ", yd_call_count_unit:" << m_targetsip.yd_call_count_unit);

	m_targetsip.target_sip = asio::ip::udp::endpoint(asio::ip::address_v4::from_string(m_targetsip.target_sip_ip)
		, Utility::FormateToInt(m_targetsip.target_sip_port.c_str()));

	// 通知url
	m_invite_notify_url = GET_CONFIG_STRING("invite_notify_url", "");

	// 获取SIP的ip和端口
	m_local_sip_ip = GET_CONFIG_STRING("sip_local_ip", "");
	m_local_sip_port = GET_CONFIG_STRING("sip_local_port", "");
	m_local_sip = asio::ip::udp::endpoint(asio::ip::address_v4::from_string(m_local_sip_ip), Utility::FormateToInt(m_local_sip_port.c_str()));

	// 打开端口
	m_sip = UDPSystemPtr(new UDPSystem);
	bool result = m_sip->Start(m_local_sip_ip, Utility::FormateToInt(m_local_sip_port.c_str()), 10000);
	m_sip->RegisterUDPHandle(C2PSipSystem::HandleSip);

	// 定时通知SIP资源到数据库服务器
	std::function<bool(int)> func1 = std::bind(&C2PSipSystem::NotifyDatabaseAllResource, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func1, 5000, 5000));

	// 定时检查呼出去的INVITE是否有trying回应
	std::function<bool(int)> func2 = std::bind(&C2PSipSystem::UpdateLogic, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func2, 1000, 2000));
	
	// 定时检查残留太久的呼叫
	std::function<bool(int)> func3 = std::bind(&C2PSipSystem::CheckCallLast, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func3, 1000*60*60, 1000*60*60));

	// 网元保活
	int session_expires_interval = GET_CONFIG_INT("session_expires_interval", 60);
	std::function<bool(int)> func5 = std::bind(&C2PSipSystem::UpdateSession, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func5, 1000*session_expires_interval, 2000));

	// 定时检查配置，更新号码
	int check_config_interval = GET_CONFIG_INT("check_config_interval", 60*10);
	std::function<bool(int)> func6 = std::bind(&C2PSipSystem::UpdateConfigFile, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func6, 1000*check_config_interval, 2000));

	// 测试代码
	// AppDelegate::loop_system->AddObject(ALittle::LoopObject(Test, 10000, 10000));
}

bool C2PSipSystem::Test(int frame)
{
	ALITTLE_PRINT_FUNC;
	CenterManager::AccountInfoPtr account = CenterManager::AccountInfoPtr(new CenterManager::AccountInfo);
	std::vector<std::string> a;
	a.push_back("059163370777");
	std::string call_id = Utility::GenerateID("call_id");
	bool repeat;
	g_C2PSipSystem.StartCallOutNormal(account, call_id, a
		, "18059146425", "xianlu-dalianhuaxun", "xianlu-dalianhuaxun-1", ""
		, 1, std::string(), std::string(), repeat);

	return true;
}

void C2PSipSystem::Shutdown()
{
	ALITTLE_PRINT_FUNC;
	m_call_map.clear();
	if (m_sip) { m_sip->Close(); m_sip = UDPSystemPtr(); }
}

void C2PSipSystem::HandleSipLogCallback( const std::string& call_id, const std::string& content )
{
	// 获取当前日志时间
	int log_time = (int)time(0);
	// 发送到数据库服务器用于存储Sip整个过程
	SimpleJsonObject param;
	param["c_call_id"] = call_id;
	param["c_content"] = content;
	param["c_log_time"] = log_time;
	g_ScheduleManager.SendDataBaseInnerMessage("SipLog:" + Utility::FormateToString(log_time), param);
}

void C2PSipSystem::HandleStatusCallback( C2PCallInfoPtr call_info, const std::string& method, const std::string& reason )
{
	// ALITTLE_PRINT_FUNC;
	
	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_TEST)
	{
		// 当出现呼叫响铃时，马上挂断
		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_RINGING)
		{
			call_info->StopCall(g_C2PSipSystem.m_sip, STRING_2_UTF8("测试接口，出现被叫响铃时，马上挂断"));
		}

		return;
	}
	
	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		if (call_info->c_account && call_info->c_account->sender)
		{
			Protocol::Sip2CenterCallStatus msg;
			msg.account_id = call_info->c_account->account_id;
			msg.call_id = call_info->c_call_id;
			msg.main_reason = method;
			msg.sub_reason = reason;
			msg.status = (int)call_info->c_sip_step;
			msg.is_completed = false;

			if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK_END)
			{
				call_info->c_account->call_id = "";
				msg.is_completed = true;
			}

			call_info->c_account->sender->Send(msg, 0, 0);

			if (call_info->c_out_or_in == false && call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK
				&& call_info->c_rtp)
			{
				// client_id要和之前的不一样
				++ call_info->c_client_id;
				Protocol::Sip2RtpTransClient trans_msg;
				trans_msg.first_port = call_info->p_rtp_port;
				trans_msg.client_id = call_info->c_client_id;
				call_info->c_rtp->Send(trans_msg, 0, 0);
			}
		}

		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK)
		{
			if (call_info->c_rtp)
			{
				Protocol::Sip2RtpCallTalk talk_msg;
				talk_msg.first_port = call_info->p_rtp_port;
				call_info->c_rtp->Send(talk_msg, 0, 0);
			}
		}
		
		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK_END)
		{
			// 发送结束
			if (call_info->c_normal_trans_interface
				&& call_info->c_normal_trans_interface->sender)
			{
				Protocol::Sip2InterfaceNormalStatus msg;
				msg.call_id = call_info->c_call_id;
				msg.xianlu_name = call_info->c_xianlu_name;
				msg.xianlu_subname = call_info->c_xianlu_subname;
				msg.show_number = call_info->c_from_number;
				msg.target_number = call_info->c_to_number;
				msg.other_info = call_info->c_other_info;
				msg.time = (int)time(0);
				msg.status = "END"; // 呼叫结束
				if (call_info->c_match_reason.size())
					msg.reason = call_info->c_match_reason;
				else
					msg.reason = reason;
				msg.sip_flag = AppDelegate::SIP_FLAG;
				call_info->c_normal_trans_interface->sender->Send(msg);
			}
		}
		return;
	}
	
	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_MARKET)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// 接口状态通知，被叫响铃
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "OUT_RING"; // 被叫响铃
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// 通知接口状态
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "OUT_ANWSER"; // 被叫接听
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// 通知RTP服务器播放什么语音
				if (call_info->c_yuyin_id.size() && call_info->c_rtp)
				{
					Protocol::Sip2RtpPlayYuYin yuyin_msg;
					yuyin_msg.first_port = call_info->p_rtp_port;
					yuyin_msg.yuyin_id = call_info->c_yuyin_id;
					yuyin_msg.yuyin_repeat = call_info->c_yuyin_repeat;
					yuyin_msg.audio_number = call_info->c_audio_number;
					call_info->c_rtp->Send(yuyin_msg, 0, 0);
				}
				{
					// 向接口询问，使用那个账号转接
					Protocol::Sip2InterfaceMarketAccount msg;
					msg.call_id = call_info->c_call_id;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "END"; // 呼叫结束
					if (call_info->c_match_reason.size())
						msg.reason = call_info->c_match_reason;
					else
						msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}

				// 向账号发送通话结束事件
				if (call_info->c_account && call_info->c_account->sender)
				{
					Protocol::Sip2CenterCallStatus msg;
					msg.account_id = call_info->c_account->account_id;
					msg.call_id = call_info->c_call_id;
					msg.main_reason = method;
					msg.sub_reason = reason;
					msg.status = (int)call_info->c_sip_step;
					msg.is_completed = true;
					call_info->c_account->call_id = "";
					call_info->c_account->sender->Send(msg, 0, 0);
				}
			}
			break;
		}
		return;
	}

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_TRANS_MARKET)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// 接口状态通知，转接对象响铃
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_RING"; // 转接对象响铃
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// 通知接口准备转接
				{
					Protocol::Sip2InterfaceMarketTransferStart msg;
					msg.src_call_id = call_info->c_src_call_id;
					msg.call_id = call_info->c_call_id;
					msg.i_rtp_ip = call_info->i_rtp_ip;
					msg.i_rtp_port = call_info->i_rtp_port;
					msg.audio_number = call_info->c_audio_number;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}
				// 通知接口状态
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "IN_ANWSER"; // 转接接听
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_END"; // 呼叫结束
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		}
		return;
	}

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_MARKET)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_RINGING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// 通知接口准备转接
				{
					Protocol::Sip2InterfaceMarketUnattendedTransferStart msg;
					msg.src_call_id = call_info->c_src_call_id;
					msg.call_id = call_info->c_call_id;
					msg.i_rtp_ip = call_info->i_rtp_ip;
					msg.i_rtp_port = call_info->i_rtp_port;
					msg.audio_number = call_info->c_audio_number;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_UNATTENDED_TRANS_END"; // 呼叫结束
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		}
		return;
	}

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_NORMAL)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_RINGING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// 通知接口准备转接
				{
					Protocol::Sip2InterfaceNormalUnattendedTransferStart msg;
					msg.src_call_id = call_info->c_src_call_id;
					msg.call_id = call_info->c_call_id;
					msg.i_rtp_ip = call_info->i_rtp_ip;
					msg.i_rtp_port = call_info->i_rtp_port;
					msg.audio_number = call_info->c_audio_number;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceNormalStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_UNATTENDED_TRANS_END"; // 呼叫结束
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		}
		return;
	}

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_IVR)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_IN_INVITE: break;		// 不处理
		case C2PCallInfo::SIPSTEP_IN_TRYING: break;		// 不处理
		case C2PCallInfo::SIPSTEP_IN_RINGING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_IN_OK: break;			// 不处理
		case C2PCallInfo::SIPSTEP_IN_FORBIDDEN: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理

		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// 打开RTP的取键
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpOpenDtmf dtmf_msg;
					dtmf_msg.first_port = call_info->p_rtp_port;
					dtmf_msg.open = true;
					call_info->c_rtp->Send(dtmf_msg, 0, 0);
				}

				// 通知接口状态
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "OUT_ANWSER"; // 被叫接听
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// 通知RTP服务器播放什么语音
				if (call_info->c_yuyin_id.size() && call_info->c_rtp)
				{
					Protocol::Sip2RtpPlayYuYin yuyin_msg;
					yuyin_msg.first_port = call_info->p_rtp_port;
					yuyin_msg.yuyin_id = call_info->c_yuyin_id;
					yuyin_msg.yuyin_repeat = call_info->c_yuyin_repeat;
					yuyin_msg.audio_number = call_info->c_audio_number;
					call_info->c_rtp->Send(yuyin_msg, 0, 0);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "END"; // 呼叫结束
					if (call_info->c_match_reason.size())
						msg.reason = call_info->c_match_reason;
					else
						msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}

				// 向账号发送通话结束事件
				if (call_info->c_account && call_info->c_account->sender)
				{
					Protocol::Sip2CenterCallStatus msg;
					msg.account_id = call_info->c_account->account_id;
					msg.call_id = call_info->c_call_id;
					msg.main_reason = method;
					msg.sub_reason = reason;
					msg.status = (int)call_info->c_sip_step;
					msg.is_completed = true;
					call_info->c_account->call_id = "";
					call_info->c_account->sender->Send(msg, 0, 0);
				}
			}
			break;
		}
		return;
	}

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_TRANS_IVR)
	{
		if (!call_info->c_interface || !call_info->c_interface->_interface || !call_info->c_interface->_interface->sender)
		{
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:参数问题"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// 不处理
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// 不处理

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// 接口状态通知，转接对象响铃
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_RING"; // 转接对象响铃
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// 通知接口准备转接
				{
					Protocol::Sip2InterfaceIVRTransferStart msg;
					msg.src_call_id = call_info->c_src_call_id;
					msg.call_id = call_info->c_call_id;
					msg.i_rtp_ip = call_info->i_rtp_ip;
					msg.i_rtp_port = call_info->i_rtp_port;
					msg.audio_number = call_info->c_audio_number;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// 通知RTP关闭对比
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}
				// 通知接口状态
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "IN_ANWSER"; // 转接接听
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// 发送结束
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_END"; // 呼叫结束
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		}
		return;
	}
}

void C2PSipSystem::SendDtmf( const std::string& call_id, const std::string& content )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip)	return;

	// 查找是否存在
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return;

	it->second->SendDtmf(m_sip, content);
}

void C2PSipSystem::HandleSipDtmfCallback( C2PCallInfoPtr call_info, const std::string& content )
{
	// ALITTLE_PRINT_FUNC;

	ALITTLE_INFO("C2PSipSystem::HandleSipDtmfCallback:" << content);
}

ALittle::C2PCallInfoPtr C2PSipSystem::StartCallOutTest( int test_invoke_id
													, const std::string& call_id
													, const std::string& from_number, const std::string& to_number
													, std::string& reason , bool& repeat )
{
	ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足").c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	std::vector<std::string> from_number_list;
	from_number_list.push_back(from_number);
	std::string out_from_number;
	if (IsShowNumberLimit(from_number_list, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, false, m_targetsip.audio_number, sip_type, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("m_targetsip.use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// 保存呼叫ID
	call_info->m_test_invoke_id = test_invoke_id;

	// 保存账号对象
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TEST;
	call_info->c_bill_type = "200";
	call_info->c_xianlu_name = m_targetsip.xianlu_name;
	call_info->c_xianlu_subname = m_targetsip.xianlu_subname;
	call_info->c_project_id = "kehufazhanpingtai";

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

C2PCallInfoPtr C2PSipSystem::StartCallOutNormal( CenterManager::AccountInfoPtr account
										  , const std::string& call_id
										  , const std::vector<std::string>& from_number, const std::string& to_number
										  , const std::string& xianlu_name, const std::string& xianlu_subname
										  , const std::string& other_info
										  , int corp
										  , std::string& out_from_number
										  , std::string& reason
										  , bool& repeat )
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	std::string area_code;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		is_fixed = true;
		hcode_corp = PhoneHCode::HCODECORP_DX;
	}
	else
	{
		area_code = hcode->area_code;
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (area_code.size() && IsAreaCodeLimit(area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, false, m_targetsip.audio_number, corp, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("m_targetsip.use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// 保存账号对象
	call_info->c_account = account;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_NORMAL;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "200";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = account->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

C2PCallInfoPtr C2PSipSystem::StartUnattendedTransferNormal( InterfaceManager::InterfaceInfoCallPtr _interface
														   , const std::string& enterprise_id
														   , const std::string& call_id
														   , const std::vector<std::string>& from_number
														   , const std::string& to_number
														   , const std::string& xianlu_name, const std::string& xianlu_subname
														   , const std::string& other_info
														   , int corp
														   , bool need_dtmf
														   , std::string& out_from_number
														   , std::string& reason
														   , bool& repeat )
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查是不是线路资源上限
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "企业线路资源已到上限:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, need_dtmf, m_targetsip.audio_number, corp, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// 保存账号对象
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_NORMAL;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "240";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

// 开始转接到客户端
void C2PSipSystem::StartCallIn( const std::string& call_id
							   , CenterManager::AccountInfoPtr account
							   , const std::string& other_info
							   , std::function<void(bool)> callback
							   , bool is_unattended_transfer)
{
	// ALITTLE_PRINT_FUNC;
	// 查找是否存在
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return;

	C2PCallInfoPtr call_info = it->second;

	// 如果有转接那么，就不能设置账号
	if (!callback) call_info->c_account = account;
	call_info->c_project_id = account->project_id;
	call_info->m_trnas_callback = callback;

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		// 保存携带信息
		call_info->c_other_info = other_info;

		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_RINGING)
			HandleStatusCallback(call_info, "INVITE", "main invite");
		// 通知呼入
		Protocol::Sip2CenterCallIn msg;
		msg.account_id = account->account_id;
		msg.call_id = call_info->c_call_id;
		// 如果是呼叫转移，并且是呼出，那么主被叫对换一下
		if (is_unattended_transfer && call_info->c_out_or_in)
		{
			msg.from_number = call_info->c_to_number;
			msg.to_number = call_info->c_from_number;
		}
		else
		{
			msg.from_number = call_info->c_from_number;
			msg.to_number = call_info->c_to_number;
		}
		msg.c_rtp_ip = call_info->GetClientRtpIpByISP(account->isp);
		msg.c_rtp_port = call_info->c_rtp_port;
		msg.client_id = call_info->c_client_id;
		msg.ssrc = call_info->c_ssrc;
		msg.audio_number = call_info->c_audio_number;
		account->sender->Send(msg, 0, 0);
	}
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_MARKET)
	{
		{
			// 通知呼入
			Protocol::Sip2CenterCallIn msg;
			msg.account_id = account->account_id;
			msg.call_id = call_info->c_call_id;
			msg.from_number = call_info->c_to_number;
			msg.to_number = call_info->c_from_number;
			msg.c_rtp_ip = call_info->GetClientRtpIpByISP(account->isp);
			msg.c_rtp_port = call_info->c_rtp_port;
			msg.client_id = call_info->c_client_id;
			msg.ssrc = call_info->c_ssrc;
			msg.audio_number = call_info->c_audio_number;
			account->sender->Send(msg, 0, 0);
		}

		// 如果是转接的目标座席，那么就不用向Interface发送IN_RING
		if (!call_info->m_trnas_callback && call_info->c_interface
			&& call_info->c_interface->_interface
			&& call_info->c_interface->_interface->sender)
		{
			// 通知接口发送呼入RING事件
			Protocol::Sip2InterfaceMarketStatus msg;
			msg.call_id = call_info->c_call_id;
			msg.xianlu_name = call_info->c_xianlu_name;
			msg.xianlu_subname = call_info->c_xianlu_subname;
			msg.show_number = call_info->c_from_number;
			msg.target_number = call_info->c_to_number;
			msg.other_info = call_info->c_other_info;
			msg.time = (int)time(0);
			msg.status = "IN_RING"; // 转接响铃
			msg.reason = "";
			msg.sip_flag = AppDelegate::SIP_FLAG;
			call_info->c_interface->_interface->sender->Send(msg);
		}
	}
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_IVR)
	{
		{
			// 通知呼入
			Protocol::Sip2CenterCallIn msg;
			msg.account_id = account->account_id;
			msg.call_id = call_info->c_call_id;
			msg.from_number = call_info->c_from_number;
			msg.to_number = call_info->c_to_number;
			msg.c_rtp_ip = call_info->GetClientRtpIpByISP(account->isp);
			msg.c_rtp_port = call_info->c_rtp_port;
			msg.client_id = call_info->c_client_id;
			msg.ssrc = call_info->c_ssrc;
			msg.audio_number = call_info->c_audio_number;
			account->sender->Send(msg, 0, 0);
		}
		if (call_info->c_interface
			&& call_info->c_interface->_interface
			&& call_info->c_interface->_interface->sender)
		{
			// 通知接口发送呼入RING事件
			Protocol::Sip2InterfaceIVRStatus msg;
			msg.call_id = call_info->c_call_id;
			msg.xianlu_name = call_info->c_xianlu_name;
			msg.xianlu_subname = call_info->c_xianlu_subname;
			msg.show_number = call_info->c_from_number;
			msg.target_number = call_info->c_to_number;
			msg.other_info = call_info->c_other_info;
			msg.time = (int)time(0);
			msg.status = "IN_RING"; // 转接响铃
			msg.reason = "";
			msg.sip_flag = AppDelegate::SIP_FLAG;
			call_info->c_interface->_interface->sender->Send(msg);
		}
	}
}

bool C2PSipSystem::StopCall( const std::string& call_id, const std::string& reason )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;

	// 查找是否存在
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return false;

	// 停止呼出
	it->second->StopCall(m_sip, reason);
	return true;
}

ALittle::C2PCallInfoPtr C2PSipSystem::GetCallInfoByID( const std::string& call_id )
{
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return C2PCallInfoPtr();

	return it->second;
}

bool C2PSipSystem::StopCall( C2PCallInfoPtr call_info, const std::string& reason )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;
	if (!call_info) return false;

	// 停止呼出
	call_info->StopCall(m_sip, reason);
	return true;
}

// 接听来电
bool C2PSipSystem::AcceptCallIn( const std::string& call_id, CenterManager::AccountInfoPtr account )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;

	// 查找是否存在
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end()) return false;

	C2PCallInfoPtr call_info = it->second;

	// 接受呼入
	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		call_info->CallInOK(m_sip);

		if (call_info->m_trnas_callback)
		{
			// 如果点击接听的是原来那个账号，那么就转接失败
			if (call_info->c_account == account)
			{
				call_info->m_trnas_callback(false);
			}
			else
			{
				// 转接成功
				call_info->m_trnas_callback(true);

				// 保存为当前的账号
				call_info->c_account = account;

				// 如果是呼出，并且已经接通了，那么通知转接
				if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK && call_info->c_rtp)
				{
					++ call_info->c_client_id;
					Protocol::Sip2RtpTransClient trans_msg;
					trans_msg.first_port = call_info->p_rtp_port;
					trans_msg.client_id = call_info->c_client_id;
					call_info->c_rtp->Send(trans_msg, 0, 0);
				}
			}
			call_info->m_trnas_callback = std::function<void(bool)>();
		}
	}
	// 通知转接成功
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_MARKET)
	{
		if (call_info->m_trnas_callback)
		{
			// 如果点击接听的是原来那个账号，那么就转接失败
			if (call_info->c_account == account)
			{
				call_info->m_trnas_callback(false);
			}
			else
			{
				// 转接成功
				call_info->m_trnas_callback(true);

				// 保存为当前的账号
				call_info->c_account = account;
			}
			call_info->m_trnas_callback = std::function<void(bool)>();
		}

		if (call_info->c_market_talk == false)
		{
			// 标记为true，这样可以拦住后面多余的接听事件
			call_info->c_market_talk = true;
			// 向账号发送已接通事件
			if (call_info->c_account && call_info->c_account->sender)
			{
				Protocol::Sip2CenterCallStatus msg;
				msg.account_id = call_info->c_account->account_id;
				msg.call_id = call_info->c_call_id;
				msg.main_reason = "MARKET";
				msg.sub_reason = "MARKET";
				msg.status = C2PCallInfo::SIPSTEP_TALK;
				msg.is_completed = false;
				call_info->c_account->sender->Send(msg, 0, 0);
			}
			// 通知接口发送呼入应答事件
			if (call_info->c_interface && call_info->c_interface->_interface && call_info->c_interface->_interface->sender)
			{
				Protocol::Sip2InterfaceMarketStatus msg;
				msg.call_id = call_info->c_call_id;
				msg.xianlu_name = call_info->c_xianlu_name;
				msg.xianlu_subname = call_info->c_xianlu_subname;
				msg.show_number = call_info->c_from_number;
				msg.target_number = call_info->c_to_number;
				msg.other_info = call_info->c_other_info;
				msg.time = (int)time(0);
				msg.status = "IN_ANWSER"; // 转接应答
				msg.reason = "";
				msg.sip_flag = AppDelegate::SIP_FLAG;
				call_info->c_interface->_interface->sender->Send(msg);
			}
			// 通知RTP进行转移
			if (call_info->c_out_or_in == true && call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK
				&& call_info->c_rtp)
			{
				++ call_info->c_client_id;
				Protocol::Sip2RtpTransClient trans_msg;
				trans_msg.first_port = call_info->p_rtp_port;
				trans_msg.client_id = call_info->c_client_id;
				call_info->c_rtp->Send(trans_msg, 0, 0);
			}
		}
	}
	// 通知转接成功
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_IVR)
	{
		if (call_info->c_market_talk == false)
		{
			// 标记为true，这样可以拦住后面多余的接听事件
			call_info->c_market_talk = true;
			// 向账号发送已接通事件
			if (call_info->c_account && call_info->c_account->sender)
			{
				Protocol::Sip2CenterCallStatus msg;
				msg.account_id = call_info->c_account->account_id;
				msg.call_id = call_info->c_call_id;
				msg.main_reason = "IVR";
				msg.sub_reason = "IVR";
				msg.status = C2PCallInfo::SIPSTEP_TALK;
				msg.is_completed = false;
				call_info->c_account->sender->Send(msg, 0, 0);
			}
			// 通知接口发送呼入应答事件
			if (call_info->c_interface && call_info->c_interface->_interface && call_info->c_interface->_interface->sender)
			{
				Protocol::Sip2InterfaceIVRStatus msg;
				msg.call_id = call_info->c_call_id;
				msg.xianlu_name = call_info->c_xianlu_name;
				msg.xianlu_subname = call_info->c_xianlu_subname;
				msg.show_number = call_info->c_from_number;
				msg.target_number = call_info->c_to_number;
				msg.other_info = call_info->c_other_info;
				msg.time = (int)time(0);
				msg.status = "IN_ANWSER"; // 转接应答
				msg.reason = "";
				msg.sip_flag = AppDelegate::SIP_FLAG;
				call_info->c_interface->_interface->sender->Send(msg);
			}
			// 通知RTP进行转移
			if (call_info->c_out_or_in == false && call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK
				&& call_info->c_rtp)
			{
				++ call_info->c_client_id;
				Protocol::Sip2RtpTransClient trans_msg;
				trans_msg.first_port = call_info->p_rtp_port;
				trans_msg.client_id = call_info->c_client_id;
				call_info->c_rtp->Send(trans_msg, 0, 0);
			}
		}
	}
	return true;
}

// 呼入寻找合适的账号，失败的话那么就挂断电话
void HandleQueryCallInAccountByNormalCallIn(bool result, const std::string& call_id)
{
	if (result) return;

	C2PCallInfoPtr call_info = g_C2PSipSystem.GetCallInfoByID(call_id);
	if (!call_info) return;

	call_info->NotifyNoAnswer();
	g_C2PSipSystem.StopCall(call_info, STRING_2_UTF8("HandleQueryCallInAccountByNormalCallIn:普通呼入被叫拒绝接听"));
}

void C2PSipSystem::HandleSip( UDPSystem::HandleInfo& info )
{
	// ALITTLE_PRINT_FUNC;
	C2PSipSystem* self = &g_C2PSipSystem;

	// 拆分sip协议
	std::vector<std::string> content_list;
	Utility::SplitString(info.memory, "\r\n", content_list);

	// 检查是否拆分出行
	if (content_list.size() == 0)
	{
		self->HandleSipLogCallback("ERROR", std::string() + "content_list size is 0:" + info.memory);
		ALITTLE_ERROR("content_list size is 0");
		return;
	}

	// 从协议中获取Call-ID
	std::string call_id = C2PCallInfo::GetKeyValueFromUDP(content_list, "CALL-ID");
	if (call_id == "") return;

	ALITTLE_INFO("SIP Recevie ------------------->:" << content_list[0] << ", CALLID:" << call_id);

	// 打印到数据库
	self->HandleSipLogCallback(call_id, std::string() + "RECEIVE <==" + info.memory);

	// 从第一行拆分出命令
	std::vector<std::string> response_list;
	Utility::SplitString(content_list[0], " ", response_list);
	if (response_list.size() < 1)
	{
		self->HandleSipLogCallback(call_id, "response_list size < 1");
		ALITTLE_ERROR("response_list size < 1");
		return;
	}

	std::string method = response_list[0];

	std::string status = "";
	if (method == "SIP/2.0")
	{
		if (response_list.size() < 2)
		{
			self->HandleSipLogCallback(call_id, "response_list size < 2");
			ALITTLE_ERROR("response_list size < 2");
			return;
		}

		status = response_list[1];
	}

	// 先查找注册call_id
	RegisterSipInfoMap::iterator register_it = self->m_callid_map_registerinfo.find(call_id);
	if (register_it != self->m_callid_map_registerinfo.end())
	{
		if (register_it->second.register_status == SipRegister::SIPREGISTER_1)
		{
			if (status == "200")
			{
				// 标记
				RegisterNumberMap::iterator sip_account_it = self->m_number_map_info.find(register_it->second.register_show_account);
				if (sip_account_it != self->m_number_map_info.end())
				{
					sip_account_it->second->register_call_id = "";

					// 从正在注册映射表中删除，添加到待注册列表的尾巴
					self->m_registering_map.erase(sip_account_it->second->show_account);
					self->m_number_list.push_back(sip_account_it->second);
				}
				// 移除
				self->m_callid_map_registerinfo.erase(register_it);
			}
			// 执行二次注册
			else
			{
				self->DoSipRegister2(register_it->second, content_list);
			}
		}
		else if (register_it->second.register_status == SipRegister::SIPREGISTER_2)
		{
			// 标记
			RegisterNumberMap::iterator sip_account_it = self->m_number_map_info.find(register_it->second.register_show_account);
			if (sip_account_it != self->m_number_map_info.end())
			{
				sip_account_it->second->register_call_id = "";
				sip_account_it->second->register_auth = register_it->second.register_auth;

				// 从正在注册映射表中删除，添加到待注册列表的尾巴
				self->m_registering_map.erase(sip_account_it->second->show_account);
				self->m_number_list.push_back(sip_account_it->second);
			}
			// 移除
			self->m_callid_map_registerinfo.erase(register_it);
		}
		return;
	}

	// 处理呼入邀请，并且当前call_id不存在，那么属于新的呼入
	if (method == "INVITE")
	{
		C2PCallInfoMap::iterator invite_it = self->m_call_map.find(call_id);
		if (invite_it == self->m_call_map.end())
		{
			// 找到后，使用量加1，并通知所有Center
			++ (g_C2PSipSystem.m_targetsip.use_call);
			ALITTLE_INFO("g_C2PSipSystem.m_targetsip.use_call:" << g_C2PSipSystem.m_targetsip.use_call);
			g_CenterManager.NotifyAllCenterResourceValue(g_C2PSipSystem.m_targetsip, 1);
			g_InterfaceManager.NotifyAllInterfaceResourceValue(g_C2PSipSystem.m_targetsip, 1);
			// 创建CallInfo对象
			C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
			call_info->c_call_id = call_id;
			self->m_call_map[call_info->c_call_id] = call_info;
			// 处理呼入信息
			if (call_info->HandleSipInfoCreateCallInInvite(self->m_sip, method, "", response_list, content_list
										, self->m_local_sip_ip, self->m_local_sip_port
										, g_C2PSipSystem.m_targetsip.xianlu_name
										, g_C2PSipSystem.m_targetsip.xianlu_subname
										, g_C2PSipSystem.m_targetsip.callin_pre, info.end_point) == false)
			{
				self->StopCall(call_id, STRING_2_UTF8("HandleSipInfoCreateCallInInvite失败"));
			}
			else
			{
				int ims_callin_type = ImsManager::CALLINTYPE_NORMAL;
				std::string ims_yuyin_id = AppDelegate::DEFAULT_YUYIN;
				std::string ims_project_id;
				// 查询呼入号码所在的规则
				ImsManager::CallInMap::iterator ims_it = g_ImsManager.m_callin_map.find(call_info->c_to_number);
				if (ims_it != g_ImsManager.m_callin_map.end())
				{
					ims_callin_type = ims_it->second.callin_type;
					ims_yuyin_id = ims_it->second.yuyin_id;
					ims_project_id = ims_it->second.project_id;
				}

				// 向RTP发送播放语音
				if (call_info->c_rtp && ims_yuyin_id.size())
				{
					Protocol::Sip2RtpPlayYuYin yuyin_msg;
					yuyin_msg.first_port = call_info->p_rtp_port;
					yuyin_msg.audio_number = call_info->c_audio_number;
					yuyin_msg.yuyin_id = ims_yuyin_id;
					yuyin_msg.yuyin_repeat = 0;	// 无限播放
					call_info->c_rtp->Send(yuyin_msg, 0, 0);
				}

				if (ims_callin_type == ImsManager::CALLINTYPE_NORMAL)
				{
					// 如果询问账号失败，那么就直接挂断
					std::function<void(bool)> func = std::bind(HandleQueryCallInAccountByNormalCallIn, std::placeholders::_1, call_id);
					if (g_CenterManager.QueryCallInAccount(call_id, ""
														, g_C2PSipSystem.m_targetsip.xianlu_name
														, call_info->c_to_number, func, std::function<void(bool)>()
														, false) == false)
					{
						call_info->NotifyNoAnswer();
						self->StopCall(call_id, STRING_2_UTF8("QueryCallInAccount没有找到可以呼入的坐席"));
					}
				}
				else if (ims_callin_type == ImsManager::CALLINTYPE_IVR)
				{
					// 根据项目ID找到对应的Interface
					InterfaceManager::InterfaceInfoPtr ims_interface = g_InterfaceManager.GetModuleById(ims_project_id);
					if (!ims_interface)
					{
						ALITTLE_ERROR("can't find interface by project_id:" << ims_project_id << ", ims:" << call_info->c_from_number);
						self->StopCall(call_id, STRING_2_UTF8("CALLINTYPE_IVR 参数问题"));
					}
					else
					{
						InterfaceManager::InterfaceInfoCallPtr _interface = InterfaceManager::InterfaceInfoCallPtr(new InterfaceManager::InterfaceInfoCall);
						_interface->call_id = call_info->c_call_id;
						_interface->_interface = ims_interface;

						call_info->c_interface = _interface;
						call_info->c_call_type = C2PCallInfo::CALLTYPE_IVR;
						call_info->c_bill_type = "1040";		// 账单类型
						// 通知接口服务器
						Protocol::Sip2InterfaceIVRCallIn ivr_callin_msg;
						ivr_callin_msg.call_id = call_id;
						ivr_callin_msg.show_number = call_info->c_from_number;
						ivr_callin_msg.target_number = call_info->c_to_number;
						ivr_callin_msg.xianlu_name = g_C2PSipSystem.m_targetsip.xianlu_name;
						ivr_callin_msg.xianlu_subname = g_C2PSipSystem.m_targetsip.xianlu_subname;
						ivr_callin_msg.start_time = call_info->c_start_time;
						ivr_callin_msg.sip_flag = AppDelegate::SIP_FLAG;
						ivr_callin_msg.i_rtp_ip = call_info->i_rtp_ip;
						ivr_callin_msg.i_rtp_port = call_info->i_rtp_port;
						ivr_callin_msg.audio_number = call_info->c_audio_number;
						ims_interface->sender->Send(ivr_callin_msg);
					}
				}
				else
				{
					self->StopCall(call_id, STRING_2_UTF8("呼叫类型错误"));
				}
			}
		}
		else
		{
			bool remove_tmp = false;
			invite_it->second->HandleCallSipReInvite(self->m_sip, method, "", response_list, content_list, remove_tmp);
		}
	}
	// 处理其他协议
	else
	{
		// 检查CallID是否存在
		C2PCallInfoMap::iterator it = self->m_call_map.find(call_id);
		if (it == self->m_call_map.end())
		{
			if (method != "NOTIFY")
			{
				self->HandleSipLogCallback(call_id, "can't find call id in map");
				ALITTLE_ERROR("can't find call id in map:" << call_id);
			}
			self->HandleErrorSip(info.end_point, self->m_sip, method, status, response_list, content_list);
			return;
		}

		bool remove = false;
		it->second->HandleSipInfo(self->m_sip, method, status, response_list, content_list, remove);		
		if (remove)
		{
			// 找到后，使用量加1，并通知所有Center
			-- (g_C2PSipSystem.m_targetsip.use_call);
			ALITTLE_INFO("g_C2PSipSystem.m_targetsip.use_call:" << g_C2PSipSystem.m_targetsip.use_call);
			g_CenterManager.NotifyAllCenterResourceValue(g_C2PSipSystem.m_targetsip, -1);
			g_InterfaceManager.NotifyAllInterfaceResourceValue(g_C2PSipSystem.m_targetsip, -1);

			self->HandleSipLogCallback(call_id, "RELEASE");
			ALITTLE_INFO("===========> RELEASE CALL-ID:" << it->second->c_call_id);
			// 如果是呼入，要把正在呼入的流程清空掉
			if (it->second->c_out_or_in == false)
				g_CenterManager.ClearCallInInfo(call_id);
			// 如果不是普通呼叫，那么就要清理接口管理器的信息
			if (it->second->c_call_type != C2PCallInfo::CALLTYPE_NORMAL && it->second->c_call_type != C2PCallInfo::CALLTYPE_TEST)
				g_InterfaceManager.ClearInterfaceInfo(it->second->c_call_id);
			// 释放Rtp
			g_RtpManager.ReleaseRtp(call_id);
			// 产生账单，发送到数据库
			it->second->SaveBill();
			if (it->second->c_out_or_in)
				g_C2PSipSystem.RemoveOnlyOneCall(it->second->c_from_number);
			else
				g_C2PSipSystem.RemoveOnlyOneCall(it->second->c_to_number);
			// 最后释放之前，调用一下这个函数做最后处理
			it->second->NotifyReleased();
			// 删除呼叫信息
			self->m_call_map.erase(it);
		}
	}
}

C2PCallInfoPtr C2PSipSystem::StartCallOutMarket( InterfaceManager::InterfaceInfoCallPtr _interface
												, const std::string& enterprise_id
												, const std::string& call_id
												, const std::vector<std::string>& from_number
												, const std::string& to_number
												, const std::string& xianlu_name, const std::string& xianlu_subname
												, const std::string& other_info
												, int corp
												, bool need_dtmf
												, bool need_record
												, std::string& out_from_number
												, std::string& reason
												, bool& repeat)
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查是不是线路资源上限
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "企业线路资源已到上限:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	// 记录开始时间
	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, need_dtmf, m_targetsip.audio_number, corp, true, need_record, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// 保存账号对象
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1080";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

C2PCallInfoPtr C2PSipSystem::StartTransferMarket( InterfaceManager::InterfaceInfoCallPtr _interface
												 , const std::string& enterprise_id
												 , const std::string& call_id
												 , const std::vector<std::string>& from_number
												 , const std::string& to_number
												 , const std::string& xianlu_name, const std::string& xianlu_subname
												 , const std::string& other_info
												 , int corp
												 , bool need_dtmf
												 , std::string& out_from_number
												 , std::string& reason
												 , bool& repeat )
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查是不是线路资源上限
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "企业线路资源已到上限:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, need_dtmf, m_targetsip.audio_number, corp, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// 保存账号对象
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TRANS_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1081";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

C2PCallInfoPtr C2PSipSystem::StartUnattendedTransferMarket( InterfaceManager::InterfaceInfoCallPtr _interface
												 , const std::string& enterprise_id
												 , const std::string& call_id
												 , const std::vector<std::string>& from_number
												 , const std::string& to_number
												 , const std::string& xianlu_name, const std::string& xianlu_subname
												 , const std::string& other_info
												 , int corp
												 , bool need_dtmf
												 , std::string& out_from_number
												 , std::string& reason
												 , bool& repeat )
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查是不是线路资源上限
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "企业线路资源已到上限:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, need_dtmf, m_targetsip.audio_number, corp, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// 保存账号对象
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "240";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

void HandleQueryCallInAccountByMarketCallIn(bool result, const std::string& call_id)
{
	if (result) return;

	C2PCallInfoPtr call_info = g_C2PSipSystem.GetCallInfoByID(call_id);
	if (!call_info) return;
	
	g_C2PSipSystem.StopCall(call_info, STRING_2_UTF8("HandleQueryCallInAccountByMarketCallIn:转接的坐席拒绝接听"));
}

void C2PSipSystem::QueryMarketAccount( const std::string& call_id, const std::string& account_id )
{
	// ALITTLE_PRINT_FUNC;

	// 查找对应的呼叫信息
	C2PCallInfoMap::iterator call_it = m_call_map.find(call_id);
	if (call_it == m_call_map.end()) return;

	C2PCallInfoPtr call_info = call_it->second;

	// 检查呼叫的类型，看看是不是营销接口
	if (call_info->c_call_type != C2PCallInfo::CALLTYPE_MARKET) return;

	// 检查呼叫当前的步骤，看看是不是还是处于通话中
	if (call_info->c_sip_step != C2PCallInfo::SIPSTEP_TALK) return;

	// 如果已经转接过了，那么接直接拦截
	if (call_info->c_market_trans) return;
	call_info->c_market_trans = true;

	// 查找账号，如果账号查找失败，直接停止呼叫
	std::function<void(bool)> func = std::bind(HandleQueryCallInAccountByMarketCallIn, std::placeholders::_1, call_info->c_call_id);
	bool result = g_CenterManager.QueryCallInAccount(call_info->c_call_id, account_id, "", "", func, std::function<void(bool)>(), false);
	if (result == false) call_info->StopCall(m_sip, STRING_2_UTF8("QueryMarketAccount:没有找到可以转接的坐席"));
}

bool C2PSipSystem::AcceptIVRCallIn( const std::string& call_id, const std::string& other_info )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;

	// 查找是否存在
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end()) return false;

	// 保存携带信息
	it->second->c_other_info = other_info;
	// 接听呼叫
	it->second->CallInOK(m_sip);
	return true;
}

void HandleQueryCallInAccountByIVRCallIn(bool result, const std::string& call_id)
{
	C2PCallInfoPtr call_info = g_C2PSipSystem.GetCallInfoByID(call_id);
	if (!call_info) return;

	if (result == false)
		call_info->NotifyIVRAnswer(false);
	else
		call_info->NotifyIVRAnswer(true);
}

void C2PSipSystem::QueryIVRAccount( ModuleClientPtr sender, const std::string& call_id, const std::string& account_id
								   , bool rewrite_other_info, const std::string& other_info )
{
	// ALITTLE_PRINT_FUNC;

	// 查找对应的呼叫信息
	C2PCallInfoMap::iterator call_it = m_call_map.find(call_id);
	if (call_it == m_call_map.end())
	{
		Protocol::Sip2InterfaceIVRAccountResult msg;
		msg.result = false;
		msg.call_id = call_id;
		msg.reason = "can't find call_id";
		msg.other_info = "";
		sender->Send(msg);
		return;
	}

	C2PCallInfoPtr call_info = call_it->second;

	// 检查呼叫的类型，看看是不是营销接口
	if (call_info->c_call_type != C2PCallInfo::CALLTYPE_IVR)
	{
		Protocol::Sip2InterfaceIVRAccountResult msg;
		msg.result = false;
		msg.call_id = call_id;
		msg.reason = "call_id is not a ivr";
		msg.other_info = "";
		sender->Send(msg);
		return;
	}

	// 覆盖携带参数
	if (rewrite_other_info) call_info->c_other_info = other_info;

	// 检查呼叫当前的步骤，看看是不是还是处于通话中
	if (call_info->c_sip_step != C2PCallInfo::SIPSTEP_TALK)
	{
		Protocol::Sip2InterfaceIVRAccountResult msg;
		msg.result = false;
		msg.call_id = call_id;
		msg.reason = "ivr self is not in talk";
		msg.other_info = call_it->second->c_other_info;
		sender->Send(msg);
		return;
	}

	// 查找账号，如果账号查找失败，直接停止呼叫
	std::function<void(bool)> func = std::bind(HandleQueryCallInAccountByIVRCallIn, std::placeholders::_1, call_id);
	bool result = g_CenterManager.QueryCallInAccount(call_info->c_call_id, account_id, "", "", func, std::function<void(bool)>(), false);
	if (result == false)
	{
		Protocol::Sip2InterfaceIVRAccountResult msg;
		msg.result = false;
		msg.call_id = call_id;
		msg.reason = "account is can't not to receive";
		msg.other_info = call_it->second->c_other_info;
		sender->Send(msg);
	}
}

C2PCallInfoPtr C2PSipSystem::StartTransferIVR( InterfaceManager::InterfaceInfoCallPtr _interface
												 , const std::string& call_id
												 , const std::vector<std::string>& from_number
												 , const std::string& to_number
												 , const std::string& xianlu_name, const std::string& xianlu_subname
												 , const std::string& other_info
												 , int corp
												 , bool need_dtmf
												 , std::string& out_from_number
												 , std::string& reason
												 , bool& repeat )
{
	// ALITTLE_PRINT_FUNC;

	repeat = false;

	if (!m_sip)
	{
		reason = "sip is null";
		return C2PCallInfoPtr();
	}

	if (AppDelegate::s_sip_open == false)
	{
		repeat = false;
		reason = STRING_2_UTF8("SIP线路已关闭:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// 查找对应的线路信息
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP线路不存在:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// 检查线路资源是否足够
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP线路资源不足:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "该区间时间内不能呼出:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效号码:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 检查号码是否超出限制
	if (IsShowNumberLimit(from_number, hcode->area_code, hcode_corp, out_from_number, reason))
	{
		ALITTLE_INFO("IsShowNumberLimit:" << reason);
		repeat = true;
		return C2PCallInfoPtr();
	}

	int sip_type = SIPTYPE_NONE;
	if (hcode_corp == PhoneHCode::HCODECORP_DX)
		sip_type = SIPTYPE_DX;
	else if (hcode_corp == PhoneHCode::HCODECORP_YD)
		sip_type = SIPTYPE_YD;
	else if (hcode_corp == PhoneHCode::HCODECORP_LT)
		sip_type = SIPTYPE_LT;
	else
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "无效归属地:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// 区域限制判断
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// 创建Rtp
	unsigned int client_id = rand() % 1000000;
	unsigned int ssrc = rand() % 1000000;
	std::string c_rtp_ip_dx;
	std::string c_rtp_ip_yd;
	std::string c_rtp_ip_lt;
	int c_rtp_port;
	std::string p_rtp_ip;
	int p_rtp_port;
	int p_rtcp_port;
	std::string i_rtp_ip;
	int i_rtp_port;
	ModuleReceiverPtr rtp = g_RtpManager.UseRtp(call_id, client_id, ssrc, "", 0, need_dtmf, m_targetsip.audio_number, corp, true, false, start_time
		, c_rtp_ip_dx, c_rtp_ip_yd, c_rtp_ip_lt, c_rtp_port, p_rtp_ip, p_rtp_port, p_rtcp_port, i_rtp_ip, i_rtp_port);
	if (!rtp)
	{
		repeat = true;
		reason = STRING_2_UTF8("RTP资源不足!");
		return C2PCallInfoPtr();
	}

	// 把使用点加1，并通知所有Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// 创建C2PCallInfo对象
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// 保存账号对象
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TRANS_IVR;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1041";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// 保存Rtp的基本信息
	call_info->c_client_id = client_id;
	call_info->c_ssrc = ssrc;
	call_info->c_rtp_ip_dx = c_rtp_ip_dx;
	call_info->c_rtp_ip_yd = c_rtp_ip_yd;
	call_info->c_rtp_ip_lt = c_rtp_ip_lt;
	call_info->c_rtp_port = c_rtp_port;
	call_info->p_rtp_ip = p_rtp_ip;
	call_info->p_rtp_port = p_rtp_port;
	call_info->p_rtcp_port = p_rtcp_port;
	call_info->i_rtp_ip = i_rtp_ip;
	call_info->i_rtp_port = i_rtp_port;
	call_info->c_rtp = rtp;

	// 保存Sip的基本信息
	call_info->c_via_branch = "z9hG4bK-" + Utility::GenerateID("via_branch");
	call_info->c_call_id = call_id;
	call_info->c_out_or_in = true;

	call_info->c_from_sip_ip = m_local_sip_ip;
	call_info->c_from_sip_port = m_local_sip_port;
	call_info->c_from_sip = m_local_sip;
	call_info->c_from_tag = Utility::GenerateID("from_tag");
	call_info->c_from_number = out_from_number;

	call_info->c_to_sip_ip = m_targetsip.target_sip_ip;
	call_info->c_to_sip_port = m_targetsip.target_sip_port;
	call_info->c_to_sip = m_targetsip.target_sip;
	call_info->c_to_tag = "";
	call_info->c_to_number = to_number;

	call_info->c_target_sip = call_info->c_to_sip;
	call_info->c_audio_number = m_targetsip.audio_number;
	call_info->c_audio_name = m_targetsip.audio_name;

	call_info->c_dtmf_number = "101";
	call_info->c_dtmf_rtpmap = "a=rtpmap:101 telephone-event/8000";
	call_info->c_dtmf_fmtp = "a=fmtp:101 0-15";

	call_info->c_target_sip = call_info->c_to_sip;

	// 执行呼出
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

bool C2PSipSystem::NotifyDatabaseAllResource(int frame_time)
{
	SimpleJsonObject param;
	param["c_log_time"] = (int)time(0);

	param["c_xianlu_name"] = m_targetsip.xianlu_name;
	param["c_xianlu_subname"] = m_targetsip.xianlu_subname;
	param["c_sip_target"] = m_targetsip.target_sip_ip + ":" + m_targetsip.target_sip_port;
	param["c_total_count"] = m_targetsip.max_call;
	param["c_use_count"] = m_targetsip.use_call;
	
	g_ScheduleManager.SendDataBaseInnerMessage("SipResource", param);

	return false;
}

void C2PSipSystem::NotifySenderAllResource( ModuleClientPtr sender )
{
	{
		Protocol::Sip2XResourceInit msg;
		msg.xianlu_name = m_targetsip.xianlu_name;
		msg.xianlu_subname = m_targetsip.xianlu_subname;
		msg.use_call = m_targetsip.use_call;
		msg.max_call = m_targetsip.max_call;
		msg.dianxin_weight = m_targetsip.dianxin_weight;
		msg.yidong_weight = m_targetsip.yidong_weight;
		msg.liantong_weight = m_targetsip.liantong_weight;
		msg.fixed_weight = m_targetsip.fixed_weight;
		msg.fixed_range_or_ab = m_targetsip.fixed_range_or_ab;
		msg.fixed_list = m_targetsip.fixed_list;
		msg.audio_number = m_targetsip.audio_number;
		sender->Send(msg);
	}
	{
		Protocol::Sip2XResourceUsage msg;
		msg.xianlu_name = m_targetsip.xianlu_name;
		msg.xianlu_subname = m_targetsip.xianlu_subname;
		msg.userate_is_persent = (GET_CONFIG_STRING("userate_is_persent", "true") == "true");
		msg.userate_persent = GET_CONFIG_DOUBLE("userate_persent", 0.02);
		msg.userate_margin = GET_CONFIG_DOUBLE("userate_margin", 1);
		sender->Send(msg);
	}
}

void C2PSipSystem::NotifySenderAllResource( ModuleReceiverPtr sender )
{
	{
		Protocol::Sip2XResourceInit msg;
		msg.xianlu_name = m_targetsip.xianlu_name;
		msg.xianlu_subname = m_targetsip.xianlu_subname;
		msg.use_call = m_targetsip.use_call;
		msg.max_call = m_targetsip.max_call;
		msg.dianxin_weight = m_targetsip.dianxin_weight;
		msg.yidong_weight = m_targetsip.yidong_weight;
		msg.liantong_weight = m_targetsip.liantong_weight;
		msg.fixed_weight = m_targetsip.fixed_weight;
		msg.fixed_range_or_ab = m_targetsip.fixed_range_or_ab;
		msg.fixed_list = m_targetsip.fixed_list;
		msg.audio_number = m_targetsip.audio_number;
		sender->Send(msg, 0, 0);
	}
	{
		Protocol::Sip2XResourceUsage msg;
		msg.xianlu_name = m_targetsip.xianlu_name;
		msg.xianlu_subname = m_targetsip.xianlu_subname;
		msg.userate_is_persent = (GET_CONFIG_STRING("userate_is_persent", "true") == "true");
		msg.userate_persent = GET_CONFIG_DOUBLE("userate_persent", 0.02);
		msg.userate_margin = GET_CONFIG_DOUBLE("userate_margin", 1);
		sender->Send(msg, 0, 0);
	}

}

bool C2PSipSystem::UpdateLogic( int frame_time )
{
	int cur_time = (int)time(0);
	{
		// 处理呼叫
		C2PCallInfoWeakMap::iterator it, end = m_call_weak_map.end();
		for (it = m_call_weak_map.begin(); it != end;)
		{
			// 如果已经销毁了，直接删除掉
			C2PCallInfoPtr call_info = it->second.lock();
			if (!call_info)
			{
				it = m_call_weak_map.erase(it);
				continue;
			}

			// 如果正在通话，那么就直接移除
			if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK)
			{
				it = m_call_weak_map.erase(it);
				continue;
			}

			// 处理INVITE
			if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_INVITE)
			{
				// 重发5次
				if (call_info->c_invite_count < 5)
				{
					// 如果直接超过两秒，重新发起
					if (cur_time - call_info->c_sip_send_time > 2)
						call_info->CallOutInviteImpl(m_sip, cur_time);
				}
				// 超过5次，那么就直接移除
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理接受到TRYING事件
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_TRYING)
			{
				// 如果这个状态超过10分钟，那么就直接移除
				if (cur_time - call_info->c_sip_receive_time > 60 * 10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理RINGRING事件
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_RINGING)
			{
				// 如果振铃时间超过10分钟，那么就直接移除
				if (cur_time - call_info->c_sip_receive_time > 60 * 10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理主动发送的CANCEL事件
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_CANCELING)
			{
				if (call_info->c_cancel_count < 15)
				{
					// 如果主动撤销的重复发送，知道对方有应答，只要有应答那么流程就可以顺利结束
					if (cur_time - call_info->c_sip_send_time >= 1)
						call_info->CallOutCancel(m_sip);
				}
				// 超过5次，那么就直接移除
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理呼入拒接
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_FORBIDDEN)
			{
				if (call_info->c_forbidden_count < 5)
				{
					// 如果呼入拒接，重复发送，只要有应答那么流程就可以顺利结束
					if (cur_time - call_info->c_sip_send_time > 10)
						call_info->CallInForbiddenImpl(m_sip);
				}
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理呼入响铃
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_RINGING)
			{
				// 如果呼入响铃持续非常久，比如3分钟，那么直接释放
				if (cur_time - call_info->c_sip_send_time > 60*10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理呼入接听
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_OK)
			{
				if (call_info->c_ok_count < 50)
				{
					// 如果呼入接听持续时间比较久，就重复发送
					if (cur_time - call_info->c_sip_send_time > 30)
						call_info->CallInOKImpl(m_sip);
				}
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// 处理挂断事件
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK_BYING)
			{
				if (call_info->c_bye_count < 50)
				{
					// 如果挂断事件持续事件比较久，就直接发送
					if (cur_time - call_info->c_sip_send_time > 30)
						call_info->TalkByeImpl(m_sip);
				}
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}

			++ it;
		}
	}

	return false;
}

bool C2PSipSystem::CheckRegister( int frame_time )
{
	int cur_time = (int)time(0);

	if (!m_sip) return false;

	int max_register = m_targetsip.register_max + m_targetsip.add_register_count;
	if (s_first_register == true)
	{
		max_register = (int)m_number_list.size();
		s_first_register = false;
	}
	m_targetsip.add_register_count = 0;

	// 处理注册
	{
		RegisterNumberList::iterator src_it, src_end = m_number_list.end();
		for (src_it = m_number_list.begin(); src_it != src_end;)
		{
			(*src_it)->last_resgiter_time = cur_time;
			(*src_it)->register_call_id = DoSipRegister1((*src_it)->show_account, (*src_it)->account, (*src_it)->password);

			m_registering_map[(*src_it)->show_account] = *src_it;

			// 从原生队列移除
			src_it = m_number_list.erase(src_it);

			-- max_register;
			if (max_register <= 0) break;
		}
	}

	// 如果出现没注册成功的，超过一分钟，立即注册
	{
		RegisterNumberMap::iterator src_it, src_end = m_registering_map.end();
		for (src_it = m_registering_map.begin(); src_it != src_end; ++src_it)
		{
			if (cur_time - src_it->second->last_resgiter_time > 60)
			{
				// 如果上次注册时间超过指定间隔，那么就自行注册
				src_it->second->last_resgiter_time = cur_time;
				src_it->second->register_call_id = DoSipRegister1(src_it->second->show_account, src_it->second->account, src_it->second->password);
			}
		}
	}

	return false;
}

bool C2PSipSystem::UpdateSession( int frame_time )
{
	int cur_time = (int)time(0);

	C2PCallInfoWeakMap::iterator it, end = m_session_expires_map.end();
	for (it = m_session_expires_map.begin(); it != end;)
	{
		// 如果已经销毁了，直接删除掉
		C2PCallInfoPtr call_info = it->second.lock();
		if (!call_info)
		{
			it = m_session_expires_map.erase(it);
			continue;
		}

		call_info->SendSession(m_sip, cur_time);
		++ it;
	}
	return false;
}

bool C2PSipSystem::UpdateConfigFile( int frame_time )
{
	ConfigSystem config;

	std::string config_path = GET_CONFIG_STRING("config_path", "");
	if (config_path != "") config.SetConfigByFile(config_path.c_str());

	// 获取所有的呼叫频率
	m_targetsip.call_time_unit = config.GetConfigIntByDefault("call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.call_count_unit = config.GetConfigIntByDefault("call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.dx_call_time_unit = config.GetConfigIntByDefault("dx_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.dx_call_count_unit = config.GetConfigIntByDefault("dx_call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.lt_call_time_unit = config.GetConfigIntByDefault("lt_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.lt_call_count_unit = config.GetConfigIntByDefault("lt_call_count_unit", 0);		// 单位时间次数限制

	m_targetsip.yd_call_time_unit = config.GetConfigIntByDefault("yd_call_time_unit", 0);		// 呼入的时间单位限制
	m_targetsip.yd_call_count_unit = config.GetConfigIntByDefault("yd_call_count_unit", 0);		// 单位时间次数限制

	std::string old_register_info = GET_CONFIG_STRING("register_info", "");
	std::string register_info = config.GetConfigStringByDefault("register_info", "");		// SIP的账号密码
	
	if (old_register_info.size() == register_info.size()
		&& old_register_info == register_info) return false;

	g_ConfigSystem.SetConfig("register_info", register_info.c_str());

	std::vector<std::string> register_info_list;
	Utility::SplitString(register_info, ";", register_info_list);
	for (unsigned int i = 0; i < register_info_list.size(); ++i)
	{
		std::vector<std::string> info_list;
		Utility::SplitString(register_info_list[i], ",", info_list);
		if (info_list.size() != 3)
		{
			ALITTLE_ERROR("splite by , error:" << register_info_list[i] << STRING_2_UTF8(", usage: 显示名,鉴权用户名,鉴权密码"));
			continue;
		}

		RegisterNumberMap::iterator it = m_number_map_info.find(info_list[0]);
		if (it != m_number_map_info.end())
		{
			it->second->show_account = info_list[0];
			it->second->account = info_list[1];
			it->second->password = info_list[2];
			continue;
		}

		RegisterNumberInfoPtr info = RegisterNumberInfoPtr(new RegisterNumberInfo);
		m_number_map_info[info_list[0]] = info;
		m_number_list.push_front(info);

		info->show_account = info_list[0];
		info->account = info_list[1];
		info->password = info_list[2];
		info->last_resgiter_time = 0;

		++ m_targetsip.add_register_count;
	}

	CalcCheckRegister();

	return false;
}


// 检查残留非常久的呼叫，用于流程差错
bool C2PSipSystem::CheckCallLast( int frame_time )
{
	int cur_time = (int)time(0);

	C2PCallInfoMap::iterator it, end = m_call_map.end();
	for (it = m_call_map.begin(); it != end; ++it)
	{
		int delta_time = cur_time - it->second->c_start_time;
		if (delta_time > 60*60)
		{
			ALITTLE_INFO(it->second->c_call_id << ": LONG LAST, " << it->second->c_start_time);
			HandleSipLogCallback(it->second->c_call_id, "LONG LAST");
		}
	}
	
	return false;
}

void C2PSipSystem::HandleErrorSip( asio::ip::udp::endpoint ep, UDPSystemPtr sip
								  , const std::string& method
								  , const std::string& status
								  , const std::vector<std::string>& response_list
								  , const std::vector<std::string>& content_list )
{
	if (method == "SIP/2.0" && (status.size() > 1 && (status[0] == '4' || status[0] == '5' || status[0] == '6')))
	{
		std::string via = C2PCallInfo::GetKeyValueFromUDP(content_list, "VIA");
		std::string from = C2PCallInfo::GetKeyValueFromUDP(content_list, "FROM");
		std::string to = C2PCallInfo::GetKeyValueFromUDP(content_list, "TO");
		std::string cseq = C2PCallInfo::GetKeyValueFromUDP(content_list, "CSEQ");
		std::string call_id = C2PCallInfo::GetKeyValueFromUDP(content_list, "CALL-ID");

		std::string to_number;
		C2PCallInfo::GetToFromUDP(content_list, to_number, std::string());
		std::string sip_head = "ACK sip:"+C2PCallInfo::EncodeNumber(to_number)+"@"+ep.address().to_v4().to_string()+":"+Utility::FormateToString(ep.port())+" SIP/2.0\r\n"
			"Via: " + via + "\r\n"
			"From: " + from + "\r\n"
			"To: " + to + "\r\n"
			"Call-ID: " + call_id + "\r\n"
			"CSeq: 1 ACK\r\n"
			"Content-Length: 0\r\n\r\n";

		ALITTLE_INFO("alittle send ------------------->:ACK, CALLID:" << call_id);
		sip->Send(sip_head, ep);

		g_C2PSipSystem.HandleSipLogCallback(call_id, std::string() + "SEND ==>" + sip_head);
	}
	else if (method == "BYE")
	{
		// 因为VIA中的branch值可能发生变化，所以要重新获取一下
		std::string via = C2PCallInfo::GetKeyValueFromUDP(content_list, "VIA");
		std::string from = C2PCallInfo::GetKeyValueFromUDP(content_list, "FROM");
		std::string to = C2PCallInfo::GetKeyValueFromUDP(content_list, "TO");
		std::string cseq = C2PCallInfo::GetKeyValueFromUDP(content_list, "CSEQ");
		std::string call_id = C2PCallInfo::GetKeyValueFromUDP(content_list, "CALL-ID");

		std::string sip_head = "SIP/2.0 200 OK\r\n"
			"Via: " + via + "\r\n"
			"From: " + from + "\r\n"
			"To: " + to + "\r\n"
			"Call-ID: " + call_id + "\r\n"
			"CSeq: " + cseq + "\r\n"
			"Content-Length: 0\r\n\r\n";

		ALITTLE_INFO("alittle send ------------------->:OK, CALLID:" << call_id);
		sip->Send(sip_head, ep);

		g_C2PSipSystem.HandleSipLogCallback(call_id, std::string() + "SEND ==>" + sip_head);
	}
	else if (method == "NOTIFY")
	{
		// 因为VIA中的branch值可能发生变化，所以要重新获取一下
		std::string via = C2PCallInfo::GetKeyValueFromUDP(content_list, "VIA");
		std::string from = C2PCallInfo::GetKeyValueFromUDP(content_list, "FROM");
		std::string to = C2PCallInfo::GetKeyValueFromUDP(content_list, "TO");
		std::string cseq = C2PCallInfo::GetKeyValueFromUDP(content_list, "CSEQ");
		std::string call_id = C2PCallInfo::GetKeyValueFromUDP(content_list, "CALL-ID");

		std::string sip_head = "SIP/2.0 200 OK\r\n"
			"Via: " + via + "\r\n"
			"From: " + from + "\r\n"
			"To: " + to + "\r\n"
			"Call-ID: " + call_id + "\r\n"
			"CSeq: " + cseq + "\r\n"
			"Content-Length: 0\r\n\r\n";

		ALITTLE_INFO("alittle send ------------------->:OK, CALLID:" << call_id);
		sip->Send(sip_head, ep);

		g_C2PSipSystem.HandleSipLogCallback(call_id, std::string() + "SEND ==>" + sip_head);
	}
}

void C2PSipSystem::RemoveOnlyOneCall( const std::string& number )
{
	C2POnlyOneCallMap::iterator it = m_only_one_call_map.find(number);
	if (it == m_only_one_call_map.end()) return;

	it->second.cur_count --;

	if (it->second.cur_count < 0)
	{
		ALITTLE_ERROR("only one call(" << it->second.cur_count << ") < 0");
	}
}

void C2PSipSystem::AddOnlyOneCall( const std::string& number )
{
	C2POnlyOneCallMap::iterator it = m_only_one_call_map.find(number);
	if (it == m_only_one_call_map.end())
	{
		OnlyOneCallInfo info;
		info.cur_count = 1;
		m_only_one_call_map[number] = info;
		return;
	}

	it->second.cur_count ++;
	if (it->second.cur_count > m_targetsip.only_one_call)
	{
		ALITTLE_ERROR("only one call(" << it->second.cur_count << ") > max_call(" << m_targetsip.only_one_call << ")");
	}
}

void C2PSipSystem::SetOnlyOneMaxCall( const std::string& number, int max_call, bool update_sqlite )
{
	C2POnlyOneCallMap::iterator it = m_only_one_call_map.find(number);
	if (it == m_only_one_call_map.end())
	{
		OnlyOneCallInfo info;
		info.max_call = max_call;
		info.cur_count = 0;
		m_only_one_call_map[number] = info;
	}
	else
	{
		it->second.max_call = max_call;
	}

	ALITTLE_INFO("SetOnlyOneMaxCall Add:" << max_call);

	// 把数据保存到数据库
	if (update_sqlite)
	{
		SimpleJsonObject param;
		param["c_ims"] = number;
		param["c_max_call"] = max_call;
		g_ScheduleManager.SendDataBaseInnerMessage("UpdateOnlyOneCall", param);
	}
}

void C2PSipSystem::SetAreaLimit( const std::string& number, const std::string& list, int range_or_ab, bool update_sqlite )
{
	std::map<std::string, bool> tmp_map;
	std::vector<std::string> split_list;
	Utility::SplitString(list, "|", split_list);	// 固话和手机区号范围(如果不填，表示全部范围，如果有填标示指定范围)
	for (unsigned int i = 0; i < split_list.size(); ++i)
		tmp_map[split_list[i]] = true;

	C2PAreaCallMap::iterator it = m_area_call_map.find(number);
	if (it == m_area_call_map.end())
	{
		AreaCallInfo info;
		info.range_map = tmp_map;
		info.range_or_ab = range_or_ab;
		m_area_call_map[number] = info;
	}
	else
	{
		it->second.range_map = tmp_map;
		it->second.range_or_ab = range_or_ab;
	}
	ALITTLE_INFO("SetAreaLimit:" << number << "," << list << "," << range_or_ab);

	// 把数据保存到数据库
	if (update_sqlite)
	{
		SimpleJsonObject param;
		param["c_ims"] = number;
		param["c_list"] = list;
		param["c_range_or_ab"] = range_or_ab;
		g_ScheduleManager.SendDataBaseInnerMessage("UpdateAreaCall", param);
	}
}

bool C2PSipSystem::IsShowNumberLimit(const std::vector<std::string>& number, const std::string& area_code, PhoneHCode::HCodeCorp corp, std::string& out_from_number, std::string& reason)
{
	// 获取当前时间
	int cur_time = (int)time(0);

	int min_count = -1;
	NumberInfo* target_info = 0;
	int number_index = 0;

	int random_offset = rand() % number.size();

	// 遍历所有号码
	for (unsigned int i = 0; i < number.size(); ++i)
	{
		unsigned int index = (i + random_offset) % number.size();
		std::string cur_number = number[index];

		NumberInfo* info_tmp = 0;
		// 如果没有查找到，那么就初始化
		ShowNumberLimitMap::iterator it = m_limit_map.find(cur_number);
		if (it == m_limit_map.end())
		{
			NumberInfo& info = m_limit_map[cur_number] = NumberInfo();
			info.start_time = cur_time;
			info.call_count = 0;
			info.dx_start_time = cur_time;
			info.dx_call_count = 0;
			info.lt_start_time = cur_time;
			info.lt_call_count = 0;
			info.yd_start_time = cur_time;
			info.yd_call_count = 0;
			
			info_tmp = &info;
		}
		else
		{
			info_tmp = &(it->second);
			// 如果超出单位时间，那么就初始化
			if (m_targetsip.call_time_unit > 0 && cur_time - info_tmp->start_time > m_targetsip.call_time_unit)
			{
				info_tmp->start_time = cur_time;
				info_tmp->call_count = 0;
			}

			// 如果超出单位时间，那么就初始化
			if (m_targetsip.dx_call_time_unit > 0 && cur_time - info_tmp->dx_start_time > m_targetsip.dx_call_time_unit)
			{
				info_tmp->dx_start_time = cur_time;
				info_tmp->dx_call_count = 0;
			}

			// 如果超出单位时间，那么就初始化
			if (m_targetsip.lt_call_time_unit > 0 && cur_time - info_tmp->lt_start_time > m_targetsip.lt_call_time_unit)
			{
				info_tmp->lt_start_time = cur_time;
				info_tmp->lt_call_count = 0;
			}

			// 如果超出单位时间，那么就初始化
			if (m_targetsip.yd_call_time_unit > 0 && cur_time - info_tmp->yd_start_time > m_targetsip.yd_call_time_unit)
			{
				info_tmp->yd_start_time = cur_time;
				info_tmp->yd_call_count = 0;
			}
		}

		// 如果有设定范围，并且超出范围那么就直接返回
		if (m_targetsip.call_count_unit > 0 && info_tmp->call_count >= m_targetsip.call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("总呼出频率太快;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_DX && m_targetsip.dx_call_count_unit > 0 && info_tmp->dx_call_count >= m_targetsip.dx_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("呼叫电信频率太快;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_LT && m_targetsip.lt_call_count_unit > 0 && info_tmp->lt_call_count >= m_targetsip.lt_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("呼叫联通频率太快;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_YD && m_targetsip.yd_call_count_unit > 0 && info_tmp->yd_call_count >= m_targetsip.yd_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("呼叫移动频率太快;");
			continue;
		}

		// 如果有设定一个主显只能同时一个呼叫，那么检查一下
		int max_call = m_targetsip.only_one_call;
		C2POnlyOneCallMap::iterator only_one_call_it = m_only_one_call_map.find(cur_number);
		if (only_one_call_it != m_only_one_call_map.end() && only_one_call_it->second.max_call > 0)
			max_call = only_one_call_it->second.max_call;

		if (only_one_call_it != m_only_one_call_map.end() && max_call > 0 && only_one_call_it->second.cur_count >= max_call)
		{
			reason += cur_number + STRING_2_UTF8("占用中;") + Utility::FormateToString(only_one_call_it->second.cur_count) + ";" + Utility::FormateToString(max_call);
			continue;
		}

		// 检查这个号码有没有区域限制
		C2PAreaCallMap::iterator area_call_it = m_area_call_map.find(cur_number);
		if (area_code.size() && area_call_it != m_area_call_map.end())
		{
			if (area_call_it->second.range_or_ab > 0)
			{
				if (area_call_it->second.range_map.size() && area_call_it->second.range_map.find(area_code) == area_call_it->second.range_map.end())
				{
					reason += cur_number + STRING_2_UTF8("限制呼出该区域;") + area_code;
					continue;
				}
			}
			else
			{
				if (area_call_it->second.range_map.size() == 0 || area_call_it->second.range_map.find(area_code) != area_call_it->second.range_map.end())
				{
					reason += cur_number + STRING_2_UTF8("限制呼出该区域;") + area_code;
					continue;
				}
			}
		}

		// 检查是否超出消费额度
		if (g_ImsManager.CheckConsumeLimit(cur_number))
		{
			reason += cur_number + STRING_2_UTF8("超出消费额度;");
			continue;
		}
		
		// 找出次数最少的那个
		if (min_count == -1 || info_tmp->call_count < min_count)
		{
			min_count = info_tmp->call_count;
			target_info = info_tmp;
			number_index = index;
		}
	}

	if (target_info)
	{
		out_from_number = number[number_index];
		++ (target_info->call_count);
		if (corp == PhoneHCode::HCodeCorp::HCODECORP_DX)
			++ (target_info->dx_call_count);
		else if (corp == PhoneHCode::HCodeCorp::HCODECORP_LT)
			++ (target_info->lt_call_count);
		else if (corp == PhoneHCode::HCodeCorp::HCODECORP_YD)
			++ (target_info->yd_call_count);
		return false;
	}

	return true;
}

bool C2PSipSystem::IsAreaCodeLimit( const std::string& area_code, PhoneHCode::HCodeCorp corp, bool is_fixed, std::string& reason )
{
	// 判断运营商是否限制
	if (is_fixed && m_targetsip.fixed_weight <= 0.0)
	{
		reason = STRING_2_UTF8("该线路限制固话号码呼出");
		return true;
	}
	
	if (corp == PhoneHCode::HCODECORP_DX && m_targetsip.dianxin_weight <= 0.0)
	{
		reason = STRING_2_UTF8("该线路限制电信手机号码呼出");
		return true;
	}

	if (corp == PhoneHCode::HCODECORP_LT && m_targetsip.liantong_weight <= 0.0)
	{
		reason = STRING_2_UTF8("该线路限制联通手机号码呼出");
		return true;
	}

	if (corp == PhoneHCode::HCODECORP_YD && m_targetsip.yidong_weight <= 0.0)
	{
		reason = STRING_2_UTF8("该线路限制移动手机号码呼出");
		return true;
	}

	// 判断正选
	if (m_targetsip.fixed_range_or_ab > 0)
	{
		// fixed_range_map大小为0表示全范围
		// 如果是有范围的，并且不再范围之内，就直接返回
		if (m_targetsip.fixed_map.size()
			&& m_targetsip.fixed_map.find(area_code) == m_targetsip.fixed_map.end())
		{
			reason = STRING_2_UTF8("该线路限制呼出该地区的号码:") + area_code;
			return true;
		}
	}
	// 判断反选
	else
	{
		// fixed_range_map大小为0表示全范围
		if (m_targetsip.fixed_map.size() == 0
			|| m_targetsip.fixed_map.find(area_code) != m_targetsip.fixed_map.end())
		{
			reason = STRING_2_UTF8("该线路限制呼出该地区的号码:") + area_code;
			return true;
		}
	}

	return false;
}

const std::string& C2PSipSystem::GetAuthPassword( const std::string& show_account )
{
	static std::string empty_string;
	RegisterNumberMap::iterator it = m_number_map_info.find(show_account);
	if (it == m_number_map_info.end()) return empty_string;
	return it->second->password;
}

const std::string& C2PSipSystem::GetAuthAccount( const std::string& show_account )
{
	static std::string empty_string;
	RegisterNumberMap::iterator it = m_number_map_info.find(show_account);
	if (it == m_number_map_info.end()) return empty_string;
	return it->second->account;
}

std::string C2PSipSystem::DoSipRegister1(const std::string& show_account, const std::string& account, const std::string& password)
{
	std::string call_id = Utility::GenerateID("call_id");
	RegisterSipInfo& info = m_callid_map_registerinfo[call_id] = RegisterSipInfo();

	info.register_status = SipRegister::SIPREGISTER_1;

	info.register_show_account = show_account;
	info.register_account = account;
	info.register_password = password;

	info.register_call_id = call_id;
	info.register_from_tag = Utility::GenerateID("from_tag");

	std::string register_url = m_targetsip.target_sip_domain;
	if (register_url.size() == 0)
		register_url = m_targetsip.target_sip_ip + ":" + m_targetsip.target_sip_port;

	std::string cmd = "REGISTER sip:" + register_url + " SIP/2.0\r\n"
		"Via: SIP/2.0/UDP " + m_local_sip_ip + ":" + m_local_sip_port + ";rport;branch=z9hG4bK-" + Utility::GenerateID("via_branch") +  "\r\n"
		"Max-Forwards: 70\r\n"
		"Contact: <sip:" + show_account + "@" + m_local_sip_ip + ":" + m_local_sip_port + ">\r\n";
	if (m_targetsip.register_show_name)
	{
		cmd +=
		"From: \"" + show_account + "\"<sip:" + show_account + "@" + register_url + ">;tag="+info.register_from_tag+"\r\n"
		"To: \"" + show_account + "\"<sip:" + show_account +"@" + register_url + ">\r\n";
	}
	else
	{
		cmd +=
			"From: <sip:" + show_account + "@" + register_url + ">;tag="+info.register_from_tag+"\r\n"
			"To: <sip:" + show_account +"@" + register_url + ">\r\n";
	}
	cmd +=
		"Call-ID: " + info.register_call_id + "\r\n"
		"CSeq: 1 REGISTER\r\n"
		"Expires: " + m_targetsip.register_expires + "\r\n"
		"Allow: INVITE,ACK,CANCEL,OPTIONS,BYE,REFER,NOTIFY,INFO,MESSAGE,SUBSCRIBE,INFO\r\n"
		"User-Agent: ALittle\r\n"
		"Content-Length: 0\r\n\r\n";

	m_sip->Send(cmd, m_targetsip.target_sip);
	g_C2PSipSystem.HandleSipLogCallback(info.register_call_id, std::string() + "SEND ==>" + cmd);

	ALITTLE_INFO("SEND ==> REGISTER1 " << show_account << ", CALL-ID:" << info.register_call_id);

	return info.register_call_id;
}

bool C2PSipSystem::GetNonceRealm( const std::string& head, const std::vector<std::string>& content_list , std::string& nonce, std::string& realm )
{
	std::string content = C2PCallInfo::GetKeyValueFromUDP(content_list, head);
	{
		std::string::size_type pos_1 = content.find("nonce=\"");
		if (pos_1 == std::string::npos)
			return false;

		pos_1 += strlen("nonce=\"");
		std::string::size_type pos_2 = content.find("\"", pos_1);
		if (pos_2 == std::string::npos)
			return false;

		nonce = content.substr(pos_1, pos_2 - pos_1);
	}
	{
		std::string::size_type pos_1 = content.find("realm=\"");
		if (pos_1 == std::string::npos)
			return false;

		pos_1 += strlen("realm=\"");
		std::string::size_type pos_2 = content.find("\"", pos_1);
		if (pos_2 == std::string::npos)
			return false;

		realm = content.substr(pos_1, pos_2 - pos_1);
	}

	return true;
}

bool C2PSipSystem::GetNextNonce( const std::string& head, const std::vector<std::string>& content_list , std::string& nonce )
{
	std::string content = C2PCallInfo::GetKeyValueFromUDP(content_list, head);
	{
		std::string::size_type pos_1 = content.find("nextnonce=\"");
		if (pos_1 == std::string::npos)
			return false;

		pos_1 += strlen("nextnonce=\"");
		std::string::size_type pos_2 = content.find("\"", pos_1);
		if (pos_2 == std::string::npos)
			return false;

		nonce = content.substr(pos_1, pos_2 - pos_1);
	}

	return true;
}

std::string C2PSipSystem::GenAuth( const std::string& nonce, const std::string& realm
								  , const std::string& account, const std::string& password
								  , const std::string& method, const std::string& uri )
{
	std::string response_1 = ScriptSystem::md5(account+":"+realm+":"+password);
	std::string response_2 = ScriptSystem::md5(method + ":" + uri);
	std::string response = ScriptSystem::md5(response_1 + ":" + nonce + ":" + response_2);

	return "Digest username=\"" + account + "\",realm=\""+realm+"\",nonce=\"" + nonce + "\",uri=\"" + uri + "\",response=\"" + response + "\",algorithm=MD5";
}

bool C2PSipSystem::CalcAuth( const std::string& head, const std::vector<std::string>& content_list
							, const std::string& account, const std::string& password
							, const std::string& method, const std::string& uri
							, std::string& nonce, std::string& realm, std::string& auth )
{
	if (GetNonceRealm(head, content_list, nonce, realm) == false) return false;

	std::string response_1 = ScriptSystem::md5(account+":"+realm+":"+password);
	std::string response_2 = ScriptSystem::md5(method + ":" + uri);
	std::string response = ScriptSystem::md5(response_1 + ":" + nonce + ":" + response_2);

	auth = GenAuth(nonce, realm, account, password, method, uri);
	return true;
}

bool C2PSipSystem::DoSipRegister2(RegisterSipInfo& info, const std::vector<std::string>& content_list)
{
	std::string nonce, realm;
	std::string uri = "sip:" + m_targetsip.target_sip_ip + ":" + m_targetsip.target_sip_port;
	if (m_targetsip.target_sip_domain.size())
		std::string uri = "sip:" + m_targetsip.target_sip_domain;

	bool result = CalcAuth("WWW-AUTHENTICATE", content_list
		, info.register_account, info.register_password
		, "REGISTER", uri
		, nonce, realm, info.register_auth);

	if (nonce.size() == 0)
	{
		ALITTLE_ERROR("can't find nonce");
		info.register_status = SipRegister::SIPREGISTER_FAILED;
		return false;
	}
	if (realm.size() == 0)
	{
		ALITTLE_ERROR("can't find realm");
		info.register_status = SipRegister::SIPREGISTER_FAILED;
		return false;
	}

	info.register_status = SipRegister::SIPREGISTER_2;

	std::string register_url = m_targetsip.target_sip_domain;
	if (register_url.size() == 0)
		register_url = m_targetsip.target_sip_ip + ":" + m_targetsip.target_sip_port;

	std::string cmd = "REGISTER sip:" + register_url + " SIP/2.0\r\n"
		"Via: SIP/2.0/UDP " + m_local_sip_ip + ":" + m_local_sip_port + ";rport;branch=z9hG4bK-" + Utility::GenerateID("via_branch") +  "\r\n"
		"Max-Forwards: 70\r\n"
		"Contact: <sip:" + info.register_show_account + "@" + m_local_sip_ip + ":" + m_local_sip_port + ">\r\n";
	if (m_targetsip.register_show_name)
	{
		cmd +=
			"From: \"" + info.register_show_account + "\"<sip:" + info.register_show_account + "@" + register_url + ">;tag="+info.register_from_tag+"\r\n"
			"To: \"" + info.register_show_account + "\"<sip:" + info.register_show_account +"@" + register_url + ">\r\n";
	}
	else
	{
		cmd +=
			"From: <sip:" + info.register_show_account + "@" + register_url + ">;tag="+info.register_from_tag+"\r\n"
			"To: <sip:" + info.register_show_account +"@" + register_url + ">\r\n";
	}
	cmd +=
		"Call-ID: " + info.register_call_id + "\r\n"
		"CSeq: 2 REGISTER\r\n"
		"Expires: " + m_targetsip.register_expires + "\r\n"
		"Allow: INVITE,ACK,CANCEL,OPTIONS,BYE,REFER,NOTIFY,INFO,MESSAGE,SUBSCRIBE,INFO\r\n"
		"Supported: eventlist\r\n"
		"User-Agent: ALittle\r\n"
		"Authorization: " + info.register_auth + "\r\n"
		"Content-Length: 0\r\n\r\n";

	m_sip->Send(cmd, m_targetsip.target_sip);
	g_C2PSipSystem.HandleSipLogCallback(info.register_call_id, std::string() + "SEND ==>" + cmd);

	ALITTLE_INFO("SEND ==> REGISTER2 " << info.register_show_account << ", CALL-ID:" << info.register_call_id);

	return true;
}

void C2PSipSystem::InviteNotify( const std::string& ims )
{
	if (m_invite_notify_url.size() == 0) return;

	SimpleJsonObject root_json;
	SimpleJsonObject param;
	param["display_ims"] = ims;
	param["charge_ims"] = "";
	param["session_id"] = "";
	param["come_type"] = 0;
	root_json["method"] = "CAASSIPNumberUse";
	root_json["param"] = param;

	std::string content;
	root_json.GetResult(content);
	HttpSystem::SendRequestPostJson(m_invite_notify_url, content, C2PSipSystem::InviteNotifyResult);
}

void C2PSipSystem::InviteNotifyResult( bool result, const std::string& body, const std::string& head )
{
	if (result == false)
	{
		ALITTLE_ERROR("InviteNotify failed!");
		return;
	}
}

void C2PSipSystem::CalcCheckRegister()
{
	if (m_number_map_info.size() == 0 || m_targetsip.register_interval == 0)
	{
		m_targetsip.register_max = 0;
		m_targetsip.check_register_interval = 3600;
		return;
	}

	int old_check_register_interval = m_targetsip.check_register_interval;
	if ((int)m_number_map_info.size() < m_targetsip.register_interval)
	{
		int second_per_count = (int)floor((float)m_targetsip.register_interval / m_number_map_info.size());
		m_targetsip.register_max = 5;
		m_targetsip.check_register_interval = second_per_count * m_targetsip.register_max;
	}
	else
	{
		int count_per_second = (int)ceil((float)m_number_map_info.size() / m_targetsip.register_interval);
		m_targetsip.check_register_interval = 30;
		m_targetsip.register_max = m_targetsip.check_register_interval * count_per_second;
	}

	ALITTLE_INFO("check_register_interval:" << m_targetsip.check_register_interval << ", " << "register_max:" << m_targetsip.register_max);

	// 如果定时器和之前不一样，那么
	if (m_targetsip.check_register_interval != old_check_register_interval)
	{
		ALITTLE_INFO("recreate check register loopobject");
		if (m_loop_check_register)
			AppDelegate::loop_system->RemoveObject(m_loop_check_register);

		// 定时检查呼出去的REGISTER是否有回应
		std::function<bool(int)> func4 = std::bind(&C2PSipSystem::CheckRegister, this, std::placeholders::_1);
		int delay = 1;
		if (s_first_register) delay = 2000;
		m_loop_check_register = AppDelegate::loop_system->AddObject(ALittle::LoopObject(func4, 1000*m_targetsip.check_register_interval, delay));
	}
}

} // ALittle