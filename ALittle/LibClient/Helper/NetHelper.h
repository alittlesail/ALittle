
#ifndef _ALITTLE_NETHELPER_H_
#define _ALITTLE_NETHELPER_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>

#include <SDL.h>
#include <string>

namespace ALittle
{

class NetHelper
{
public:
	/**
	 * find sub vector from buffer
	 * @param buffer char buffer
	 * @param target char target
	 * @return start_index, end_index
	 * @return succeed or not
	 */
	static bool VectorCharFindString(const std::vector<char>& buffer, const std::vector<char>& target, int& start_index, int& end_index);
	
	/**
	 * trans vector char to hex number
	 * @param buffer char buffer
	 * @return result
	 * @return succeed or not
	 */
	static bool VectorChar2Hex(const std::vector<char>& buffer, int& result);

public:
	/* ip to string
	* @param ip: ip in unsigned int
	* @return ip in string
	*/
	static std::string Ip2String(unsigned int ip);

public:
	/**
	* get network type
	*/
	static const char* GetNetworkType();
	static void StartNetworkListener();

	static std::string s_temp_string;
};

} // ALittle

#endif // _ALITTLE_NETHELPER_H_
