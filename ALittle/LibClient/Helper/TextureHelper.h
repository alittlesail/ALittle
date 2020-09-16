
#ifndef _ALITTLE_TEXTUREHELPER_H_
#define _ALITTLE_TEXTUREHELPER_H_

#include <string>
#include <SDL.h>

namespace ALittle
{

class TextureHelper
{
public:
	/**
	 * create surface
	 * @param width
	 * @param height
	 * @return surface
	 */
	static SDL_Surface* CreateSurface(unsigned int width, unsigned int height);
	
	/**
	 * copy surface
	 * @param dest
	 * @param src
	 * @param x
	 * @param y
	 */
	static void	BlitSurface(SDL_Surface* dest, SDL_Surface* src, unsigned int x, unsigned int y);

	/**
	 * copy surface
	 * @param dest
	 * @param src
	 * @param from
	 * @param to
	 */
	static bool	CutBlitSurface(SDL_Surface* dest, SDL_Surface* src, const char* to, const char* from );
	
	/**
	 * get pixel in surface
	 * @param surface
	 * @param x
	 * @param y
	 * @return pixel
	 */
	static unsigned int GetSurfacePixel(SDL_Surface* surface, int x, int y);
	
	/**
	 * set pixel in surface
	 * @param surface
	 * @param x
	 * @param y
	 * @param color
	 */
	static bool SetSurfacePixel(SDL_Surface* surface, int x, int y, unsigned int color);
	static unsigned int GetPixelAlpha(unsigned int color) { return color >> 24; }
	static unsigned int SetPixelAlpha(unsigned int color, unsigned int alpha) { return (color & 0x00ffffff) | (alpha << 24); }
	static unsigned int GetPixelRed(unsigned int color) { return color & 0x000000ff; }
	static unsigned int SetPixelRed(unsigned int color, unsigned int red) { return (color & 0xffffff00) | red; }
	static unsigned int GetPixelGreen(unsigned int color) { return (color & 0x0000ff00) >> 8; }
	static unsigned int SetPixelGreen(unsigned int color, unsigned int green) { return (color & 0xffff00ff) | (green << 8); }
	static unsigned int GetPixelBlue(unsigned int color) { return (color & 0x00ff0000) >> 16; }
	static unsigned int SetPixelBlue(unsigned int color, unsigned int blue) { return (color & 0xff00ffff) | (blue << 16); }

	/**
	* rejust surface's alpha
	* @param surface
	*/
	static void RejustSurfaceAlpha(SDL_Surface* surface);

public:
	/**
	 * load surface
	 * @param file_path
	 * @return surface
	 */
	static SDL_Surface* LoadSurface(const char* file_path);
	static SDL_Surface* LoadImageFromFile(const char* file_path);
	static SDL_Surface* LoadImageFromMemory(const char* mem, size_t len);
	
	/**
	 * get surface width
	 * @return width
	 */
	static unsigned int GetSurfaceWidth(SDL_Surface* surface);
	
	/**
	 * get surface height
	 * @return height
	 */
	static unsigned int GetSurfaceHeight(SDL_Surface* surface);
	
	/**
	 * Get scratchable latex four edges
	 * @param surface
	 * @param edge type, left, right, top, bottom
	 * @return edge size
	 */
	static unsigned int GetSurfaceGrid9(SDL_Surface* surface, const char* type);

public:
	/**
	 * save surface
	 * @param surface
	 * @param file_path
	 * @return succeed or not
	 */
	static bool SaveSurface(SDL_Surface* surface, const char* file_path);
};

} // ALittle

#endif // _ALITTLE_TEXTUREATLASHELPER_H_
