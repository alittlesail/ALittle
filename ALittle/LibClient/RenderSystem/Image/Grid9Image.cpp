
#include "Grid9Image.h"

#include "ALittle/LibClient/RenderSystem/Texture/Texture.h"

namespace ALittle
{

Grid9Image::Grid9Image()
: m_tex_top(0), m_tex_bottom(1), m_tex_left(0), m_tex_right(1)
, m_flip(SDL_FLIP_NONE), m_texture(0)
, m_logic_top(0), m_logic_bottom(0), m_logic_left(0), m_logic_right(0)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			AddChild(&(m_image[i][j]));
}

Grid9Image::~Grid9Image()
{
}

void Grid9Image::UpdateTextureCoord()
{
	if (m_texture == 0) return;

	int tex_width = m_texture->GetWidth();
	int tex_height = m_texture->GetHeight();
	if (tex_width <= 0 || tex_height <= 0) return;

	if (!m_texture_dirty) return;
	m_texture_dirty = false;

	float logic_left = m_logic_left / (float)tex_width;
	float logic_right = m_logic_right / (float)tex_width;
	float logic_top = m_logic_top / (float)tex_height;
	float logic_bottom = m_logic_bottom / (float)tex_height;

	float tex_x[4] = { m_tex_left, m_tex_left + logic_left, m_tex_right - logic_right, m_tex_right };
	if (m_flip & SDL_FLIP_HORIZONTAL)
	{
		float temp;
		temp = tex_x[0]; tex_x[0] = tex_x[3]; tex_x[3] = temp;
		temp = tex_x[1]; tex_x[1] = tex_x[2]; tex_x[2] = temp;
	}
	float tex_y[4] = { m_tex_top, m_tex_top + logic_top, m_tex_bottom - logic_bottom, m_tex_bottom };
	if (m_flip & SDL_FLIP_VERTICAL)
	{
		float temp;
		temp = tex_y[0]; tex_y[0] = tex_y[3]; tex_y[3] = temp;
		temp = tex_y[1]; tex_y[1] = tex_y[2]; tex_y[2] = temp;
	}

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			m_image[i][j].SetTextureCoord(tex_y[i], tex_y[i+1], tex_x[j], tex_x[j+1]);
}

void Grid9Image::UpdateVertexCoord()
{
	if (!m_vertex_dirty) return;
	m_vertex_dirty = false;

	int logic_left = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_logic_left : m_logic_right;
	int logic_right = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_logic_right : m_logic_left;
	int logic_top = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_logic_top : m_logic_bottom;
	int logic_bottom = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_logic_bottom : m_logic_top;

	int dest_h[3] = { logic_top, (int)m_size.y - logic_top - logic_bottom, logic_bottom };
	int dest_w[3] = { logic_left, (int)m_size.x - logic_left - logic_right, logic_right };

	if (dest_h[1] < 0 && dest_h[0] + dest_h[2] > 0)
	{
		dest_h[0] = (int)((double)dest_h[0] / ((double)dest_h[0] + (double)dest_h[2]) * (int)m_size.y);
		dest_h[1] = 0;
		dest_h[2] = (int)m_size.y - dest_h[0];
	}
	if (dest_w[1] < 0 && dest_w[0] + dest_w[2] > 0)
	{
		dest_w[0] = (int)((double)dest_w[0] / ((double)dest_w[0] + (double)dest_w[2]) * (int)m_size.x);
		dest_w[1] = 0;
		dest_w[2] = (int)m_size.x - dest_w[0];
	}
	int dest_y[3] = { 0, dest_h[0], dest_h[0] + dest_h[1] };
	int dest_x[3] = { 0, dest_w[0], dest_w[0] + dest_w[1] };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_image[i][j].SetX((float)dest_x[j]);
			m_image[i][j].SetY((float)dest_y[i]);
			m_image[i][j].SetWidth((float)dest_w[j]);
			m_image[i][j].SetHeight((float)dest_h[i]);
		}
	}
}

} // ALittle
