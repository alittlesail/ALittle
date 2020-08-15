
#ifndef _ALITTLE_WINDOWSSYSTEM_H_
#define _ALITTLE_WINDOWSSYSTEM_H_

#include <SDL.h>

#ifdef _WIN32

#include <windows.h>

namespace ALittle
{

void Windows_InstallExe(const char* file_path);
void Windows_StartApp(const char* package_name);
void Windows_MoveTaskToBack();
const char* Windows_GetNetworkType();
int Windows_StartNetworkListener();
void Windows_UpdateNetwork(int cur_time);
const char* Windows_GetDeviceID();
int Windows_GetScreenWidth();
int Windows_GetScreenHeight();
void Windows_SystemSelectFile(const char* init_dir);
void Windows_SystemSelectDirectory(const char* init_dir);
void Windows_SystemSaveFile(const char* file_name, const char* init_dir);
void Windows_OpenUrlBySystemBrowser(const char* url);

SDL_Surface* Windows_GetClipboardImage();
bool		 Windows_HasClipboardImage();
bool		 Windows_SetClipboardImage(SDL_Surface* surface);

} // ALittle

#endif // _WIN32

#endif // _ALITTLE_WINDOWSSYSTEM_H_
