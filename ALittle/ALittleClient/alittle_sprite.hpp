#ifndef ALITTLE_SPRITE_INCLUDED
#define ALITTLE_SPRITE_INCLUDED

#include "SDL.h"
#include "alittle_displayobject.hpp"
#include "alittle_image.hpp"
#include "alittle_texture.hpp"

class ALittleSprite : public ALittleImage
{
public:
	ALittleSprite() {}
	~ALittleSprite() {}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleSprite, ALittleImage>("__CPPAPISprite")
			.addConstructor<void(*)()>()
			.addFunction("SetX", &ALittleSprite::SetX)
			.addFunction("SetY", &ALittleSprite::SetY)
			.addFunction("SetWidth", &ALittleSprite::SetWidth)
			.addFunction("SetHeight", &ALittleSprite::SetHeight)
			.addFunction("SetRed", &ALittleSprite::SetRed)
			.addFunction("SetGreen", &ALittleSprite::SetGreen)
			.addFunction("SetBlue", &ALittleSprite::SetBlue)
			.addFunction("SetAlpha", &ALittleSprite::SetAlpha)
			.addFunction("SetTexture", &ALittleSprite::SetTexture)
			.addFunction("ClearTexture", &ALittleSprite::ClearTexture)
			.addFunction("SetTextureCoord", &ALittleSprite::SetTextureCoord)
			.addFunction("SetVisible", &ALittleSprite::SetVisible)
			.addFunction("SetClip", &ALittleSprite::SetClip)
			.addFunction("SetScaleX", &ALittleSprite::SetScaleX)
			.addFunction("SetScaleY", &ALittleSprite::SetScaleY)
			.addFunction("SetCenterX", &ALittleSprite::SetCenterX)
			.addFunction("SetCenterY", &ALittleSprite::SetCenterY)
			.addFunction("SetAngle", &ALittleSprite::SetAngle)
			.addFunction("SetFlip", &ALittleSprite::SetFlip)
			.addFunction("SetRowColCount", &ALittleSprite::SetRowColCount)
			.addFunction("SetRowColIndex", &ALittleSprite::SetRowColIndex)
			.endClass();
	}

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
	void ClearTexture() { Image::ClearTexture(); }
	void SetTextureCoord(float top, float bottom, float left, float right) { Image::SetTextureCoord(top, bottom, left, right); }
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
	virtual void UpdateTextureCoord() override
	{
		if (m_texture == nullptr) return;

		const int tex_width = m_texture->GetWidth();
		const int tex_height = m_texture->GetHeight();
		if (tex_width == 0 || tex_height == 0) return;

		if (!m_texture_dirty) return;
		m_texture_dirty = false;

		int row_count = m_row_count;
		if (row_count < 1) row_count = 1;
		int col_count = m_col_count;
		if (col_count < 1) col_count = 1;

		int row_index = m_row_index;
		if (row_index < 0 || row_index >= m_row_count)
			row_index = 0;
		int col_index = m_col_index;
		if (col_index < 0 || col_index >= m_col_count)
			col_index = 0;

		const int tex_left = static_cast<int>(ceil(m_tex_left * tex_width));
		const int tex_right = static_cast<int>(ceil(m_tex_right * tex_width));
		const int tex_top = static_cast<int>(ceil(m_tex_top * tex_height));
		const int tex_bottom = static_cast<int>(ceil(m_tex_bottom * tex_height));

		const int cell_width = (tex_right - tex_left) / col_count;
		const int cell_height = (tex_bottom - tex_top) / row_count;

		float tex_left_tmp = (tex_left + cell_width * col_index) / static_cast<float>(tex_width);
		float tex_right_tmp = (tex_left + cell_width * col_index + cell_width) / static_cast<float>(tex_width);
		float tex_top_tmp = (tex_top + cell_height * row_index) / static_cast<float>(tex_height);
		float tex_bottom_tmp = (tex_top + cell_height * row_index + cell_height) / static_cast<float>(tex_height);

		const float left = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? tex_left_tmp : tex_right_tmp;
		const float right = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? tex_right_tmp : tex_left_tmp;
		const float top = (m_flip & SDL_FLIP_VERTICAL) == 0 ? tex_top_tmp : tex_bottom_tmp;
		const float bottom = (m_flip & SDL_FLIP_VERTICAL) == 0 ? tex_bottom_tmp : tex_top_tmp;

		m_texture_coord[0] = left; m_texture_coord[1] = top;
		m_texture_coord[2] = right; m_texture_coord[3] = top;
		m_texture_coord[4] = right; m_texture_coord[5] = bottom;
		m_texture_coord[6] = left; m_texture_coord[7] = bottom;
	}

private:
	int m_row_count = 1;
	int m_col_count = 1;
	int m_row_index = 0;
	int m_col_index = 0;
};


#endif
