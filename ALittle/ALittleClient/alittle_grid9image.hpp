#ifndef ALITTLE_GRID9IMAGE_INCLUDED
#define ALITTLE_GRID9IMAGE_INCLUDED

#include "alittle_display.hpp"
#include "alittle_displayobject.hpp"
#include "alittle_texture.hpp"
#include "alittle_image.hpp"

class ALittleGrid9Image : public ALittleDisplayObjects
{
public:
	ALittleGrid9Image()
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				AddChild(&(m_image[i][j]));
	}
	~ALittleGrid9Image()
	{
		
	}

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleGrid9Image, ALittleDisplayObjects>("__CPPAPIGrid9Image")
			.addConstructor<void(*)()>()
			.addFunction("SetX", &ALittleGrid9Image::SetX)
			.addFunction("SetY", &ALittleGrid9Image::SetY)
			.addFunction("SetZ", &ALittleGrid9Image::SetZ)
			.addFunction("SetWidth", &ALittleGrid9Image::SetWidth)
			.addFunction("SetHeight", &ALittleGrid9Image::SetHeight)
			.addFunction("SetRed", &ALittleGrid9Image::SetRed)
			.addFunction("SetGreen", &ALittleGrid9Image::SetGreen)
			.addFunction("SetBlue", &ALittleGrid9Image::SetBlue)
			.addFunction("SetAlpha", &ALittleGrid9Image::SetAlpha)
			.addFunction("SetTexture", &ALittleGrid9Image::SetTexture)
			.addFunction("ClearTexture", &ALittleGrid9Image::ClearTexture)
			.addFunction("SetTextureCoord", &ALittleGrid9Image::SetTextureCoord)
			.addFunction("SetVisible", &ALittleGrid9Image::SetVisible)
			.addFunction("SetClip", &ALittleGrid9Image::SetClip)
			.addFunction("SetScaleX", &ALittleGrid9Image::SetScaleX)
			.addFunction("SetScaleY", &ALittleGrid9Image::SetScaleY)
			.addFunction("SetCenterX", &ALittleGrid9Image::SetCenterX)
			.addFunction("SetCenterY", &ALittleGrid9Image::SetCenterY)
			.addFunction("SetAngle", &ALittleGrid9Image::SetAngle)
			.addFunction("SetTopSize", &ALittleGrid9Image::SetTopSize)
			.addFunction("SetBottomSize", &ALittleGrid9Image::SetBottomSize)
			.addFunction("SetLeftSize", &ALittleGrid9Image::SetLeftSize)
			.addFunction("SetRightSize", &ALittleGrid9Image::SetRightSize)
			.endClass();

	}

	void SetX(float x) override { ALittleDisplayObjects::SetX(x); }
	void SetY(float y) override { ALittleDisplayObjects::SetY(y); }
	void SetZ(float z) override { ALittleDisplayObjects::SetZ(z); }

	void SetWidth(float width) override { ALittleDisplayObjects::SetWidth(width); }
	void SetHeight(float height) override { ALittleDisplayObjects::SetHeight(height); }

	void SetAngle(float angle) override { ALittleDisplayObjects::SetAngle(angle); }

	void SetScaleX(float x) override { ALittleDisplayObjects::SetScaleX(x); }
	void SetScaleY(float y) override { ALittleDisplayObjects::SetScaleY(y); }

	void SetCenterX(float x) override { ALittleDisplayObjects::SetCenterX(x); }
	void SetCenterY(float y) override { ALittleDisplayObjects::SetCenterY(y); }

	void SetVisible(bool visible) override { ALittleDisplayObjects::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleDisplayObjects::SetClip(clip); }

public:
	void SetTopSize(float size) { m_logic_top = static_cast<int>(floor(size)); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetBottomSize(float size) { m_logic_bottom = static_cast<int>(floor(size)); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetLeftSize(float size) { m_logic_left = static_cast<int>(floor(size)); m_vertex_dirty = true; m_texture_dirty = true; }
	void SetRightSize(float size) { m_logic_right = static_cast<int>(floor(size)); m_vertex_dirty = true; m_texture_dirty = true; }

public:
	void SetRed(float red) override
	{
		m_color.r = static_cast<unsigned char>(red * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetRed(red);
	}
	void SetGreen(float green) override
	{
		m_color.g = static_cast<unsigned char>(green * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetGreen(green);
	}
	void SetBlue(float blue) override
	{
		m_color.b = static_cast<unsigned char>(blue * 255);
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetBlue(blue);
	}
	void SetAlpha(float alpha) override
	{
		if (alpha > 1.0f) m_color.a = 255;
		else if (alpha < 0.0f) m_color.a = 0;
		else m_color.a = static_cast<unsigned char>(alpha * 255);
		if (m_color.a <= 0) SetSelfMatrixDirty();
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetAlpha(alpha);
	}

public:
	void SetTexture(ALittleTexture* texture)
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

		m_texture = nullptr;
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

public:
	void UpdateTextureCoord() override
	{
		if (m_texture == nullptr) return;

		const int tex_width = m_texture->GetWidth();
		const int tex_height = m_texture->GetHeight();
		if (tex_width <= 0 || tex_height <= 0) return;

		if (!m_texture_dirty) return;
		m_texture_dirty = false;

		const float logic_left = m_logic_left / static_cast<float>(tex_width);
		const float logic_right = m_logic_right / static_cast<float>(tex_width);
		const float logic_top = m_logic_top / static_cast<float>(tex_height);
		const float logic_bottom = m_logic_bottom / static_cast<float>(tex_height);

		float tex_x[4] = { m_tex_left, m_tex_left + logic_left, m_tex_right - logic_right, m_tex_right };
		float tex_y[4] = { m_tex_top, m_tex_top + logic_top, m_tex_bottom - logic_bottom, m_tex_bottom };

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m_image[i][j].SetTextureCoord(tex_y[i], tex_y[i + 1], tex_x[j], tex_x[j + 1]);
	}
	void UpdateVertexCoord() override
	{
		if (!m_vertex_dirty) return;
		m_vertex_dirty = false;

		int dest_h[3] = { m_logic_top, static_cast<int>(m_size.y) - m_logic_top - m_logic_bottom, m_logic_bottom };
		int dest_w[3] = { m_logic_left, static_cast<int>(m_size.x) - m_logic_left - m_logic_right, m_logic_right };

		if (dest_h[1] < 0 && dest_h[0] + dest_h[2] > 0)
		{
			dest_h[0] = static_cast<int>(static_cast<double>(dest_h[0]) / (static_cast<double>(dest_h[0]) + static_cast<double>(dest_h[2]))
				* static_cast<int>(m_size.y));
			dest_h[1] = 0;
			dest_h[2] = static_cast<int>(m_size.y) - dest_h[0];
		}
		if (dest_w[1] < 0 && dest_w[0] + dest_w[2] > 0)
		{
			dest_w[0] = static_cast<int>(static_cast<double>(dest_w[0]) / (static_cast<double>(dest_w[0]) + static_cast<double>(dest_w[2]))
				* static_cast<int>(m_size.x));
			dest_w[1] = 0;
			dest_w[2] = static_cast<int>(m_size.x) - dest_w[0];
		}
		int dest_y[3] = { 0, dest_h[0], dest_h[0] + dest_h[1] };
		int dest_x[3] = { 0, dest_w[0], dest_w[0] + dest_w[1] };

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m_image[i][j].SetX(static_cast<float>(dest_x[j]));
				m_image[i][j].SetY(static_cast<float>(dest_y[i]));
				m_image[i][j].SetWidth(static_cast<float>(dest_w[j]));
				m_image[i][j].SetHeight(static_cast<float>(dest_h[i]));
			}
		}
	}

private:
	ALittleTexture* m_texture = nullptr;
	ALittleImage m_image[3][3];

private:
	float m_tex_top = 0.0f, m_tex_bottom = 1.0f, m_tex_left = 0.0f, m_tex_right = 1.0f;
	int m_logic_top = 0, m_logic_bottom = 0, m_logic_left = 0, m_logic_right = 0;
};

#endif
