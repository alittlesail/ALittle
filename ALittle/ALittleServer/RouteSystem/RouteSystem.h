
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

class CarpMessage;

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

class ConnectRouteDisconnected;

class ServerSchedule;

class RouteSystem
{
//ϵͳ����/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// ��ʼ��
	void Start(ROUTE_ID route_id, int heartbeat_interval, int reconnect_interval, ServerSchedule* schedule);
	// �ͷ������ڴ�
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
	std::map<ROUTE_ID, ConnectEndpointPtr> m_endpoint_map;		// �������������Ѿ�ע��������ӵ�
	std::map<std::string, ConnectClientPtr> m_connect_client_map;		// �����������б��ش����Ŀͻ������ӵ�
	std::map<std::string, ConnectServerPtr> m_connect_server_map;		// �����������б��ش����ķ����

private:
	ROUTE_ID m_route_id;		// ��ǰ�ڵ��·��ID
	int m_heartbeat_interval;		// ���������ʱ�䣨�룩
	int m_reconnect_interval;		// ����ͻ������ӵ�����ʧ�ܣ���ô����һ��ʱ�����´���

public:
	ServerSchedule* GetSchedule() { return m_schedule; }

private:
	ServerSchedule* m_schedule;

private:
    void HandleConnectNotify(bool is_connected, SessionConnectionPtr session);

//�ڵ�Ѱ·/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// Ѱ·����ص�
	// reason, route_id_list
	typedef std::function<void(const std::string*, const std::list<ROUTE_ID>&)> SearchRouteCallback;
	
	// ������������ڵ�
	struct SearchPathInfo
	{
		int parent_index;			// ���ڵ���±�
		ROUTE_ID route_id;	// ·��ID
	};

	// �������������Ϣ
	struct SearchRouteInfo
	{
		SearchRouteInfo() : cur_index(0), route_id(0) { }

		std::vector<SearchRouteCallback> callback_list;		// �ص������б�
		ROUTE_ID route_id;							// Ŀ��ڵ�·��ID

		// ����µ�·�ɽڵ�
		// route_id �����Ľڵ�·��ID
		// first_insert ����ǵ�һ���ڵ㣬��ô���ڵ�����Ϊ-1
		void AddRoute(ROUTE_ID route_id, bool first_insert)
		{
			// ���˵��Ѿ���ӵĽڵ�
			if (search_route_id_set.find(route_id) != search_route_id_set.end())
				return;
			// �����µ������ڵ���Ϣ
			SearchPathInfo info;
			if (first_insert)
				info.parent_index = -1;
			else
				info.parent_index = cur_index;
			info.route_id = route_id;
			search_path.push_back(info);
			// ����·��ID���ڹ���
			search_route_id_set.insert(route_id);
		}

		int cur_index;	// ��ǰ�����ڵ���±�
		std::vector<SearchPathInfo> search_path;			// ������������б�
		std::set<ROUTE_ID> search_route_id_set;	// �������нڵ�·��ID�����ڹ���
	};
	
	// ���������������
	void SearchRoute(ROUTE_ID route_id, SearchRouteCallback callback);

private:
	void SearchRouteImpl(ROUTE_ID search_key, const std::string* reason);
	
	void SearchRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size
								, ROUTE_ID search_key);

	void SearchRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
								, ConnectEndpointWeakPtr src_endpoint, int rpc_id);

	std::map<unsigned int, SearchRouteInfo> m_search_route_map;	// �������ڽ���������·��

//�Ự����/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// �����Ự����
	// route_id_list ���ӵ�·��·��ID�б������Լ���
	// ע�⣺���û�����ӳɹ�����ô�ص�������SessionConnectionPtr�������ǿ�ָ��
	void ConnectRoute(const std::list<ROUTE_ID>& route_id_list, SessionConnection::ConnectRouteCallback callback);
	void ConnectRoute(ROUTE_ID route_id, SessionConnection::ConnectRouteCallback callback);
	
private:
	void ConnectRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size
									, CONNECT_KEY connect_key);

	void ConnectRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
									, ConnectEndpointWeakPtr src_endpoint, int rpc_id, CONNECT_KEY connect_key);
	
	std::map<CONNECT_KEY, SessionConnectionPtr> m_connect_route_map;	// ��ǰ���лỰ������Ϣ

	void ConnectRouteSearchRouteCallback(const std::string* reason, const std::list<ROUTE_ID>& route_id_list
										, SessionConnection::ConnectRouteCallback callback);
	
//���ݰ�����/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	// �������ӵ�Ŀɿ��Ե��ã��������ﲻ����ô������Ҫ�������أ�����崻��ˣ�
	void HandleQConnect2ConnectRPC(ConnectEndpointPtr endpoint, int src_rpcid
		, int message_id, void* message_body, int message_size);
	// ����Ự���ӶϿ�����Ϣ
	void HandleConnectRouteDisconnected(ConnectEndpointPtr endpoint, const ConnectRouteDisconnected& msg);
	// ����Ự���ӷ������ĵ������ݰ�
	void HandleConnectRouteMessage(ConnectEndpointPtr endpoint, CONNECT_KEY connect_key, int src_rpcid
		, int message_id, int message_rpcid, void* message_body, int message_size
		, void* memory, int memory_size, bool& need_free);
	// �رջỰ����
	bool CloseConnect(SessionConnectionPtr session);

public:
	RouteSystem();
	~RouteSystem() { Close(); }
};

} // ALittle

#endif // _ALITTLE_ROUTESYSTEM_H_
