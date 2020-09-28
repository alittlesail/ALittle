#ifndef ALITTLE_DISPLAY_INCLUDED
#define ALITTLE_DISPLAY_INCLUDED (1)

#include "alittle_displayobject.hpp"
#include "alittle_displayobjects.hpp"

class ALittleDisplay
{

public:
	void Setup();
	void Shutdown()
	{
		m_layer_list.RemoveAllChild();
		m_special_layer_list.RemoveAllChild();
	}
	
public:
	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleDisplay>("__CPPAPIDisplaySystem")
			.addFunction("AddChild", &ALittleDisplay::AddChild)
			.addFunction("AddChildAfter", &ALittleDisplay::AddChildAfter)
			.addFunction("AddChildBefore", &ALittleDisplay::AddChildBefore)
			.addFunction("AddSpecialChild", &ALittleDisplay::AddSpecialChild)
			.addFunction("AddSpecialChildAfter", &ALittleDisplay::AddSpecialChildAfter)
			.addFunction("AddSpecialChildBefore", &ALittleDisplay::AddSpecialChildBefore)
			.addFunction("RemoveChild", &ALittleDisplay::RemoveChild)
			.addFunction("RemoveAllChild", &ALittleDisplay::RemoveAllChild)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_DisplaySystem");
	}
	
public:
	void AddSpecialChild(ALittleDisplayObject* object)
	{
		m_special_layer_list.AddChild(object);
	}

	void AddSpecialChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object)
	{
		m_special_layer_list.AddChildAfter(front_object, target_object);
	}

	void AddSpecialChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object)
	{
		m_special_layer_list.AddChildBefore(back_object, target_object);
	}

	void AddChild(ALittleDisplayObject* object)
	{
		m_layer_list.AddChild(object);
	}

	void AddChildAfter(ALittleDisplayObject* front_object, ALittleDisplayObject* target_object)
	{
		m_layer_list.AddChildAfter(front_object, target_object);
	}

	void AddChildBefore(ALittleDisplayObject* back_object, ALittleDisplayObject* target_object)
	{
		m_layer_list.AddChildBefore(back_object, target_object);
	}

	void RemoveChild(ALittleDisplayObject* object)
	{
		m_layer_list.RemoveChild(object);
	}

	void RemoveAllChild()
	{
		m_layer_list.RemoveAllChild();
		m_special_layer_list.RemoveAllChild();
	}

	void Render()
	{
		m_layer_list.Render(CarpMatrix2D(), false);
		m_special_layer_list.Render(CarpMatrix2D(), false);
	}

private:
	ALittleDisplayObjects m_layer_list;				// normal layer list
	ALittleDisplayObjects m_special_layer_list;		// special layer, render at last forever
};

extern ALittleDisplay s_alittle_display;

#endif

#ifdef ALITTLE_DISPLAY_IMPL
ALittleDisplay s_alittle_display;
#endif

