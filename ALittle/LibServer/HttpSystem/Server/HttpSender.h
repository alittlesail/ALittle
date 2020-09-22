
#ifndef _ALITTLE_HTTPSENDER_H_
#define _ALITTLE_HTTPSENDER_H_

#include <memory>
#include <string>
#include <vector>

class CarpHttpSocket;
typedef std::shared_ptr<CarpHttpSocket> CarpHttpSocketPtr;

namespace ALittle
{

class HttpReceiver;
typedef std::shared_ptr<HttpReceiver> HttpReceiverPtr;
typedef std::weak_ptr<HttpReceiver> HttpReceiverWeakPtr;

class HttpSender;
typedef std::shared_ptr<HttpSender> HttpSenderPtr;
typedef std::weak_ptr<HttpSender> HttpSenderWeakPtr;

class HttpServer;
typedef std::shared_ptr<HttpServer> HttpServerPtr;
typedef std::weak_ptr<HttpServer> HttpServerWeakPtr;

class FileCacheHelper;
class ServerSchedule;

class HttpSender : public std::enable_shared_from_this<HttpSender>
{
public:
	friend HttpServer;

public:
	HttpSender(CarpHttpSocketPtr socket, HttpServerPtr server, ServerSchedule* schedule);
	~HttpSender();

public:
	/* send string message
	 * @param message: content to response
	 */
	void SendString(const std::string& message);

public:
	/* send file
	 * @param path: the path of file to send
	 * @param content_type: type of content
	 * @param for_download: is notify browser to download
	 * @param start_size: start size of file
	 * @param use_cache: use cache or not
	 * @param show_name: show name for http
	 */
	void SendFile(const char* path, const char* content_type, bool for_download, int start_size, bool use_cache, const char* show_name);

	void Close();

public:
	bool StartReceiveFile(const std::string& file_path, int start_size, std::string& reason);

private:
	void Clear();

public:
	const std::string& GetRemoteIP() const;
	int GetRemotePort() const;

public:
	void HandleSend(std::size_t bytes_transferred);

public:
	void* GetSocket() const { return m_socket.get(); }
	CarpHttpSocketPtr GetSocketPtr() const { return m_socket; }

private:
	CarpHttpSocketPtr m_socket;			// socket

	std::string m_remote_ip;			// ip dress
	int m_remote_port;

public:
	void* m_user_data;
	int m_id;

private:
	std::string m_http_content;	// send http response

	// file info
	FileCacheHelper* m_file;
	std::string m_file_path;
	std::vector<char> m_file_buffer;

private:
	// store last send time
	time_t m_end_time;
	void Heartbeat(int second);

public:
	bool IsSending() const;
	bool IsRemoved() const;

private:
	bool m_is_sending;
	bool m_is_removed;

private:
	HttpServerWeakPtr m_server_system;

public:
	HttpReceiverWeakPtr m_receiver;
};

} // ALittle

#endif // _ALITTLE_HTTPSENDER_H_