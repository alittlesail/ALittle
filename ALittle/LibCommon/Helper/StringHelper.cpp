
#include "StringHelper.h"
#include "TimeHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}

#include <vector>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ALittle
{
	
void StringHelper::TrimLeft(std::string& target)
{
	std::string::size_type pos = target.find_first_not_of(' ');
	if (pos == std::string::npos) return;
	if (pos == 0) return;

	target = target.substr(pos);
}

void StringHelper::TrimRight(std::string& target)
{
	std::string::size_type pos = target.find_last_not_of(' ');
	if (pos == std::string::npos) return;
	if (pos + 1 == target.size()) return;

	target = target.substr(0, pos+1);
}

void StringHelper::UpperString(std::string& target)
{
	for (size_t i = 0; i < target.size(); ++i)
	{
		char c = target[i];
		if (c >= 'a' && c <= 'z')
		{
			c -= 'a' - 'A';
			target[i] = c;
		}
	}
}

std::string StringHelper::Ip2String(unsigned int ip)
{
	char ip_dest[16] = {0};
#ifdef _WIN32
	sprintf_s(ip_dest, "%u.%u.%u.%u", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#else
	sprintf(ip_dest, "%u.%u.%u.%u", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#endif
	return std::string(ip_dest);
}

std::string StringHelper::UTF82ANSI(const char* content)
{
	const char* res = utf8_UTF82ANSI(content);
	if (res == 0) return content;
	std::string result = res;
	free((void*)res);
	return result;
}

std::string StringHelper::ANSI2UTF8(const char* content)
{
    const char* res = utf8_ANSI2UTF8(content);
    if (res == 0) return content;
    std::string result = res;
    free((void*)res);
    return result;
}

std::string StringHelper::DoubleQouteEscape(const std::string& value)
{
    std::string result;
    for (auto& c : value)
    {
        if (c == '\\')
        {
            result.push_back(c);
            result.push_back(c);
        }
        else if (c == '"')
        {
            result.push_back('\"');
            result.push_back(c);
        }
        else if (c == '\t')
        {
            result.push_back('\\');
            result.push_back('t');
        }
        else if (c == '\r')
        {
            result.push_back('\\');
            result.push_back('r');
        }
        else if (c == '\n')
        {
            result.push_back('\\');
            result.push_back('n');
        }
        else
        {
            result.push_back(c);
        }
    }
    return result;
}

} // ALittle