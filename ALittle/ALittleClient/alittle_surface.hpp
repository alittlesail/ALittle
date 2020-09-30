#ifndef ALITTLE_SURFACE_INCLUDED
#define ALITTLE_SURFACE_INCLUDED (1)

#include "SDL.h"
#include <string>
#include <vector>
#include <stb/stb_image.h>

#include "Carp/carp_string.hpp"

#include "Carp/carp_rwops.hpp"
#include "stb/stb_image_write.h"

class ALittleSurface
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<SDL_Surface>("__CPPAPISurface")
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.addFunction("__CPPAPI_CreateSurface", CreateSurface)
			.addFunction("__CPPAPI_FreeSurface", SDL_FreeSurface)
			.addFunction("__CPPAPI_BlitSurface", BlitSurface)
			.addFunction("__CPPAPI_LoadSurface", LoadSurfaceForLua)
			.addFunction("__CPPAPI_SaveSurface", SaveSurface)
			.addFunction("__CPPAPI_GetSurfaceWidth", GetSurfaceWidth)
			.addFunction("__CPPAPI_GetSurfaceHeight", GetSurfaceHeight)
			.addFunction("__CPPAPI_CutBlitSurface", CutBlitSurface)
			.addFunction("__CPPAPI_GetSurfaceGrid9", GetSurfaceGrid9)
			.addFunction("__CPPAPI_GetSurfacePixel", GetSurfacePixel)
			.addFunction("__CPPAPI_SetSurfacePixel", SetSurfacePixel)
			.addFunction("__CPPAPI_GetPixelAlpha", GetPixelAlpha)
			.addFunction("__CPPAPI_SetPixelAlpha", SetPixelAlpha)
			.addFunction("__CPPAPI_GetPixelRed", GetPixelRed)
			.addFunction("__CPPAPI_SetPixelRed", SetPixelRed)
			.addFunction("__CPPAPI_GetPixelGreen", GetPixelGreen)
			.addFunction("__CPPAPI_SetPixelGreen", SetPixelGreen)
			.addFunction("__CPPAPI_GetPixelBlue", GetPixelBlue)
			.addFunction("__CPPAPI_SetPixelBlue", SetPixelBlue)
			;
	}
	
public:
	/**
	 * create surface
	 * @param width
	 * @param height
	 * @return surface
	 */
	static SDL_Surface* CreateSurface(unsigned int width, unsigned int height)
	{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		const int rmask = 0xff000000;
		const int gmask = 0x00ff0000;
		const int bmask = 0x0000ff00;
		const int amask = 0x000000ff;
#else
		const int rmask = 0x000000ff;
		const int gmask = 0x0000ff00;
		const int bmask = 0x00ff0000;
		const int amask = 0xff000000;
#endif
		return SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	}

	/**
	 * copy surface
	 * @param dest
	 * @param src
	 * @param x
	 * @param y
	 */
	static void	BlitSurface(SDL_Surface* dest, SDL_Surface* src, unsigned int x, unsigned int y)
	{
		SDL_Rect dst_rect;
		dst_rect.x = x;
		dst_rect.y = y;
		dst_rect.w = src->w;
		dst_rect.h = src->h;

		SDL_BlitSurface(src, nullptr, dest, &dst_rect);
	}

	/**
	 * copy surface
	 * @param dest
	 * @param src
	 * @param from
	 * @param to
	 */
	static bool	CutBlitSurface(SDL_Surface* dest, SDL_Surface* src, const char* to, const char* from)
	{
		std::vector<std::string> to_list;
		CarpString::Split(to, ",", to_list);
		if (to_list.size() < 4) return false;

		std::vector<std::string> from_list;
		CarpString::Split(from, ",", from_list);
		if (from_list.size() < 4) return false;

		SDL_Rect dst_rect;
		dst_rect.x = atoi(to_list[0].c_str());
		dst_rect.y = atoi(to_list[1].c_str());
		dst_rect.w = atoi(to_list[2].c_str());
		dst_rect.h = atoi(to_list[3].c_str());

		SDL_Rect src_rect;
		src_rect.x = atoi(from_list[0].c_str());
		src_rect.y = atoi(from_list[1].c_str());
		src_rect.w = atoi(from_list[2].c_str());
		src_rect.h = atoi(from_list[3].c_str());

		SDL_BlitScaled(src, &src_rect, dest, &dst_rect);

		return true;
	}

	/**
	 * get pixel in surface
	 * @param surface
	 * @param x
	 * @param y
	 * @return pixel
	 */
	static unsigned int GetSurfacePixel(SDL_Surface* surface, int x, int y)
	{
		if (surface == 0) return 0;
		if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) return 0;

		const int byte_count = surface->pitch / surface->w;
		const int cur_offset = y * surface->pitch + x * byte_count;
		unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

		if (byte_count == 1)
			return *cur;
		else if (byte_count == 2)
		{
			unsigned short value;
			memcpy(&value, cur, sizeof(value));
			return value;
		}
		else
		{
			unsigned int value;
			memcpy(&value, cur, sizeof(value));
			return value;
		}
	}

	/**
	 * set pixel in surface
	 * @param surface
	 * @param x
	 * @param y
	 * @param color
	 */
	static bool SetSurfacePixel(SDL_Surface* surface, int x, int y, unsigned int color)
	{
		if (surface == 0) return false;
		if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) return false;

		const int byte_count = surface->pitch / surface->w;
		const int cur_offset = y * surface->pitch + x * byte_count;
		unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

		if (byte_count == 1)
			*cur = static_cast<unsigned char>(color);
		else if (byte_count == 2)
		{
			unsigned short value = static_cast<unsigned short>(color);
			memcpy(cur, &value, sizeof(value));
		}
		else
		{
			memcpy(cur, &color, sizeof(color));
		}

		return true;
	}
	static unsigned int GetPixelAlpha(unsigned int color) { return color >> 24; }
	static unsigned int SetPixelAlpha(unsigned int color, unsigned int alpha) { return (color & 0x00ffffff) | (alpha << 24); }
	static unsigned int GetPixelRed(unsigned int color) { return color & 0x000000ff; }
	static unsigned int SetPixelRed(unsigned int color, unsigned int red) { return (color & 0xffffff00) | red; }
	static unsigned int GetPixelGreen(unsigned int color) { return (color & 0x0000ff00) >> 8; }
	static unsigned int SetPixelGreen(unsigned int color, unsigned int green) { return (color & 0xffff00ff) | (green << 8); }
	static unsigned int GetPixelBlue(unsigned int color) { return (color & 0x00ff0000) >> 16; }
	static unsigned int SetPixelBlue(unsigned int color, unsigned int blue) { return (color & 0xff00ffff) | (blue << 16); }

public:
	/**
	 * load surface
	 * @param file_path
	 * @return surface
	 */
	static SDL_Surface* LoadSurfaceForLua(const char* file_path) { return LoadSurface(file_path); }
	static SDL_Surface* LoadSurface(const char* file_path)
	{
		CarpLocalFile file;
		file.SetPath(file_path);
		if (!file.Load(false)) return nullptr;
		return LoadSurface(file);
	}
	
	static SDL_Surface* LoadSurface(const CarpLocalFile& file)
	{
		int width = 0;
		int height = 0;
		int comp = 0;
		stbi_uc* uc = stbi_load_from_memory((unsigned char*)file.GetContent(), (int)file.GetSize(), &width, &height, &comp, 4);
		if (uc == nullptr) return nullptr;
		if (comp != 4)
		{
			stbi_image_free(uc);
			return nullptr;
		}
		SDL_Surface* surface = CreateSurface(width, height);
		if (surface)
		{
			memcpy(surface->pixels, uc, width * height * comp);
			SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
		}
		stbi_image_free(uc);
		return surface;
	}

	/**
	 * get surface width
	 * @return width
	 */
	static unsigned int GetSurfaceWidth(SDL_Surface* surface) { return surface->w; }

	/**
	 * get surface height
	 * @return height
	 */
	static unsigned int GetSurfaceHeight(SDL_Surface* surface) { return surface->h; }

	/**
	 * Get scratchable latex four edges
	 * @param surface
	 * @param type left, right, top, bottom
	 * @return edge size
	 */
	static unsigned int GetSurfaceGrid9(SDL_Surface* surface, const char* type)
	{
		if (surface == nullptr || type == nullptr || surface->w == 0 || surface->h == 0) return 0;

		const std::string new_type = type;
		const int byte_count = surface->pitch / surface->w;

		if (new_type == "left")
		{
			int col = surface->w / 2;
			while (col)
			{
				for (int row = 0; row < surface->h; ++row)
				{
					const int cur_offset = row * surface->pitch + col * byte_count;
					unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

					const int next_offset = row * surface->pitch + (col - 1) * byte_count;
					unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

					for (int k = 0; k < byte_count; ++k)
					{
						if (cur[k] != next[k]) return col;
					}
				}
				--col;
			}
			return col;
		}

		if (new_type == "right")
		{
			int col = surface->w / 2;
			while (col + 1 < surface->w)
			{
				for (int row = 0; row < surface->h; ++row)
				{
					const int cur_offset = row * surface->pitch + col * byte_count;
					unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

					const int next_offset = row * surface->pitch + (col + 1) * byte_count;
					unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

					for (int k = 0; k < byte_count; ++k)
					{
						if (cur[k] != next[k])
							return col;
					}
				}
				++col;
			}
			return col;
		}

		if (new_type == "top")
		{
			int row = surface->h / 2;
			while (row)
			{
				for (int col = 0; col < surface->w; ++col)
				{
					const int cur_offset = row * surface->pitch + col * byte_count;
					unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

					const int next_offset = (row - 1) * surface->pitch + col * byte_count;
					unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

					for (int k = 0; k < byte_count; ++k)
					{
						if (cur[k] != next[k])
							return row;
					}
				}
				--row;
			}
			return row;
		}

		if (new_type == "bottom")
		{
			int row = surface->h / 2;
			while (row + 1 < surface->h)
			{
				for (int col = 0; col < surface->w; ++col)
				{
					const int cur_offset = row * surface->pitch + col * byte_count;
					unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

					const int next_offset = (row + 1) * surface->pitch + col * byte_count;
					unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

					for (int k = 0; k < byte_count; ++k)
					{
						if (cur[k] != next[k])
							return row;
					}
				}
				++row;
			}
			return row;
		}

		return 0;
	}

public:
	/**
	 * save surface
	 * @param surface
	 * @param file_path
	 * @return succeed or not
	 */
	static bool SaveSurface(SDL_Surface* surface, const char* file_path)
	{
		return stbi_write_png(file_path, surface->w, surface->h, 4, surface->pixels, surface->pitch) != 0;
	}
};
#endif

#ifdef ALITTLE_SURFACE_IMPL
#ifndef ALITTLE_SURFACE_IMPL_INCLUDE
#define ALITTLE_SURFACE_IMPL_INCLUDE
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#endif
#endif