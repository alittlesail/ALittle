
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
#include <SDL_net.h>
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

	/**
	 * receive bytes until fill full with buffer
	 * @param socket TCPSocket object
	 * @param buffer 
	 * @param len
	 * @return result <= 0 is receive failed, if result > 0 is byte count received
	 */
	static int TCPSocketReceive(TCPsocket sock, void *buffer, int len);
	
	/**
	 * send bytes
	 * @param socket TCPSocket
	 * @param buffer
	 * @param len
	 * @return result <= 0 is send failed, if result > 0 is send byte count sended
	 */
	static int TCPSocketSend(TCPsocket sock, void *buffer, int len);

public:
	/* get local ip list
	* @return ip list in json
	*/
	static const char* GetLocalIPList();

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


private:
	static int s_ai_family;
	static std::string s_temp_string;

public:
	static int GetAIFamily(const char* ip, int port);
	static void ClearAIFamily();
};

} // ALittle

#endif // _ALITTLE_NETHELPER_H_
