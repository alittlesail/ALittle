
#include "SurfaceTexture.h"

#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "Carp/carp_log.hpp"

namespace ALittle
{

SurfaceTexture::SurfaceTexture()
: m_texture(0), m_surface(0)
, m_width(0), m_height(0)
{
}

SurfaceTexture::SurfaceTexture(SDL_Surface* surface)
: m_texture(0), m_surface(surface)
{
	m_width = surface->w;
	m_height = surface->h;
}

SurfaceTexture::~SurfaceTexture()
{
	Clear();
}

void SurfaceTexture::GenerateImpl()
{
	if (m_texture) return;
	if (m_surface == 0) return;

#if (defined __ANDROID__) || (defined __IPHONEOS__)
	if (!SDL_GL_GetCurrentContext()) return;
#endif

	// get renderer info
	SDL_Renderer* renderer = g_RenderSystem.GetRender();
	const SDL_RendererInfo& renderer_info = g_RenderSystem.GetRenderInfo();
	// if surface small then max texture size then create single texture
	if (m_surface->w <= renderer_info.max_texture_width && m_surface->h <= renderer_info.max_texture_height)
	{
		m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
		if (m_texture) SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(m_surface);
		m_surface = 0;
		return;
	}

	CARP_ERROR("surface is too large:" << m_surface->w << "," << m_surface->h);

	SDL_FreeSurface(m_surface);
	m_surface = 0;
}

void SurfaceTexture::Clear()
{
	if (m_surface)
	{
		SDL_FreeSurface(m_surface);
		m_surface = 0;
	}

	if (m_texture)
		g_RenderSystem.DestroyTexture(m_texture);
	m_texture = 0;

	m_width = 0;
	m_height = 0;
}

int SurfaceTexture::GetWidth() const
{
	return m_width;
}

int SurfaceTexture::GetHeight() const
{
	return m_height;
}

void SurfaceTexture::Render(const Color4& color, float* vertex_coord, float* texture_coord)
{
	GenerateImpl();

	// if single texture then render
	if (m_texture)
		g_RenderSystem.PushRenderQuad(m_texture, color, vertex_coord, texture_coord);
}


void SurfaceTexture::RenderTriangle(const Color4& color, float* vertex_coord, float* texture_coord)
{
	GenerateImpl();

	// if single texture then render
	if (m_texture)
		g_RenderSystem.PushRenderTriangle(m_texture, color, vertex_coord, texture_coord);
}

} // ALittle
