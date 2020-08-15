
#include "Triangle.h"

#include "ALittle/LibClient/RenderSystem/Texture/Texture.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

Triangle::Triangle()
: m_texture(0)
, m_tex_top(0), m_tex_bottom(1), m_tex_left(0), m_tex_right(1)
{
}

Triangle::~Triangle()
{
}

void Triangle::UpdateTextureCoord()
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

void Triangle::UpdateVertexCoord()
{
	if (!m_vertex_dirty) return;
	m_vertex_dirty = false;

	Vector2D coord[3];
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

void Triangle::Render(const Matrix2D& parent, bool parent_changed)
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

void Triangle::SetTexUV(int index, double u, double v)
{
	if (index < 0 || index >= 3) return;

	m_texture_coord_logic[index].x = (float)u;
	m_texture_coord_logic[index].y = (float)v;

	m_texture_dirty = true;
}

void Triangle::SetPosXY(int index, double x, double y)
{
	if (index < 0 || index >= 3) return;

	m_vertex_coord_logic[index].x = (float)x;
	m_vertex_coord_logic[index].y = (float)y;

	m_vertex_dirty = true;
}

} // ALittle
