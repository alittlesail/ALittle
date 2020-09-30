#ifndef ALITTLE_TRIANGLE_INCLUDED
#define ALITTLE_TRIANGLE_INCLUDED (1)

#include "alittle_displayobject.hpp"
#include "alittle_texture.hpp"

class ALittleTriangle : public ALittleDisplayObject
{
public:
	ALittleTriangle() {}
	~ALittleTriangle() {}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleTriangle, ALittleDisplayObject>("__CPPAPITriangle")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleTriangle::SetScaleX)
			.addFunction("SetScaleY", &ALittleTriangle::SetScaleY)
			.addFunction("SetCenterX", &ALittleTriangle::SetCenterX)
			.addFunction("SetCenterY", &ALittleTriangle::SetCenterY)
			.addFunction("SetAngle", &ALittleTriangle::SetAngle)
			.addFunction("SetX", &ALittleTriangle::SetX)
			.addFunction("SetY", &ALittleTriangle::SetY)
			.addFunction("SetWidth", &ALittleTriangle::SetWidth)
			.addFunction("SetHeight", &ALittleTriangle::SetHeight)
			.addFunction("SetRed", &ALittleTriangle::SetRed)
			.addFunction("SetGreen", &ALittleTriangle::SetGreen)
			.addFunction("SetBlue", &ALittleTriangle::SetBlue)
			.addFunction("SetAlpha", &ALittleTriangle::SetAlpha)
			.addFunction("SetTexture", &ALittleTriangle::SetTexture)
			.addFunction("ClearTexture", &ALittleTriangle::ClearTexture)
			.addFunction("SetTextureCoord", &ALittleTriangle::SetTextureCoord)
			.addFunction("SetVisible", &ALittleTriangle::SetVisible)
			.addFunction("SetClip", &ALittleTriangle::SetClip)
			.addFunction("SetPosXY", &ALittleTriangle::SetPosXY)
			.addFunction("SetTexUV", &ALittleTriangle::SetTexUV)
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
		if (index < 0 || index >= 3) return;

		m_texture_coord_logic[index].x = (float)u;
		m_texture_coord_logic[index].y = (float)v;

		m_texture_dirty = true;
	}
	void SetPosXY(int index, double x, double y)
	{
		if (index < 0 || index >= 3) return;

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
		for (int i = 0; i < 3; ++i)
		{
			m_texture_coord[index++] = (float)((m_texture_coord_logic[i].x * w + l) / m_texture->GetWidth());
			m_texture_coord[index++] = (float)((m_texture_coord_logic[i].y * h + t) / m_texture->GetHeight());
		}
	}
	void UpdateVertexCoord() override
	{
		if (!m_vertex_dirty) return;
		m_vertex_dirty = false;

		CarpVector2D coord[3];
		coord[0] = m_vertex_coord_logic[0];
		coord[1] = m_vertex_coord_logic[1];
		coord[2] = m_vertex_coord_logic[2];

		int index = 0;
		for (int i = 0; i < 3; ++i)
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

		m_texture->RenderTriangle(m_color, m_vertex_coord, m_texture_coord);
	}

private:
	ALittleTexture* m_texture = nullptr;

protected:
	float m_tex_top = 0.0f, m_tex_bottom = 1.0f, m_tex_left = 0.0f, m_tex_right = 1.0f;

protected:
	CarpVector2D m_vertex_coord_logic[3];
	CarpVector2D m_texture_coord_logic[3];

private:
	float m_vertex_coord[3 * 2];
	float m_texture_coord[3 * 2];
};

#endif
