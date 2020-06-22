-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1421505194, "AUIPlugin.AUICodeLineInfo", {
name = "AUIPlugin.AUICodeLineInfo", ns_name = "AUIPlugin", rl_name = "AUICodeLineInfo", hash_code = 1421505194,
name_list = {"char_list","char_count","container","quad"},
type_list = {"List<AUIPlugin.AUICodeCharInfo>","int","AUIPlugin.AUICodeLineContainer","ALittle.Quad"},
option_map = {}
})
ALittle.RegStruct(1494749965, "AUIPlugin.AUICodeCharInfo", {
name = "AUIPlugin.AUICodeCharInfo", ns_name = "AUIPlugin", rl_name = "AUICodeCharInfo", hash_code = 1494749965,
name_list = {"char","text","red","green","blue","pre_width","width"},
type_list = {"string","ALittle.Text","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
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
ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name = "ALittle.UIShowEvent", ns_name = "ALittle", rl_name = "UIShowEvent", hash_code = 1862557463,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

local LINE_HEIGHT = 18
local FONT_SIZE = 14
local FONT_PATH = "YaHei-Consolas.ttf"
local FONT_RED = 169 / 255
local FONT_GREEN = 183 / 255
local FONT_BLUE = 198 / 255
local SELECT_RED = 33 / 255
local SELECT_GREEN = 66 / 255
local SELECT_BLUE = 131 / 255
assert(ALittle.Quad, " extends class:ALittle.Quad is nil")
AUICodeQuad = Lua.Class(ALittle.Quad, "AUIPlugin.AUICodeQuad")

function AUICodeQuad.__getter:is_input()
	return true
end

function AUICodeQuad.__getter:editable()
	return true
end

function AUICodeQuad.__getter:font_size()
	return FONT_SIZE
end

function AUICodeQuad.__getter:cursor_x()
	local tab_child = self._user_data
	return tab_child.cursor.x
end

function AUICodeQuad.__getter:cursor_y()
	local tab_child = self._user_data
	return tab_child.cursor.y
end

function AUICodeQuad.__getter:cursor_b()
	local tab_child = self._user_data
	return tab_child.cursor.y + tab_child.cursor.height
end

assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
AUICodeLinear = Lua.Class(ALittle.Linear, "AUIPlugin.AUICodeLinear")

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeLineContainer = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeLineContainer")

function AUICodeLineContainer:Ctor(ctrl_sys)
	___rawset(self, "_showd", false)
	self:AddEventListener(___all_struct[348388800], self, self.HandleHide)
	self:AddEventListener(___all_struct[1862557463], self, self.HandleShow)
end

function AUICodeLineContainer:CreateAndAdd(char)
	if not self._showd then
		return
	end
	if char.text == nil and char.width > 0 and char.char ~= " " and char.char ~= "\t" then
		char.text = ALittle.Text(g_Control)
		char.text.red = char.red
		char.text.green = char.green
		char.text.blue = char.blue
		char.text.font_path = FONT_PATH
		char.text.font_size = FONT_SIZE
		char.text.text = char.char
		char.text.x = char.pre_width
		self:AddChild(char.text)
	end
end

function AUICodeLineContainer:HandleHide(event)
end

function AUICodeLineContainer:HandleShow(event)
	if self._showd then
		return
	end
	self._showd = true
	local line = self._user_data
	for index, char in ___ipairs(line.char_list) do
		if char.text == nil and char.width > 0 and char.char ~= " " and char.char ~= "\t" then
			char.text = ALittle.Text(g_Control)
			char.text.red = FONT_RED
			char.text.green = FONT_GREEN
			char.text.blue = FONT_BLUE
			char.text.font_path = FONT_PATH
			char.text.font_size = FONT_SIZE
			char.text.text = char.char
			char.text.x = char.pre_width
			self:AddChild(char.text)
		end
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeEditContainer = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeEditContainer")

function AUICodeEditContainer:ClipRect(x, y, width, height, h_move, v_move)
	self._user_data:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
end

assert(ALittle.ScrollScreen, " extends class:ALittle.ScrollScreen is nil")
AUICodeEdit = Lua.Class(ALittle.ScrollScreen, "AUIPlugin.AUICodeEdit")

function AUICodeEdit:Ctor()
	___rawset(self, "_line_list", {})
	___rawset(self, "_line_count", 0)
end

function AUICodeEdit:TCtor()
	self.container = AUICodeEditContainer(self._ctrl_sys)
	self._edit_quad._user_data = self
	self.container._user_data = self._code_linear
	self._cursor = AUICodeCursor(self._ctrl_sys, self)
	self._cursor.width = 1
	self._cursor.height = LINE_HEIGHT
	self._cursor_container:AddChild(self._cursor)
	self._select_cursor = AUICodeSelectCursor(self)
	self._text_show = ALittle.Text(self._ctrl_sys)
	self._text_show.font_path = "YaHei-Consolas.ttf"
	self._text_show.font_size = 14
	self._ascii_width = self._text_show.native_show:CalcTextWidth("A")
	self._word_width = self._text_show.native_show:CalcTextWidth("测")
end

function AUICodeEdit.__getter:code_linear()
	return self._code_linear
end

function AUICodeEdit.__getter:cursor()
	return self._cursor
end

function AUICodeEdit.__setter:line_count(count)
	self._line_count = count
end

function AUICodeEdit.__getter:line_count()
	return self._line_count
end

function AUICodeEdit.__getter:line_list()
	return self._line_list
end

function AUICodeEdit.__getter:line_height()
	return LINE_HEIGHT
end

function AUICodeEdit.__getter:revoke_list()
	return self._revoke_list
end

function AUICodeEdit:HandleMoveIn(event)
	ALittle.System_SetEditCursor()
end

function AUICodeEdit:HandleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function AUICodeEdit:HandleLButtonDown(event)
	self._select_cursor:Hide()
	self._cursor:SetOffsetXY(event.rel_x, event.rel_y)
	if event.count > 1 then
		local it_start, it_end = self._cursor:CalcSelectWord()
		if it_start == nil then
			return
		end
		self._cursor:SetLineChar(self._cursor.line, it_end)
		self._select_cursor:StartLineChar(self._cursor.line, it_start)
		self._select_cursor:UpdateLineChar(self._cursor.line, it_end)
	end
end

function AUICodeEdit:HandleDragBegin(event)
	self._cursor:SetOffsetXY(event.rel_x, event.rel_y)
	self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
end

function AUICodeEdit:HandleDrag(event)
	self._cursor:SetOffsetXY(event.rel_x, event.rel_y)
	self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
end

function AUICodeEdit:HandleDragEnd(event)
	self._select_cursor:TryHide()
end

function AUICodeEdit:CalcLineAndChar(x, y)
	local it_line = ALittle.Math_Floor(y / LINE_HEIGHT) + 1
	if it_line < 1 then
		it_line = 1
	elseif it_line > self._line_count then
		it_line = self._line_count
	end
	local it_char = 0
	local line = self._line_list[it_line]
	if line == nil then
		return it_line, it_char
	end
	if line.char_count == 0 then
		return it_line, 0
	end
	local pre_width = line.char_list[1].width / 2
	if x < line.char_list[1].width / 2 then
		return it_line, 0
	end
	local index = 1
	while true do
		if not(index < line.char_count) then break end
		local next_width = pre_width + line.char_list[index].width / 2 + line.char_list[index + 1].width / 2
		if x >= pre_width and x < next_width then
			return it_line, index
		end
		pre_width = next_width
		index = index+(1)
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	return it_line, count
end

function AUICodeEdit:BrushColor(line_start, char_start, line_end, char_end, red, green, blue)
	if line_start == line_end then
		local line = self._line_list[line_start]
		local it_char = char_start + 1
		while true do
			if not(it_char <= char_end) then break end
			local char = line.char_list[it_char]
			char.red = red
			char.green = green
			char.blue = blue
			if char.text ~= nil then
				char.text.red = red
				char.text.green = green
				char.text.blue = blue
			end
			it_char = it_char+(1)
		end
		return
	end
	local it_line = line_start
	while true do
		if not(it_line <= line_end) then break end
		local line = self._line_list[it_line]
		if it_line == line_start then
			local it_char = char_start + 1
			while true do
				if not(it_char <= line.char_count) then break end
				local char = line.char_list[it_char]
				char.red = red
				char.green = green
				char.blue = blue
				if char.text ~= nil then
					char.text.red = red
					char.text.green = green
					char.text.blue = blue
				end
				it_char = it_char+(1)
			end
		elseif it_line == line_end then
			local it_char = 1
			while true do
				if not(it_char <= char_end) then break end
				local char = line.char_list[it_char]
				char.red = red
				char.green = green
				char.blue = blue
				if char.text ~= nil then
					char.text.red = red
					char.text.green = green
					char.text.blue = blue
				end
				it_char = it_char+(1)
			end
		else
			local it_char = 1
			while true do
				if not(it_char <= line.char_count) then break end
				local char = line.char_list[it_char]
				char.red = red
				char.green = green
				char.blue = blue
				if char.text ~= nil then
					char.text.red = red
					char.text.green = green
					char.text.blue = blue
				end
				it_char = it_char+(1)
			end
		end
		it_line = it_line+(1)
	end
end

function AUICodeEdit:DeleteSelectText()
	local result, it_line, it_char = self._select_cursor:DeleteSelect(true)
	if result then
		self._cursor:SetLineChar(it_line, it_char)
	end
	return result
end

function AUICodeEdit:HandleTextInput(event)
	if self:InsertText(event.text, true) then
		self:DispatchEvent(___all_struct[958494922], {})
	end
end

function AUICodeEdit:HandleKeyDown(event)
	local is_change = false
	if event.sym == 1073741904 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetLeft()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetLeft()
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetLeft()
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 1073741906 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetUp()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetUp()
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetUp()
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 1073741905 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetDown()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetDown()
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetDown()
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 1073741903 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetRight()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetRight()
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetRight()
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 8 then
		if self._select_cursor.line_start == nil then
			is_change = self._cursor:DeleteLeft(true)
		else
			is_change = self:DeleteSelectText()
		end
		event.handled = true
	elseif event.sym == 127 then
		if self._select_cursor.line_start == nil then
			is_change = self._cursor:DeleteRight(true)
		else
			is_change = self:DeleteSelectText()
		end
		event.handled = true
	elseif event.sym == 1073741898 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetHome()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetHome()
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 1073741901 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetEnd()
			end
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetEnd()
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	elseif event.sym == 13 or event.sym == 1073741912 then
		is_change = self:InsertText("\n", true)
		event.handled = true
	elseif event.sym == 9 then
		is_change = self:InsertText("\t", true)
		event.handled = true
	elseif event.sym == 120 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local select_text = self._select_cursor:GetSelectText()
		if select_text ~= nil then
			ALittle.System_SetClipboardText(select_text)
		end
		is_change = self:DeleteSelectText()
		event.handled = true
	elseif event.sym == 99 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local select_text = self._select_cursor:GetSelectText()
		if select_text ~= nil then
			ALittle.System_SetClipboardText(select_text)
		end
		event.handled = true
	elseif event.sym == 118 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		if ALittle.System_HasClipboardText() then
			is_change = self:InsertText(ALittle.System_GetClipboardText(), true)
		end
		event.handled = true
	elseif event.sym == 97 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		if self._line_count > 0 then
			self._cursor:SetLineChar(self._line_count, self._line_list[self._line_count].char_count)
			self._select_cursor:StartLineChar(1, 0)
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
		end
		event.handled = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
	end
end

function AUICodeEdit:OnHide()
	self._cursor:Hide()
end

function AUICodeEdit:OnShow()
	self._cursor:Show()
end

function AUICodeEdit:OnClose()
	self._cursor:Hide()
	self._file_path = nil
end

function AUICodeEdit:Load(file_path, revoke_list)
	local content = ALittle.File_ReadTextFromStdFile(file_path)
	if content == nil then
		return false
	end
	self:SetText(content)
	self._file_path = file_path
	self._revoke_list = revoke_list
	if self._revoke_list == nil then
		self._revoke_list = ALittle.RevokeList()
	end
	return true
end

function AUICodeEdit:CreateLines(content)
	local line_list = {}
	local line_count = 0
	local max_width = 0.0
	local line = nil
	local len = ALittle.String_Len(content)
	local index = 1
	local pre_width = 0.0
	while index <= len do
		local is_asicc = true
		local byte_count = 1
		local char_text = nil
		do
			byte_count = utf8.bytecount(content, index - 1, 1)
			if byte_count > 1 then
				is_asicc = false
			end
			char_text = string.sub(content, index, index + byte_count - 1)
		end
		index = index + (byte_count)
		local char = {}
		if is_asicc then
			if char_text == "\t" then
				char.width = self._ascii_width * 4
			elseif char_text == "\r" or char_text == "\n" then
				char.width = 0
			else
				char.width = self._ascii_width
			end
		else
			char.width = self._word_width
		end
		char.red = FONT_RED
		char.green = FONT_GREEN
		char.blue = FONT_BLUE
		char.char = char_text
		char.pre_width = pre_width
		pre_width = pre_width + (char.width)
		if line == nil then
			line = {}
			line.char_count = 0
			line.char_list = {}
			line.quad = ALittle.Quad(g_Control)
			line.container = AUICodeLineContainer(g_Control)
			line.container._user_data = line
			line.container.height = LINE_HEIGHT
			line.quad.red = SELECT_RED
			line.quad.green = SELECT_GREEN
			line.quad.blue = SELECT_BLUE
			line.quad.height = LINE_HEIGHT
			line.quad.visible = false
			line.container:AddChild(line.quad)
		end
		line.char_count = line.char_count + (1)
		line.char_list[line.char_count] = char
		if char_text == "\n" then
			line_count = line_count + (1)
			line_list[line_count] = line
			line = nil
			pre_width = 0
		end
	end
	if line ~= nil then
		line_count = line_count + (1)
		line_list[line_count] = line
	end
	local last_line = line_list[line_count]
	if last_line == nil then
		return line_list, line_count, max_width
	end
	local last_char = last_line.char_list[last_line.char_count]
	if last_char == nil then
		return line_list, line_count, max_width
	end
	if last_char.char == "\n" then
		line = {}
		line.char_count = 0
		line.char_list = {}
		line.quad = ALittle.Quad(g_Control)
		line.container = AUICodeLineContainer(g_Control)
		line.container._user_data = line
		line.container.height = LINE_HEIGHT
		line.quad.red = SELECT_RED
		line.quad.green = SELECT_GREEN
		line.quad.blue = SELECT_BLUE
		line.quad.height = LINE_HEIGHT
		line.quad.visible = false
		line.container:AddChild(line.quad)
		line_count = line_count + (1)
		line_list[line_count] = line
	end
	for i, line_info in ___ipairs(line_list) do
		last_char = line_info.char_list[line_info.char_count]
		if last_char ~= nil then
			line_info.container.width = last_char.pre_width + last_char.width
		end
		if line_info.container.width > max_width then
			max_width = line_info.container.width
		end
	end
	return line_list, line_count, max_width
end

function AUICodeEdit:SetText(content)
	self._code_linear:RemoveAllChild()
	local max_width = 0.0
	self._line_list, self._line_count, max_width = self:CreateLines(content)
	for index, line in ___ipairs(self._line_list) do
		self._code_linear:AddChild(line.container)
	end
	self.container.width = max_width
	self.container.height = self._line_count * LINE_HEIGHT
	self:RejustScrollBar()
	self._cursor:SetLineChar(1, 0)
end

function AUICodeEdit:InsertText(content, need_revoke, revoke_bind)
	local insert_revoke
	if need_revoke then
		insert_revoke = ALittle.RevokeBind()
	end
	local is_changed, delete_it_line, delete_it_char = self._select_cursor:DeleteSelect(need_revoke, insert_revoke)
	if is_changed then
		self._cursor:SetLineChar(delete_it_line, delete_it_char)
	end
	local line_list, line_count, max_width = self:CreateLines(content)
	if line_count == 0 then
		return is_changed
	end
	is_changed = true
	local old_it_line = self._cursor.line
	local old_it_char = self._cursor.char
	local split_pre_line = self._line_list[self._cursor.line]
	local split_it_char = self._cursor.char
	if split_pre_line == nil then
		split_pre_line = {}
		split_pre_line.char_count = 0
		split_pre_line.char_list = {}
		split_pre_line.quad = ALittle.Quad(g_Control)
		split_pre_line.container = AUICodeLineContainer(g_Control)
		split_pre_line.container._user_data = split_pre_line
		split_pre_line.container.height = LINE_HEIGHT
		split_pre_line.quad.red = SELECT_RED
		split_pre_line.quad.green = SELECT_GREEN
		split_pre_line.quad.blue = SELECT_BLUE
		split_pre_line.quad.height = LINE_HEIGHT
		split_pre_line.quad.visible = false
		split_pre_line.container:AddChild(split_pre_line.quad)
		self._code_linear:AddChild(split_pre_line.container)
		self._line_count = self._line_count + (1)
		self._line_list[self._line_count] = split_pre_line
	end
	local split_next_line = split_pre_line
	local it_cursor_line = self._cursor.line
	local it_cursor_char = self._cursor.char
	if line_count > 1 then
		self._code_linear:RemoveAllChild()
		local new_line_list = {}
		local new_line_count = 0
		local i = 1
		while true do
			if not(i < self._cursor.line) then break end
			local line = self._line_list[i]
			self._code_linear:AddChild(line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = line
			i = i+(1)
		end
		do
			split_pre_line = self._line_list[self._cursor.line]
			if split_pre_line == nil then
				return is_changed
			end
			split_next_line = {}
			split_next_line.char_count = 0
			split_next_line.char_list = {}
			split_next_line.quad = ALittle.Quad(g_Control)
			split_next_line.container = AUICodeLineContainer(g_Control)
			split_next_line.container._user_data = split_next_line
			split_next_line.container.height = LINE_HEIGHT
			split_next_line.quad.red = SELECT_RED
			split_next_line.quad.green = SELECT_GREEN
			split_next_line.quad.blue = SELECT_BLUE
			split_next_line.quad.height = LINE_HEIGHT
			split_next_line.quad.visible = false
			split_next_line.container:AddChild(split_next_line.quad)
			local i = self._cursor.char + 1
			while true do
				if not(i <= split_pre_line.char_count) then break end
				split_next_line.char_count = split_next_line.char_count + (1)
				split_next_line.char_list[split_next_line.char_count] = split_pre_line.char_list[i]
				if split_pre_line.char_list[i].text ~= nil then
					split_next_line.container:AddChild(split_pre_line.char_list[i].text)
				end
				i = i+(1)
			end
			local split_count = split_pre_line.char_count - self._cursor.char
			ALittle.List_Splice(split_pre_line.char_list, self._cursor.char + 1, split_count)
			split_pre_line.char_count = split_pre_line.char_count - (split_count)
			self._code_linear:AddChild(split_pre_line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = split_pre_line
		end
		local i = 2
		while true do
			if not(i < line_count) then break end
			local line = line_list[i]
			self._code_linear:AddChild(line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = line
			i = i+(1)
		end
		do
			self._code_linear:AddChild(split_next_line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = split_next_line
			it_cursor_line = new_line_count
			it_cursor_char = 0
		end
		local i = self._cursor.line + 1
		while true do
			if not(i <= self._line_count) then break end
			local line = self._line_list[i]
			self._code_linear:AddChild(line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = line
			i = i+(1)
		end
		self._line_list = new_line_list
		self._line_count = new_line_count
	end
	if line_count > 0 then
		local line = line_list[1]
		local char_list = {}
		local char_count = 0
		split_pre_line.container:RemoveAllChild()
		split_pre_line.container:AddChild(split_pre_line.quad)
		local pre_width = 0.0
		local i = 1
		while true do
			if not(i <= split_it_char) then break end
			local char = split_pre_line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
				split_pre_line.container:AddChild(char.text)
			elseif char.width > 0 then
				split_pre_line.container:CreateAndAdd(char)
			end
			char_count = char_count + (1)
			char_list[char_count] = char
			pre_width = pre_width + (char.width)
			i = i+(1)
		end
		local i = 1
		while true do
			if not(i <= line.char_count) then break end
			local char = line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
				split_pre_line.container:AddChild(char.text)
			elseif char.width > 0 then
				split_pre_line.container:CreateAndAdd(char)
			end
			char_count = char_count + (1)
			char_list[char_count] = char
			pre_width = pre_width + (char.width)
			i = i+(1)
		end
		if line_count <= 1 then
			it_cursor_char = char_count
		end
		local i = split_it_char + 1
		while true do
			if not(i <= split_pre_line.char_count) then break end
			local char = split_pre_line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
				split_pre_line.container:AddChild(char.text)
			elseif char.width > 0 then
				split_pre_line.container:CreateAndAdd(char)
			end
			char_count = char_count + (1)
			char_list[char_count] = char
			pre_width = pre_width + (char.width)
			i = i+(1)
		end
		split_pre_line.char_count = char_count
		split_pre_line.char_list = char_list
		split_pre_line.container.width = pre_width
	end
	if line_count > 1 then
		local line = line_list[line_count]
		local char_list = {}
		local char_count = 0
		split_next_line.container:RemoveAllChild()
		split_next_line.container:AddChild(split_next_line.quad)
		local pre_width = 0.0
		local i = 1
		while true do
			if not(i <= line.char_count) then break end
			local char = line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
				split_next_line.container:AddChild(char.text)
			elseif char.width > 0 then
				split_next_line.container:CreateAndAdd(char)
			end
			char_count = char_count + (1)
			char_list[char_count] = char
			pre_width = pre_width + (char.width)
			i = i+(1)
		end
		it_cursor_char = char_count
		local i = 1
		while true do
			if not(i <= split_next_line.char_count) then break end
			local char = split_next_line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
				split_next_line.container:AddChild(char.text)
			elseif char.width > 0 then
				split_next_line.container:CreateAndAdd(char)
			end
			char_count = char_count + (1)
			char_list[char_count] = char
			pre_width = pre_width + (char.width)
			i = i+(1)
		end
		split_next_line.char_count = char_count
		split_next_line.char_list = char_list
		split_next_line.container.width = pre_width
	end
	max_width = 0.0
	for index, line in ___ipairs(self._line_list) do
		if line.container.width > max_width then
			max_width = line.container.width
		end
	end
	self.container.width = max_width
	self.container.height = self._line_count * LINE_HEIGHT
	self:RejustScrollBar()
	self._cursor:SetLineChar(it_cursor_line, it_cursor_char)
	if need_revoke then
		local revoke = AUICodeInsetTextRevoke(self, self._cursor, self._select_cursor, old_it_line, old_it_char, it_cursor_line, it_cursor_char, content)
		insert_revoke:PushRevoke(revoke)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(insert_revoke)
		else
			self._revoke_list:PushRevoke(insert_revoke)
		end
	end
	return is_changed
end

function AUICodeEdit:GetText()
	if self._file_path == nil then
		return ""
	end
	local text_list = {}
	local text_count = 0
	for i, line in ___ipairs(self._line_list) do
		for j, char in ___ipairs(line.char_list) do
			text_count = text_count + (1)
			text_list[text_count] = char.char
		end
	end
	return ALittle.String_Join(text_list, "")
end

function AUICodeEdit:Save()
	if self._file_path == nil then
		return false
	end
	local text_list = {}
	local text_count = 0
	for i, line in ___ipairs(self._line_list) do
		for j, char in ___ipairs(line.char_list) do
			text_count = text_count + (1)
			text_list[text_count] = char.char
		end
	end
	ALittle.File_WriteTextToFile(ALittle.String_Join(text_list, ""), self._file_path)
	return true
end

function AUICodeEdit:EditFocus()
	self._edit_quad:DelayFocus()
end

