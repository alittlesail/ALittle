
#include "RtpTransfer.h"
#include "RtpSchedule.h"

#include "carp_log.hpp"

#include "pjmedia/rtp.h"

bool RtpTransfer::Create(RtpSchedule* schedule
	, const std::vector<std::string>& client_rtp_ip_list, unsigned client_rtp_port
	, const std::string& remote_rtp_ip, unsigned remote_rtp_port
	, const std::string& inner_rtp_ip, unsigned inner_rtp_port)
{
	// 获取弱引用
    RtpTransferWeakPtr self_weak_ptr = this->shared_from_this();

	// 如果已经创建了，那么就直接返回true
	if (m_udp_remote_rtp)
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

	// 创建客户端rtp
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

	// 创建线路rtp
	m_udp_remote_rtp = std::make_shared<CarpUdpServer>(schedule->GetIOService());
	m_udp_remote_rtp->RegisterUdpHandle(std::bind(HandleRemoteRtp, std::placeholders::_1, self_weak_ptr));
	if (!m_udp_remote_rtp->Start(remote_rtp_ip, remote_rtp_port))
	{
		Close();
		return false;
	}

	// 创建转发rtp
	m_udp_inner_rtp = std::make_shared<CarpUdpServer>(schedule->GetIOService());
	m_udp_inner_rtp->RegisterUdpHandle(std::bind(HandleInnerRtp, std::placeholders::_1, self_weak_ptr));
	if (!m_udp_inner_rtp->Start(inner_rtp_ip, inner_rtp_port))
	{
		Close();
		return false;
	}

	// 保存相关数据
	m_udp_client_rtp = CarpUdpServerPtr();
	m_client_rtp_port = client_rtp_port;
	m_remote_rtp_ip = remote_rtp_ip;
	m_remote_rtp_port = remote_rtp_port;
	m_inner_rtp_port = inner_rtp_port;

	return true;
}

bool RtpTransfer::Start(const std::string& call_id, unsigned int client_id, unsigned int ssrc)
{
	// 打印正在使用的警告
	if (m_in_using) CARP_ERROR("m_call_id(" << m_call_id << "), m_client_rtp_port(" << m_client_rtp_port << "), already in used!");
	// 如果没有创建直接返回false
	if (!m_udp_remote_rtp) return false;
	// 标记为正在使用
	m_in_using = true;

	// 打印日志
	CARP_INFO("RtpTransfer Start: call_id:" << call_id
		<< ", client_rtp_port:" << m_client_rtp_port
		<< ", remote_rtp_port:" << m_remote_rtp_port);

	// 初始化相关数据
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
	// 打印日志
	CARP_INFO("RtpTransfer Stop: call_id:" << m_call_id
		<< ", client_rtp_port:" << m_client_rtp_port
		<< ", remote_rtp_port:" << m_remote_rtp_port);

	// 标记为不在使用
	m_in_using = false;
}

void RtpTransfer::SetInnerRtp(const std::string& rtp_ip, unsigned int rtp_port)
{
	CARP_INFO("===================Set Inner RTP======================");
	m_inner_rtp_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(rtp_ip), rtp_port);
	m_has_inner_rtp_endpoint = true;
}

bool RtpTransfer::ChangeClient(unsigned int client_id)
{
	if (!m_udp_remote_rtp) return false;
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
	if (m_udp_remote_rtp) m_udp_remote_rtp->Close();
	m_udp_remote_rtp = CarpUdpServerPtr();
	if (m_udp_inner_rtp) m_udp_inner_rtp->Close();
	m_udp_inner_rtp = CarpUdpServerPtr();
}

void RtpTransfer::UpdateIdleTime()
{
	m_idle_time = time(0);
}

void RtpTransfer::HandleRemoteRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self)
{
	// 获取Transfer
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// 检查是否正在使用
	if (self_ptr->m_in_using == false) return;

	// 检查是否设置好对端
	if (self_ptr->m_has_remote_rtp_endpoint == false || self_ptr->m_remote_rtp_endpoint != info.end_point) return;

	// 转发给内部
	if (self_ptr->m_has_inner_rtp_endpoint)
	{
		void* new_memory = malloc(info.memory_size);
		memcpy(new_memory, info.memory, info.memory_size);
		self_ptr->m_udp_inner_rtp->Send(new_memory, info.memory_size, self_ptr->m_inner_rtp_endpoint);
		return;
	}

	// 转发给客户端
	if (self_ptr->m_has_client_rtp_endpoint)
	{
		// 解包
		const pjmedia_rtp_hdr* hdr = nullptr;
		const void* rtp_memory = nullptr;
		unsigned int last_len = 0;
		const auto ret = pjmedia_rtp_decode_rtp(nullptr, info.memory, info.memory_size, &hdr, &rtp_memory, &last_len);
		if (ret != PJ_SUCCESS)
		{
			CARP_ERROR("pjmedia_rtp_decode_rtp failed!");
			return;
		}

		// 获取数据，把大端转为小端
		unsigned char payload_type = hdr->pt;
		int sequence_number = pj_ntohs(hdr->seq);
		unsigned int timestamp = pj_ntohl(hdr->ts);

		// 创建客户端的rtp包
		const size_t new_memory_size = sizeof(unsigned int) + sizeof(char) + last_len + sizeof(char) + sizeof(int) + sizeof(int);
		char* new_memory = static_cast<char*>(malloc(new_memory_size));
		char* body_memory = new_memory;
		memcpy(body_memory, &(self_ptr->m_client_id), sizeof(unsigned int));
		body_memory += 4;
		*body_memory = 'd'; // rtp 媒体数据
		body_memory += 1;
		memcpy(body_memory, &payload_type, sizeof(char));
		body_memory += sizeof(char);
		memcpy(body_memory, &sequence_number, sizeof(int));
		body_memory += sizeof(int);
		memcpy(body_memory, &timestamp, sizeof(int));
		body_memory += sizeof(int);
		memcpy(body_memory, rtp_memory, last_len);
		self_ptr->m_udp_client_rtp->Send(new_memory, new_memory_size, self_ptr->m_client_rtp_endpoint);
	}
}

void RtpTransfer::HandleClientRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self, CarpUdpServerWeakPtr real_udp)
{
	// 获取Transfer
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// 检查是否正在使用
	if (self_ptr->m_in_using == false) return;

	// 解析数据包
	const char* rtp_memory = info.memory;
	size_t check_len = info.memory_size;

	if (check_len < sizeof(unsigned int))
	{
		CARP_ERROR("rtp package len error1:" << check_len);
		return;
	}
	unsigned int client_id;
	memcpy(&client_id, rtp_memory, sizeof(client_id));
	rtp_memory += sizeof(client_id);
	check_len -= sizeof(client_id);

	if (check_len < sizeof(unsigned char))
	{
		CARP_ERROR("rtp package len error2:" << check_len);
		return;
	}
	char data_type = *rtp_memory;
	rtp_memory += 1;
	check_len -= 1;

	// 处理rtp媒体包
	if (data_type == 'd')
	{
		// 设置客户端
		if (self_ptr->m_has_client_rtp_endpoint == false && self_ptr->m_client_id == client_id)
		{
			self_ptr->m_client_rtp_endpoint = info.end_point;
			self_ptr->m_has_client_rtp_endpoint = true;
			self_ptr->m_udp_client_rtp = real_udp.lock();
			CARP_INFO("!!!!!!carp rtp!!!!!!:" << self_ptr->m_call_id);
		}

		// 间隔5秒发送一次数据包，用于反馈服务器有收到客户端的数据包
		// 因为有的客户端所在的网络和服务器的网络不连通，所以需要这个来检查
		time_t cur_time = time(nullptr);
		if (self_ptr->m_has_client_rtp_endpoint && cur_time - self_ptr->m_last_receive_time > 5)
		{
			self_ptr->m_last_receive_time = cur_time;

			// 发送反馈包
			size_t memory_size = sizeof(unsigned int) + sizeof(unsigned char) + sizeof(unsigned int);
			char* memory = static_cast<char*>(malloc(memory_size));
			char* new_memory = memory;
			memcpy(new_memory, &(self_ptr->m_client_id), sizeof(unsigned int));
			new_memory += 4;
			*new_memory = 'e'; // 控制信息
			new_memory += 1;
			memcpy(new_memory, &cur_time, sizeof(cur_time));
			new_memory += sizeof(cur_time);
			self_ptr->m_udp_client_rtp->Send(memory, memory_size, self_ptr->m_client_rtp_endpoint);
		}

		// 如果没有线路，直接返回
		if (self_ptr->m_has_remote_rtp_endpoint == false) return;

		// get payload type
		if (check_len < sizeof(unsigned char))
		{
			CARP_ERROR("rtp package len error3:" << check_len);
			return;
		}
		unsigned char payload_type = 0;
		memcpy(&payload_type, rtp_memory, sizeof(payload_type));
		rtp_memory += sizeof(payload_type);
		check_len -= sizeof(payload_type);

		// get sequence number
		if (check_len < sizeof(unsigned int))
		{
			CARP_ERROR("rtp package len error4:" << check_len);
			return;
		}
		unsigned int sequence_number = 0;
		memcpy(&sequence_number, rtp_memory, sizeof(sequence_number));
		rtp_memory += sizeof(sequence_number);
		check_len -= sizeof(sequence_number);
		const unsigned short sequence = static_cast<unsigned short>(sequence_number);

		// get timestamp
		if (check_len < sizeof(unsigned int))
		{
			CARP_ERROR("rtp package len error5:" << check_len);
			return;
		}
		unsigned int timestamp = 0;
		memcpy(&timestamp, rtp_memory, sizeof(timestamp));
		rtp_memory += sizeof(timestamp);
		check_len -= sizeof(timestamp);

		// last len
		if (check_len <= 0)
		{
			CARP_ERROR("rtp package len error6:" << check_len);
			return;
		}

		pjmedia_rtp_hdr rtp_hdr;
		rtp_hdr.cc = 0;
		rtp_hdr.x = 0;
		rtp_hdr.p = 0;
		rtp_hdr.v = 2;
		rtp_hdr.pt = payload_type;
		rtp_hdr.m = 0;
		rtp_hdr.seq = pj_htons(sequence);
		rtp_hdr.ts = pj_htonl(timestamp);
		rtp_hdr.ssrc = pj_htonl(self_ptr->m_ssrc);
		const size_t hdr_len = sizeof(pjmedia_rtp_hdr);

		// 申请并复制内存
		size_t new_size = hdr_len + check_len;
		char* new_memory = static_cast<char*>(malloc(new_size));
		memcpy(new_memory, &rtp_hdr, hdr_len);
		memcpy(new_memory + hdr_len, rtp_memory, check_len);
		// 发送
		self_ptr->m_udp_remote_rtp->Send(new_memory, new_size, self_ptr->m_remote_rtp_endpoint);
	}
	else if (data_type == 't')
	{
		if (self_ptr->m_has_client_rtp_endpoint == false && self_ptr->m_client_id == client_id)
		{
			self_ptr->m_client_rtp_endpoint = info.end_point;
			self_ptr->m_has_client_rtp_endpoint = true;
			self_ptr->m_udp_client_rtp = real_udp.lock();
			CARP_INFO("!!!!!!!!!!!!!!!!!carp rtcp!!!!!!!!!!!!!!!!");
		}

		// get dtmf event
		if (check_len < sizeof(unsigned char))
		{
			CARP_ERROR("rtp package len error4:" << check_len);
			return;
		}
		unsigned char dtmf_event = 0;
		memcpy(&dtmf_event, rtp_memory, sizeof(dtmf_event));
		rtp_memory += sizeof(dtmf_event);
		check_len -= sizeof(dtmf_event);

		// get dtmf end
		if (check_len < sizeof(unsigned char))
		{
			CARP_ERROR("rtp package len error5:" << check_len);
			return;
		}
		unsigned char dtmf_end = 0;
		memcpy(&dtmf_end, rtp_memory, sizeof(dtmf_end));
		rtp_memory += sizeof(dtmf_end);
		check_len -= sizeof(dtmf_end);

		if (dtmf_end) dtmf_end = 0x8a;
		else dtmf_end = 0x0a;

		// get sequence_number
		if (check_len < sizeof(int))
		{
			CARP_ERROR("rtp package len error6:" << check_len);
			return;
		}
		unsigned int sequence_number = 0;
		memcpy(&sequence_number, rtp_memory, sizeof(sequence_number));
		rtp_memory += sizeof(sequence_number);
		check_len -= sizeof(sequence_number);
		const unsigned short sequence = static_cast<unsigned short>(sequence_number);

		// get timestamp
		if (check_len < sizeof(int))
		{
			CARP_ERROR("rtp package len error7:" << check_len);
			return;
		}
		unsigned int timestamp = 0;
		memcpy(&timestamp, rtp_memory, sizeof(timestamp));
		rtp_memory += sizeof(timestamp);
		check_len -= sizeof(timestamp);

		// get duration
		if (check_len < sizeof(unsigned short))
		{
			CARP_ERROR("rtp package len error8:" << check_len);
			return;
		}
		unsigned short duration = 0;
		memcpy(&duration, rtp_memory, sizeof(duration));
		rtp_memory += sizeof(duration);
		check_len -= sizeof(duration);

		// 填充dtmf数据
		unsigned char rtp_info[4];
		rtp_info[0] = dtmf_event;
		rtp_info[1] = dtmf_end;
		duration = pj_ntohs(duration);
		memcpy(rtp_info + 2, &duration, sizeof(duration));

		pjmedia_rtp_hdr rtp_hdr;
		rtp_hdr.cc = 0;
		rtp_hdr.x = 0;
		rtp_hdr.p = 0;
		rtp_hdr.v = 2;
		rtp_hdr.pt = 101;
		rtp_hdr.m = 0;
		rtp_hdr.seq = pj_htons(sequence);
		rtp_hdr.ts = pj_htonl(timestamp);
		rtp_hdr.ssrc = pj_htonl(self_ptr->m_ssrc);
		const size_t hdr_len = sizeof(pjmedia_rtp_hdr);

		// 申请并复制内存
		size_t new_size = hdr_len + sizeof(rtp_info);
		char* new_memory = static_cast<char*>(malloc(new_size));
		memcpy(new_memory, &rtp_hdr, hdr_len);
		memcpy(new_memory + hdr_len, rtp_info, sizeof(rtp_info));
		// 发送
		self_ptr->m_udp_remote_rtp->Send(new_memory, new_size, self_ptr->m_remote_rtp_endpoint);
	}
}

void RtpTransfer::HandleInnerRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self)
{
	RtpTransferPtr self_ptr = self.lock();
	if (!self_ptr) return;

	// check used
	if (self_ptr->m_in_using == false) return;
	if (self_ptr->m_has_remote_rtp_endpoint == false) return;

	// 转发给线路
	void* new_memory = malloc(info.memory_size);
	memcpy(new_memory, info.memory, info.memory_size);
	self_ptr->m_udp_remote_rtp->Send(new_memory, info.memory_size, self_ptr->m_remote_rtp_endpoint);
}
