
#ifndef _ALITTLE_GRID9IMAGE_H_
#define _ALITTLE_GRID9IMAGE_H_

#include "ALittle/LibClient/RenderSystem/DisplayObject/DisplayObjects.h"
#include "Image.h"

#include <SDL.h>

namespace ALittle
{

class Texture;

class Grid9Image : public DisplayObjects
{
public:
	Grid9Image();
	~Grid9Image();

#ifdef __EMSCRIPTEN__
	void SetX(float x) { DisplayObjects::SetX(x); }
	void SetY(float y) { DisplayObjects::SetY(y); }

	void SetWidth(float width) { DisplayObjects::SetWidth(width); }
	void SetHeight(float height) { DisplayObjects::SetHeight(height); }

	void SetAngle(float angle) { DisplayObjects::SetAngle(angle); }

	void SetScaleX(float x) { DisplayObjects::SetScaleX(x); }
	void SetScaleY(float y) { DisplayObjects::SetScaleY(y); }

	void SetCenterX(float x) { DisplayObjects::SetCenterX(x); }
	void SetCenterY(float y) { DisplayObjects::SetCenterY(y); }

	void SetVisible(bool visible) { DisplayObjects::SetVisible(visible); }
	void SetClip(bool clip) { DisplayObjects::SetClip(clip); }
#endif

public:
	void SetTopSize(float size) { m_logic_top = (int)floor(size); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetBottomSize(float size) { m_logic_bottom = (int)floor(size); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetLeftSize(float size) { m_logic_left = (int)floor(size); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetRightSize(float size) { m_logic_right = (int)floor(size); m_vertex_dirty = true; m_texture_dirty = true; }

public:
	void SetRed(float red)
	{
		m_color.r = (unsigned char)(red * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetRed(red);
	}
	void SetGreen(float green)
	{
		m_color.g = (unsigned char)(green * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetGreen(green);
	}
	void SetBlue(float blue)
	{
		m_color.b = (unsigned char)(blue * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetBlue(blue);
	}
	void SetAlpha(float alpha)
	{
		if (alpha > 1.0f) m_color.a = 255;
		else if (alpha < 0.0f) m_color.a = 0;
		else m_color.a = (unsigned char)(alpha * 255);
		if (m_color.a <= 0) SetSelfMatrixDirty();
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetAlpha(alpha);
	}

public:
	void SetTexture(Texture* texture)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetTexture(texture);

		m_texture = texture;
		m_texture_dirty = true;
	}
	void ClearTexture()
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].ClearTexture();

		m_texture = 0;
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

public:
	void UpdateTextureCoord();
	void UpdateVertexCoord();

private:
	Texture* m_texture;
	Image m_image[3][3];
	int m_flip;

private:
	float m_tex_top, m_tex_bottom, m_tex_left, m_tex_right;
	int m_logic_top, m_logic_bottom, m_logic_left, m_logic_right;
};

} // ALittle

#endif // _ALITTLE_GRID9IMAGE_H_
