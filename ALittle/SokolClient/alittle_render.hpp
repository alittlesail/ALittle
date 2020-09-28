#ifndef ALITTLE_RENDER_INCLUDED
#define ALITTLE_RENDER_INCLUDED (1)

#include "sokol/sokol_gfx.h"
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
	}

	void Render()
	{
		sg_begin_default_pass(&m_pass_action, sapp_width(), sapp_height());
		s_alittle_display.Render();
		sg_end_pass();
		sg_commit();
	}

	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleRender>("__CPPAPIRenderSystem")
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_RenderSystem");
	}

	void Shutdown()
	{
		sg_shutdown();
	}

private:
	sg_pass_action m_pass_action{0};
};

extern ALittleRender s_alittle_render;

#endif

#ifdef ALITTLE_RENDER_IMPL
ALittleRender s_alittle_render;
#endif

