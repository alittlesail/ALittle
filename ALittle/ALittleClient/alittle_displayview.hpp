#ifndef ALITTLE_DISPLAYVIEW_INCLUDED
#define ALITTLE_DISPLAYVIEW_INCLUDED

#include "alittle_displayobjects.hpp"
#include "alittle_render.hpp"

struct ScissorInfo { SDL_Rect rect={0}; int r = 0, b = 0; };
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
			.addFunction("SetZ", &ALittleDisplayView::SetZ)
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
			.addFunction("SetSortChild", &ALittleDisplayView::SetSortChild)
			.addFunction("SetVisible", &ALittleDisplayView::SetVisible)
			.addFunction("SetClip", &ALittleDisplayView::SetClip)
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

	void SetRed(float red) override { ALittleDisplayObjects::SetRed(red); }
	void SetGreen(float green) override { ALittleDisplayObjects::SetGreen(green); }
	void SetBlue(float blue) override { ALittleDisplayObjects::SetBlue(blue); }
	void SetAlpha(float alpha) override { ALittleDisplayObjects::SetAlpha(alpha); }

	void SetVisible(bool visible) override { ALittleDisplayObjects::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleDisplayObjects::SetClip(clip); }

	void AddChild(ALittleDisplayObject* object) override { ALittleDisplayObjects::AddChild(object); }
	void AddChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object) override { ALittleDisplayObjects::AddChildAfter(front_object, target_object); }
	void AddChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object) override { ALittleDisplayObjects::AddChildBefore(back_object, target_object); }
	void RemoveChild(ALittleDisplayObject* object) override { ALittleDisplayObjects::RemoveChild(object); }
	void RemoveAllChild() override { ALittleDisplayObjects::RemoveAllChild(); }
	void SetSortChild(bool value) override { ALittleDisplayObjects::SetSortChild(value); }

public:
	void Render(const CarpMatrix2D& parent, bool parent_changed) override
	{
		if (m_clip) return;
		if (!m_visible) return;
		if (m_head_node == nullptr) return;

		const bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		int scissor_x = static_cast<int>(ceil(m_global_matrix.m[2][0]));
		int scissor_y = static_cast<int>(ceil(m_global_matrix.m[2][1]));
		int width = static_cast<int>(ceil(m_global_matrix.m[0][0] * m_size.x));
		int height = static_cast<int>(ceil(m_global_matrix.m[1][1] * m_size.y));

		if (width <= 0 || height <= 0) return;

		// if stack size == 0 then start scissor
		if (s_scissor_stack.empty())
		{
			s_scissor_stack.resize(0);
			s_scissor_stack.emplace_back(ScissorInfo());
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
			s_scissor_stack.emplace_back(ScissorInfo());
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
			s_alittle_render.FlushRender();
			SDL_RenderSetClipRect(s_alittle_render.GetRender(), &new_info.rect);
			RenderImpl(global_changed);
		}

		s_scissor_stack.pop_back();

		// if stack size == 0 then close scissor
		if (s_scissor_stack.empty())
		{
			// must flush
			s_alittle_render.FlushRender();
			SDL_RenderSetClipRect(s_alittle_render.GetRender(), nullptr);
			s_scissor_stack.resize(0);
		}
		else
		{
			ScissorInfo& last_info = s_scissor_stack.back();
			// must flush
			s_alittle_render.FlushRender();
			SDL_RenderSetClipRect(s_alittle_render.GetRender(), &last_info.rect);
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

