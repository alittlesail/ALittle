
#include "NetHelper.h"

#include "BitHelper.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "ALittle/LibClient/Platform/Android/AndroidSystem.h"
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "ALittle/LibClient/Platform/Windows/WindowsSystem.h"

namespace ALittle
{

bool NetHelper::VectorCharFindString( const std::vector<char>& buffer, const std::vector<char>& target, int& start_index, int& end_index )
{
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		bool find = true;
		for (size_t j = 0; j < target.size(); ++j)
		{
			if (i + j >= buffer.size()) { find = false; break; }
			if (target[j] != buffer[i + j]) { find = false; break; }
		}

		if (find)
		{
			start_index = static_cast<int>(i);
			end_index = static_cast<int>(i + target.size());
			return true;
		}
	}
	return false;
}

bool NetHelper::VectorChar2Hex( const std::vector<char>& buffer, int& result )
{
	result = 0;
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		char n = buffer[i];

		int v = 0;
		if (n >= '0' && n <= '9')
			v = n -'0';
		else if (n >= 'A' && n <= 'F')
			v = n - 'A' + 10;
		else if (n >= 'a' && n <= 'f')
			v = n - 'a' + 10;
		else
			return false;

		result = result * 16 + v;
	}
	return true;
}

std::string NetHelper::Ip2String(unsigned int ip)
{
	char ip_dest[16] = { 0 };
#ifdef _WIN32
	sprintf_s(ip_dest, "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#else
	sprintf(ip_dest, "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#endif
	return std::string(ip_dest);
}

std::string NetHelper::s_temp_string;
const char* NetHelper::GetNetworkType()
{
#ifdef __ANDROID__
	return Android_GetNetworkType();
#elif __IPHONEOS__
	return iOS_GetNetworkType();
#elif _WIN32
	return Windows_GetNetworkType();
#else
	s_temp_string = "OtherSystem_NotifyNetwork_none";
	return s_temp_string.c_str();
#endif
}

void NetHelper::StartNetworkListener()
{
#ifdef __ANDROID__
	Android_StartNetworkListener();
#elif __IPHONEOS__
	iOS_StartNetworkListener();
#elif _WIN32
	Windows_StartNetworkListener();
#endif
}

} // ALittle