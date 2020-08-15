
#ifndef _ALITTLE_TEXTURE_H_
#define _ALITTLE_TEXTURE_H_

#include "ALittle/LibClient/RenderSystem/Matrix2D.h"

namespace ALittle
{

class Texture
{
public:
	Texture() {}
	virtual ~Texture() {}

public:
	/**
	 * render
	 */
	virtual void Render(const Color4& color, float* vertex_coord, float* texture_coord) {}
	virtual void RenderTriangle(const Color4& color, float* vertex_coord, float* texture_coord) {}

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

class TextureWrap
{
public:
	TextureWrap() : m_texture(0) {}
	~TextureWrap() { if (m_texture) delete m_texture; }

public:
	void SetTexture(Texture* texture) { m_texture = texture; }
	Texture* GetTexture() { return m_texture; }
	void Clear() { if (m_texture == 0) return; m_texture->Clear(); }
	int GetWidth() const { if (m_texture) return m_texture->GetWidth(); return 0; }
	int GetHeight() const { if (m_texture) return m_texture->GetHeight(); return 0; }

public:
	Texture* m_texture;
};

} // ALittle

#endif // _ALITTLE_TEXTURE_H_
