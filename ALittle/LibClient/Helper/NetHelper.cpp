
#include "NetHelper.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "ALittle/LibClient/Platform/Android/AndroidSystem.h"
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "ALittle/LibClient/Platform/Windows/WindowsSystem.h"

namespace ALittle
{
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