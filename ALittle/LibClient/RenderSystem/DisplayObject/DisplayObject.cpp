
#include "DisplayObject.h"

namespace ALittle
{

bool DisplayObject::UpdateSelfMatrix2D()
{
	if (!m_self_matrix_dirty) return false;
	m_self_matrix_dirty = false;
	m_vertex_dirty = true;

	m_self_matrix.SetTranslation(-m_center.x, -m_center.y);
	m_self_matrix.Scale(m_scale.x, m_scale.y);
	m_self_matrix.Rotate(m_angle);
	m_self_matrix.Translation(m_center.x, m_center.y);
	m_self_matrix.Translation(m_pos.x, m_pos.y);

	return true;
}

bool DisplayObject::UpdateGlobalMatrix2D(const Matrix2D& parent, bool parent_changed)
{
	bool self_update = UpdateSelfMatrix2D();
	if (parent_changed || self_update)
	{
		m_global_matrix = m_self_matrix;
		m_global_matrix.Multiply(parent);
		m_vertex_dirty = true;

		return true;
	}

	return false;
}

} // ALittle
