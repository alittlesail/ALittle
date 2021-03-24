
#ifndef _ALITTLE_SERVERSCHEDULE_H_
#define _ALITTLE_SERVERSCHEDULE_H_

#include <set>
#include <map>
#include <string>

#include "Carp/carp_connect_server.hpp"
#include "Carp/carp_rudp_server.hpp"
#include "Carp/carp_safe_id_creator.hpp"
#include "Carp/carp_file_cache.hpp"
#include "Carp/carp_rtp_server.hpp"
#include "Carp/carp_udp_server.hpp"

#include "../HttpSystem/HttpServer.h"
#include "../RouteSystem/RouteSystem.h"
#include "../MysqlSystem/MysqlSystem.h"
#include "../ScriptSystem/ScriptSystem.h"

namespace ALittle
{

class ServerSchedule : public CarpSchedule, public CarpConnectInterface, public CarpRudpInterface
{
public:
	ServerSchedule(const std::string& core_path
		, const std::string& std_path
		, const std::string& sengine_path
		, const std::string& module_title
		, const std::string& module_name
		, const std::string& module_path
		, const std::string& config_path);
	~ServerSchedule();

private:
	void RegisterToScript();
	CarpSchedule* GetCarpSchedule() { return this; }

public:
	int Start();

	// 处理控制台命令，因为cmd是从另一个线程来的，所以这里不要使用const std::string&
	void HandleConsoleCmd(std::string cmd);

public:
	/* get io service
		* @return io service
		*/
	CarpFileCacheGroup& GetFileCacheGroup() { return m_file_cache; }
	ScriptSystem& GetScriptSystem() { return m_script_system; }
	const std::string& GetModuleTitle() const { return m_module_title; }

private:
	void Update(time_t cur_time);

private:
	std::string m_core_path;
	std::string m_std_path;
	std::string m_sengine_path;
	std::string m_module_title;
	std::string m_module_path;
	std::string m_module_name;
	std::string m_config_path;
	std::string m_string;

private:
	ScriptSystem m_script_system;
	CarpSafeIDCreator<int> m_id_creator;
	time_t m_current_time;
	AsioTimerPtr m_timer;
	CarpMessageReadFactory m_read_factory;

	//FileCache//////////////////////////////////////////////////////////////////////////////////
public:
	void UseFileCache(bool value) { m_use_file_cache = value; }
	void SetFileCacheMaxSize(int max_size) { m_file_cache.SetMaxSize(max_size); }
	void SetFileCacheClearAll() { m_file_cache.ClearAll(); }
	void SetFileCacheClearByMaxSize(int max_size) { m_file_cache.ClearByMaxSize(max_size); }
	void SetFileCacheClearByFilePath(const char* file_path) { m_file_cache.ClearByPath(file_path); }
	void SetFileCacheClearBySize(int size) { m_file_cache.ClearBySize(size); }
	void SetFileCacheClearByTime(int time) { m_file_cache.ClearByTime(time); }

private:
	bool m_use_file_cache = false;
	CarpFileCacheGroup m_file_cache;

	//Mysql//////////////////////////////////////////////////////////////////////////////////
public:
	void StartMysqlQuery(int thread_count
		, const char* ip
		, const char* username
		, const char* password
		, unsigned int port
		, const char* db_name);
    bool AddMysqlStatement(int thread_id, int query_id, MysqlStatementQuery* query);
	bool AddMysqlNormal(int thread_id, int query_id, const char* sql);
	bool AddMysqlEmpty(int thread_id, int query_id);
	// 因为reason是从另一个线程来的，所以不要使用const std::string&
	void HandleMysqlQuery(int query_id, bool result, std::string reason);
	void HandleMysqlEmpty(int query_id, bool result, std::string reason);

private:
	MysqlSystem m_mysql_system;

	//HttpServer//////////////////////////////////////////////////////////////////////////////////
public:
	bool CreateHttpServer(const char* yun_ip, const char* ip, int port, bool is_ssl);
	const char* GetHttpServerYunIp() const;
	const char* GetHttpServerIp() const;
	int GetHttpServerPort() const;

	// handle http message
	void HandleHttpMessage(HttpSenderPtr sender, const std::string& msg);
	// handle http file message
	bool HandleHttpFileMessage(HttpSenderPtr sender, const std::string& msg);
	// handle http file completed message
	void HandleHttpFileCompletedMessage(HttpSenderPtr sender
		, const std::string& file_path
		, bool succeed
		, const std::string& reason);

	void HttpGet(int id, const char* url);
	void HttpPost(int id, const char* url, const char* type, const char* content);

private:
	void HttpClose(int id);
	void HttpSendString(int id, const char* content);
	void HttpSendFile(int id, const char* file_path, int start_size);
	void HttpStartReceiveFile(int id, const char* file_path, int start_size);

	// handle http file completed message
	void HandleHttpFileCompletedMessageImpl(HttpSenderPtr sender
		, const std::string& file_path
		, bool succeed
		, const std::string& reason);

	std::set<HttpServerPtr> m_http_server_set;
	std::map<int, HttpSenderWeakPtr> m_id_map_http;

	//ClientServer//////////////////////////////////////////////////////////////////////////////////
public:
	bool CreateClientServer(const char* yun_ip, const char* ip, int port, bool rudp);
	const char* GetClientServerYunIp() const;
	const char* GetClientServerIp() const;
	int GetClientServerPort() const;

	// handle client connect
	void HandleClientConnect(CarpConnectReceiverPtr sender) override;
	// handle client disconnect
	void HandleClientDisconnect(CarpConnectReceiverPtr sender) override;
	// handle client message
	void HandleClientMessage(CarpConnectReceiverPtr sender, int message_size, int message_id, int message_rpcid, void* memory) override;

private:
	void ClientClose(int id);
	void ClientSend(int id, CarpMessageWriteFactory* factory);

	std::set<CarpConnectServerPtr> m_client_server_set;
	std::map<int, CarpConnectReceiverPtr> m_id_map_client;
	std::map<CarpConnectReceiverPtr, int> m_client_map_id;

public:
	// handle client connect
	void HandleRudpConnect(CarpRudpReceiverPtr sender) override;
	// handle client disconnect
	void HandleRudpDisconnect(CarpRudpReceiverPtr sender) override;
	// handle client message
	void HandleRudpMessage(CarpRudpReceiverPtr sender, int message_size, int message_id, int message_rpcid, void* memory) override;

private:
	std::set<CarpRudpServerPtr> m_rudp_server_set;
	std::map<int, CarpRudpReceiverPtr> m_id_map_rudp;
	std::map<CarpRudpReceiverPtr, int> m_rudp_map_id;

	//RtpServer//////////////////////////////////////////////////////////////////////////////////
public:
	// 释放rtp
	void ReleaseRtp(int first_port);
	void ReleaseAllRtp();

    int UseRtpForLua(lua_State* L);
	// 开始使用rtp
	bool UseRtp(int first_port
		, const std::vector<std::string>& client_rtp_ip_list, int client_rtp_port
		, const std::string& self_rtp_ip, int self_rtp_port
		, const std::string& inner_rtp_ip, int inner_rtp_port
		, const std::string& remote_rtp_ip, int remote_rtp_port
		, const std::string& call_id, int client_id, unsigned int ssrc);

	// 设置线路的rtp
	void SetRemoteRtp(int first_port, const std::string& remote_rtp_ip, int remote_rtp_port);

	// 设置内部转接rtp
	void SetInnerRtp(int first_port, const std::string& inner_rtp_ip, int inner_rtp_port);

	// 转接到客户端
	void TransClient(int first_port, int client_id);

	// 清理空闲的rtp
	void ClearIdleRtp(int idle_delta_time);

private:
	// 所有的rtp
	std::map<int, CarpRtpServerPtr> m_use_map_rtp;
	// 等待释放的rtp
	std::map<int, CarpRtpServerPtr> m_release_map_rtp;

    //SipServer//////////////////////////////////////////////////////////////////////////////////
public:
	// 启动Udp服务器
	bool CreateUdpServer(const char* ip, int port);
	// 关闭Udp服务器
	void CloseUdpServer(const char* ip, int port);
	// 发送消息
	void SendUdpMessage(const char* self_ip, int self_port, const char* remote_ip, int remote_port, const char* message);

private:
	void HandleUdpMessage(CarpUdpServer::HandleInfo& info, const std::string& self_ip, int self_port);

private:
	// UDP服务器
	std::map<std::string, std::map<int, CarpUdpServerPtr>> m_udp_server_map;
	std::map<std::string, std::map<int, asio::ip::udp::endpoint>> m_udp_endpoint_map;

	//RouteSystem//////////////////////////////////////////////////////////////////////////////////
private:
	void StartRouteSystem(ROUTE_TYPE route_type, ROUTE_NUM route_num);
	int GetRouteType() const;
	int GetRouteNum() const;
	int GetRouteId() const;
	bool CreateConnectServer(const char* yun_ip, const char* ip, int port);
	bool CreateConnectClient(const char* ip, int port);
	void ConnectSession(ROUTE_TYPE route_type, ROUTE_NUM route_num);
	CONNECT_KEY CalcConnectKey(ROUTE_TYPE src_route_type, ROUTE_NUM src_route_num, ROUTE_TYPE dst_route_type, ROUTE_NUM dst_route_num);

public:
	// handle session connected or disconnected
	void HandleSessionNotify(bool is_connected, SessionConnectionPtr session);
	// handle session message
	void HandleSessionMessage(CONNECT_KEY connect_key, int message_id, int message_rpcid, void* message_body, int message_size);

private:
	void SessionClose(CONNECT_KEY connect_key);
	void SessionSend(CONNECT_KEY connect_key, CarpMessageWriteFactory* factory);

	std::map<CONNECT_KEY, SessionConnectionPtr> m_session_map;
	RouteSystem* m_route_system;
};

} // ALittle

#endif // _ALITTLE_SERVERSCHEDULE_H_
