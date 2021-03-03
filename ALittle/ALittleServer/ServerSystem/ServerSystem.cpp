
#include <asio.hpp>

#include "ServerSystem.h"
#include "ServerSchedule.h"

#include "Carp/carp_mysql.hpp"
#include "Carp/carp_file.hpp"
#include "Carp/carp_string.hpp"
#include "Carp/carp_dump.hpp"
#include "Carp/carp_console.hpp"

namespace ALittle
{

ServerSystem& ServerSystem::Instance()
{
	static ServerSystem instance;
	return instance;
}

#ifdef _WIN32
BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// case CTRL_LOGOFF_EVENT:
		// case CTRL_SHUTDOWN_EVENT:
	case CTRL_CLOSE_EVENT:
		CARP_INFO("CTRL_CLOSE_EVENT->Exit");
		ServerSystem::Instance().Close();
		break;
	case CTRL_C_EVENT:
		CARP_INFO("CTRL_C_EVENT->Exit");
		ServerSystem::Instance().Close();
		break;
	}
	return TRUE;
}
#endif // _WIN32

void ServerSystem::Setup(const std::map<std::string, ModuleInfo>& modules)
{
	// 计算模块名
	std::vector<std::string> module_name_list;
	for (auto it = modules.begin(); it != modules.end(); ++it)
		module_name_list.push_back(it->first);
	std::string module_name = CarpString::Join(module_name_list, "-");

#ifdef _WIN32
	s_carp_dump.Setup(module_name, []() {s_carp_dump.Shutdown(); });
#endif // _WIN32

	// set prename of log file from config
	CarpFile::CreateDeepFolder("Log");
	s_carp_log.Setup("Log/", module_name, true);
	
#ifdef _WIN32
	s_carp_console.Setup(module_name, std::bind(&ServerSystem::HandleConsoleCmd, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ServerSystem::HandleConsoleExit, this)
		, std::bind(&ServerSystem::HandleConsoleHelp, this)
		, std::bind(&ServerSystem::HandleConsoleRestart, this));
	// disabled the close button
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(GetConsoleWindow());

	// hook the Ctrl Message
#ifdef _DEBUG
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE) == FALSE)
		CARP_ERROR("SetConsoleCtrlHandler failed");
#else
	if (SetConsoleCtrlHandler(NULL, TRUE) == FALSE)
		CARP_ERROR("SetConsoleCtrlHandler failed");
#endif // _DEBUG
#endif // _WIN32

	// init mysql
	MysqlConnection::Setup();
}

void ServerSystem::Shutdown()
{
	s_carp_log.Shutdown();
	MysqlConnection::Shutdown();

#ifdef _WIN32
	s_carp_dump.Shutdown();
#endif // _WIN32
}

void ServerSystem::Start(const std::string& core_path, const std::string& std_path, const std::string& sengine_path
	, const std::map<std::string, ModuleInfo>& modules)
{
	while (true)
	{
		for (auto it = modules.begin(); it != modules.end(); ++it)
		{
			ServerSchedule* schedule = new ServerSchedule(core_path, std_path, sengine_path, it->first, it->second.module_name, it->second.module_path, it->second.config_path);
			std::thread* thread = new std::thread(ServerSystem::ScheduleRun, schedule);
			m_map[thread] = schedule;
		}

		for (auto it = m_map.begin(); it != m_map.end(); ++it)
		{
			it->first->join();
		}

		for (auto it = m_map.begin(); it != m_map.end(); ++it)
		{
			delete it->second;
			delete it->first;
		}

		m_map.clear();

		if (!m_restart) break;
		m_restart = false;
	}
}

void ServerSystem::Close()
{
	for (auto it = m_map.begin(); it != m_map.end(); ++it)
	{
		it->second->Exit();
	}
}

void ServerSystem::HandleConsoleCmd(const std::string& module_title, const std::string& cmd)
{
	for (auto it = m_map.begin(); it != m_map.end(); ++it)
	{
		if (it->second->GetModuleTitle() == module_title)
		{
			it->second->Execute(std::bind(&ServerSchedule::HandleConsoleCmd, it->second, cmd));
			return;
		}
	}
	CARP_WARN(u8"没有找到模块:" << module_title);
}

void ServerSystem::HandleConsoleExit()
{
	m_restart = false;
	Close();
}

void ServerSystem::HandleConsoleHelp()
{
	std::list<std::string> name_list;
	for (auto it = m_map.begin(); it != m_map.end(); ++it)
		name_list.push_back(it->second->GetModuleTitle());
	CARP_INFO(u8"模块列表:" << CarpString::Join(name_list, " "));
}

void ServerSystem::HandleConsoleRestart()
{
	m_restart = true;
	Close();
}

int ServerSystem::ScheduleRun(ServerSchedule* self)
{
	return self->Start();
}

} // ALittle
