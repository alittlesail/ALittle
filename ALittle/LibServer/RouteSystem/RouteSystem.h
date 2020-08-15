
#ifndef _ALITTLE_ROUTESYSTEM_H_
#define _ALITTLE_ROUTESYSTEM_H_

#include <map>
#include <set>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <functional>

#include "RouteIdDefine.h"
#include "SessionConnection.h"

namespace ALittle
{

class ConnectClient;
typedef std::shared_ptr<ConnectClient> ConnectClientPtr;

class ConnectServer;
typedef std::shared_ptr<ConnectServer> ConnectServerPtr;

class ConnectEndpoint;
typedef std::shared_ptr<ConnectEndpoint> ConnectEndpointPtr;
typedef std::weak_ptr<ConnectEndpoint> ConnectEndpointWeakPtr;

class SessionConnection;
typedef std::shared_ptr<SessionConnection> SessionConnectionPtr;

class QConnect2ConnectRPCRead;
class ConnectRouteDisconnected;
class ConnectRouteMessageRead;
class QSession2SessionRPCRead;
class Message;

class ServerSchedule;

class RouteSystem
{
//系统管理/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// 初始化
	void Start(ROUTE_ID route_id, int heartbeat_interval, int reconnect_interval, ServerSchedule* schedule);
	// 释放所有内存
	void Close();

public:
	bool CreateConnectServer(const std::string& yun_ip, const std::string& ip, unsigned int port);
	void ReleaseConnectServer(const std::string& ip, unsigned int port);
	bool CreateConnectClient(const std::string& ip, unsigned int port);
	void ReleaseConnectClient(const std::string& ip, unsigned int port);
	
public:
	bool AddConnectEndpoint(ConnectEndpointPtr endpoint, ROUTE_ID target_route_id);
	void RemoveConnectEndpoint(ConnectEndpointPtr endpoint);

public:
	ROUTE_ID GetRouteId() const { return m_route_id; }

private:
	std::map<ROUTE_ID, ConnectEndpointPtr> m_endpoint_map;		// 用来保存所有已经注册过的连接点
	std::map<std::string, ConnectClientPtr> m_connect_client_map;		// 用来保存所有本地创建的客户端连接点
	std::map<std::string, ConnectServerPtr> m_connect_server_map;		// 用来保存所有本地创建的服务端

private:
	ROUTE_ID m_route_id;		// 当前节点的路由ID
	int m_heartbeat_interval;		// 心跳包间隔时间（秒）
	int m_reconnect_interval;		// 如果客户端连接点连接失败，那么会间隔一定时间重新创建

public:
	ServerSchedule* GetSchedule() { return m_schedule; }

private:
	ServerSchedule* m_schedule;

private:
    void HandleConnectNotify(bool is_connected, SessionConnectionPtr session);

//节点寻路/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// 寻路结果回调
	// reason, route_id_list
	typedef std::function<void(const std::string*, const std::list<ROUTE_ID>&)> SearchRouteCallback;
	
	// 广度优先搜索节点
	struct SearchPathInfo
	{
		int parent_index;			// 父节点的下表
		ROUTE_ID route_id;	// 路由ID
	};

	// 广度优先搜索信息
	struct SearchRouteInfo
	{
		SearchRouteInfo() : cur_index(0), route_id(0) { }

		std::vector<SearchRouteCallback> callback_list;		// 回调函数列表
		ROUTE_ID route_id;							// 目标节点路由ID

		// 添加新的路由节点
		// route_id 新增的节点路由ID
		// first_insert 如果是第一批节点，那么父节点设置为-1
		void AddRoute(ROUTE_ID route_id, bool first_insert)
		{
			// 过滤掉已经添加的节点
			if (search_route_id_set.find(route_id) != search_route_id_set.end())
				return;
			// 设置新的搜索节点信息
			SearchPathInfo info;
			if (first_insert)
				info.parent_index = -1;
			else
				info.parent_index = cur_index;
			info.route_id = route_id;
			search_path.push_back(info);
			// 保存路由ID用于过滤
			search_route_id_set.insert(route_id);
		}

		int cur_index;	// 当前搜索节点的下表
		std::vector<SearchPathInfo> search_path;			// 广度优先搜索列表
		std::set<ROUTE_ID> search_route_id_set;	// 保存所有节点路由ID，用于过滤
	};
	
	// 启动广度优先搜索
	void SearchRoute(ROUTE_ID route_id, SearchRouteCallback callback);

private:
	void SearchRouteImpl(ROUTE_ID search_key, const std::string* reason);
	
	void SearchRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size
								, ROUTE_ID search_key);

	void SearchRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
								, ConnectEndpointWeakPtr src_endpoint, int rpc_id);

	std::map<unsigned int, SearchRouteInfo> m_search_route_map;	// 当期正在进行搜索的路径

//会话连接/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// 启动会话连接
	// route_id_list 连接的路径路由ID列表（包括自己）
	// 注意：如果没有连接成功，那么回调函数的SessionConnectionPtr参数会是空指针
	void ConnectRoute(const std::list<ROUTE_ID>& route_id_list, SessionConnection::ConnectRouteCallback callback);
	void ConnectRoute(ROUTE_ID route_id, SessionConnection::ConnectRouteCallback callback);
	
private:
	void ConnectRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size
									, CONNECT_KEY connect_key);

	void ConnectRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
									, ConnectEndpointWeakPtr src_endpoint, int rpc_id, CONNECT_KEY connect_key);
	
	std::map<unsigned int, SessionConnectionPtr> m_connect_route_map;	// 当前所有会话连接信息

	void ConnectRouteSearchRouteCallback(const std::string* reason, const std::list<ROUTE_ID>& route_id_list
										, SessionConnection::ConnectRouteCallback callback);
	
//数据包处理/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// 处理连接点的可靠性调用，所以这里不管怎么样，都要正常返回（除非宕机了）
	void HandleQConnect2ConnectRPC(ConnectEndpointPtr endpoint, int src_rpcid
		, int message_id, void* message_body, int message_size);
	// 处理会话连接断开的消息
	void HandleConnectRouteDisconnected(ConnectEndpointPtr endpoint, const ConnectRouteDisconnected& msg);
	// 处理会话连接发过来的单向数据包
	void HandleConnectRouteMessage(ConnectEndpointPtr endpoint, CONNECT_KEY connect_key, int src_rpcid
		, int message_id, int message_rpcid, void* message_body, int message_size
		, void* memory, int memory_size, bool& need_free);
	// 关闭会话连接
	bool CloseConnect(SessionConnectionPtr session);

public:
	RouteSystem();
	~RouteSystem() { Close(); }
};

} // ALittle

#endif // _ALITTLE_ROUTESYSTEM_H_
