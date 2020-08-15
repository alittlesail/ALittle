
#ifndef _ALITTLE_SYSTEMHELPER_H_
#define _ALITTLE_SYSTEMHELPER_H_

#include <string>
#include <vector>

namespace ALittle
{

class SystemHelper
{
public:
	/**
	* alert
	*/
	static void Alert(const char* message);
	/**
	* install param
	*/
	static void InstallProgram(const char* file_path);

	/**
	* start a param
	*/
	static void StartProgram(const char* package_name);

	/**
	* set param to background
	*/
	static void BackProgram();

	/**
	* get device id
	*/
	static const char* GetDeviceID();

	/**
	* screen
	*/
	static int GetScreenWidth();
	static int GetScreenHeight();
	static int GetStatusBarHeight();

	/**
	* system select file
	*/
	static void SystemSelectFile(const char* init_dir);

	/**
	* system select directory
	*/
	static void SystemSelectDirectory(const char* init_dir);

	/**
	* system save file
	*/
	static void SystemSaveFile(const char* file_name, const char* init_dir);

	/**
	* open url by system browser
	*/
	static void OpenUrlBySystemBrowser(const char* url);

	// 获取屏幕模式
	static int GetDisplayOrientation();

private:
	static std::string s_temp_string;
};

} // ALittle

#endif // _ALITTLE_SYSTEMHELPER_H_
