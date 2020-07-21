-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeText = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeText")

function AUICodeText:Ctor(ctrl_sys, font_path, font_size, ascii_width, word_width)
	___rawset(self, "_text", "")
	___rawset(self, "_font_path", font_path)
	___rawset(self, "_font_size", font_size)
	___rawset(self, "_ascii_width", ascii_width)
	___rawset(self, "_word_width", word_width)
end

function AUICodeText.__getter:text()
	return self._text
end

function AUICodeText.__setter:text(value)
	if self._text == value then
		return
	end
	self._text = value
	local text_list = ALittle.String_SplitUTF8(value)
	self:RemoveAllChild()
	local offset = 0.0
	for index, char in ___ipairs(text_list) do
		if char == "\t" then
			offset = offset + (self._ascii_width * 4)
		elseif char == " " then
			offset = offset + (self._ascii_width)
		elseif char ~= "\r" and char ~= "\n" then
			local text = ALittle.Text(self._ctrl_sys)
			text.red = self._red
			text.green = self._green
			text.blue = self._blue
			text.text = char
			text.x = offset
			text.font_path = self._font_path
			text.font_size = self.font_size
			self.y_value = 3
			self:AddChild(text)
		end
	end
end

function AUICodeText:RejustSize()
	local child = self._childs[self._child_count]
	if child == nil then
		self.width = 0
		return
	end
	self.width = child.x + child.width
end

function AUICodeText.__setter:red(value)
	self._red = value
	for index, child in ___ipairs(self._childs) do
		child.red = value
	end
end

function AUICodeText.__setter:green(value)
	self._green = value
	for index, child in ___ipairs(self._childs) do
		child.green = value
	end
end

function AUICodeText.__setter:blue(value)
	self._blue = value
	for index, child in ___ipairs(self._childs) do
		child.blue = value
	end
end

