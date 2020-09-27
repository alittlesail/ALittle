
#include "TextureHelper.h"

#include <SDL_surface.h>
#include <vector>
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "Carp/carp_string.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace ALittle
{

SDL_Surface* TextureHelper::CreateSurface(unsigned int width, unsigned int height)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int rmask = 0xff000000;
	int gmask = 0x00ff0000;
	int bmask = 0x0000ff00;
	int amask = 0x000000ff;
#else
	int rmask = 0x000000ff;
	int gmask = 0x0000ff00;
	int bmask = 0x00ff0000;
	int amask = 0xff000000;
#endif
	return SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
}

void TextureHelper::BlitSurface(SDL_Surface* dest, SDL_Surface* src, unsigned int x, unsigned int y)
{
	SDL_Rect dst_rect;
	dst_rect.x = x;
	dst_rect.y = y;
	dst_rect.w = src->w;
	dst_rect.h = src->h;
	 
	SDL_BlitSurface(src, NULL, dest, &dst_rect);
}

bool TextureHelper::CutBlitSurface(SDL_Surface* dest, SDL_Surface* src, const char* to, const char* from)
{
	std::vector<std::string> to_list;
	CarpString::Split(to, ",", to_list);
	if (to_list.size() < 4 ) return false;

	std::vector<std::string> from_list;
	CarpString::Split(from, ",", from_list);
	if (from_list.size() < 4 ) return false;

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

unsigned int TextureHelper::GetSurfacePixel(SDL_Surface* surface, int x, int y)
{
	if (surface == 0) return 0;
	if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) return 0;

	int byte_count = surface->pitch / surface->w;
	int cur_offset = y * surface->pitch + x * byte_count;
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

bool TextureHelper::SetSurfacePixel(SDL_Surface* surface, int x, int y, unsigned int color)
{
	if (surface == 0) return false;
	if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) return false;

	int byte_count = surface->pitch / surface->w;
	int cur_offset = y * surface->pitch + x * byte_count;
	unsigned char* cur = (unsigned char*)surface->pixels + cur_offset;

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

void TextureHelper::AdjustSurfaceAlpha(SDL_Surface * surface)
{
	if (surface == 0 || surface->w == 0) return;

	int byte_count = surface->pitch / surface->w;
	if (byte_count != 4) return;

	int row_offset = 0;
	for (int j = 0; j < surface->h; ++j)
	{
		int col_offset = 0;
		for (int i = 0; i < surface->w; ++i)
		{
			unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + row_offset + col_offset;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			if (cur[0] == 0)
			{
				cur[1] = 255;
				cur[2] = 255;
				cur[3] = 255;
			}
#else
			if (cur[3] == 0)
			{
				cur[0] = 255;
				cur[1] = 255;
				cur[2] = 255;
			}
#endif
			col_offset += 4;
		}
		row_offset += surface->pitch;
	}
}

SDL_Surface* TextureHelper::LoadSurface(const char* file_path)
{
#ifdef __IPHONEOS__
	SDL_Surface* surface = LoadImageFromFile(file_path);
	if (surface == 0) surface = iOS_GetPhoto(file_path);
#else
	SDL_Surface* surface = LoadImageFromFile(file_path);
#endif
	if (surface) SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	return surface;
}

SDL_Surface* TextureHelper::LoadImageFromFile(const char* file_path)
{
	int width = 0;
	int height = 0;
	int comp = 0;
	stbi_uc* uc = stbi_load(file_path, &width, &height, &comp, 0);
	if (uc == nullptr) return nullptr;
	SDL_Surface* surface = CreateSurface(width, height);
	if (surface) memcpy(surface->pixels, uc, width * height * comp);
	stbi_image_free(uc);
	return surface;
}

SDL_Surface* TextureHelper::LoadImageFromMemory(const char* mem, size_t len)
{
	int width = 0;
	int height = 0;
	int comp = 0;
	stbi_uc* uc = stbi_load_from_memory((unsigned char*)mem, (int)len, &width, &height, &comp, 0);
	if (uc == nullptr) return nullptr;
	SDL_Surface* surface = CreateSurface(width, height);
	if (surface) memcpy(surface->pixels, uc, width * height * comp);
	stbi_image_free(uc);
	return surface;
}

unsigned int TextureHelper::GetSurfaceWidth(SDL_Surface* surface)
{
	return surface->w;
}

unsigned int TextureHelper::GetSurfaceHeight(SDL_Surface* surface)
{
	return surface->h;
}

bool TextureHelper::SaveSurface(SDL_Surface* surface, const char* file_name)
{
	return stbi_write_png(file_name, surface->w, surface->h, 4, surface->pixels, surface->pitch) != 0;
}

unsigned int TextureHelper::GetSurfaceGrid9(SDL_Surface* surface, const char* type)
{
	if (surface == 0 || type == 0 || surface->w == 0 || surface->h == 0) return 0;

	std::string new_type = type;
	int byte_count = surface->pitch / surface->w;

	if (new_type == "left")
	{
		int left = surface->w / 2;
		while (left)
		{
			int cur_col = left;
			int next_col = left - 1;

			for (int i = 0; i < surface->h; ++i)
			{
				int cur_offset = i * surface->pitch + cur_col * byte_count;
				unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

				int next_offset = i * surface->pitch + next_col * byte_count;
				unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

				for (int k = 0; k < byte_count; ++k)
				{
					if (cur[k] != next[k]) return left;
				}
			}

			-- left;
		}
		return left;
	}
	
	if (new_type == "right")
	{
		int right = surface->w / 2;
		while (right <= surface->w)
		{
			int cur_col = right;
			int next_col = right + 1;

			for (int i = 0; i < surface->h; ++i)
			{
				int cur_offset = i * surface->pitch + cur_col * byte_count;
				unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

				int next_offset = i * surface->pitch + next_col * byte_count;
				unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

				for (int k = 0; k < byte_count; ++k)
				{
					if (cur[k] != next[k])
						return right + 1;
				}
			}

			++ right;
		}

		return right;
	}
	
	if (new_type == "top")
	{
		int top = surface->h / 2;
		while (top)
		{
			int cur_row = top;
			int next_row = top - 1;

			for (int i = 0; i < surface->w; ++i)
			{
				int cur_offset = cur_row * surface->pitch + i * byte_count;
				unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

				int next_offset = next_row * surface->pitch + i * byte_count;
				unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

				for (int k = 0; k < byte_count; ++k)
				{
					if (cur[k] != next[k])
						return top;
				}
			}

			-- top;
		}
		return top;
	}
	
	if (new_type == "bottom")
	{
		int bottom = surface->h / 2;
		while (bottom < surface->h)
		{
			int cur_row = bottom;
			int next_row = bottom + 1;

			for (int i = 0; i < surface->w; ++i)
			{
				int cur_offset = cur_row * surface->pitch + i * byte_count;
				unsigned char* cur = static_cast<unsigned char*>(surface->pixels) + cur_offset;

				int next_offset = next_row * surface->pitch + i * byte_count;
				unsigned char* next = static_cast<unsigned char*>(surface->pixels) + next_offset;

				for (int k = 0; k < byte_count; ++k)
				{
					if (cur[k] != next[k])
						return bottom + 1;
				}
			}

			++ bottom;
		}

		return bottom;
	}

	return 0;
}

} // ALittle