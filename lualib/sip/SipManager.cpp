
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

	// ��ȡ�Ƿ���Ҫһ��ʼ��ʱ��ע��ȫ������
	s_first_register = (GET_CONFIG_STRING("first_register_all", "true") != "false");

	ALITTLE_INFO("s_first_register:" << (int)s_first_register);

	std::string register_info = GET_CONFIG_STRING("register_info", "");		// SIP���˺�����
	std::vector<std::string> register_info_list;
	Utility::SplitString(register_info, ";", register_info_list);
	for (unsigned int i = 0; i < register_info_list.size(); ++i)
	{
		std::vector<std::string> info_list;
		Utility::SplitString(register_info_list[i], ",", info_list);
		if (info_list.size() != 3)
		{
			ALITTLE_ERROR("splite by , error:" << register_info_list[i] << STRING_2_UTF8(", usage: ��ʾ��,��Ȩ�û���,��Ȩ����"));
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

	m_targetsip.register_show_name = (GET_CONFIG_STRING("register_show_name", "true") != "false");	// Ĭ��ע���ʱ��ʹ��ע����
	m_targetsip.register_interval = GET_CONFIG_INT("register_interval", 900);	// Ĭ��30����ע��һ��
	m_targetsip.register_expires = GET_CONFIG_STRING("register_expires", "3600");	// Ĭ��30����ע��һ��
	m_targetsip.add_register_count = 0;
	m_targetsip.check_register_interval = 0;
	CalcCheckRegister();

	m_targetsip.target_sip_domain = GET_CONFIG_STRING("target_sip_domain", "");		// SIP�Ĵ�������

	m_targetsip.xianlu_name = GET_CONFIG_STRING("xianlu_name", "");			// ����·��
	m_targetsip.xianlu_subname = GET_CONFIG_STRING("xianlu_subname", "");	// ����·��

	m_targetsip.target_sip_ip = GET_CONFIG_STRING("target_sip_ip", "");		// �Խ�SIP��IP
	m_targetsip.target_sip_port = GET_CONFIG_STRING("target_sip_port", "");	// �Խ�SIP�Ķ˿�

	m_targetsip.audio_number = GET_CONFIG_STRING("audio_number", "");		// ����������
	m_targetsip.audio_name = GET_CONFIG_STRING("audio_name", "");			// ������������

	m_targetsip.support_100rel = (GET_CONFIG_STRING("support_100rel", "false") == "true");	// �Ƿ�֧��100rel

	m_targetsip.dianxin_weight = GET_CONFIG_DOUBLE("dianxin_weight", 0);	// ����Ȩ��
	m_targetsip.yidong_weight = GET_CONFIG_DOUBLE("yidong_weight", 0);		// �ƶ�Ȩ��
	m_targetsip.liantong_weight = GET_CONFIG_DOUBLE("liantong_weight", 0);	// ��ͨȨ��
	m_targetsip.fixed_weight = GET_CONFIG_DOUBLE("fixed_weight", 0);		// �̻�Ȩ��

	m_targetsip.fixed_range_or_ab = GET_CONFIG_INT("fixed_range_or_ab", 1);	// ����0��ʾ��ѡ��С�ڻ����0��ʾ��ѡ
	Utility::SplitString(GET_CONFIG_STRING("fixed_list", ""), "|", m_targetsip.fixed_list);	// �̻����ֻ����ŷ�Χ(��������ʾȫ����Χ����������ʾָ����Χ)
	for (unsigned int i = 0; i < m_targetsip.fixed_list.size(); ++i)
		m_targetsip.fixed_map[m_targetsip.fixed_list[i]] = true;

	m_targetsip.max_call = GET_CONFIG_INT("max_call", 0);					// ��·��������
	m_targetsip.use_call = 0;

	m_targetsip.callin_pre = GET_CONFIG_STRING("callin_pre", "");					// ����ǰ׺
	m_targetsip.callout_pre = GET_CONFIG_STRING("callout_pre", "");					// ����ǰ׺
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

	m_targetsip.callout_mobile_pre = GET_CONFIG_STRING("callout_mobile_pre", "");	// ��������ʱ���ֻ����Ƿ��ǰ׺
	m_targetsip.callout_mobile_area = GET_CONFIG_STRING("callout_mobile_area", "");	// ���ǰ׺������

	m_targetsip.call_time_unit = GET_CONFIG_INT("call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.call_count_unit = GET_CONFIG_INT("call_count_unit", 0);		// ��λʱ���������

	m_targetsip.dx_call_time_unit = GET_CONFIG_INT("dx_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.dx_call_count_unit = GET_CONFIG_INT("dx_call_count_unit", 0);		// ��λʱ���������

	m_targetsip.lt_call_time_unit = GET_CONFIG_INT("lt_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.lt_call_count_unit = GET_CONFIG_INT("lt_call_count_unit", 0);		// ��λʱ���������

	m_targetsip.yd_call_time_unit = GET_CONFIG_INT("yd_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.yd_call_count_unit = GET_CONFIG_INT("yd_call_count_unit", 0);		// ��λʱ���������

	// ��ȡͬһ�������Ƿ�ֻ�ܴ�һ���绰����
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

	// ֪ͨurl
	m_invite_notify_url = GET_CONFIG_STRING("invite_notify_url", "");

	// ��ȡSIP��ip�Ͷ˿�
	m_local_sip_ip = GET_CONFIG_STRING("sip_local_ip", "");
	m_local_sip_port = GET_CONFIG_STRING("sip_local_port", "");
	m_local_sip = asio::ip::udp::endpoint(asio::ip::address_v4::from_string(m_local_sip_ip), Utility::FormateToInt(m_local_sip_port.c_str()));

	// �򿪶˿�
	m_sip = UDPSystemPtr(new UDPSystem);
	bool result = m_sip->Start(m_local_sip_ip, Utility::FormateToInt(m_local_sip_port.c_str()), 10000);
	m_sip->RegisterUDPHandle(C2PSipSystem::HandleSip);

	// ��ʱ֪ͨSIP��Դ�����ݿ������
	std::function<bool(int)> func1 = std::bind(&C2PSipSystem::NotifyDatabaseAllResource, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func1, 5000, 5000));

	// ��ʱ������ȥ��INVITE�Ƿ���trying��Ӧ
	std::function<bool(int)> func2 = std::bind(&C2PSipSystem::UpdateLogic, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func2, 1000, 2000));
	
	// ��ʱ������̫�õĺ���
	std::function<bool(int)> func3 = std::bind(&C2PSipSystem::CheckCallLast, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func3, 1000*60*60, 1000*60*60));

	// ��Ԫ����
	int session_expires_interval = GET_CONFIG_INT("session_expires_interval", 60);
	std::function<bool(int)> func5 = std::bind(&C2PSipSystem::UpdateSession, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func5, 1000*session_expires_interval, 2000));

	// ��ʱ������ã����º���
	int check_config_interval = GET_CONFIG_INT("check_config_interval", 60*10);
	std::function<bool(int)> func6 = std::bind(&C2PSipSystem::UpdateConfigFile, this, std::placeholders::_1);
	AppDelegate::loop_system->AddObject(ALittle::LoopObject(func6, 1000*check_config_interval, 2000));

	// ���Դ���
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
	// ��ȡ��ǰ��־ʱ��
	int log_time = (int)time(0);
	// ���͵����ݿ���������ڴ洢Sip��������
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
		// �����ֺ�������ʱ�����ϹҶ�
		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_RINGING)
		{
			call_info->StopCall(g_C2PSipSystem.m_sip, STRING_2_UTF8("���Խӿڣ����ֱ�������ʱ�����ϹҶ�"));
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
				// client_idҪ��֮ǰ�Ĳ�һ��
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
			// ���ͽ���
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
				msg.status = "END"; // ���н���
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// �ӿ�״̬֪ͨ����������
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "OUT_RING"; // ��������
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// ֪ͨ�ӿ�״̬
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "OUT_ANWSER"; // ���н���
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// ֪ͨRTP����������ʲô����
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
					// ��ӿ�ѯ�ʣ�ʹ���Ǹ��˺�ת��
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
				// ���ͽ���
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "END"; // ���н���
					if (call_info->c_match_reason.size())
						msg.reason = call_info->c_match_reason;
					else
						msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}

				// ���˺ŷ���ͨ�������¼�
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// �ӿ�״̬֪ͨ��ת�Ӷ�������
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_RING"; // ת�Ӷ�������
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// ֪ͨ�ӿ�׼��ת��
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
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}
				// ֪ͨ�ӿ�״̬
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "IN_ANWSER"; // ת�ӽ���
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// ���ͽ���
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_END"; // ���н���
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_RINGING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// ֪ͨ�ӿ�׼��ת��
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
				// ���ͽ���
				{
					Protocol::Sip2InterfaceMarketStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_UNATTENDED_TRANS_END"; // ���н���
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_RINGING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK:
			{
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// ֪ͨ�ӿ�׼��ת��
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
				// ���ͽ���
				{
					Protocol::Sip2InterfaceNormalStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_UNATTENDED_TRANS_END"; // ���н���
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_IN_INVITE: break;		// ������
		case C2PCallInfo::SIPSTEP_IN_TRYING: break;		// ������
		case C2PCallInfo::SIPSTEP_IN_RINGING: break;	// ������
		case C2PCallInfo::SIPSTEP_IN_OK: break;			// ������
		case C2PCallInfo::SIPSTEP_IN_FORBIDDEN: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������

		case C2PCallInfo::SIPSTEP_TALK:
			{
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}

				// ��RTP��ȡ��
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpOpenDtmf dtmf_msg;
					dtmf_msg.first_port = call_info->p_rtp_port;
					dtmf_msg.open = true;
					call_info->c_rtp->Send(dtmf_msg, 0, 0);
				}

				// ֪ͨ�ӿ�״̬
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "OUT_ANWSER"; // ���н���
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// ֪ͨRTP����������ʲô����
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
				// ���ͽ���
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "END"; // ���н���
					if (call_info->c_match_reason.size())
						msg.reason = call_info->c_match_reason;
					else
						msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}

				// ���˺ŷ���ͨ�������¼�
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
			g_C2PSipSystem.StopCall(call_info->c_call_id, STRING_2_UTF8("HandleStatusCallback:��������"));
			return;
		}

		switch(call_info->c_sip_step)
		{
		case C2PCallInfo::SIPSTEP_OUT_INVITE: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_TRYING: break;	// ������
		case C2PCallInfo::SIPSTEP_OUT_CANCELING: break;	// ������
		case C2PCallInfo::SIPSTEP_TALK_BYING: break;	// ������

		case C2PCallInfo::SIPSTEP_OUT_RINGING:
			{
				{
					// �ӿ�״̬֪ͨ��ת�Ӷ�������
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_RING"; // ת�Ӷ�������
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
				// ֪ͨ�ӿ�׼��ת��
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
				// ֪ͨRTP�رնԱ�
				if (call_info->c_rtp)
				{
					Protocol::Sip2RtpCallTalk talk_msg;
					talk_msg.first_port = call_info->p_rtp_port;
					call_info->c_rtp->Send(talk_msg, 0, 0);
				}
				// ֪ͨ�ӿ�״̬
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = call_info->c_anwser_time;
					msg.status = "IN_ANWSER"; // ת�ӽ���
					msg.reason = reason;
					msg.sip_flag = AppDelegate::SIP_FLAG;
					call_info->c_interface->_interface->sender->Send(msg);
				}
			}
			break;
		case C2PCallInfo::SIPSTEP_TALK_END:
			{
				// ���ͽ���
				{
					Protocol::Sip2InterfaceIVRStatus msg;
					msg.call_id = call_info->c_src_call_id;
					msg.xianlu_name = call_info->c_xianlu_name;
					msg.xianlu_subname = call_info->c_xianlu_subname;
					msg.show_number = call_info->c_from_number;
					msg.target_number = call_info->c_to_number;
					msg.other_info = call_info->c_other_info;
					msg.time = (int)time(0);
					msg.status = "IN_END"; // ���н���
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

	// �����Ƿ����
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

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����").c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("m_targetsip.use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// �������ID
	call_info->m_test_invoke_id = test_invoke_id;

	// �����˺Ŷ���
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TEST;
	call_info->c_bill_type = "200";
	call_info->c_xianlu_name = m_targetsip.xianlu_name;
	call_info->c_xianlu_subname = m_targetsip.xianlu_subname;
	call_info->c_project_id = "kehufazhanpingtai";

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
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

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (area_code.size() && IsAreaCodeLimit(area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("m_targetsip.use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// �����˺Ŷ���
	call_info->c_account = account;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_NORMAL;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "200";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = account->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// ����ǲ�����·��Դ����
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "��ҵ��·��Դ�ѵ�����:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// �����˺Ŷ���
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_NORMAL;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "240";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

// ��ʼת�ӵ��ͻ���
void C2PSipSystem::StartCallIn( const std::string& call_id
							   , CenterManager::AccountInfoPtr account
							   , const std::string& other_info
							   , std::function<void(bool)> callback
							   , bool is_unattended_transfer)
{
	// ALITTLE_PRINT_FUNC;
	// �����Ƿ����
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return;

	C2PCallInfoPtr call_info = it->second;

	// �����ת����ô���Ͳ��������˺�
	if (!callback) call_info->c_account = account;
	call_info->c_project_id = account->project_id;
	call_info->m_trnas_callback = callback;

	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		// ����Я����Ϣ
		call_info->c_other_info = other_info;

		if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_RINGING)
			HandleStatusCallback(call_info, "INVITE", "main invite");
		// ֪ͨ����
		Protocol::Sip2CenterCallIn msg;
		msg.account_id = account->account_id;
		msg.call_id = call_info->c_call_id;
		// ����Ǻ���ת�ƣ������Ǻ�������ô�����жԻ�һ��
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
			// ֪ͨ����
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

		// �����ת�ӵ�Ŀ����ϯ����ô�Ͳ�����Interface����IN_RING
		if (!call_info->m_trnas_callback && call_info->c_interface
			&& call_info->c_interface->_interface
			&& call_info->c_interface->_interface->sender)
		{
			// ֪ͨ�ӿڷ��ͺ���RING�¼�
			Protocol::Sip2InterfaceMarketStatus msg;
			msg.call_id = call_info->c_call_id;
			msg.xianlu_name = call_info->c_xianlu_name;
			msg.xianlu_subname = call_info->c_xianlu_subname;
			msg.show_number = call_info->c_from_number;
			msg.target_number = call_info->c_to_number;
			msg.other_info = call_info->c_other_info;
			msg.time = (int)time(0);
			msg.status = "IN_RING"; // ת������
			msg.reason = "";
			msg.sip_flag = AppDelegate::SIP_FLAG;
			call_info->c_interface->_interface->sender->Send(msg);
		}
	}
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_IVR)
	{
		{
			// ֪ͨ����
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
			// ֪ͨ�ӿڷ��ͺ���RING�¼�
			Protocol::Sip2InterfaceIVRStatus msg;
			msg.call_id = call_info->c_call_id;
			msg.xianlu_name = call_info->c_xianlu_name;
			msg.xianlu_subname = call_info->c_xianlu_subname;
			msg.show_number = call_info->c_from_number;
			msg.target_number = call_info->c_to_number;
			msg.other_info = call_info->c_other_info;
			msg.time = (int)time(0);
			msg.status = "IN_RING"; // ת������
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

	// �����Ƿ����
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end())	return false;

	// ֹͣ����
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

	// ֹͣ����
	call_info->StopCall(m_sip, reason);
	return true;
}

// ��������
bool C2PSipSystem::AcceptCallIn( const std::string& call_id, CenterManager::AccountInfoPtr account )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;

	// �����Ƿ����
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end()) return false;

	C2PCallInfoPtr call_info = it->second;

	// ���ܺ���
	if (call_info->c_call_type == C2PCallInfo::CALLTYPE_NORMAL)
	{
		call_info->CallInOK(m_sip);

		if (call_info->m_trnas_callback)
		{
			// ��������������ԭ���Ǹ��˺ţ���ô��ת��ʧ��
			if (call_info->c_account == account)
			{
				call_info->m_trnas_callback(false);
			}
			else
			{
				// ת�ӳɹ�
				call_info->m_trnas_callback(true);

				// ����Ϊ��ǰ���˺�
				call_info->c_account = account;

				// ����Ǻ����������Ѿ���ͨ�ˣ���ô֪ͨת��
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
	// ֪ͨת�ӳɹ�
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_MARKET)
	{
		if (call_info->m_trnas_callback)
		{
			// ��������������ԭ���Ǹ��˺ţ���ô��ת��ʧ��
			if (call_info->c_account == account)
			{
				call_info->m_trnas_callback(false);
			}
			else
			{
				// ת�ӳɹ�
				call_info->m_trnas_callback(true);

				// ����Ϊ��ǰ���˺�
				call_info->c_account = account;
			}
			call_info->m_trnas_callback = std::function<void(bool)>();
		}

		if (call_info->c_market_talk == false)
		{
			// ���Ϊtrue������������ס�������Ľ����¼�
			call_info->c_market_talk = true;
			// ���˺ŷ����ѽ�ͨ�¼�
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
			// ֪ͨ�ӿڷ��ͺ���Ӧ���¼�
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
				msg.status = "IN_ANWSER"; // ת��Ӧ��
				msg.reason = "";
				msg.sip_flag = AppDelegate::SIP_FLAG;
				call_info->c_interface->_interface->sender->Send(msg);
			}
			// ֪ͨRTP����ת��
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
	// ֪ͨת�ӳɹ�
	else if (call_info->c_call_type == C2PCallInfo::CALLTYPE_IVR)
	{
		if (call_info->c_market_talk == false)
		{
			// ���Ϊtrue������������ס�������Ľ����¼�
			call_info->c_market_talk = true;
			// ���˺ŷ����ѽ�ͨ�¼�
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
			// ֪ͨ�ӿڷ��ͺ���Ӧ���¼�
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
				msg.status = "IN_ANWSER"; // ת��Ӧ��
				msg.reason = "";
				msg.sip_flag = AppDelegate::SIP_FLAG;
				call_info->c_interface->_interface->sender->Send(msg);
			}
			// ֪ͨRTP����ת��
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

// ����Ѱ�Һ��ʵ��˺ţ�ʧ�ܵĻ���ô�͹Ҷϵ绰
void HandleQueryCallInAccountByNormalCallIn(bool result, const std::string& call_id)
{
	if (result) return;

	C2PCallInfoPtr call_info = g_C2PSipSystem.GetCallInfoByID(call_id);
	if (!call_info) return;

	call_info->NotifyNoAnswer();
	g_C2PSipSystem.StopCall(call_info, STRING_2_UTF8("HandleQueryCallInAccountByNormalCallIn:��ͨ���뱻�оܾ�����"));
}

void C2PSipSystem::HandleSip( UDPSystem::HandleInfo& info )
{
	// ALITTLE_PRINT_FUNC;
	C2PSipSystem* self = &g_C2PSipSystem;

	// ���sipЭ��
	std::vector<std::string> content_list;
	Utility::SplitString(info.memory, "\r\n", content_list);

	// ����Ƿ��ֳ���
	if (content_list.size() == 0)
	{
		self->HandleSipLogCallback("ERROR", std::string() + "content_list size is 0:" + info.memory);
		ALITTLE_ERROR("content_list size is 0");
		return;
	}

	// ��Э���л�ȡCall-ID
	std::string call_id = C2PCallInfo::GetKeyValueFromUDP(content_list, "CALL-ID");
	if (call_id == "") return;

	ALITTLE_INFO("SIP Recevie ------------------->:" << content_list[0] << ", CALLID:" << call_id);

	// ��ӡ�����ݿ�
	self->HandleSipLogCallback(call_id, std::string() + "RECEIVE <==" + info.memory);

	// �ӵ�һ�в�ֳ�����
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

	// �Ȳ���ע��call_id
	RegisterSipInfoMap::iterator register_it = self->m_callid_map_registerinfo.find(call_id);
	if (register_it != self->m_callid_map_registerinfo.end())
	{
		if (register_it->second.register_status == SipRegister::SIPREGISTER_1)
		{
			if (status == "200")
			{
				// ���
				RegisterNumberMap::iterator sip_account_it = self->m_number_map_info.find(register_it->second.register_show_account);
				if (sip_account_it != self->m_number_map_info.end())
				{
					sip_account_it->second->register_call_id = "";

					// ������ע��ӳ�����ɾ������ӵ���ע���б��β��
					self->m_registering_map.erase(sip_account_it->second->show_account);
					self->m_number_list.push_back(sip_account_it->second);
				}
				// �Ƴ�
				self->m_callid_map_registerinfo.erase(register_it);
			}
			// ִ�ж���ע��
			else
			{
				self->DoSipRegister2(register_it->second, content_list);
			}
		}
		else if (register_it->second.register_status == SipRegister::SIPREGISTER_2)
		{
			// ���
			RegisterNumberMap::iterator sip_account_it = self->m_number_map_info.find(register_it->second.register_show_account);
			if (sip_account_it != self->m_number_map_info.end())
			{
				sip_account_it->second->register_call_id = "";
				sip_account_it->second->register_auth = register_it->second.register_auth;

				// ������ע��ӳ�����ɾ������ӵ���ע���б��β��
				self->m_registering_map.erase(sip_account_it->second->show_account);
				self->m_number_list.push_back(sip_account_it->second);
			}
			// �Ƴ�
			self->m_callid_map_registerinfo.erase(register_it);
		}
		return;
	}

	// ����������룬���ҵ�ǰcall_id�����ڣ���ô�����µĺ���
	if (method == "INVITE")
	{
		C2PCallInfoMap::iterator invite_it = self->m_call_map.find(call_id);
		if (invite_it == self->m_call_map.end())
		{
			// �ҵ���ʹ������1����֪ͨ����Center
			++ (g_C2PSipSystem.m_targetsip.use_call);
			ALITTLE_INFO("g_C2PSipSystem.m_targetsip.use_call:" << g_C2PSipSystem.m_targetsip.use_call);
			g_CenterManager.NotifyAllCenterResourceValue(g_C2PSipSystem.m_targetsip, 1);
			g_InterfaceManager.NotifyAllInterfaceResourceValue(g_C2PSipSystem.m_targetsip, 1);
			// ����CallInfo����
			C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
			call_info->c_call_id = call_id;
			self->m_call_map[call_info->c_call_id] = call_info;
			// ���������Ϣ
			if (call_info->HandleSipInfoCreateCallInInvite(self->m_sip, method, "", response_list, content_list
										, self->m_local_sip_ip, self->m_local_sip_port
										, g_C2PSipSystem.m_targetsip.xianlu_name
										, g_C2PSipSystem.m_targetsip.xianlu_subname
										, g_C2PSipSystem.m_targetsip.callin_pre, info.end_point) == false)
			{
				self->StopCall(call_id, STRING_2_UTF8("HandleSipInfoCreateCallInInviteʧ��"));
			}
			else
			{
				int ims_callin_type = ImsManager::CALLINTYPE_NORMAL;
				std::string ims_yuyin_id = AppDelegate::DEFAULT_YUYIN;
				std::string ims_project_id;
				// ��ѯ����������ڵĹ���
				ImsManager::CallInMap::iterator ims_it = g_ImsManager.m_callin_map.find(call_info->c_to_number);
				if (ims_it != g_ImsManager.m_callin_map.end())
				{
					ims_callin_type = ims_it->second.callin_type;
					ims_yuyin_id = ims_it->second.yuyin_id;
					ims_project_id = ims_it->second.project_id;
				}

				// ��RTP���Ͳ�������
				if (call_info->c_rtp && ims_yuyin_id.size())
				{
					Protocol::Sip2RtpPlayYuYin yuyin_msg;
					yuyin_msg.first_port = call_info->p_rtp_port;
					yuyin_msg.audio_number = call_info->c_audio_number;
					yuyin_msg.yuyin_id = ims_yuyin_id;
					yuyin_msg.yuyin_repeat = 0;	// ���޲���
					call_info->c_rtp->Send(yuyin_msg, 0, 0);
				}

				if (ims_callin_type == ImsManager::CALLINTYPE_NORMAL)
				{
					// ���ѯ���˺�ʧ�ܣ���ô��ֱ�ӹҶ�
					std::function<void(bool)> func = std::bind(HandleQueryCallInAccountByNormalCallIn, std::placeholders::_1, call_id);
					if (g_CenterManager.QueryCallInAccount(call_id, ""
														, g_C2PSipSystem.m_targetsip.xianlu_name
														, call_info->c_to_number, func, std::function<void(bool)>()
														, false) == false)
					{
						call_info->NotifyNoAnswer();
						self->StopCall(call_id, STRING_2_UTF8("QueryCallInAccountû���ҵ����Ժ������ϯ"));
					}
				}
				else if (ims_callin_type == ImsManager::CALLINTYPE_IVR)
				{
					// ������ĿID�ҵ���Ӧ��Interface
					InterfaceManager::InterfaceInfoPtr ims_interface = g_InterfaceManager.GetModuleById(ims_project_id);
					if (!ims_interface)
					{
						ALITTLE_ERROR("can't find interface by project_id:" << ims_project_id << ", ims:" << call_info->c_from_number);
						self->StopCall(call_id, STRING_2_UTF8("CALLINTYPE_IVR ��������"));
					}
					else
					{
						InterfaceManager::InterfaceInfoCallPtr _interface = InterfaceManager::InterfaceInfoCallPtr(new InterfaceManager::InterfaceInfoCall);
						_interface->call_id = call_info->c_call_id;
						_interface->_interface = ims_interface;

						call_info->c_interface = _interface;
						call_info->c_call_type = C2PCallInfo::CALLTYPE_IVR;
						call_info->c_bill_type = "1040";		// �˵�����
						// ֪ͨ�ӿڷ�����
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
					self->StopCall(call_id, STRING_2_UTF8("�������ʹ���"));
				}
			}
		}
		else
		{
			bool remove_tmp = false;
			invite_it->second->HandleCallSipReInvite(self->m_sip, method, "", response_list, content_list, remove_tmp);
		}
	}
	// ��������Э��
	else
	{
		// ���CallID�Ƿ����
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
			// �ҵ���ʹ������1����֪ͨ����Center
			-- (g_C2PSipSystem.m_targetsip.use_call);
			ALITTLE_INFO("g_C2PSipSystem.m_targetsip.use_call:" << g_C2PSipSystem.m_targetsip.use_call);
			g_CenterManager.NotifyAllCenterResourceValue(g_C2PSipSystem.m_targetsip, -1);
			g_InterfaceManager.NotifyAllInterfaceResourceValue(g_C2PSipSystem.m_targetsip, -1);

			self->HandleSipLogCallback(call_id, "RELEASE");
			ALITTLE_INFO("===========> RELEASE CALL-ID:" << it->second->c_call_id);
			// ����Ǻ��룬Ҫ�����ں����������յ�
			if (it->second->c_out_or_in == false)
				g_CenterManager.ClearCallInInfo(call_id);
			// ���������ͨ���У���ô��Ҫ����ӿڹ���������Ϣ
			if (it->second->c_call_type != C2PCallInfo::CALLTYPE_NORMAL && it->second->c_call_type != C2PCallInfo::CALLTYPE_TEST)
				g_InterfaceManager.ClearInterfaceInfo(it->second->c_call_id);
			// �ͷ�Rtp
			g_RtpManager.ReleaseRtp(call_id);
			// �����˵������͵����ݿ�
			it->second->SaveBill();
			if (it->second->c_out_or_in)
				g_C2PSipSystem.RemoveOnlyOneCall(it->second->c_from_number);
			else
				g_C2PSipSystem.RemoveOnlyOneCall(it->second->c_to_number);
			// ����ͷ�֮ǰ������һ����������������
			it->second->NotifyReleased();
			// ɾ��������Ϣ
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// ����ǲ�����·��Դ����
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "��ҵ��·��Դ�ѵ�����:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	// ��¼��ʼʱ��
	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// �����˺Ŷ���
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1080";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// ����ǲ�����·��Դ����
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "��ҵ��·��Դ�ѵ�����:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// �����˺Ŷ���
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TRANS_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1081";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// ����ǲ�����·��Դ����
	int max_count = -1;
	if (g_ImsManager.CheckLimitEnterprise(enterprise_id, max_count))
	{
		repeat = true;
		reason = STRING_2_UTF8((reason + "��ҵ��·��Դ�ѵ�����:" + xianlu_name + ":" + xianlu_subname + ":" + Utility::FormateToString(max_count)).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);
	g_ImsManager.AddLimitEnterprise(enterprise_id);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	call_info->m_enterprise_id = enterprise_id;

	// �����˺Ŷ���
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_UNATTENDED_TRANS_MARKET;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "240";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
	call_info->CallOutInvite(m_sip, start_time);
	return call_info;
}

void HandleQueryCallInAccountByMarketCallIn(bool result, const std::string& call_id)
{
	if (result) return;

	C2PCallInfoPtr call_info = g_C2PSipSystem.GetCallInfoByID(call_id);
	if (!call_info) return;
	
	g_C2PSipSystem.StopCall(call_info, STRING_2_UTF8("HandleQueryCallInAccountByMarketCallIn:ת�ӵ���ϯ�ܾ�����"));
}

void C2PSipSystem::QueryMarketAccount( const std::string& call_id, const std::string& account_id )
{
	// ALITTLE_PRINT_FUNC;

	// ���Ҷ�Ӧ�ĺ�����Ϣ
	C2PCallInfoMap::iterator call_it = m_call_map.find(call_id);
	if (call_it == m_call_map.end()) return;

	C2PCallInfoPtr call_info = call_it->second;

	// �����е����ͣ������ǲ���Ӫ���ӿ�
	if (call_info->c_call_type != C2PCallInfo::CALLTYPE_MARKET) return;

	// �����е�ǰ�Ĳ��裬�����ǲ��ǻ��Ǵ���ͨ����
	if (call_info->c_sip_step != C2PCallInfo::SIPSTEP_TALK) return;

	// ����Ѿ�ת�ӹ��ˣ���ô��ֱ������
	if (call_info->c_market_trans) return;
	call_info->c_market_trans = true;

	// �����˺ţ�����˺Ų���ʧ�ܣ�ֱ��ֹͣ����
	std::function<void(bool)> func = std::bind(HandleQueryCallInAccountByMarketCallIn, std::placeholders::_1, call_info->c_call_id);
	bool result = g_CenterManager.QueryCallInAccount(call_info->c_call_id, account_id, "", "", func, std::function<void(bool)>(), false);
	if (result == false) call_info->StopCall(m_sip, STRING_2_UTF8("QueryMarketAccount:û���ҵ�����ת�ӵ���ϯ"));
}

bool C2PSipSystem::AcceptIVRCallIn( const std::string& call_id, const std::string& other_info )
{
	// ALITTLE_PRINT_FUNC;
	if (!m_sip) return false;

	// �����Ƿ����
	C2PCallInfoMap::iterator it = m_call_map.find(call_id);
	if (it == m_call_map.end()) return false;

	// ����Я����Ϣ
	it->second->c_other_info = other_info;
	// ��������
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

	// ���Ҷ�Ӧ�ĺ�����Ϣ
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

	// �����е����ͣ������ǲ���Ӫ���ӿ�
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

	// ����Я������
	if (rewrite_other_info) call_info->c_other_info = other_info;

	// �����е�ǰ�Ĳ��裬�����ǲ��ǻ��Ǵ���ͨ����
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

	// �����˺ţ�����˺Ų���ʧ�ܣ�ֱ��ֹͣ����
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
		reason = STRING_2_UTF8("SIP��·�ѹر�:") + m_targetsip.xianlu_name + "," + m_targetsip.xianlu_subname;
		return C2PCallInfoPtr();
	}

	// ���Ҷ�Ӧ����·��Ϣ
	if (m_targetsip.xianlu_name != xianlu_name || m_targetsip.xianlu_subname != xianlu_subname)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "SIP��·������:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	// �����·��Դ�Ƿ��㹻
	if (m_targetsip.use_call >= m_targetsip.max_call)
	{
		repeat = true;
		reason = STRING_2_UTF8((std::string() + "SIP��·��Դ����:" + xianlu_name + ":" + xianlu_subname).c_str());
		return C2PCallInfoPtr();
	}

	if (AppDelegate::IsInForbiddenTime(time(0)))
	{
		reason = STRING_2_UTF8((std::string() + "������ʱ���ڲ��ܺ���:" + AppDelegate::FORBIDDEN_TIME_LIST).c_str());
		return C2PCallInfoPtr();
	}

	PhoneHCode::HCodeCorp hcode_corp;
	bool is_fixed = false;
	PhoneHCode::FixedHcodePtr hcode = AppDelegate::phone_hcode.GetHCode(to_number, hcode_corp, is_fixed);
	if (!hcode)
	{
		repeat = false;
		reason = STRING_2_UTF8((std::string() + "��Ч����:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// �������Ƿ񳬳�����
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
		reason = STRING_2_UTF8((std::string() + "��Ч������:" + to_number).c_str());
		return C2PCallInfoPtr();
	}

	// ���������ж�
	if (IsAreaCodeLimit(hcode->area_code, hcode_corp, is_fixed, reason))
	{
		ALITTLE_INFO("IsAreaCodeLimit:" << reason);
		repeat = false;
		return C2PCallInfoPtr();
	}

	int start_time = (int)time(0);

	// ����Rtp
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
		reason = STRING_2_UTF8("RTP��Դ����!");
		return C2PCallInfoPtr();
	}

	// ��ʹ�õ��1����֪ͨ����Center
	++ (m_targetsip.use_call);
	ALITTLE_INFO("sip_it->second->use_call:" << m_targetsip.use_call);
	g_CenterManager.NotifyAllCenterResourceValue(m_targetsip, 1);
	g_InterfaceManager.NotifyAllInterfaceResourceValue(m_targetsip, 1);

	// ����C2PCallInfo����
	C2PCallInfoPtr call_info = C2PCallInfoPtr(new C2PCallInfo);
	m_call_map[call_id] = call_info;

	// �����˺Ŷ���
	call_info->c_interface = _interface;
	call_info->c_call_type = C2PCallInfo::CALLTYPE_TRANS_IVR;
	call_info->c_other_info = other_info;
	call_info->c_bill_type = "1041";
	call_info->c_xianlu_name = xianlu_name;
	call_info->c_xianlu_subname = xianlu_subname;
	call_info->c_project_id = _interface->_interface->project_id;

	// ����Rtp�Ļ�����Ϣ
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

	// ����Sip�Ļ�����Ϣ
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

	// ִ�к���
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
		// �������
		C2PCallInfoWeakMap::iterator it, end = m_call_weak_map.end();
		for (it = m_call_weak_map.begin(); it != end;)
		{
			// ����Ѿ������ˣ�ֱ��ɾ����
			C2PCallInfoPtr call_info = it->second.lock();
			if (!call_info)
			{
				it = m_call_weak_map.erase(it);
				continue;
			}

			// �������ͨ������ô��ֱ���Ƴ�
			if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK)
			{
				it = m_call_weak_map.erase(it);
				continue;
			}

			// ����INVITE
			if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_INVITE)
			{
				// �ط�5��
				if (call_info->c_invite_count < 5)
				{
					// ���ֱ�ӳ������룬���·���
					if (cur_time - call_info->c_sip_send_time > 2)
						call_info->CallOutInviteImpl(m_sip, cur_time);
				}
				// ����5�Σ���ô��ֱ���Ƴ�
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// ������ܵ�TRYING�¼�
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_TRYING)
			{
				// ������״̬����10���ӣ���ô��ֱ���Ƴ�
				if (cur_time - call_info->c_sip_receive_time > 60 * 10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// ����RINGRING�¼�
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_RINGING)
			{
				// �������ʱ�䳬��10���ӣ���ô��ֱ���Ƴ�
				if (cur_time - call_info->c_sip_receive_time > 60 * 10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// �����������͵�CANCEL�¼�
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_OUT_CANCELING)
			{
				if (call_info->c_cancel_count < 15)
				{
					// ��������������ظ����ͣ�֪���Է���Ӧ��ֻҪ��Ӧ����ô���̾Ϳ���˳������
					if (cur_time - call_info->c_sip_send_time >= 1)
						call_info->CallOutCancel(m_sip);
				}
				// ����5�Σ���ô��ֱ���Ƴ�
				else
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// �������ܽ�
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_FORBIDDEN)
			{
				if (call_info->c_forbidden_count < 5)
				{
					// �������ܽӣ��ظ����ͣ�ֻҪ��Ӧ����ô���̾Ϳ���˳������
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
			// �����������
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_RINGING)
			{
				// ���������������ǳ��ã�����3���ӣ���ôֱ���ͷ�
				if (cur_time - call_info->c_sip_send_time > 60*10)
				{
					call_info->ReleaseCall();
					it = m_call_weak_map.erase(it);
					continue;
				}
			}
			// ����������
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_IN_OK)
			{
				if (call_info->c_ok_count < 50)
				{
					// ��������������ʱ��ȽϾã����ظ�����
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
			// ����Ҷ��¼�
			else if (call_info->c_sip_step == C2PCallInfo::SIPSTEP_TALK_BYING)
			{
				if (call_info->c_bye_count < 50)
				{
					// ����Ҷ��¼������¼��ȽϾã���ֱ�ӷ���
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

	// ����ע��
	{
		RegisterNumberList::iterator src_it, src_end = m_number_list.end();
		for (src_it = m_number_list.begin(); src_it != src_end;)
		{
			(*src_it)->last_resgiter_time = cur_time;
			(*src_it)->register_call_id = DoSipRegister1((*src_it)->show_account, (*src_it)->account, (*src_it)->password);

			m_registering_map[(*src_it)->show_account] = *src_it;

			// ��ԭ�������Ƴ�
			src_it = m_number_list.erase(src_it);

			-- max_register;
			if (max_register <= 0) break;
		}
	}

	// �������ûע��ɹ��ģ�����һ���ӣ�����ע��
	{
		RegisterNumberMap::iterator src_it, src_end = m_registering_map.end();
		for (src_it = m_registering_map.begin(); src_it != src_end; ++src_it)
		{
			if (cur_time - src_it->second->last_resgiter_time > 60)
			{
				// ����ϴ�ע��ʱ�䳬��ָ���������ô������ע��
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
		// ����Ѿ������ˣ�ֱ��ɾ����
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

	// ��ȡ���еĺ���Ƶ��
	m_targetsip.call_time_unit = config.GetConfigIntByDefault("call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.call_count_unit = config.GetConfigIntByDefault("call_count_unit", 0);		// ��λʱ���������

	m_targetsip.dx_call_time_unit = config.GetConfigIntByDefault("dx_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.dx_call_count_unit = config.GetConfigIntByDefault("dx_call_count_unit", 0);		// ��λʱ���������

	m_targetsip.lt_call_time_unit = config.GetConfigIntByDefault("lt_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.lt_call_count_unit = config.GetConfigIntByDefault("lt_call_count_unit", 0);		// ��λʱ���������

	m_targetsip.yd_call_time_unit = config.GetConfigIntByDefault("yd_call_time_unit", 0);		// �����ʱ�䵥λ����
	m_targetsip.yd_call_count_unit = config.GetConfigIntByDefault("yd_call_count_unit", 0);		// ��λʱ���������

	std::string old_register_info = GET_CONFIG_STRING("register_info", "");
	std::string register_info = config.GetConfigStringByDefault("register_info", "");		// SIP���˺�����
	
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
			ALITTLE_ERROR("splite by , error:" << register_info_list[i] << STRING_2_UTF8(", usage: ��ʾ��,��Ȩ�û���,��Ȩ����"));
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


// �������ǳ��õĺ��У��������̲��
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
		// ��ΪVIA�е�branchֵ���ܷ����仯������Ҫ���»�ȡһ��
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
		// ��ΪVIA�е�branchֵ���ܷ����仯������Ҫ���»�ȡһ��
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

	// �����ݱ��浽���ݿ�
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
	Utility::SplitString(list, "|", split_list);	// �̻����ֻ����ŷ�Χ(��������ʾȫ����Χ����������ʾָ����Χ)
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

	// �����ݱ��浽���ݿ�
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
	// ��ȡ��ǰʱ��
	int cur_time = (int)time(0);

	int min_count = -1;
	NumberInfo* target_info = 0;
	int number_index = 0;

	int random_offset = rand() % number.size();

	// �������к���
	for (unsigned int i = 0; i < number.size(); ++i)
	{
		unsigned int index = (i + random_offset) % number.size();
		std::string cur_number = number[index];

		NumberInfo* info_tmp = 0;
		// ���û�в��ҵ�����ô�ͳ�ʼ��
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
			// ���������λʱ�䣬��ô�ͳ�ʼ��
			if (m_targetsip.call_time_unit > 0 && cur_time - info_tmp->start_time > m_targetsip.call_time_unit)
			{
				info_tmp->start_time = cur_time;
				info_tmp->call_count = 0;
			}

			// ���������λʱ�䣬��ô�ͳ�ʼ��
			if (m_targetsip.dx_call_time_unit > 0 && cur_time - info_tmp->dx_start_time > m_targetsip.dx_call_time_unit)
			{
				info_tmp->dx_start_time = cur_time;
				info_tmp->dx_call_count = 0;
			}

			// ���������λʱ�䣬��ô�ͳ�ʼ��
			if (m_targetsip.lt_call_time_unit > 0 && cur_time - info_tmp->lt_start_time > m_targetsip.lt_call_time_unit)
			{
				info_tmp->lt_start_time = cur_time;
				info_tmp->lt_call_count = 0;
			}

			// ���������λʱ�䣬��ô�ͳ�ʼ��
			if (m_targetsip.yd_call_time_unit > 0 && cur_time - info_tmp->yd_start_time > m_targetsip.yd_call_time_unit)
			{
				info_tmp->yd_start_time = cur_time;
				info_tmp->yd_call_count = 0;
			}
		}

		// ������趨��Χ�����ҳ�����Χ��ô��ֱ�ӷ���
		if (m_targetsip.call_count_unit > 0 && info_tmp->call_count >= m_targetsip.call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("�ܺ���Ƶ��̫��;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_DX && m_targetsip.dx_call_count_unit > 0 && info_tmp->dx_call_count >= m_targetsip.dx_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("���е���Ƶ��̫��;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_LT && m_targetsip.lt_call_count_unit > 0 && info_tmp->lt_call_count >= m_targetsip.lt_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("������ͨƵ��̫��;");
			continue;
		}

		if (corp == PhoneHCode::HCodeCorp::HCODECORP_YD && m_targetsip.yd_call_count_unit > 0 && info_tmp->yd_call_count >= m_targetsip.yd_call_count_unit)
		{
			reason += cur_number + STRING_2_UTF8("�����ƶ�Ƶ��̫��;");
			continue;
		}

		// ������趨һ������ֻ��ͬʱһ�����У���ô���һ��
		int max_call = m_targetsip.only_one_call;
		C2POnlyOneCallMap::iterator only_one_call_it = m_only_one_call_map.find(cur_number);
		if (only_one_call_it != m_only_one_call_map.end() && only_one_call_it->second.max_call > 0)
			max_call = only_one_call_it->second.max_call;

		if (only_one_call_it != m_only_one_call_map.end() && max_call > 0 && only_one_call_it->second.cur_count >= max_call)
		{
			reason += cur_number + STRING_2_UTF8("ռ����;") + Utility::FormateToString(only_one_call_it->second.cur_count) + ";" + Utility::FormateToString(max_call);
			continue;
		}

		// ������������û����������
		C2PAreaCallMap::iterator area_call_it = m_area_call_map.find(cur_number);
		if (area_code.size() && area_call_it != m_area_call_map.end())
		{
			if (area_call_it->second.range_or_ab > 0)
			{
				if (area_call_it->second.range_map.size() && area_call_it->second.range_map.find(area_code) == area_call_it->second.range_map.end())
				{
					reason += cur_number + STRING_2_UTF8("���ƺ���������;") + area_code;
					continue;
				}
			}
			else
			{
				if (area_call_it->second.range_map.size() == 0 || area_call_it->second.range_map.find(area_code) != area_call_it->second.range_map.end())
				{
					reason += cur_number + STRING_2_UTF8("���ƺ���������;") + area_code;
					continue;
				}
			}
		}

		// ����Ƿ񳬳����Ѷ��
		if (g_ImsManager.CheckConsumeLimit(cur_number))
		{
			reason += cur_number + STRING_2_UTF8("�������Ѷ��;");
			continue;
		}
		
		// �ҳ��������ٵ��Ǹ�
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
	// �ж���Ӫ���Ƿ�����
	if (is_fixed && m_targetsip.fixed_weight <= 0.0)
	{
		reason = STRING_2_UTF8("����·���ƹ̻��������");
		return true;
	}
	
	if (corp == PhoneHCode::HCODECORP_DX && m_targetsip.dianxin_weight <= 0.0)
	{
		reason = STRING_2_UTF8("����·���Ƶ����ֻ��������");
		return true;
	}

	if (corp == PhoneHCode::HCODECORP_LT && m_targetsip.liantong_weight <= 0.0)
	{
		reason = STRING_2_UTF8("����·������ͨ�ֻ��������");
		return true;
	}

	if (corp == PhoneHCode::HCODECORP_YD && m_targetsip.yidong_weight <= 0.0)
	{
		reason = STRING_2_UTF8("����·�����ƶ��ֻ��������");
		return true;
	}

	// �ж���ѡ
	if (m_targetsip.fixed_range_or_ab > 0)
	{
		// fixed_range_map��СΪ0��ʾȫ��Χ
		// ������з�Χ�ģ����Ҳ��ٷ�Χ֮�ڣ���ֱ�ӷ���
		if (m_targetsip.fixed_map.size()
			&& m_targetsip.fixed_map.find(area_code) == m_targetsip.fixed_map.end())
		{
			reason = STRING_2_UTF8("����·���ƺ����õ����ĺ���:") + area_code;
			return true;
		}
	}
	// �жϷ�ѡ
	else
	{
		// fixed_range_map��СΪ0��ʾȫ��Χ
		if (m_targetsip.fixed_map.size() == 0
			|| m_targetsip.fixed_map.find(area_code) != m_targetsip.fixed_map.end())
		{
			reason = STRING_2_UTF8("����·���ƺ����õ����ĺ���:") + area_code;
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

	// �����ʱ����֮ǰ��һ������ô
	if (m_targetsip.check_register_interval != old_check_register_interval)
	{
		ALITTLE_INFO("recreate check register loopobject");
		if (m_loop_check_register)
			AppDelegate::loop_system->RemoveObject(m_loop_check_register);

		// ��ʱ������ȥ��REGISTER�Ƿ��л�Ӧ
		std::function<bool(int)> func4 = std::bind(&C2PSipSystem::CheckRegister, this, std::placeholders::_1);
		int delay = 1;
		if (s_first_register) delay = 2000;
		m_loop_check_register = AppDelegate::loop_system->AddObject(ALittle::LoopObject(func4, 1000*m_targetsip.check_register_interval, delay));
	}
}

} // ALittle