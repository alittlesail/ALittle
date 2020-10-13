#ifndef ALITTLE_TEXTURE_INCLUDED
#define ALITTLE_TEXTURE_INCLUDED (1)

#include "alittle_render.hpp"
#include "SDL.h"
#include "Carp/carp_math_2d.hpp"
#include "Carp/carp_surface_bind.hpp"

enum class ALittleTextureRenderMode
{
	ATRM_NEAREST, /**< nearest pixel sampling */
	ATRM_LINEAR,  /**< linear filtering */
	ATRM_BEST     /**< anisotropic filtering */
};

class ALittleTexture
{
public:
	ALittleTexture() {}
	virtual ~ALittleTexture() {}

public:
	/**
	 * render
	 */
	virtual void Render(const CarpColor4& color, float* vertex_coord, float* texture_coord) {}
	virtual void RenderTriangle(const CarpColor4& color, float* vertex_coord, float* texture_coord) {}

	/**
	* clear
	*/
	virtual void Clear() {}

	/**
	* get width and height
	*/
	virtual int GetWidth() const { return 0; }
	virtual int GetHeight() const { return 0; }
};

class ALittleTextureWrap
{
public:
	ALittleTextureWrap() {}
	~ALittleTextureWrap() { delete m_texture; }

public:
	void SetTexture(ALittleTexture* texture) { m_texture = texture; }
	ALittleTexture* GetTexture() const { return m_texture; }
	void Clear() const { if (m_texture == nullptr) return; m_texture->Clear(); }
	int GetWidth() const { if (m_texture) return m_texture->GetWidth(); return 0; }
	int GetHeight() const { if (m_texture) return m_texture->GetHeight(); return 0; }

public:
	ALittleTexture* m_texture = nullptr;
};


class ALittleSurfaceTexture : public ALittleTexture
{
public:
	ALittleSurfaceTexture(CarpSurface* surface, ALittleTextureRenderMode mode)
	{
		m_surface = surface;
		m_mode = mode;
		m_width = surface->GetWidth();
		m_height = surface->GetHeight();
	}
	~ALittleSurfaceTexture()
	{
		Clear();
	}

public:
	void GenerateImpl()
	{
		if (m_texture) return;
		if (m_surface == nullptr) return;

#if (defined __ANDROID__) || (defined __IPHONEOS__)
		if (!SDL_GL_GetCurrentContext()) return;
#endif

		// if surface small then max texture size then create single texture
		if (m_surface->GetWidth() <= s_alittle_render.GetMaxTextureWidth() && m_surface->GetHeight() <= s_alittle_render.GetMaxTextureHeight())
		{
			m_texture = SDL_CreateTexture(s_alittle_render.GetRender(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, m_surface->GetWidth(), m_surface->GetHeight());
			if (m_texture)
			{
				SDL_UpdateTexture(m_texture, nullptr, m_surface->GetPixels(), m_surface->GetPitch());
				switch (m_mode)
				{
				case ALittleTextureRenderMode::ATRM_NEAREST:
					SDL_SetTextureScaleMode(m_texture, SDL_ScaleModeNearest);
					break;
				case ALittleTextureRenderMode::ATRM_BEST:
					SDL_SetTextureScaleMode(m_texture, SDL_ScaleModeBest);
					break;
				default:
					SDL_SetTextureScaleMode(m_texture, SDL_ScaleModeLinear);
					break;
				}
				SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
			}
			CarpSurfaceBind::FreeCarpSurface(m_surface);
			m_surface = nullptr;
			return;
		}

		CARP_ERROR("surface is too large:" << m_surface->GetWidth() << "," << m_surface->GetHeight());

		CarpSurfaceBind::FreeCarpSurface(m_surface);
		m_surface = nullptr;
	}

public:
	/**
	 * clear texture
	 */
	void Clear() override
	{
		if (m_surface)
		{
			CarpSurfaceBind::FreeCarpSurface(m_surface);
			m_surface = nullptr;
		}

		if (m_texture) s_alittle_render.DestroyTexture(m_texture);
		m_texture = nullptr;

		m_width = 0;
		m_height = 0;
	}

	/**
	 * get width and height
	 */
	int GetWidth() const override { return m_width; }
	int GetHeight() const override { return m_height; }

public:
	void Render(const CarpColor4& color, float* vertex_coord, float* texture_coord) override
	{
		GenerateImpl();

		// if single texture then render
		if (m_texture)
			s_alittle_render.PushRenderQuad(m_texture, color, vertex_coord, texture_coord);
	}
	void RenderTriangle(const CarpColor4& color, float* vertex_coord, float* texture_coord) override
	{
		GenerateImpl();

		// if single texture then render
		if (m_texture)
			s_alittle_render.PushRenderTriangle(m_texture, color, vertex_coord, texture_coord);
	}

private:
	SDL_Texture* m_texture = nullptr;
	CarpSurface* m_surface = nullptr;

private:
	int m_width = 0, m_height = 0;
	ALittleTextureRenderMode m_mode = ALittleTextureRenderMode::ATRM_LINEAR;
};


class ALittleRenderTexture : public ALittleTexture
{
public:
	ALittleRenderTexture() {}
	~ALittleRenderTexture() { Clear(); }

public:
	bool Draw(ALittleDisplayObject* object, int width, int height)
	{
		Clear();

		if (width <= 0 || height <= 0) return false;
		if (!SDL_RenderTargetSupported(s_alittle_render.GetRender())) return false;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 format = SDL_PIXELFORMAT_RGBA8888;
#else
		Uint32 format = SDL_PIXELFORMAT_ABGR8888;
#endif
		SDL_Texture* texture = SDL_CreateTexture(s_alittle_render.GetRender(), format, SDL_TEXTUREACCESS_TARGET, width, height);
		if (texture == 0) return false;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		SDL_Texture* old_texture = SDL_GetRenderTarget(s_alittle_render.GetRender());
		SDL_SetRenderTarget(s_alittle_render.GetRender(), texture);

		// set render blend
		SDL_SetRenderDrawBlendMode(s_alittle_render.GetRender(), SDL_BLENDMODE_BLEND);

		// clear color
		SDL_SetRenderDrawColor(s_alittle_render.GetRender(), 0, 0, 0, 0);
		SDL_RenderClear(s_alittle_render.GetRender());

		object->SetSelfMatrixDirty();
		object->Render(CarpMatrix2D(), false);
		object->SetSelfMatrixDirty();

		// present
		s_alittle_render.FlushRender();
		SDL_RenderPresent(s_alittle_render.GetRender());
		SDL_SetRenderTarget(s_alittle_render.GetRender(), old_texture);

		m_texture = texture;
		m_width = width;
		m_height = height;

		return true;
	}
	bool Save(const char* file_path, ALittleDisplayObject* object, int width, int height)
	{
		Clear();

		if (width <= 0 || height <= 0) return false;
		if (!SDL_RenderTargetSupported(s_alittle_render.GetRender())) return false;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 format = SDL_PIXELFORMAT_RGBA8888;
#else
		Uint32 format = SDL_PIXELFORMAT_ABGR8888;
#endif

		SDL_Texture* texture = SDL_CreateTexture(s_alittle_render.GetRender(), format, SDL_TEXTUREACCESS_TARGET, width, height);
		if (texture == 0) return false;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		SDL_Texture* old_texture = SDL_GetRenderTarget(s_alittle_render.GetRender());
		SDL_SetRenderTarget(s_alittle_render.GetRender(), texture);

		// set render blend
		SDL_SetRenderDrawBlendMode(s_alittle_render.GetRender(), SDL_BLENDMODE_BLEND);

		// clear color
		SDL_SetRenderDrawColor(s_alittle_render.GetRender(), 0, 0, 0, 0);
		SDL_RenderClear(s_alittle_render.GetRender());

		object->SetSelfMatrixDirty();
		object->Render(CarpMatrix2D(), false);
		object->SetSelfMatrixDirty();

		// present
		s_alittle_render.FlushRender();
		SDL_RenderPresent(s_alittle_render.GetRender());

		bool result = false;
		int renderer_width, renderer_height;
		SDL_GetRendererOutputSize(s_alittle_render.GetRender(), &renderer_width, &renderer_height);

		auto* surface = CarpSurfaceBind::CreateCarpSurface(renderer_width, renderer_height);
		if (surface)
		{
			int read_result = SDL_RenderReadPixels(s_alittle_render.GetRender(), 0, format, surface->GetPixels(), surface->GetPitch());
			if (read_result == 0)
			{
				if (!CarpSurfaceBind::SaveCarpSurface(surface, file_path))
					CARP_ERROR("SaveCarpSurface failed:" << file_path);
			}
			else
				CARP_ERROR("SDL_RenderReadPixels failed:" << renderer_width << ", " << renderer_height);
			CarpSurfaceBind::FreeCarpSurface(surface);
		}
		else
			CARP_ERROR("SDL_CreateRGBSurface failed:" << renderer_width << ", " << renderer_height);

		SDL_SetRenderTarget(s_alittle_render.GetRender(), old_texture);
		s_alittle_render.DestroyTexture(texture);

		return result;
	}
	
	void Clear() override
	{
		if (m_texture)
			s_alittle_render.DestroyTexture(m_texture);
		m_texture = 0;
		m_width = 0;
		m_height = 0;
	}

public:
	void Render(const CarpColor4& color, float* vertex_coord, float* texture_coord) override
	{
		if (m_texture == nullptr) return;
		s_alittle_render.PushRenderQuad(m_texture, color, vertex_coord, texture_coord);
	}
	void RenderTriangle(const CarpColor4& color, float* vertex_coord, float* texture_coord) override
	{
		if (m_texture == nullptr) return;
		s_alittle_render.PushRenderTriangle(m_texture, color, vertex_coord, texture_coord);
	}

public:
	int GetWidth() const override { return m_width; }
	int GetHeight() const override { return m_height; }

private:
	SDL_Texture* m_texture = nullptr;
	int m_width = 0;
	int m_height = 0;
};

extern int s_texture_loader_id_creator;

class ALittleTextureLoader : public CarpTask
{
public:
	ALittleTextureLoader()
	{
		++s_texture_loader_id_creator;
		m_id = s_texture_loader_id_creator;
	}
	~ALittleTextureLoader() {}

public:
	void Start() { s_carp_task_consumer.AddTask(this); }
	
	int GetID() const { return m_id; }
	
	void SetPath(const char* file_path, const char* atlas_info, int width, int height, bool crypt_mode)
	{
		m_file_path = file_path;
		m_atlas_info = atlas_info;
		m_crypt_mode = crypt_mode;
		m_width = width;
		m_height = height;
	}
	const char* GetPath() const { return m_file_path.c_str(); }

public:
	void Execute() override
	{
		CarpSurface* surface = 0;
		if (m_width > 0 && m_height > 0)
		{
			surface = CarpSurfaceBind::CreateCarpSurface(m_width, m_height);
		}

		std::vector<std::string> atlas_list;
		CarpString::Split(m_atlas_info, ";", atlas_list);
		for (unsigned int i = 0; i < atlas_list.size(); ++i)
		{
			std::vector<std::string> atlas_info;
			CarpString::Split(atlas_list[i], ",", atlas_info);
			if (atlas_info.size() < 1) continue;
			std::string file_path = atlas_info[0];
			if (atlas_info.size() < 2) continue;
			int t = std::atoi(atlas_info[1].c_str());
			if (atlas_info.size() < 3) continue;
			int b = std::atoi(atlas_info[2].c_str());
			if (atlas_info.size() < 4) continue;
			int l = std::atoi(atlas_info[3].c_str());
			if (atlas_info.size() < 5) continue;
			int r = std::atoi(atlas_info[4].c_str());
			if (atlas_info.size() < 6) continue;
			int w = std::atoi(atlas_info[5].c_str());
			if (atlas_info.size() < 7) continue;
			int h = std::atoi(atlas_info[6].c_str());

			CarpLocalFile file;
			file.SetPath(file_path.c_str());
			if (!file.Load(false))
			{
				if (surface) CarpSurfaceBind::FreeCarpSurface(surface);
				CARP_ERROR("LocalFile load failed, " << file_path);
				s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureLoadFailed", this); });
				return;
			}
			if (m_crypt_mode) file.Decrypt(0);

			// create surface
			auto* child_surface = CarpSurfaceBind::LoadSurface(file);
			if (!child_surface)
			{
				if (surface) CarpSurfaceBind::FreeCarpSurface(surface);
				CARP_ERROR("LoadImageFromMemory failed:" << file_path);
				s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureLoadFailed", this); });
				return;
			}
			
			if (surface == 0) { surface = child_surface; break; }

			CarpSurfaceBind::BlitCarpSurface(child_surface, surface, l, t);
			// top
			for (int i = 0; i < w; ++i)
			{
				unsigned int pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, i, 0);
				CarpSurfaceBind::SetCarpSurfacePixel(surface, l + i, t - 1, pixel);
			}

			// bottom
			for (int i = 0; i < w; ++i)
			{
				unsigned int pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, i, h - 1);
				CarpSurfaceBind::SetCarpSurfacePixel(surface, l + i, t + h, pixel);
			}

			// left
			for (int i = 0; i < h; ++i)
			{
				unsigned int pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, 0, i);
				CarpSurfaceBind::SetCarpSurfacePixel(surface, l - 1, t + i, pixel);
			}

			// right
			for (int i = 0; i < h; ++i)
			{
				unsigned int pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, w - 1, i);
				CarpSurfaceBind::SetCarpSurfacePixel(surface, l + w, t + i, pixel);
			}

			// left-top
			unsigned int pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, 0, 0);
			CarpSurfaceBind::SetCarpSurfacePixel(surface, l - 1, t - 1, pixel);
			// right-top
			pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, w - 1, 0);
			CarpSurfaceBind::SetCarpSurfacePixel(surface, l + w, t - 1, pixel);
			// left-bottom
			pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, 0, h - 1);
			CarpSurfaceBind::SetCarpSurfacePixel(surface, l - 1, t + h, pixel);
			// right-bottom
			pixel = CarpSurfaceBind::GetCarpSurfacePixel(child_surface, w - 1, h - 1);
			CarpSurfaceBind::SetCarpSurfacePixel(surface, l + w, t + h, pixel);

			CarpSurfaceBind::FreeCarpSurface(child_surface);
		}
		
		s_carp_task_consumer.PushEvent([this, surface]()
		{
			ALittleSurfaceTexture* texture = new ALittleSurfaceTexture(surface, ALittleTextureRenderMode::ATRM_LINEAR);
			texture->GenerateImpl();
			s_alittle_script.Invoke("__ALITTLEAPI_TextureLoadSucceed", this, (ALittleTexture*)texture);
		});
	}
	void Abandon() override
	{
		s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureLoadFailed", this); });
	}

private:
	std::string m_file_path;
	std::string m_atlas_info;
	bool m_crypt_mode = false;
	int m_width = 0, m_height = 0;
	int m_id = 0;
};


class ALittleTextureCutLoader : public CarpTask
{
public:
	ALittleTextureCutLoader()
	{
		++s_texture_loader_id_creator;
		m_id = s_texture_loader_id_creator;
	}
	~ALittleTextureCutLoader() = default;

public:
	int GetID() const { return m_id; }
	void SetPath(const char* file_path, int max_width, int max_height)
	{
		m_file_path = file_path;
		m_max_width = max_width;
		m_max_height = max_height;
	}
	void Start()
	{
		s_carp_task_consumer.AddTask(this);
	}
	const char* GetPath() const { return m_file_path.c_str(); }
	int GetMaxWidth() const { return m_max_width; }
	int GetMaxHeight() const { return m_max_height; }

public:
	void Execute() override
	{
		// surface
		CarpSurface* surface = nullptr;

		// load for local file
		CarpLocalFile local_file;
		local_file.SetPath(m_file_path.c_str());
		if (!local_file.Load(false))
		{
			CARP_ERROR("LocalFile load failed, " << m_file_path);
			s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureCutLoadFailed", this); });
			return;
		}

		// create surface
		surface = CarpSurfaceBind::LoadSurface(local_file);
		if (!surface)
		{
			CARP_ERROR("LoadImageFromMemory failed:" << m_file_path);
			s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureCutLoadFailed", this); });
			return;
		}

		if (m_max_width > 0 && m_max_height > 0 && (surface->GetWidth() > m_max_width || surface->GetHeight() > m_max_height))
		{
			float scale_x = (float)m_max_width / (float)surface->GetWidth();
			float scale_y = (float)m_max_height / (float)surface->GetHeight();

			float max_scale = scale_x;
			if (max_scale > scale_y) max_scale = scale_y;

			int adjust_width = int(max_scale * surface->GetWidth());
			if (adjust_width == 0) adjust_width = 1;
			int adjust_height = int(max_scale * surface->GetHeight());
			if (adjust_height == 0) adjust_height = 1;

			auto* new_surface = CarpSurfaceBind::CreateCarpSurface(adjust_width, adjust_height);
			new_surface->ScaleFrom(surface, nullptr, nullptr);
			CarpSurfaceBind::FreeCarpSurface(surface);
			surface = new_surface;
		}

		s_carp_task_consumer.PushEvent([this, surface]()
		{
			ALittleTexture* texture = new ALittleSurfaceTexture(surface, ALittleTextureRenderMode::ATRM_LINEAR);
			s_alittle_script.Invoke("__ALITTLEAPI_TextureCutLoadSucceed", this, texture);
		});
	}
	
	void Abandon() override
	{
		s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_TextureCutLoadFailed", this); });
	}

private:
	std::string m_file_path;
	int m_max_width = 0;
	int m_max_height = 0;
	int m_id = 0;
};

class ALittleTextureBind
{
public:
	static void Bind(lua_State* l_state)
	{

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleTexture>("__CPPAPITexture")
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleTextureWrap>("__CPPAPITextureWrap")
			.addConstructor<void(*)()>()
			.addFunction("SetTexture", &ALittleTextureWrap::SetTexture)
			.addFunction("GetTexture", &ALittleTextureWrap::GetTexture)
			.addFunction("GetWidth", &ALittleTextureWrap::GetWidth)
			.addFunction("GetHeight", &ALittleTextureWrap::GetHeight)
			.addFunction("Clear", &ALittleTextureWrap::Clear)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleRenderTexture, ALittleTexture>("__CPPAPIRenderTexture")
			.addConstructor<void(*)()>()
			.addFunction("Draw", &ALittleRenderTexture::Draw)
			.addFunction("Save", &ALittleRenderTexture::Save)
			.addFunction("Clear", &ALittleRenderTexture::Clear)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleTextureLoader>("__CPPAPITextureLoader")
			.addConstructor<void(*)()>()
			.addFunction("SetPath", &ALittleTextureLoader::SetPath)
			.addFunction("Start", &ALittleTextureLoader::Start)
			.addFunction("GetPath", &ALittleTextureLoader::GetPath)
			.addFunction("GetID", &ALittleTextureLoader::GetID)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleTextureCutLoader>("__CPPAPITextureCutLoader")
			.addConstructor<void(*)()>()
			.addFunction("GetMaxWidth", &ALittleTextureCutLoader::GetMaxWidth)
			.addFunction("GetMaxHeight", &ALittleTextureCutLoader::GetMaxHeight)
			.addFunction("SetPath", &ALittleTextureCutLoader::SetPath)
			.addFunction("Start", &ALittleTextureCutLoader::Start)
			.addFunction("GetPath", &ALittleTextureCutLoader::GetPath)
			.addFunction("GetID", &ALittleTextureCutLoader::GetID)
			.endClass();
	}
};

#endif

#ifdef ALITTLE_TEXTURE_IMPL
#ifndef ALITTLE_TEXTURE_IMPL_INCLUDE
#define ALITTLE_TEXTURE_IMPL_INCLUDE
int s_texture_loader_id_creator = 0;
#endif
#endif