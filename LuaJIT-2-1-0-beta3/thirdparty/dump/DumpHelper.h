
#ifndef _ALITTLE_DUMPHELPER_H_
#define _ALITTLE_DUMPHELPER_H_

#ifdef _WIN32

#include <string>

class DumpHelper
{
public:
    static void Setup(const std::string& pre_name);

    /********************************************************************
    * method: initProcessExceptionHandler
    * return: void
    * NOTE: set exception handler on per-process
    *********************************************************************/
    static void InitProcessExceptionHandler();

    /********************************************************************
    * method: initThreadExceptionHandler
    * return: void
    * NOTE: set exception handler on per-thread
    *********************************************************************/
    static void InitThreadExceptionHandler();

    /********************************************************************
    * method: getCallStackString
    * param:
    *		thread: thread handle
    *		buffer: callstack string buffer
    *		size:	buffer size
    * Note: 获取其他线程调用栈信息，需要先挂起该线程，执行完毕后再ResmueThread
    *********************************************************************/
    static void GetCallStackString(void* thread, char* buffer, size_t size);
};

#endif

#endif // _ALITTLE_DUMPHELPER_H_