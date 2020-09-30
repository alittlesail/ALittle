#ifndef ALITTLE_INPUT_INCLUDED
#define ALITTLE_INPUT_INCLUDED (1)

#include <SDL.h>
#include <string>

#include "alittle_render.hpp"
#include "Carp/carp_string.hpp"
#include "Carp/carp_lua.hpp"

#ifdef _WIN32
#include <windows.h>
#include <imm.h>
#pragma comment(lib, "Imm32.lib")
#endif

class ALittleInput
{
public:
	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleInput>("__CPPAPIInputSystem")
			.addFunction("GetClipboardText", &ALittleInput::GetClipboardText)
			.addFunction("SetClipboardText", &ALittleInput::SetClipboardText)
			.addFunction("HasClipboardText", &ALittleInput::HasClipboardText)
			.addFunction("GetIMESelectList", &ALittleInput::GetIMESelectList)
			.addFunction("SetIMEPos", &ALittleInput::SetIMEPos)
			.addFunction("OpenIME", &ALittleInput::StartTextInput)
			.addFunction("CloseIME", &ALittleInput::StopTextInput)
			.addFunction("SetIMERect", &ALittleInput::SetIMERect)
			.addFunction("GetCursorX", &ALittleInput::GetCursorX)
			.addFunction("GetCursorY", &ALittleInput::GetCursorY)
			.addFunction("SetEditCursor", &ALittleInput::SetEditCursor)
			.addFunction("SetNormalCursor", &ALittleInput::SetNormalCursor)
			.addFunction("SetHandCursor", &ALittleInput::SetHandCursor)
			.addFunction("SetHDragCursor", &ALittleInput::SetHDragCursor)
			.addFunction("SetVDragCursor", &ALittleInput::SetVDragCursor)
			.addFunction("SetHVDragCursor", &ALittleInput::SetHVDragCursor)
			.addFunction("SetHV2DragCursor", &ALittleInput::SetHV2DragCursor)
			.addFunction("SetCrossDragCursor", &ALittleInput::SetCrossDragCursor)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_InputSystem");
	}

	void StartTextInput()
	{
		SDL_StartTextInput();
	}

	void StopTextInput()
	{
		SDL_StopTextInput();
	}
	
	const char* GetIMESelectList()
	{
		static std::string s_content;
		s_content = "";

#ifdef _WIN32
		const SDL_SysWMinfo& info = s_alittle_render.GetSysWMinfo();
		if (info.info.win.window == nullptr) return s_content.c_str();
		const HIMC hImc = ImmGetContext(info.info.win.window);
		if (hImc == nullptr) return s_content.c_str();

		DWORD dwSize = ImmGetCandidateListW(hImc, 0, 0, 0);
		if (dwSize == 0)
		{
			ImmReleaseContext(info.info.win.window, hImc);
			return s_content.c_str();
		}

		char* pBuf = new char[dwSize];
		LPCANDIDATELIST pList = reinterpret_cast<LPCANDIDATELIST>(pBuf);
		dwSize = ImmGetCandidateListW(hImc, 0, pList, dwSize);
		if (dwSize)
		{
			for (DWORD i = 0; i < pList->dwCount; ++i)
			{
				wchar_t* content = reinterpret_cast<wchar_t*>(pBuf + pList->dwOffset[pList->dwPageStart + i]);
				if (content == nullptr) continue;

				s_content += CarpString::Unicode2UTF8(content);
				if (i + 1 < pList->dwCount) s_content.push_back(' ');
			}
		}

		delete[] pBuf;
		ImmReleaseContext(info.info.win.window, hImc);
#endif
		return s_content.c_str();
	}

	void SetIMEPos(int x, int y)
	{
		m_ime_rect.x = x;
		m_ime_rect.y = y;
		const float scale_x = s_alittle_render.GetScaleX();
		const float scale_y = s_alittle_render.GetScaleY();
		SDL_Rect rect = { static_cast<int>(x * scale_x), static_cast<int>(y * scale_y), static_cast<int>(m_ime_rect.w * scale_x), static_cast<int>(m_ime_rect.h * scale_y) };
		SDL_SetTextInputRect(&rect);
	}

	void SetIMERect(int x, int y, int width, int height)
	{
		m_ime_rect.x = x;
		m_ime_rect.y = y;
		m_ime_rect.w = width;
		m_ime_rect.h = height;
		const float scale_x = s_alittle_render.GetScaleX();
		const float scale_y = s_alittle_render.GetScaleY();
		SDL_Rect rect = { static_cast<int>(x * scale_x), static_cast<int>(y * scale_y), static_cast<int>(m_ime_rect.w * scale_x), static_cast<int>(m_ime_rect.h * scale_y) };
		SDL_SetTextInputRect(&rect);
	}
	SDL_Rect m_ime_rect = {0};
	
public:
	const char* GetClipboardText()
	{
		return SDL_GetClipboardText();
	}

	bool HasClipboardText() const
	{
		return SDL_HasClipboardText() == SDL_TRUE;
	}

	bool SetClipboardText(const char* text)
	{
		return SDL_SetClipboardText(text) == SDL_TRUE;
	}

	int GetCursorX() const
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		return mouse_x;
	}

	int GetCursorY() const
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		return mouse_y;
	}

	void SetEditCursor()
	{
		if (m_cursor_ibeam == 0)
			m_cursor_ibeam = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
		SDL_SetCursor(m_cursor_ibeam);
	}
	void SetNormalCursor()
	{
		if (m_cursor_arrow == 0)
			m_cursor_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		SDL_SetCursor(m_cursor_arrow);
	}
	void SetHandCursor()
	{
		if (m_cursor_hand == 0)
			m_cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		SDL_SetCursor(m_cursor_hand);
	}
	void SetHDragCursor()
	{
		if (m_cursor_hdrag == 0)
			m_cursor_hdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
		SDL_SetCursor(m_cursor_hdrag);
	}
	void SetVDragCursor()
	{
		if (m_cursor_vdrag == 0)
			m_cursor_vdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
		SDL_SetCursor(m_cursor_vdrag);
	}
	void SetHVDragCursor()
	{
		if (m_cursor_hvdrag == 0)
			m_cursor_hvdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
		SDL_SetCursor(m_cursor_hvdrag);
	}
	void SetHV2DragCursor()
	{
		if (m_cursor_hv2drag == 0)
			m_cursor_hv2drag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
		SDL_SetCursor(m_cursor_hv2drag);
	}
	void SetCrossDragCursor()
	{
		if (m_cursor_crossdrag == 0)
			m_cursor_crossdrag = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
		SDL_SetCursor(m_cursor_crossdrag);
	}

	SDL_Cursor* m_cursor_arrow = nullptr;
	SDL_Cursor* m_cursor_ibeam = nullptr;
	SDL_Cursor* m_cursor_hand = nullptr;
	SDL_Cursor* m_cursor_hdrag = nullptr;
	SDL_Cursor* m_cursor_vdrag = nullptr;
	SDL_Cursor* m_cursor_hvdrag = nullptr;
	SDL_Cursor* m_cursor_hv2drag = nullptr;
	SDL_Cursor* m_cursor_crossdrag = nullptr;

public:
	void Shutdown()
	{
		if (m_cursor_arrow) { SDL_FreeCursor(m_cursor_arrow); m_cursor_arrow = nullptr; }
		if (m_cursor_ibeam) { SDL_FreeCursor(m_cursor_ibeam); m_cursor_ibeam = nullptr; }
		if (m_cursor_hand) { SDL_FreeCursor(m_cursor_hand); m_cursor_hand = nullptr; }
		if (m_cursor_hdrag) { SDL_FreeCursor(m_cursor_hdrag); m_cursor_hdrag = nullptr; }
		if (m_cursor_vdrag) { SDL_FreeCursor(m_cursor_vdrag); m_cursor_vdrag = nullptr; }
		if (m_cursor_hvdrag) { SDL_FreeCursor(m_cursor_hvdrag); m_cursor_hvdrag = nullptr; }
		if (m_cursor_hv2drag) { SDL_FreeCursor(m_cursor_hv2drag); m_cursor_hv2drag = nullptr; }
		if (m_cursor_crossdrag) { SDL_FreeCursor(m_cursor_crossdrag); m_cursor_crossdrag = nullptr; }
	}
};

extern ALittleInput s_alittle_input;

#endif

#ifdef ALITTLE_INPUT_IMPL
#ifndef ALITTLE_INPUT_IMPL_INCLUDE
#define ALITTLE_INPUT_IMPL_INCLUDE
ALittleInput s_alittle_input;
#endif
#endif
