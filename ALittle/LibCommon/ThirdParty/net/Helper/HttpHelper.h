
#ifndef _ALITTLE_HTTPHELPER_H_
#define _ALITTLE_HTTPHELPER_H_

#include <string>
#include <map>

namespace ALittle
{

class HttpHelper
{
public:
	enum class ResponseType
	{
		RESPONSE_TYPE_CONTENT_LENGTH,
		RESPONSE_TYPE_CHUNK,
		RESPONSE_TYPE_DATAFOLLOW
	};

	// 把十六进制数转成数值，如果出现非法字符就返回false
	static bool String2HexNumber(int& result, const std::string& content);

public:
	// url加密
	static std::string UrlEncode(const std::string& url);
	// PHP版本的url加密
	static std::string PHPUrlEncode(const std::string& url);
	// url解密
	static std::string UrlDecode(const std::string& url);
	
public:
	// 生成Get请求头
	static void GenerateGetRequestHead(const std::string& domain, const std::string& path, std::string& result);
	// 生成Post请求头
	static void GeneratePostRequestHead(const std::string& domain, const std::string& path, const std::string& content, std::string& result);
	
public:
	static bool AnalysisRequest(const std::string& request, std::string& method, std::string& path, std::string* param, std::string* content_type, std::string* content);
	
public:
	// 从http头获取status
	static bool CalcStatusFromHttp(const std::string& response, std::string& status);
	// 从http头获取文件大小
	static bool CalcFileSizeFromHttp(const std::string& response, int& length, ResponseType& type);
	// 从http头获取域名和端口
	static bool CalcDomainAndPortByUrl(const std::string& url, std::string& demain, int& port, std::string& path);
	// 从http头获取获取文件类型
	static bool CalcContentTypeFromHttp(const std::string& response, std::string& type);
	
public:
	// 根据后缀名查找对应的文件文件类型
    static std::string GetContentTypeByExt(const std::string& ext);
};

} // ALittle

#endif // _ALITTLE_HTTPHELPER_H_
