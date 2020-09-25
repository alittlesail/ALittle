
#ifndef _ALITTLE_RenderSystem_H_
#define _ALITTLE_RenderSystem_H_

#include <SDL.h>
#include <SDL_syswm.h>
#include <list>
#include <string>

#include "Matrix2D.h"

namespace ALittle
{

class ScriptSystem;

class RenderSystem
{
public:
	static RenderSystem& Instance();

public:
	void Setup();
	void Shutdown();
	void RegisterToScript(ScriptSystem& script_system);
	
public:
	/**
	 * create view
	 * @param title
	 * @param width
	 * @param height
	 * @param flag
	 * @return succeed or not
	 */
	bool CreateView(const char* title, unsigned int width, unsigned int height, unsigned int flag, float scale);
	bool SetViewShape(const char* file_path);
	
public:
	/**
	 * render
	 */
	bool Render();
	
//render info////////////////////////////////////////////////////////////////////////
public:
	inline SDL_Renderer* GetRender() const { return m_render; }
	inline const SDL_RendererInfo& GetRenderInfo() const { return m_render_info; }

public:
	inline void PushRenderQuad(SDL_Texture* texture, const Color4& color, float* vertex_coord, float* texture_coord)
	{
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(texture, color.a);
		SDL_RenderQuad(m_render, texture, texture_coord, vertex_coord);
	}
	inline void PushRenderTriangle(SDL_Texture* texture, const Color4& color, float* vertex_coord, float* texture_coord)
	{
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(texture, color.a);
		SDL_RenderTriangle(m_render, texture, texture_coord, vertex_coord);
	}
	inline void FlushRender() { SDL_RenderFlush(m_render); }
	
private:
	SDL_Renderer* m_render;		// render object
	SDL_RendererInfo m_render_info;
	bool m_enable_render;

public:
	bool m_android_surface_resize;

//window info////////////////////////////////////////////////////////////////////////
public:
	inline SDL_Window* GetWindow() const { return m_window; }
	unsigned int GetLogicWidth() const;
	unsigned int GetLogicHeight() const;
	const SDL_SysWMinfo& GetSysWMinfo() const { return m_syswm_info; }

	float CalcFingerX(float tfinger_x);
	float CalcFingerY(float tfinger_y);

public:
	void HandleViewResized(unsigned int width, unsigned int height);
	void HandleDeviceReset();

	void SetViewSize(unsigned int width, unsigned int height);

	void SetMaxViewSize();
	void HandleMaxViewSize();
	
	void SetMinViewSize();
	void HandleMinViewSize();
	
	void SetRestoreViewSize();
	void HandleRestoreViewSize();
	
	int GetViewX();
	int GetViewY();
	void SetViewPosition(int x, int y);
	
	void RaiseView();
	bool ShowView();
	bool HideView();
	
	bool SetViewTitle(const char* title);
	bool SetViewIcon(const char* path);
	void SetParentView(void* data);

	int GetViewFlag();

	int GetMaxTextureWidth() const;
	int GetMaxTextureHeight() const;

private:
	SDL_Window* m_window;			// window object
	unsigned int m_window_width;	// window width
	unsigned int m_window_height;	// window height
	unsigned int m_view_width;		// real view width
	unsigned int m_view_height;		// real view height
	unsigned int m_logic_width;		// logic view width
	unsigned int m_logic_height;	// logic view height

	SDL_Surface* m_icon;			// view icon
	std::string m_title;			// title
	bool m_fullscreen;				// fullscreen or not
	int m_flag;						// flag

//scale info////////////////////////////////////////////////////////////////////////
public:
	float GetScaleX() const;
	float GetScaleY() const;

private:
	float m_scale_x, m_scale_y;

//window info////////////////////////////////////////////////////////////////////////
private:
	SDL_SysWMinfo m_syswm_info;
	void* m_parent_window;		// web plugin root window object

public:
	void DestroyTexture(SDL_Texture* texture);
	void DestroyTextureList();

private:
	std::list<SDL_Texture*> m_texture_destroy_list;

private:
	RenderSystem();
	~RenderSystem();
};

} // ALittle

#define g_RenderSystem ALittle::RenderSystem::Instance()

#endif // _ALITTLE_RenderSystem_H_
