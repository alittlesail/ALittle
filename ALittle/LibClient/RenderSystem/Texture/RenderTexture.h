
#ifndef _ALITTLE_RENDERTEXTURE_H_
#define _ALITTLE_RENDERTEXTURE_H_

#include "ALittle/LibClient/RenderSystem/DisplayObject/DisplayObject.h"
#include "ALittle/LibClient/RenderSystem/Texture/Texture.h"

#include <SDL.h>

namespace ALittle
{

class RenderTexture : public Texture
{
public:
	RenderTexture();
	~RenderTexture();

public:
	bool Draw(DisplayObject* object, int width, int height);
	bool Save(const char* file_path, DisplayObject* object, int width, int height);
	void Clear();

public:
	void Render(const Color4& color, float* vertex_coord, float* texture_coord);
	void RenderTriangle(const Color4& color, float* vertex_coord, float* texture_coord);

public:
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	SDL_Texture* m_texture;
	int m_width;
	int m_height;
};

} // ALittle

#endif // _ALITTLE_RENDERTEXTURE_H_
