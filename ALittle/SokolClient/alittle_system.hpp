#ifndef ALITTLE_SYSTEM_INCLUDED
#define ALITTLE_SYSTEM_INCLUDED (1)

extern "C" {
#include "lua.h"
}
#include "LuaBridge/LuaBridge.h"
#include "Carp/carp_system.h"

#ifdef _WIN32
#include <commdlg.h>
#include <ShlObj.h>
#pragma comment(lib, "Iphlpapi.lib")
#endif

class ALittleSystem
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.addCFunction("__CPPAPI_GetDeviceID", GetDeviceID)
			.addCFunction("__CPPAPI_GetPlatform", GetPlatform)
			.addFunction("__CPPAPI_InstallProgram", CARP_InstallProgram)
			.addFunction("__CPPAPI_GetScreenWidth", CARP_GetScreenWidth)
			.addFunction("__CPPAPI_GetScreenHeight", CARP_GetScreenHeight)
			.addFunction("__CPPAPI_SystemSelectFile", SystemSelectFile)
			.addFunction("__CPPAPI_SystemSelectDirectory", SystemSelectDirectory)
			.addFunction("__CPPAPI_SystemSaveFile", SystemSaveFile)
			.addFunction("__CPPAPI_OpenUrlBySystemBrowser", OpenUrlBySystemBrowser)
			.addFunction("__CPPAPI_Alert", CARP_Alert)
			;
	}

	static int GetPlatform(lua_State* l_state)
	{
		char buffer[128] = { 0 };
		CARP_GetPlatform(buffer, sizeof(buffer));
		lua_pushstring(l_state, buffer);
		return 1;
	}

	static int GetDeviceID(lua_State* l_state)
	{
		char buffer[128] = { 0 };
		CARP_GetDeviceID(buffer, sizeof(buffer));
		lua_pushstring(l_state, buffer);
		return 1;
	}

	static void SystemSelectFile(const char* init_dir)
	{
#ifdef _WIN32
		wchar_t path_name[MAX_PATH] = { 0 };
		OPENFILENAMEW ofn = { OPENFILENAME_SIZE_VERSION_400 };				// or {sizeof (OPENFILENAME)}
		ofn.hwndOwner = (HWND)sapp_win32_get_hwnd();	// set parent window
		ofn.lpstrFilter = NULL;				// not set filter
		ofn.lpstrFile = path_name;			// set path
		ofn.nMaxFile = sizeof(path_name);	// size of buffer
		ofn.lpstrTitle = L"Select File";			// set title
		wchar_t cur_dir[MAX_PATH] = { 0 };
		GetCurrentDirectoryW(sizeof(cur_dir), cur_dir);	// get current path
		std::wstring gbk_dir = cur_dir;
		if (init_dir)
			gbk_dir = CarpString::UTF82Unicode(init_dir);
		ofn.lpstrInitialDir = gbk_dir.c_str();			// init first dir
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
		BOOL bOk = GetOpenFileNameW(&ofn);				// open dialog
		SetCurrentDirectoryW(cur_dir);					// reset old dir

		std::string utf8_path_name = CarpString::Unicode2UTF8(path_name);
		if (bOk)
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectFile", utf8_path_name.c_str());
		else
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectFile");
#endif
	}

	static void SystemSelectDirectory(const char* init_dir)
	{
#ifdef _WIN32
		wchar_t path_name[MAX_PATH] = { 0 };
		BROWSEINFOW bInfo = { 0 };				// or {sizeof (OPENFILENAME)}
		bInfo.hwndOwner = (HWND)sapp_win32_get_hwnd();	// set parent window
		bInfo.lpszTitle = L"Select Directory";			// set title
		bInfo.pszDisplayName = path_name;
		bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI; /*包含一个编辑框 用户可以手动填写路径 对话框可以调整大小之类的..*/
		LPITEMIDLIST lpDlist = SHBrowseForFolderW(&bInfo);
		if (lpDlist != NULL)
		{
			SHGetPathFromIDListW(lpDlist, path_name);
			std::string utf8_path_name = CarpString::Unicode2UTF8(path_name);
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectDirectory", utf8_path_name.c_str());
		}
		else
		{
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectDirectory");
		}
#endif
	}

	static void SystemSaveFile(const char* utf8_file_name, const char* init_dir)
	{
#ifdef _WIN32
		std::wstring file_name;
		if (utf8_file_name) file_name = CarpString::UTF82Unicode(utf8_file_name);

		wchar_t path_name[MAX_PATH];
		OPENFILENAMEW ofn = { OPENFILENAME_SIZE_VERSION_400 };//or  {sizeof (OPENFILENAME)}  
		// lStructSize  
		// 指定这个结构的大小，以字节为单位。  
		// Windows 95/98和Windows NT 4.0：特意为Windows 95/98或Windows NT 4.0，及带有WINVER和_WIN32_WINNT >= 0x0500编译时，  
		//  为这个成员使用OPENFILENAME_SIZE_VERSION_400。  
		// Windows 2000及更高版本：这个参数使用sizeof (OPENFILENAME) 。  
		ofn.hwndOwner = GetForegroundWindow();// 打开OR保存文件对话框的父窗口  
		ofn.lpstrFilter = NULL;
		//过滤器 如果为 NULL 不使用过滤器  
		//具体用法看上面  注意 /0  
		path_name[0] = 0;
		wcscpy_s(path_name, file_name.c_str());
		ofn.lpstrFile = path_name;
		ofn.nMaxFile = sizeof(path_name);//存放用户选择文件的 路径及文件名 缓冲区  
		ofn.lpstrTitle = L"Save File";//选择文件对话框标题  
		wchar_t szCurDir[MAX_PATH];
		GetCurrentDirectoryW(sizeof(szCurDir), szCurDir);
		std::wstring gbk_dir = szCurDir;
		if (init_dir)
			gbk_dir = CarpString::UTF82Unicode(init_dir);
		ofn.lpstrInitialDir = gbk_dir.c_str();			// init first dir
		ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//如果需要选择多个文件 则必须带有  OFN_ALLOWMULTISELECT标志  

		BOOL bOk = GetSaveFileNameW(&ofn);//调用对话框打开文件
		SetCurrentDirectoryW(szCurDir);

		std::string utf8_path_name = CarpString::Unicode2UTF8(path_name);
		if (bOk)
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSaveFile", utf8_path_name.c_str());
		else
			s_alittle_script.Invoke("__ALITTLEAPI_SystemSaveFile");
#endif
	}

	static void OpenUrlBySystemBrowser(const char* url)
	{
		if (url == 0) return;

#ifdef _WIN32
		std::string commond = "start \"\" ";
		commond.append("\"").append(url).append("\"");
		_wsystem(CarpString::UTF82Unicode(commond.c_str()).c_str());
#endif
	}
};

#endif

#ifdef ALITTLE_SYSTEM_IMPL
#define CARP_SYSTEM_IMPL
#include "Carp/carp_system.h"
#endif