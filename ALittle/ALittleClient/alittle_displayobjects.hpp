#ifndef ALITTLE_DISPLAYOBJECTS_INCLUDED
#define ALITTLE_DISPLAYOBJECTS_INCLUDED

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
			.addFunction("SetZ", &ALittleDisplayObjects::SetZ)
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
			.addFunction("SetSortChild", &ALittleDisplayObjects::SetSortChild)
			.addFunction("SetVisible", &ALittleDisplayObjects::SetVisible)
			.addFunction("SetClip", &ALittleDisplayObjects::SetClip)
			.endClass();
	}

	void SetX(float x) override { ALittleDisplayObject::SetX(x); }
	void SetY(float y) override { ALittleDisplayObject::SetY(y); }
	void SetZ(float z) override { ALittleDisplayObject::SetZ(z); }

	void SetWidth(float width) override { ALittleDisplayObject::SetWidth(width); }
	void SetHeight(float height) override { ALittleDisplayObject::SetHeight(height); }

	void SetAngle(float angle) override { ALittleDisplayObject::SetAngle(angle); }

	void SetScaleX(float x) override { ALittleDisplayObject::SetScaleX(x); }
	void SetScaleY(float y) override { ALittleDisplayObject::SetScaleY(y); }

	void SetCenterX(float x) override { ALittleDisplayObject::SetCenterX(x); }
	void SetCenterY(float y) override { ALittleDisplayObject::SetCenterY(y); }

	void SetRed(float red) override { ALittleDisplayObject::SetRed(red); }
	void SetGreen(float green) override { ALittleDisplayObject::SetGreen(green); }
	void SetBlue(float blue) override { ALittleDisplayObject::SetBlue(blue); }
	void SetAlpha(float alpha) override { ALittleDisplayObject::SetAlpha(alpha); }

	void SetVisible(bool visible) override { ALittleDisplayObject::SetVisible(visible); }
	void SetClip(bool clip) override { ALittleDisplayObject::SetClip(clip); }

public:
	virtual void SetSortDirty() override { m_sort_dirty = true; }
	virtual void SetSortChild(bool value) { m_sort_child = value; if (m_sort_child) m_sort_dirty = true; }

	virtual void AddChild(ALittleDisplayObject* object)
	{
		if (object == nullptr) return;
		object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();
		SetSortDirty();

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
	virtual void AddChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object)
	{
		if (target_object == nullptr) return;
		target_object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();
		SetSortDirty();

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
	virtual void AddChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object)
	{
		if (target_object == nullptr) return;
		target_object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();
		SetSortDirty();

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
	virtual void RemoveChild(ALittleDisplayObject* object)
	{
		if (object == nullptr) return;
		object->SetSelfMatrixDirty();
		SetSelfMatrixDirty();
		SetSortDirty();

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
	virtual void RemoveAllChild()
	{
		SetSelfMatrixDirty();
		SetSortDirty();
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
	void Render(const CarpMatrix2D& parent, bool parent_changed) override
	{
		if (m_clip) return;
		if (!m_visible) return;
		if (m_head_node == nullptr) return;

		const bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
		UpdateVertexCoord();
		UpdateTextureCoord();
		RenderImpl(global_changed);
	}

protected:
	void RenderImpl(bool global_changed)
	{
		if (!m_sort_child)
		{
			ALittleDisplayObject* node = m_head_node;
			while (node)
			{
				node->Render(m_global_matrix, global_changed);
				node = node->m_back_node;
			}
		}
		else
		{
			if (m_sort_dirty)
			{
				m_sort_dirty = false;
				m_sort_list.resize(0);

				ALittleDisplayObject* node = m_head_node;
				while (node)
				{
					m_sort_list.push_back(node);
					node = node->m_back_node;
				}

				std::sort(m_sort_list.begin(), m_sort_list.end(), [](const ALittleDisplayObject* a, const ALittleDisplayObject* b) -> bool { return a->GetZ() < b->GetZ(); });
			}

			for (auto& node : m_sort_list)
				node->Render(m_global_matrix, global_changed);
		}
	}

protected:
	ALittleDisplayObject* m_head_node = nullptr;
	ALittleDisplayObject* m_tail_node = nullptr;

	std::vector<ALittleDisplayObject*> m_sort_list;

	bool m_sort_dirty = false;
	bool m_sort_child = false;
};

#endif


