
#include "Quad.h"

#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"

namespace ALittle
{

Quad::Quad()
{
	m_texture = g_DisplaySystem.GetQuadTexture();
	SetTextureCoord(0.1f, 0.9f, 0.1f, 0.9f);
}

Quad::~Quad()
{
}

} // ALittle
