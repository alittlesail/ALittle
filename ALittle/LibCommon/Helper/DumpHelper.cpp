
#include "DumpHelper.h"
#include "ALittle/LibCommon/Tool/LogSystem.h"

#ifdef _WIN32

#include <eh.h>
#include <new.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(push)
#pragma warning(disable : 4091)  // disable: warning C4091
#include <dbghelp.h>
#pragma warning(pop)
#include <intrin.h>

#pragma comment(lib, "dbghelp.lib")

void* _ReturnAddress(void);  // NOLINT
#pragma intrinsic(_ReturnAddress)

#if defined(_M_IX86) || defined(_M_X64)
void* _AddressOfReturnAddress(void);  // NOLINT
#pragma intrinsic(_AddressOfReturnAddress)
#endif /* defined (_M_IX86) || defined (_M_X64) */

// custom exception code
#define CUSTOM_EXCEPTION_CODE_SIGNAL_ABORT 0xF0000001
#define CUSTOM_EXCEPTION_CODE_SIGNAL_FPE 0xF0000002
#define CUSTOM_EXCEPTION_CODE_INVALID_PARAMERTER 0xF0000010
#define CUSTOM_EXCEPTION_CODE_PURE_CALL 0xF0000011
#define CUSTOM_EXCEPTION_CODE_NEW 0xF0000012
#define CUSTOM_EXCEPTION_CODE_TERMINATE 0xF0000013
#define CUSTOM_EXCEPTION_CODE_UNEXPECTED 0xF0000014

class Locker
{
public:
  Locker() { InitializeCriticalSection(&cs_); }  // NOLINT
  ~Locker() { DeleteCriticalSection(&cs_); }

  void Lock() { EnterCriticalSection(&cs_); }

  void Unlock() { LeaveCriticalSection(&cs_); }

private:
  CRITICAL_SECTION cs_;
};

class LockGuard
{
public:
  explicit LockGuard(Locker* l)
    : lock_(l)
  {
    lock_->Lock();
  }
  ~LockGuard() { lock_->Unlock(); }

private:
  Locker* lock_;
};

// static global variable
static Locker callstack_locker;
static char log_buffer[64 * 1024];
static char symbol_buffer_1[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
static char symbol_buffer_2[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
static void* dump_buffer = NULL;
#define DUMP_BUFFER_SIZE (5 * 1024 * 1024)

static void log(                                          // NOLINT
  const char* szFile, const char* szLog, size_t log_len)  // NOLINT
{
  HANDLE hfile = NULL;
  time_t tt;
  tm st{};
  char sztime[32] = {0};
  int ret = 0;
  DWORD dw_bytes_written = 0;

  time(&tt);
  ret = localtime_s(&st, &tt);
  if (ret != 0)
  {
    return;
  }

  ret = sprintf_s(sztime, sizeof(sztime), "%04d-%02d-%02d %02d:%02d:%02d ",
    st.tm_year + 1900, st.tm_mon + 1, st.tm_mday, st.tm_hour, st.tm_min,
    st.tm_sec);
  if (ret == -1)
  {
    return;
  }

  hfile = CreateFileA(szFile, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL, NULL);

  if (hfile == INVALID_HANDLE_VALUE)
  {
    return;
  }

  WriteFile(hfile, sztime, ret, &dw_bytes_written, NULL);
  WriteFile(hfile, szLog, static_cast<DWORD>(log_len), &dw_bytes_written, NULL);
  WriteFile(hfile, "\r\n", 2, &dw_bytes_written, NULL);
  CloseHandle(hfile);
}

static void logf(const char* szFileName, const char* fmt, ...)  // NOLINT
{
  int ret = 0;

  va_list arglist;
  va_start(arglist, fmt);
  ret = vsprintf_s(log_buffer, sizeof(log_buffer), fmt, arglist);
  va_end(arglist);
  if (ret < 0)
  {
    return;
  }

  log(szFileName, log_buffer, ret);
}

static void* get_current_context(CONTEXT* context)  // NOLINT
{
  ZeroMemory(context, sizeof(CONTEXT));

#ifdef _M_IX86
  CONTEXT aContext;
  ZeroMemory(&aContext, sizeof(CONTEXT));
  __asm {
		mov dword ptr[aContext.Eax], eax
		mov dword ptr[aContext.Ecx], ecx
		mov dword ptr[aContext.Edx], edx
		mov dword ptr[aContext.Ebx], ebx
		mov dword ptr[aContext.Esi], esi
		mov dword ptr[aContext.Edi], edi
		mov word ptr[aContext.SegSs], ss
		mov word ptr[aContext.SegCs], cs
		mov word ptr[aContext.SegDs], ds
		mov word ptr[aContext.SegEs], es
		mov word ptr[aContext.SegFs], fs
		mov word ptr[aContext.SegGs], gs
		pushfd
		pop[aContext.EFlags]
  }

  aContext.ContextFlags = CONTEXT_CONTROL;
  *context = aContext;
#pragma warning(push)
#pragma warning(disable : 4311)
  context->Eip = (ULONG)_ReturnAddress();
  context->Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
  context->Ebp = *((ULONG*)_AddressOfReturnAddress() - 1);
#elif defined(_M_X64)
  ULONG64 control_pc;
  ULONG64 establisher_frame;
  PRUNTIME_FUNCTION function_entry;
  PVOID handler_data;
  ULONG64 image_base;

  RtlCaptureContext(context);
  control_pc = context->Rip;
  function_entry = RtlLookupFunctionEntry(control_pc, &image_base, NULL);
  if (function_entry != NULL)
  {
    RtlVirtualUnwind(UNW_FLAG_NHANDLER, image_base, control_pc, function_entry,
      context, &handler_data, &establisher_frame, NULL);
  }
  else
  {
    context->Rip = (ULONGLONG)_ReturnAddress();           // NOLINT
    context->Rsp = (ULONGLONG)_AddressOfReturnAddress();  // NOLINT
  }
#elif defined(_M_IA64)
  RtlCaptureContext(context);
#else
#error Architecture is not supported.
#endif

  return _ReturnAddress();
}

static void get_stackframe(STACKFRAME64* frame, CONTEXT* context)  // NOLINT
{
  ZeroMemory(frame, sizeof(STACKFRAME64));

#ifdef _M_IX86
  frame->AddrPC.Offset = context->Eip;
  frame->AddrPC.Mode = AddrModeFlat;
  frame->AddrFrame.Offset = context->Ebp;
  frame->AddrFrame.Mode = AddrModeFlat;
  frame->AddrStack.Offset = context->Esp;
  frame->AddrStack.Mode = AddrModeFlat;
#elif _M_X64
  frame->AddrPC.Offset = context->Rip;
  frame->AddrPC.Mode = AddrModeFlat;
  frame->AddrFrame.Offset = context->Rbp;
  frame->AddrFrame.Mode = AddrModeFlat;
  frame->AddrStack.Offset = context->Rsp;
  frame->AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
  frame->AddrPC.Offset = context->StIIP;
  frame->AddrPC.Mode = AddrModeFlat;
  frame->AddrFrame.Offset = context->IntSp;
  frame->AddrFrame.Mode = AddrModeFlat;
  frame->AddrBStore.Offset = context->RsBSP;
  frame->AddrBStore.Mode = AddrModeFlat;
  frame->AddrStack.Offset = context->IntSp;
  frame->AddrStack.Mode = AddrModeFlat;
#else
#error Architecture is not supported.
#endif
}

static void log_call_stack(                          // NOLINT
  const char* szFileName, CONTEXT* pcontext = NULL)  // NOLINT
{
  CONTEXT context{};
  STACKFRAME64 stack{};
  HANDLE hprocess = GetCurrentProcess();
  HANDLE hthread = GetCurrentThread();

  if (NULL == pcontext)
  {
    get_current_context(&context);
  }
  else
  {
    context = *pcontext;
  }
  get_stackframe(&stack, &context);

  SymCleanup(hprocess);
  SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
  SymInitialize(hprocess, NULL, TRUE);

  for (int frame = 0;; frame++)
  {
    DWORD image_type;
#ifdef _M_IX86
    image_type = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
    image_type = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
    image_type = IMAGE_FILE_MACHINE_IA64;
#else
#error Architecture is not supported.
#endif

    if (!StackWalk64(image_type, hprocess, hthread, &stack, &context, NULL,
          SymFunctionTableAccess64, SymGetModuleBase64, NULL))
    {
      break;
    }

    DWORD64 dw64displacement = 0;
    DWORD dwdisplacement = 0;
    IMAGEHLP_LINE64 line = {};
    ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    DWORD64 dwaddress = stack.AddrPC.Offset;
    SYMBOL_INFO* symbol = (PSYMBOL_INFO)symbol_buffer_1;  // NOLINT
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    BOOL name_ok = SymFromAddr(hprocess, dwaddress, &dw64displacement, symbol);
    BOOL addr_ok =
      SymGetLineFromAddr64(hprocess, dwaddress, &dwdisplacement, &line);

    if (name_ok && addr_ok)
    {
      logf(szFileName, "Frame %d: %s %s line:%u", frame, symbol->Name,
        line.FileName, line.LineNumber);
    }
    else if (name_ok)
    {
      logf(szFileName, "Frame %d: %s", frame, symbol->Name);
    }
    else if (addr_ok)
    {
      logf(szFileName, "Frame %d: %s line:%u", frame, line.FileName,
        line.LineNumber);
    }
  }
}

static void call_stack_to_string(             // NOLINT
  HANDLE hThread, char* output, size_t size)  // NOLINT
{
  CONTEXT context{};
  STACKFRAME64 stack{};
  HANDLE hprocess = GetCurrentProcess();
  bool is_current_thread = (NULL == hThread);
  if (is_current_thread)
  {
    get_current_context(&context);
  }
  else
  {
    ZeroMemory(&context, sizeof(CONTEXT));

    context.ContextFlags = (CONTEXT_FULL);
    if (!GetThreadContext(hThread, &context))
    {
      return;
    }
  }
  get_stackframe(&stack, &context);

  SymCleanup(hprocess);
  SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
  SymInitialize(hprocess, NULL, TRUE);

  size_t pos = 0;
  for (int frame = 0; pos < size; frame++)
  {
    DWORD image_type;
#ifdef _M_IX86
    image_type = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
    image_type = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
    image_type = IMAGE_FILE_MACHINE_IA64;
#else
#error Architecture is not supported.
#endif

    if (!StackWalk64(image_type, hprocess, hThread, &stack, &context, NULL,
          SymFunctionTableAccess64, SymGetModuleBase64, NULL))
    {
      break;
    }

    DWORD64 dw64displacement = 0;
    DWORD dwdisplacement = 0;
    IMAGEHLP_LINE64 line{};
    ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    DWORD64 dwaddress = stack.AddrPC.Offset;
    SYMBOL_INFO* symbol = (PSYMBOL_INFO)symbol_buffer_2;  // NOLINT
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    BOOL name_ok = SymFromAddr(hprocess, dwaddress, &dw64displacement, symbol);
    BOOL addr_ok =
      SymGetLineFromAddr64(hprocess, dwaddress, &dwdisplacement, &line);

    if (name_ok && addr_ok)
    {
      int ret =
        sprintf_s(output + pos, size - pos, "Frame %d: %s %s line:%u\r\n",
          frame, symbol->Name, line.FileName, line.LineNumber);
      if (ret < 0)
      {
        return;
      }
      pos += ret;
    }
    else if (name_ok)
    {
      int ret = sprintf_s(
        output + pos, size - pos, "Frame %d: %s\r\n", frame, symbol->Name);
      if (ret < 0)
      {
        return;
      }
      pos += ret;
    }
    else if (addr_ok)
    {
      int ret = sprintf_s(output + pos, size - pos, "Frame %d: %s line:%u\r\n",
        frame, line.FileName, line.LineNumber);
      if (ret < 0)
      {
        return;
      }
      pos += ret;
    }
  }
}

static void log_exception_callstack(CONTEXT* context = NULL)  // NOLINT
{
  char szfilename[256] = {0};
  int ret = 0;

  ret = sprintf_s(szfilename, sizeof(szfilename), "exception_handler-%u-%u.log",
    GetCurrentProcessId(), GetCurrentThreadId());
  if (ret == -1)
  {
    return;
  }

  log_call_stack(szfilename, context);
}

static std::string s_pre_name;

static void write_minidump(EXCEPTION_POINTERS* pExceptions)  // NOLINT
{
  free(dump_buffer);
  dump_buffer = NULL;

  HANDLE hfile = NULL;
  MINIDUMP_EXCEPTION_INFORMATION mei{};
  MINIDUMP_CALLBACK_INFORMATION mci{};
  HANDLE hprocess = GetCurrentProcess();
  DWORD dwprocessid = GetCurrentProcessId();
  DWORD dwthreadid = GetCurrentThreadId();
  char szfilename[256] = {0};
  int ret = 0;

  ret = sprintf_s(szfilename, sizeof(szfilename), "%s-crashdump-%u-%u-%u.dmp", s_pre_name.c_str(),
    dwprocessid, dwthreadid, GetTickCount());
  if (ret == -1)
  {
    return;
  }

  hfile = CreateFileA(szfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL, NULL);
  if (hfile == INVALID_HANDLE_VALUE)
  {
    return;
  }

  mei.ThreadId = dwthreadid;
  mei.ExceptionPointers = pExceptions;
  mei.ClientPointers = FALSE;
  mci.CallbackRoutine = NULL;
  mci.CallbackParam = NULL;

  MiniDumpWriteDump(hprocess, dwprocessid, hfile,
    static_cast<MINIDUMP_TYPE>(
      MiniDumpWithFullMemory | MiniDumpIgnoreInaccessibleMemory),
    &mei, NULL, &mci);

  CloseHandle(hfile);
}

/*
* dwExceptionCode: custom defined exception code
*				   Don't conflict with system code,
*				   such as STATUS_INVALID_CRUNTIME_PARAMETER etc
*in winnt.h
*/
static void write_minidump_ex(DWORD dwExceptionCode)  // NOLINT
{
  EXCEPTION_RECORD exception{};
  CONTEXT context{};
  EXCEPTION_POINTERS exception_pointers = {&exception, &context};

  void* ret_addr = get_current_context(&context);
  ZeroMemory(&exception, sizeof(EXCEPTION_RECORD));
  exception.ExceptionCode = dwExceptionCode;
  exception.ExceptionAddress = ret_addr;

  write_minidump(&exception_pointers);
}

static LONG WINAPI my_unhandle_exception_filter(   // NOLINT
  struct _EXCEPTION_POINTERS* ptr_exception_info)  // NOLINT
{
  g_LogSystem.Shutdown();
  log_exception_callstack(ptr_exception_info->ContextRecord);
  write_minidump(ptr_exception_info);
  TerminateProcess(GetCurrentProcess(), 1);

  return EXCEPTION_EXECUTE_HANDLER;
}

static void my_invalid_param_handler(const wchar_t*, const wchar_t*,  // NOLINT
  const wchar_t*, unsigned int, uintptr_t)                            // NOLINT
{
	g_LogSystem.Shutdown();
  // do nothing
  return;
}

static void my_purecall_handler()  // NOLINT
{
	g_LogSystem.Shutdown();
  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_PURE_CALL);
  TerminateProcess(GetCurrentProcess(), 1);
}

static int my_new_handler(size_t want_alloc)  // NOLINT
{
	g_LogSystem.Shutdown();
  // TODO(jianxihua): log more info, want_alloc eg.

  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_NEW);
  TerminateProcess(GetCurrentProcess(), 1);
  return 0;
}

static void my_signal_abrt_handle(int signal)  // NOLINT
{
	g_LogSystem.Shutdown();
  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_SIGNAL_ABORT);
  TerminateProcess(GetCurrentProcess(), 1);
}

static void my_signal_fpe_handle(int signal, int error_code)  // NOLINT
{
	g_LogSystem.Shutdown();
  // TODO(jianxihua): error_code check <float.h>, FPE_INVALID ...

  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_SIGNAL_FPE);
  TerminateProcess(GetCurrentProcess(), 1);
}

static void my_terminate_handler()  // NOLINT
{
	g_LogSystem.Shutdown();
  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_TERMINATE);
  TerminateProcess(GetCurrentProcess(), 1);
}

static void my_unexpected_handler()  // NOLINT
{
	g_LogSystem.Shutdown();
  log_exception_callstack();
  write_minidump_ex(CUSTOM_EXCEPTION_CODE_UNEXPECTED);
  TerminateProcess(GetCurrentProcess(), 1);
}

void DumpHelper::Setup(const std::string& pre_name)
{
    s_pre_name = pre_name;
    InitProcessExceptionHandler();
    InitThreadExceptionHandler();
}

void DumpHelper::Shutdown()
{
    if (dump_buffer != NULL)
    {
        free(dump_buffer);
        dump_buffer = NULL;
    }
}

void DumpHelper::InitProcessExceptionHandler()
{
  SetUnhandledExceptionFilter(my_unhandle_exception_filter);
  _set_invalid_parameter_handler(my_invalid_param_handler);
  _set_purecall_handler(my_purecall_handler);
  _set_new_handler(my_new_handler);

#ifndef _DEBUG
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
               SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif
  dump_buffer = malloc(DUMP_BUFFER_SIZE);

  _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
  // https://msdn.microsoft.com/en-us/library/xdkz3x12(v=vs.100)
  signal(SIGABRT, my_signal_abrt_handle);
  typedef void (*SignalHandler)(int);
  signal(SIGFPE, (SignalHandler)my_signal_fpe_handle);  // NOLINT
}

void DumpHelper::InitThreadExceptionHandler()
{
  set_terminate(my_terminate_handler);
  set_unexpected(my_unexpected_handler);
}

void DumpHelper::GetCallStackString(void* thread, char* buffer, size_t size)
{
  if (NULL == buffer || 0 == size)
  {
    return;
  }

  LockGuard guard(&callstack_locker);
  call_stack_to_string(thread, buffer, size);
}

#endif