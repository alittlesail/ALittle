
#ifndef _ALITTLE_CONNECTENDPOINT_H_
#define _ALITTLE_CONNECTENDPOINT_H_

#include <asio.hpp>
#include "Carp/carp_message.hpp"
#include "Carp/carp_safe_id_creator.hpp"
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
	virtual void Close(const std::string& reason, int delay_second=0) = 0;
	virtual void Send(const CarpMessage& msg) = 0;
	virtual void SendPocket(void* memory, int memory_size) = 0;
	virtual void NextReadHead() = 0;
	virtual bool IsConnected() = 0;
	virtual const std::string& GetIP() const = 0;
	virtual unsigned int GetPort() const = 0;

public:
	virtual void HandleAsyncConnect(const asio::error_code& ec) {}
	virtual void HandleReconnectTimer(const asio::error_code& ec) {}
	virtual void HandleHeartbeatTimer(const asio::error_code& ec) {}
	virtual void HandleDelayCloseTimer(const asio::error_code& ec, const std::string& reason) {}
	virtual void HandleReadHead(const asio::error_code& ec, std::size_t actual_size) {}
	virtual void HandleReadBody(const asio::error_code& ec, std::size_t actual_size) {}
	virtual void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory) {}

public:
	// ����RPC���÷��ذ�����
	typedef std::function<void(const std::string* reason, int message_id, void* memory, int memory_size)> RPCCallback;

public:
	// ���Ϳɿ��Ե���
	void SendWithCallback(const CarpMessage& msg, RPCCallback& callback);
	// Ӧ��ɿ��Ե���
	void SendError(int rpc_id, const std::string& reason);
	void SendResponse(int rpc_id, const CarpMessage& msg);

public:
	// ��������״̬
	void HandleConnectSucceed();
	void HandleConnectFailed();
	void HandleDisconnected();
	// ������Ϣ��
	void HandleMessage(void* memory, size_t memory_size);

private:
	void HandleMessageImpl(void* memory, size_t memory_size, bool& need_free);

public:
	ROUTE_ID GetTargetRouteId() const { return m_target_route_id; }

public:
	ROUTE_ID m_route_id;			// ����·��ID
	ROUTE_ID m_target_route_id;	// �Զ�·��ID

protected:
	RouteSystem* m_route_system;

public:
	// ����RPC
	void ClearRPC(const std::string& reason);

private:
	CarpSafeIDCreator<int> m_id_creator;
	std::map<int, RPCCallback> m_rpc_map;
};

} // ALittle

#endif // _ALITTLE_CONNECTENDPOINT_H_
