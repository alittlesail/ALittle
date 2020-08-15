
#ifndef _ALITTLE_TRIANGLE_H_
#define _ALITTLE_TRIANGLE_H_

#include "ALittle/LibClient/RenderSystem/DisplayObject/DisplayObject.h"

#include <SDL.h>

namespace ALittle
{

class Texture;

class Triangle : public DisplayObject
{
public:
	Triangle();
	~Triangle();

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
	void SetTexture(Texture* texture)
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
	void SetTexUV(int index, double u, double v);
	void SetPosXY(int index, double x, double y);

protected:
	virtual void UpdateTextureCoord();
	virtual void UpdateVertexCoord();

public:
	virtual void Render(const Matrix2D& parent, bool parent_changed);

private:
	Texture * m_texture;

protected:
	float m_tex_top, m_tex_bottom, m_tex_left, m_tex_right;

protected:
	Vector2D m_vertex_coord_logic[3];
	Vector2D m_texture_coord_logic[3];

private:
	float m_vertex_coord[3 * 2];
	float m_texture_coord[3 * 2];
};

} // ALittle

#endif // _ALITTLE_TRIANGLE_H_
