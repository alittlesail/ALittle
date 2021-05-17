
#include <asio.hpp>

#include "ServerSystem/ServerSystem.h"
#include "Carp/carp_log.hpp"
#include "Carp/carp_string.hpp"

#include <map>
#include <vector>
#include <string>
#include "Carp/carp_json_all.hpp"

#include "Carp/carp_file.hpp"

int main(int argc, char* argv[])
{
	std::string core_path;
	std::string std_path;
	std::string sengine_path;
	std::map<std::string, ALittle::ModuleInfo> module_map;

	// 简易模式参数，直接使用当前Git上的目录格局
	if (argc == 2)
	{
		core_path = "Module/ALittleIDE/Other/GameLibrary/Core/";
		std_path = "Module/ALittleIDE/Other/GameLibrary/Std/";
		sengine_path = "Module/ALittleIDE/Other/GameLibrary/SEngine/";

		std::vector<std::string> module_split;
		CarpString::Split(argv[1], ";", false, module_split);
		for (auto& module_name : module_split)
		{
			module_map[module_name].module_name = module_name;
			module_map[module_name].module_path = CarpFile::TryAddFileSeparator("Server/" + module_name);
			module_map[module_name].config_path = module_map[module_name].module_path + module_name + ".cfg";
		}
	}
	else if (argc == 5)
	{
		core_path = argv[1];
		std_path = argv[2];
		sengine_path = argv[3];

		std::vector<std::string> module_split;
		CarpString::Split(argv[4], ";", false, module_split);
		for (auto& module_info : module_split)
		{
			std::vector<std::string> info_split;
			CarpString::Split(module_info, ",", false, info_split);
			if (info_split.size() != 4)
			{
				CARP_WARN(u8"错误的格式:" << module_info);
				continue;
			}
			module_map[info_split[0]].module_name = info_split[1];
			module_map[info_split[0]].module_path = CarpFile::TryAddFileSeparator(info_split[2]);
			module_map[info_split[0]].config_path = info_split[3];
		}
	}
	else
	{
		CARP_ERROR(u8"1个参数时\n"
			"Core模块脚本根路径:Module/ALittleIDE/Other/GameLibrary/Core/\n"
			"Std模块脚本根路径:Module/ALittleIDE/Other/GameLibrary/Std/\n"
			"SEngine模块脚本根路径:Module/ALittleIDE/Other/GameLibrary/SEngine/\n"
			"参数1:逻辑模块列表，路径前缀Module/Server/:"
			"模块名1,模块文件夹名1;"
			"模块名2,模块文件夹名2;"
			"...");

		CARP_ERROR(u8"4个参数时\n"
			"参数1:Core模块脚本根路径\n"
			"参数2:Std模块脚本根路径\n"
			"参数3:SEngine模块脚本根路径\n"
			"参数4:逻辑模块列表:"
			"模块标题1,模块名1,模块路径1,配置文件路径1;"
			"模块标题2,模块名2,模块路径2,配置文件路径2;"
			"...");
		return 0;
	}

	ALittle::ServerSystem::Instance().Setup(module_map);
	ALittle::ServerSystem::Instance().Start(core_path, std_path, sengine_path, module_map);
	ALittle::ServerSystem::Instance().Shutdown();
	return 0;
}

#define CARP_CONSOLE_IMPL
#include "Carp/carp_console.hpp"
#define CARP_DUMP_IMPL
#include "Carp/carp_dump.hpp"
#define CARP_LOG_IMPL
#include "Carp/carp_log.hpp"
#define CARP_TASK_CONSUMER_IMPL
#include "Carp/carp_task_consumer.hpp"
#define CARP_SCHEDULE_IMPL
#include "Carp/carp_schedule.hpp"
#define CARP_SURFACE_IMPL
#include "Carp/carp_surface_bind.hpp"
