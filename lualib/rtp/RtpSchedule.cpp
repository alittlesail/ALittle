
#include "RtpSchedule.h"

RtpSchedule::~RtpSchedule()
{
	for (auto& pair : m_use_map_rtp)
	{
		pair.second->Stop();
		m_release_map_rtp[pair.first] = pair.second;
	}
	m_use_map_rtp.clear();

	CARP_INFO("release count:" << m_release_map_rtp.size());
	CARP_INFO("use count:" << m_use_map_rtp.size());
}

void RtpSchedule::ReleaseRtp(int first_port)
{
	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->Stop();
	m_release_map_rtp[first_port] = use_it->second;
	m_use_map_rtp.erase(use_it);

	CARP_INFO("release count:" << m_release_map_rtp.size());
    CARP_INFO("use count:" << m_use_map_rtp.size());
}

void RtpSchedule::ReleaseAllRtp()
{
	for (auto& pair : m_use_map_rtp)
	{
		pair.second->Stop();
		m_release_map_rtp[pair.first] = pair.second;
	}
	m_use_map_rtp.clear();

	CARP_INFO("release count:" << m_release_map_rtp.size());
	CARP_INFO("use count:" << m_use_map_rtp.size());
}

void RtpSchedule::UseRtp(int first_port
                         , const std::vector<std::string>& client_rtp_ip_list, int client_rtp_port
                         , const std::string& self_rtp_ip, int self_rtp_port
                         , const std::string& inner_rtp_ip, int inner_rtp_port
                         , const std::string& remote_rtp_ip, int remote_rtp_port
                         , const std::string& call_id, int client_id, unsigned int ssrc)
{
	RtpTransferPtr rtp;
	const auto release_it = m_release_map_rtp.find(first_port);
	if (release_it != m_release_map_rtp.end())
	{
		rtp = release_it->second;
		m_release_map_rtp.erase(release_it);
	}
	else
	{
		rtp = std::make_shared<RtpTransfer>();
	}
	m_use_map_rtp[first_port] = rtp;

	// 创建rtp
	rtp->Create(this, client_rtp_ip_list, client_rtp_port
		, self_rtp_ip, self_rtp_port
		, inner_rtp_ip, inner_rtp_port);

	// 开始使用rtp
	rtp->Start(call_id, client_id, ssrc);

	// 如果线路的rtp已知道，那么就直接设置进去
	if (!remote_rtp_ip.empty()) rtp->SetRemoteRtp(remote_rtp_ip, remote_rtp_port);

	// 打印信息
	CARP_INFO("release count:" << m_release_map_rtp.size());
	CARP_INFO("use count:" << m_use_map_rtp.size());
}

void RtpSchedule::SetRemoteRtp(int first_port, const std::string& remote_rtp_ip, int remote_rtp_port)
{
	if (remote_rtp_ip.empty()) return;

	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->SetRemoteRtp(remote_rtp_ip, remote_rtp_port);
}

void RtpSchedule::SetInnerRtp(int first_port, const std::string& inner_rtp_ip, int inner_rtp_port)
{
	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->SetInnerRtp(inner_rtp_ip, inner_rtp_port);
}

void RtpSchedule::TransClient(int first_port, int client_id)
{
	auto use_it = m_use_map_rtp.find(first_port);
	if (use_it == m_use_map_rtp.end()) return;

	use_it->second->ChangeClient(client_id);
}

void RtpSchedule::ClearIdleRtp()
{
	const time_t cur_time = time(nullptr);

	bool has_close = false;
	for (auto release_it = m_release_map_rtp.begin(); release_it != m_release_map_rtp.end();)
	{
		if (cur_time - release_it->second->GetIdleTime() > 30)
		{
			release_it->second->Close();
			release_it = m_release_map_rtp.erase(release_it);

			has_close = true;
		}
		else
		{
			++release_it;
		}
	}

	if (has_close)
	{
		CARP_INFO("release count:" << m_release_map_rtp.size());
		CARP_INFO("use count:" << m_use_map_rtp.size());
	}
}
