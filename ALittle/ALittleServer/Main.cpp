
#include <asio.hpp>

#include "ServerSystem/ServerSystem.h"
#include "Carp/carp_log.hpp"
#include "Carp/carp_string.hpp"

#include <map>
#include <vector>
#include <string>

#include "Carp/carp_file.hpp"

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		CARP_ERROR(u8"需要输入4个参数\n参数1:Core模块脚本根路径\n参数2:Std模块脚本根路径\n参数3:SEngine模块脚本根路径\n参数4:逻辑模块列表:模块标题1,模块名1,模块路径1,配置文件路径1;模块标题2,模块名2,模块路径2,配置文件路径2;...");
		return 0;
	}

	std::string core_path = argv[1];
	std::string std_path = argv[2];
	std::string sengine_path = argv[3];
	std::map<std::string, ALittle::ModuleInfo> module_map;

	std::vector<std::string> module_split;
	CarpString::Split(argv[4], ";", module_split);
	for (auto& module : module_split)
	{
		std::vector<std::string> info_split;
		CarpString::Split(module, ",", info_split);
		if (info_split.size() < 2 || info_split.size() > 4)
		{
			CARP_WARN(u8"错误的格式:" << module);
			continue;
		}
		module_map[info_split[0]].module_name = info_split[1];
		module_map[info_split[0]].module_path = CarpFile::TryAddFileSeparator(info_split[2]);
		module_map[info_split[0]].config_path = info_split[3];
	}

	ALittle::ServerSystem::Instance().Setup(module_map);
	ALittle::ServerSystem::Instance().Start(core_path, std_path, sengine_path, module_map, true);
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