
#include "RenderSystem.h"

#include <SDL.h>
#include <SDL_shape.h>
#include <SDL_syswm.h>

#include "DisplaySystem.h"

#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"
#include "ALittle/LibClient/Helper/TextureHelper.h"

#include "Carp/carp_log.hpp"

namespace ALittle
{

RenderSystem::RenderSystem()
: m_render(0)
, m_window(0)
, m_window_width(0)
, m_window_height(0)
, m_view_width(0)
, m_view_height(0)
, m_logic_width(800)
, m_logic_height(600)
, m_title("ALittle")
, m_fullscreen(false)
, m_flag(0)
, m_icon(0)
, m_enable_render(true)
, m_scale_x(1), m_scale_y(1)
, m_parent_window(0)
, m_android_surface_resize(false)
{ }

RenderSystem::~RenderSystem() {}

RenderSystem& RenderSystem::Instance()
{
	static RenderSystem instance;
	return instance;
}

void RenderSystem::Setup()
{
	CARP_INFO("SDL Setup");

	g_DisplaySystem.Setup();
}

void RenderSystem::Shutdown()
{
	// shutdown DisplaySystem
	g_DisplaySystem.Shutdown();

	// destroy texture list
	DestroyTextureList();

	// release icon
	if (m_icon) { SDL_FreeSurface(m_icon); m_icon = 0; }

	// release render
	if (m_render)
	{
		SDL_DestroyRenderer(m_render);
		m_render = NULL;
	}

	// release window
	if (m_window)
	{
		 SDL_DestroyWindow(m_window);
		 m_window = NULL;
	}

	// reset parent window
	m_parent_window = 0;
}

void RenderSystem::SetParentView(void* data)
{
	m_parent_window = data;
}

int RenderSystem::GetViewFlag()
{
	return m_flag;
}

int RenderSystem::GetMaxTextureWidth() const
{
	return m_render_info.max_texture_width;
}

int RenderSystem::GetMaxTextureHeight() const
{
	return m_render_info.max_texture_height;
}

bool RenderSystem::CreateView(const char* title, unsigned int width, unsigned int height, unsigned int flag, float scale)
{
	// check param
	if (m_window || width == 0 || height == 0) return false;

	// init ios status bar color
#ifdef __IPHONEOS__
	IOS_SetStatusBarLight();
#endif

	// enable SDL_HINT_RENDER_VSYNC
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	int windows_x = SDL_WINDOWPOS_CENTERED;
	int windows_y = SDL_WINDOWPOS_CENTERED;

	if (m_parent_window)
	{
		// get parent window size
#ifdef _WIN32
		HWND parent_hWnd = (HWND)m_parent_window;
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
		m_window = SDL_CreateWindow(title, windows_x, windows_y, (int)(width*scale), (int)(height*scale), flag);
#endif
	}
	else
	{
		flag &= ~0x10000000;
#if (defined __ANDROID__) || (defined __IPHONEOS__)
		m_window = SDL_CreateShapedWindow(title, windows_x, windows_y, 0, 0, flag);
#else
		m_window = SDL_CreateShapedWindow(title, windows_x, windows_y, (int)(width*scale), (int)(height*scale), flag);
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
    
    SDL_GL_GetDrawableSize(m_window, (int*)&m_view_width, (int*)&m_view_height);
    SDL_GetWindowSize(m_window, (int*)&m_window_width, (int*)&m_window_height);

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
    SDL_RenderSetViewport(m_render, NULL);

	float scale_x, scale_y;
    SDL_RenderGetScale(m_render, &scale_x, &scale_y);
    CARP_INFO("render logic scale_x:" << m_scale_x << ", scale_y:" << m_scale_y);
	CARP_INFO("render real scale_x:" << scale_x << ", scale_y:" << scale_y);
	
	// set render blend
	SDL_SetRenderDrawBlendMode(m_render, SDL_BLENDMODE_BLEND);
	
	// DisplaySystem setup
	g_DisplaySystem.Setup();

	// notify size
	g_ScriptSystem.Invoke("__ALITTLEAPI_ViewResized", m_logic_width, m_logic_height);

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

bool RenderSystem::SetViewShape(const char* file_path)
{
	if (!m_window || SDL_IsShapedWindow(m_window) == false) return false;

	// load icon from file
	std::vector<char> file_content;
	if (!FileHelperEx::LoadFile(file_path, false, file_content)) return false;

	// create surface
	SDL_Surface* surface = TextureHelper::LoadImageFromMemory(file_content.data(), file_content.size());
	// check load succeed or not
	if (surface == 0)
	{
		CARP_ERROR("LoadImageFromMemory failed:" << file_path);
		return false;
	}

	// if surface is not match windows size, then scale
	if (surface->w != m_view_width || surface->h != m_view_height)
	{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int rmask = 0xff000000;
		int gmask = 0x00ff0000;
		int bmask = 0x0000ff00;
		int amask = 0x000000ff;
#else
		int rmask = 0x000000ff;
		int gmask = 0x0000ff00;
		int bmask = 0x00ff0000;
		int amask = 0xff000000;
#endif
		SDL_Surface* new_surface = SDL_CreateRGBSurface(0, m_view_width, m_view_height, 32, rmask, gmask, bmask, amask);
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
		SDL_BlitScaled(surface, 0, new_surface, 0);
		SDL_FreeSurface(surface);
		surface = new_surface;
	}

	// black color
	SDL_Color black = {0, 0, 0, 0xff};
	// clac shape
	SDL_WindowShapeMode shape_mode;
	if (SDL_ISPIXELFORMAT_ALPHA(surface->format->format))
	{
		shape_mode.mode = ShapeModeBinarizeAlpha;
		shape_mode.parameters.binarizationCutoff = 255;
	}
	else {
		shape_mode.mode = ShapeModeColorKey;
		shape_mode.parameters.colorKey = black;
	}

	int result = SDL_SetWindowShape(m_window, surface, &shape_mode);
	if (result == -2)
		CARP_ERROR("SDL_INVALID_SHAPE_ARGUMENT");
	SDL_FreeSurface(surface);
	return result == 0;
}

void RenderSystem::SetViewSize(unsigned int width, unsigned int height)
{
	if (m_window == 0) return;
	
	// logic size transfer to view size
	int new_view_width = int(width * m_scale_x);
	int new_view_height = int(height * m_scale_y);

	// set window size
	SDL_SetWindowSize(m_window, new_view_width, new_view_height);
}

bool RenderSystem::Render()
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
	g_DisplaySystem.Render();

	// show
	SDL_RenderPresent(m_render);

	return true;
}

void RenderSystem::HandleViewResized(unsigned int width, unsigned int height)
{
	// set surface resize false
	m_android_surface_resize = false;

	// if scale is to small then return
	if (m_scale_x <= 0.001f || m_scale_y <= 0.001f) return;

	SDL_GL_GetDrawableSize(m_window, (int*)&m_view_width, (int*)&m_view_height);
    SDL_GetWindowSize(m_window, (int*)&m_window_width, (int*)&m_window_height);

	// calc logic size
	m_logic_width = (int)(m_view_width / m_scale_x);
	m_logic_height = (int)(m_view_height / m_scale_y);
    
	// change size
	if (m_render)
	{
		SDL_RenderSetLogicalSize(m_render, m_logic_width, m_logic_height);
        SDL_RenderSetViewport(m_render, NULL);
    }

	// notify script system
	g_ScriptSystem.Invoke("__ALITTLEAPI_ViewResized", m_logic_width, m_logic_height);

#if (defined __ANDROID__) || (defined __IPHONEOS__)
	Render();
#endif
}

void RenderSystem::HandleDeviceReset()
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

	g_ScriptSystem.Invoke("__ALITTLEAPI_RenderDeviceReset");
}

unsigned int RenderSystem::GetLogicWidth() const
{
	return m_logic_width;
}

unsigned int RenderSystem::GetLogicHeight() const
{
	return m_logic_height;
}

float RenderSystem::GetScaleX() const
{
	return m_scale_x;
}

float RenderSystem::GetScaleY() const
{
	return m_scale_y;
}

float RenderSystem::CalcFingerX(float tfinger_x)
{
	float result = tfinger_x * m_logic_width;
	if (m_view_width == 0) return result;
	return result * ((float)m_window_width / (float)m_view_width);
}

float RenderSystem::CalcFingerY(float tfinger_y)
{
	float result = tfinger_y * m_logic_height;
	if (m_view_height == 0) return result;
	return result * ((float)m_window_height / (float)m_view_height);
}

bool RenderSystem::SetViewTitle(const char* title)
{
	if (!m_window || title == 0) return false;

	SDL_SetWindowTitle(m_window, title);
	return true;
}

bool RenderSystem::SetViewIcon(const char* path)
{
	if (!m_window || path == 0) return false;

	// free current icon
	if (m_icon) { SDL_FreeSurface(m_icon); m_icon = 0; }

	// load icon from file
	std::vector<char> file_content;
	if (!FileHelperEx::LoadFile(path, false, file_content)) return false;

	// create surface
	m_icon = TextureHelper::LoadImageFromMemory(file_content.data(), file_content.size());

	// check load succeed or not
	if (m_icon == 0)
	{
		CARP_ERROR("LoadImageFromMemory failed:" << path);
		return false;
	}

	// set icon
	SDL_SetWindowIcon(m_window, m_icon);
	return true;
}

void RenderSystem::SetMaxViewSize()
{
	if (!m_window) return;
	// max winows size
	m_enable_render = true;
	SDL_MaximizeWindow(m_window);
}

void RenderSystem::SetMinViewSize()
{
	if (!m_window) return;
	// min windows size
	m_enable_render = false;
	SDL_MinimizeWindow(m_window);
}

void RenderSystem::SetRestoreViewSize()
{
	if (!m_window) return;
	// restore windows size
	m_enable_render = true;
	SDL_RestoreWindow(m_window);
}

void RenderSystem::HandleRestoreViewSize()
{
	if (!m_window) return;

	m_enable_render = true;

	// get windows real size
	int width, height;
	SDL_GetWindowSize(m_window, &width, &height);
	
	HandleViewResized(width, height);
}

int RenderSystem::GetViewX()
{
	if (!m_window) return 0;
	int x, y;
	SDL_GetWindowPosition(m_window, &x, &y);
	return x;
}

int RenderSystem::GetViewY()
{
	if (!m_window) return 0;
	int x, y;
	SDL_GetWindowPosition(m_window, &x, &y);
	return y;
}

void RenderSystem::SetViewPosition(int x, int y)
{
	if (!m_window) return ;
	SDL_SetWindowPosition(m_window, x, y);
}

void RenderSystem::RaiseView()
{
	if (m_window == 0) return;

#ifdef _WIN32
	HWND hwnd = m_syswm_info.info.win.window;
	// if (GetForegroundWindow() == hwnd) return;

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#else
	SDL_RaiseWindow(m_window);
#endif
}

void RenderSystem::HandleMinViewSize()
{
	m_enable_render = false;
}

void RenderSystem::HandleMaxViewSize()
{
	m_enable_render = true;
}

bool RenderSystem::ShowView()
{
	if (m_window == 0) return false;
	SDL_ShowWindow(m_window);
	return true;
}

bool RenderSystem::HideView()
{
	if (m_window == 0) return false;
	SDL_HideWindow(m_window);
	return true;
}

void RenderSystem::DestroyTexture(SDL_Texture* texture)
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

void RenderSystem::DestroyTextureList()
{
#if (defined __ANDROID__) || (defined __IPHONEOS__)
	while (m_texture_destroy_list.size())
	{
		SDL_DestroyTexture(m_texture_destroy_list.front());
		m_texture_destroy_list.pop_front();
	}
#endif
}

void RenderSystem::RegisterToScript(ScriptSystem& script_system)
{
	g_DisplaySystem.RegisterToScript(script_system);

	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<RenderSystem>("__CPPAPIRenderSystem")
		.addFunction("CreateView", &RenderSystem::CreateView)
		.addFunction("SetViewSize", &RenderSystem::SetViewSize)
		.addFunction("SetMaxViewSize", &RenderSystem::SetMaxViewSize)
		.addFunction("SetMinViewSize", &RenderSystem::SetMinViewSize)
		.addFunction("SetRestoreViewSize", &RenderSystem::SetRestoreViewSize)
		.addFunction("GetViewX", &RenderSystem::GetViewX)
		.addFunction("GetViewY", &RenderSystem::GetViewY)
		.addFunction("SetViewPosition", &RenderSystem::SetViewPosition)
		.addFunction("RaiseView", &RenderSystem::RaiseView)
		.addFunction("ShowView", &RenderSystem::ShowView)
		.addFunction("HideView", &RenderSystem::HideView)
		.addFunction("SetViewTitle", &RenderSystem::SetViewTitle)
		.addFunction("SetViewIcon", &RenderSystem::SetViewIcon)
		.addFunction("SetViewShape", &RenderSystem::SetViewShape)
		.addFunction("GetMaxTextureWidth", &RenderSystem::GetMaxTextureWidth)
		.addFunction("GetMaxTextureHeight", &RenderSystem::GetMaxTextureHeight)
		.addFunction("Render", &RenderSystem::Render)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_RenderSystem");
}

} // ALittle
