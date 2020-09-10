
#ifndef _ALITTLE_HTTPFILE_H_
#define _ALITTLE_HTTPFILE_H_

#include <string>
#include <vector>

#include "ALittle/LibCommon/Tool/SafeIDCreator.h"
#include "ALittle/LibClient/ThreadSystem/Task.h"
#include "ALittle/LibClient/Helper/NetHelper.h"

namespace ALittle
{

class HttpFile : public Task
{
public:
	HttpFile();
	~HttpFile();

public:
	/**
	 * handle HTTP response
	 * @param event_type
	 * @param data1 HttpFile object
	 */
	static void HandleEvent(unsigned int event_type, void* data1, void* data2);

public:
	/**
	 * set URL
	 * @param url HTTP url
	 * @param file_name file name
	 * @param true:download, false:upload
	 * @param start_size: file offset to start
	 */
	void SetURL(const char* url, const char* file_name, bool download, int start_size, bool array_buffer);
	
	int GetID() const;

public:
	/**
	 * download
	 * @return succeed or not
	 */
	bool Download();
	/**
	 * upload
	 * @return succeed or not
	 */
	bool Upload();

	/**
	 * start
	 */
	void Start();

	/**
	 * stop
	 */
	void Stop();

public:
	const char* GetStatus();
	const char* GetContent();
	const char* GetPath();
	unsigned int GetTotalSize() const;
	unsigned int GetCurSize() const;

public:
	void Execute();
	void Abandon();

private:
	int m_id;
	std::string m_url;				// uel
	std::string m_file_path;		// file path
	unsigned int m_total_size;		// total file size
	unsigned int m_cur_size;	// current size
	int m_start_size;				// start size
	bool m_download;				// download or upload
	bool m_continue_load;			// continue or not
	std::string m_response;			// response for upload
	std::vector<char> m_chunk_buffer; // chunk buffer
	std::string m_status;			// response status
	std::string m_failed_reason;		//  ß∞‹‘≠“Ú

	static SafeIDCreator<int> s_id_creator;

private:
	TCPsocket m_socket;
};

} // ALittle

#endif // _ALITTLE_HTTPFILE_H_
