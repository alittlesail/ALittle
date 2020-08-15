
#include "LogHelper.h"

#include "ALittle/LibCommon/Tool/LogSystem.h"

namespace ALittle
{

void LogHelper::Log(const char * content, short level)
{
	g_LogSystem.Log(content, level);
}

} // ALittle
