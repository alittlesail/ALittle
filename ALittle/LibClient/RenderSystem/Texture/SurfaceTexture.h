
#ifndef _ALITTLE_SURFACETEXTURE_H_
#define _ALITTLE_SURFACETEXTURE_H_

#include <SDL.h>
#include <vector>
#include <string>

#include "Texture.h"

namespace ALittle
{

class SurfaceTexture : public Texture
{
public:
	SurfaceTexture();
	SurfaceTexture(SDL_Surface* surface);
	~SurfaceTexture();

public:
	void GenerateImpl();

public:
	/**
	 * clear texture
	 */
	void Clear();

	/**
	 * get width and height
	 */
	int GetWidth() const;
	int GetHeight() const;

public:
	void Render(const Color4& color, float* vertex_coord, float* texture_coord);
	void RenderTriangle(const Color4& color, float* vertex_coord, float* texture_coord);

private:
	SDL_Texture* m_texture;
	SDL_Surface* m_surface;

private:
	int m_width, m_height;
};

} // ALittle

#endif // _ALITTLE_SURFACETEXTURE_H_
