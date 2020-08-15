/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL.h>

#ifdef __IPHONEOS__

#ifndef _ALITTLE_IOSSYSTEM_H_
#define _ALITTLE_IOSSYSTEM_H_

#include <stdio.h>
#include <string>

/* For proper OS X applications, the resources are contained inside the application bundle.
 So the strategy is to first check the application bundle for the file, then fallback to the current working directory.
 Note: One additional corner-case is if the resource is in a framework's resource bundle instead of the app.
 We might want to use bundle identifiers, e.g. org.libsdl.sdl to get the bundle for the framework,
 but we would somehow need to know what the bundle identifiers we need to search are.
 Also, note the bundle layouts are different for iPhone and Mac.
 */

std::string iOS_GetResourcePath();
int iOS_GetScreenWidth();
int iOS_GetScreenHeight();
int iOS_GetStatusBarHeight();
void iOS_SetStatusBarLight();
void iOS_StartAPP(const char* package_name);
const char* iOS_GetNetworkType();
int iOS_StartNetworkListener();
const char* iOS_GetDeviceID();

void iOS_WebViewCreate(int web_id);
void iOS_WebViewRelease(int web_id);
int iOS_WebViewNavigate(int web_id, const std::string& url);
int iOS_WebViewInvokeJs(int web_id, const std::string& method, const std::string& param);
void iOS_WebViewUpdateRect(int web_id, int x, int y, int width, int height);
void iOS_WebViewUpdateVisible(int web_id, int visible);
void iOS_WebViewGoBack(int web_id);
void iOS_WebViewGoForward(int web_id);
void iOS_SystemSelectFile(const char* init_dir);
void iOS_SystemSelectDirectory(const char* init_dir);
void iOS_SystemSaveFile(const char* file_name, const char* init_dir);

void iOS_OpenUrlBySystemBrowser(const char* url);

SDL_Surface* iOS_GetClipboardImage();
bool		 iOS_HasClipboardImage();
bool		 iOS_SetClipboardImage(SDL_Surface* surface);
const char*	 iOS_GetClipboardText();
bool		 iOS_HasClipboardText();
bool		 iOS_SetClipboardText(const char* text);

SDL_Surface* iOS_GetPhoto(const char* file_path);

#endif
#endif
