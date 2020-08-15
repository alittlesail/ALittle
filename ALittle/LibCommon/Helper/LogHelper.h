
#ifndef _ALITTLE_LOGHELPER_H_
#define _ALITTLE_LOGHELPER_H_

#include <sstream>

namespace ALittle
{
#define LOG_FOREGROUND_BLUE			0x0001 // text color contains blue.
#define LOG_FOREGROUND_GREEN		0x0002 // text color contains green.
#define LOG_FOREGROUND_RED			0x0004 // text color contains red.
#define LOG_FOREGROUND_INTENSITY	0x0008 // text color is intensified.
#define LOG_BACKGROUND_BLUE			0x0010 // background color contains blue.
#define LOG_BACKGROUND_GREEN		0x0020 // background color contains green.
#define LOG_BACKGROUND_RED			0x0040 // background color contains red.

class LogHelper
{
public:
	enum LogLevel
	{
		LL_INFO = 0,
		LL_WARN = 1,
		LL_ERROR = 2,
		LL_SYSTEM = 3,
		LL_DATABASE = 4,
		LL_EVENT = 5,
	};

	enum LogColor
	{
		LC_ERROR = LOG_BACKGROUND_RED | LOG_BACKGROUND_GREEN | LOG_BACKGROUND_BLUE | LOG_FOREGROUND_RED,
		LC_SYSTEM = LOG_FOREGROUND_GREEN | LOG_FOREGROUND_BLUE | LOG_FOREGROUND_BLUE,
		LC_DATABASE = LOG_BACKGROUND_RED | LOG_BACKGROUND_GREEN | LOG_BACKGROUND_BLUE,
		LC_EVENT = LOG_FOREGROUND_RED | LOG_FOREGROUND_GREEN,
		LC_WARN = LOG_FOREGROUND_RED | LOG_FOREGROUND_GREEN,
		LC_INFO = LOG_FOREGROUND_RED | LOG_FOREGROUND_GREEN | LOG_FOREGROUND_BLUE,
	};

public:
	static void Log(const char* content, short level);
};

} // ALittle

// 属于严重的代码错误，属于非常意外的，没想到会在这里出错的
#define ALITTLE_ERROR(text) do{ std::ostringstream astream; astream << "ERROR:" << __FILE__ << ":"<< __FUNCTION__ << "() " << __LINE__ << ":" << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_ERROR); }while(0)
// 属于系统级别的错误，这种错误是预知的，已经在系统流程规划之内，也是无关紧要的日志
#define ALITTLE_SYSTEM(text) do{ std::ostringstream astream; astream << "SYSTEM:" << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_SYSTEM); }while(0)
// 属于数据库错误，属于严重错误
#define ALITTLE_DATABASE(text) do{ std::ostringstream astream; astream << "DATABASE:" << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_DATABASE); }while(0)
// 事件性
#define ALITTLE_EVENT(text) do{ std::ostringstream astream; astream << "EVENT:" << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_EVENT); }while(0)
// 警告，比如负载很高了，压力很大了
#define ALITTLE_WARN(text) do{ std::ostringstream astream; astream << "WARN:" << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_WARN); }while(0)
// 单纯的调试打印
#define ALITTLE_INFO(text) do{ std::ostringstream astream; astream << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_INFO); }while(0)
// 属于严重的代码错误，属于非常意外的，没想到会在这里出错的，提供给脚本系统使用
#define ALITTLE_SCRIPT_ERROR(text) do{ std::ostringstream astream; astream << text; ALittle::LogHelper::Log(astream.str().c_str(), ALittle::LogHelper::LL_ERROR); }while(0)

#endif // _ALITTLE_LOGHELPER_H_
