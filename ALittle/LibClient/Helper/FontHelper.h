
#ifndef _ALITTLE_FONTHELPER_H_
#define _ALITTLE_FONTHELPER_H_

#include <vector>

#include <SDL_ttf.h>

namespace ALittle
{

class FontHelper
{
public:

	
	/**
	* cut text by width
	* @param content: total text
	* @param remain_width: remain width to cut
	* @param font: TTF_Font object
	* @param max_width: max width to cut
	* @return pos offset from content
	*/
	static int CutTextByWidth(const char* content, int width, TTF_Font* font, int max_width, std::vector<int>* list);

	/**
	* get offset by offset x
	* @param x: x offset from 0
	* @param content: total text
	* @return adjust offset from content
	*/
	static int AdjustCursorPos(int x, const char* content, TTF_Font* font);

	/**
	* set font style
	* @param font
	* @param style
	* @return
	*/
	static void SetFontStyle(TTF_Font* font, int style);
	static void SetFontOutline(TTF_Font* font, int outline);
};

} // ALittle

#endif // _ALITTLE_FONTHELPER_H_
