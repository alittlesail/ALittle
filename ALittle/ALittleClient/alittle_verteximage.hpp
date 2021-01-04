#ifndef ALITTLE_VERTEXIMAGE_INCLUDED
#define ALITTLE_VERTEXIMAGE_INCLUDED (1)

#include "alittle_displayobject.hpp"
#include "alittle_texture.hpp"

class ALittleVertexImage : public ALittleDisplayObject
{
public:
	ALittleVertexImage() {}
	~ALittleVertexImage() {}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleVertexImage, ALittleDisplayObject>("__CPPAPIVertexImage")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleVertexImage::SetScaleX)
			.addFunction("SetScaleY", &ALittleVertexImage::SetScaleY)
			.addFunction("SetCenterX", &ALittleVertexImage::SetCenterX)
			.addFunction("SetCenterY", &ALittleVertexImage::SetCenterY)
			.addFunction("SetAngle", &ALittleVertexImage::SetAngle)
			.addFunction("SetX", &ALittleVertexImage::SetX)
			.addFunction("SetY", &ALittleVertexImage::SetY)
			.addFunction("SetWidth", &ALittleVertexImage::SetWidth)
			.addFunction("SetHeight", &ALittleVertexImage::SetHeight)
			.addFunction("SetRed", &ALittleVertexImage::SetRed)
			.addFunction("SetGreen", &ALittleVertexImage::SetGreen)
			.addFunction("SetBlue", &ALittleVertexImage::SetBlue)
			.addFunction("SetAlpha", &ALittleVertexImage::SetAlpha)
			.addFunction("SetTexture", &ALittleVertexImage::SetTexture)
			.addFunction("ClearTexture", &ALittleVertexImage::ClearTexture)
			.addFunction("SetTextureCoord", &ALittleVertexImage::SetTextureCoord)
			.addFunction("SetVisible", &ALittleVertexImage::SetVisible)
			.addFunction("SetClip", &ALittleVertexImage::SetClip)
			.addFunction("SetPosXY", &ALittleVertexImage::SetPosXY)
			.addFunction("SetTexUV", &ALittleVertexImage::SetTexUV)
			.endClass();
	}

	void SetX(float x) override { ALittleDisplayObject::SetX(x); }
	void SetY(float y) override { ALittleDisplayObject::SetY(y); }

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

	void SetTextureCoord(float top, float bottom, float left, float right)
	{
		m_tex_top = top;
		m_tex_bottom = bottom;
		m_tex_left = left;
		m_tex_right = right;

		m_texture_dirty = true;
	}

public:
	void SetTexUV(int index, double u, double v)
	{
		if (index < 0 || index >= 4) return;

		m_texture_coord_logic[index].x = (float)u;
		m_texture_coord_logic[index].y = (float)v;

		m_texture_dirty = true;
	}
	void SetPosXY(int index, double x, double y)
	{
		if (index < 0 || index >= 4) return;

		m_vertex_coord_logic[index].x = (float)x;
		m_vertex_coord_logic[index].y = (float)y;

		m_vertex_dirty = true;
	}

protected:
	virtual void UpdateTextureCoord() override
	{
		if (!m_texture) return;
		if (m_texture->GetWidth() == 0 || m_texture->GetHeight() == 0) return;

		if (!m_texture_dirty) return;
		m_texture_dirty = false;

		double l = m_texture->GetWidth() * m_tex_left;
		double t = m_texture->GetHeight() * m_tex_top;
		double r = m_texture->GetWidth() * m_tex_right;
		double b = m_texture->GetHeight() * m_tex_bottom;

		double w = r - l;
		double h = b - t;

		int index = 0;
		for (int i = 0; i < 4; ++i)
		{
			m_texture_coord[index++] = (float)((m_texture_coord_logic[i].x * w + l) / m_texture->GetWidth());
			m_texture_coord[index++] = (float)((m_texture_coord_logic[i].y * h + t) / m_texture->GetHeight());
		}
	}
	void UpdateVertexCoord() override
	{
		if (!m_vertex_dirty) return;
		m_vertex_dirty = false;

		CarpVector2D coord[4];
		coord[0] = m_vertex_coord_logic[0];
		coord[1] = m_vertex_coord_logic[1];
		coord[2] = m_vertex_coord_logic[2];
		coord[3] = m_vertex_coord_logic[3];

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
		if (m_texture == 0) return;

		UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		m_texture->Render(m_color, m_vertex_coord, m_texture_coord);
	}

private:
	ALittleTexture* m_texture = nullptr;

protected:
	float m_tex_top = 0.0f, m_tex_bottom = 1.0f, m_tex_left = 0.0f, m_tex_right = 1.0f;

protected:
	CarpVector2D m_vertex_coord_logic[4];
	CarpVector2D m_texture_coord_logic[4];

private:
	float m_vertex_coord[4 * 2];
	float m_texture_coord[4 * 2];
};

#endif
