
#ifndef _ALITTLE_LOGSYSTEM_H_
#define _ALITTLE_LOGSYSTEM_H_

#include "ThreadConsumer.h"

#include <string>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace ALittle
{

class ScriptSystem;

// 日志信息结构体
struct LogStringInfo
{
	LogStringInfo() : level(0) {}
    std::string content;		// 日志内容
    short level;				// 级别
};

class LogSystem : public ThreadConsumer<LogStringInfo>
{
public:
	static LogSystem& Instance();

public:
	// 设置日志文件名前缀
    void Setup(const std::string& path, const std::string& name);

private:
    // 日志文件前缀
    std::string m_file_name;
	std::string m_file_path;
	
public:
	// 日志
	// content 表示日志的内容
	void Log(const char* content, short level);

	// 关闭日志系统
	void Shutdown();

protected:
	// 执行日志
	virtual void Flush(LogStringInfo& info) override;

private:
    FILE* m_file;			// 日志文件对象
    time_t m_current_day;		// 当天0点的时间

#ifdef _WIN32
	HANDLE m_out;		// 控制台句柄
#endif // _WIN32

private:
	LogSystem();
	~LogSystem();
};

} // ALittle

#define g_LogSystem ALittle::LogSystem::Instance()

#endif // _ALITTLE_LOGSYSTEM_H_
