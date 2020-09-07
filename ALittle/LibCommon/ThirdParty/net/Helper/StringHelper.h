
#ifndef _ALITTLE_STRINGHELPER_H_
#define _ALITTLE_STRINGHELPER_H_

#include <string>
#include <vector>
#include <list>

namespace ALittle
{

// Êý×ÖºÍ×Ö·û´®»¥×ª£¬ÇëÊ¹ÓÃstd::to_stringºÍstd::atoi

class StringHelper
{
public:
    // É¾³ý×ó±ßµÄ¿Õ¸ñ
	static void TrimLeft(std::string& target);
	
    // É¾³ýÓÒ±ßµÄ¿Õ¸ñ
	static void TrimRight(std::string& target);
	
    // ¸ÄÎª´óÐ´
	static void UpperString(std::string& target);

    // °ÑÕûÐÎIP×ªÎª×Ö·û´®
	static std::string Ip2String(unsigned int ip);

	// ÅÐ¶ÏÊÇ·ñÊÇÊý×Ö
	static bool IsNumber(char value) { return value >= '0' && value <= '9'; }
	// ÅÐ¶ÏÊÇ·ñÊÇ×ÖÄ¸
	static bool IsLetter(char value) { return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z'); }

    // Ë«ÒýºÅ×ªÒÆ
    static std::string DoubleQouteEscape(const std::string& value);

private:
    template <typename T>
    static void AddElement(T& list, const std::string& v) { list.push_back(v); }
    static void AddElement(std::list<int>& list, const std::string& v) { list.push_back(std::atoi(v.c_str())); }
    static void AddElement(std::vector<int>& list, const std::string& v) { list.push_back(std::atoi(v.c_str())); }

public:
    // ÇÐ¸î×Ö·û´®
    template <typename T>
    static void Split(const std::string& content, const std::string& split, T& list)
    {
        list.resize(0);
        if (content.size() == 0) return;

        size_t start_index = 0;
        while (true)
        {
            size_t pos = content.find(split, start_index);
            if (pos != std::string::npos)
            {
                AddElement(list, content.substr(start_index, pos - start_index));
                start_index = pos + split.size();
                continue;
            }
            break;
        }

        if (start_index == 0)
            AddElement(list, content);
        else
            AddElement(list, content.substr(start_index));
    }

private:
    template <typename T>
    static void AddString(std::string& result, const T& v) { result.append(std::to_string(v)); }
    static void AddString(std::string& result, const std::string& v) { result.append(v); }
    
public:
    // Æ´½Ó×Ö·û´®
    template <typename T>
	static std::string Join(const T& container, const std::string& split)
	{
		std::string result;
		size_t count = 0;
		for (auto it = container.begin(); it != container.end(); ++it)
		{
			++count;
            AddString(result, *it);
			if (count != container.size())
				result.append(split);

		}
		return result;
	}

};

} // ALittle

#endif // _ALITTLE_STRINGHELPER_H_
