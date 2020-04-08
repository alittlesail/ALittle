
extern "C" {
	#include "dump.h"
}
#include "DumpHelper.h"

void dump_setup(const char* name)
{
#ifdef _WIN32
	DumpHelper::Setup(name);
	DumpHelper::InitProcessExceptionHandler();
	DumpHelper::InitThreadExceptionHandler();
#endif
}
