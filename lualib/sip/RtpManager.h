
#ifndef _ALITTLE_RTPMANAGER_H_
#define _ALITTLE_RTPMANAGER_H_

#include <string>
#include <map>
#include <list>
#include <vector>

class SipSchedule;

class RtpManager
{
public:
	RtpManager(SipSchedule* schedule) : m_schedule(schedule) {}

public:
	void HandleRtpDisconnect(unsigned int route_id);
	void SetRtpResource(unsigned int route_id
		, const std::vector<std::string>& client_ip_list
		, const std::string& remote_ip
		, const std::string& inner_ip
	    , int min_port, int max_port);

public:
	unsigned int UseRtp(const std::string& call_id
				, unsigned int client_id
				, unsigned int ssrc
				, const std::string& target_remote_rtp_ip
				, int target_remote_rtp_port
				, std::vector<std::string>& client_rtp_ip_list
				, int& client_rtp_port
				, std::string& remote_rtp_ip
				, int& remote_rtp_port
				, int& remote_rtcp_port
				, std::string& inner_rtp_ip
				, int& inner_rtp_port);

	void ReleaseRtp(const std::string& call_id);

public:
	struct RtpInfo
	{
		std::vector<std::string> client_ip_list; // 提供给客户端的 RTP 的地址
		std::string remote_ip;			// 提供给线路的 RTP 的地址
		std::string inner_ip;			// 提供给内部转发的RTP 的地址

		std::map<std::string, int> call_id_map_port;	// CALLID映射表

		int cur_port = 0;					// 当前递增的ip
		std::list<int> idle_list;		// 当前空闲列表

		int total_count = 0;				// 端口总数
		int use_count = 0;					// 使用个数

		int min_port = 0;					// 最小端口
		int max_port = 0;					// 最大端口
	};
	std::map<unsigned int, RtpInfo> m_module_map_info;

private:
	SipSchedule* m_schedule = nullptr;
};

#endif
