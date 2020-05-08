-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDisplayObject = Lua.Class(nil, "ALittle.IDisplayObject")

function IDisplayObject:SetX(value)
end

function IDisplayObject:SetY(value)
end

function IDisplayObject:SetScaleX(value)
end

function IDisplayObject:SetScaleY(value)
end

function IDisplayObject:SetCenterX(value)
end

function IDisplayObject:SetCenterY(value)
end

function IDisplayObject:SetAngle(value)
end

function IDisplayObject:SetRed(value)
end

function IDisplayObject:SetGreen(value)
end

function IDisplayObject:SetBlue(value)
end

function IDisplayObject:SetAlpha(value)
end

function IDisplayObject:SetClip(value)
end

function IDisplayObject:SetWidth(value)
end

function IDisplayObject:SetHeight(value)
end

function IDisplayObject:SetVisible(value)
end

function IDisplayObject:RemoveChild(value)
end

function IDisplayObject:AddChild(value)
end

function IDisplayObject:AddChildBefore(value1, value2)
end

function IDisplayObject:RemoveAllChild()
end

function IDisplayObject:SetFont(path, size)
end

function IDisplayObject:ClearTexture()
end

function IDisplayObject:SetTexture(texture)
end

function IDisplayObject:SetTextureCoord(t, b, l, r)
end

function IDisplayObject:SetFlip(value)
end

function IDisplayObject:SetRowColCount(row_count, col_count)
end

function IDisplayObject:SetRowColIndex(row, col)
end

function IDisplayObject:NeedDraw()
end

function IDisplayObject:SetText(value)
end

function IDisplayObject:SetBold(value)
end

function IDisplayObject:SetItalic(value)
end

function IDisplayObject:SetUnderline(value)
end

function IDisplayObject:SetDeleteline(value)
end

function IDisplayObject:SetOutline(value)
end

function IDisplayObject:GetRealWidth()
	return 0
end

function IDisplayObject:GetRealHeight()
	return 0
end

function IDisplayObject:GetFontHeight()
	return 0
end

function IDisplayObject:SetHAlign(value)
end

function IDisplayObject:SetVAlign(value)
end

function IDisplayObject:SetCursorAlpha(value)
end

function IDisplayObject:GetLineWidth(value)
	return 0
end

function IDisplayObject:GetLineCount()
	return 0
end

function IDisplayObject:GetScrollOffset()
	return 0
end

function IDisplayObject:IsDefaultText()
	return false
end

function IDisplayObject:SetDefaultText(defaultv, value)
end

function IDisplayObject:SetDefaultTextAlpha(value)
end

function IDisplayObject:GetCursorX()
	return 0
end

function IDisplayObject:GetCursorY()
	return 0
end

function IDisplayObject:GetText()
	return nil
end

function IDisplayObject:SetCursorToEnd()
end

function IDisplayObject:SetCursorToHome()
end

function IDisplayObject:ShowCursor(value)
end

function IDisplayObject:ClickCursor(x, y)
end

function IDisplayObject:ClickWordCursor(x, y)
	return false
end

function IDisplayObject:SelectAll()
end

function IDisplayObject:GetSelectText()
	return nil
end

function IDisplayObject:InsertText(value)
	return false
end

function IDisplayObject:CursorOffsetLR(value)
end

function IDisplayObject:SelectCursorOffsetLR(value)
end

function IDisplayObject:CursorOffsetUD(value)
end

function IDisplayObject:SelectCursorOffsetUD(value)
end

function IDisplayObject:DeleteText(value)
	return false
end

function IDisplayObject:DeleteSelectText()
	return false
end

function IDisplayObject:DragCursorBegin()
end

function IDisplayObject:DragCursor(x, y)
end

function IDisplayObject:SetCursorRed(value)
end

function IDisplayObject:SetCursorGreen(value)
end

function IDisplayObject:SetCursorBlue(value)
end

function IDisplayObject:SetPasswordMode(value)
end

function IDisplayObject:CursorOffset(value)
end

function IDisplayObject:SelectCursorOffset(value)
end

function IDisplayObject:SetTexUV(index, u, v)
end

function IDisplayObject:SetPosXY(index, x, y)
end

function IDisplayObject:SetLeftSize(value)
end

function IDisplayObject:SetRightSize(value)
end

function IDisplayObject:SetTopSize(value)
end

function IDisplayObject:SetBottomSize(value)
end

function IDisplayObject:CutTextByWidth(remain_width, text, total_width)
	return 0
end

function IDisplayObject:ClearCutWidthCache()
end

function IDisplayObject:GetCutWidthListCount()
	return 0
end

function IDisplayObject:GetCutWidthByIndex(index)
	return 0
end

function IDisplayObject:CalcTextWidth(value)
	return 0
end

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IDisplayObjects = Lua.Class(ALittle.IDisplayObject, "ALittle.IDisplayObjects")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IDisplayView = Lua.Class(ALittle.IDisplayObject, "ALittle.IDisplayView")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IImage = Lua.Class(ALittle.IDisplayObject, "ALittle.IImage")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IQuad = Lua.Class(ALittle.IDisplayObject, "ALittle.IQuad")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ISprite = Lua.Class(ALittle.IDisplayObject, "ALittle.ISprite")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IText = Lua.Class(ALittle.IDisplayObject, "ALittle.IText")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ITextArea = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextArea")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ITextEdit = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextEdit")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ITextInput = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextInput")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ITriangle = Lua.Class(ALittle.IDisplayObject, "ALittle.ITriangle")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
IGrid9Image = Lua.Class(ALittle.IDisplayObject, "ALittle.IGrid9Image")

IDisplaySystem = Lua.Class(nil, "ALittle.IDisplaySystem")

function IDisplaySystem:AddSpecialChild(value)
end

function IDisplaySystem:AddChild(value)
end

function IDisplaySystem:AddChildBefore(value1, value2)
end

function IDisplaySystem:RemoveChild(value)
end

function IDisplaySystem:RemoveAllChild()
end

ITexture = Lua.Class(nil, "ALittle.ITexture")

function ITexture:Clear()
end

function ITexture:GetTexture()
	return self
end

function ITexture:GetWidth()
	return 0
end

function ITexture:GetHeight()
	return 0
end

assert(ALittle.ITexture, " extends class:ALittle.ITexture is nil")
IRenderTexture = Lua.Class(ALittle.ITexture, "ALittle.IRenderTexture")

function IRenderTexture:Save(file_path, show, width, height, scale)
	return false
end

function IRenderTexture:Draw(show, width, height, scale)
	return false
end

ITextureLoader = Lua.Class(nil, "ALittle.ITextureLoader")

function ITextureLoader:SetPath(big_path, altas, big_width, big_height, crypt_mode)
end

function ITextureLoader:Start()
end

function ITextureLoader:GetID()
	return 0
end

function ITextureLoader:GetPath()
	return nil
end

ITextureCutLoader = Lua.Class(nil, "ALittle.ITextureCutLoader")

function ITextureCutLoader:SetPath(path, max_width, max_height)
end

function ITextureCutLoader:Start()
end

function ITextureCutLoader:GetID()
	return 0
end

function ITextureCutLoader:GetPath()
	return nil
end

function ITextureCutLoader:GetMaxWidth()
	return 0
end

function ITextureCutLoader:GetMaxHeight()
	return 0
end

