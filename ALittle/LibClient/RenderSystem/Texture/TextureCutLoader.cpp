
#include "TextureCutLoader.h"
#include "SurfaceTexture.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibCommon/Helper/CryptHelper.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"

#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/Tool/LocalFile.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/Helper/TextureHelper.h"

#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"

namespace ALittle
{

void TextureCutLoader::SetPath(const char* file_path, int max_width, int max_height)
{
	m_file_path = file_path;
	m_max_width = max_width;
	m_max_height = max_height;
}

void TextureCutLoader::Start()
{
    g_ThreadSystem.AddTask(this, ThreadSystem::THREAD_TYPE_FAST);
}

void TextureCutLoader::Execute()
{
    // sdl surface
    SDL_Surface* surface = 0;

	// load for local file
	LocalFile local_file;
#ifdef __IPHONEOS__
    surface = iOS_GetPhoto(m_file_path.c_str());
	if (surface == 0)
	{
#endif
		local_file.SetPath(m_file_path.c_str());
		if (local_file.Load() == false)
		{
			ALITTLE_ERROR("LocalFile load failed, " << m_file_path);
			g_ScheduleSystem.PushUserEvent(TEXTURECUT_LOAD_FAILED, this);
			return;
		}

		// create surface
		surface = TextureHelper::LoadImageFromMemory(local_file.GetContent(), local_file.GetSize());
#ifdef __IPHONEOS__
	}
#endif

	if (!surface)
	{
		ALITTLE_ERROR("LoadImageFromMemory failed:" << m_file_path);
		g_ScheduleSystem.PushUserEvent(TEXTURECUT_LOAD_FAILED, this);
		return;
	}

	if (m_max_width > 0 && m_max_height > 0 && (surface->w > m_max_width || surface->h > m_max_height))
	{
		float scale_x = (float)m_max_width / (float)surface->w;
		float scale_y = (float)m_max_height / (float)surface->h;

		float max_scale = scale_x;
		if (max_scale > scale_y) max_scale = scale_y;

		int adjust_width = int(max_scale * surface->w);
		if (adjust_width == 0) adjust_width = 1;
		int adjust_height = int(max_scale * surface->h);
		if (adjust_height == 0) adjust_height = 1;

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
		SDL_Surface* new_surface = SDL_CreateRGBSurface(0, adjust_width, adjust_height, 32, rmask, gmask, bmask, amask);
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
		SDL_BlitScaled(surface, 0, new_surface, 0);
		SDL_FreeSurface(surface);
		surface = new_surface;
	}

	// TextureHelper::AdjustSurfaceAlpha(surface);
	g_ScheduleSystem.PushUserEvent(TEXTURECUT_LOAD_SUCCEED, this, surface);
}

void TextureCutLoader::Abandon()
{
	g_ScheduleSystem.PushUserEvent(TEXTURECUT_LOAD_FAILED, this);
}

int TextureCutLoader::GetID() const
{
#ifdef __IPHONEOS__
	static int s_id = 0;
	++s_id;
	return s_id;
#else
	int id = 0;
	const TextureCutLoader* data = this;
	memcpy(&id, &data, sizeof(int));
	return id;
#endif
}

void TextureCutLoader::HandleEvent(unsigned int event_type, void* data1, void* data2)
{
	TextureCutLoader* loader = (TextureCutLoader*)data1;
	if (event_type == TEXTURECUT_LOAD_FAILED)
	{
		g_ScriptSystem.Invoke("__ALITTLEAPI_TextureCutLoadFailed", loader);
		return;
	}

	SDL_Surface* surface = (SDL_Surface*)data2;
	Texture* texture = new SurfaceTexture(surface);
	g_ScriptSystem.Invoke("__ALITTLEAPI_TextureCutLoadSucceed", loader, texture);
}

} // ALittle
