
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
	* get network type
	*/
	static const char* GetNetworkType();
	static void StartNetworkListener();

	static std::string s_temp_string;
};

} // ALittle

#endif // _ALITTLE_NETHELPER_H_
