
#ifndef _ALITTLE_RTPTRANSFER_H_
#define _ALITTLE_RTPTRANSFER_H_

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "carp_udp_server.hpp"

typedef unsigned int CARP_RTP_CLIENT_ID;
typedef unsigned char CARP_RTP_CMD_TYPE;
typedef unsigned char CARP_RTP_PAYLOAD_TYPE;
typedef unsigned short CARP_RTP_SEQUENCE_NUMBER;
typedef unsigned int CARP_RTP_TIMESTAMP;

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
	// 初始化
	// client_rtp_ip_list 表示要使用的ip，用于和客户端互发媒体包。
	//						因为客户端的网络可能是不同运营商，运营商之前会互相拦截数据包
	//						所以这里可以开多个不同的运营商ip，来兼容客户端不同的网络
	// self_rtp_ip 表示要使用的ip，用于和线路方互发RTP包
	// inner_rtp_ip 表示要使用的ip，用于内部rtp服务器转发媒体包，用于转接的场景
	bool Create(RtpSchedule* schedule
		, const std::vector<std::string>& client_rtp_ip_list, unsigned int client_rtp_port
		, const std::string& self_rtp_ip, unsigned int self_rtp_port
		, const std::string& inner_rtp_ip, unsigned int inner_rtp_port);

	// 启动一个电话媒体包
	bool Start(const std::string& call_id, unsigned int client_id, unsigned int ssrc);

	// 停止一个电话媒体包
	void Stop();

	// 设置内部转发媒体包的ip和端口，以及语音编码
	void SetInnerRtp(const std::string& rtp_ip, unsigned int rtp_port);
	// 设置和线路方互发RTP包的ip和端口
	void SetRemoteRtp(const std::string& rtp_ip, unsigned int rtp_port);

	// 转移到客户端
	bool ChangeClient(unsigned int client_id);

	// 关闭rtp
	void Close();

public:
	time_t GetIdleTime() const { return m_idle_time; }

private:
	// 空闲时间
	time_t m_idle_time = 0;
	// 是否在使用中
	bool m_in_using = false;

private:
	// 所有用于与客户端互发的udp
	std::map<std::string, CarpUdpServerPtr> m_udp_client_rtp_map;
	// 实际正在使用的udp服务器
	CarpUdpServerPtr m_udp_client_rtp;
	unsigned int m_client_rtp_port = 0;
	bool m_has_client_rtp_endpoint = false;	// client talk
	asio::ip::udp::endpoint m_client_rtp_endpoint;

	// 与线路方互发rtp的udp
	CarpUdpServerPtr m_udp_self_rtp;
	std::string m_self_rtp_ip;
	unsigned int m_self_rtp_port = 0;
	bool m_has_remote_rtp_endpoint = false;	// phone system talk
	asio::ip::udp::endpoint m_remote_rtp_endpoint;

	// 内部转发的udp
	CarpUdpServerPtr m_udp_inner_rtp;
	unsigned int m_inner_rtp_port = 0;
	bool m_has_inner_rtp_endpoint = false; // inner rtp
	asio::ip::udp::endpoint m_inner_rtp_endpoint;

	// 与线路方识别媒体包的序列号
	unsigned int m_ssrc = 0;
	// 与客户端识别媒体包的序列号
	CARP_RTP_CLIENT_ID m_client_id = 0;

private:
	std::string m_call_id;		// SIP呼叫ID
	time_t m_last_receive_time = 0;	// 最后收到客户端数据包的时间
	std::vector<unsigned char> m_rtp_buffer; // 用于发送rtp的缓冲区

private:
	// rtp数据包处理
	static void HandleRemoteRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self);
	static void HandleClientRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self, CarpUdpServerWeakPtr real_udp);
	static void HandleInnerRtp(CarpUdpServer::HandleInfo& info, RtpTransferWeakPtr self);
};

#endif
