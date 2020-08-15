
#include "DisplayObjects.h"

namespace ALittle
{

DisplayObjects::DisplayObjects()
: m_head_node(nullptr), m_tail_node(nullptr)
{
}

DisplayObjects::~DisplayObjects()
{
	RemoveAllChild();
}

void DisplayObjects::Render(const Matrix2D& parent, bool parent_changed)
{
	if (m_clip) return;
	if (!m_visible) return;
	if (m_head_node == nullptr) return;

	bool global_changed = UpdateGlobalMatrix2D(parent, parent_changed);
	UpdateVertexCoord();
	UpdateTextureCoord();
	
	DisplayObject* node = m_head_node;
	while (node)
	{
		node->Render(m_global_matrix, global_changed);
		node = node->m_back_node;
	}
}

void DisplayObjects::AddChild(DisplayObject* object)
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

void DisplayObjects::AddChildAfter(DisplayObject* front_object, DisplayObject* target_object)
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

	DisplayObject* back_node = front_object->m_back_node;

	front_object->m_back_node = target_object;
	target_object->m_front_node = front_object;
	target_object->m_back_node = back_node;
	if (back_node) back_node->m_front_node = target_object;

	if (m_tail_node == front_object)
		m_tail_node = target_object;
}

void DisplayObjects::AddChildBefore(DisplayObject* back_object, DisplayObject* target_object)
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

	DisplayObject* front_node = back_object->m_front_node;

	back_object->m_front_node = target_object;
	target_object->m_back_node = back_object;
	target_object->m_front_node = front_node;
	if (front_node) front_node->m_back_node = target_object;

	if (m_head_node == back_object)
		m_head_node = target_object;
}

void DisplayObjects::RemoveChild(DisplayObject* object)
{
	if (object == nullptr) return;
	object->SetSelfMatrixDirty();
	SetSelfMatrixDirty();
	
	DisplayObject* front_node = object->m_front_node;
	object->m_front_node = nullptr;
	DisplayObject* back_node = object->m_back_node;
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

void DisplayObjects::RemoveAllChild()
{
	SetSelfMatrixDirty();
	DisplayObject* node = m_head_node;
	while (node)
	{
		node->SetSelfMatrixDirty();
		DisplayObject* next = node->m_back_node;
		node->m_front_node = nullptr;
		node->m_back_node = nullptr;
		node = next;
	}

	m_head_node = nullptr;
	m_tail_node = nullptr;
}

} // ALittle
