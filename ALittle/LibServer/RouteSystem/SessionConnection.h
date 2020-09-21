
#ifndef _ALITTLE_SESSIONCONNECTION_H_
#define _ALITTLE_SESSIONCONNECTION_H_

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <functional>

#include "RouteIdDefine.h"

class CarpMessage;

namespace ALittle
{

class ConnectEndpoint;
typedef std::shared_ptr<ConnectEndpoint> ConnectEndpointPtr;
typedef std::weak_ptr<ConnectEndpoint> ConnectEndpointWeakPtr;

class SessionConnection;
typedef std::shared_ptr<SessionConnection> SessionConnectionPtr;
typedef std::weak_ptr<SessionConnection> SessionConnectionWeakPtr;

// 会话节点信息
class SessionConnection : public std::enable_shared_from_this<SessionConnection>
{
public:
	enum class Status
	{
		SCS_IDLE,			// 空闲
		SCS_CONNECTING,		// 正在连接
		SCS_CONNECTED,		// 连接成功
	};

public:
	SessionConnection() : m_status(Status::SCS_IDLE), m_connect_index(0), m_connect_key(0) {}
	~SessionConnection();
	friend class RouteSystem;
	
public:
	inline CONNECT_KEY GetConnectKey() const { return m_connect_key; }
	// 获取被连接点的route_id
	inline ROUTE_ID GetRouteId() const
	{
		if (m_connect_index == 0)
			return m_vector_route_path.back();
		else
			return m_vector_route_path.front();
	}
    // 获取被连接点的route_type
    inline ROUTE_TYPE GetRouteType() const { return RouteIdDefine::CalcRouteType(GetRouteId()); }
	inline ROUTE_NUM GetRouteNum() const { return RouteIdDefine::CalcRouteNum(GetRouteId()); }
	bool IsConnected() const { return m_status == Status::SCS_CONNECTED; }

	bool Send(const CarpMessage& msg);
	
private:
	bool Close();

private:
	Status m_status;									// 当前连接状态
	std::vector<ROUTE_ID> m_vector_route_path;	// 连接路由
	std::list<ROUTE_ID> m_list_route_path;		// 连接路由
	unsigned short m_connect_index;						// 当前服务器在这个路径中的节点下标

	CONNECT_KEY m_connect_key;					// 连接ID

	ConnectEndpointWeakPtr m_pre_endpoint;		// 上一个节点
	ConnectEndpointWeakPtr m_next_endpoint;		// 下一个节点

public:
	// 会话连接回调
	// reason, SessionConnectionPtr
	typedef std::function<void(const std::string*, SessionConnectionPtr)> ConnectRouteCallback;
	std::vector<ConnectRouteCallback> callback_list;	// 回调函数列表
};

} // ALittle

#endif // _ALITTLE_SESSIONCONNECTION_H_
