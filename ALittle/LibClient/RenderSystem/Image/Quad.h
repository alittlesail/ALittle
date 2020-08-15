
#ifndef _ALITTLE_QUAD_H_
#define _ALITTLE_QUAD_H_

#include "Image.h"

namespace ALittle
{

class Quad : public Image
{
public:
	Quad();
	~Quad();

#ifdef __EMSCRIPTEN__
	void SetX(float x) { Image::SetX(x); }
	void SetY(float y) { Image::SetY(y); }

	void SetWidth(float width) { Image::SetWidth(width); }
	void SetHeight(float height) { Image::SetHeight(height); }

	void SetAngle(float angle) { Image::SetAngle(angle); }

	void SetScaleX(float x) { Image::SetScaleX(x); }
	void SetScaleY(float y) { Image::SetScaleY(y); }

	void SetCenterX(float x) { Image::SetCenterX(x); }
	void SetCenterY(float y) { Image::SetCenterY(y); }

	void SetRed(float red) { Image::SetRed(red); }
	void SetGreen(float green) { Image::SetGreen(green); }
	void SetBlue(float blue) { Image::SetBlue(blue); }
	void SetAlpha(float alpha) { Image::SetAlpha(alpha); }

	void SetVisible(bool visible) { Image::SetVisible(visible); }
	void SetClip(bool clip) { Image::SetClip(clip); }
#endif
};

} // ALittle

#endif // _ALITTLE_QUAD_H_
