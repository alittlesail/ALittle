
#ifndef _ALITTLE_HTTPFILE_H_
#define _ALITTLE_HTTPFILE_H_

#include <string>
#include <vector>

#include "Carp/carp_http.hpp"
#include "Carp/carp_safe_id_creator.h"

namespace ALittle
{

class HttpFile
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
	 * start
	 */
	void Start();

	/**
	 * stop
	 */
	void Stop();

public:
	const char* GetPath();
	unsigned int GetTotalSize() const;
	unsigned int GetCurSize() const;

private:
	int m_id;
	std::string m_url;				// uel
	std::string m_file_path;		// file path
	unsigned int m_total_size;		// total file size
	unsigned int m_cur_size;	// current size
	int m_start_size;				// start size
	bool m_download;				// download or upload
	std::string m_failed_reason;

private:
	static CarpSafeIDCreator<int> s_id_creator;

private:
	CarpHttpClientPostPtr m_upload_client;
	CarpHttpClientTextPtr m_download_client;
};

} // ALittle

#endif // _ALITTLE_HTTPFILE_H_
