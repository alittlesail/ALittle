-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name = "ALittle.UIShowEvent", ns_name = "ALittle", rl_name = "UIShowEvent", hash_code = 1862557463,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUICodeLineNumber = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeLineNumber")

function AUIPlugin.AUICodeLineNumber:Ctor(ctrl_sys, font_path, font_size, ascii_width, word_width, edit)
	___rawset(self, "_showd", false)
	___rawset(self, "_text", "")
	___rawset(self, "_font_path", font_path)
	___rawset(self, "_font_size", font_size)
	___rawset(self, "_ascii_width", ascii_width)
	___rawset(self, "_word_width", word_width)
	___rawset(self, "_edit", edit)
	self:AddEventListener(___all_struct[1862557463], self, self.HandleShow)
end

function AUIPlugin.AUICodeLineNumber:SetLineNumber(line_number)
	self._line_number = line_number
	self.text = ALittle.String_ToString(self._line_number)
end

function AUIPlugin.AUICodeLineNumber:HandleShow(event)
	if self._showd then
		return
	end
	self._showd = true
	self:UpdateShow()
end

function AUIPlugin.AUICodeLineNumber:HandleBreakChanged(event)
	if event.target.selected then
		self._edit:AddBreakPoint(self._line_number)
	else
		self._edit:RemoveBreakPoint(self._line_number)
	end
end

function AUIPlugin.AUICodeLineNumber:UpdateShow()
	local text_list = ALittle.String_SplitUTF8(self._text)
	self:RemoveAllChild()
	local quad = ALittle.Quad(self._ctrl_sys)
	quad.red = AUIPlugin.CODE_BACKGROUND_RED
	quad.green = AUIPlugin.CODE_BACKGROUND_GREEN
	quad.blue = AUIPlugin.CODE_BACKGROUND_BLUE
	quad.width_type = 4
	quad.height_type = 4
	self:AddChild(quad)
	local break_btn = AUIPlugin.g_Control:CreateControl("code_break_check_btn")
	break_btn.y_type = 3
	break_btn.x = 2
	break_btn.y_value = 1
	self:AddChild(break_btn)
	break_btn:AddEventListener(___all_struct[958494922], self, self.HandleBreakChanged)
	break_btn.selected = self._edit:GetBreakPoint(self._line_number)
	local offset = 0.0
	local len = ALittle.List_Len(text_list)
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
				local byte_count = carp.UTF8ByteCount(char, 0, 1)
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

function AUIPlugin.AUICodeLineNumber.__getter:text()
	return self._text
end

function AUIPlugin.AUICodeLineNumber.__setter:text(value)
	if self._text == value then
		return
	end
	self._text = value
end

function AUIPlugin.AUICodeLineNumber.__setter:red(value)
	self._red = value
	for index, child in ___ipairs(self._childs) do
		child.red = value
	end
end

function AUIPlugin.AUICodeLineNumber.__setter:green(value)
	self._green = value
	for index, child in ___ipairs(self._childs) do
		child.green = value
	end
end

function AUIPlugin.AUICodeLineNumber.__setter:blue(value)
	self._blue = value
	for index, child in ___ipairs(self._childs) do
		child.blue = value
	end
end

end