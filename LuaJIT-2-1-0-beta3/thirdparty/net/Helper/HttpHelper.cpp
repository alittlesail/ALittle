
#include "HttpHelper.h"
#include "StringHelper.h"

namespace ALittle
{

bool HttpHelper::String2HexNumber(int& result, const std::string& content)
{
	result = 0;
	for (size_t i = 0; i < content.size(); ++i)
	{
		int num = 0;
		if (content[i] >= '0' && content[i] <= '9')
			num = content[i] - '0';
		else if (content[i] >= 'a' && content[i] <= 'f')
			num = content[i] - 'a' + 10;
		else if (content[i] >= 'A' && content[i] <= 'F')
			num = content[i] - 'A' + 10;
		else
			return false;

		result = result * 16 + num;
	}

	return true;
}

std::string HttpHelper::UrlEncode(const std::string& url)
{
	static char hex[] = "0123456789ABCDEF";
	std::string dst;

	for (size_t i = 0; i < url.size(); ++i)
	{
		unsigned char cc = url[i];
		if (isascii(cc))
		{
			if (cc == ' ')
				dst += "%20";
			else
				dst += cc;
		}
		else
		{
			dst += '%';
			dst += hex[cc / 16];
			dst += hex[cc % 16];
		}
	}
	return dst;
}

std::string HttpHelper::PHPUrlEncode(const std::string& url)
{
	static char hex[] = "0123456789ABCDEF";
	std::string dst;

	for (size_t i = 0; i < url.size(); ++i)
	{
		unsigned char cc = url[i];
		if (((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <='Z') || (cc >= '0' && cc <= '9'))
			|| cc == '.'
			|| cc == '-'
			|| cc == '_')
		{
			dst += cc;
		}
		else if (cc == ' ')
			dst += "+";
		else
		{
			dst += '%';
			dst += hex[cc / 16];
			dst += hex[cc % 16];
		}
	}
	return dst;
}

std::string HttpHelper::UrlDecode(const std::string& url)
{
	std::string result;
	int hex = 0;
	for (size_t i = 0; i < url.size(); ++i)
	{
		switch (url[i])
		{
		case '+': result += ' ';
			break;
		case '%':
			if (isxdigit(url[i + 1]) && isxdigit(url[i + 2]))
			{
				std::string hex_str = url.substr(i + 1, 2);
				hex = strtol(hex_str.c_str(), 0, 16);
				if (!((hex >= 48 && hex <= 57) ||
					(hex >=97 && hex <= 122) ||
					(hex >=65 && hex <= 90) ||
					hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
					|| hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
					|| hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
					))
				{
					result += static_cast<char>(hex);
					i += 2;
				}
				else result += '%';
			}else {
				result += '%';
			}

			break;
		default: result += url[i];
			break;
		}
	}

	return result;
}

void HttpHelper::GenerateGetRequestHead(const std::string& domain, const std::string& path, std::string& result)
{
	result = "";
	if (!path.empty())
		result.append("GET ").append(UrlEncode(path)).append(" HTTP/1.1\r\n");
	else
		result.append("GET / HTTP/1.1\r\n");
	result.append("Accept: */*\r\n");
	result.append("User-Agent: ALittle Client\r\n");
	result.append("Host: ").append(domain).append("\r\n");

	result.append("Connection: Close\r\n");
	result.append("\r\n");
}

void HttpHelper::GeneratePostRequestHead(const std::string& domain, const std::string& path, const std::string& content, std::string& result)
{
	result = "";
	if (!path.empty())
		result.append("POST ").append(UrlEncode(path)).append(" HTTP/1.1\r\n");
	else
		result.append("POST / HTTP/1.1\r\n");
	result.append("Accept: */*\r\n");
	result.append("User-Agent: ALittle Client\r\n");
	result.append("Host: ").append(domain).append("\r\n");
	result.append("Content-Type: application/x-www-form-urlencoded\r\n");

	char text[32] = { 0 };
#ifdef _WIN32
	sprintf_s(text, "%zd", content.size());
#else
	sprintf(text, "%zd", content.size());
#endif
	result.append("Content-Length: ").append(text).append("\r\n");

	result.append("Connection: Close\r\n");
	result.append("\r\n");
	result.append(content);
}

bool HttpHelper::CalcStatusFromHttp(const std::string& response, std::string& status)
{
	status = "";
	std::string::size_type pos = response.find("HTTP/");
	if (pos == std::string::npos) return false;

	pos = response.find(' ', pos);

	++ pos;

	std::string::size_type pos_end = response.find(' ', pos);
	if (pos_end == std::string::npos) return false;

	status = response.substr(pos, pos_end - pos);
	
	return status.size() != 0;
}

bool HttpHelper::CalcFileSizeFromHttp(const std::string& response, int& length, ResponseType& type)
{
	std::string new_response = response;
	StringHelper::UpperString(new_response);

	length = 0;
	std::string::size_type content_length_pos = new_response.find("CONTENT-LENGTH:");
	if (content_length_pos != std::string::npos)
	{
		std::string::size_type content_length_pos_end = new_response.find("\r\n", content_length_pos);
		if (content_length_pos_end == std::string::npos)
			return false;

		content_length_pos += strlen("CONTENT-LENGTH:");
		std::string content = response.substr(content_length_pos, content_length_pos_end - content_length_pos);
		StringHelper::TrimRight(content); StringHelper::TrimLeft(content);
		length = atoi(content.c_str());

		type = HttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH;
		return true;
	}

	std::string::size_type content_chunk_pos = new_response.find("CHUNKED");
	if (content_chunk_pos != std::string::npos)
	{
		type = HttpHelper::ResponseType::RESPONSE_TYPE_CHUNK;
		return true;
	}

	type = HttpHelper::ResponseType::RESPONSE_TYPE_DATAFOLLOW;
	return true;
}

bool HttpHelper::CalcContentTypeFromHttp(const std::string& response, std::string& type)
{
	std::string new_response = response;
	StringHelper::UpperString(new_response);

	type = "";
	std::string::size_type content_length_pos = new_response.find("CONTENT-TYPE:");
	if (content_length_pos == std::string::npos)
		return false;

	std::string::size_type content_length_pos_end = new_response.find("\r\n", content_length_pos);
	if (content_length_pos_end == std::string::npos)
		return false;

	content_length_pos += strlen("CONTENT-TYPE:");
	type = response.substr(content_length_pos, content_length_pos_end - content_length_pos);
	StringHelper::TrimRight(type); StringHelper::TrimLeft(type);
	return true;
}

bool HttpHelper::CalcDomainAndPortByUrl(const std::string& url, std::string& demain, int& port, std::string& path)
{
	const char* start_demain_pos = url.c_str();

	port = 80;
	if (url.substr(0, 7) == "http://")
		start_demain_pos += 7;

	if (url.size() >= 8 && url.substr(0, 8) == "https://")
	{
		start_demain_pos += 8;
		port = 443;
	}

	const char* end_demain_pos = start_demain_pos;
	while (*end_demain_pos && *end_demain_pos != '/')
		++end_demain_pos;

	std::string new_url = url.substr(start_demain_pos - url.c_str(), end_demain_pos - start_demain_pos);
	demain = new_url;
	std::string::size_type port_pos = new_url.find(":");
	if (port_pos != std::string::npos)
	{
		demain = new_url.substr(0, port_pos);
		std::string str_port = new_url.substr(port_pos + 1);
		port = atoi(str_port.c_str());
	}

	path = url.substr(end_demain_pos - url.c_str());

	return true;
}

std::string HttpHelper::GetContentTypeByExt(const std::string& ext)
{
    std::string upper_ext = ext;
    StringHelper::UpperString(upper_ext);

    if (upper_ext == "HTML" || upper_ext == "HTM" || upper_ext == "HTX") return "text/html";
    if (upper_ext == "ICO") return "image/x-icon";
    if (upper_ext == "CSS") return "text/css";
    if (upper_ext == "XML" || upper_ext == "plist") return "text/xml";
    if (upper_ext == "JSON") return "application/json";
    if (upper_ext == "JS") return "application/x-javascript";
    if (upper_ext == "PNG") return "image/png";
    if (upper_ext == "JPG" || upper_ext == "JPEG") return "image/jpeg";
    if (upper_ext == "GIF") return "image/gif";
    if (upper_ext == "BMP") return "application/x-bmp";
    return "";
}

bool HttpHelper::AnalysisRequest(const std::string& request, std::string& method, std::string& path, std::string* param, std::string* content_type, std::string* content)
{
	size_t method_end_pos = request.find(' ');
	if (method_end_pos == std::string::npos)
		return false;

	method = request.substr(0, method_end_pos);

	size_t url_end_pos = request.find(' ', method_end_pos + 1);
	if (url_end_pos == std::string::npos)
		return false;

	std::string url = UrlDecode(request.substr(method_end_pos + 1, url_end_pos - method_end_pos - 1));

	size_t path_end_pos = url.find('?');
	if (path_end_pos != std::string::npos)
	{
		path = url.substr(0, path_end_pos);
		if (param) *param = url.substr(path_end_pos + 1);
	}
	else
		path = url;

	size_t content_pos = request.find("\r\n\r\n");

	if (content_type)
		CalcContentTypeFromHttp(request.substr(0, content_pos), *content_type);

	if (content)
	{
		if (content_pos != std::string::npos)
		{
			content_pos += strlen("\r\n\r\n");
			*content = request.substr(content_pos);
		}
	}
	return true;
}

} // ALittle
