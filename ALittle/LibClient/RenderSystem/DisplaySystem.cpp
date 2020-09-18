
#include "DisplaySystem.h"
#include "RenderSystem.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

#include "ALittle/LibClient/Helper/TextureHelper.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"

#include "ALittle/LibCommon/ScriptSystem/ScriptSystem.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"

#include "DisplayObject/DisplayView.h"

#include "Image/Quad.h"
#include "Image/Image.h"
#include "Image/Triangle.h"
#include "Image/Grid9Image.h"
#include "Image/Sprite.h"
#include "Text/Text.h"
#include "TextArea/TextArea.h"
#include "TextInput/TextInput.h"
#include "TextEdit/TextEdit.h"

#include "Texture/Texture.h"
#include "Texture/RenderTexture.h"
#include "Texture/SurfaceTexture.h"
#include "Texture/TextureLoader.h"
#include "Texture/TextureCutLoader.h"

#include <SDL.h>

#include "ALittle/LibClient/Helper/FontHelper.h"

namespace ALittle
{

DisplaySystem::DisplaySystem()
	: m_quad_texture(0)
{ }

DisplaySystem::~DisplaySystem() {}

DisplaySystem& DisplaySystem::Instance()
{
	static DisplaySystem instance;
	return instance;
}

void DisplaySystem::Setup()
{
	g_ScheduleSystem.RegisterHandle(TEXTURE_LOAD_SUCCEED, TextureLoader::HandleEvent);
	g_ScheduleSystem.RegisterHandle(TEXTURE_LOAD_FAILED, TextureLoader::HandleEvent);

	g_ScheduleSystem.RegisterHandle(TEXTURECUT_LOAD_SUCCEED, TextureCutLoader::HandleEvent);
	g_ScheduleSystem.RegisterHandle(TEXTURECUT_LOAD_FAILED, TextureCutLoader::HandleEvent);
}

void DisplaySystem::Shutdown()
{
	m_layer_list.RemoveAllChild();
	m_special_layer_list.RemoveAllChild();

	if (m_quad_texture)
	{
		delete m_quad_texture;
		m_quad_texture = 0;
	}

	ClearFont();
}

void DisplaySystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<DisplayObject>("__CPPAPIDisplayObject")
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<DisplayObjects, DisplayObject>("__CPPAPIDisplayObjects")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &DisplayObjects::SetScaleX)
		.addFunction("SetScaleY", &DisplayObjects::SetScaleY)
		.addFunction("SetCenterX", &DisplayObjects::SetCenterX)
		.addFunction("SetCenterY", &DisplayObjects::SetCenterY)
		.addFunction("SetAngle", &DisplayObjects::SetAngle)
		.addFunction("SetX", &DisplayObjects::SetX)
		.addFunction("SetY", &DisplayObjects::SetY)
		.addFunction("SetWidth", &DisplayObjects::SetWidth)
		.addFunction("SetHeight", &DisplayObjects::SetHeight)
		.addFunction("SetRed", &DisplayObjects::SetRed)
		.addFunction("SetGreen", &DisplayObjects::SetGreen)
		.addFunction("SetBlue", &DisplayObjects::SetBlue)
		.addFunction("SetAlpha", &DisplayObjects::SetAlpha)
		.addFunction("AddChild", &DisplayObjects::AddChild)
		.addFunction("AddChildAfter", &DisplayObjects::AddChildAfter)
		.addFunction("AddChildBefore", &DisplayObjects::AddChildBefore)
		.addFunction("RemoveChild", &DisplayObjects::RemoveChild)
		.addFunction("RemoveAllChild", &DisplayObjects::RemoveAllChild)
		.addFunction("SetVisible", &DisplayObjects::SetVisible)
		.addFunction("SetClip", &DisplayObjects::SetClip)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Image, DisplayObject>("__CPPAPIImage")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &Image::SetScaleX)
		.addFunction("SetScaleY", &Image::SetScaleY)
		.addFunction("SetCenterX", &Image::SetCenterX)
		.addFunction("SetCenterY", &Image::SetCenterY)
		.addFunction("SetAngle", &Image::SetAngle)
		.addFunction("SetFlip", &Image::SetFlip)
		.addFunction("SetX", &Image::SetX)
		.addFunction("SetY", &Image::SetY)
		.addFunction("SetWidth", &Image::SetWidth)
		.addFunction("SetHeight", &Image::SetHeight)
		.addFunction("SetRed", &Image::SetRed)
		.addFunction("SetGreen", &Image::SetGreen)
		.addFunction("SetBlue", &Image::SetBlue)
		.addFunction("SetAlpha", &Image::SetAlpha)
		.addFunction("SetTexture", &Image::SetTexture)
		.addFunction("ClearTexture", &Image::ClearTexture)
		.addFunction("SetTextureCoord", &Image::SetTextureCoord)
		.addFunction("SetVisible", &Image::SetVisible)
		.addFunction("SetClip", &Image::SetClip)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Quad, Image>("__CPPAPIQuad")
		.addConstructor<void(*)()>()
		.addFunction("SetX", &Quad::SetX)
		.addFunction("SetY", &Quad::SetY)
		.addFunction("SetWidth", &Quad::SetWidth)
		.addFunction("SetHeight", &Quad::SetHeight)
		.addFunction("SetScaleX", &Quad::SetScaleX)
		.addFunction("SetScaleY", &Quad::SetScaleY)
		.addFunction("SetCenterX", &Quad::SetCenterX)
		.addFunction("SetCenterY", &Quad::SetCenterY)
		.addFunction("SetAngle", &Quad::SetAngle)
		.addFunction("SetRed", &Quad::SetRed)
		.addFunction("SetGreen", &Quad::SetGreen)
		.addFunction("SetBlue", &Quad::SetBlue)
		.addFunction("SetAlpha", &Quad::SetAlpha)
		.addFunction("SetVisible", &Quad::SetVisible)
		.addFunction("SetClip", &Quad::SetClip)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Sprite, Image>("__CPPAPISprite")
		.addConstructor<void(*)()>()
		.addFunction("SetX", &Sprite::SetX)
		.addFunction("SetY", &Sprite::SetY)
		.addFunction("SetWidth", &Sprite::SetWidth)
		.addFunction("SetHeight", &Sprite::SetHeight)
		.addFunction("SetRed", &Sprite::SetRed)
		.addFunction("SetGreen", &Sprite::SetGreen)
		.addFunction("SetBlue", &Sprite::SetBlue)
		.addFunction("SetAlpha", &Sprite::SetAlpha)
		.addFunction("SetTexture", &Sprite::SetTexture)
		.addFunction("ClearTexture", &Sprite::ClearTexture)
		.addFunction("SetTextureCoord", &Sprite::SetTextureCoord)
		.addFunction("SetVisible", &Sprite::SetVisible)
		.addFunction("SetClip", &Sprite::SetClip)
		.addFunction("SetScaleX", &Sprite::SetScaleX)
		.addFunction("SetScaleY", &Sprite::SetScaleY)
		.addFunction("SetCenterX", &Sprite::SetCenterX)
		.addFunction("SetCenterY", &Sprite::SetCenterY)
		.addFunction("SetAngle", &Sprite::SetAngle)
		.addFunction("SetFlip", &Sprite::SetFlip)
		.addFunction("SetRowColCount", &Sprite::SetRowColCount)
		.addFunction("SetRowColIndex", &Sprite::SetRowColIndex)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Triangle, DisplayObject>("__CPPAPITriangle")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &Triangle::SetScaleX)
		.addFunction("SetScaleY", &Triangle::SetScaleY)
		.addFunction("SetCenterX", &Triangle::SetCenterX)
		.addFunction("SetCenterY", &Triangle::SetCenterY)
		.addFunction("SetAngle", &Triangle::SetAngle)
		.addFunction("SetX", &Triangle::SetX)
		.addFunction("SetY", &Triangle::SetY)
		.addFunction("SetWidth", &Triangle::SetWidth)
		.addFunction("SetHeight", &Triangle::SetHeight)
		.addFunction("SetRed", &Triangle::SetRed)
		.addFunction("SetGreen", &Triangle::SetGreen)
		.addFunction("SetBlue", &Triangle::SetBlue)
		.addFunction("SetAlpha", &Triangle::SetAlpha)
		.addFunction("SetTexture", &Triangle::SetTexture)
		.addFunction("ClearTexture", &Triangle::ClearTexture)
		.addFunction("SetTextureCoord", &Triangle::SetTextureCoord)
		.addFunction("SetVisible", &Triangle::SetVisible)
		.addFunction("SetClip", &Triangle::SetClip)
		.addFunction("SetPosXY", &Triangle::SetPosXY)
		.addFunction("SetTexUV", &Triangle::SetTexUV)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Grid9Image, DisplayObjects>("__CPPAPIGrid9Image")
		.addConstructor<void(*)()>()
		.addFunction("SetX", &Grid9Image::SetX)
		.addFunction("SetY", &Grid9Image::SetY)
		.addFunction("SetWidth", &Grid9Image::SetWidth)
		.addFunction("SetHeight", &Grid9Image::SetHeight)
		.addFunction("SetRed", &Grid9Image::SetRed)
		.addFunction("SetGreen", &Grid9Image::SetGreen)
		.addFunction("SetBlue", &Grid9Image::SetBlue)
		.addFunction("SetAlpha", &Grid9Image::SetAlpha)
		.addFunction("SetTexture", &Grid9Image::SetTexture)
		.addFunction("ClearTexture", &Grid9Image::ClearTexture)
		.addFunction("SetTextureCoord", &Grid9Image::SetTextureCoord)
		.addFunction("SetVisible", &Grid9Image::SetVisible)
		.addFunction("SetClip", &Grid9Image::SetClip)
		.addFunction("SetScaleX", &Grid9Image::SetScaleX)
		.addFunction("SetScaleY", &Grid9Image::SetScaleY)
		.addFunction("SetCenterX", &Grid9Image::SetCenterX)
		.addFunction("SetCenterY", &Grid9Image::SetCenterY)
		.addFunction("SetAngle", &Grid9Image::SetAngle)
		.addFunction("SetFlip", &Grid9Image::SetFlip)
		.addFunction("SetTopSize", &Grid9Image::SetTopSize)
		.addFunction("SetBottomSize", &Grid9Image::SetBottomSize)
		.addFunction("SetLeftSize", &Grid9Image::SetLeftSize)
		.addFunction("SetRightSize", &Grid9Image::SetRightSize)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<DisplayView, DisplayObjects>("__CPPAPIDisplayView")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &DisplayView::SetScaleX)
		.addFunction("SetScaleY", &DisplayView::SetScaleY)
		.addFunction("SetCenterX", &DisplayView::SetCenterX)
		.addFunction("SetCenterY", &DisplayView::SetCenterY)
		.addFunction("SetAngle", &DisplayView::SetAngle)
		.addFunction("SetX", &DisplayView::SetX)
		.addFunction("SetY", &DisplayView::SetY)
		.addFunction("SetWidth", &DisplayView::SetWidth)
		.addFunction("SetHeight", &DisplayView::SetHeight)
		.addFunction("SetRed", &DisplayView::SetRed)
		.addFunction("SetGreen", &DisplayView::SetGreen)
		.addFunction("SetBlue", &DisplayView::SetBlue)
		.addFunction("SetAlpha", &DisplayView::SetAlpha)
		.addFunction("AddChild", &DisplayView::AddChild)
		.addFunction("AddChildAfter", &DisplayView::AddChildAfter)
		.addFunction("AddChildBefore", &DisplayView::AddChildBefore)
		.addFunction("RemoveChild", &DisplayView::RemoveChild)
		.addFunction("RemoveAllChild", &DisplayView::RemoveAllChild)
		.addFunction("SetVisible", &DisplayView::SetVisible)
		.addFunction("SetClip", &DisplayView::SetClip)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<Text, Image>("__CPPAPIText")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &Text::SetScaleX)
		.addFunction("SetScaleY", &Text::SetScaleY)
		.addFunction("SetCenterX", &Text::SetCenterX)
		.addFunction("SetCenterY", &Text::SetCenterY)
		.addFunction("SetAngle", &Text::SetAngle)
		.addFunction("SetX", &Text::SetX)
		.addFunction("SetY", &Text::SetY)
		.addFunction("SetWidth", &Text::SetWidth)
		.addFunction("SetHeight", &Text::SetHeight)
		.addFunction("SetRed", &Text::SetRed)
		.addFunction("SetGreen", &Text::SetGreen)
		.addFunction("SetBlue", &Text::SetBlue)
		.addFunction("SetAlpha", &Text::SetAlpha)
		.addFunction("SetFont", &Text::SetFont)
		.addFunction("SetText", &Text::SetText)
		.addFunction("GetRealWidth", &Text::GetRealWidth)
		.addFunction("GetRealHeight", &Text::GetRealHeight)
		.addFunction("AdjustSize", &Text::AdjustSize)
		.addFunction("SetVisible", &Text::SetVisible)
		.addFunction("SetBold", &Text::SetBold)
		.addFunction("SetDeleteline", &Text::SetDeleteline)
		.addFunction("SetUnderline", &Text::SetUnderline)
		.addFunction("SetItalic", &Text::SetItalic)
		.addFunction("SetClip", &Text::SetClip)
		.addFunction("SetFlip", &Text::SetFlip)
		.addFunction("GetFontHeight", &Text::GetFontHeight)
		.addFunction("CutTextByWidth", &Text::CutTextByWidth)
		.addFunction("CalcTextWidth", &Text::CalcTextWidth)
		.addFunction("NeedDraw", &Text::NeedDraw)
		.addFunction("GetCutWidthListCount", &Text::GetCutWidthListCount)
		.addFunction("GetCutWidthByIndex", &Text::GetCutWidthByIndex)
		.addFunction("ClearCutWidthCache", &Text::ClearCutWidthCache)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<TextArea, Image>("__CPPAPITextArea")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &TextArea::SetScaleX)
		.addFunction("SetScaleY", &TextArea::SetScaleY)
		.addFunction("SetCenterX", &TextArea::SetCenterX)
		.addFunction("SetCenterY", &TextArea::SetCenterY)
		.addFunction("SetAngle", &TextArea::SetAngle)
		.addFunction("SetX", &TextArea::SetX)
		.addFunction("SetY", &TextArea::SetY)
		.addFunction("SetWidth", &TextArea::SetWidth)
		.addFunction("SetHeight", &TextArea::SetHeight)
		.addFunction("SetRed", &TextArea::SetRed)
		.addFunction("SetGreen", &TextArea::SetGreen)
		.addFunction("SetBlue", &TextArea::SetBlue)
		.addFunction("SetAlpha", &TextArea::SetAlpha)
		.addFunction("SetFont", &TextArea::SetFont)
		.addFunction("SetText", &TextArea::SetText)
		.addFunction("GetRealHeight", &TextArea::GetRealHeight)
		.addFunction("SetVisible", &TextArea::SetVisible)
		.addFunction("SetBold", &TextArea::SetBold)
		.addFunction("SetDeleteline", &TextArea::SetDeleteline)
		.addFunction("SetUnderline", &TextArea::SetUnderline)
		.addFunction("SetItalic", &TextArea::SetItalic)
		.addFunction("SetClip", &TextArea::SetClip)
		.addFunction("SetFlip", &TextArea::SetFlip)
		.addFunction("SetHAlign", &TextArea::SetHAlign)
		.addFunction("SetVAlign", &TextArea::SetVAlign)
		.addFunction("NeedDraw", &TextArea::NeedDraw)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<TextInput, Image>("__CPPAPITextInput")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &TextInput::SetScaleX)
		.addFunction("SetScaleY", &TextInput::SetScaleY)
		.addFunction("SetCenterX", &TextInput::SetCenterX)
		.addFunction("SetCenterY", &TextInput::SetCenterY)
		.addFunction("SetAngle", &TextInput::SetAngle)
		.addFunction("SetX", &TextInput::SetX)
		.addFunction("SetY", &TextInput::SetY)
		.addFunction("SetWidth", &TextInput::SetWidth)
		.addFunction("SetHeight", &TextInput::SetHeight)
		.addFunction("SetRed", &TextInput::SetRed)
		.addFunction("SetGreen", &TextInput::SetGreen)
		.addFunction("SetBlue", &TextInput::SetBlue)
		.addFunction("SetAlpha", &TextInput::SetAlpha)
		.addFunction("SetCursorRed", &TextInput::SetCursorRed)
		.addFunction("SetCursorGreen", &TextInput::SetCursorGreen)
		.addFunction("SetCursorBlue", &TextInput::SetCursorBlue)
		.addFunction("SetCursorAlpha", &TextInput::SetCursorAlpha)
		.addFunction("SetFont", &TextInput::SetFont)
		.addFunction("SetText", &TextInput::SetText)
		.addFunction("SetDefaultText", &TextInput::SetDefaultText)
		.addFunction("SetDefaultTextAlpha", &TextInput::SetDefaultTextAlpha)
		.addFunction("IsDefaultText", &TextInput::IsDefaultText)
		.addFunction("SetVisible", &TextInput::SetVisible)
		.addFunction("GetText", &TextInput::GetText)
		.addFunction("InsertText", &TextInput::InsertText)
		.addFunction("DeleteText", &TextInput::DeleteText)
		.addFunction("CursorOffset", &TextInput::CursorOffset)
		.addFunction("SelectCursorOffset", &TextInput::SelectCursorOffset)
		.addFunction("SelectAll", &TextInput::SelectAll)
		.addFunction("ClickCursor", &TextInput::ClickCursor)
		.addFunction("ClickWordCursor", &TextInput::ClickWordCursor)
		.addFunction("ShowCursor", &TextInput::ShowCursor)
		.addFunction("SetCursorToHome", &TextInput::SetCursorToHome)
		.addFunction("SetCursorToEnd", &TextInput::SetCursorToEnd)
		.addFunction("SetBold", &TextInput::SetBold)
		.addFunction("SetDeleteline", &TextInput::SetDeleteline)
		.addFunction("SetUnderline", &TextInput::SetUnderline)
		.addFunction("SetItalic", &TextInput::SetItalic)
		.addFunction("SetPasswordMode", &TextInput::SetPasswordMode)
		.addFunction("SetClip", &TextInput::SetClip)
		.addFunction("SetFlip", &TextInput::SetFlip)
		.addFunction("GetSelectText", &TextInput::GetSelectText)
		.addFunction("DeleteSelectText", &TextInput::DeleteSelectText)
		.addFunction("DragCursorBegin", &TextInput::DragCursorBegin)
		.addFunction("DragCursor", &TextInput::DragCursor)
		.addFunction("GetCursorX", &TextInput::GetCursorX)
		.addFunction("GetCursorY", &TextInput::GetCursorY)
		.addFunction("GetCursorHeight", &TextInput::GetCursorHeight)
		.addFunction("NeedDraw", &TextInput::NeedDraw)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<TextEdit, Image>("__CPPAPITextEdit")
		.addConstructor<void(*)()>()
		.addFunction("SetScaleX", &TextEdit::SetScaleX)
		.addFunction("SetScaleY", &TextEdit::SetScaleY)
		.addFunction("SetCenterX", &TextEdit::SetCenterX)
		.addFunction("SetCenterY", &TextEdit::SetCenterY)
		.addFunction("SetAngle", &TextEdit::SetAngle)
		.addFunction("SetX", &TextEdit::SetX)
		.addFunction("SetY", &TextEdit::SetY)
		.addFunction("SetWidth", &TextEdit::SetWidth)
		.addFunction("SetHeight", &TextEdit::SetHeight)
		.addFunction("SetRed", &TextEdit::SetRed)
		.addFunction("SetGreen", &TextEdit::SetGreen)
		.addFunction("SetBlue", &TextEdit::SetBlue)
		.addFunction("SetAlpha", &TextEdit::SetAlpha)
		.addFunction("SetCursorRed", &TextEdit::SetCursorRed)
		.addFunction("SetCursorGreen", &TextEdit::SetCursorGreen)
		.addFunction("SetCursorBlue", &TextEdit::SetCursorBlue)
		.addFunction("SetCursorAlpha", &TextEdit::SetCursorAlpha)
		.addFunction("SetFont", &TextEdit::SetFont)
		.addFunction("SetText", &TextEdit::SetText)
		.addFunction("SetDefaultText", &TextEdit::SetDefaultText)
		.addFunction("SetDefaultTextAlpha", &TextEdit::SetDefaultTextAlpha)
		.addFunction("IsDefaultText", &TextEdit::IsDefaultText)
		.addFunction("SetVisible", &TextEdit::SetVisible)
		.addFunction("GetText", &TextEdit::GetText)
		.addFunction("InsertText", &TextEdit::InsertText)
		.addFunction("DeleteText", &TextEdit::DeleteText)
		.addFunction("CursorOffsetLR", &TextEdit::CursorOffsetLR)
		.addFunction("SelectCursorOffsetLR", &TextEdit::SelectCursorOffsetLR)
		.addFunction("CursorOffsetUD", &TextEdit::CursorOffsetUD)
		.addFunction("SelectCursorOffsetUD", &TextEdit::SelectCursorOffsetUD)
		.addFunction("ClickCursor", &TextEdit::ClickCursor)
		.addFunction("ClickWordCursor", &TextEdit::ClickWordCursor)
		.addFunction("ShowCursor", &TextEdit::ShowCursor)
		.addFunction("SetCursorToHome", &TextEdit::SetCursorToHome)
		.addFunction("SetCursorToEnd", &TextEdit::SetCursorToEnd)
		.addFunction("SelectAll", &TextEdit::SelectAll)
		.addFunction("SetBold", &TextEdit::SetBold)
		.addFunction("SetDeleteline", &TextEdit::SetDeleteline)
		.addFunction("SetUnderline", &TextEdit::SetUnderline)
		.addFunction("SetItalic", &TextEdit::SetItalic)
		.addFunction("SetClip", &TextEdit::SetClip)
		.addFunction("SetFlip", &TextEdit::SetFlip)
		.addFunction("GetSelectText", &TextEdit::GetSelectText)
		.addFunction("DeleteSelectText", &TextEdit::DeleteSelectText)
		.addFunction("DragCursorBegin", &TextEdit::DragCursorBegin)
		.addFunction("DragCursor", &TextEdit::DragCursor)
		.addFunction("GetCursorX", &TextEdit::GetCursorX)
		.addFunction("GetCursorY", &TextEdit::GetCursorY)
		.addFunction("GetCursorHeight", &TextEdit::GetCursorHeight)
		.addFunction("GetRealHeight", &TextEdit::GetRealHeight)
		.addFunction("GetLineWidth", &TextEdit::GetLineWidth)
		.addFunction("GetLineCount", &TextEdit::GetLineCount)
		.addFunction("GetScrollOffset", &TextEdit::GetScrollOffset)
		.addFunction("NeedDraw", &TextEdit::NeedDraw)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<Texture>("__CPPAPITexture")
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<TextureWrap>("__CPPAPITextureWrap")
		.addConstructor<void(*)()>()
		.addFunction("SetTexture", &TextureWrap::SetTexture)
		.addFunction("GetTexture", &TextureWrap::GetTexture)
		.addFunction("GetWidth", &TextureWrap::GetWidth)
		.addFunction("GetHeight", &TextureWrap::GetHeight)
		.addFunction("Clear", &TextureWrap::Clear)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.deriveClass<RenderTexture, Texture>("__CPPAPIRenderTexture")
		.addConstructor<void(*)()>()
		.addFunction("Draw", &RenderTexture::Draw)
		.addFunction("Save", &RenderTexture::Save)
		.addFunction("Clear", &RenderTexture::Clear)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<TextureLoader>("__CPPAPITextureLoader")
		.addConstructor<void(*)()>()
        .addFunction("SetPath", &TextureLoader::SetPath)
        .addFunction("Start", &TextureLoader::Start)
		.addFunction("GetPath", &TextureLoader::GetPath)
		.addFunction("GetID", &TextureLoader::GetID)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<TextureCutLoader>("__CPPAPITextureCutLoader")
		.addConstructor<void(*)()>()
		.addFunction("GetMaxWidth", &TextureCutLoader::GetMaxWidth)
		.addFunction("GetMaxHeight", &TextureCutLoader::GetMaxHeight)
        .addFunction("SetPath", &TextureCutLoader::SetPath)
        .addFunction("Start", &TextureCutLoader::Start)
		.addFunction("GetPath", &TextureCutLoader::GetPath)
		.addFunction("GetID", &TextureCutLoader::GetID)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<DisplaySystem>("__CPPAPIDisplaySystem")
		.addFunction("AddChild", &DisplaySystem::AddChild)
		.addFunction("AddChildAfter", &DisplaySystem::AddChildAfter)
		.addFunction("AddChildBefore", &DisplaySystem::AddChildBefore)
		.addFunction("AddSpecialChild", &DisplaySystem::AddSpecialChild)
		.addFunction("AddSpecialChildAfter", &DisplaySystem::AddSpecialChildAfter)
		.addFunction("AddSpecialChildBefore", &DisplaySystem::AddSpecialChildBefore)
		.addFunction("RemoveChild", &DisplaySystem::RemoveChild)
		.addFunction("RemoveAllChild", &DisplaySystem::RemoveAllChild)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_DisplaySystem");
}

void DisplaySystem::AddSpecialChild(DisplayObject* object)
{
	m_special_layer_list.AddChild(object);
}

void DisplaySystem::AddSpecialChildAfter(DisplayObject* front_object, DisplayObject* target_object)
{
	m_special_layer_list.AddChildAfter(front_object, target_object);
}

void DisplaySystem::AddSpecialChildBefore(DisplayObject* back_object, DisplayObject* target_object)
{
	m_special_layer_list.AddChildBefore(back_object, target_object);
}

void DisplaySystem::AddChild(DisplayObject* object)
{
	m_layer_list.AddChild(object);
}

void DisplaySystem::AddChildAfter(DisplayObject* front_object, DisplayObject* target_object)
{
	m_layer_list.AddChildAfter(front_object, target_object);
}

void DisplaySystem::AddChildBefore(DisplayObject* back_object, DisplayObject* target_object)
{
	m_layer_list.AddChildBefore(back_object, target_object);
}

void DisplaySystem::RemoveChild(DisplayObject* object)
{
	m_layer_list.RemoveChild(object);
}

void DisplaySystem::RemoveAllChild()
{
	m_layer_list.RemoveAllChild();
	m_special_layer_list.RemoveAllChild();
}

void DisplaySystem::Render()
{
	m_layer_list.Render(Matrix2D(), false);
	m_special_layer_list.Render(Matrix2D(), false);
}

Texture * DisplaySystem::GetQuadTexture()
{
	if (m_quad_texture) return m_quad_texture;

	SDL_Surface* surface = TextureHelper::CreateSurface(32, 32);
	if (surface == 0) return 0;

	for (int i = 0; i < 32; ++i)
		for (int j = 0; j < 32; ++j)
			TextureHelper::SetSurfacePixel(surface, i, j, 0xFFFFFFFF);

	m_quad_texture = new SurfaceTexture(surface);
	return m_quad_texture;
}

carp_font_t* DisplaySystem::GetFont(const char* font_path, unsigned int font_style, unsigned int font_size)
{
	// check font path
	if (!font_path) return NULL;
	std::string font_full_path = font_path;

	// find font
	auto& style_map = m_font_map[font_full_path];
	auto& size_map = style_map[font_style];

	// find font size
	auto size_it = size_map.find(font_size);
	if (size_it != size_map.end())
		return size_it->second;

	// get file name
	std::string font_just_name = FileHelper::GetFileNameByPath(font_full_path);
	std::string font_just_path = font_full_path.substr(0, font_full_path.size() - font_just_name.size());

// special in android
#if (defined __ANDROID__) || (defined __IPHONEOS__)
	// chcke font is already in internal storage
	std::string internal_full_path = FileHelperEx::BaseFilePath();
	internal_full_path.append(font_full_path);
	// if not exist then copy
	if (FileHelper::IsFileExist(internal_full_path) == false)
	{
		// create deep directory
		std::string internal_path = FileHelperEx::BaseFilePath();
		internal_path.append(font_just_path);
		FileHelper::CreateDeepFolder(internal_path);

		FileHelperEx::CpFile(font_full_path.c_str(), internal_full_path.c_str(), true);
	}

	carp_font_t* font = FontHelper::LoadFont(GetFontFile(internal_full_path), font_size, font_style);
#else
	carp_font_t* font = FontHelper::LoadFont(GetFontFile(font_path), font_size, font_style);
#endif
	if (font == nullptr)
	{
		// if create failed then use system font
#ifdef _WIN32
		ALITTLE_ERROR("create font failed: path(" << font_path << ") can't find or font_size(" << font_size << ") not support " << ", and try C:\\Windows\\Fonts\\msyhbd.ttf");
		std::string new_font_path = "C:\\Windows\\Fonts\\";
		new_font_path += font_just_name;
		font = FontHelper::LoadFont(GetFontFile(new_font_path), font_size, font_style);
#elif __ANDROID__
		ALITTLE_ERROR("create font failed: path(" << font_path << ") can't find or font_size(" << font_size << ") not support " << ", and try /system/fonts/Miui-Regular.ttf");
		std::string new_font_path = "/system/fonts/";
		new_font_path += font_just_name;
		font = FontHelper::LoadFont(GetFontFile(new_font_path), font_size);
#endif
	}
	if (font == nullptr)
	{
		ALITTLE_ERROR("Load font failed:" << font_path);
		return nullptr;
	}

	// save font
	size_map[font_size] = font;

	// return font
	return font;
}

LocalFile* DisplaySystem::GetFontFile(const std::string& font_path)
{
	auto it = m_font_file_map.find(font_path);
	if (it != m_font_file_map.end()) return it->second;

	LocalFile* file = new LocalFile();
	file->SetPath(font_path.c_str());
	if (!file->Load())
	{
		delete file;
		return nullptr;
	}
	m_font_file_map[font_path] = file;

	return file;
}

void DisplaySystem::ClearFont()
{
	for (auto font_it = m_font_map.begin(); font_it != m_font_map.end(); ++font_it)
	{
		for (auto style_it = font_it->second.begin(); style_it != font_it->second.end(); ++style_it)
		{
			for (auto size_it = style_it->second.begin(); size_it != style_it->second.end(); ++size_it)
			{
				FontHelper::ReleaseFont(size_it->second);
			}
		}
	}
	m_font_map.clear();
	for (auto& pair : m_font_file_map)
	{
		delete pair.second;
	}
	m_font_file_map.clear();
}

} // ALittle
