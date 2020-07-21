-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name = "ALittle.UIShowEvent", ns_name = "ALittle", rl_name = "UIShowEvent", hash_code = 1862557463,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeLineNumber = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeLineNumber")

function AUICodeLineNumber:Ctor(ctrl_sys, font_path, font_size, ascii_width, word_width)
	___rawset(self, "_showd", false)
	___rawset(self, "_text", "")
	___rawset(self, "_font_path", font_path)
	___rawset(self, "_font_size", font_size)
	___rawset(self, "_ascii_width", ascii_width)
	___rawset(self, "_word_width", word_width)
	self:AddEventListener(___all_struct[1862557463], self, self.HandleShow)
end

function AUICodeLineNumber:HandleShow(event)
	if self._showd then
		return
	end
	self._showd = true
	self:UpdateShow()
end

function AUICodeLineNumber:UpdateShow()
	local text_list = ALittle.String_SplitUTF8(self._text)
	self:RemoveAllChild()
	local offset = 0.0
	local len = ALittle.List_MaxN(text_list)
	local index = len
	while true do
		if not(index >= 1) then break end
		local char = text_list[index]
		if char == "\t" then
			offset = offset + (self._ascii_width * 4)
		elseif char == " " then
			offset = offset + (self._ascii_width)
		elseif char ~= "\r" and char ~= "\n" then
			local is_asicc = true
			do
				local byte_count = utf8.bytecount(char, 0, 1)
				if byte_count > 1 then
					is_asicc = false
				end
			end
			local text = ALittle.Text(self._ctrl_sys)
			text.red = self._red
			text.green = self._green
			text.blue = self._blue
			text.text = char
			text.x_value = offset
			text.x_type = 4
			text.font_path = self._font_path
			text.font_size = self._font_size
			self.y_value = 3
			self:AddChild(text)
			if is_asicc then
				offset = offset + (self._ascii_width)
			else
				offset = offset + (self._word_width)
			end
		end
		index = index+(-1)
	end
end

function AUICodeLineNumber.__getter:text()
	return self._text
end

function AUICodeLineNumber.__setter:text(value)
	if self._text == value then
		return
	end
	self._text = value
end

function AUICodeLineNumber.__setter:red(value)
	self._red = value
	for index, child in ___ipairs(self._childs) do
		child.red = value
	end
end

function AUICodeLineNumber.__setter:green(value)
	self._green = value
	for index, child in ___ipairs(self._childs) do
		child.green = value
	end
end

function AUICodeLineNumber.__setter:blue(value)
	self._blue = value
	for index, child in ___ipairs(self._childs) do
		child.blue = value
	end
end

