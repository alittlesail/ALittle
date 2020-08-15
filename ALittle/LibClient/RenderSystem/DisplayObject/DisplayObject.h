
#ifndef _ALITTLE_DISPLAYOBJECT_H_
#define _ALITTLE_DISPLAYOBJECT_H_

#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibClient/RenderSystem/Matrix2D.h"

namespace ALittle
{

class DisplayObject
{
public:
	DisplayObject()
		: m_angle(0)
		, m_self_matrix_dirty(true)
		, m_vertex_dirty(true), m_texture_dirty(true)
		, m_visible(true), m_clip(false)
		, m_pos(Vector2D(0.0f, 0.0f))
		, m_size(Vector2D(0.0f, 0.0f))
		, m_scale(Vector2D(1.0f, 1.0f))
		, m_front_node(NULL), m_back_node(NULL) {}
	virtual ~DisplayObject() { }

public:
	/**
	 *¡¡render
	 */
	virtual void Render(const Matrix2D& parent, bool parent_changed) { }

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
	virtual bool UpdateSelfMatrix2D();

	virtual bool UpdateGlobalMatrix2D(const Matrix2D& parent, bool parent_changed);

	virtual void UpdateTextureCoord() {}
	virtual void UpdateVertexCoord() {}

protected:
	bool m_visible;
	bool m_clip;

protected:
	Vector2D m_pos;
	Vector2D m_scale;
	Color4 m_color;
	Vector2D m_size;
	Vector2D m_center;
	float m_angle;

protected:
	Matrix2D m_self_matrix;
	bool m_self_matrix_dirty;
	Matrix2D m_global_matrix;
	bool m_vertex_dirty;
	bool m_texture_dirty;

public:
	DisplayObject* m_front_node;
	DisplayObject* m_back_node;
};

} // ALittle

#endif // _ALITTLE_DISPLAYOBJECT_H_
