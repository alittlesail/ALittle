
#ifndef _ALITTLE_RTPTRANSFER_H_
#define _ALITTLE_RTPTRANSFER_H_

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "carp_udp_server.hpp"

class RtpSchedule;

class RtpTransfer;
typedef std::shared_ptr<RtpTransfer> RtpTransferPtr;
typedef std::weak_ptr<RtpTransfer> RtpTransferWeakPtr;

class RtpTransfer : public std::enable_shared_from_this<RtpTransfer>
{
public:
    RtpTransfer() {}
	~RtpTransfer() { Close(); }

public:
	// ��ʼ��
	// client_rtp_ip_list ��ʾҪʹ�õ�ip�����ںͿͻ��˻���ý�����
	//						��Ϊ�ͻ��˵���������ǲ�ͬ��Ӫ�̣���Ӫ��֮ǰ�ụ���������ݰ�
	//						����������Կ������ͬ����Ӫ��ip�������ݿͻ��˲�ͬ������
	// remote_rtp_ip ��ʾҪʹ�õ�ip�����ں���·������RTP��
	// inner_rtp_ip ��ʾҪʹ�õ�ip�������ڲ�rtp������ת��ý���������ת�ӵĳ���
	bool Create(RtpSchedule* schedule
		, const std::vector<std::string>& client_rtp_ip_list, unsigned int client_rtp_port
		, const std::string& remote_rtp_ip, unsigned int remote_rtp_port
		, const std::string& inner_rtp_ip, unsigned int inner_rtp_port);

	// ����һ���绰ý���
	bool Start(const std::string& call_id, unsigned int client_id, unsigned int ssrc);

	// ֹͣһ���绰ý���
	void Stop();

	// �����ڲ�ת��ý�����ip�Ͷ˿ڣ��Լ���������
	void SetInnerRtp(const std::string& rtp_ip, unsigned int rtp_port);
	// ���ú���·������RTP����ip�Ͷ˿�
	void SetRemoteRtp(const std::string& rtp_ip, unsigned int rtp_port);

	bool ChangeClient(unsigned int client_id);
	void Close();

public:
	void UpdateIdleTime();
	time_t GetIdleTime() const { return m_idle_time; }

private:
	// ����ʱ��
	time_t m_idle_time = 0;
	// �Ƿ���ʹ����
	bool m_in_using = false;

private:
	// ����������ͻ��˻�����udp
	std::map<std::string, CarpUdpServerPtr> m_udp_client_rtp_map;
	// ʵ������ʹ�õ�udp������
	CarpUdpServerPtr m_udp_client_rtp;
	unsigned int m_client_rtp_port = 0;
	bool m_has_client_rtp_endpoint = false;	// client talk
	asio::ip::udp::endpoint m_client_rtp_endpoint;

	// ����·������rtp��udp
	CarpUdpServerPtr m_udp_remote_rtp;
	std::string m_remote_rtp_ip;
	unsigned int m_remote_rtp_port = 0;
	bool m_has_remote_rtp_endpoint = false;	// phone system talk
	asio::ip::udp::endpoint m_remote_rtp_endpoint;

	// �ڲ�ת����udp
	CarpUdpServerPtr m_udp_inner_rtp;
	unsigned int m_inner_rtp_port = 0;
	bool m_has_inner_rtp_endpoint = false; // inner rtp
	asio::ip::udp::endpoint m_inner_rtp_endpoint;

	// ����·��ʶ��ý��������к�
	unsigned int m_ssrc = 0;
	// ��ͻ���ʶ��ý��������к�
	unsigned int m_client_id = 0;

private:
	std::string m_call_id;		// SIP����ID
	time_t m_last_receive_time = 0;	// ����յ��ͻ������ݰ���ʱ��

private:
	static void HandleRemoteRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self);
	static void HandleClientRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self, CarpUdpServerWeakPtr real_udp);
	static void HandleInnerRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self);
};

#endif
