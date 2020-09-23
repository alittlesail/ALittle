
#include "ConnectEndpoint.h"
#include "ConnectMessage.h"
#include "RouteMessage.h"
#include "RouteDefine.h"
#include "RouteSystem.h"

#include "Carp/carp_log.hpp"

#include <chrono>

namespace ALittle
{

ConnectEndpoint::ConnectEndpoint(RouteSystem* route_system) : m_route_id(0), m_target_route_id(0), m_route_system(route_system)
{
}

ConnectEndpoint::~ConnectEndpoint()
{
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint 析构函数，ClearRPC");
#endif // CONNECT_INVOKE_LOG
	ClearRPC("route_id:" + ROUTE2S(m_route_id) + u8" ConnectEndpoint:~ConnectEndpoint 调用析构函数的时候触发ClearRPC");
}

void ConnectEndpoint::SendWithCallback(const CarpMessage& msg, RPCCallback& callback)
{
	// 如果已经断开连接，那么就直接调用返回值
	if (IsConnected() == false)
	{
		if (callback)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + "<->" + "target_route_id:" + ROUTE2S(m_target_route_id) + u8" 连接已经断开了，SendWithCallback调用失败";
			callback(&reason, 0, 0, 0);
		}
		return;
	}

	// 创建一个调用RPC ID
	int rpc_id = m_id_creator.CreateID();
	m_rpc_map[rpc_id] = callback;
	
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint SendWithCallback 向:" << ROUTE2S(m_target_route_id) << " rpc_id:" << rpc_id);
#endif // CONNECT_INVOKE_LOG

	QConnect2ConnectRPCWrite wrap_msg;
	wrap_msg.SetRpcID(rpc_id);
	wrap_msg.message_id = msg.GetID();
	wrap_msg.message_body = (CarpMessage*)&msg;
	Send(wrap_msg);
}

void ConnectEndpoint::SendError(int rpc_id, const std::string& reason)
{
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint SendError 向:" << ROUTE2S(m_target_route_id) << ", rpc_id:" << rpc_id << ", reason:" << reason);
#endif // CONNECT_INVOKE_LOG

	RpcErrorMessage wrap_msg;
	wrap_msg.SetRpcID(-rpc_id);
	wrap_msg.reason = reason;
	Send(wrap_msg);
}

void ConnectEndpoint::SendResponse(int rpc_id, const CarpMessage& msg)
{
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint SendResponse 向:" << ROUTE2S(m_target_route_id) << ", rpc_id:" << rpc_id << ", message_id:" << msg.GetID());
#endif // CONNECT_INVOKE_LOG

	AConnect2ConnectRPCWrite wrap_msg;
	wrap_msg.SetRpcID(-rpc_id);
	wrap_msg.message_id = msg.GetID();
	wrap_msg.message_body = (CarpMessage*)&msg;
	Send(wrap_msg);
}

void ConnectEndpoint::HandleConnectSucceed()
{
}

void ConnectEndpoint::HandleConnectFailed()
{
}

void ConnectEndpoint::HandleDisconnected()
{
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint HandleDisconnected，ClearRPC");
#endif // CONNECT_INVOKE_LOG

	// 清理所有的调用
	ClearRPC("route_id:" + ROUTE2S(m_route_id) + u8":ConnectEndpoint:HandleDisconnected 断开连接，触发ClearRPC");

	// 通知route_system移除自己
	m_route_system->RemoveConnectEndpoint(this->shared_from_this());
}

void ConnectEndpoint::ClearRPC(const std::string& reason)
{
	// 遍历所有回调，一个一个执行
	std::list<RPCCallback> callback_list;
	for (auto it = m_rpc_map.begin(); it != m_rpc_map.end(); ++it)
	{
		if (it->second)	callback_list.push_back(it->second);
		m_id_creator.ReleaseID(it->first);
	}
	// 清理映射表
	m_rpc_map.clear();

	// 把回调全部执行以下
	for (auto it = callback_list.begin(); it != callback_list.end(); ++it)
		(*it)(&reason, 0, 0, 0);
}

void ConnectEndpoint::HandleMessage(void* memory, size_t memory_size)
{
	// 这个是HandleMessageImpl的输出值，用来判断是否需要释放内存
	bool need_free = true;
	// 调用实际处理函数
	HandleMessageImpl(memory, memory_size, need_free);
	// 如果需要释放内存，那么就free
	if (need_free) free(memory);
}

void ConnectEndpoint::HandleMessageImpl(void* memory, size_t memory_size, bool& need_free)
{
	char* body_memory = (char*)memory;

	// 读取协议大小和协议ID
	CARP_MESSAGE_SIZE message_size = 0;
	memcpy(&message_size, body_memory, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	CARP_MESSAGE_ID message_id = 0;
	memcpy(&message_id, body_memory, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	CARP_MESSAGE_RPCID message_rpcid = 0;
	memcpy(&message_rpcid, body_memory, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);
	
	// 心跳包，直接跳过
	if (message_id == HeartbeatMessage::GetStaticID())
		return;
		
	// 处理对方注册请求
	if (message_id == QConnectRegister::GetStaticID())
	{
		QConnectRegister msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			CARP_ERROR(u8"QConnectRegister Deserialize 失败!");
			Close(u8"QConnectRegister Deserialize 失败!");
			return;
		}

		// 如果已经收到过了，那么就直接应答
		if (m_target_route_id != 0)
		{
			CARP_ERROR(u8"不能重复注册");
			Close(u8"不能重复注册");
			return;
		}

		// 检查发过来的路由ID
		if (msg.route_id == 0)
		{
			CARP_ERROR(u8"发过来的route_id不能是0");
			Close(u8"发过来的route_id不能是0");
			return;
		}

		// 尝试锁定
		if (!m_route_system->AddConnectEndpoint(this->shared_from_this(), msg.route_id))
		{
			CARP_ERROR(std::to_string(msg.route_id) + u8"已存在");
			Close(std::to_string(msg.route_id) + u8"已存在");
			return;
		}

		// 返回成功包
		AConnectRegister response_msg;
		response_msg.route_id = m_route_id;
		Send(response_msg);
		return;
	}
	
	// 处理对方注册应答
	if (message_id == AConnectRegister::GetStaticID())
	{
		AConnectRegister msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			CARP_ERROR(u8"AConnectRegister Deserialize 失败!");
			Close(u8"AConnectRegister Deserialize 失败!");
			return;
		}

		// 如果已经收到过了，那么就直接返回成功
		if (m_target_route_id != 0)
		{
			CARP_ERROR(u8"不能重复注册");
			Close(u8"不能重复注册");
			return;
		}

		// 检查是否被其他节点锁定了
		if (!m_route_system->AddConnectEndpoint(this->shared_from_this(), msg.route_id))
		{
			CARP_ERROR(std::to_string(msg.route_id) + u8"已存在");
			Close(std::to_string(msg.route_id) + u8"已存在");
			return;
		}
		return;
	}

	// 可靠性调用
	if (message_id == QConnect2ConnectRPCRead::GetStaticID())
	{
		// 如果m_target_route_id还没赋值，那说明注册流程还没走通
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id是0，所以不执行QConnect2ConnectRPC操作!");
			Close(u8"m_target_route_id是0，所以不执行QConnect2ConnectRPC操作!");
			return;
		}

		// 解析RPC请求包
		QConnect2ConnectRPCRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"QConnect2ConnectRPC Deserialize 失败!");
			Close(u8"QConnect2ConnectRPC Deserialize 失败!");
			return;
		}

#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"收到QConnect2ConnectRPC来自:" << m_target_route_id << ", rpc_id:" << message_rpcid);
#endif // CONNECT_INVOKE_LOG

		// 把携带的协议交给route_system处理
		m_route_system->HandleQConnect2ConnectRPC(this->shared_from_this(), message_rpcid
			, msg.message_id, body_memory + deser_size, message_size - deser_size);
		return;
	}

	if (message_id == RpcErrorMessage::GetStaticID())
	{
#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"收到AConnect2ConnectRPC来自 route_id:" << ROUTE2S(m_target_route_id));
#endif // CONNECT_INVOKE_LOG

		// 如果m_target_route_id还没赋值，那说明注册流程还没走通
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id是0，所以不执行AConnect2ConnectRPC操作!");
			Close(u8"m_target_route_id是0，所以不执行AConnect2ConnectRPC操作!");
			return;
		}

		RpcErrorMessage msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"AConnect2ConnectRPC Deserialize 失败!");
			Close(u8"AConnect2ConnectRPC Deserialize 失败!");
			return;
		}
		int rpc_id = -message_rpcid;

		// 查找回调函数
		auto rpc_it = m_rpc_map.find(rpc_id);
		if (rpc_it != m_rpc_map.end())
		{
			// 取出回调函数
			RPCCallback callback = rpc_it->second;
			// 回收ID
			m_id_creator.ReleaseID(rpc_it->first);
			// 删除对象
			m_rpc_map.erase(rpc_it);
			// 最后调用回调函数，避免回调函数内部间接操作了m_rpc_map，而使得rpc_it迭代器失效
			if (callback) callback(&msg.reason, 0, 0, 0);
		}
		else
		{
			CARP_ERROR(u8"为什么没有找到对应的rpc回调，框架肯定有问题! rpc_id:" << rpc_id);
		}
		return;
	}
	
	// 处理可靠性应答
	if (message_id == AConnect2ConnectRPCRead::GetStaticID())
	{
#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"收到AConnect2ConnectRPC来自 route_id:" << ROUTE2S(m_target_route_id));
#endif // CONNECT_INVOKE_LOG

		// 如果m_target_route_id还没赋值，那说明注册流程还没走通
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id 是0，所以不执行AConnect2ConnectRPC操作!");
			Close(u8"m_target_route_id 是0，所以不执行AConnect2ConnectRPC操作!");
			return;
		}

		AConnect2ConnectRPCRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"AConnect2ConnectRPC Deserialize 失败!");
			Close(u8"AConnect2ConnectRPC Deserialize 失败!");
			return;
		}
		int rpc_id = -message_rpcid;

		// 查找回调函数
		auto rpc_it = m_rpc_map.find(rpc_id);
		if (rpc_it != m_rpc_map.end())
		{
			// 取出回调函数
			RPCCallback callback = rpc_it->second;
			// 回收ID
			m_id_creator.ReleaseID(rpc_it->first);
			// 删除对象
			m_rpc_map.erase(rpc_it);
			// 最后调用回调函数，避免回调函数内部间接操作了m_rpc_map，而使得rpc_it迭代器失效
			if (callback) callback(nullptr, msg.message_id, body_memory + deser_size, message_size - deser_size);
		}
		else
		{
			CARP_ERROR(u8"为什么没有找到对应的rpc回调，框架肯定有问题! rpc_id:" << rpc_id);
		}
		return;
	}
	
	// 会话连接断开
	if (message_id == ConnectRouteDisconnected::GetStaticID())
	{
		// 如果m_target_route_id还没赋值，那说明注册流程还没走通
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id 是0，所以不执行ConnectRouteDisconnected操作!");
			Close(u8"m_target_route_id 是0，所以不执行ConnectRouteDisconnected操作!");
			return;
		}

		ConnectRouteDisconnected msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			CARP_ERROR(u8"ConnectRouteDisconnected Deserialize 失败!");
			Close(u8"ConnectRouteDisconnected Deserialize 失败!");
			return;
		}

		// 把会话连接断开的操作交给route_system处理
		m_route_system->HandleConnectRouteDisconnected(this->shared_from_this(), msg);
		return;
	}

	// 从会话链路发过来的单向数据包
	if (message_id == ConnectRouteMessageRead::GetStaticID())
	{
		// 如果m_target_route_id还没赋值，那说明注册流程还没走通
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id 是0，所以不执行ConnectRouteMessage操作!");
			Close(u8"m_target_route_id 是0，所以不执行ConnectRouteMessage操作!");
			return;
		}

        ConnectRouteMessageRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"ConnectRouteMessage Deserialize 失败!");
			Close(u8"ConnectRouteMessage Deserialize 失败!");
			return;
		}

		// 把携带的协议交给route_system处理
		m_route_system->HandleConnectRouteMessage(this->shared_from_this(), msg.connect_key, message_rpcid
													, msg.message_id, msg.message_rpcid, body_memory + deser_size, message_size - deser_size
													, memory, (int)memory_size, need_free);
		return;
	}

	// 打印一下未知协议ID
	CARP_ERROR("unknow message id:" + std::to_string(message_id));
	Close("unknow message id:" + std::to_string(message_id));
}

} // ALittle
