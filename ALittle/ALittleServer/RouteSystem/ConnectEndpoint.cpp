
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
	CARP_INFO(u8"ConnectEndpoint ����������ClearRPC");
#endif // CONNECT_INVOKE_LOG
	ClearRPC("route_id:" + ROUTE2S(m_route_id) + u8" ConnectEndpoint:~ConnectEndpoint ��������������ʱ�򴥷�ClearRPC");
}

void ConnectEndpoint::SendWithCallback(const CarpMessage& msg, RPCCallback& callback)
{
	// ����Ѿ��Ͽ����ӣ���ô��ֱ�ӵ��÷���ֵ
	if (IsConnected() == false)
	{
		if (callback)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + "<->" + "target_route_id:" + ROUTE2S(m_target_route_id) + u8" �����Ѿ��Ͽ��ˣ�SendWithCallback����ʧ��";
			callback(&reason, 0, 0, 0);
		}
		return;
	}

	// ����һ������RPC ID
	int rpc_id = m_id_creator.CreateID();
	m_rpc_map[rpc_id] = callback;
	
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint SendWithCallback ��:" << ROUTE2S(m_target_route_id) << " rpc_id:" << rpc_id);
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
	CARP_INFO(u8"ConnectEndpoint SendError ��:" << ROUTE2S(m_target_route_id) << ", rpc_id:" << rpc_id << ", reason:" << reason);
#endif // CONNECT_INVOKE_LOG

	RpcErrorMessage wrap_msg;
	wrap_msg.SetRpcID(-rpc_id);
	wrap_msg.reason = reason;
	Send(wrap_msg);
}

void ConnectEndpoint::SendResponse(int rpc_id, const CarpMessage& msg)
{
#ifdef CONNECT_INVOKE_LOG
	CARP_INFO(u8"ConnectEndpoint SendResponse ��:" << ROUTE2S(m_target_route_id) << ", rpc_id:" << rpc_id << ", message_id:" << msg.GetID());
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
	CARP_INFO(u8"ConnectEndpoint HandleDisconnected��ClearRPC");
#endif // CONNECT_INVOKE_LOG

	// �������еĵ���
	ClearRPC("route_id:" + ROUTE2S(m_route_id) + u8":ConnectEndpoint:HandleDisconnected �Ͽ����ӣ�����ClearRPC");

	// ֪ͨroute_system�Ƴ��Լ�
	m_route_system->RemoveConnectEndpoint(this->shared_from_this());
}

void ConnectEndpoint::ClearRPC(const std::string& reason)
{
	// �������лص���һ��һ��ִ��
	std::list<RPCCallback> callback_list;
	for (auto it = m_rpc_map.begin(); it != m_rpc_map.end(); ++it)
	{
		if (it->second)	callback_list.push_back(it->second);
		m_id_creator.ReleaseID(it->first);
	}
	// ����ӳ���
	m_rpc_map.clear();

	// �ѻص�ȫ��ִ������
	for (auto it = callback_list.begin(); it != callback_list.end(); ++it)
		(*it)(&reason, 0, 0, 0);
}

void ConnectEndpoint::HandleMessage(void* memory, size_t memory_size)
{
	// �����HandleMessageImpl�����ֵ�������ж��Ƿ���Ҫ�ͷ��ڴ�
	bool need_free = true;
	// ����ʵ�ʴ�����
	HandleMessageImpl(memory, memory_size, need_free);
	// �����Ҫ�ͷ��ڴ棬��ô��free
	if (need_free) free(memory);
}

void ConnectEndpoint::HandleMessageImpl(void* memory, size_t memory_size, bool& need_free)
{
	char* body_memory = (char*)memory;

	// ��ȡЭ���С��Э��ID
	CARP_MESSAGE_SIZE message_size = 0;
	memcpy(&message_size, body_memory, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	CARP_MESSAGE_ID message_id = 0;
	memcpy(&message_id, body_memory, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	CARP_MESSAGE_RPCID message_rpcid = 0;
	memcpy(&message_rpcid, body_memory, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);
	
	// ��������ֱ������
	if (message_id == HeartbeatMessage::GetStaticID())
		return;
		
	// ����Է�ע������
	if (message_id == QConnectRegister::GetStaticID())
	{
		// ���������
		AConnectRegister response_msg;
		response_msg.route_id = m_route_id;

		QConnectRegister msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			response_msg.error = static_cast<int>(ConnectRegisterError::QCONNECTREGISTER_DESERIALIZE_FAILED);
			response_msg.reason = u8"QConnectRegister Deserialize ʧ��!";
			Send(response_msg);
			Close(response_msg.reason, 5);
			return;
		}

		// ����Ѿ��յ����ˣ���ô��ֱ��Ӧ��
		if (m_target_route_id != 0)
		{
			response_msg.error = static_cast<int>(ConnectRegisterError::REGISTER_REPEATED);
			std::string reason = u8"��ǰ��ע����:" + RouteIdDefine::CalcRouteName(m_target_route_id) + u8", �����ظ�ע��:" + RouteIdDefine::CalcRouteName(msg.route_id);
			Send(response_msg);
			Close(response_msg.reason, 5);
			return;
		}

		// ��鷢������·��ID
		if (msg.route_id == 0)
		{
			response_msg.error = static_cast<int>(ConnectRegisterError::ROUTE_ID_MUST_NOT_BE_ZERO);
			response_msg.reason = u8"��������route_id������0";
			Send(response_msg);
			Close(response_msg.reason, 5);
			return;
		}

		// ��������
		if (!m_route_system->AddConnectEndpoint(this->shared_from_this(), msg.route_id))
		{
			response_msg.error = static_cast<int>(ConnectRegisterError::ROUTE_ID_ALREADY_EXIST);
			response_msg.reason = RouteIdDefine::CalcRouteName(msg.route_id) + u8"�Ѵ���";
			Send(response_msg);
			Close(response_msg.reason, 5);
			return;
		}

		// ���ؽ��
		Send(response_msg);
		return;
	}
	
	// ����Է�ע��Ӧ��
	if (message_id == AConnectRegister::GetStaticID())
	{
		AConnectRegister msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			CARP_ERROR(u8"AConnectRegister Deserialize ʧ��!");
			Close(u8"AConnectRegister Deserialize ʧ��!");
			return;
		}

		// ���������Ϣ
		if (msg.error != static_cast<int>(ConnectRegisterError::SUCCEED))
		{
			// ��ӡ����
			std::string reason = u8"ע��ʧ��:" + msg.reason + u8", ���������ر����ӣ�ֹͣ�������ƣ�����������֮���ٴη������ӡ�";
			CARP_ERROR(reason);
			// ��Ϊ��Щ������������ֹ�ҷ��ٴγ���ȥ���ӣ���������ֹͣ
			Close(reason);
			return;
		}

		// ����Ѿ��յ����ˣ���ô��ֱ�ӷ��سɹ�
		if (m_target_route_id != 0)
		{
			std::string reason = u8"��ǰ��ע����:" + RouteIdDefine::CalcRouteName(m_target_route_id) + u8", �����ظ�ע��:" + RouteIdDefine::CalcRouteName(msg.route_id);
			CARP_ERROR(reason);
			Close(reason);
			return;
		}

		// ����Ƿ������ڵ�������
		if (!m_route_system->AddConnectEndpoint(this->shared_from_this(), msg.route_id))
		{
			std::string reason = RouteIdDefine::CalcRouteName(msg.route_id) + u8"�Ѵ���";
			CARP_ERROR(reason);
			Close(reason);
			return;
		}
		return;
	}

	// �ɿ��Ե���
	if (message_id == QConnect2ConnectRPCRead::GetStaticID())
	{
		// ���m_target_route_id��û��ֵ����˵��ע�����̻�û��ͨ
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id��0�����Բ�ִ��QConnect2ConnectRPC����!");
			Close(u8"m_target_route_id��0�����Բ�ִ��QConnect2ConnectRPC����!");
			return;
		}

		// ����RPC�����
		QConnect2ConnectRPCRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"QConnect2ConnectRPC Deserialize ʧ��!");
			Close(u8"QConnect2ConnectRPC Deserialize ʧ��!");
			return;
		}

#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"�յ�QConnect2ConnectRPC����:" << m_target_route_id << ", rpc_id:" << message_rpcid);
#endif // CONNECT_INVOKE_LOG

		// ��Я����Э�齻��route_system����
		m_route_system->HandleQConnect2ConnectRPC(this->shared_from_this(), message_rpcid
			, msg.message_id, body_memory + deser_size, message_size - deser_size);
		return;
	}

	if (message_id == RpcErrorMessage::GetStaticID())
	{
#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"�յ�AConnect2ConnectRPC���� route_id:" << ROUTE2S(m_target_route_id));
#endif // CONNECT_INVOKE_LOG

		// ���m_target_route_id��û��ֵ����˵��ע�����̻�û��ͨ
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id��0�����Բ�ִ��AConnect2ConnectRPC����!");
			Close(u8"m_target_route_id��0�����Բ�ִ��AConnect2ConnectRPC����!");
			return;
		}

		RpcErrorMessage msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"AConnect2ConnectRPC Deserialize ʧ��!");
			Close(u8"AConnect2ConnectRPC Deserialize ʧ��!");
			return;
		}
		int rpc_id = -message_rpcid;

		// ���һص�����
		auto rpc_it = m_rpc_map.find(rpc_id);
		if (rpc_it != m_rpc_map.end())
		{
			// ȡ���ص�����
			RPCCallback callback = rpc_it->second;
			// ����ID
			m_id_creator.ReleaseID(rpc_it->first);
			// ɾ������
			m_rpc_map.erase(rpc_it);
			// �����ûص�����������ص������ڲ���Ӳ�����m_rpc_map����ʹ��rpc_it������ʧЧ
			if (callback) callback(&msg.reason, 0, 0, 0);
		}
		else
		{
			CARP_ERROR(u8"Ϊʲôû���ҵ���Ӧ��rpc�ص�����ܿ϶�������! rpc_id:" << rpc_id);
		}
		return;
	}
	
	// ����ɿ���Ӧ��
	if (message_id == AConnect2ConnectRPCRead::GetStaticID())
	{
#ifdef CONNECT_INVOKE_LOG
		CARP_INFO(u8"�յ�AConnect2ConnectRPC���� route_id:" << ROUTE2S(m_target_route_id));
#endif // CONNECT_INVOKE_LOG

		// ���m_target_route_id��û��ֵ����˵��ע�����̻�û��ͨ
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id ��0�����Բ�ִ��AConnect2ConnectRPC����!");
			Close(u8"m_target_route_id ��0�����Բ�ִ��AConnect2ConnectRPC����!");
			return;
		}

		AConnect2ConnectRPCRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"AConnect2ConnectRPC Deserialize ʧ��!");
			Close(u8"AConnect2ConnectRPC Deserialize ʧ��!");
			return;
		}
		int rpc_id = -message_rpcid;

		// ���һص�����
		auto rpc_it = m_rpc_map.find(rpc_id);
		if (rpc_it != m_rpc_map.end())
		{
			// ȡ���ص�����
			RPCCallback callback = rpc_it->second;
			// ����ID
			m_id_creator.ReleaseID(rpc_it->first);
			// ɾ������
			m_rpc_map.erase(rpc_it);
			// �����ûص�����������ص������ڲ���Ӳ�����m_rpc_map����ʹ��rpc_it������ʧЧ
			if (callback) callback(nullptr, msg.message_id, body_memory + deser_size, message_size - deser_size);
		}
		else
		{
			CARP_ERROR(u8"Ϊʲôû���ҵ���Ӧ��rpc�ص�����ܿ϶�������! rpc_id:" << rpc_id);
		}
		return;
	}
	
	// �Ự���ӶϿ�
	if (message_id == ConnectRouteDisconnected::GetStaticID())
	{
		// ���m_target_route_id��û��ֵ����˵��ע�����̻�û��ͨ
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id ��0�����Բ�ִ��ConnectRouteDisconnected����!");
			Close(u8"m_target_route_id ��0�����Բ�ִ��ConnectRouteDisconnected����!");
			return;
		}

		ConnectRouteDisconnected msg;
		if (msg.Deserialize(body_memory, message_size) < 0)
		{
			CARP_ERROR(u8"ConnectRouteDisconnected Deserialize ʧ��!");
			Close(u8"ConnectRouteDisconnected Deserialize ʧ��!");
			return;
		}

		// �ѻỰ���ӶϿ��Ĳ�������route_system����
		m_route_system->HandleConnectRouteDisconnected(this->shared_from_this(), msg);
		return;
	}

	// �ӻỰ��·�������ĵ������ݰ�
	if (message_id == ConnectRouteMessageRead::GetStaticID())
	{
		// ���m_target_route_id��û��ֵ����˵��ע�����̻�û��ͨ
		if (m_target_route_id == 0)
		{
			CARP_ERROR(u8"m_target_route_id ��0�����Բ�ִ��ConnectRouteMessage����!");
			Close(u8"m_target_route_id ��0�����Բ�ִ��ConnectRouteMessage����!");
			return;
		}

        ConnectRouteMessageRead msg;
		int deser_size = msg.Deserialize(body_memory, message_size);
		if (deser_size < 0)
		{
			CARP_ERROR(u8"ConnectRouteMessage Deserialize ʧ��!");
			Close(u8"ConnectRouteMessage Deserialize ʧ��!");
			return;
		}

		// ��Я����Э�齻��route_system����
		m_route_system->HandleConnectRouteMessage(this->shared_from_this(), msg.connect_key, message_rpcid
													, msg.message_id, msg.message_rpcid, body_memory + deser_size, message_size - deser_size
													, memory, (int)memory_size, need_free);
		return;
	}

	// ��ӡһ��δ֪Э��ID
	CARP_ERROR("unknow message id:" + std::to_string(message_id));
	Close("unknow message id:" + std::to_string(message_id));
}

} // ALittle
