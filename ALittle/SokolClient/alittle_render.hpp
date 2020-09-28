#ifndef ALITTLE_RENDER_INCLUDED
#define ALITTLE_RENDER_INCLUDED (1)

#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#include "alittle_display.hpp"

class ALittleRender
{
public:
	void Setup()
	{
		m_pass_action.colors[0].action = SG_ACTION_CLEAR;
		m_pass_action.colors[0].val[0] = 0.0f;
		m_pass_action.colors[0].val[1] = 0.0f;
		m_pass_action.colors[0].val[2] = 0.0f;
		m_pass_action.colors[0].val[3] = 1.0f;

		sg_desc desc = { 0 };
		desc.context = sapp_sgcontext();
		sg_setup(&desc);
	}

	void Render()
	{
		sg_begin_default_pass(&m_pass_action, sapp_width(), sapp_height());
		s_alittle_display.Render();
		sg_end_pass();
		sg_commit();
	}

	bool CreateView(const char* title, unsigned int width, unsigned int height, unsigned int flag, float scale)
	{
		sapp_set_window_title(title);
		m_scale_x = scale;
		m_scale_y = scale;
		return true;
	}

	void SetViewSize(unsigned int width, unsigned int height)
	{
		// logic size transfer to view size
		int new_view_width = int(width * m_scale_x);
		int new_view_height = int(height * m_scale_y);

		// set window size
		// SDL_SetWindowSize(m_window, new_view_width, new_view_height);
	}

	int GetViewX()
	{
		return 0;
	}

	int GetViewY()
	{
		return 0;
	}

	void SetViewPosition(int x, int y)
	{
		
	}

	void ShowView()
	{
		
	}

	void HideView()
	{
		
	}

	bool SetViewTitle(const char* title)
	{
		sapp_set_window_title(title);
		return true;
	}

	int GetMaxTextureWidth()
	{
		return 1024;
	}

	int GetMaxTextureHeight()
	{
		return 1024;
	}

	bool SetViewIcon(const char* file_path)
	{
		return false;
	}

	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleRender>("__CPPAPIRenderSystem")
			.addFunction("CreateView", &ALittleRender::CreateView)
			.addFunction("SetViewSize", &ALittleRender::SetViewSize)
			.addFunction("GetViewX", &ALittleRender::GetViewX)
			.addFunction("GetViewY", &ALittleRender::GetViewY)
			.addFunction("SetViewPosition", &ALittleRender::SetViewPosition)
			.addFunction("ShowView", &ALittleRender::ShowView)
			.addFunction("HideView", &ALittleRender::HideView)
			.addFunction("SetViewTitle", &ALittleRender::SetViewTitle)
			.addFunction("SetViewIcon", &ALittleRender::SetViewIcon)
			.addFunction("GetMaxTextureWidth", &ALittleRender::GetMaxTextureWidth)
			.addFunction("GetMaxTextureHeight", &ALittleRender::GetMaxTextureHeight)
			.addFunction("Render", &ALittleRender::Render)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_RenderSystem");
	}

	void Shutdown()
	{
		sg_shutdown();
	}

private:
	sg_pass_action m_pass_action{0};

	float m_scale_x = 1.0f;
	float m_scale_y = 1.0f;
};

extern ALittleRender s_alittle_render;

#endif

#ifdef ALITTLE_RENDER_IMPL
ALittleRender s_alittle_render;
#endif

