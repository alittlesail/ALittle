
#ifndef _ALITTLE_CONNECTENDPOINT_H_
#define _ALITTLE_CONNECTENDPOINT_H_

#include <asio/asio.hpp>
#include "ALittle/LibCommon/Protocol/Message.h"
#include "ALittle/LibCommon/Tool/SafeIDCreator.h"
#include "RouteIdDefine.h"

#include <memory>
#include <functional>

namespace ALittle
{

class RouteSystem;

class ConnectEndpoint : public std::enable_shared_from_this<ConnectEndpoint>
{
public:
	ConnectEndpoint(RouteSystem* route_system);
	virtual ~ConnectEndpoint();

public:
	virtual void Close(const std::string& reason) = 0;
	virtual void Send(const Message& msg) = 0;
	virtual void SendPocket(void* memory, int memory_size) = 0;
	virtual void NextReadHead() = 0;
	virtual bool IsConnected() = 0;
	virtual const std::string& GetIP() const = 0;
	virtual unsigned int GetPort() const = 0;

public:
	virtual void HandleAsyncConnect(const asio::error_code& ec) {}
	virtual void HandleReconnectTimer(const asio::error_code& ec) {}
	virtual void HandleHeartbeatTimer(const asio::error_code& ec) {}
	virtual void HandleReadHead(const asio::error_code& ec, std::size_t actual_size) {}
	virtual void HandleReadBody(const asio::error_code& ec, std::size_t actual_size) {}
	virtual void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory) {}

public:
	// 处理RPC调用返回包函数
	typedef std::function<void(const std::string* reason, int message_id, void* memory, int memory_size)> RPCCallback;

public:
	// 发送可靠性调用
	void SendWithCallback(const Message& msg, RPCCallback& callback);
	// 应答可靠性调用
	void SendError(int rpc_id, const std::string& reason);
	void SendResponse(int rpc_id, const Message& msg);

public:
	// 处理连接状态
	void HandleConnectSucceed();
	void HandleConnectFailed();
	void HandleDisconnected();
	// 处理消息包
	void HandleMessage(void* memory, int memory_size);

private:
	void HandleMessageImpl(void* memory, int memory_size, bool& need_free);

public:
	ROUTE_ID GetTargetRouteId() const { return m_target_route_id; }

public:
	ROUTE_ID m_route_id;			// 本地路由ID
	ROUTE_ID m_target_route_id;	// 对端路由ID

protected:
	RouteSystem* m_route_system;

public:
	// 清理RPC
	void ClearRPC(const std::string& reason);

private:
	SafeIDCreator<int> m_id_creator;
	std::map<int, RPCCallback> m_rpc_map;
};

} // ALittle

#endif // _ALITTLE_CONNECTENDPOINT_H_
