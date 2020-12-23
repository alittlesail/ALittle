-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __tostring = ALittle.String_ToString
local __byte = ALittle.String_Byte
local __type = ALittle.String_Type
assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.Text = Lua.Class(ALittle.DisplayObject, "ALittle.Text")

function ALittle.Text:Ctor(ctrl_sys)
	___rawset(self, "_text", "")
	___rawset(self, "_bold", false)
	___rawset(self, "_italic", false)
	___rawset(self, "_underline", false)
	___rawset(self, "_deleteline", false)
	___rawset(self, "_flip", 0)
	___rawset(self, "_show", __CPPAPIText())
	A_LoadTextureManager:RegisterRedrawControl(self)
end

function ALittle.Text:Redraw()
	self._show:NeedDraw()
end

function ALittle.Text.__setter:font_path(value)
	self._font_path = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
	self:RejuseSize()
end

function ALittle.Text.__setter:font_size(value)
	self._font_size = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
	self:RejuseSize()
end

function ALittle.Text.__getter:font_path()
	return self._font_path
end

function ALittle.Text.__getter:font_size()
	return self._font_size
end

function ALittle.Text.__setter:text(value)
	if value == nil then
		return
	end
	value = __tostring(value)
	if self._text == value then
		return
	end
	self._text = value
	self._show:SetText(value)
	self:RejuseSize()
end

function ALittle.Text.__getter:text()
	return self._text
end

function ALittle.Text.__setter:bold(value)
	if self._bold == value then
		return
	end
	self._bold = value
	self._show:SetBold(value)
	self:RejuseSize()
end

function ALittle.Text.__getter:bold()
	return self._bold
end

function ALittle.Text.__setter:italic(value)
	if self._italic == value then
		return
	end
	self._italic = value
	self._show:SetItalic(value)
	self:RejuseSize()
end

function ALittle.Text.__getter:italic()
	return self._italic
end

function ALittle.Text.__setter:underline(value)
	if self._underline == value then
		return
	end
	self._underline = value
	self._show:SetUnderline(value)
	self:RejuseSize()
end

function ALittle.Text.__getter:underline()
	return self._underline
end

function ALittle.Text.__setter:deleteline(value)
	if self._deleteline == value then
		return
	end
	self._deleteline = value
	self._show:SetDeleteline(value)
	self:RejuseSize()
end

function ALittle.Text.__getter:deleteline()
	return self._deleteline
end

function ALittle.Text:RejuseSize()
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self.width = self._show:GetRealWidth()
	self.height = self._show:GetRealHeight()
	self:UpdateLayout()
end

function ALittle.Text.__setter:rejust_size(value)
	if value ~= true then
		return
	end
	self:RejuseSize()
end

function ALittle.Text:DeserializeSetter(info)
	local base_attr = info.__base_attr
	if base_attr == nil then
		base_attr = {}
		for key, value in ___pairs(info) do
			if __byte(key, 1) ~= 95 and (__type(value) ~= "table" or value.__class == nil) and key ~= "file_path" then
				base_attr[key] = value
			end
		end
		info.__base_attr = base_attr
	end
	for key, value in ___pairs(base_attr) do
		self[key] = value
	end
	if info.font_path ~= nil then
		self["font_path"] = info.font_path
	end
end

function ALittle.Text.__getter:font_height()
	return self._show:GetFontHeight()
end

function ALittle.Text.__getter:flip()
	return self._flip
end

function ALittle.Text.__setter:flip(value)
	self._flip = value
	self._show:SetFlip(value)
end

end