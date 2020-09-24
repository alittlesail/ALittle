
#include "InputHelper.h"

#include "Carp/carp_string.hpp"

#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/Platform/Android/AndroidSystem.h"
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "ALittle/LibClient/Platform/Windows/WindowsSystem.h"

#ifdef _WIN32
#include <windows.h>
#include <imm.h>
#pragma comment(lib, "Imm32.lib")
#endif

namespace ALittle
{

const char* InputHelper::GetIMESelectList()
{
	static std::string s_content;
	s_content = "";

#ifdef _WIN32
	const SDL_SysWMinfo& info = g_RenderSystem.GetSysWMinfo();
	if (info.info.win.window == NULL) return s_content.c_str();
	HIMC hImc = ImmGetContext(info.info.win.window);
	if (hImc == NULL) return s_content.c_str();

	DWORD dwSize = ImmGetCandidateListW(hImc, 0, 0, 0);
	if (dwSize == 0)
	{
		ImmReleaseContext(info.info.win.window, hImc);
		return s_content.c_str();
	}

	wchar_t* pBuf = new wchar_t[dwSize];
	LPCANDIDATELIST pList = (LPCANDIDATELIST)pBuf;  
	dwSize = ImmGetCandidateListW(hImc, 0, pList, dwSize);
	if (dwSize)
	{
		for (DWORD i = 0; i < pList->dwCount; ++i)   
		{
			wchar_t* content = (wchar_t*)(pBuf+pList->dwOffset[pList->dwPageStart+i]);
			if (content == NULL) continue;

			s_content += CarpString::Unicode2UTF8(content);
			if (i+1 < pList->dwCount) s_content.push_back(' ');
		}
	}

	delete[] pBuf;
	ImmReleaseContext(info.info.win.window, hImc);
#endif
	return s_content.c_str();
}

SDL_Rect InputHelper::s_ime_rect;
void InputHelper::SetIMSPos(int x, int y)
{
	s_ime_rect.x = x;
	s_ime_rect.y = y;
	float scale_x = g_RenderSystem.GetScaleX();
	float scale_y = g_RenderSystem.GetScaleY();
	SDL_Rect rect = {(int)(x*scale_x), (int)(y*scale_y), (int)(s_ime_rect.w*scale_x), (int)(s_ime_rect.h*scale_y)};
	SDL_SetTextInputRect(&rect);
}

void InputHelper::SetIMSRect(int x, int y, int width, int height)
{
	s_ime_rect.x = x;
	s_ime_rect.y = y;
	s_ime_rect.w = width;
	s_ime_rect.h = height;
	float scale_x = g_RenderSystem.GetScaleX();
	float scale_y = g_RenderSystem.GetScaleY();
	SDL_Rect rect = {(int)(x*scale_x), (int)(y*scale_y), (int)(s_ime_rect.w*scale_x), (int)(s_ime_rect.h*scale_y)};
	SDL_SetTextInputRect(&rect);
}

SDL_Surface* InputHelper::GetClipboardImage()
{
#ifdef _WIN32
	return Windows_GetClipboardImage();
#elif __ANDROID__
	return Android_GetClipboardImage();
#elif __IPHONEOS__
	return iOS_GetClipboardImage();
#else
	return nullptr;
#endif
}

bool InputHelper::HasClipboardImage()
{
#ifdef _WIN32
	return Windows_HasClipboardImage();
#elif __ANDROID__
	return Android_HasClipboardImage();
#elif __IPHONEOS__
	return iOS_HasClipboardImage();
#else
	return false;
#endif
}

bool InputHelper::SetClipboardImage(SDL_Surface* surface)
{
#ifdef _WIN32
	return Windows_SetClipboardImage(surface);
#elif __ANDROID__
	return Android_SetClipboardImage(surface);
#elif __IPHONEOS__
	return iOS_SetClipboardImage(surface);
#else
	return false;
#endif
}

const char* InputHelper::GetClipboardText()
{
#if __IPHONEOS__
	return iOS_GetClipboardText();
#else
	return SDL_GetClipboardText();
#endif
}

bool InputHelper::HasClipboardText()
{
#if __IPHONEOS__
	return iOS_HasClipboardText();
#else
	return SDL_HasClipboardText() == SDL_TRUE;
#endif
}

bool InputHelper::SetClipboardText(const char* text)
{
#if __IPHONEOS__
	return iOS_SetClipboardText(text);
#else
	return SDL_SetClipboardText(text) == SDL_TRUE;
#endif
}

int InputHelper::GetCursorX()
{
	SDL_Window* window = g_RenderSystem.GetWindow();
	if (!window) return 0;

	int window_x, window_y;
	SDL_GetWindowPosition(window, &window_x, &window_y);
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return window_x + mouse_x;
}

int InputHelper::GetCursorY()
{
	SDL_Window* window = g_RenderSystem.GetWindow();
	if (!window) return 0;

	int window_x, window_y;
	SDL_GetWindowPosition(window, &window_x, &window_y);
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return window_y + mouse_y;
}

SDL_Cursor* InputHelper::s_cursor_arrow = 0;
SDL_Cursor* InputHelper::s_cursor_ibeam = 0;
SDL_Cursor* InputHelper::s_cursor_hand = 0;
SDL_Cursor* InputHelper::s_cursor_hdrag = 0;
SDL_Cursor* InputHelper::s_cursor_vdrag = 0;
SDL_Cursor* InputHelper::s_cursor_hvdrag = 0;
SDL_Cursor* InputHelper::s_cursor_hv2drag = 0;
SDL_Cursor* InputHelper::s_cursor_crossdrag = 0;

void InputHelper::SetEditCursor()
{
	if (s_cursor_ibeam == 0)
		s_cursor_ibeam = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	SDL_SetCursor(s_cursor_ibeam);
}
void InputHelper::SetNormalCursor()
{
	if (s_cursor_arrow == 0)
		s_cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(s_cursor_arrow);
}
void InputHelper::SetHandCursor()
{
	if (s_cursor_hand == 0)
		s_cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(s_cursor_hand);
}
void InputHelper::SetHDragCursor()
{
	if (s_cursor_hdrag == 0)
		s_cursor_hdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
	SDL_SetCursor(s_cursor_hdrag);
}
void InputHelper::SetVDragCursor()
{
	if (s_cursor_vdrag == 0)
		s_cursor_vdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
	SDL_SetCursor(s_cursor_vdrag);
}
void InputHelper::SetHVDragCursor()
{
	if (s_cursor_hvdrag == 0)
		s_cursor_hvdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
	SDL_SetCursor(s_cursor_hvdrag);
}
void InputHelper::SetHV2DragCursor()
{
	if (s_cursor_hv2drag == 0)
		s_cursor_hv2drag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
	SDL_SetCursor(s_cursor_hv2drag);
}
void InputHelper::SetCrossDragCursor()
{
	if (s_cursor_crossdrag == 0)
		s_cursor_crossdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	SDL_SetCursor(s_cursor_crossdrag);
}

void InputHelper::Shutdown()
{
	if (s_cursor_arrow) { SDL_FreeCursor(s_cursor_arrow); s_cursor_arrow = 0; }
	if (s_cursor_ibeam) { SDL_FreeCursor(s_cursor_ibeam); s_cursor_ibeam = 0; }
	if (s_cursor_hand) { SDL_FreeCursor(s_cursor_hand); s_cursor_hand = 0; }
	if (s_cursor_hdrag) { SDL_FreeCursor(s_cursor_hdrag); s_cursor_hdrag = 0; }
	if (s_cursor_vdrag) { SDL_FreeCursor(s_cursor_vdrag); s_cursor_vdrag = 0; }
	if (s_cursor_hvdrag) { SDL_FreeCursor(s_cursor_hvdrag); s_cursor_hvdrag = 0; }
	if (s_cursor_hv2drag) { SDL_FreeCursor(s_cursor_hv2drag); s_cursor_hv2drag = 0; }
	if (s_cursor_crossdrag) { SDL_FreeCursor(s_cursor_crossdrag); s_cursor_crossdrag = 0; }
}

} // ALittle
