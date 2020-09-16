
#include "RenderTexture.h"

#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "ALittle/LibClient/Helper/TextureHelper.h"

namespace ALittle
{

RenderTexture::RenderTexture()
	: m_texture(0), m_width(0), m_height(0)
{
}

RenderTexture::~RenderTexture()
{
	Clear();
}

void RenderTexture::Clear()
{
	if (m_texture)
		g_RenderSystem.DestroyTexture(m_texture);
	m_texture = 0;
	m_width = 0;
	m_height = 0;
}

void RenderTexture::Render(const Color4& color, float* vertex_coord, float* texture_coord)
{
	if (m_texture == 0) return;

	g_RenderSystem.PushRenderQuad(m_texture, color, vertex_coord, texture_coord);
}

void RenderTexture::RenderTriangle(const Color4& color, float* vertex_coord, float* texture_coord)
{
	if (m_texture == 0) return;

	g_RenderSystem.PushRenderTriangle(m_texture, color, vertex_coord, texture_coord);
}

bool RenderTexture::Draw(DisplayObject* object, int width, int height)
{
	Clear();

	if (width <= 0 || height <= 0) return false;
	if (!SDL_RenderTargetSupported(g_RenderSystem.GetRender())) return false;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 format = SDL_PIXELFORMAT_RGBA8888;
#else
	Uint32 format = SDL_PIXELFORMAT_ABGR8888;
#endif
	SDL_Texture* texture = SDL_CreateTexture(g_RenderSystem.GetRender(), format, SDL_TEXTUREACCESS_TARGET, width, height);
	if (texture == 0) return false;
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_Texture* old_texture = SDL_GetRenderTarget(g_RenderSystem.GetRender());
	SDL_SetRenderTarget(g_RenderSystem.GetRender(), texture);

	// set render blend
	SDL_SetRenderDrawBlendMode(g_RenderSystem.GetRender(), SDL_BLENDMODE_BLEND);

	// clear color
	SDL_SetRenderDrawColor(g_RenderSystem.GetRender(), 0, 0, 0, 0);
	SDL_RenderClear(g_RenderSystem.GetRender());

	object->SetSelfMatrixDirty();
	object->Render(Matrix2D(), false);
	object->SetSelfMatrixDirty();

	// present
	g_RenderSystem.FlushRender();
	SDL_RenderPresent(g_RenderSystem.GetRender());
	SDL_SetRenderTarget(g_RenderSystem.GetRender(), old_texture);

	m_texture = texture;
	m_width = width;
	m_height = height;

	return true;
}	

bool RenderTexture::Save(const char* file_path, DisplayObject* object, int width, int height)
{
	Clear();

	if (width <= 0 || height <= 0) return false;
	if (!SDL_RenderTargetSupported(g_RenderSystem.GetRender())) return false;
	
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 format = SDL_PIXELFORMAT_RGBA8888;
#else
	Uint32 format = SDL_PIXELFORMAT_ABGR8888;
#endif

	SDL_Texture* texture = SDL_CreateTexture(g_RenderSystem.GetRender(), format, SDL_TEXTUREACCESS_TARGET, width, height);
	if (texture == 0) return false;
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_Texture* old_texture = SDL_GetRenderTarget(g_RenderSystem.GetRender());
	SDL_SetRenderTarget(g_RenderSystem.GetRender(), texture);

	// set render blend
	SDL_SetRenderDrawBlendMode(g_RenderSystem.GetRender(), SDL_BLENDMODE_BLEND);

	// clear color
	SDL_SetRenderDrawColor(g_RenderSystem.GetRender(), 0, 0, 0, 0);
	SDL_RenderClear(g_RenderSystem.GetRender());

	object->SetSelfMatrixDirty();
	object->Render(Matrix2D(), false);
	object->SetSelfMatrixDirty();

	// present
	g_RenderSystem.FlushRender();
	SDL_RenderPresent(g_RenderSystem.GetRender());

	bool result = false;
	int renderer_width, renderer_height;
	SDL_GetRendererOutputSize(g_RenderSystem.GetRender(), &renderer_width, &renderer_height);

	SDL_Surface* surface = TextureHelper::CreateSurface(renderer_width, renderer_height);
	if (surface)
	{
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
		int read_result = SDL_RenderReadPixels(g_RenderSystem.GetRender(), 0, format, surface->pixels, surface->pitch);
		if (read_result == 0)
		{
			if (!TextureHelper::SaveSurface(surface, file_path))
				ALITTLE_ERROR("SaveSurface failed:" << file_path);
		}
		else
			ALITTLE_ERROR("SDL_RenderReadPixels failed:" << renderer_width << ", " << renderer_height);
		SDL_FreeSurface(surface);
	}
	else
		ALITTLE_ERROR("SDL_CreateRGBSurface failed:" << renderer_width << ", " << renderer_height);

	SDL_SetRenderTarget(g_RenderSystem.GetRender(), old_texture);
	g_RenderSystem.DestroyTexture(texture);

	return result;
}

} // ALittle
