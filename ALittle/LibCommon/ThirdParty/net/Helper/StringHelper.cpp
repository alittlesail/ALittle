
#include "StringHelper.h"

#include <vector>

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
	sprintf_s(ip_dest, "%lu.%lu.%lu.%lu", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#else
	sprintf(ip_dest, "%lu.%lu.%lu.%lu", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
#endif
	return std::string(ip_dest);
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