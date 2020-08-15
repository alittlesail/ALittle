
#ifndef _ALITTLE_HTTPCLIENT_H_
#define _ALITTLE_HTTPCLIENT_H_

#include <string>
#include <vector>

#include "ALittle/LibCommon/Tool/SafeIDCreator.h"
#include "ALittle/LibClient/Helper/NetHelper.h"
#include "ALittle/LibClient/ThreadSystem/Task.h"

namespace ALittle
{

class HttpClient : public Task
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
	 * start load
	 * @return succeed or not
	 */
	bool Load();

	/**
	 * Start http
	 */
	void Start();

	/**
	 * stop http
	 */
	void Stop();

	const char* GetStatus() const;
	
	/**
	 * get response
	 * @return response
	 */
	const char* GetResponse() const;
	/**
	 * get response
	 * @return response
	 */
	void GetContent(char*& content, int& size);
	
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

public:
	void Execute();
	void Abandon();

private:
	int m_id;
	std::string m_url;			// url
	std::string m_content;		// if content is empty, then GET. otherwise POST
	std::vector<char> m_response;		// repones
	std::vector<char> m_chunk_buffer; // chunk buffer
	bool m_continue_load;		// check load continue
	std::string m_status;		// status of response
	std::string m_failed_reason;	//  ß∞‹‘≠“Ú

	static SafeIDCreator<int> s_id_creator;

private:
	TCPsocket m_socket;
};

} // ALittle

#endif // _ALITTLE_HTTPCLIENT_H_
