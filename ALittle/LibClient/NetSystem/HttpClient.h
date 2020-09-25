
#ifndef _ALITTLE_HTTPCLIENT_H_
#define _ALITTLE_HTTPCLIENT_H_

#include <string>

#include "Carp/carp_http.hpp"
#include "Carp/carp_safe_id_creator.hpp"

namespace ALittle
{

class HttpClient
{
public:
	HttpClient();
	~HttpClient();

public:
	/**
	 * handle HTTP response
	 * @param event_type
	 * @param data1 HttpClient object
	 */
	static void HandleEvent(unsigned int event_type, void* data1, void* data2);

public:
	/**
	 * set url
	 * @param url HTTP url
	 * @param content POST content
	 */
	void SetURL(const char* url, const char* content);

	/**
	 * Start http
	 */
	void Start();

	/**
	 * stop http
	 */
	void Stop();

	/**
	 * get response
	 * @return response
	 */
	const char* GetResponse() const;
	/**
	 * get response
	 * @return response
	 */
	void GetContent(const char*& content, int& size);
	
	/**
	 * get URL
	 * @return HTTP url
	 */
	const char* GetURL() const;
	
	/**
	 * get ID
	 * return HttpClient ID
	 */
	int GetID() const;

private:
	int m_id;
	std::string m_url;			// url
	std::string m_content;		// if content is empty, then GET. otherwise POST
	std::string m_response;		// repones
	std::string m_failed_reason;	//  ß∞‹‘≠“Ú

	static CarpSafeIDCreator<int> s_id_creator;

private:
	CarpHttpClientTextPtr m_client;
};

} // ALittle

#endif // _ALITTLE_HTTPCLIENT_H_
