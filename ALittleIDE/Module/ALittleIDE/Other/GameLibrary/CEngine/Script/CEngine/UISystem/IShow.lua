-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IDisplayObject = Lua.Class(nil, "ALittle.IDisplayObject")

function ALittle.IDisplayObject:SetX(value)
end

function ALittle.IDisplayObject:SetY(value)
end

function ALittle.IDisplayObject:SetScaleX(value)
end

function ALittle.IDisplayObject:SetScaleY(value)
end

function ALittle.IDisplayObject:SetCenterX(value)
end

function ALittle.IDisplayObject:SetCenterY(value)
end

function ALittle.IDisplayObject:SetAngle(value)
end

function ALittle.IDisplayObject:SetRed(value)
end

function ALittle.IDisplayObject:SetGreen(value)
end

function ALittle.IDisplayObject:SetBlue(value)
end

function ALittle.IDisplayObject:SetAlpha(value)
end

function ALittle.IDisplayObject:SetClip(value)
end

function ALittle.IDisplayObject:SetWidth(value)
end

function ALittle.IDisplayObject:SetHeight(value)
end

function ALittle.IDisplayObject:SetVisible(value)
end

function ALittle.IDisplayObject:RemoveChild(value)
end

function ALittle.IDisplayObject:AddChild(value)
end

function ALittle.IDisplayObject:AddChildBefore(value1, value2)
end

function ALittle.IDisplayObject:RemoveAllChild()
end

function ALittle.IDisplayObject:SetFont(path, size)
end

function ALittle.IDisplayObject:ClearTexture()
end

function ALittle.IDisplayObject:SetTexture(texture)
end

function ALittle.IDisplayObject:SetTextureCoord(t, b, l, r)
end

function ALittle.IDisplayObject:SetFlip(value)
end

function ALittle.IDisplayObject:SetRowColCount(row_count, col_count)
end

function ALittle.IDisplayObject:SetRowColIndex(row, col)
end

function ALittle.IDisplayObject:NeedDraw()
end

function ALittle.IDisplayObject:SetText(value)
end

function ALittle.IDisplayObject:SetBold(value)
end

function ALittle.IDisplayObject:SetItalic(value)
end

function ALittle.IDisplayObject:SetUnderline(value)
end

function ALittle.IDisplayObject:SetDeleteline(value)
end

function ALittle.IDisplayObject:GetRealWidth()
	return 0
end

function ALittle.IDisplayObject:GetRealHeight()
	return 0
end

function ALittle.IDisplayObject:GetFontHeight()
	return 0
end

function ALittle.IDisplayObject:SetHAlign(value)
end

function ALittle.IDisplayObject:SetVAlign(value)
end

function ALittle.IDisplayObject:SetCursorAlpha(value)
end

function ALittle.IDisplayObject:GetLineWidth(value)
	return 0
end

function ALittle.IDisplayObject:GetLineCount()
	return 0
end

function ALittle.IDisplayObject:GetScrollOffset()
	return 0
end

function ALittle.IDisplayObject:IsDefaultText()
	return false
end

function ALittle.IDisplayObject:SetDefaultText(defaultv, value)
end

function ALittle.IDisplayObject:SetDefaultTextAlpha(value)
end

function ALittle.IDisplayObject:GetCursorX()
	return 0
end

function ALittle.IDisplayObject:GetCursorY()
	return 0
end

function ALittle.IDisplayObject:GetCursorHeight()
	return 0
end

function ALittle.IDisplayObject:GetText()
	return nil
end

function ALittle.IDisplayObject:SetCursorToEnd()
end

function ALittle.IDisplayObject:SetCursorToHome()
end

function ALittle.IDisplayObject:ShowCursor(value)
end

function ALittle.IDisplayObject:ClickCursor(x, y)
end

function ALittle.IDisplayObject:ClickWordCursor(x, y)
	return false
end

function ALittle.IDisplayObject:SelectAll()
end

function ALittle.IDisplayObject:GetSelectText()
	return nil
end

function ALittle.IDisplayObject:InsertText(value)
	return false
end

function ALittle.IDisplayObject:CursorOffsetLR(value)
end

function ALittle.IDisplayObject:SelectCursorOffsetLR(value)
end

function ALittle.IDisplayObject:CursorOffsetUD(value)
end

function ALittle.IDisplayObject:SelectCursorOffsetUD(value)
end

function ALittle.IDisplayObject:DeleteText(value)
	return false
end

function ALittle.IDisplayObject:DeleteSelectText()
	return false
end

function ALittle.IDisplayObject:DragCursorBegin()
end

function ALittle.IDisplayObject:DragCursor(x, y)
end

function ALittle.IDisplayObject:SetCursorRed(value)
end

function ALittle.IDisplayObject:SetCursorGreen(value)
end

function ALittle.IDisplayObject:SetCursorBlue(value)
end

function ALittle.IDisplayObject:SetPasswordMode(value)
end

function ALittle.IDisplayObject:CursorOffset(value)
end

function ALittle.IDisplayObject:SelectCursorOffset(value)
end

function ALittle.IDisplayObject:SetTexUV(index, u, v)
end

function ALittle.IDisplayObject:SetPosXY(index, x, y)
end

function ALittle.IDisplayObject:SetLeftSize(value)
end

function ALittle.IDisplayObject:SetRightSize(value)
end

function ALittle.IDisplayObject:SetTopSize(value)
end

function ALittle.IDisplayObject:SetBottomSize(value)
end

function ALittle.IDisplayObject:CutTextByWidth(remain_width, text, total_width)
	return 0
end

function ALittle.IDisplayObject:ClearCutWidthCache()
end

function ALittle.IDisplayObject:GetCutWidthListCount()
	return 0
end

function ALittle.IDisplayObject:GetCutWidthByIndex(index)
	return 0
end

function ALittle.IDisplayObject:CalcTextWidth(value)
	return 0
end

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IDisplayObjects = Lua.Class(ALittle.IDisplayObject, "ALittle.IDisplayObjects")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IDisplayView = Lua.Class(ALittle.IDisplayObject, "ALittle.IDisplayView")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IImage = Lua.Class(ALittle.IDisplayObject, "ALittle.IImage")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IQuad = Lua.Class(ALittle.IDisplayObject, "ALittle.IQuad")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.ISprite = Lua.Class(ALittle.IDisplayObject, "ALittle.ISprite")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IText = Lua.Class(ALittle.IDisplayObject, "ALittle.IText")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.ITextArea = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextArea")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.ITextEdit = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextEdit")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.ITextInput = Lua.Class(ALittle.IDisplayObject, "ALittle.ITextInput")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.ITriangle = Lua.Class(ALittle.IDisplayObject, "ALittle.ITriangle")

assert(ALittle.IDisplayObject, " extends class:ALittle.IDisplayObject is nil")
ALittle.IGrid9Image = Lua.Class(ALittle.IDisplayObject, "ALittle.IGrid9Image")

ALittle.IDisplaySystem = Lua.Class(nil, "ALittle.IDisplaySystem")

function ALittle.IDisplaySystem:AddSpecialChild(value)
end

function ALittle.IDisplaySystem:AddChild(value)
end

function ALittle.IDisplaySystem:AddChildBefore(value1, value2)
end

function ALittle.IDisplaySystem:RemoveChild(value)
end

function ALittle.IDisplaySystem:RemoveAllChild()
end

ALittle.ITexture = Lua.Class(nil, "ALittle.ITexture")

function ALittle.ITexture:Clear()
end

function ALittle.ITexture:GetTexture()
	return self
end

function ALittle.ITexture:GetWidth()
	return 0
end

function ALittle.ITexture:GetHeight()
	return 0
end

assert(ALittle.ITexture, " extends class:ALittle.ITexture is nil")
ALittle.IRenderTexture = Lua.Class(ALittle.ITexture, "ALittle.IRenderTexture")

function ALittle.IRenderTexture:Save(file_path, show, width, height, scale)
	return false
end

function ALittle.IRenderTexture:Draw(show, width, height, scale)
	return false
end

ALittle.ITextureLoader = Lua.Class(nil, "ALittle.ITextureLoader")

function ALittle.ITextureLoader:SetPath(big_path, altas, big_width, big_height, crypt_mode)
end

function ALittle.ITextureLoader:Start()
end

function ALittle.ITextureLoader:GetID()
	return 0
end

function ALittle.ITextureLoader:GetPath()
	return nil
end

ALittle.ITextureCutLoader = Lua.Class(nil, "ALittle.ITextureCutLoader")

function ALittle.ITextureCutLoader:SetPath(path, max_width, max_height)
end

function ALittle.ITextureCutLoader:Start()
end

function ALittle.ITextureCutLoader:GetID()
	return 0
end

function ALittle.ITextureCutLoader:GetPath()
	return nil
end

function ALittle.ITextureCutLoader:GetMaxWidth()
	return 0
end

function ALittle.ITextureCutLoader:GetMaxHeight()
	return 0
end

end