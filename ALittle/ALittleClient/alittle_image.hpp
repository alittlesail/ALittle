#ifndef ALITTLE_IMAGE_INCLUDED
#define ALITTLE_IMAGE_INCLUDED (1)

#include "SDL.h"
#include "alittle_displayobject.hpp"
#include "alittle_texture.hpp"

class ALittleImage : public ALittleDisplayObject
{
public:
	virtual ~ALittleImage() {}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleImage, ALittleDisplayObject>("__CPPAPIImage")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleImage::SetScaleX)
			.addFunction("SetScaleY", &ALittleImage::SetScaleY)
			.addFunction("SetCenterX", &ALittleImage::SetCenterX)
			.addFunction("SetCenterY", &ALittleImage::SetCenterY)
			.addFunction("SetAngle", &ALittleImage::SetAngle)
			.addFunction("SetX", &ALittleImage::SetX)
			.addFunction("SetY", &ALittleImage::SetY)
			.addFunction("SetZ", &ALittleImage::SetZ)
			.addFunction("SetWidth", &ALittleImage::SetWidth)
			.addFunction("SetHeight", &ALittleImage::SetHeight)
			.addFunction("SetRed", &ALittleImage::SetRed)
			.addFunction("SetGreen", &ALittleImage::SetGreen)
			.addFunction("SetBlue", &ALittleImage::SetBlue)
			.addFunction("SetAlpha", &ALittleImage::SetAlpha)
			.addFunction("SetTexture", &ALittleImage::SetTexture)
			.addFunction("ClearTexture", &ALittleImage::ClearTexture)
			.addFunction("SetTextureCoord", &ALittleImage::SetTextureCoord)
			.addFunction("SetVisible", &ALittleImage::SetVisible)
			.addFunction("SetClip", &ALittleImage::SetClip)
			.endClass();

	}

	void SetX(float x) override { ALittleDisplayObject::SetX(x); }
	void SetY(float y) override { ALittleDisplayObject::SetY(y); }
	void SetZ(float z) override { ALittleDisplayObject::SetZ(z); }

	void SetWidth(float width) override { ALittleDisplayObject::SetWidth(width); }
	void SetHeight(float height) override { ALittleDisplayObject::SetHeight(height); }

	void SetAngle(float angle) override { ALittleDisplayObject::SetAngle(angle); }

	void SetScaleX(float x) override { ALittleDisplayObject::SetScaleX(x); }
	void SetScaleY(float y) override { ALittleDisplayObject::SetScaleY(y); }

	void SetCenterX(float x) override { ALittleDisplayObject::SetCenterX(x); }
	void SetCenterY(float y) override { ALittleDisplayObject::SetCenterY(y); }

	void SetRed(float red) override { ALittleDisplayObject::SetRed(red); }
	void SetGreen(float green) override { ALittleDisplayObject::SetGreen(green); }
	void SetBlue(float blue) override { ALittleDisplayObject::SetBlue(blue); }
	void SetAlpha(float alpha) override { ALittleDisplayObject::SetAlpha(alpha); }

	void SetVisible(bool visible) override { ALittleDisplayObject::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleDisplayObject::SetClip(clip); }

public:
	virtual void SetTexture(ALittleTexture* texture)
	{
		if (texture == nullptr) SetSelfMatrixDirty();
		m_texture = texture;
	}
	virtual void ClearTexture()
	{
		m_texture = nullptr;
		SetSelfMatrixDirty();
	}

public:
	virtual void SetTextureCoord(float top, float bottom, float left, float right)
	{
		m_tex_top = top;
		m_tex_bottom = bottom;
		m_tex_left = left;
		m_tex_right = right;

		m_texture_dirty = true;
	}

protected:
	void UpdateTextureCoord() override
	{
		if (!m_texture_dirty) return;
		m_texture_dirty = false;

		m_texture_coord[0] = m_tex_left; m_texture_coord[1] = m_tex_top;
		m_texture_coord[2] = m_tex_right; m_texture_coord[3] = m_tex_top;
		m_texture_coord[4] = m_tex_right; m_texture_coord[5] = m_tex_bottom;
		m_texture_coord[6] = m_tex_left; m_texture_coord[7] = m_tex_bottom;
	}
	
	void UpdateVertexCoord() override
	{
		if (!m_vertex_dirty) return;
		m_vertex_dirty = false;

		CarpVector2D coord[4];
		coord[0].x = 0.0f; coord[0].y = 0.0f;
		coord[1].x = m_size.x; coord[1].y = 0.0f;
		coord[2].x = m_size.x; coord[2].y = m_size.y;
		coord[3].x = 0.0f; coord[3].y = m_size.y;

		int index = 0;
		for (int i = 0; i < 4; ++i)
		{
			coord[i].Multiply(m_global_matrix);
			m_vertex_coord[index++] = coord[i].x;
			m_vertex_coord[index++] = coord[i].y;
		}
	}

public:
	void Render(const CarpMatrix2D& parent, bool parent_changed) override
	{
		if (m_clip) return;
		if (!m_visible) return;
		if (m_color.a <= 0) return;
		if (m_texture == nullptr) return;

		UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
	}

protected:
	ALittleTexture* m_texture = nullptr;

protected:
	float m_tex_top = 0.0f, m_tex_bottom = 1.0f, m_tex_left = 0.0f, m_tex_right = 1.0f;

protected:
	float m_vertex_coord[4 * 2] = {0.0f};
	float m_texture_coord[4 * 2] = { 0.0f };
};

#endif
