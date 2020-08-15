
#ifndef _ALITTLE_DISPLAYVIEW_H_
#define _ALITTLE_DISPLAYVIEW_H_

#include "DisplayObjects.h"

#include <list>
#include <vector>

#include <SDL.h>

namespace ALittle
{

class DisplayView : public DisplayObjects
{
public:
	DisplayView();
	virtual ~DisplayView();

#ifdef __EMSCRIPTEN__
	void SetX(float x) { DisplayObjects::SetX(x); }
	void SetY(float y) { DisplayObjects::SetY(y); }

	void SetWidth(float width) { DisplayObjects::SetWidth(width); }
	void SetHeight(float height) { DisplayObjects::SetHeight(height); }

	void SetAngle(float angle) { DisplayObjects::SetAngle(angle); }

	void SetScaleX(float x) { DisplayObjects::SetScaleX(x); }
	void SetScaleY(float y) { DisplayObjects::SetScaleY(y); }

	void SetCenterX(float x) { DisplayObjects::SetCenterX(x); }
	void SetCenterY(float y) { DisplayObjects::SetCenterY(y); }

	void SetRed(float red) { DisplayObjects::SetRed(red); }
	void SetGreen(float green) { DisplayObjects::SetGreen(green); }
	void SetBlue(float blue) { DisplayObjects::SetBlue(blue); }
	void SetAlpha(float alpha) { DisplayObjects::SetAlpha(alpha); }

	void SetVisible(bool visible) { DisplayObjects::SetVisible(visible); }
	void SetClip(bool clip) { DisplayObjects::SetClip(clip); }

	void AddChild(DisplayObject* object) { DisplayObjects::AddChild(object);  }
	void AddChildAfter(DisplayObject* front_object, DisplayObject* target_object) { DisplayObjects::AddChildAfter(front_object, target_object); }
	void AddChildBefore(DisplayObject* back_object, DisplayObject* target_object) { DisplayObjects::AddChildBefore(back_object, target_object); }
	void RemoveChild(DisplayObject* object) { DisplayObjects::RemoveChild(object); }
	void RemoveAllChild() { DisplayObjects::RemoveAllChild();  }
#endif

public:
	virtual void Render(const Matrix2D& parent, bool parent_changed);

private:
	struct ScissorInfo { SDL_Rect rect; int r, b; };
	static std::vector<ScissorInfo> s_scissor_stack;
};

} // ALittle

#endif // _ALITTLE_DISPLAYVIEW_H_
