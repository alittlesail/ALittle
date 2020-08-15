
#include "Image.h"

#include "ALittle/LibClient/RenderSystem/Texture/Texture.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

Image::Image()
: m_texture(0)
, m_tex_top(0), m_tex_bottom(1), m_tex_left(0), m_tex_right(1)
, m_flip(SDL_FLIP_NONE)
{
}

Image::~Image()
{
}

void Image::UpdateTextureCoord()
{
	if (!m_texture_dirty) return;
	m_texture_dirty = false;

	float left = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_tex_left : m_tex_right;
	float right = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? m_tex_right : m_tex_left;

	float top = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_tex_top : m_tex_bottom;
	float bottom = (m_flip & SDL_FLIP_VERTICAL) == 0 ? m_tex_bottom : m_tex_top;

	m_texture_coord[0] = left; m_texture_coord[1] = top;
	m_texture_coord[2] = right; m_texture_coord[3] = top;
	m_texture_coord[4] = right; m_texture_coord[5] = bottom;
	m_texture_coord[6] = left; m_texture_coord[7] = bottom;
}

void Image::UpdateVertexCoord()
{
	if (!m_vertex_dirty) return;
	m_vertex_dirty = false;

	Vector2D coord[4];
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

void Image::Render(const Matrix2D& parent, bool parent_changed)
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

} // ALittle
