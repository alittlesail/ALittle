#ifndef ALITTLE_DISPLAYOBJECT_INCLUDED
#define ALITTLE_DISPLAYOBJECT_INCLUDED (1)

extern "C" {
#include "lua.h"
}

#include "LuaBridge/LuaBridge.h"
#include "Carp/carp_matrix_2d.hpp"

class ALittleDisplayObject
{
public:
	ALittleDisplayObject() : m_scale(1.0f, 1.0f) {}
	virtual ~ALittleDisplayObject() { }

public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleDisplayObject>("__CPPAPIDisplayObject")
			.endClass();
	}

public:
	/**
	 *¡¡render
	 */
	virtual void Render(const CarpMatrix2D& parent, bool parent_changed) { }

public:
	virtual void SetVisible(bool visible)
	{
		if (visible == false) m_self_matrix_dirty = true;
		m_visible = visible;
	}
	virtual bool GetVisible() const { return m_visible; }
	virtual void SetClip(bool clip)
	{
		if (clip == true) m_self_matrix_dirty = true;
		m_clip = clip;
	}

public:
	virtual void SetX(float x) { m_pos.x = (float)floor(x); m_self_matrix_dirty = true; }
	virtual int GetX() const { return (int)m_pos.x; }
	virtual void SetY(float y) { m_pos.y = (float)floor(y); m_self_matrix_dirty = true; }
	virtual int GetY() const { return (int)m_pos.y; }

public:
	virtual void SetWidth(float width) { m_size.x = (float)floor(width); m_self_matrix_dirty = true; }
	virtual void SetHeight(float height) { m_size.y = (float)floor(height); m_self_matrix_dirty = true; }
	virtual int GetHeight() { return (int)m_size.y; }

	virtual void SetAngle(float angle)
	{
		m_angle = (float)(3.1415926 * (float)angle / 180.0f);
		m_self_matrix_dirty = true;
	}

	virtual void SetScaleX(float x) { m_scale.x = x; m_self_matrix_dirty = true; }
	virtual void SetScaleY(float y) { m_scale.y = y; m_self_matrix_dirty = true; }

	virtual void SetCenterX(float x) { m_center.x = x; m_self_matrix_dirty = true; }
	virtual void SetCenterY(float y) { m_center.y = y; m_self_matrix_dirty = true; }

public:
	virtual void SetRed(float red) { m_color.r = (unsigned char)(red * 255); }
	virtual void SetGreen(float green) { m_color.g = (unsigned char)(green * 255); }
	virtual void SetBlue(float blue) { m_color.b = (unsigned char)(blue * 255); }
	virtual void SetAlpha(float alpha)
	{
		if (alpha > 1.0f) m_color.a = 255;
		else if (alpha < 0.0f) m_color.a = 0;
		else m_color.a = (unsigned char)(alpha * 255);
		if (m_color.a <= 0) m_self_matrix_dirty = true;
	}

public:
	virtual void SetSelfMatrixDirty() { m_self_matrix_dirty = true; }
	virtual bool UpdateSelfMatrix2D()
	{
		if (!m_self_matrix_dirty) return false;
		m_self_matrix_dirty = false;
		m_vertex_dirty = true;

		m_self_matrix.SetTranslation(-m_center.x, -m_center.y);
		m_self_matrix.Scale(m_scale.x, m_scale.y);
		m_self_matrix.Rotate(m_angle);
		m_self_matrix.Translation(m_pos.x, m_pos.y);

		return true;
	}

	virtual bool UpdateGlobalMatrix2D(const CarpMatrix2D& parent, bool parent_changed)
	{
		const bool self_update = UpdateSelfMatrix2D();
		if (parent_changed || self_update)
		{
			m_global_matrix = m_self_matrix;
			m_global_matrix.Multiply(parent);
			m_vertex_dirty = true;

			return true;
		}

		return false;
	}

	virtual void UpdateTextureCoord() {}
	virtual void UpdateVertexCoord() {}

protected:
	bool m_visible = true;
	bool m_clip = false;

protected:
	CarpVector2D m_pos;
	CarpVector2D m_scale;
	CarpColor4 m_color;
	CarpVector2D m_size;
	CarpVector2D m_center;
	float m_angle = 0.0f;

protected:
	CarpMatrix2D m_self_matrix;
	bool m_self_matrix_dirty = true;
	CarpMatrix2D m_global_matrix;
	bool m_vertex_dirty = true;
	bool m_texture_dirty = true;

public:
	ALittleDisplayObject* m_front_node = nullptr;
	ALittleDisplayObject* m_back_node = nullptr;
};

#endif


