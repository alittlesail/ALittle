
#include "DisplayView.h"

#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

namespace ALittle
{

std::vector<DisplayView::ScissorInfo> DisplayView::s_scissor_stack;

DisplayView::DisplayView()
{ }

DisplayView::~DisplayView()
{ }

void DisplayView::Render(const Matrix2D& parent, bool parent_changed)
{
	if (m_clip) return;
	if (!m_visible) return;
	if (m_head_node == nullptr) return;

	bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
	UpdateVertexCoord();
	UpdateTextureCoord();

	int scissor_x = (int)ceil(m_global_matrix.m[2][0]);
	int scissor_y = (int)ceil(m_global_matrix.m[2][1]);
	int width = (int)ceil(m_global_matrix.m[0][0] * m_size.x);
	int height = (int)ceil(m_global_matrix.m[1][1] * m_size.y);

	if (width <= 0 || height <= 0) return;

	// if stack size == 0 then start scissor
	if (s_scissor_stack.size() == 0)
	{
		s_scissor_stack.resize(0);
		s_scissor_stack.push_back(ScissorInfo());
		ScissorInfo& new_info = s_scissor_stack.back();
		new_info.rect.x = scissor_x;
		new_info.rect.y = scissor_y;
		new_info.rect.w = width;
		new_info.rect.h = height;
		new_info.r = new_info.rect.x + new_info.rect.w;
		new_info.b = new_info.rect.y + new_info.rect.h;
	}
	else
	{
		ScissorInfo& cur_info = s_scissor_stack.back();
		s_scissor_stack.push_back(ScissorInfo());
		ScissorInfo& new_info = s_scissor_stack.back();
		new_info.r = scissor_x + width;
		new_info.b = scissor_y + height;
		new_info.rect.x = scissor_x > cur_info.rect.x ? scissor_x : cur_info.rect.x;
		new_info.rect.y = scissor_y > cur_info.rect.y ? scissor_y : cur_info.rect.y;
		new_info.r = new_info.r < cur_info.r ? new_info.r : cur_info.r;
		new_info.b = new_info.b < cur_info.b ? new_info.b : cur_info.b;
		new_info.rect.w = new_info.r - new_info.rect.x;
		if (new_info.rect.w < 0) new_info.rect.w = 0;
		new_info.rect.h = new_info.b - new_info.rect.y;
		if (new_info.rect.h < 0) new_info.rect.h = 0;
	}

	ScissorInfo& new_info = s_scissor_stack.back();

	if (new_info.rect.w > 0 && new_info.rect.h > 0)
	{
		// must flush
		g_RenderSystem.FlushRender();
		SDL_RenderSetClipRect(g_RenderSystem.GetRender(), &new_info.rect);

		DisplayObject* node = m_head_node;
		while (node)
		{
			node->Render(m_global_matrix, global_changed);
			node = node->m_back_node;
		}
	}
	
	s_scissor_stack.pop_back();

	// if stack size == 0 then close scissor
	if (s_scissor_stack.size() == 0)
	{
		// must flush
		g_RenderSystem.FlushRender();
		SDL_RenderSetClipRect(g_RenderSystem.GetRender(), NULL);
		s_scissor_stack.resize(0);
	}
	else
	{
		ScissorInfo& last_info = s_scissor_stack.back();
		// must flush
		g_RenderSystem.FlushRender();
		SDL_RenderSetClipRect(g_RenderSystem.GetRender(), &last_info.rect);
	}
}

} // ALittle
