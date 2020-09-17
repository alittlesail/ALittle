
#include "FontHelper.h"

#include "ALittle/LibCommon/Helper/StringHelper.h"
extern "C" {
#include "ALittle/LibCommon/ThirdParty/utf8/utf8.h"
}

namespace ALittle
{

void CutTextByWidthCallback(void* data, int width)
{
	std::vector<int>* list = (std::vector<int>*)data;
	list->push_back(width);
}

int FontHelper::CutTextByWidth(const char* content, int width, TTF_Font* font, int max_width, std::vector<int>* list)
{
	if (font == 0 || content == 0 || width <= 0) return 0;
	if (content[0] == 0) return 0;
	
	int text_width = 0, char_count = 0;
	if (list)
		TTF_MeasureUTF8(font, content, width, &text_width, &char_count, CutTextByWidthCallback, list);
	else
		TTF_MeasureUTF8(font, content, width, &text_width, &char_count, 0, 0);
	if (char_count == 0)
	{
		char text[8] = {0};
		int tmp = utf8_GetByteCountOfOneWord(*content);
		memcpy(text, content, tmp);
		TTF_SizeUTF8(font, text, &text_width, 0);
		if (text_width > max_width)
		{
			if (list) list->push_back(text_width);
			return tmp;
		}
	}

	return utf8_CalcByteCountByWordCount(content, 0, char_count);
}

int FontHelper::AdjustCursorPos(int x, const char* content, TTF_Font* font)
{
	if (font == 0 || content == 0) return 0;

	const char* str = content;
	int result = 0;

	std::string calc_text;
	while(true)
	{
		int byte_count = utf8_GetByteCountOfOneWord(*str);
		if (byte_count == 1)
		{
			if (*str == '\0')
			{
				break;
			}
			else if (*str == '\r' || *str == '\t' || *str == '\n')
			{
				str += byte_count;
				continue;
			}
		}

		calc_text.append(str, byte_count);

		int text_width = 0, text_height = 0;
		TTF_SizeUTF8(font, calc_text.c_str(), &text_width, &text_height);
		if (text_width - (text_width - result) / 2 > x) break;

		result = text_width;
		str += byte_count;
	}

	return result;
}

void FontHelper::SetFontStyle(TTF_Font* font, int style)
{
	if (TTF_GetFontStyle(font) == style) return;
	TTF_SetFontStyle(font, style);
}

void FontHelper::SetFontOutline(TTF_Font* font, int outline)
{
	if (TTF_GetFontOutline(font) == outline) return;
	TTF_SetFontOutline(font, outline);
}

} // ALittle
