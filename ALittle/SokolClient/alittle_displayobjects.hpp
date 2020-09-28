#ifndef ALITTLE_DISPLAYOBJECTS_INCLUDED
#define ALITTLE_DISPLAYOBJECTS_INCLUDED (1)

#include "alittle_displayobject.hpp"

class ALittleDisplayObjects : public ALittleDisplayObject
{
public:
	ALittleDisplayObjects() {}
	virtual ~ALittleDisplayObjects() { RemoveAllChild(); }

public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.deriveClass<ALittleDisplayObjects, ALittleDisplayObject>("__CPPAPIDisplayObjects")
			.addConstructor<void(*)()>()
			.addFunction("SetScaleX", &ALittleDisplayObjects::SetScaleX)
			.addFunction("SetScaleY", &ALittleDisplayObjects::SetScaleY)
			.addFunction("SetCenterX", &ALittleDisplayObjects::SetCenterX)
			.addFunction("SetCenterY", &ALittleDisplayObjects::SetCenterY)
			.addFunction("SetAngle", &ALittleDisplayObjects::SetAngle)
			.addFunction("SetX", &ALittleDisplayObjects::SetX)
			.addFunction("SetY", &ALittleDisplayObjects::SetY)
			.addFunction("SetWidth", &ALittleDisplayObjects::SetWidth)
			.addFunction("SetHeight", &ALittleDisplayObjects::SetHeight)
			.addFunction("SetRed", &ALittleDisplayObjects::SetRed)
			.addFunction("SetGreen", &ALittleDisplayObjects::SetGreen)
			.addFunction("SetBlue", &ALittleDisplayObjects::SetBlue)
			.addFunction("SetAlpha", &ALittleDisplayObjects::SetAlpha)
			.addFunction("AddChild", &ALittleDisplayObjects::AddChild)
			.addFunction("AddChildAfter", &ALittleDisplayObjects::AddChildAfter)
			.addFunction("AddChildBefore", &ALittleDisplayObjects::AddChildBefore)
			.addFunction("RemoveChild", &ALittleDisplayObjects::RemoveChild)
			.addFunction("RemoveAllChild", &ALittleDisplayObjects::RemoveAllChild)
			.addFunction("SetVisible", &ALittleDisplayObjects::SetVisible)
			.addFunction("SetClip", &ALittleDisplayObjects::SetClip)
			.endClass();
	}
	
#ifdef __EMSCRIPTEN__
	void SetX(float x) { ALittleDisplayObject::SetX(x); }
	void SetY(float y) { ALittleDisplayObject::SetY(y); }

	void SetWidth(float width) { ALittleDisplayObject::SetWidth(width); }
	void SetHeight(float height) { ALittleDisplayObject::SetHeight(height); }

	void SetAngle(float angle) { ALittleDisplayObject::SetAngle(angle); }

	void SetScaleX(float x) { ALittleDisplayObject::SetScaleX(x); }
	void SetScaleY(float y) { ALittleDisplayObject::SetScaleY(y); }

	void SetCenterX(float x) { ALittleDisplayObject::SetCenterX(x); }
	void SetCenterY(float y) { ALittleDisplayObject::SetCenterY(y); }

	void SetRed(float red) { ALittleDisplayObject::SetRed(red); }
	void SetGreen(float green) { ALittleDisplayObject::SetGreen(green); }
	void SetBlue(float blue) { ALittleDisplayObject::SetBlue(blue); }
	void SetAlpha(float alpha) { ALittleDisplayObject::SetAlpha(alpha); }

	void SetVisible(bool visible) { ALittleDisplayObject::SetVisible(visible); }
	void SetClip(bool clip) { ALittleDisplayObject::SetClip(clip); }
#endif

public:
	void AddChild(ALittleDisplayObject* object)
	{
		if (object == nullptr) return;
		object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();

		if (m_head_node == nullptr)
		{
			m_head_node = object;
			m_tail_node = object;
			return;
		}

		m_tail_node->m_back_node = object;
		object->m_front_node = m_tail_node;
		m_tail_node = object;
	}
	void AddChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object)
	{
		if (target_object == nullptr) return;
		target_object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();

		if (m_head_node == nullptr)
		{
			AddChild(target_object);
			return;
		}

		if (front_object == nullptr) return;
		if (target_object == front_object) return;

		ALittleDisplayObject* back_node = front_object->m_back_node;

		front_object->m_back_node = target_object;
		target_object->m_front_node = front_object;
		target_object->m_back_node = back_node;
		if (back_node) back_node->m_front_node = target_object;

		if (m_tail_node == front_object)
			m_tail_node = target_object;
	}
	void AddChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object)
	{
		if (target_object == nullptr) return;
		target_object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();

		if (m_head_node == nullptr)
		{
			AddChild(target_object);
			return;
		}

		if (back_object == nullptr) return;
		if (target_object == back_object) return;

		ALittleDisplayObject* front_node = back_object->m_front_node;

		back_object->m_front_node = target_object;
		target_object->m_back_node = back_object;
		target_object->m_front_node = front_node;
		if (front_node) front_node->m_back_node = target_object;

		if (m_head_node == back_object)
			m_head_node = target_object;
	}
	void RemoveChild(ALittleDisplayObject* object)
	{
		if (object == nullptr) return;
		object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();

		ALittleDisplayObject* front_node = object->m_front_node;
		object->m_front_node = nullptr;
		ALittleDisplayObject* back_node = object->m_back_node;
		object->m_back_node = nullptr;

		if (front_node)
			front_node->m_back_node = back_node;
		if (back_node)
			back_node->m_front_node = front_node;

		if (object == m_head_node)
			m_head_node = back_node;

		if (object == m_tail_node)
			m_tail_node = front_node;
	}
	void RemoveAllChild()
	{
		SetSelfMatrixDirty();
		ALittleDisplayObject* node = m_head_node;
		while (node)
		{
			node->SetSelfMatrixDirty();
			ALittleDisplayObject* next = node->m_back_node;
			node->m_front_node = nullptr;
			node->m_back_node = nullptr;
			node = next;
		}

		m_head_node = nullptr;
		m_tail_node = nullptr;
	}

public:
	virtual void Render(const CarpMatrix2D& parent, bool parent_changed)
	{
		if (m_clip) return;
		if (!m_visible) return;
		if (m_head_node == nullptr) return;

		bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();

		ALittleDisplayObject* node = m_head_node;
		while (node)
		{
			node->Render(m_global_matrix, global_changed);
			node = node->m_back_node;
		}
	}

protected:
	ALittleDisplayObject* m_head_node = nullptr;
	ALittleDisplayObject* m_tail_node = nullptr;
};

#endif


