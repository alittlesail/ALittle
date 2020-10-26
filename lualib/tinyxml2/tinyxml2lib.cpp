
extern "C" {
#include "tinyxml2lib.h"
}
#include "tinyxml2.h"
#include "carp_lua.hpp"

int luaopen_carp(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("tinyxml2")
		.beginClass<tinyxml2::XMLAttribute>("XMLAttribute")
		.addFunction("Name", &tinyxml2::XMLAttribute::Name)
		.addFunction("Value", &tinyxml2::XMLAttribute::Value)
		.addFunction("Next", &tinyxml2::XMLAttribute::Next)
		.addFunction("SetAttribute", &tinyxml2::XMLAttribute::SetAttributeForLua)
		.endClass()
		.beginClass<tinyxml2::XMLNode>("XMLNode")
		.addFunction("GetDocument", &tinyxml2::XMLNode::GetDocumentForLua)
		.addFunction("ToElement", &tinyxml2::XMLNode::ToElementForLua)
		.addFunction("ToText", &tinyxml2::XMLNode::ToTextForLua)
		.addFunction("ToComment", &tinyxml2::XMLNode::ToCommentForLua)
		.addFunction("ToDocument", &tinyxml2::XMLNode::ToDocumentForLua)
		.addFunction("ToDeclaration", &tinyxml2::XMLNode::ToDeclarationForLua)
		.addFunction("Value", &tinyxml2::XMLNode::Value)
		.addFunction("SetValue", &tinyxml2::XMLNode::SetValue)
		.addFunction("Parent", &tinyxml2::XMLNode::ParentFroLua)
		.addFunction("NoChildren", &tinyxml2::XMLNode::NoChildren)
		.addFunction("FirstChild", &tinyxml2::XMLNode::FirstChildForLua)
		.addFunction("NextSibling", &tinyxml2::XMLNode::NextSiblingForLua)
		.addFunction("LastChild", &tinyxml2::XMLNode::LastChildForLua)
		.addFunction("PreviousSibling", &tinyxml2::XMLNode::PreviousSiblingForLua)
		.addFunction("DeleteChild", &tinyxml2::XMLNode::DeleteChild)
		.addFunction("DeleteChildren", &tinyxml2::XMLNode::DeleteChildren)
		.addFunction("InsertEndChild", &tinyxml2::XMLNode::InsertEndChild)
		.addFunction("InsertFirstChild", &tinyxml2::XMLNode::InsertFirstChild)
		.addFunction("InsertAfterChild", &tinyxml2::XMLNode::InsertAfterChild)
		.endClass()
		.deriveClass<tinyxml2::XMLElement, tinyxml2::XMLNode>("XMLElement")
		.addFunction("Name", &tinyxml2::XMLElement::Name)
		.addFunction("SetName", &tinyxml2::XMLElement::SetName)
		.addFunction("Attribute", &tinyxml2::XMLElement::Attribute)
		.addFunction("SetAttribute", &tinyxml2::XMLElement::SetAttributeForLua)
		.addFunction("GetText", &tinyxml2::XMLElement::GetText)
		.addFunction("SetText", &tinyxml2::XMLElement::SetTextForLua)
		.addFunction("FirstAttribute", &tinyxml2::XMLElement::FirstAttribute)
		.endClass()
		.deriveClass<tinyxml2::XMLComment, tinyxml2::XMLNode>("XMLComment")
		.endClass()
		.deriveClass<tinyxml2::XMLDeclaration, tinyxml2::XMLNode>("XMLDeclaration")
		.endClass()
		.deriveClass<tinyxml2::XMLText, tinyxml2::XMLNode>("XMLText")
		.endClass()
		.deriveClass<tinyxml2::XMLDocument, tinyxml2::XMLNode>("XMLDocument")
		.addConstructor<void(*)()>()
		.addFunction("Parse", &tinyxml2::XMLDocument::ParseForLua)
		.addFunction("LoadFile", &tinyxml2::XMLDocument::LoadFileForLua)
		.addFunction("SaveFile", &tinyxml2::XMLDocument::SaveFileForLua)
		.addFunction("RootElement", &tinyxml2::XMLDocument::RootElementForLua)
		.addFunction("NewElement", &tinyxml2::XMLDocument::NewElement)
		.addFunction("NewComment", &tinyxml2::XMLDocument::NewComment)
		.addFunction("DeleteNode", &tinyxml2::XMLDocument::DeleteNode)
		.addFunction("NewDeclaration", &tinyxml2::XMLDocument::NewDeclaration)
		.addFunction("NewText", &tinyxml2::XMLDocument::NewText)
		.endClass()
		.endNamespace();
	
    lua_getglobal(l_state, "tinyxml2");
    return 1;
}
