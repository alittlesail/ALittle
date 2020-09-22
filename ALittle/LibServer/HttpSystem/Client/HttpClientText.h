
#ifndef _ALITTLE_HTTPCLIENTTEXT_H_
#define _ALITTLE_HTTPCLIENTTEXT_H_

#define CARP_HAS_SSL
#include "Carp/carp_http.hpp"
#include "ALittle/LibCommon/Helper/HttpHelper.h"

#include <string>
#include <fstream>

#include <functional>
#include <memory>

namespace ALittle
{

class HttpClientText;
typedef std::shared_ptr<HttpClientText> HttpClientTextPtr;
typedef std::shared_ptr<asio::ip::tcp::resolver> ResolverPtr;

#define HTTP_HEAD_BUFFER_SIZE 1024

class HttpClientText : public std::enable_shared_from_this<HttpClientText>
{
public:
	HttpClientText();
	~HttpClientText();

public:
	/* send request
	 * @param get_or_post: true: get method, false: post method
	 * @param type type of content. ie text/xml. text/html text/json
	 * @param file_path: write content of response to file(if file_path is not empry, then string of callback is empty£©
	 * @param func: callback function, bool:succeed or not, string:content of response, string:head of response
	 * @param is_ssl: is ssl
	 */
	void SendRequest(const std::string& url
		, bool get_or_post, const std::string& type, const char* content, size_t content_len
		, std::function<void(bool, const std::string&, const std::string&)> func
		, asio::io_service* io_service
		, const std::string& file_path="", const std::string& add_header="");

private:
	void HandleQueryIPByDemain(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator
		, const std::string& domain, const std::string& port);

	void HandleQueryIPByDemainAgain(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator);

	void HandleSocketConnect(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator);

	void HandleSSLHandShake(const asio::error_code& ec);

	bool GenerateRequestHead(const std::string& domain, const std::string& add_header="");

	void HandleSocketSendRequestHead1(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleSocketSendRequestHead2(const asio::error_code& ec
		, std::size_t bytes_transferred);

	void HandleResponseHead(const asio::error_code& ec, std::size_t actual_size);

private:
	void HandleResponseByContentLength(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);
	void HandleResponseByChunk(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);
	void HandleResponseByDataFollow(const asio::error_code& ec, std::size_t actual_size, int buffer_offset);

private:
	std::string m_url;				// url
	std::string m_domain;			// domain
	bool		m_get_or_post;		// get or post
	std::string m_type;				// type of content
	std::vector<char> m_content;	// content
	std::string m_request_head;		// request head
	std::string m_response;			// response
	std::string m_response_head;	// response head
	HttpHelper::ResponseType m_response_type;			// response type
	std::string m_chunk_size;		// save for chunk size string
	int m_response_size;			// size of response

	CarpHttpSocketPtr m_socket;		// socket
	ResolverPtr m_resolver;			// reslover
	asio::io_service* m_io_service;	// io_service

	std::function<void(bool, const std::string&, const std::string&)> m_callback; // callback
	std::string m_file_path;		// file path to write
	std::ofstream m_file;			// file object
	
private:
	char m_http_buffer[HTTP_HEAD_BUFFER_SIZE]; // receive buffer
	std::string m_status;
};

} // ALittle

#endif // _ALITTLE_HTTPCLIENTTEXT_H_
