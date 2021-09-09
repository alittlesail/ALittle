
#include <asio.hpp>

#include "ServerSchedule.h"
#include "ServerSystem.h"

#ifdef HAS_MYSQL
#include "Carp/carp_mysql.hpp"
#endif // HAS_MYSQL
#include "Carp/carp_file.hpp"
#include "Carp/carp_http_client.hpp"

namespace ALittle
{

ServerSchedule::ServerSchedule(const std::string& core_path
	, const std::string& std_path
	, const std::string& sengine_path
	, const std::string& module_title
	, const std::string& module_name
	, const std::string& module_path
	, const std::string& config_path)
{
	m_core_path = core_path;
	m_std_path = std_path;
	m_sengine_path = sengine_path;
	m_module_title = module_title;
	m_module_path = module_path;
	m_module_name = module_name;
	m_config_path = config_path;
	m_current_time = 0;
	m_route_system = nullptr;
}

ServerSchedule::~ServerSchedule()
{
}

void ServerSchedule::RegisterToScript()
{
	lua_State* L = m_script_system.GetLuaState();

	// register script system
	luabridge::getGlobalNamespace(L)
        .beginClass<ServerSchedule>("__CPPAPIServerSchedule")

#ifdef HAS_MYSQL
        .addFunction("StartMysqlQuery", &ServerSchedule::StartMysqlQuery)
        .addFunction("AddMysqlStatement", &ServerSchedule::AddMysqlStatement)
        .addFunction("AddMysqlNormal", &ServerSchedule::AddMysqlNormal)
		.addFunction("AddMysqlEmpty", &ServerSchedule::AddMysqlEmpty)
#endif // HAS_MYSQL

		.addFunction("HttpGet", &ServerSchedule::HttpGet)
		.addFunction("HttpPost", &ServerSchedule::HttpPost)
		.addFunction("CreateHttpServer", &ServerSchedule::CreateHttpServer)
		.addFunction("GetHttpServerYunIp", &ServerSchedule::GetHttpServerYunIp)
		.addFunction("GetHttpServerIp", &ServerSchedule::GetHttpServerIp)
		.addFunction("GetHttpServerPort", &ServerSchedule::GetHttpServerPort)
		.addFunction("HttpClose", &ServerSchedule::HttpClose)
		.addFunction("HttpSendString", &ServerSchedule::HttpSendString)
		.addFunction("HttpSendFile", &ServerSchedule::HttpSendFile)
		.addFunction("HttpStartReceiveFile", &ServerSchedule::HttpStartReceiveFile)

		.addFunction("CreateClientServer", &ServerSchedule::CreateClientServer)
		.addFunction("GetClientServerYunIp", &ServerSchedule::GetClientServerYunIp)
		.addFunction("GetClientServerIp", &ServerSchedule::GetClientServerIp)
		.addFunction("GetClientServerPort", &ServerSchedule::GetClientServerPort)
		.addFunction("ClientClose", &ServerSchedule::ClientClose)
		.addFunction("ClientSend", &ServerSchedule::ClientSend)

	    .addFunction("ReleaseRtp", &ServerSchedule::ReleaseRtp)
		.addFunction("ReleaseAllRtp", &ServerSchedule::ReleaseAllRtp)
		.addCFunction("UseRtp", &ServerSchedule::UseRtpForLua)
		.addFunction("SetFromRtp", &ServerSchedule::SetFromRtp)
		.addFunction("SetFromAuth", &ServerSchedule::SetFromAuth)
		.addFunction("SetToRtp", &ServerSchedule::SetToRtp)
		.addFunction("SetToAuth", &ServerSchedule::SetToAuth)
		.addFunction("ClearIdleRtp", &ServerSchedule::ClearIdleRtp)
		.addFunction("StartRecordRtp", &ServerSchedule::StartRecordRtp)
		.addFunction("StopRecordRtp", &ServerSchedule::StopRecordRtp)

		.addFunction("ReleaseNat", &ServerSchedule::ReleaseNat)
		.addFunction("ReleaseAllNat", &ServerSchedule::ReleaseAllNat)
		.addFunction("UseNat", &ServerSchedule::UseNat)
		.addFunction("SetNatAuth", &ServerSchedule::SetNatAuth)
		.addFunction("SetNatTarget", &ServerSchedule::SetNatTarget)
		.addFunction("ClearIdleNat", &ServerSchedule::ClearIdleNat)

		.addFunction("CreateUdpServer", &ServerSchedule::CreateUdpServer)
		.addFunction("CloseUdpServer", &ServerSchedule::CloseUdpServer)
		.addFunction("SendUdpMessage", &ServerSchedule::SendUdpMessage)

		.addFunction("StartRouteSystem", &ServerSchedule::StartRouteSystem)
		.addFunction("GetRouteType", &ServerSchedule::GetRouteType)
		.addFunction("GetRouteNum", &ServerSchedule::GetRouteNum)
		.addFunction("GetRouteId", &ServerSchedule::GetRouteId)
		.addFunction("CreateConnectServer", &ServerSchedule::CreateConnectServer)
		.addFunction("CreateConnectClient", &ServerSchedule::CreateConnectClient)
		.addFunction("ConnectSession", &ServerSchedule::ConnectSession)
		.addFunction("CalcConnectKey", &ServerSchedule::CalcConnectKey)
		.addFunction("SessionClose", &ServerSchedule::SessionClose)
		.addFunction("SessionSend", &ServerSchedule::SessionSend)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_ServerSchedule");

#ifdef HAS_MYSQL
	luabridge::getGlobalNamespace(L)
		.beginClass<MysqlStatementQuery>("__CPPAPIMysqlStatementQuery")
		.addConstructor<void(*)()>()
        .addFunction("SetSQL", &MysqlStatementQuery::SetSQL)
        .addFunction("GetSQL", &MysqlStatementQuery::GetSQL)
		.addFunction("GetCount", &MysqlStatementQuery::GetCount)
		.addFunction("GetAffectCount", &MysqlStatementQuery::GetAffectCount)
		.addFunction("PushBool", &MysqlStatementQuery::PushBool)
		.addFunction("PushInt", &MysqlStatementQuery::PushInt)
		.addFunction("PushDouble", &MysqlStatementQuery::PushDouble)
		.addFunction("PushI64", &MysqlStatementQuery::PushLongLong)
		.addFunction("PushString", &MysqlStatementQuery::PushString)
		.addFunction("HasNext", &MysqlStatementQuery::HasNext)
		.addFunction("Next", &MysqlStatementQuery::Next)
		.addFunction("ReadType", &MysqlStatementQuery::ReadType)
		.addFunction("ReadBool", &MysqlStatementQuery::ReadBool)
		.addFunction("ReadInt", &MysqlStatementQuery::ReadInt)
		.addFunction("ReadDouble", &MysqlStatementQuery::ReadDouble)
		.addFunction("ReadI64", &MysqlStatementQuery::ReadLongLong)
		.addFunction("ReadString", &MysqlStatementQuery::ReadString)
		.endClass();
#endif // HAS_MYSQL
}

int ServerSchedule::Start()
{
	// 初始化脚本系统
	m_script_system.Setup();
	
	// 把相关接口注册到脚本
	RegisterToScript();

	m_script_system.Require((m_core_path + "Script/ALittle").c_str());
	m_script_system.Invoke("RequireCore", (m_core_path + "Script/").c_str());
	m_script_system.Require((m_std_path + "Script/ALittle").c_str());
	m_script_system.Invoke("RequireStd", (m_std_path + "Script/").c_str());
	m_script_system.Require((m_sengine_path + "Script/ALittle").c_str());
	m_script_system.Invoke("RequireSEngine", (m_sengine_path + "Script/").c_str());

	m_script_system.Invoke("__ALITTLEAPI_SetupMainModule", m_sengine_path.c_str(), m_module_path.c_str(), m_module_name.c_str(), m_config_path.c_str());

	// 创建定时器
	m_current_time = CarpTime::GetCurMSTime();
	// 间隔20毫秒执行一次update
	TimerLoop(20, std::bind(&ServerSchedule::Update, this, std::placeholders::_1));
	// 阻塞执行
	Run(false);

#ifdef HAS_MYSQL
	m_mysql_system.Shutdown();
#endif // HAS_MYSQL
	m_script_system.Invoke("__ALITTLEAPI_ShutdownMainModule", m_module_name.c_str());

	m_script_system.Release();

	for (const auto& server : m_http_server_set)
		server->Close();
	m_http_server_set.clear();
	m_id_map_http.clear();

	for (const auto& server : m_client_server_set)
		server->Close();
	m_client_server_set.clear();

	m_id_map_client.clear();
	m_client_map_id.clear();

	for (const auto& server : m_rudp_server_set)
		server->Close(true);
	m_rudp_server_set.clear();

	m_id_map_rudp.clear();
	m_rudp_map_id.clear();

	if (m_route_system != nullptr)
	{
		m_route_system->Close();
		delete m_route_system;
		m_route_system = nullptr;
	}

	for (auto& pair : m_use_map_rtp)
		pair.second->Stop();
	m_use_map_rtp.clear();
	m_release_map_rtp.clear();

	for (auto& pair : m_use_map_nat)
		pair.second->Stop();
	m_use_map_nat.clear();
	m_release_map_nat.clear();

	for (auto& pair : m_udp_server_map)
	{
		for (auto& sub_pair : pair.second)
		    sub_pair.second->Close();
	}
	m_udp_server_map.clear();

	return 0;
}

void ServerSchedule::Update(time_t cur_time)
{
	// update script logic
	m_script_system.Invoke("__ALITTLEAPI_Update", cur_time - m_current_time);
	m_current_time = cur_time;
}

#ifdef HAS_MYSQL

void ServerSchedule::StartMysqlQuery(int thread_count, const char* ip, const char* username, const char* password, unsigned int port, const char* db_name)
{
	m_mysql_system.Setup(thread_count, ip, username, password, port, db_name);
}

bool ServerSchedule::AddMysqlStatement(int thread_id, int query_id, MysqlStatementQuery* query)
{
	return m_mysql_system.AddTask(thread_id, query_id, query, this);
}

bool ServerSchedule::AddMysqlNormal(int thread_id, int query_id, const char* sql)
{
	return m_mysql_system.AddTask(thread_id, query_id, sql, this);
}

bool ServerSchedule::AddMysqlEmpty(int thread_id, int query_id)
{
	return m_mysql_system.AddTask(thread_id, query_id, this);
}

void ServerSchedule::HandleMysqlQuery(int query_id, bool result, std::string reason)
{
	if (result)
		m_script_system.Invoke("__ALITTLEAPI_HandleMysqlQueryTask", query_id);
	else
		m_script_system.Invoke("__ALITTLEAPI_HandleMysqlQueryTask", query_id, reason.c_str());
}

void ServerSchedule::HandleMysqlEmpty(int query_id, bool result, std::string reason)
{
	if (result)
		m_script_system.Invoke("__ALITTLEAPI_HandleMysqlEmptyTask", query_id);
	else
		m_script_system.Invoke("__ALITTLEAPI_HandleMysqlEmptyTask", query_id, reason.c_str());
}

#endif // HAS_MYSQL

bool ServerSchedule::CreateHttpServer(const char* yun_ip, const char* ip, int port, bool is_ssl)
{
	std::string yun_ip_str;
	if (yun_ip != nullptr) yun_ip_str = yun_ip;
	std::string ip_str;
	if (ip != nullptr) ip_str = ip;

	auto server = std::make_shared<CarpHttpServer>();
	const bool result = server->Start(yun_ip_str, ip_str, port, 30, is_ssl
		, &GetIOService()
		, std::bind(&ServerSchedule::HandleHttpMessage, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ServerSchedule::HandleHttpFileMessage, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ServerSchedule::HandleHttpFileCompletedMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
		, "", "", "");
	if (!result) return false;

	m_http_server_set.insert(server);
	return true;
}

const char* ServerSchedule::GetHttpServerYunIp() const
{
	if (m_http_server_set.empty()) return nullptr;

	const auto it = m_http_server_set.begin();
	return (*it)->GetYunIp().c_str();
}

const char* ServerSchedule::GetHttpServerIp() const
{
	if (m_http_server_set.empty()) return nullptr;

	const auto it = m_http_server_set.begin();
	return (*it)->GetIp().c_str();
}

int ServerSchedule::GetHttpServerPort() const
{
	if (m_http_server_set.empty()) return 0;

	auto it = m_http_server_set.begin();
	return (*it)->GetPort();
}

void ServerSchedule::HandleHttpMessage(CarpHttpSenderPtr sender, const std::string& msg)
{
	const int id = m_id_creator.CreateID();
	m_id_map_http[id] = sender;
	sender->m_id = id;

	std::string url;
	std::string method;
	std::string path;
	std::string param;
	std::string content_type;
	std::string content;
	if (!CarpHttp::AnalysisRequest(msg, url, method, path, &param, &content_type, &content))
	{
		CARP_WARN("error request:\n" << msg);
		sender->Close();
		return;
	}

	if (!path.empty() && path[0] == '/')
		path = path.substr(1);

	m_script_system.Invoke("__ALITTLEAPI_HttpTask", id, url.c_str(), path.c_str(), param.c_str(), content.c_str());
}

bool ServerSchedule::HandleHttpFileMessage(CarpHttpSenderPtr sender, const std::string& msg)
{
	std::string url;
	std::string method;
	std::string path;
	std::string param;
	std::string content_type;
	std::string content;
	if (!CarpHttp::AnalysisRequest(msg, url, method, path, &param, &content_type, &content))
	{
		CARP_WARN("error request:\n" << msg);
		return false;
	}

	int id = m_id_creator.CreateID();
	m_id_map_http[id] = sender;
	sender->m_id = id;

	if (!path.empty() && path[0] == '/')
		path = path.substr(1);

	m_script_system.Invoke("__ALITTLEAPI_HttpFileTask", id, path.c_str(), param.c_str(), content.c_str());
	return true;
}

void ServerSchedule::HttpGet(int id, const char* url)
{
	CarpHttpClientTextPtr client = CarpHttpClientTextPtr(new CarpHttpClientText);
	client->SendRequest(url, true, "text/html", "", 0
		, [this, id](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			if (result)
				m_script_system.Invoke("__ALITTLEAPI_HttpSucceed", id, body.c_str());
			else
				m_script_system.Invoke("__ALITTLEAPI_HttpFailed", id, head.c_str());
		}, nullptr, &GetIOService(), "", 0, "");
}

void ServerSchedule::HttpPost(int id, const char* url, const char* type, const char* content)
{
	CarpHttpClientTextPtr client = CarpHttpClientTextPtr(new CarpHttpClientText);
	client->SendRequest(url, false, type, content, strlen(content)
		, [this, id](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			if (result)
				m_script_system.Invoke("__ALITTLEAPI_HttpSucceed", id, body.c_str());
			else
				m_script_system.Invoke("__ALITTLEAPI_HttpFailed", id, head.c_str());
		}, nullptr, &GetIOService(), "", 0, "");
}

void ServerSchedule::HttpClose(int id)
{
	auto it = m_id_map_http.find(id);
	if (it == m_id_map_http.end())
		return;

	CarpHttpSenderPtr sender = it->second.lock();
	m_id_creator.ReleaseID(id);
	m_id_map_http.erase(it);
	if (!sender) return;

	sender->Close();
}

void ServerSchedule::HttpSendString(int id, const char* content)
{
	auto it = m_id_map_http.find(id);
	if (it == m_id_map_http.end())
		return;

	CarpHttpSenderPtr sender = it->second.lock();
	m_id_creator.ReleaseID(id);
	m_id_map_http.erase(it);
	if (!sender) return;

	sender->SendString(content);
}

void ServerSchedule::HttpSendFile(int id, const char* file_path, int start_size)
{
	const auto it = m_id_map_http.find(id);
	if (it == m_id_map_http.end())
		return;

	CarpHttpSenderPtr sender = it->second.lock();
	m_id_creator.ReleaseID(id);
	m_id_map_http.erase(it);
	if (!sender) return;

	const std::string content_type = CarpHttp::GetContentTypeByExt(CarpFile::GetFileExtByPath(file_path));
	const std::string show_name = CarpFile::GetFileNameByPath(file_path);
	sender->SendFile(file_path, content_type.c_str(), false, start_size, show_name.c_str());
}

void ServerSchedule::HttpStartReceiveFile(int id, const char* file_path, int start_size)
{
	const auto it = m_id_map_http.find(id);
	if (it == m_id_map_http.end()) return;

	CarpHttpSenderPtr sender = it->second.lock();
	if (!sender)
	{
		HandleHttpFileCompletedMessage(sender, std::string(file_path), false, std::string(u8"Http请求方已经断开"));
		return;
	}

	std::string reason;
	if (!sender->StartReceiveFile(file_path, start_size, reason))
	{
		HandleHttpFileCompletedMessage(sender, std::string(file_path), false, reason);
	}
}

void ServerSchedule::HandleHttpFileCompletedMessage(CarpHttpSenderPtr sender, const std::string& file_path, bool succeed, const std::string& reason)
{
	// 这里保证lua协程执行有严格的顺序
	GetIOService().post(std::bind(&ServerSchedule::HandleHttpFileCompletedMessageImpl, this, sender, std::string(file_path), succeed, reason));
}

void ServerSchedule::HandleHttpFileCompletedMessageImpl(CarpHttpSenderPtr sender, const std::string& file_path, bool succeed, const std::string& reason)
{
	const int id = sender->m_id;

	const auto it = m_id_map_http.find(id);
	if (it == m_id_map_http.end())
		return;

	if (succeed)
		m_script_system.Invoke("__ALITTLEAPI_HttpFileCompletedTask", id);
	else
		m_script_system.Invoke("__ALITTLEAPI_HttpFileCompletedTask", id, reason.c_str());
}

bool ServerSchedule::CreateClientServer(const char* yun_ip, const char* ip, int port, bool rudp)
{
	std::string yun_ip_str;
	if (yun_ip != nullptr) yun_ip_str = yun_ip;
	std::string ip_str;
	if (ip != nullptr) ip_str = ip;

	if (rudp)
	{
		auto server = std::make_shared<CarpRudpServerImpl>();
		if (!server->Start(yun_ip_str, ip_str, port, 30, this, this)) return false;
		m_rudp_server_set.insert(server);
	}
	else
	{
		auto server = std::make_shared<CarpConnectServerImpl>();
		if (!server->Start(yun_ip_str, ip_str, port, 30, this, this)) return false;
		m_client_server_set.insert(server);
	}
	return true;
}

const char* ServerSchedule::GetClientServerYunIp() const
{
	if (!m_client_server_set.empty())
	{
		const auto it = m_client_server_set.begin();
		return (*it)->GetYunIp().c_str();
	}

	if (!m_rudp_server_set.empty())
	{
		auto it = m_rudp_server_set.begin();
		return (*it)->GetYunIp().c_str();
	}

	return nullptr;
}

const char* ServerSchedule::GetClientServerIp() const
{
	if (m_client_server_set.empty()) return nullptr;

	const auto it = m_client_server_set.begin();
	return (*it)->GetIp().c_str();
}

int ServerSchedule::GetClientServerPort() const
{
	if (!m_client_server_set.empty())
	{
		const auto it = m_client_server_set.begin();
		return (*it)->GetPort();
	}

	if (!m_rudp_server_set.empty())
	{
		const auto it = m_rudp_server_set.begin();
		return (*it)->GetPort();
	}

	return 0;
}

void ServerSchedule::HandleClientConnect(CarpConnectReceiverPtr sender)
{
	const int id = m_id_creator.CreateID();
	m_id_map_client[id] = sender;
	m_client_map_id[sender] = id;

	m_script_system.Invoke("__ALITTLEAPI_ClientConnect", id, sender->GetRemoteIP().c_str(), sender->GetRemotePort());
}

void ServerSchedule::HandleClientDisconnect(CarpConnectReceiverPtr sender)
{
	const auto it = m_client_map_id.find(sender);
	if (it == m_client_map_id.end()) return;
	const int id = it->second;
	m_client_map_id.erase(it);

	m_id_map_client.erase(id);
	m_id_creator.ReleaseID(id);

	m_script_system.Invoke("__ALITTLEAPI_ClientDisconnect", id);
}

void ServerSchedule::HandleClientMessage(CarpConnectReceiverPtr sender, int message_size, int message_id, int message_rpcid, void* memory)
{
	const auto it = m_client_map_id.find(sender);
	if (it == m_client_map_id.end()) return;

	m_read_factory.Deserialize(memory, message_size);
	m_read_factory.SetID(message_id);
	m_read_factory.SetRpcID(message_rpcid);

	m_script_system.Invoke("__ALITTLEAPI_ClientMessage", it->second, message_id, message_rpcid, &m_read_factory);
}

void ServerSchedule::ClientClose(int id)
{
	{
		auto it = m_id_map_client.find(id);
		if (it != m_id_map_client.end())
		{
			it->second->Close();
			m_id_map_client.erase(it);
			return;
		}
	}

	{
		auto it = m_id_map_rudp.find(id);
		if (it != m_id_map_rudp.end())
		{
			it->second->Close(false);
			m_id_map_rudp.erase(it);
			return;
		}
	}
}

void ServerSchedule::ClientSend(int id, CarpMessageWriteFactory* factory)
{
	{
		auto it = m_id_map_client.find(id);
		if (it != m_id_map_client.end())
		{
			it->second->Send(*factory);
			return;
		}
	}

	{
		auto it = m_id_map_rudp.find(id);
		if (it != m_id_map_rudp.end())
		{
			it->second->Send(*factory);
			return;
		}
	}
}

void ServerSchedule::HandleRudpConnect(CarpRudpReceiverPtr sender)
{
	int id = m_id_creator.CreateID();
	m_id_map_rudp[id] = sender;
	m_rudp_map_id[sender] = id;

	m_script_system.Invoke("__ALITTLEAPI_ClientConnect", id, sender->GetRemoteIP().c_str(), sender->GetRemotePort());
}

void ServerSchedule::HandleRudpDisconnect(CarpRudpReceiverPtr sender)
{
	const auto it = m_rudp_map_id.find(sender);
	if (it == m_rudp_map_id.end()) return;
	const int id = it->second;
	m_rudp_map_id.erase(it);

	m_id_map_rudp.erase(id);
	m_id_creator.ReleaseID(id);

	m_script_system.Invoke("__ALITTLEAPI_ClientDisconnect", id);
}

void ServerSchedule::HandleRudpMessage(CarpRudpReceiverPtr sender, int message_size, int message_id, int message_rpcid, void* memory)
{
	auto it = m_rudp_map_id.find(sender);
	if (it == m_rudp_map_id.end()) return;

	m_read_factory.Deserialize(memory, message_size);
	m_read_factory.SetID(message_id);
	m_read_factory.SetRpcID(message_rpcid);

	m_script_system.Invoke("__ALITTLEAPI_ClientMessage", it->second, message_id, message_rpcid, &m_read_factory);
}

void ServerSchedule::ReleaseRtp(int first_port)
{
	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->Stop();
	m_release_map_rtp[first_port] = use_it->second;
	m_use_map_rtp.erase(use_it);

	CARP_INFO("rtp release count:" << m_release_map_rtp.size());
	CARP_INFO("rtp use count:" << m_use_map_rtp.size());
}

void ServerSchedule::ReleaseAllRtp()
{
	for (auto& pair : m_use_map_rtp)
	{
		pair.second->Stop();
		m_release_map_rtp[pair.first] = pair.second;
	}
	m_use_map_rtp.clear();

	CARP_INFO("rtp release count:" << m_release_map_rtp.size());
	CARP_INFO("rtp use count:" << m_use_map_rtp.size());
}

int ServerSchedule::UseRtpForLua(lua_State* L)
{
    // 读取参数
    int index = 2;
	int first_port = static_cast<int>(luaL_checkinteger(L, index++));
    const char* call_id = luaL_checkstring(L, index++);

    const char* from_rtp_ip = luaL_checkstring(L, index++);
	const int from_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));
	
	const char* to_rtp_ip = luaL_checkstring(L, index++);
	const int to_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));

    // 执行
    UseRtp(first_port, call_id
           , from_rtp_ip, from_rtp_port
           , to_rtp_ip, to_rtp_port);

    return 0;
}

bool ServerSchedule::UseRtp(int first_port, const std::string& call_id
                            , const std::string& from_rtp_ip, int from_rtp_port
							, const std::string& to_rtp_ip, int to_rtp_port)
{
	CarpRtpServerPtr rtp;
	const auto release_it = m_release_map_rtp.find(first_port);
	if (release_it != m_release_map_rtp.end())
	{
		rtp = release_it->second;
		m_release_map_rtp.erase(release_it);
	}
	else
	{
		rtp = std::make_shared<CarpRtpServer>();
	}

	// 创建rtp
	if (!rtp->Create(from_rtp_ip, from_rtp_port, to_rtp_ip, to_rtp_port, this))
		return false;

	m_use_map_rtp[first_port] = rtp;
	// 开始使用rtp
	rtp->Start(call_id);

	// 打印信息
	CARP_INFO("rtp release count:" << m_release_map_rtp.size());
	CARP_INFO("rtp use count:" << m_use_map_rtp.size());

	return true;
}

void ServerSchedule::SetFromRtp(int first_port, const char* rtp_ip, int rtp_port)
{
	if (rtp_ip == nullptr) return;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end())
	{
		CARP_WARN("SetFromRtp can't find rtp first_port:" << first_port);
		return;
	}

	use_it->second->SetFromRtp(rtp_ip, rtp_port);
}

void ServerSchedule::SetFromAuth(int first_port, const char* password)
{
	if (password == nullptr) return;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end())
	{
		CARP_WARN("SetFromAuth can't find rtp first_port:" << first_port);
		return;
	}

	use_it->second->SetFromAuth(password);
}

void ServerSchedule::SetToRtp(int first_port, const char* rtp_ip, int rtp_port)
{
	if (rtp_ip == nullptr) return;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end())
	{
		CARP_WARN("SetToRtp can't find rtp first_port:" << first_port);
		return;
	}

	use_it->second->SetToRtp(rtp_ip, rtp_port);
}

void ServerSchedule::SetToAuth(int first_port, const char* password)
{
	if (password == nullptr) return;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end())
	{
		CARP_WARN("SetToAuth can't find rtp first_port:" << first_port);
		return;
	}

	use_it->second->SetToAuth(password);
}

bool ServerSchedule::StartRecordRtp(int first_port, const char* file_path)
{
	if (file_path == nullptr) return false;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return false;

	return use_it->second->StartRecord(file_path);
}

void ServerSchedule::StopRecordRtp(int first_port)
{
	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->StopRecord();
}

void ServerSchedule::ClearIdleRtp(int idle_delta_time)
{
	const time_t cur_time = time(nullptr);

	bool has_close = false;
	for (auto release_it = m_release_map_rtp.begin(); release_it != m_release_map_rtp.end();)
	{
		if (cur_time - release_it->second->GetIdleTime() > idle_delta_time)
		{
			release_it->second->Close();
			release_it = m_release_map_rtp.erase(release_it);

			has_close = true;
		}
		else
		{
			++release_it;
		}
	}

	if (has_close)
	{
		CARP_INFO("rtp release count:" << m_release_map_rtp.size());
		CARP_INFO("rtp use count:" << m_use_map_rtp.size());
	}
}

void ServerSchedule::ReleaseNat(int nat_port)
{
	auto use_it = m_use_map_nat.find(nat_port);
	if (use_it == m_use_map_nat.end()) return;

	use_it->second->Stop();
	m_release_map_nat[nat_port] = use_it->second;
	m_use_map_nat.erase(use_it);

	CARP_INFO("nat release count:" << m_release_map_nat.size());
	CARP_INFO("nat use count:" << m_use_map_nat.size());
}

void ServerSchedule::ReleaseAllNat()
{
	for (auto& pair : m_use_map_nat)
	{
		pair.second->Stop();
		m_release_map_nat[pair.first] = pair.second;
	}
	m_use_map_nat.clear();

	CARP_INFO("nat release count:" << m_release_map_nat.size());
	CARP_INFO("nat use count:" << m_use_map_nat.size());
}

bool ServerSchedule::UseNat(const char* nat_ip, int nat_port)
{
	CarpNatServerPtr nat;
	const auto release_it = m_release_map_nat.find(nat_port);
	if (release_it != m_release_map_nat.end())
	{
		nat = release_it->second;
		m_release_map_nat.erase(release_it);
	}
	else
	{
		nat = std::make_shared<CarpNatServer>();
	}

	// 创建nat
	if (!nat->Create(nat_ip, nat_port, this))
		return false;

	m_use_map_nat[nat_port] = nat;
	// 开始使用nat
	nat->Start();

	// 打印信息
	CARP_INFO("nat release count:" << m_release_map_nat.size());
	CARP_INFO("nat use count:" << m_use_map_nat.size());

	return true;
}

// 设置NAT的鉴权密码
void ServerSchedule::SetNatAuth(int nat_port, const char* password)
{
	if (password == nullptr) return;

	auto use_it = m_use_map_nat.find(nat_port);
	if (use_it == m_use_map_nat.end())
	{
		CARP_WARN("SetNatAuth can't find nat nat_port:" << nat_port);
		return;
	}

	use_it->second->SetAuth(password);
}

// 设置被呼叫方ip和端口
void ServerSchedule::SetNatTarget(int nat_port, const char* target_ip, int target_port)
{
	if (target_ip == nullptr) return;

	auto use_it = m_use_map_nat.find(nat_port);
	if (use_it == m_use_map_nat.end())
	{
		CARP_WARN("SetNatTarget can't find nat nat_port:" << nat_port);
		return;
	}

	use_it->second->SetTarget(target_ip, target_port);
}

void ServerSchedule::ClearIdleNat(int idle_delta_time)
{
	const time_t cur_time = time(nullptr);

	bool has_close = false;
	for (auto release_it = m_release_map_nat.begin(); release_it != m_release_map_nat.end();)
	{
		if (cur_time - release_it->second->GetIdleTime() > idle_delta_time)
		{
			release_it->second->Close();
			release_it = m_release_map_nat.erase(release_it);

			has_close = true;
		}
		else
		{
			++release_it;
		}
	}

	if (has_close)
	{
		CARP_INFO("nat release count:" << m_release_map_nat.size());
		CARP_INFO("nat use count:" << m_use_map_nat.size());
	}
}

bool ServerSchedule::CreateUdpServer(const char* ip, int port)
{
	if (ip == nullptr) return false;

	const auto ip_it = m_udp_server_map.find(ip);
	if (ip_it != m_udp_server_map.end())
	{
		const auto port_it = ip_it->second.find(port);
		if (port_it != ip_it->second.end()) return true;
	}

	auto server = std::make_shared<CarpUdpServer>(GetIOService());
	server->RegisterUdpHandle(std::bind(&ServerSchedule::HandleUdpMessage, this, std::placeholders::_1, std::string(ip), port));
	if (!server->Start(ip, port)) return false;

	m_udp_server_map[ip][port] = server;
	return true;
}

void ServerSchedule::CloseUdpServer(const char* ip, int port)
{
	if (ip == nullptr) return;

	const auto ip_it = m_udp_server_map.find(ip);
	if (ip_it == m_udp_server_map.end()) return;

	const auto port_it = ip_it->second.find(port);
	if (port_it == ip_it->second.end()) return;

	port_it->second->Close();
	ip_it->second.erase(port_it);
	if (ip_it->second.empty()) m_udp_server_map.erase(ip_it);
}

void ServerSchedule::SendUdpMessage(const char* self_ip, int self_port, const char* remote_ip, int remote_port, const char* message)
{
	if (self_ip == nullptr || remote_ip == nullptr || message == nullptr) return;

	const auto ip_it = m_udp_server_map.find(self_ip);
	if (ip_it == m_udp_server_map.end()) return;

	const auto port_it = ip_it->second.find(self_port);
	if (port_it == ip_it->second.end()) return;

	const auto e_ip_it = m_udp_endpoint_map.find(remote_ip);
	if (e_ip_it != m_udp_endpoint_map.end())
	{
		const auto e_port_it = e_ip_it->second.find(remote_port);
		if (e_port_it != e_ip_it->second.end())
		{
			port_it->second->Send(message, e_port_it->second);
			return;
		}
	}

	size_t count = 0;
	for (auto& ip_pair : m_udp_endpoint_map)
	{
		for (auto& port_pair : ip_pair.second)
			count += port_pair.second.size();
	}
	if (count >= 10240) m_udp_endpoint_map.clear();

	asio::ip::udp::endpoint& endpoint = m_udp_endpoint_map[remote_ip][remote_port] = asio::ip::udp::endpoint(asio::ip::address::from_string(remote_ip), remote_port);
	port_it->second->Send(message, endpoint);
}

void ServerSchedule::HandleUdpMessage(CarpUdpServer::HandleInfo& info, const std::string& self_ip, int self_port)
{
	m_script_system.Invoke("__ALITTLEAPI_HandleUdpMessage", self_ip.c_str(), self_port, info.end_point.address().to_string().c_str(), info.end_point.port(), info.memory);
}

void ServerSchedule::StartRouteSystem(ROUTE_TYPE route_type, ROUTE_NUM route_num)
{
	if (m_route_system != nullptr)
	{
		CARP_ERROR(u8"RouteSystem 已经初始化");
		return;
	}

	const ROUTE_ID route_id = RouteIdDefine::CalcRouteId(route_type, route_num);
	m_route_system = new RouteSystem();
	m_route_system->Start(route_id, 30, 5, this);
}

int ServerSchedule::GetRouteType() const
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return 0;
	}

	return RouteIdDefine::CalcRouteType(m_route_system->GetRouteId());
}

int ServerSchedule::GetRouteNum() const
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return 0;
	}

	return RouteIdDefine::CalcRouteNum(m_route_system->GetRouteId());
}

int ServerSchedule::GetRouteId() const
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return 0;
	}

	return m_route_system->GetRouteId();
}


bool ServerSchedule::CreateConnectServer(const char* yun_ip, const char* ip, int port)
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return false;
	}

	std::string yun_ip_str;
	if (yun_ip != nullptr) yun_ip_str = yun_ip;
	std::string ip_str;
	if (ip != nullptr) ip_str = ip;
	return m_route_system->CreateConnectServer(yun_ip_str, ip_str, port);
}

bool ServerSchedule::CreateConnectClient(const char* ip, int port)
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return false;
	}

	std::string ip_str;
	if (ip != nullptr) ip_str = ip;
	return m_route_system->CreateConnectClient(ip_str, port);
}

void ServerSchedule::ConnectSession(ROUTE_TYPE route_type, ROUTE_NUM route_num)
{
	if (m_route_system == nullptr)
	{
		CARP_ERROR(u8"RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		m_script_system.Invoke("__ALITTLEAPI_ConnectSessionFailed", route_type, route_num, "RouteSystem还未初始化，请调用StartRouteSystem进行初始化");
		return;
	}

	ROUTE_ID route_id = RouteIdDefine::CalcRouteId(route_type, route_num);
	m_route_system->ConnectRoute(route_id, [this, route_type, route_num](const std::string* reason, SessionConnectionPtr session)
		{
			if (reason != nullptr)
			{
				m_script_system.Invoke("__ALITTLEAPI_ConnectSessionFailed", route_type, route_num, reason->c_str());
				return;
			}
			m_script_system.Invoke("__ALITTLEAPI_ConnectSessionSucceed", session->GetConnectKey(), route_type, route_num);
		});
}

CONNECT_KEY ServerSchedule::CalcConnectKey(ROUTE_TYPE src_route_type, ROUTE_NUM src_route_num, ROUTE_TYPE dst_route_type, ROUTE_NUM dst_route_num)
{
	return RouteIdDefine::CalcConnectKey(RouteIdDefine::CalcRouteId(src_route_type, src_route_num), RouteIdDefine::CalcRouteId(dst_route_type, dst_route_num));
}

void ServerSchedule::HandleSessionNotify(bool is_connected, SessionConnectionPtr session)
{
	if (is_connected)
	{
		m_session_map[session->GetConnectKey()] = session;
		m_script_system.Invoke("__ALITTLEAPI_SessionConnect", session->GetConnectKey(), session->GetRouteType(), session->GetRouteNum());
	}
	else
	{
		m_session_map.erase(session->GetConnectKey());
		m_script_system.Invoke("__ALITTLEAPI_SessionDisconnect", session->GetConnectKey(), session->GetRouteType(), session->GetRouteNum());
	}
}

void ServerSchedule::HandleSessionMessage(CONNECT_KEY connect_key, int message_id, int message_rpcid, void* message_body, int message_size)
{
	m_read_factory.Deserialize(message_body, message_size);
	m_read_factory.SetID(message_id);
	m_read_factory.SetRpcID(message_rpcid);

	m_script_system.Invoke("__ALITTLEAPI_SessionMessage", connect_key, message_id, message_rpcid, &m_read_factory);
}

void ServerSchedule::SessionClose(CONNECT_KEY connect_key)
{
	auto it = m_session_map.find(connect_key);
	if (it == m_session_map.end()) return;

	m_route_system->CloseConnect(it->second);
	m_session_map.erase(it);
}

void ServerSchedule::SessionSend(CONNECT_KEY connect_key, CarpMessageWriteFactory* factory)
{
	auto it = m_session_map.find(connect_key);
	if (it == m_session_map.end()) return;

	it->second->Send(*factory);
}

void ServerSchedule::HandleConsoleCmd(std::string cmd)
{
	m_script_system.Invoke("__ALITTLEAPI_HandleConsoleCmd", cmd.c_str());
}

} // ALittle
