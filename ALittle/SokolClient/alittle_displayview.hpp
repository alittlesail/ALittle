#ifndef ALITTLE_DISPLAYVIEW_INCLUDED
#define ALITTLE_DISPLAYVIEW_INCLUDED (1)

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"

#include "alittle_displayobjects.hpp"

struct ScissorInfo { int x = 0; int y = 0; int w = 0; int h = 0; int r = 0, b = 0; };
extern std::vector<ScissorInfo> s_scissor_stack;

class ALittleDisplayView : public ALittleDisplayObjects
{
public:
	ALittleDisplayView() {}
	virtual ~ALittleDisplayView() {}

public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleDisplayView, ALittleDisplayObjects>("__CPPAPIDisplayView")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleDisplayView::SetScaleX)
			.addFunction("SetScaleY", &ALittleDisplayView::SetScaleY)
			.addFunction("SetCenterX", &ALittleDisplayView::SetCenterX)
			.addFunction("SetCenterY", &ALittleDisplayView::SetCenterY)
			.addFunction("SetAngle", &ALittleDisplayView::SetAngle)
			.addFunction("SetX", &ALittleDisplayView::SetX)
			.addFunction("SetY", &ALittleDisplayView::SetY)
			.addFunction("SetWidth", &ALittleDisplayView::SetWidth)
			.addFunction("SetHeight", &ALittleDisplayView::SetHeight)
			.addFunction("SetRed", &ALittleDisplayView::SetRed)
			.addFunction("SetGreen", &ALittleDisplayView::SetGreen)
			.addFunction("SetBlue", &ALittleDisplayView::SetBlue)
			.addFunction("SetAlpha", &ALittleDisplayView::SetAlpha)
			.addFunction("AddChild", &ALittleDisplayView::AddChild)
			.addFunction("AddChildAfter", &ALittleDisplayView::AddChildAfter)
			.addFunction("AddChildBefore", &ALittleDisplayView::AddChildBefore)
			.addFunction("RemoveChild", &ALittleDisplayView::RemoveChild)
			.addFunction("RemoveAllChild", &ALittleDisplayView::RemoveAllChild)
			.addFunction("SetVisible", &ALittleDisplayView::SetVisible)
			.addFunction("SetClip", &ALittleDisplayView::SetClip)
			.endClass();
	}

#ifdef __EMSCRIPTEN__
	void SetX(float x) { ALittleDisplayObjects::SetX(x); }
	void SetY(float y) { ALittleDisplayObjects::SetY(y); }

	void SetWidth(float width) { ALittleDisplayObjects::SetWidth(width); }
	void SetHeight(float height) { ALittleDisplayObjects::SetHeight(height); }

	void SetAngle(float angle) { ALittleDisplayObjects::SetAngle(angle); }

	void SetScaleX(float x) { ALittleDisplayObjects::SetScaleX(x); }
	void SetScaleY(float y) { ALittleDisplayObjects::SetScaleY(y); }

	void SetCenterX(float x) { ALittleDisplayObjects::SetCenterX(x); }
	void SetCenterY(float y) { ALittleDisplayObjects::SetCenterY(y); }

	void SetRed(float red) { ALittleDisplayObjects::SetRed(red); }
	void SetGreen(float green) { ALittleDisplayObjects::SetGreen(green); }
	void SetBlue(float blue) { ALittleDisplayObjects::SetBlue(blue); }
	void SetAlpha(float alpha) { ALittleDisplayObjects::SetAlpha(alpha); }

	void SetVisible(bool visible) { ALittleDisplayObjects::SetVisible(visible); }
	void SetClip(bool clip) { ALittleDisplayObjects::SetClip(clip); }

	void AddChild(ALittleDisplayObject* object) { ALittleDisplayObjects::AddChild(object); }
	void AddChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object) { ALittleDisplayObjects::AddChildAfter(front_object, target_object); }
	void AddChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object) { ALittleDisplayObjects::AddChildBefore(back_object, target_object); }
	void RemoveChild(ALittleDisplayObject* object) { ALittleDisplayObjects::RemoveChild(object); }
	void RemoveAllChild() { ALittleDisplayObjects::RemoveAllChild(); }
#endif

public:
	virtual void Render(const CarpMatrix2D& parent, bool parent_changed)
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
			new_info.x = scissor_x;
			new_info.y = scissor_y;
			new_info.w = width;
			new_info.h = height;
			new_info.r = new_info.x + new_info.w;
			new_info.b = new_info.y + new_info.h;
		}
		else
		{
			ScissorInfo& cur_info = s_scissor_stack.back();
			s_scissor_stack.push_back(ScissorInfo());
			ScissorInfo& new_info = s_scissor_stack.back();
			new_info.r = scissor_x + width;
			new_info.b = scissor_y + height;
			new_info.x = scissor_x > cur_info.x ? scissor_x : cur_info.x;
			new_info.y = scissor_y > cur_info.y ? scissor_y : cur_info.y;
			new_info.r = new_info.r < cur_info.r ? new_info.r : cur_info.r;
			new_info.b = new_info.b < cur_info.b ? new_info.b : cur_info.b;
			new_info.w = new_info.r - new_info.x;
			if (new_info.w < 0) new_info.w = 0;
			new_info.h = new_info.b - new_info.y;
			if (new_info.h < 0) new_info.h = 0;
		}

		ScissorInfo& new_info = s_scissor_stack.back();

		if (new_info.w > 0 && new_info.h > 0)
		{
			// must flush
			// TODO g_RenderSystem.FlushRender();
			sg_apply_scissor_rect(new_info.x, new_info.y, new_info.w, new_info.h, true);

			ALittleDisplayObject* node = m_head_node;
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
			// TODO g_RenderSystem.FlushRender();
			sg_apply_scissor_rect(0, 0, sapp_width(), sapp_height(), true);
			s_scissor_stack.resize(0);
		}
		else
		{
			ScissorInfo& last_info = s_scissor_stack.back();
			// must flush
			// TODO g_RenderSystem.FlushRender();
			sg_apply_scissor_rect(last_info.x, last_info.y, last_info.w, last_info.h, true);
		}
	}
};

#endif

#ifdef ALITTLE_DISPLAYVIEW_IMPL
#ifndef ALITTLE_DISPLAYVIEW_IMPL_INCLUDE
#define ALITTLE_DISPLAYVIEW_IMPL_INCLUDE
std::vector<ScissorInfo> s_scissor_stack;
#endif
#endif

