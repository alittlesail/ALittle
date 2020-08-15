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

#import "iOSDelegate.h"

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>
#import <AudioToolbox/AudioToolbox.h>

#include <dlfcn.h>
#include "Reachability.h"
#include "KeychainItemWrapper.h"
#include "iOSSystem.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"

std::string iOS_GetResourcePath()
{
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* path = [paths objectAtIndex:0];
    return [path UTF8String];
}

int iOS_GetScreenWidth()
{
	return [[UIScreen mainScreen] bounds].size.width * [UIScreen mainScreen].scale;
}

int iOS_GetScreenHeight()
{
	return [[UIScreen mainScreen] bounds].size.height * [UIScreen mainScreen].scale;
}

int iOS_GetStatusBarHeight()
{
    return [[UIApplication sharedApplication] statusBarFrame].size.height * [UIScreen mainScreen].scale;
}

void iOS_SetStatusBarLight()
{
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
}

void iOS_StartAPP(const char* package_name)
{
    NSString *path = [NSString stringWithUTF8String:package_name];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:path]];
}

const char* iOS_GetNetworkType()
{
    Reachability *r = [Reachability reachabilityWithHostName:@"www.apple.com"];
    switch ([r currentReachabilityStatus]) {
        case NotReachable: return "OtherSystem_NotifyNetwork_none";
        case ReachableViaWWAN: return "OtherSystem_NotifyNetwork_line";
        case ReachableViaWiFi: return "OtherSystem_NotifyNetwork_wifi";
    }
    return 0;
}

const char* iOS_GetDeviceID()
{
    static std::string info;
	if (info.size()) return info.c_str();
	
	KeychainItemWrapper *keyChainWrapper = [[KeychainItemWrapper alloc] initWithIdentifier:@"ALittle" accessGroup:nil];
    NSString *UUID = [keyChainWrapper objectForKey:(id)kSecValueData];

    if (UUID == nil || UUID.length == 0) {
        UUID = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
        [keyChainWrapper setObject:UUID forKey:(id)kSecAttrAccount];
        [keyChainWrapper setObject:UUID forKey:(id)kSecValueData];
    }
    [keyChainWrapper release];
	
	info = [UUID UTF8String]; 
    return info.c_str();
}

static iOSReachabilityDelegate* s_iOS_reachability_delegate = nil;
int iOS_StartNetworkListener()
{
    if (s_iOS_reachability_delegate == nil)
    {
        s_iOS_reachability_delegate = [[iOSReachabilityDelegate alloc] init];
        [s_iOS_reachability_delegate Init];
        [s_iOS_reachability_delegate StartNotify];
    }
    return 0;
}

static iOSAlbumManager* g_iOSAlbumManager = nil;
SDL_Surface* iOS_GetPhoto(const char* file_path)
{
    if (g_iOSAlbumManager == nil)
        g_iOSAlbumManager = [[iOSAlbumManager alloc] init];
    return [g_iOSAlbumManager getPhoto:file_path];
}

void iOS_SystemSelectFile(const char* init_dir)
{
    if (g_iOSAlbumManager == nil)
        g_iOSAlbumManager = [[iOSAlbumManager alloc] init];
    if (![g_iOSAlbumManager openAlbum])
        g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSelectFile");
}

void iOS_SystemSelectDirectory(const char* init_dir)
{
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSaveDirectory");
}

void iOS_SystemSaveFile(const char* file_name, const char* init_dir)
{
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSaveFile");
}

static std::map<int, UIWebView*> s_webview_map;
static iOSWebViewDelegate* s_iOS_webview_delegate = nil;
void iOS_WebViewCreate(int web_id)
{
    UIWebView * view = [[UIWebView alloc]init];
    s_webview_map[web_id] = view;
    if (s_iOS_webview_delegate == nil)
        s_iOS_webview_delegate = [[iOSWebViewDelegate alloc] init];
    
    view.delegate = s_iOS_webview_delegate;
    
    SDL_SysWMinfo sys_info;
    SDL_GetVersion(&sys_info.version);
    if (!SDL_GetWindowWMInfo(g_RenderSystem.GetWindow(), &sys_info))
    {
        ALITTLE_ERROR("SDL_GetWindowWMInfo Failed:" << SDL_GetError());
        return;
    }
    [sys_info.info.uikit.window.rootViewController.view addSubview:view];
}

void iOS_WebViewRelease(int web_id)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return;
    
    SDL_SysWMinfo sys_info;
    SDL_GetVersion(&sys_info.version);
    if (!SDL_GetWindowWMInfo(g_RenderSystem.GetWindow(), &sys_info))
    {
        ALITTLE_ERROR("SDL_GetWindowWMInfo Failed:" << SDL_GetError());
        return;
    }
    
    [sys_info.info.uikit.window willRemoveSubview:it->second];
    
    [it->second release];
	s_webview_map.erase(it);
}

int iOS_WebViewNavigate(int web_id, const std::string& url)
{
    NSString *ns_url = [NSString stringWithUTF8String:url.c_str()];
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return 0;
    [it->second loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:ns_url]]];
    return 0;
}

void StringReplace(std::string &strBase, const std::string& strSrc, const std::string& strDes)
{
    std::string::size_type pos = 0;
    std::string::size_type srcLen = strSrc.size();
    std::string::size_type desLen = strDes.size();
    pos = strBase.find(strSrc, pos);
    while ((pos != std::string::npos))
    {
        strBase.replace(pos, srcLen, strDes);
        pos=strBase.find(strSrc, (pos+desLen));
    }
}

int iOS_WebViewInvokeJs(int web_id, const std::string& method, const std::string& param)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return 0;
    
    std::string new_param = param;
    StringReplace(new_param, "\\", "\\\\");
    StringReplace(new_param, "\"", "\\\"");
    new_param = method + "(\"" + new_param + "\")";
    NSString * jsCode = [NSString stringWithUTF8String:new_param.c_str()];
    [it->second stringByEvaluatingJavaScriptFromString:jsCode];
    return 0;
}

void iOS_WebViewUpdateRect(int web_id, int x, int y, int width, int height)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return;
    
    CGRect rect;
    rect.origin.x = x;
    rect.origin.y = y;
    rect.size.width = width;
    rect.size.height = height;
    [it->second setFrame:rect];
}

void iOS_WebViewUpdateVisible(int web_id, int visible)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return;
    
    BOOL new_visible = visible == 0 ? TRUE : FALSE;
    [it->second setHidden:new_visible];
}

void iOS_WebViewGoBack(int web_id)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return;
    if ([it->second canGoBack]) [it->second goBack];
}

void iOS_WebViewGoForward(int web_id)
{
    std::map<int, UIWebView*>::iterator it = s_webview_map.find(web_id);
    if (it == s_webview_map.end()) return;
    if ([it->second canGoForward]) [it->second goForward];
}

void iOS_OpenUrlBySystemBrowser(const char* url)
{
	if (url == 0) return;
	
    NSString* ns_url = [NSString stringWithUTF8String:url];
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:ns_url]];
}

SDL_Surface* iOS_GetClipboardImage()
{
	return 0;
}

bool iOS_HasClipboardImage()
{
	return false;
}

bool iOS_SetClipboardImage(SDL_Surface* surface)
{
	return false;
}

const char* iOS_GetClipboardText()
{
	static std::string text;
	UIPasteboard* pasteboard = [UIPasteboard generalPasteboard];
    NSString* string = pasteboard.string;
	if (string == nil)
		text = "";
	else
		text = [string UTF8String];
	 
	return text.c_str();
}

bool iOS_HasClipboardText()
{
	UIPasteboard* pasteboard = [UIPasteboard generalPasteboard];
    NSString* string = pasteboard.string;
	return string != nil;
}

bool iOS_SetClipboardText(const char* text)
{
	if (text == 0) return false;
	UIPasteboard* pasteboard = [UIPasteboard generalPasteboard];
	pasteboard.string = [NSString stringWithUTF8String:text];
	return true;
}

#endif /* __MACOSX__ */

/* vi: set ts=4 sw=4 expandtab: */
