
#ifndef _ALITTLE_SERVERSYSTEM_H_
#define _ALITTLE_SERVERSYSTEM_H_

#include <map>
#include <string>
#include <thread>

namespace ALittle
{

class ServerSchedule;

struct ModuleInfo
{
	std::string module_name;
	std::string module_path;
	std::string config_path;
};

class ServerSystem
{
public:
	static ServerSystem& Instance();

public:
	void Setup(const std::map<std::string, ModuleInfo>& modules);
	void Shutdown();

public:
	void Start(const std::string& core_path, const std::string& std_path, const std::string& sengine_path
		, const std::map<std::string, ModuleInfo>& modules, bool block);
	void Close();
	
	// 把命令发给指定模块线程的脚本系统
	void HandleConsoleCmd(const std::string& module_name, const std::string& cmd);
	// 执行退出
	void HandleConsoleExit();
	// 执行help
	void HandleConsoleHelp();

private:
	// 支线程函数
	static int ScheduleRun(ServerSchedule* self);

private:
	std::map<std::thread*, ServerSchedule*> m_map;
	bool m_block;

private:
	ServerSystem() : m_block(false) {}
	~ServerSystem() {}
};

} // ALittle

#endif // _ALITTLE_SERVERSYSTEM_H_
