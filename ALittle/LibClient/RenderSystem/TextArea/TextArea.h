
#ifndef _ALITTLE_TEXTAREA_H_
#define _ALITTLE_TEXTAREA_H_

#include "ALittle/LibClient/RenderSystem/Image/Image.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace ALittle
{

class Texture;

class TextArea : public Image
{
public:
	TextArea();
	~TextArea();

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
	void SetBold(bool bold);
	void SetUnderline(bool underline);
	void SetDeleteline(bool deleteline);
	void SetItalic(bool italic);
	
public:
	void SetFont(const char* font_path, unsigned int font_size);
	void SetText(const char* text);

public:
	enum HAlign
	{
		HALIGN_LEFT,
		HALIGN_CENTER,
		HALIGN_RIGHT
	};

	enum VAlign
	{
		VALIGN_TOP,
		VALIGN_CENTER,
		VALIGN_BOTTOM
	};

	void SetHAlign(int align);
	void SetVAlign(int align);

public:
	int GetRealHeight();

public:
	void NeedDraw() { m_need_redraw = true; }
	void Render(const Matrix2D& parent, bool parent_changed);

private:
	void Draw(bool draw);

private:
	bool m_need_redraw;

private:
	int m_halign;
	int m_valign;
	int m_real_height;

private:
	std::string m_text;
	unsigned int m_font_style;
	std::string m_font_path;
	unsigned int m_font_size;
	TTF_Font* m_font;
};

} // ALittle

#endif // _ALITTLE_TEXTAREA_H_
