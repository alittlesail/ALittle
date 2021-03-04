
#ifndef _ALITTLE_SIPMANAGER_H_
#define _ALITTLE_SIPMANAGER_H_

#include <asio.hpp>
#include <memory>
#include <map>
#include <string>

class SipSchedule;

class C2PCallInfo;
typedef std::shared_ptr<C2PCallInfo> C2PCallInfoPtr;
typedef std::weak_ptr<C2PCallInfo> C2PCallInfoWeakPtr;

class SipManager
{
public:
	SipManager(SipSchedule* schedule) : m_schedule(schedule) {}

	//=========================================================================================
public:
	void Setup();
	void Shutdown();

	static bool Test(int frame);
	void InviteNotify(const std::string& ims);
	static void InviteNotifyResult(bool result, const std::string& body, const std::string& head);

//target SIP Manager/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	C2PSipInfo m_targetsip;

public:
	enum SipRegister
	{
		SIPREGISTER_UNDO,		// ��û��ע��
		SIPREGISTER_1,			// ��ʼ����ע����Ϣ
		SIPREGISTER_2,			// ���͵ڶ���ע����Ϣ
		SIPREGISTER_SUCCEED,	// ע��ɹ�
		SIPREGISTER_FAILED,		// ע��ʧ��
	};

	// ���ڱ���Ҫע��ĺ������Ϣ
	struct RegisterNumberInfo
	{
		RegisterNumberInfo() { }
		~RegisterNumberInfo() { }

		std::string show_account;			// �ʺ���
		std::string account;			// �ʺ���
		std::string password;			// ����
		int last_resgiter_time;			// �ϴ�ע���ʱ��
		std::string register_call_id;	// ע���call_id
		std::string register_auth;		// ע��֤��
	};
	typedef std::shared_ptr<RegisterNumberInfo> RegisterNumberInfoPtr;
	typedef std::map<std::string, RegisterNumberInfoPtr> RegisterNumberMap;
	RegisterNumberMap m_number_map_info;

	// ��Ҫע����б�
	typedef std::list<RegisterNumberInfoPtr> RegisterNumberList;
	RegisterNumberList m_number_list;

	// ����ע����б�
	RegisterNumberMap m_registering_map;

public:
	const std::string& GetAuthPassword(const std::string& show_account);
	const std::string& GetAuthAccount(const std::string& show_account);

private:
	struct RegisterSipInfo
	{
		SipRegister register_status;	// ע��״̬

		std::string register_show_account;	// ��ʾ��
		std::string register_account;	// ע���˺�
		std::string register_password;	// ע������
		std::string register_call_id;	// ��Ӧ��call_id
		std::string register_from_tag;	// ��Ӧ��from_tag
		std::string register_auth;		// ��Ӧ����Ȩ
	};
	typedef std::map<std::string, RegisterSipInfo> RegisterSipInfoMap;
	RegisterSipInfoMap m_callid_map_registerinfo;

public:
	std::string DoSipRegister1(const std::string& show_account, const std::string& account, const std::string& password);
	bool GetNonceRealm(const std::string& head, const std::vector<std::string>& content_list
		, std::string& nonce, std::string& realm);
	bool GetNextNonce( const std::string& head, const std::vector<std::string>& content_list , std::string& nonce );

	std::string GenAuth(const std::string& nonce, const std::string& realm
		, const std::string& account, const std::string& password
		, const std::string& method, const std::string& uri);
	bool CalcAuth(const std::string& head, const std::vector<std::string>& content_list
		, const std::string& account, const std::string& password
		, const std::string& method, const std::string& uri
		, std::string& nonce, std::string& realm, std::string& auth);
	bool DoSipRegister2(RegisterSipInfo& info, const std::vector<std::string>& content_list);

public:
	bool NotifyDatabaseAllResource(int frame_time);
	void NotifySenderAllResource(ModuleClientPtr sender);
	void NotifySenderAllResource(ModuleReceiverPtr sender);

public:
	void HandleSipLogCallback( const std::string& call_id, const std::string& content );
	void HandleStatusCallback( C2PCallInfoPtr call_info, const std::string& method, const std::string& reason);
	void HandleSipDtmfCallback( C2PCallInfoPtr call_info, const std::string& content);

public:
	bool UpdateLogic(int frame_time);
	bool CheckCallLast(int frame_time);
	bool CheckRegister(int frame_time);
	bool UpdateSession(int frame_time);
	bool UpdateConfigFile(int frame_time);

public:
	void CalcCheckRegister();
	LoopObject* m_loop_check_register;
	
//SIP////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	typedef std::map<std::string, C2PCallInfoPtr> C2PCallInfoMap;
	// ���ڱ��浱ǰ���еĺ���
	C2PCallInfoMap m_call_map;
	typedef std::map<std::string, C2PCallInfoWeakPtr> C2PCallInfoWeakMap;
	C2PCallInfoWeakMap m_call_weak_map;		// ���ڶ�ʱ����SIP����

	C2PCallInfoWeakMap m_session_expires_map;
	
	struct NumberInfo
	{
		int start_time;		// ��ʼʱ��
		int call_count;		// ����

		int dx_start_time;		// ��ʼʱ��
		int dx_call_count;

		int lt_start_time;		// ��ʼʱ��
		int lt_call_count;

		int yd_start_time;		// ��ʼʱ��
		int yd_call_count;
	};
	typedef std::hash_map<std::string, NumberInfo> ShowNumberLimitMap;
	ShowNumberLimitMap m_limit_map;

	// ���ڱ��
	struct OnlyOneCallInfo
	{
		OnlyOneCallInfo() : cur_count(0), max_call(0) {}
		int cur_count;
		int max_call;
	};
	typedef std::map<std::string, OnlyOneCallInfo> C2POnlyOneCallMap;
	C2POnlyOneCallMap m_only_one_call_map;
	void RemoveOnlyOneCall(const std::string& number);
	void AddOnlyOneCall(const std::string& number);
	void SetOnlyOneMaxCall(const std::string& number, int max_call, bool update_sqlite);

	// ���ڱ��
	struct AreaCallInfo
	{
		AreaCallInfo() : range_or_ab(0) {}
		std::map<std::string, bool> range_map;
		int range_or_ab;
	};
	typedef std::map<std::string, AreaCallInfo> C2PAreaCallMap;
	C2PAreaCallMap m_area_call_map;
	void SetAreaLimit(const std::string& number, const std::string& list, int range_or_ab, bool update_sqlite);

	bool IsShowNumberLimit(const std::vector<std::string>& number, const std::string& area_code, PhoneHCode::HCodeCorp corp, std::string& out_from_number, std::string& reason);
	bool IsAreaCodeLimit(const std::string& area_code, PhoneHCode::HCodeCorp corp, bool is_fixed, std::string& reason);

public:
	C2PCallInfoPtr StartCallOutTest(int test_invoke_id
								, const std::string& call_id
								, const std::string& from_number, const std::string& to_number
								, std::string& reason
								, bool& repeat);
	
public:
	C2PCallInfoPtr StartCallOutNormal(CenterManager::AccountInfoPtr account
								, const std::string& call_id
								, const std::vector<std::string>& from_number, const std::string& to_number
								, const std::string& xianlu_name, const std::string& xianlu_subname
								, const std::string& other_info
								, int corp
								, std::string& out_from_number
								, std::string& reason
								, bool& repeat);

	void StartCallIn(const std::string& call_id
		, CenterManager::AccountInfoPtr account
		, const std::string& other_info
		, std::function<void(bool)> callback
		, bool is_unattended_transfer);
	bool AcceptCallIn(const std::string& call_id, CenterManager::AccountInfoPtr account);
	bool StopCall(const std::string& call_id, const std::string& reason);
	bool StopCall(C2PCallInfoPtr call_info, const std::string& reason);
	C2PCallInfoPtr GetCallInfoByID(const std::string& call_id);
	void SendDtmf(const std::string& call_id, const std::string& content);


	C2PCallInfoPtr StartUnattendedTransferNormal(InterfaceManager::InterfaceInfoCallPtr _interface
												, const std::string& enterprise_id
												, const std::string& call_id
												, const std::vector<std::string>& from_number, const std::string& to_number
												, const std::string& xianlu_name, const std::string& xianlu_subname
												, const std::string& other_info
												, int corp
												, bool need_dtmf
												, std::string& out_from_number
												, std::string& reason
												, bool& repeat);

public:
	C2PCallInfoPtr StartCallOutMarket(InterfaceManager::InterfaceInfoCallPtr _interface
								, const std::string& enterprise_id
								, const std::string& call_id
								, const std::vector<std::string>& from_number, const std::string& to_number
								, const std::string& xianlu_name, const std::string& xianlu_subname
								, const std::string& other_info
								, int corp
								, bool need_dtmf
								, bool need_record
								, std::string& out_from_number
								, std::string& reason
								, bool& repeat);

	void QueryMarketAccount(const std::string& call_id, const std::string& account_id);

	C2PCallInfoPtr StartTransferMarket(InterfaceManager::InterfaceInfoCallPtr _interface
								, const std::string& enterprise_id
								, const std::string& call_id
								, const std::vector<std::string>& from_number, const std::string& to_number
								, const std::string& xianlu_name, const std::string& xianlu_subname
								, const std::string& other_info
								, int corp
								, bool need_dtmf
								, std::string& out_from_number
								, std::string& reason
								, bool& repeat);

	C2PCallInfoPtr StartUnattendedTransferMarket(InterfaceManager::InterfaceInfoCallPtr _interface
								, const std::string& enterprise_id
								, const std::string& call_id
								, const std::vector<std::string>& from_number, const std::string& to_number
								, const std::string& xianlu_name, const std::string& xianlu_subname
								, const std::string& other_info
								, int corp
								, bool need_dtmf
								, std::string& out_from_number
								, std::string& reason
								, bool& repeat);

public:
	bool AcceptIVRCallIn(const std::string& call_id, const std::string& other_info);
	void QueryIVRAccount(ModuleClientPtr sender, const std::string& call_id, const std::string& account_id
		, bool rewrite_other_info, const std::string& other_info);
	C2PCallInfoPtr StartTransferIVR(InterfaceManager::InterfaceInfoCallPtr _interface
								, const std::string& call_id
								, const std::vector<std::string>& from_number, const std::string& to_number
								, const std::string& xianlu_name, const std::string& xianlu_subname
								, const std::string& other_info
								, int corp
								, bool need_dtmf
								, std::string& out_from_number
								, std::string& reason
								, bool& repeat);

private:
	static void HandleSip(UDPSystem::HandleInfo& info);
	static void HandleErrorSip(asio::ip::udp::endpoint ep, UDPSystemPtr sip
		, const std::string& method
		, const std::string& status
		, const std::vector<std::string>& response_list
		, const std::vector<std::string>& content_list);

private:
	std::string m_local_sip_ip;
	std::string m_local_sip_port;
	asio::ip::udp::endpoint m_local_sip;

private:
	std::string m_invite_notify_url;

private:
	static bool s_first_register;

public:
	UDPSystemPtr m_sip;

private:
	SipSchedule* m_schedule = nullptr;
};

#endif