#ifndef ALITTLE_RENDER_INCLUDED
#define ALITTLE_RENDER_INCLUDED

#include <SDL.h>
#include <SDL_syswm.h>
#include <list>
#include <string>

#include "alittle_script.hpp"
#include "alittle_display.hpp"
#include "Carp/carp_log.hpp"
#include "Carp/carp_lua.hpp"
#include "Carp/carp_math_2d.hpp"
#include "Carp/carp_surface_bind.hpp"

class ALittleRender
{
public:
	void Setup()
	{
	}
	
	void Shutdown()
	{
		// destroy texture list
		DestroyTextureList();

		// release render
		if (m_render)
		{
			SDL_DestroyRenderer(m_render);
			m_render = nullptr;
		}

		// release window
		if (m_window)
		{
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		// reset parent window
		m_parent_window = nullptr;
	}
	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleRender>("__CPPAPIRenderSystem")
			.addFunction("CreateView", &ALittleRender::CreateView)
			.addFunction("SetViewTitle", &ALittleRender::SetViewTitle)
			.addFunction("SetViewIcon", &ALittleRender::SetViewIcon)
			.addFunction("SetViewSize", &ALittleRender::SetViewSize)
			.addFunction("GetMaxTextureWidth", &ALittleRender::GetMaxTextureWidth)
			.addFunction("GetMaxTextureHeight", &ALittleRender::GetMaxTextureHeight)
			.addFunction("Render", &ALittleRender::Render)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_RenderSystem");
	}

public:
	/**
	 * create view
	 * @param title
	 * @param width
	 * @param height
	 * @param flag
	 * @return succeed or not
	 */
	bool CreateView(const char* title, unsigned int width, unsigned int height, unsigned int flag, float scale)
	{
		// check param
		if (m_window || width == 0 || height == 0) return false;

		// enable SDL_HINT_RENDER_VSYNC
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

		int windows_x = SDL_WINDOWPOS_CENTERED;
		int windows_y = SDL_WINDOWPOS_CENTERED;

		if (m_parent_window)
		{
			// get parent window size
#ifdef _WIN32
			HWND parent_hWnd = static_cast<HWND>(m_parent_window);
			RECT hWnd_rect;
			::GetWindowRect(parent_hWnd, &hWnd_rect);
			width = hWnd_rect.right - hWnd_rect.left;
			height = hWnd_rect.bottom - hWnd_rect.top;
			windows_x = 0;
			windows_y = 0;
#endif
		}

		m_scale_x = scale;
		m_scale_y = scale;
		m_fullscreen = (width == 0 || height == 0);

		if (m_fullscreen) flag |= SDL_WINDOW_FULLSCREEN;
		flag |= SDL_WINDOW_SHOWN;
		flag |= SDL_WINDOW_ALLOW_HIGHDPI;

		// if add to parent windows, then chang window style
		if (m_parent_window)
		{
			flag |= SDL_WINDOW_BORDERLESS;
			flag &= ~SDL_WINDOW_RESIZABLE;
		}

		// create window
		if ((flag & 0x10000000) == 0)
		{
#if (defined __ANDROID__) || (defined __IPHONEOS__)
			m_window = SDL_CreateWindow(title, windows_x, windows_y, 0, 0, flag);
#else
			m_window = SDL_CreateWindow(title, windows_x, windows_y, static_cast<int>(width * scale), static_cast<int>(height * scale), flag);
#endif
		}
		else
		{
			flag &= ~0x10000000;
#if (defined __ANDROID__) || (defined __IPHONEOS__)
			m_window = SDL_CreateShapedWindow(title, windows_x, windows_y, 0, 0, flag);
#else
			m_window = SDL_CreateShapedWindow(title, windows_x, windows_y, static_cast<int>(width * scale), static_cast<int>(height * scale), flag);
#endif
		}
		if (!m_window)
		{
			CARP_ERROR("window recreate failed:" << SDL_GetError());
			return false;
		}

		// create render
		m_render = SDL_CreateRenderer(m_window, -1, 0);
		if (!m_render)
		{
			CARP_ERROR(SDL_GetError());
			return false;
		}

		// enable screen saver
		SDL_EnableScreenSaver();

		// get render info
		SDL_GetRendererInfo(m_render, &m_render_info);
		if (m_render_info.name)
			CARP_INFO("rederer:" << m_render_info.name);

		m_title = title;			// save title
		m_logic_width = width;		// save logic width
		m_logic_height = height;	// save logic height

		SDL_GL_GetDrawableSize(m_window, reinterpret_cast<int*>(&m_view_width), reinterpret_cast<int*>(&m_view_height));
		SDL_GetWindowSize(m_window, reinterpret_cast<int*>(&m_window_width), reinterpret_cast<int*>(&m_window_height));

		CARP_INFO("logic_width:" << m_logic_width << ", logic_height:" << m_logic_height);
		CARP_INFO("view_width:" << m_view_width << ", view_height:" << m_view_height);
		CARP_INFO("window_width:" << m_window_width << ", window_height:" << m_window_height);
		m_flag = SDL_GetWindowFlags(m_window);

		// init scale
#if (defined __ANDROID__) || (defined __IPHONEOS__)
		m_scale_x = (float)m_view_width / (float)m_logic_width;
		m_scale_y = (float)m_view_height / (float)m_logic_height;
#endif

		// render config
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		SDL_RenderSetLogicalSize(m_render, m_logic_width, m_logic_height);
		SDL_RenderSetViewport(m_render, nullptr);

		float scale_x, scale_y;
		SDL_RenderGetScale(m_render, &scale_x, &scale_y);
		CARP_INFO("render logic scale_x:" << m_scale_x << ", scale_y:" << m_scale_y);
		CARP_INFO("render real scale_x:" << scale_x << ", scale_y:" << scale_y);

		// set render blend
		SDL_SetRenderDrawBlendMode(m_render, SDL_BLENDMODE_BLEND);

		// DisplaySystem setup
		s_alittle_display.Setup();

		// notify size
		s_alittle_script.Invoke("__ALITTLEAPI_ViewResized", m_logic_width, m_logic_height);

		// get syswm info
		SDL_VERSION(&m_syswm_info.version);
		SDL_GetWindowWMInfo(m_window, &m_syswm_info);

		// append to parent window
		if (m_parent_window)
		{
#ifdef _WIN32
			HWND parent_hWnd = (HWND)m_parent_window;
			::SetParent(m_syswm_info.info.win.window, parent_hWnd);
#endif // _WIN32
		}

		return true;
	}

public:
	/**
	 * render
	 */
	bool Render()
	{
		if (!m_render) return false;

		if (m_android_surface_resize) return false;

#if (defined __ANDROID__) || (defined __IPHONEOS__)
		if (!SDL_GL_GetCurrentContext()) return false;
		DestroyTextureList();
#endif

		// clear color
		SDL_SetRenderDrawColor(m_render, 0, 0, 0, 0);
		SDL_RenderClear(m_render);

		// render ui system
		s_alittle_display.Render();

		// show
		SDL_RenderPresent(m_render);

		return true;
	}

	//render info////////////////////////////////////////////////////////////////////////
public:
	inline SDL_Renderer* GetRender() const { return m_render; }
	inline const SDL_RendererInfo& GetRenderInfo() const { return m_render_info; }

public:
	void PushRenderQuad(SDL_Texture* texture, const CarpColor4& color, float* vertex_coord, float* texture_coord) const
	{
		static int indices[] = { 0, 1, 2, 0, 2, 3 };
		SDL_RenderGeometryRaw(m_render, texture, vertex_coord, sizeof(float)*2, (int*)&color, 0, texture_coord, sizeof(float)*2, 4, indices, 6, sizeof(int));
	}
	void PushRenderTriangle(SDL_Texture* texture, const CarpColor4& color, float* vertex_coord, float* texture_coord) const
	{
		SDL_RenderGeometryRaw(m_render, texture, vertex_coord, sizeof(float) * 2, (int*)&color, 0, texture_coord, sizeof(float) * 2, 3, nullptr, 0, 0);
	}
	inline void FlushRender() const { SDL_RenderFlush(m_render); }

private:
	SDL_Renderer* m_render = nullptr;		// render object
	SDL_RendererInfo m_render_info;
	bool m_enable_render = true;

public:
	bool m_android_surface_resize = false;

	//window info////////////////////////////////////////////////////////////////////////
public:
	inline SDL_Window* GetWindow() const { return m_window; }
	unsigned int GetLogicWidth() const { return m_logic_width; }
	unsigned int GetLogicHeight() const { return m_logic_height; }
	const SDL_SysWMinfo& GetSysWMinfo() const { return m_syswm_info; }

	float CalcFingerX(float tfinger_x) const
	{
		const float result = tfinger_x * m_logic_width;
		if (m_view_width == 0) return result;
		return result * (static_cast<float>(m_window_width) / static_cast<float>(m_view_width));
	}
	float CalcFingerY(float tfinger_y) const
	{
		const float result = tfinger_y * m_logic_height;
		if (m_view_height == 0) return result;
		return result * (static_cast<float>(m_window_height) / static_cast<float>(m_view_height));
	}

public:
	void HandleMinViewSize()
	{
		m_enable_render = false;
	}

	void HandleMaxViewSize()
	{
		m_enable_render = true;
	}

	void HandleRestoreViewSize()
	{
		if (!m_window) return;

		m_enable_render = true;

		// get windows real size
		int width, height;
		SDL_GetWindowSize(m_window, &width, &height);

		HandleViewResized(width, height);
	}
	
	void HandleViewResized(unsigned int width, unsigned int height)
	{
		// set surface resize false
		m_android_surface_resize = false;

		// if scale is to small then return
		if (m_scale_x <= 0.001f || m_scale_y <= 0.001f) return;

		SDL_GL_GetDrawableSize(m_window, reinterpret_cast<int*>(&m_view_width), reinterpret_cast<int*>(&m_view_height));
		SDL_GetWindowSize(m_window, reinterpret_cast<int*>(&m_window_width), reinterpret_cast<int*>(&m_window_height));

		// calc logic size
		m_logic_width = static_cast<int>(m_view_width / m_scale_x);
		m_logic_height = static_cast<int>(m_view_height / m_scale_y);

		// change size
		if (m_render)
		{
			SDL_RenderSetLogicalSize(m_render, m_logic_width, m_logic_height);
			SDL_RenderSetViewport(m_render, nullptr);
		}

		// notify script system
		s_alittle_script.Invoke("__ALITTLEAPI_ViewResized", m_logic_width, m_logic_height);

#if (defined __ANDROID__) || (defined __IPHONEOS__)
		Render();
#endif
	}
	void HandleDeviceReset()
	{
		CARP_INFO("device reset");

		if (m_render)
		{
			// render config
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			SDL_RenderSetLogicalSize(m_render, m_logic_width, m_logic_height);

			// set render blend
			SDL_SetRenderDrawBlendMode(m_render, SDL_BLENDMODE_BLEND);
		}

		s_alittle_script.Invoke("__ALITTLEAPI_RenderDeviceReset");
	}

	bool SetViewTitle(const char* title)
	{
		if (!m_window || title == 0) return false;

		SDL_SetWindowTitle(m_window, title);
		return true;
	}
	bool SetViewIcon(const char* path)
	{
		if (!m_window || path == 0) return false;

		// create surface
		auto* icon = CarpSurfaceBind::LoadSurface(path);
		// check load succeed or not
		if (icon == nullptr)
		{
			CARP_ERROR("CarpSurface::LoadSurface failed:" << path);
			return false;
		}

		auto* surface = SDL_CreateRGBSurface(0, icon->GetWidth(), icon->GetHeight(), 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		if (surface) memcpy(surface->pixels, icon->GetPixels(), icon->GetPitch() * icon->GetHeight());
		CarpSurfaceBind::FreeCarpSurface(icon);
		
		// check load succeed or not
		if (surface == nullptr)
		{
			CARP_ERROR("CarpSurface::LoadSurface failed:" << path);
			return false;
		}
		
		// set icon
		SDL_SetWindowIcon(m_window, surface);
		SDL_FreeSurface(surface);
		return true;
	}

	void SetViewSize(unsigned int width, unsigned int height)
	{
		if (m_window == 0) return;

		// logic size transfer to view size
		int new_view_width = int(width * m_scale_x);
		int new_view_height = int(height * m_scale_y);

		// set window size
		SDL_SetWindowSize(m_window, new_view_width, new_view_height);
	}
	
	int GetMaxTextureWidth() const
	{
		return m_render_info.max_texture_width;
	}
	int GetMaxTextureHeight() const
	{
		return m_render_info.max_texture_height;
	}

private:
	SDL_Window* m_window = nullptr;			// window object
	unsigned int m_window_width = 0;	// window width
	unsigned int m_window_height = 0;	// window height
	unsigned int m_view_width = 0;		// real view width
	unsigned int m_view_height = 0;		// real view height
	unsigned int m_logic_width = 0;		// logic view width
	unsigned int m_logic_height = 0;	// logic view height

	std::string m_title;			// title
	bool m_fullscreen = false;				// fullscreen or not
	int m_flag = 0;						// flag

//scale info////////////////////////////////////////////////////////////////////////
public:
	float GetScaleX() const { return m_scale_x; }
	float GetScaleY() const { return m_scale_y; }

private:
	float m_scale_x = 1.0f, m_scale_y = 1.0f;

	//window info////////////////////////////////////////////////////////////////////////
private:
	SDL_SysWMinfo m_syswm_info = {0};
	void* m_parent_window = nullptr;		// web plugin root window object

public:
	void DestroyTexture(SDL_Texture* texture)
	{
		if (texture == 0) return;

#if (defined __ANDROID__) || (defined __IPHONEOS__)
		if (!SDL_GL_GetCurrentContext())
			m_texture_destroy_list.push_back(texture);
		else
			SDL_DestroyTexture(texture);
#else
		SDL_DestroyTexture(texture);
#endif
	}
	void DestroyTextureList()
	{
#if (defined __ANDROID__) || (defined __IPHONEOS__)
		while (m_texture_destroy_list.size())
		{
			SDL_DestroyTexture(m_texture_destroy_list.front());
			m_texture_destroy_list.pop_front();
		}
#endif
	}

private:
	std::list<SDL_Texture*> m_texture_destroy_list;
};

extern ALittleRender s_alittle_render;

#endif

#ifdef ALITTLE_RENDER_IMPL
#ifndef ALITTLE_RENDER_IMPL_INCLUDE
#define ALITTLE_RENDER_IMPL_INCLUDE
ALittleRender s_alittle_render;
#endif
#endif
