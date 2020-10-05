#ifndef ALITTLE_SYSTEM_INCLUDED
#define ALITTLE_SYSTEM_INCLUDED

#include <SDL.h>

#include "alittle_render.hpp"
#include "Carp/carp_lua.hpp"
#include "Carp/carp_system.h"
#include "Carp/carp_string.hpp"
#include "alittle_script.hpp"

#ifdef _WIN32
#include <commdlg.h>
#include <ShlObj.h>
#pragma comment(lib, "Iphlpapi.lib")
#endif

#ifdef __ANDROID__
#include <jni.h>
#endif

class ALittleSystem
{
public:
	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleSystem>("__CPPAPISystem")
			.addFunction("GetDeviceID", &ALittleSystem::GetDeviceID)
			.addFunction("GetPlatform", &ALittleSystem::GetPlatform)
			.addFunction("InstallProgram", &ALittleSystem::InstallProgram)
			.addFunction("StartProgram", &ALittleSystem::StartProgram)
			.addFunction("GetScreenWidth", &ALittleSystem::GetScreenWidth)
			.addFunction("GetScreenHeight", &ALittleSystem::GetScreenHeight)
			.addFunction("SystemSelectFile", &ALittleSystem::SystemSelectFile)
			.addFunction("SystemSelectDirectory", &ALittleSystem::SystemSelectDirectory)
			.addFunction("SystemSaveFile", &ALittleSystem::SystemSaveFile)
			.addFunction("OpenUrlBySystemBrowser", &ALittleSystem::OpenUrlBySystemBrowser)
			.addFunction("Alert", &ALittleSystem::Alert);
		luabridge::setGlobal(l_state, this, "__CPPAPI_System");
	}

public:
#ifdef __ANDROID__
	static std::string Android_jstring2stdstring(JNIEnv* env, jstring jstr)
	{
		std::string rtn;
		jclass clsstring = env->FindClass("java/lang/String");
		jstring strencode = env->NewStringUTF("utf-8");
		jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
		jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode); // String .getByte("utf-8"); 
		jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
		jsize alen = env->GetArrayLength(barr);

		if (ba && alen > 0) rtn.assign((char*)ba, alen);
		env->ReleaseByteArrayElements(barr, ba, 0);  // release memory

		env->DeleteLocalRef(clsstring);
		env->DeleteLocalRef(strencode);
		env->DeleteLocalRef(barr);
		return rtn;
	}

	static jstring Android_stdstring2jstring(JNIEnv* env, const char* str)
	{
		if (!env || !str) return 0;
		jstring js = env->NewStringUTF(str);
		return js;
	}
#endif
	
public:
	const char* GetPlatform()
	{
		return SDL_GetPlatform();
	}
	
	void Alert(const char* message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", message, NULL);
	}

	void InstallProgram(const char* file_path)
	{
#ifdef __ANDROID__
		JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
		if (jni_env == 0) return;

		jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
		jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_InstallAPK", "(Ljava/lang/String;)I");

		jstring j_file_path = Android_stdstring2jstring(jni_env, file_path);
		int result = jni_env->CallStaticIntMethod(login_api, login_func, j_file_path);

		jni_env->DeleteLocalRef(login_api);
		jni_env->DeleteLocalRef(j_file_path);
#elif __IPHONEOS__
#elif _WIN32
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(NULL, (LPTSTR)file_path, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
#endif
	}

	void StartProgram(const char* package_name)
	{
#ifdef __ANDROID__
		JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
		if (jni_env == 0) return;

		jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
		jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_StartAPP", "(Ljava/lang/String;)I");
		jstring j_package_name = Android_stdstring2jstring(jni_env, package_name);
		int result = jni_env->CallStaticIntMethod(login_api, login_func, j_package_name);

		jni_env->DeleteLocalRef(login_api);
		jni_env->DeleteLocalRef(j_package_name);
#elif __IPHONEOS__
		NSString* path = [NSString stringWithUTF8String : package_name];
		[[UIApplication sharedApplication]openURL:[NSURL URLWithString : path] ];
#elif _WIN32
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(NULL, (LPTSTR)package_name, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
#endif
	}

	/**
	* get device id
	*/
	const char* GetDeviceID()
	{
		if (!m_device_id.empty()) return m_device_id.c_str();
		static char buffer[256] = { 0 };
		Carp_GetDeviceID(buffer, sizeof(buffer));
		m_device_id = buffer;
		return m_device_id.c_str();
	}

	int GetScreenWidth()
	{
		SDL_DisplayMode dm;
		if (SDL_GetDesktopDisplayMode(0, &dm) != 0) return 0;
		return dm.w;
	}
	int GetScreenHeight()
	{
		SDL_DisplayMode dm;
		if (SDL_GetDesktopDisplayMode(0, &dm) != 0) return 0;
		return dm.h;
	}

	void SystemSelectFile(const char* init_dir)
	{
#ifdef _WIN32
		wchar_t path_name[MAX_PATH] = { 0 };
		OPENFILENAMEW ofn = { OPENFILENAME_SIZE_VERSION_400 };				// or {sizeof (OPENFILENAME)}
		ofn.hwndOwner = s_alittle_render.GetSysWMinfo().info.win.window;	// set parent window
		ofn.lpstrFilter = NULL;				// not set filter
		ofn.lpstrFile = path_name;			// set path
		ofn.nMaxFile = sizeof(path_name);	// size of buffer
		ofn.lpstrTitle = L"选择文件";			// set title
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
#else
		s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectFile");
#endif
	}

	void SystemSelectDirectory(const char* init_dir)
	{
#ifdef _WIN32
		wchar_t path_name[MAX_PATH] = { 0 };
		BROWSEINFOW bInfo = { 0 };				// or {sizeof (OPENFILENAME)}
		bInfo.hwndOwner = s_alittle_render.GetSysWMinfo().info.win.window;	// set parent window
		bInfo.lpszTitle = L"选择文件夹";			// set title
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
#else
		s_alittle_script.Invoke("__ALITTLEAPI_SystemSelectDirectory");
#endif
	}

	void SystemSaveFile(const char* utf8_file_name, const char* init_dir)
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
		ofn.hwndOwner = s_alittle_render.GetSysWMinfo().info.win.window;// 打开OR保存文件对话框的父窗口  
		ofn.lpstrFilter = NULL;
		//过滤器 如果为 NULL 不使用过滤器  
		//具体用法看上面  注意 /0  
		path_name[0] = 0;
		wcscpy_s(path_name, file_name.c_str());
		ofn.lpstrFile = path_name;
		ofn.nMaxFile = sizeof(path_name);//存放用户选择文件的 路径及文件名 缓冲区  
		ofn.lpstrTitle = L"保存文件";//选择文件对话框标题  
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
#else
		s_alittle_script.Invoke("__ALITTLEAPI_SystemSaveFile");
#endif
	}

	void OpenUrlBySystemBrowser(const char* url)
	{
		if (url == 0) return;
#ifdef _WIN32
		std::string commond = "start \"\" ";
		commond.append("\"").append(url).append("\"");
		_wsystem(CarpString::UTF82Unicode(commond.c_str()).c_str());
#elif __ANDROID__
		JNIEnv* jni_env = (JNIEnv*)SDL_AndroidGetJNIEnv();
		if (jni_env == 0) return;

		jclass login_api = jni_env->FindClass("org/libsdl/app/GlobalFunc");
		jmethodID login_func = jni_env->GetStaticMethodID(login_api, "C2J_OpenUrlBySystemBrowser", "(Ljava/lang/String;)I");
		jstring j_url = Android_stdstring2jstring(jni_env, url);
		int result = jni_env->CallStaticIntMethod(login_api, login_func, j_url);

		jni_env->DeleteLocalRef(login_api);
		jni_env->DeleteLocalRef(j_url);
#elif __IPHONEOS__
		NSString* ns_url = [NSString stringWithUTF8String : url];
		[[UIApplication sharedApplication]openURL:[NSURL URLWithString : ns_url] ];
#endif
	}

private:
	std::string m_device_id;
};

extern ALittleSystem s_alittle_system;

#endif

#ifdef ALITTLE_SYSTEM_IMPL
#define CARP_SYSTEM_IMPL
#include "Carp/carp_system.h"
ALittleSystem s_alittle_system;
#endif