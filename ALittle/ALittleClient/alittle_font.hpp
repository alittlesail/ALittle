#ifndef ALITTLE_FONT_INCLUDED
#define ALITTLE_FONT_INCLUDED

#include "SDL.h"
#include <map>

#include "Carp/carp_file.hpp"
#include "Carp/carp_font.hpp"
#include "Carp/carp_rwops_bind.hpp"
#include "Carp/carp_surface_bind.hpp"

class ALittleFont
{
public:
	~ALittleFont() { Shutdown(); }
		
public:
	CarpFont* GetFont(const char* font_path, unsigned int font_size, unsigned int font_style)
	{
		// check font path
		if (!font_path) return nullptr;
		std::string font_full_path = font_path;

		// find font
		auto& style_map = m_font_map[font_full_path];
		auto& size_map = style_map[font_style];

		// find font size
		auto size_it = size_map.find(font_size);
		if (size_it != size_map.end())
			return size_it->second;

		// get file name
		std::string font_just_name = CarpFile::GetFileNameByPath(font_full_path);
		std::string font_just_path = font_full_path.substr(0, font_full_path.size() - font_just_name.size());

		CarpFont* font = LoadFont(font_path, font_size, font_style);
		if (font == nullptr)
		{
			// if create failed then use system font
#ifdef _WIN32
			std::string new_font_path = "C:\\Windows\\Fonts\\";
			new_font_path += font_just_name;
			font = LoadFont(new_font_path, font_size, font_style);
#elif __ANDROID__
			CARP_ERROR("create font failed: path(" << font_path << ") can't find or font_size(" << font_size << ") not support " << ", and try /system/fonts/Miui-Regular.ttf");
			std::string new_font_path = "/system/fonts/";
			new_font_path += font_just_name;
			font = LoadFont(new_font_path, font_size, font_style);
#endif
		}
		if (font == nullptr) return nullptr;

		// save font
		size_map[font_size] = font;

		// return font
		return font;
	}

	CarpSurface* CreateSurface(CarpFont* font, const char* content)
	{
		if (content == 0 || font == 0) return nullptr;

		CarpFontBitmap* carp_bitmap = font->CreateBitmapFromUTF8(content, false);
		if (carp_bitmap == nullptr) return nullptr;

		CarpSurface* surface = CarpSurfaceBind::CreateCarpSurface(carp_bitmap->width, carp_bitmap->height);
		if (surface == nullptr)
		{
			delete carp_bitmap;
			return nullptr;
		}

		for (int row = 0; row < carp_bitmap->height; ++row)
		{
			const int offset = row * carp_bitmap->width;
			for (int col = 0; col < carp_bitmap->width; ++col)
			{
				const unsigned int value = carp_bitmap->bitmap[offset + col];
				if (value != 0)
				{
					const unsigned int color = value << 24 | 0x00FFFFFF;
					CarpSurfaceBind::SetCarpSurfacePixel(surface, col, row, color);
				}
			}
		}

		delete carp_bitmap;
		return surface;
	}

	void Shutdown()
	{
		for (auto& font_pair : m_font_map)
			for (auto& style_pair : font_pair.second)
				for (auto& size_pair : style_pair.second)
					delete size_pair.second;
		m_font_map.clear();
		for (auto& pair : m_font_file_map)
			delete pair.second;
		m_font_file_map.clear();
	}
	
private:
	CarpFont* LoadFont(const std::string& font_path, unsigned int font_size, unsigned int font_style)
	{
		CarpLocalFile* file = nullptr;
		const auto it = m_font_file_map.find(font_path);
		if (it == m_font_file_map.end())
		{
			file = new CarpLocalFile();
			file->SetPath(font_path.c_str());
			if (!file->Load(false))
			{
				delete file;
				return nullptr;
			}

			m_font_file_map[font_path] = file;
		}
		else
		{
			file = it->second;
		}

		return new CarpFont(file->GetContent(), file->GetSize(), font_size, font_style);
	}

private:
	// font size map font object
	typedef std::map<unsigned int, CarpFont*> TTF_FontSizeMap;
	// font style map font object
	typedef std::map<unsigned int, TTF_FontSizeMap> TTF_FontStyleMap;
	// font path map TTF_FontMap
	typedef std::map<std::string, TTF_FontStyleMap> TTF_FontMap;
	TTF_FontMap m_font_map;
	std::map<std::string, CarpLocalFile*> m_font_file_map;

};

extern ALittleFont s_alittle_font;

#endif


#ifdef ALITTLE_FONT_IMPL
#ifndef ALITTLE_FONT_IMPL_INCLUDE
#define ALITTLE_FONT_IMPL_INCLUDE
#define CARP_FONT_IMPL
#include "Carp/carp_font.hpp"
ALittleFont s_alittle_font;
#endif
#endif

