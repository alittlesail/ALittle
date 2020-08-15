
#ifndef _ALITTLE_SPRITE_H_
#define _ALITTLE_SPRITE_H_

#include "Image.h"

#include <SDL.h>

namespace ALittle
{

class Sprite : public Image
{
public:
	Sprite();
	~Sprite();

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

	void SetTexture(Texture* texture) { Image::SetTexture(texture); }
	void ClearTexture() { Image::ClearTexture();  }
	void SetTextureCoord(float top, float bottom, float left, float right) { Image::SetTextureCoord(top, bottom, left, right);  }
	void SetFlip(int flip) { Image::SetFlip(flip); }
#endif

public:
	void SetRowColCount(int row, int col)
	{
		m_row_count = row;
		m_col_count = col;
		m_texture_dirty = true;
	}
	void SetRowColIndex(int row, int col)
	{
		m_row_index = row - 1;
		m_col_index = col - 1;
		m_texture_dirty = true;
	}

public:
	virtual void UpdateTextureCoord();

private:
	int m_row_count;
	int m_col_count;
	int m_row_index;
	int m_col_index;
};

} // ALittle

#endif // _ALITTLE_SPRITE_H_
