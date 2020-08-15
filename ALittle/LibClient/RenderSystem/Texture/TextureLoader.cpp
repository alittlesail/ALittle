
#include "TextureLoader.h"
#include "SurfaceTexture.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibCommon/Helper/CryptHelper.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"

#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/Helper/TextureHelper.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"

namespace ALittle
{

void TextureLoader::SetPath(const char* file_path, const char* atlas_info, int width, int height, bool crypt_mode)
{
	m_file_path = file_path;
	m_atlas_info = atlas_info;
	m_crypt_mode = crypt_mode;
	m_width = width;
	m_height = height;
}

void TextureLoader::Execute()
{
	SDL_Surface* surface = 0;
	if (m_width > 0 && m_height > 0)
	{
		surface = TextureHelper::CreateSurface(m_width, m_height);
		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
	}

	std::vector<std::string> atlas_list;
	StringHelper::Split(m_atlas_info, ";", atlas_list);
	for (unsigned int i = 0; i < atlas_list.size(); ++i)
	{
		std::vector<std::string> atlas_info;
		StringHelper::Split(atlas_list[i], ",", atlas_info);
		if (atlas_info.size() < 1) continue;
		std::string file_path = atlas_info[0];
		if (atlas_info.size() < 2) continue;
		int t = S2I(atlas_info[1].c_str());
		if (atlas_info.size() < 3) continue;
		int b = S2I(atlas_info[2].c_str());
		if (atlas_info.size() < 4) continue;
		int l = S2I(atlas_info[3].c_str());
		if (atlas_info.size() < 5) continue;
		int r = S2I(atlas_info[4].c_str());
		if (atlas_info.size() < 6) continue;
		int w = S2I(atlas_info[5].c_str());
		if (atlas_info.size() < 7) continue;
		int h = S2I(atlas_info[6].c_str());

		std::vector<char> file_content;
		if (!FileHelperEx::LoadFile(file_path, false, file_content))
		{
			if (surface) SDL_FreeSurface(surface);
			ALITTLE_ERROR("LocalFile load failed, " << file_path);
			g_ScheduleSystem.PushUserEvent(TEXTURE_LOAD_FAILED, this);
			return;
		}
		if (m_crypt_mode) CryptHelper::XXTeaDecodeMemory(&(file_content[0]), static_cast<int>(file_content.size()), 0);
		// load from memory
		SDL_RWops* mem = SDL_RWFromMem((void*)&(file_content[0]), static_cast<int>(file_content.size()));
		if (mem == 0)
		{
			if (surface) SDL_FreeSurface(surface);
			ALITTLE_ERROR(SDL_GetError() << ", " << file_path);
			g_ScheduleSystem.PushUserEvent(TEXTURE_LOAD_FAILED, this);
			return;
		}

		// create surface
		SDL_Surface* child_surface = IMG_Load_RW(mem, 0);
		// release mem
		SDL_RWclose(mem);
		if (!child_surface)
		{
			if (surface) SDL_FreeSurface(surface);
			ALITTLE_ERROR(IMG_GetError() << ", " << file_path);
			g_ScheduleSystem.PushUserEvent(TEXTURE_LOAD_FAILED, this);
			return;
		}
		SDL_SetSurfaceBlendMode(child_surface, SDL_BLENDMODE_NONE);

		if (surface == 0) { surface = child_surface; break; }

		TextureHelper::BlitSurface(surface, child_surface, l, t);
		// top
		for (int i = 0; i < w; ++i)
		{
			unsigned int pixel = TextureHelper::GetSurfacePixel(child_surface, i, 0);
			TextureHelper::SetSurfacePixel(surface, l + i, t - 1, pixel);
		}

		// bottom
		for (int i = 0; i < w; ++i)
		{
			unsigned int pixel = TextureHelper::GetSurfacePixel(child_surface, i, h - 1);
			TextureHelper::SetSurfacePixel(surface, l + i, t + h, pixel);
		}

		// left
		for (int i = 0; i < h; ++i)
		{
			unsigned int pixel = TextureHelper::GetSurfacePixel(child_surface, 0, i);
			TextureHelper::SetSurfacePixel(surface, l - 1, t + i, pixel);
		}
		
		// right
		for (int i = 0; i < h; ++i)
		{
			unsigned int pixel = TextureHelper::GetSurfacePixel(child_surface, w - 1, i);
			TextureHelper::SetSurfacePixel(surface, l + w, t + i, pixel);
		}
		
		// left-top
		unsigned int pixel = TextureHelper::GetSurfacePixel(child_surface, 0, 0);
		TextureHelper::SetSurfacePixel(surface, l - 1, t - 1, pixel);
		// right-top
		pixel = TextureHelper::GetSurfacePixel(child_surface, w - 1, 0);
		TextureHelper::SetSurfacePixel(surface, l + w, t - 1, pixel);
		// left-bottom
		pixel = TextureHelper::GetSurfacePixel(child_surface, 0, h - 1);
		TextureHelper::SetSurfacePixel(surface, l - 1, t + h, pixel);
		// right-bottom
		pixel = TextureHelper::GetSurfacePixel(child_surface, w - 1, h - 1);
		TextureHelper::SetSurfacePixel(surface, l + w, t + h, pixel);

		SDL_FreeSurface(child_surface);
	}
	// TextureHelper::RejustSurfaceAlpha(surface);
	g_ScheduleSystem.PushUserEvent(TEXTURE_LOAD_SUCCEED, this, surface);
}

void TextureLoader::Abandon()
{
	g_ScheduleSystem.PushUserEvent(TEXTURE_LOAD_FAILED, this);
}

int TextureLoader::GetID() const
{
#ifdef __IPHONEOS__
	static int s_id = 0;
	++s_id;
	return s_id;
#else
	int id = 0;
	const TextureLoader* data = this;
	memcpy(&id, &data, sizeof(int));
	return id;
#endif
}

void TextureLoader::HandleEvent(unsigned int event_type, void* data1, void* data2)
{
	TextureLoader* loader = (TextureLoader*)data1;
	if (event_type == TEXTURE_LOAD_FAILED)
	{
		g_ScriptSystem.Invoke("__ALITTLEAPI_TextureLoadFailed", loader);
		return;
	}

	SDL_Surface* surface = (SDL_Surface*)data2;
	SurfaceTexture* texture = new SurfaceTexture(surface);
	texture->GenerateImpl();
	g_ScriptSystem.Invoke("__ALITTLEAPI_TextureLoadSucceed", loader, (Texture*)texture);
}

void TextureLoader::Start()
{
    g_ThreadSystem.AddTask(this, ThreadSystem::THREAD_TYPE_FAST);
}

} // ALittle