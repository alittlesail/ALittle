-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __tostring = ALittle.String_ToString
assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.TextArea = Lua.Class(ALittle.DisplayObject, "ALittle.TextArea")

function ALittle.TextArea:Ctor(ctrl_sys)
	___rawset(self, "_text", "")
	___rawset(self, "_bold", false)
	___rawset(self, "_italic", false)
	___rawset(self, "_underline", false)
	___rawset(self, "_deleteline", false)
	___rawset(self, "_flip", 0)
	___rawset(self, "_halign_type", 0)
	___rawset(self, "_valign_type", 0)
	___rawset(self, "_show", __CPPAPITextArea())
	A_LoadTextureManager:RegisterRedrawControl(self)
end

function ALittle.TextArea:Redraw()
	self._show:NeedDraw()
end

function ALittle.TextArea.__setter:font_path(value)
	self._font_path = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
end

function ALittle.TextArea.__setter:font_size(value)
	self._font_size = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
end

function ALittle.TextArea.__getter:font_path()
	return self._font_path
end

function ALittle.TextArea.__getter:font_size()
	return self._font_size
end

function ALittle.TextArea.__setter:text(value)
	if value == nil then
		return
	end
	value = __tostring(value)
	if self._text == value then
		return
	end
	self._text = value
	self._show:SetText(value)
end

function ALittle.TextArea.__getter:text()
	return self._text
end

function ALittle.TextArea.__setter:bold(value)
	if self._bold == value then
		return
	end
	self._bold = value
	self._show:SetBold(value)
end

function ALittle.TextArea.__getter:bold()
	return self._bold
end

function ALittle.TextArea.__setter:italic(value)
	if self._italic == value then
		return
	end
	self._italic = value
	self._show:SetItalic(value)
end

function ALittle.TextArea.__getter:italic()
	return self._italic
end

function ALittle.TextArea.__setter:underline(value)
	if self._underline == value then
		return
	end
	self._underline = value
	self._show:SetUnderline(value)
end

function ALittle.TextArea.__getter:underline()
	return self._underline
end

function ALittle.TextArea.__setter:deleteline(value)
	if self._deleteline == value then
		return
	end
	self._deleteline = value
	self._show:SetDeleteline(value)
end

function ALittle.TextArea.__getter:deleteline()
	return self._deleteline
end

function ALittle.TextArea.__setter:halign(value)
	if self._halign_type == value then
		return
	end
	self._halign_type = value
	self._show:SetHAlign(value)
end

function ALittle.TextArea.__getter:halign()
	return self._halign_type
end

function ALittle.TextArea.__setter:valign(value)
	if self._valign_type == value then
		return
	end
	self._valign_type = value
	self._show:SetVAlign(value)
end

function ALittle.TextArea.__getter:valign()
	return self._valign_type
end

function ALittle.TextArea.__getter:real_height()
	return self._show:GetRealHeight()
end

function ALittle.TextArea.__getter:flip()
	return self._flip
end

function ALittle.TextArea.__setter:flip(value)
	self._flip = value
	self._show:SetFlip(value)
end

end