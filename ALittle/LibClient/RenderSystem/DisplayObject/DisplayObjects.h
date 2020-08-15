
#ifndef _ALITTLE_DisplayObjects_H_
#define _ALITTLE_DisplayObjects_H_

#include "DisplayObject.h"
#include "ALittle/LibClient/RenderSystem/Matrix2D.h"

#include <list>

namespace ALittle
{

class DisplayObjects : public DisplayObject
{
public:
	DisplayObjects();
	virtual ~DisplayObjects();

#ifdef __EMSCRIPTEN__
	void SetX(float x) { DisplayObject::SetX(x); }
	void SetY(float y) { DisplayObject::SetY(y); }

	void SetWidth(float width) { DisplayObject::SetWidth(width); }
	void SetHeight(float height) { DisplayObject::SetHeight(height); }

	void SetAngle(float angle) { DisplayObject::SetAngle(angle); }
	
	void SetScaleX(float x) { DisplayObject::SetScaleX(x); }
	void SetScaleY(float y) { DisplayObject::SetScaleY(y); }

	void SetCenterX(float x) { DisplayObject::SetCenterX(x); }
	void SetCenterY(float y) { DisplayObject::SetCenterY(y); }

	void SetRed(float red) { DisplayObject::SetRed(red); }
	void SetGreen(float green) { DisplayObject::SetGreen(green); }
	void SetBlue(float blue) { DisplayObject::SetBlue(blue); }
	void SetAlpha(float alpha) { DisplayObject::SetAlpha(alpha); }

	void SetVisible(bool visible) { DisplayObject::SetVisible(visible); }
	void SetClip(bool clip) { DisplayObject::SetClip(clip); }
#endif

public:
	void AddChild(DisplayObject* object);
	void AddChildAfter(DisplayObject* front_object, DisplayObject* target_object);
	void AddChildBefore(DisplayObject* back_object, DisplayObject* target_object );
	void RemoveChild(DisplayObject* object);
	void RemoveAllChild();

public:
	virtual void Render(const Matrix2D& parent, bool parent_changed);

protected:
	DisplayObject* m_head_node;
	DisplayObject* m_tail_node;
};

} // ALittle

#endif // _ALITTLE_DisplayObjects_H_
