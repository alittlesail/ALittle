
#ifndef _ALITTLE_TEXT_H_
#define _ALITTLE_TEXT_H_

#include "ALittle/LibClient/RenderSystem/Image/Image.h"

#include <string>
#include <unordered_map>

class CarpFont;

namespace ALittle
{

class Texture;

class TextTextureInfo
{
public:
	TextTextureInfo() : font(0), texture(0), ref_count(0) {}
	Texture* texture;
	CarpFont* font;
	int ref_count;
	std::string text;
};

class Text : public Image
{
public:
	Text();
	~Text();

#ifdef __EMSCRIPTEN__
	void SetX(float x) { Image::SetX(x); }
	void SetY(float y) { Image::SetY(y); }

	void SetWidth(float width) { Image::SetWidth(width); }
	void SetHeight(float height) { Image::SetHeight(height); }

	void SetAngle(float angle) { Image::SetAngle(angle); }

	void SetScaleX(float x) { Image::SetScaleX(x); }
	void SetScaleY(float y) { Image::SetScaleY(y); }

	void SetCenterX(float x) { Image::SetCenterX(x); }
	void SetCenterY(float y) { Image::SetCenterY(y); }

	void SetRed(float red) { Image::SetRed(red); }
	void SetGreen(float green) { Image::SetGreen(green); }
	void SetBlue(float blue) { Image::SetBlue(blue); }
	void SetAlpha(float alpha) { Image::SetAlpha(alpha); }

	void SetVisible(bool visible) { Image::SetVisible(visible); }
	void SetClip(bool clip) { Image::SetClip(clip); }

	void SetFlip(int flip) { Image::SetFlip(flip); }
#endif

public:
	unsigned int GetRealWidth();
	unsigned int GetRealHeight();
	void AdjustSize();

public:
	void SetBold(bool bold);
	void SetUnderline(bool underline);
	void SetDeleteline(bool deleteline);
	void SetItalic(bool italic);

public:
	void SetFont(const char* font_path, unsigned int font_size);
	void SetText(const char* text);
	int GetFontHeight();
	int CutTextByWidth(float width, const char* content, int max_width);
	int GetCutWidthListCount() {return static_cast<int>(m_calc_width_list.size()); }
	int GetCutWidthByIndex(int index) { return m_calc_width_list[index]; }
	void ClearCutWidthCache() { m_calc_width_list.clear();}
	int CalcTextWidth(const char* content);
	
public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const Matrix2D& parent, bool parent_changed);

private:
	void Draw();

private:
	bool m_need_redraw;
	TextTextureInfo* m_texture_info;

private:
	bool	m_calc_real_size;
	unsigned int m_real_width, m_real_height;

private:
	std::string m_text;
	unsigned int m_font_style;
	std::string m_font_path;
	unsigned int m_font_size;
	CarpFont* m_font;

private:
	std::vector<int> m_calc_width_list;

private:
	static TextTextureInfo* CreateTextureInfo(CarpFont* font, const std::string& text);
	static void ReleaseTextureInfo(TextTextureInfo* info);
	static std::unordered_map<CarpFont*, std::unordered_map<std::string, TextTextureInfo*>> s_texture_map;
};

} // ALittle

#endif // _ALITTLE_TEXT_H_
