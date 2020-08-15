
#include "SessionConnection.h"
#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include "RouteMessage.h"
#include "ConnectEndpoint.h"

namespace ALittle
{

SessionConnection::~SessionConnection()
{
}

bool SessionConnection::Send(const Message& msg)
{
	// 如果本节点不是起始点或者终点，那么就没有权利发送数据包
	if (m_connect_index > 0 && m_connect_index + 1 < (int)m_vector_route_path.size())
	{
		ALITTLE_ERROR(u8"本节点不是这个会话连接的端点，不能发送数据包 " << GetConnectKey());
		return false;
	}

	// 找到对应的连接点
	ConnectEndpointPtr target_endpoint = m_pre_endpoint.lock();
	if (!target_endpoint) target_endpoint = m_next_endpoint.lock();
	if (!target_endpoint)
	{
		ALITTLE_ERROR(u8"pre_endpoint和next_endpoint都是空指针，不能发送数据包 " << CONNECT2S(GetConnectKey()));
		return false;
	}

	// 发送数据包
	ConnectRouteMessageWrite wrap_msg;
	wrap_msg.connect_key = GetConnectKey();
	wrap_msg.message_id = msg.GetID();
	wrap_msg.message_rpcid = msg.GetRpcID();
	wrap_msg.message_body = (Message*)&msg;
	target_endpoint->Send(wrap_msg);

	return true;
}

bool SessionConnection::Close()
{
	// 如果不是处于连接状态的，不能关闭连接
	if (m_status != SessionConnection::Status::SCS_CONNECTED)
		return false;

	// 如果不是路径起点或者终点，那么没有权利关闭连接
	if (m_connect_index > 0 && m_connect_index + 1 < (int)m_vector_route_path.size())
		return false;
	
	// 把当前状态标记为
	m_status = SessionConnection::Status::SCS_IDLE;

	// 向前面和后面的节点通知断开连接的数据包
	ConnectRouteDisconnected msg;
	msg.connect_key = m_connect_key;
	ConnectEndpointPtr pre_endpoint = m_pre_endpoint.lock();
	if (pre_endpoint && pre_endpoint->IsConnected()) pre_endpoint->Send(msg);
	pre_endpoint = ConnectEndpointPtr();
	ConnectEndpointPtr next_endpoint = m_next_endpoint.lock();
	if (next_endpoint && next_endpoint->IsConnected()) next_endpoint->Send(msg);
	next_endpoint = ConnectEndpointPtr();
	return true;
}

} // ALittle
