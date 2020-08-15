
#ifndef _ALITTLE_ANDROIDSYSTEM_H_
#define _ALITTLE_ANDROIDSYSTEM_H_

#ifdef __ANDROID__

#include "jni.h"
#include <SDL.h>
#include <string>

namespace ALittle
{
std::string Android_jstring2stdstring(JNIEnv* env, jstring jstr);
jstring Android_stdstring2jstring(JNIEnv* env, const char* str);

int Android_InstallAPK(const char* file_path);
int Android_StartAPP(const char* package_name);
const char* Android_GetNetworkType();
int Android_StartNetworkListener();
const char* Android_GetDeviceID();
int Android_MoveTaskToBack();
int Android_GetScreenWidth();
int Android_GetScreenHeight();
int Android_GetStatusBarHeight();
int Android_SystemSelectFile(const char* init_dir);
int Android_SystemSelectDirectory(const char* init_dir);
int Android_SystemSaveFile(const char* file_name, const char* init_dir);

int Android_OpenUrlBySystemBrowser(const char* url);

SDL_Surface* Android_GetClipboardImage();
bool		 Android_HasClipboardImage();
bool		 Android_SetClipboardImage(SDL_Surface* surface);

} // ALittle

extern "C" { 
	JNIEXPORT void JNICALL Java_org_libsdl_app_GlobalFunc_SurfaceResize(JNIEnv *, jobject);
	JNIEXPORT void JNICALL Java_org_libsdl_app_GlobalFunc_J2CLog(JNIEnv *, jobject, jstring);
	JNIEXPORT void JNICALL Java_org_libsdl_app_GlobalFunc_Invoke(JNIEnv *, jobject, jstring, jstring);
}

#endif // __ANDROID__

#endif // _ALITTLE_ANDROIDSYSTEM_H_
