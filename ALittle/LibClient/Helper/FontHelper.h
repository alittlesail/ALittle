
#ifndef _ALITTLE_FONTHELPER_H_
#define _ALITTLE_FONTHELPER_H_

#include <SDL_surface.h>
#include <vector>

typedef struct _carp_font_t carp_font_t;

#define CARP_FONT_STYLE_NORMAL 0
#define CARP_FONT_STYLE_BOLD 1
#define CARP_FONT_STYLE_ITALIC 2
#define CARP_FONT_STYLE_UNDERLINE 4
#define CARP_FONT_STYLE_DELETELINE 8

namespace ALittle
{
class LocalFile;

class FontHelper
{
public:
	static carp_font_t* LoadFont(LocalFile* file, int font_size, int font_style);
	static void ReleaseFont(carp_font_t* font);
	static int GetFontHeight(carp_font_t* font);
	static int GetFontLineGap(carp_font_t* font);

	static SDL_Surface* CreateSurface(carp_font_t* font, const char* content);
	
	/**
	* cut text by width
	* @param content: total text
	* @param width: remain width to cut
	* @param font: carp_font_t object
	* @param max_width: max width to cut
	* @return pos offset from content
	*/
	static int CutTextByWidth(const char* content, int width, carp_font_t* font, int max_width, std::vector<int>* list);

	/**
	* cut text width
	* @param content: total text
	* @param font: carp_font_t object
	*/
	static int CutTextWidth(const char* content, carp_font_t* font);
};

} // ALittle

#endif // _ALITTLE_FONTHELPER_H_
