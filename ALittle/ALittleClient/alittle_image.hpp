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
			.addFunction("SetFlip", &ALittleImage::SetFlip)
			.addFunction("SetX", &ALittleImage::SetX)
			.addFunction("SetY", &ALittleImage::SetY)
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

#ifdef __EMSCRIPTEN__
	void SetX(float x) { DisplayObject::SetX(x); }
	void SetY(float y) { DisplayObject::SetY(y); }

	void SetWidth(float width) { DisplayObject::SetWidth(width); }
	void SetHeight(float height) { DisplayObject::SetHeight(height); }

	void SetAngle(float angle) { DisplayObject::SetAngle(angle); }

	void SetScaleX(float x) { DisplayObject::SetScaleX(x); }
	void SetScaleY(float y) { DisplayObject::SetScaleY(y); }

	void SetCenterX(float x) { DisplayObject::SetCenterX(x); }
	void SetCenterY(float y) { DisplayObject::SetCenterY(y); }

	void SetRed(float red) { DisplayObject::SetRed(red); }
	void SetGreen(float green) { DisplayObject::SetGreen(green); }
	void SetBlue(float blue) { DisplayObject::SetBlue(blue); }
	void SetAlpha(float alpha) { DisplayObject::SetAlpha(alpha); }

	void SetVisible(bool visible) { DisplayObject::SetVisible(visible); }
	void SetClip(bool clip) { DisplayObject::SetClip(clip); }
#endif

public:
	void SetTexture(ALittleTexture* texture)
	{
		if (texture == nullptr) SetSelfMatrixDirty();
		m_texture = texture;
	}
	void ClearTexture()
	{
		m_texture = nullptr;
		SetSelfMatrixDirty();
	}

public:
	void SetTextureCoord(float top, float bottom, float left, float right)
	{
		m_tex_top = top;
		m_tex_bottom = bottom;
		m_tex_left = left;
		m_tex_right = right;

		m_texture_dirty = true;
	}
	void SetFlip(int flip)
	{
		if (m_flip == flip) return;
		m_flip = flip;
		m_texture_dirty = true;
	}

protected:
	void UpdateTextureCoord() override
	{
		if (!m_texture_dirty) return;
		m_texture_dirty = false;

		const float left = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_tex_left : m_tex_right;
		const float right = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_tex_right : m_tex_left;

		const float top = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_tex_top : m_tex_bottom;
		const float bottom = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_tex_bottom : m_tex_top;

		m_texture_coord[0] = left; m_texture_coord[1] = top;
		m_texture_coord[2] = right; m_texture_coord[3] = top;
		m_texture_coord[4] = right; m_texture_coord[5] = bottom;
		m_texture_coord[6] = left; m_texture_coord[7] = bottom;
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
	int m_flip = SDL_FLIP_NONE;

protected:
	float m_tex_top = 0.0f, m_tex_bottom = 1.0f, m_tex_left = 0.0f, m_tex_right = 1.0f;

protected:
	float m_vertex_coord[4 * 2] = {0.0f};
	float m_texture_coord[4 * 2] = { 0.0f };
};

#endif
