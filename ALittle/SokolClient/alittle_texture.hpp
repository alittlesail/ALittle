#ifndef ALITTLE_TEXTURE_INCLUDED
#define ALITTLE_TEXTURE_INCLUDED (1)

#include "Carp/carp_matrix_2d.hpp"
#include "Carp/carp_surface.h"
#include "Carp/carp_log.hpp"

#include "alittle_render.hpp"

class ALittleTexture
{
public:
	ALittleTexture() {}
	virtual ~ALittleTexture() {}

public:
	virtual void Render(const CarpColor4& color, float* vertex_coord, float* texture_coord) {}
	virtual void RenderTriangle(const CarpColor4& color, float* vertex_coord, float* texture_coord) {}

	virtual void Clear() {}

	virtual int GetWidth() const { return 0; }
	virtual int GetHeight() const { return 0; }
};

class ALittleTextureWrap
{
public:
	ALittleTextureWrap() : m_texture(0) {}
	~ALittleTextureWrap() { if (m_texture) delete m_texture; }

public:
	void SetTexture(ALittleTexture* texture) { m_texture = texture; }
	ALittleTexture* GetTexture() { return m_texture; }
	void Clear() { if (m_texture == 0) return; m_texture->Clear(); }
	int GetWidth() const { if (m_texture) return m_texture->GetWidth(); return 0; }
	int GetHeight() const { if (m_texture) return m_texture->GetHeight(); return 0; }

public:
	ALittleTexture* m_texture;
};


class ALittleSurfaceTexture : public ALittleTexture
{
public:
	ALittleSurfaceTexture() {}
	ALittleSurfaceTexture(CARP_Surface* surface)
	{
		m_surface = surface;
		m_width = surface->w;
		m_height = surface->h;
	}
	~ALittleSurfaceTexture()
	{
		Clear();
	}

public:
	void GenerateImpl()
	{
		if (m_texture.id != SG_INVALID_ID) return;
		if (m_surface == nullptr) return;

		// if surface small then max texture size then create single texture
		if (m_surface->w <= s_alittle_render.GetMaxTextureWidth() && m_surface->h <= s_alittle_render.GetMaxTextureHeight())
		{
			m_texture = sg_alloc_image();
			sg_image_desc desc = { 0 };
			desc.width = m_surface->w;
			desc.height = m_surface->h;
			desc.pixel_format = SG_PIXELFORMAT_RGBA8;
			desc.min_filter = SG_FILTER_LINEAR;
			desc.mag_filter = SG_FILTER_LINEAR;
			desc.content.subimage[0][0].ptr = m_surface->pixels;
			desc.content.subimage[0][0].size = m_surface->w * m_surface->h * 4;
			sg_init_image(m_texture, &desc);
			Carp_FreeSurface(m_surface);
			m_surface = nullptr;
			return;
		}

		CARP_ERROR("surface is too large:" << m_surface->w << "," << m_surface->h);

		Carp_FreeSurface(m_surface);
		m_surface = 0;
	}

public:
	/**
	 * clear texture
	 */
	void Clear()
	{

		if (m_surface)
		{
			Carp_FreeSurface(m_surface);
			m_surface = 0;
		}

		sg_destroy_image(m_texture);
		m_texture = {0};

		m_width = 0;
		m_height = 0;
	}

	/**
	 * get width and height
	 */
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

public:
	void Render(const CarpColor4& color, float* vertex_coord, float* texture_coord);
	void RenderTriangle(const CarpColor4& color, float* vertex_coord, float* texture_coord);

private:
	sg_image m_texture = {0};
	CARP_Surface* m_surface = nullptr;

private:
	int m_width = 0, m_height = 0;
};

#endif
