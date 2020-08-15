
#include "Sprite.h"

#include "ALittle/LibClient/RenderSystem/Texture/Texture.h"

namespace ALittle
{

Sprite::Sprite()
: m_row_count(1), m_col_count(1), m_row_index(0), m_col_index(0)
{
}

Sprite::~Sprite()
{
}

void Sprite::UpdateTextureCoord()
{
	if (m_texture == 0) return;

	int tex_width = m_texture->GetWidth();
	int tex_height = m_texture->GetHeight();
	if (tex_width == 0 || tex_height == 0) return;

	if (!m_texture_dirty) return;
	m_texture_dirty = false;

	int row_count = m_row_count;
	if (row_count < 1) row_count = 1;
	int col_count = m_col_count;
	if (col_count < 1) col_count = 1;

	int row_index = m_row_index;
	if (row_index < 0 || row_index >= m_row_count)
		row_index = 0;
	int col_index = m_col_index;
	if (col_index < 0 || col_index >= m_col_count)
		col_index = 0;

	int tex_left = (int)ceil(m_tex_left * tex_width);
	int tex_right = (int)ceil(m_tex_right * tex_width);
	int tex_top = (int)ceil(m_tex_top * tex_height);
	int tex_bottom = (int)ceil(m_tex_bottom * tex_height);

	int cell_width = (tex_right - tex_left) / col_count;
	int cell_height = (tex_bottom - tex_top) / row_count;

	float tex_left_tmp = (tex_left + cell_width * col_index) / (float)tex_width;
	float tex_right_tmp = (tex_left + cell_width * col_index + cell_width) / (float)tex_width;
	float tex_top_tmp = (tex_top + cell_height * row_index) / (float)tex_height;
	float tex_bottom_tmp = (tex_top + cell_height * row_index + cell_height) / (float)tex_height;

	float left = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? tex_left_tmp : tex_right_tmp;
	float right = (m_flip & SDL_FLIP_HORIZONTAL) == 0 ? tex_right_tmp : tex_left_tmp;
	float top = (m_flip & SDL_FLIP_VERTICAL) == 0 ? tex_top_tmp : tex_bottom_tmp;
	float bottom = (m_flip & SDL_FLIP_VERTICAL) == 0 ? tex_bottom_tmp : tex_top_tmp;

	m_texture_coord[0] = left; m_texture_coord[1] = top;
	m_texture_coord[2] = right; m_texture_coord[3] = top;
	m_texture_coord[4] = right; m_texture_coord[5] = bottom;
	m_texture_coord[6] = left; m_texture_coord[7] = bottom;
}

} // ALittle
