
#include "RtpTransfer.h"
#include "RtpSchedule.h"

#include "carp_log.hpp"
extern "C" {
#include "rtp-packet.h"
#include "rtp-internal.h"
}

bool RtpTransfer::Create(RtpSchedule* schedule
	, const std::vector<std::string>& client_rtp_ip_list, unsigned client_rtp_port
	, const std::string& self_rtp_ip, unsigned self_rtp_port
	, const std::string& inner_rtp_ip, unsigned inner_rtp_port)
{
	// ��ȡ������
    RtpTransferWeakPtr self_weak_ptr = this->shared_from_this();

	// ����Ѿ������ˣ���ô��ֱ�ӷ���true
	if (m_udp_self_rtp)
	{
		for (const auto& ip : client_rtp_ip_list)
		{
			auto it = m_udp_client_rtp_map.find(ip);
			if (it == m_udp_client_rtp_map.end())
				CARP_ERROR("can't find client ip:" << ip);
		}
		if (m_client_rtp_port != client_rtp_port)
			CARP_ERROR("error client port, m_client_rtp_port(" << m_client_rtp_port << ") != client_rtp_port(" << client_rtp_port << ")");
		return true;
	}

	// �����ͻ���rtp
	for (const auto& ip : client_rtp_ip_list)
	{
		auto it = m_udp_client_rtp_map.find(ip);
		if (it != m_udp_client_rtp_map.end()) continue;

		auto udp_server = std::make_shared<CarpUdpServer>(schedule->GetIOService());
		CarpUdpServerWeakPtr self_udp_ptr = udp_server;
		udp_server->RegisterUdpHandle(std::bind(HandleClientRtp, std::placeholders::_1, self_weak_ptr, self_udp_ptr));
		if (!udp_server->Start(ip, client_rtp_port))
		{
			Close();
			return false;
		}
		m_udp_client_rtp_map[ip] = udp_server;
	}

	// ������·rtp
	m_udp_self_rtp = std::make_shared<CarpUdpServer>(schedule->GetIOService());
	m_udp_self_rtp->RegisterUdpHandle(std::bind(HandleRemoteRtp, std::placeholders::_1, self_weak_ptr));
	if (!m_udp_self_rtp->Start(self_rtp_ip, self_rtp_port))
	{
		Close();
		return false;
	}

	// ����ת��rtp
	m_udp_inner_rtp = std::make_shared<CarpUdpServer>(schedule->GetIOService());
	m_udp_inner_rtp->RegisterUdpHandle(std::bind(HandleInnerRtp, std::placeholders::_1, self_weak_ptr));
	if (!m_udp_inner_rtp->Start(inner_rtp_ip, inner_rtp_port))
	{
		Close();
		return false;
	}

	// �����������
	m_udp_client_rtp = CarpUdpServerPtr();
	m_client_rtp_port = client_rtp_port;
	m_self_rtp_ip = self_rtp_ip;
	m_self_rtp_port = self_rtp_port;
	m_inner_rtp_port = inner_rtp_port;

	return true;
}

bool RtpTransfer::Start(const std::string& call_id, unsigned int client_id, unsigned int ssrc)
{
	// ��ӡ����ʹ�õľ���
	if (m_in_using) CARP_ERROR("m_call_id(" << m_call_id << "), m_client_rtp_port(" << m_client_rtp_port << "), already in used!");
	// ���û�д���ֱ�ӷ���false
	if (!m_udp_self_rtp) return false;
	// ���Ϊ����ʹ��
	m_in_using = true;

	// ��ӡ��־
	CARP_INFO("RtpTransfer Start: call_id:" << call_id
		<< ", client_rtp_port:" << m_client_rtp_port
		<< ", self_rtp_port:" << m_self_rtp_port);

	// ��ʼ���������
	m_udp_client_rtp = CarpUdpServerPtr();
	m_has_client_rtp_endpoint = false;
	m_has_remote_rtp_endpoint = false;
	m_has_inner_rtp_endpoint = false;
	m_ssrc = ssrc;
	m_client_id = client_id;
	m_call_id = call_id;
	return true;
}

void RtpTransfer::Stop()
{
	// ��ӡ��־
	CARP_INFO("RtpTransfer Stop: call_id:" << m_call_id
		<< ", client_rtp_port:" << m_client_rtp_port
		<< ", self_rtp_port:" << m_self_rtp_port);

	// ���Ϊ����ʹ��
	m_in_using = false;

	// ���¿���ʱ��
	m_idle_time = time(nullptr);
}

void RtpTransfer::SetInnerRtp(const std::string& rtp_ip, unsigned int rtp_port)
{
	CARP_INFO("===================Set Inner RTP======================");
	m_inner_rtp_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(rtp_ip), rtp_port);
	m_has_inner_rtp_endpoint = true;
}

bool RtpTransfer::ChangeClient(unsigned int client_id)
{
	if (!m_udp_self_rtp) return false;
	m_client_id = client_id;
	m_has_client_rtp_endpoint = false;
	m_udp_client_rtp = CarpUdpServerPtr();
	return true;
}

void RtpTransfer::SetRemoteRtp(const std::string& rtp_ip, unsigned int rtp_port)
{
	CARP_INFO("======Set Remote RTP======:(ip)" << rtp_ip << " (port)" << rtp_port << " " << m_call_id);
	m_remote_rtp_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(rtp_ip), rtp_port);
	m_has_remote_rtp_endpoint = true;
}

void RtpTransfer::Close()
{
	for (auto& pair : m_udp_client_rtp_map)
		pair.second->Close();
	m_udp_client_rtp_map.clear();
	if (m_udp_self_rtp) m_udp_self_rtp->Close();
	m_udp_self_rtp = CarpUdpServerPtr();
	if (m_udp_inner_rtp) m_udp_inner_rtp->Close();
	m_udp_inner_rtp = CarpUdpServerPtr();
}

void RtpTransfer::HandleRemoteRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self)
{
	// ��ȡTransfer
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// ����Ƿ�����ʹ��
	if (self_ptr->m_in_using == false) return;

	// ����Ƿ����úöԶ�
	if (self_ptr->m_has_remote_rtp_endpoint == false || self_ptr->m_remote_rtp_endpoint != info.end_point) return;

	// ת�����ڲ�
	if (self_ptr->m_has_inner_rtp_endpoint)
	{
		void* new_memory = malloc(info.memory_size);
		memcpy(new_memory, info.memory, info.memory_size);
		self_ptr->m_udp_inner_rtp->Send(new_memory, info.memory_size, self_ptr->m_inner_rtp_endpoint);
		return;
	}

	// ת�����ͻ���
	if (self_ptr->m_has_client_rtp_endpoint)
	{
		// ���
		rtp_packet_t pocket = {0};
		const auto ret = rtp_packet_deserialize(&pocket, info.memory, static_cast<int>(info.memory_size));
		if (ret != 0)
		{
			CARP_ERROR("rtp_packet_deserialize failed!");
			return;
		}

		CARP_RTP_CMD_TYPE cmd_type = 'd'; // rtp ý������
		CARP_RTP_PAYLOAD_TYPE payload_type = pocket.rtp.pt;
		CARP_RTP_SEQUENCE_NUMBER sequence_number = pocket.rtp.seq;
		CARP_RTP_TIMESTAMP timestamp = pocket.rtp.timestamp;

		// �����ͻ��˵�rtp����client_id,
		const size_t new_memory_size = sizeof(CARP_RTP_CLIENT_ID)
			+ sizeof(CARP_RTP_CMD_TYPE)
			+ sizeof(CARP_RTP_PAYLOAD_TYPE)
			+ sizeof(CARP_RTP_SEQUENCE_NUMBER)
			+ sizeof(CARP_RTP_TIMESTAMP)
			+ pocket.payloadlen;

		char* new_memory = static_cast<char*>(malloc(new_memory_size));
		char* body_memory = new_memory;
		memcpy(body_memory, &(self_ptr->m_client_id), sizeof(CARP_RTP_CLIENT_ID)); body_memory += sizeof(CARP_RTP_CLIENT_ID);
		memcpy(body_memory, &cmd_type, sizeof(CARP_RTP_CMD_TYPE)); body_memory += sizeof(CARP_RTP_CMD_TYPE);
		memcpy(body_memory, &payload_type, sizeof(CARP_RTP_PAYLOAD_TYPE)); body_memory += sizeof(CARP_RTP_PAYLOAD_TYPE);
		memcpy(body_memory, &sequence_number, sizeof(CARP_RTP_SEQUENCE_NUMBER)); body_memory += sizeof(CARP_RTP_SEQUENCE_NUMBER);
		memcpy(body_memory, &timestamp, sizeof(CARP_RTP_TIMESTAMP)); body_memory += sizeof(CARP_RTP_TIMESTAMP);
		memcpy(body_memory, pocket.payload, pocket.payloadlen);
		self_ptr->m_udp_client_rtp->Send(new_memory, new_memory_size, self_ptr->m_client_rtp_endpoint);
	}
}

void RtpTransfer::HandleClientRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self, CarpUdpServerWeakPtr real_udp)
{
	// ��ȡTransfer
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// ����Ƿ�����ʹ��
	if (self_ptr->m_in_using == false) return;

	// �������ݰ�
	const char* rtp_memory = info.memory;
	size_t check_len = info.memory_size;

	if (check_len < sizeof(CARP_RTP_CLIENT_ID))
	{
		CARP_ERROR("rtp package len error1:" << check_len);
		return;
	}
	CARP_RTP_CLIENT_ID client_id;
	memcpy(&client_id, rtp_memory, sizeof(client_id));
	rtp_memory += sizeof(client_id);
	check_len -= sizeof(client_id);

	if (check_len < sizeof(CARP_RTP_CMD_TYPE))
	{
		CARP_ERROR("rtp package len error2:" << check_len);
		return;
	}
	CARP_RTP_CMD_TYPE cmd_type = *rtp_memory;
	rtp_memory += sizeof(cmd_type);
	check_len -= sizeof(cmd_type);

	// ����rtpý���
	if (cmd_type == 'd')
	{
		// ���ÿͻ���
		if (self_ptr->m_has_client_rtp_endpoint == false && self_ptr->m_client_id == client_id)
		{
			self_ptr->m_client_rtp_endpoint = info.end_point;
			self_ptr->m_has_client_rtp_endpoint = true;
			self_ptr->m_udp_client_rtp = real_udp.lock();
			CARP_INFO("!!!!!!carp rtp!!!!!!:" << self_ptr->m_call_id);
		}

		// ���5�뷢��һ�����ݰ������ڷ������������յ��ͻ��˵����ݰ�
		// ��Ϊ�еĿͻ������ڵ�����ͷ����������粻��ͨ��������Ҫ��������
		time_t cur_time = time(nullptr);
		if (self_ptr->m_has_client_rtp_endpoint && cur_time - self_ptr->m_last_receive_time > 5)
		{
			self_ptr->m_last_receive_time = cur_time;

			const CARP_RTP_CMD_TYPE e_cmd_type = 'e'; // ������Ϣ

			// ���ͷ�����
			size_t memory_size = sizeof(CARP_RTP_CLIENT_ID) + sizeof(CARP_RTP_CMD_TYPE) + sizeof(CARP_RTP_TIMESTAMP);
			char* memory = static_cast<char*>(malloc(memory_size));
			char* new_memory = memory;
			memcpy(new_memory, &(self_ptr->m_client_id), sizeof(CARP_RTP_CLIENT_ID)); new_memory += sizeof(CARP_RTP_CLIENT_ID);
			memcpy(new_memory, &e_cmd_type, sizeof(e_cmd_type)); new_memory += sizeof(e_cmd_type);
			memcpy(new_memory, &cur_time, sizeof(cur_time)); new_memory += sizeof(cur_time);
			self_ptr->m_udp_client_rtp->Send(memory, memory_size, self_ptr->m_client_rtp_endpoint);
		}

		// ���û����·��ֱ�ӷ���
		if (self_ptr->m_has_remote_rtp_endpoint == false) return;

		// get payload type
		if (check_len < sizeof(CARP_RTP_PAYLOAD_TYPE))
		{
			CARP_ERROR("rtp package len error3:" << check_len);
			return;
		}
		CARP_RTP_PAYLOAD_TYPE payload_type = 0;
		memcpy(&payload_type, rtp_memory, sizeof(payload_type));
		rtp_memory += sizeof(payload_type);
		check_len -= sizeof(payload_type);

		// get sequence number
		if (check_len < sizeof(CARP_RTP_SEQUENCE_NUMBER))
		{
			CARP_ERROR("rtp package len error4:" << check_len);
			return;
		}
		CARP_RTP_SEQUENCE_NUMBER sequence_number = 0;
		memcpy(&sequence_number, rtp_memory, sizeof(sequence_number));
		rtp_memory += sizeof(sequence_number);
		check_len -= sizeof(sequence_number);

		// get timestamp
		if (check_len < sizeof(CARP_RTP_TIMESTAMP))
		{
			CARP_ERROR("rtp package len error5:" << check_len);
			return;
		}
		CARP_RTP_TIMESTAMP timestamp = 0;
		memcpy(&timestamp, rtp_memory, sizeof(timestamp));
		rtp_memory += sizeof(timestamp);
		check_len -= sizeof(timestamp);

		// last len
		if (check_len <= 0)
		{
			CARP_ERROR("rtp package len error6:" << check_len);
			return;
		}

		if (self_ptr->m_rtp_buffer.size() < RTP_FIXED_HEADER + check_len)
			self_ptr->m_rtp_buffer.resize(RTP_FIXED_HEADER + check_len, 0);

		rtp_packet_t pocket = { 0 };
		pocket.payload = rtp_memory;
		pocket.payloadlen = static_cast<int>(check_len);
		pocket.rtp.v = RTP_VERSION;
		pocket.rtp.pt = payload_type;
		pocket.rtp.seq = sequence_number;
		pocket.rtp.timestamp = timestamp;
		pocket.rtp.ssrc = self_ptr->m_ssrc;

		int pocket_size = 0;
		while (true)
		{
			pocket_size = rtp_packet_serialize(&pocket, self_ptr->m_rtp_buffer.data(), static_cast<int>(self_ptr->m_rtp_buffer.size()));
			if (pocket_size > 0) break;

			if (self_ptr->m_rtp_buffer.size() > self_ptr->m_udp_self_rtp->GetBufferSize())
			{
				CARP_ERROR("rtp_packet_serialize failed check_len:" << check_len);
				return;
			}

			self_ptr->m_rtp_buffer.resize(self_ptr->m_rtp_buffer.size() * 2, 0);
		}

		// ����
		void* new_memory = malloc(pocket_size);
		memcpy(new_memory, self_ptr->m_rtp_buffer.data(), pocket_size);
		self_ptr->m_udp_self_rtp->Send(new_memory, pocket_size, self_ptr->m_remote_rtp_endpoint);
	}
}

void RtpTransfer::HandleInnerRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self)
{
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// check used
	if (self_ptr->m_in_using == false) return;
	if (self_ptr->m_has_remote_rtp_endpoint == false) return;

	// ת������·
	void* new_memory = malloc(info.memory_size);
	memcpy(new_memory, info.memory, info.memory_size);
	self_ptr->m_udp_self_rtp->Send(new_memory, info.memory_size, self_ptr->m_remote_rtp_endpoint);
}
