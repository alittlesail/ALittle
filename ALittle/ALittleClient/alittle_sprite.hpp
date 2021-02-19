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
			.addFunction("SetZ", &ALittleSprite::SetZ)
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
			.addFunction("SetRowColCount", &ALittleSprite::SetRowColCount)
			.addFunction("SetRowColIndex", &ALittleSprite::SetRowColIndex)
			.endClass();
	}

	void SetX(float x) override { ALittleImage::SetX(x); }
	void SetY(float y) override { ALittleImage::SetY(y); }
	void SetZ(float z) override { ALittleImage::SetZ(z); }

	void SetWidth(float width) override { ALittleImage::SetWidth(width); }
	void SetHeight(float height) override { ALittleImage::SetHeight(height); }

	void SetAngle(float angle) override { ALittleImage::SetAngle(angle); }

	void SetScaleX(float x) override { ALittleImage::SetScaleX(x); }
	void SetScaleY(float y) override { ALittleImage::SetScaleY(y); }

	void SetCenterX(float x) override { ALittleImage::SetCenterX(x); }
	void SetCenterY(float y) override { ALittleImage::SetCenterY(y); }

	void SetRed(float red) override { ALittleImage::SetRed(red); }
	void SetGreen(float green) override { ALittleImage::SetGreen(green); }
	void SetBlue(float blue) override { ALittleImage::SetBlue(blue); }
	void SetAlpha(float alpha) override { ALittleImage::SetAlpha(alpha); }

	void SetVisible(bool visible) override { ALittleImage::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleImage::SetClip(clip); }

	void SetTexture(ALittleTexture* texture) override { ALittleImage::SetTexture(texture); }
	void ClearTexture() override { ALittleImage::ClearTexture(); }
	void SetTextureCoord(float top, float bottom, float left, float right) override { ALittleImage::SetTextureCoord(top, bottom, left, right); }

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

		m_texture_coord[0] = tex_left_tmp; m_texture_coord[1] = tex_top_tmp;
		m_texture_coord[2] = tex_right_tmp; m_texture_coord[3] = tex_top_tmp;
		m_texture_coord[4] = tex_right_tmp; m_texture_coord[5] = tex_bottom_tmp;
		m_texture_coord[6] = tex_left_tmp; m_texture_coord[7] = tex_bottom_tmp;
	}

private:
	int m_row_count = 1;
	int m_col_count = 1;
	int m_row_index = 0;
	int m_col_index = 0;
};


#endif
