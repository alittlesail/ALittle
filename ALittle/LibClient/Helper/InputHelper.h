
#ifndef _ALITTLE_INPUTHELPER_H_
#define _ALITTLE_INPUTHELPER_H_

#include <string>
#include <vector>

#include <SDL.h>

namespace ALittle
{

class InputHelper
{
public:
	/**
	* IME
	*/
	static const char* GetIMESelectList();
	static void SetIMSPos(int x, int y);
	static void SetIMSRect(int x, int y, int width, int height);
	static SDL_Rect s_ime_rect;

	/**
	* Clipboard
	*/
	static SDL_Surface* GetClipboardImage();
	static bool		 HasClipboardImage();
	static bool		 SetClipboardImage(SDL_Surface* surface);

	static const char* GetClipboardText();
	static bool		 HasClipboardText();
	static bool		 SetClipboardText(const char* text);

	/**
	* Cursor
	*/
	static int GetCursorX();
	static int GetCursorY();

	static void SetEditCursor();
	static void SetNormalCursor();
	static void SetHandCursor();
	static void SetHDragCursor();
	static void SetVDragCursor();
	static void SetHVDragCursor();
	static void SetHV2DragCursor();
	static void SetCrossDragCursor();

	static SDL_Cursor* s_cursor_arrow;
	static SDL_Cursor* s_cursor_ibeam;
	static SDL_Cursor* s_cursor_hand;
	static SDL_Cursor* s_cursor_hdrag;
	static SDL_Cursor* s_cursor_vdrag;
	static SDL_Cursor* s_cursor_hvdrag;
	static SDL_Cursor* s_cursor_hv2drag;
	static SDL_Cursor* s_cursor_crossdrag;

public:
	static void Shutdown();
};

} // ALittle

#endif // _ALITTLE_INPUTHELPER_H_
