
#include "FontHelper.h"
#include "TextureHelper.h"
#include "ALittle/LibClient/Tool/LocalFile.h"

#include "ALittle/LibCommon/Helper/StringHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}
#include "Carp/carp_font.h"

namespace ALittle
{

int FontHelper::CutTextByWidth(const char* content, int width, carp_font_t* font, int max_width, std::vector<int>* list)
{
	if (font == 0 || content == 0 || width <= 0) return 0;
	int len = (int)strlen(content);
	if (len == 0) return 0;
	
	int acc_width = carp_font_italic_extra_wdith(font);
	unsigned int pre_char = 0;
	int char_count = 0;
	while (len > 0)
	{
		int inc = 0;
		unsigned int c = utf8_GetOneUnicode(content, len, &inc);
		
		acc_width += carp_font_calc_wchar_width(font, c, pre_char);
		if (acc_width > width)
		{
			// 如果一个字符都没有切到，并且大于最大宽度，那么如果留到下一行依然无法切到
			// 所以这里干脆直接切掉
			if (char_count == 0 && acc_width > max_width)
			{
				if (list) list->push_back(acc_width);
				return inc;
			}
			break;
		}
		
		if (list) list->push_back(acc_width);
		pre_char = c;
		content += inc;
		len -= inc;
		char_count += inc;
	}

	return char_count;
}

int FontHelper::CutTextWidth(const char* content, carp_font_t* font)
{
	if (font == 0 || content == 0) return 0;
	int len = (int)strlen(content);
	if (len == 0) return 0;

	int acc_width = carp_font_italic_extra_wdith(font);
	unsigned int pre_char = 0;
	while (len > 0)
	{
		int inc = 0;
		unsigned int c = utf8_GetOneUnicode(content, len, &inc);

		acc_width += carp_font_calc_wchar_width(font, c, pre_char);
		pre_char = c;
		content += inc;
		len -= inc;
	}
	
	return acc_width;
}

carp_font_t* FontHelper::LoadFont(LocalFile* file, int font_size, int font_style)
{
	if (file == nullptr) return nullptr;
	return carp_font_load(file->GetContent(), file->GetSize(), font_size, font_style);
}

void FontHelper::ReleaseFont(carp_font_t* font)
{
	carp_font_free(font);
}

int FontHelper::GetFontHeight(carp_font_t* font)
{
	return carp_font_height(font);
}

int FontHelper::GetFontLineGap(carp_font_t* font)
{
	return carp_font_linegap(font);
}

SDL_Surface* FontHelper::CreateSurface(carp_font_t* font, const char* content)
{
	if (content == 0) return nullptr;

	int len = (int)strlen(content);
	if (len == 0) return nullptr;
	std::vector<unsigned int> unicode_list;
	while (len > 0)
	{
		int inc = 0;
		unicode_list.push_back(utf8_GetOneUnicode(content, len, &inc));
		content += inc;
		len -= inc;
	}
	
	int width = 0;
	int height = 0;
	unsigned char* bitmap = carp_font_create_bitmap(font, unicode_list.data(), unicode_list.size(), &width, &height);
	if (bitmap == nullptr) return nullptr;

	SDL_Surface* surface = TextureHelper::CreateSurface(width, height);
	if (surface == nullptr)
	{
		carp_font_release_bitmap(bitmap);
		return nullptr;
	}

	for (int row = 0; row < height; ++row)
	{
		int offset = row * width;
		for (int col = 0; col < width; ++col)
		{
			unsigned int value = bitmap[offset + col];
			if (value != 0)
			{
				unsigned int color = value << 24 | 0x00FFFFFF;
				TextureHelper::SetSurfacePixel(surface, col, row, color);
			}
		}
	}

	carp_font_release_bitmap(bitmap);
	return surface;
}
	
} // ALittle
