#ifndef _ALITTLE_HTTPCLIENTPOST_H_
#define _ALITTLE_HTTPCLIENTPOST_H_

#include "ALittle/LibServer/Tool/SocketWrap.h"
#include "ALittle/LibCommon/Helper/HttpHelper.h"

#include <string>
#include <fstream>
#include <map>

#include <functional>
#include <memory>

namespace ALittle
{

class HttpClientPost;
typedef std::shared_ptr<HttpClientPost> HttpClientPostPtr;
typedef std::shared_ptr<asio::ip::tcp::resolver> ResolverPtr;

#define HTTP_HEAD_BUFFER_SIZE 1024

class HttpClientPost : public std::enable_shared_from_this<HttpClientPost>
{
public:
	HttpClientPost();
	~HttpClientPost();

public:
	/* send request
	 * @param value_map: params(KEY-VALUE)
	 * @param file_name: rename the file to upload
	 * @param file_path: the path of file to upload
	 * @param func: callback function, bool:succeed or not, string:content of response, string:head of response
	 */
	void SendRequest(const std::string& url
		, const std::map<std::string, std::string>& value_map
		, const std::string& file_name
		, const std::string& file_path
		, std::function<void(bool, const std::string&, const std::string&)> func
		, asio::io_service* io_service
		, const std::string& add_header="");

private:
	void HandleQueryIPByDemain(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator
		, const std::string& domain, const std::string& port);

	void HandleQueryIPByDemainAgain(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator);

	void HandleSocketConnect(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator);

	void HandleSSLHandShake(const asio::error_code& ec);

	bool GeneratePostRequest(const std::string& domain, const std::string& add_header="");

	void HandleSocketSendRequestHead(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleSocketSendRequestParam(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleSocketSendRequestFileBegin(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleSocketSendRequestFile(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleSocketSendRequestFileEnd(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleResponseHead(const asio::error_code& ec, std::size_t actual_size);

private:
	void HandleResponseByContentLength(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);
	void HandleResponseByChunk(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);
	void HandleResponseByDataFollow(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);

private:
	std::string m_url;					// url
	std::string m_request_head;			// request head
	std::string m_request_param;		// param of request
	std::string m_request_file_begin;	// head param of file
	std::string m_request_file_end;		// tail patam of file
	std::string m_response;				// response
	std::string m_response_head;		// response head
	HttpHelper::ResponseType m_response_type;	// response type
	std::string m_chunk_size;			// save for chunk size string
	int m_response_size;				// size of response

	ALittleSocketPtr m_socket;			// Socket
	ResolverPtr m_resolver;				// reslover
	asio::io_service* m_io_service;		// io_service

	std::function<void(bool, const std::string&, const std::string&)> m_callback; // callback
	std::string m_file_path;			// the path of file to upload
	std::string m_file_name;			// rename the file to upload
	FILE* m_file;						// file object

	std::map<std::string, std::string> m_value_map;	// KEY-VALUE

private:
	char m_http_buffer[HTTP_HEAD_BUFFER_SIZE]; // receive buffer
};

} // ALittle

#endif // _ALITTLE_HTTPCLIENTPOST_H_
