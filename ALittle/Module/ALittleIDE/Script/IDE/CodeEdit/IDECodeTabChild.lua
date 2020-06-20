-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

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
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1100004461, "ALittleIDE.IDECodeCharInfo", {
name = "ALittleIDE.IDECodeCharInfo", ns_name = "ALittleIDE", rl_name = "IDECodeCharInfo", hash_code = -1100004461,
name_list = {"char","text","pre_width","width"},
type_list = {"string","ALittle.Text","double","double"},
option_map = {}
})
ALittle.RegStruct(-14518441, "ALittleIDE.IDECodeLineInfo", {
name = "ALittleIDE.IDECodeLineInfo", ns_name = "ALittleIDE", rl_name = "IDECodeLineInfo", hash_code = -14518441,
name_list = {"char_list","char_count","width","container","quad"},
type_list = {"List<ALittleIDE.IDECodeCharInfo>","int","double","ALittle.DisplayLayout","ALittle.Quad"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(776398171, "ALittle.UIEnterKeyEvent", {
name = "ALittle.UIEnterKeyEvent", ns_name = "ALittle", rl_name = "UIEnterKeyEvent", hash_code = 776398171,
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
IDECodeQuad = Lua.Class(ALittle.Quad, "ALittleIDE.IDECodeQuad")

function IDECodeQuad.__getter:is_input()
	return true
end

function IDECodeQuad.__getter:editable()
	return true
end

function IDECodeQuad.__getter:font_size()
	return FONT_SIZE
end

function IDECodeQuad.__getter:cursor_x()
	local tab_child = self._user_data
	return tab_child.cursor.x
end

function IDECodeQuad.__getter:cursor_y()
	local tab_child = self._user_data
	return tab_child.cursor.y
end

function IDECodeQuad.__getter:cursor_b()
	local tab_child = self._user_data
	return tab_child.cursor.y + tab_child.cursor.height
end

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
IDECodeTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDECodeTabChild")

function IDECodeTabChild:Ctor(ctrl_sys, name, save)
	___rawset(self, "_line_list", {})
	___rawset(self, "_line_count", 0)
	___rawset(self, "_tab_screen", g_Control:CreateControl("ide_code_tab_screen", self))
	self._tab_screen.container = ALittle.DisplayLayout(g_Control)
	self._tab_screen:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._tab_screen:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._tab_screen._user_data = self
	self._edit_quad._user_data = self
	self._code_container.disabled = true
	___rawset(self, "_cursor", IDECodeCursor(ctrl_sys, self))
	self._cursor.width = 1
	self._cursor.height = LINE_HEIGHT
	self._cursor_container:AddChild(self._cursor)
	___rawset(self, "_select_cursor", IDECodeSelectCursor(self))
	___rawset(self, "_text_show", ALittle.Text(g_Control))
	self._text_show.font_path = "YaHei-Consolas.ttf"
	self._text_show.font_size = 14
	___rawset(self, "_ascii_width", self._text_show.native_show:CalcTextWidth("A"))
	___rawset(self, "_word_width", self._text_show.native_show:CalcTextWidth("测"))
end

function IDECodeTabChild.__getter:code_container()
	return self._code_container
end

function IDECodeTabChild.__getter:cursor()
	return self._cursor
end

function IDECodeTabChild.__setter:line_count(count)
	self._line_count = count
end

function IDECodeTabChild.__getter:line_count()
	return self._line_count
end

function IDECodeTabChild.__getter:line_list()
	return self._line_list
end

function IDECodeTabChild.__getter:line_height()
	return LINE_HEIGHT
end

function IDECodeTabChild:HandleMoveIn(event)
	ALittle.System_SetEditCursor()
end

function IDECodeTabChild:HandleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function IDECodeTabChild:HandleLButtonDown(event)
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

function IDECodeTabChild:HandleDragBegin(event)
	self._cursor:SetOffsetXY(event.rel_x, event.rel_y)
	self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
end

function IDECodeTabChild:HandleDrag(event)
	self._cursor:SetOffsetXY(event.rel_x, event.rel_y)
	self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
end

function IDECodeTabChild:HandleDragEnd(event)
	if self._select_cursor.line_start == nil or self._select_cursor.line_start == self._select_cursor.line_end and self._select_cursor.char_start == self._select_cursor.char_end then
		self._select_cursor:Hide()
	end
end

function IDECodeTabChild:CalcLineAndChar(x, y)
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

function IDECodeTabChild:DeleteSelectText()
	local result = self._select_cursor:DeleteSelect()
	return result
end

function IDECodeTabChild:HandleTextInput(event)
	ALittle.Log(event.text)
end

function IDECodeTabChild:HandleKeyDown(event)
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
			self._cursor:DeleteLeft()
		else
			local result, it_line, it_char = self._select_cursor:DeleteSelect()
			if result then
				self._cursor:SetLineChar(it_line, it_char)
			end
		end
		event.handled = true
	elseif event.sym == 127 then
		if self._select_cursor.line_start == nil then
			self._cursor:DeleteRight()
		else
			local result, it_line, it_char = self._select_cursor:DeleteSelect()
			if result then
				self._cursor:SetLineChar(it_line, it_char)
			end
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
		self:DispatchEvent(___all_struct[776398171], {})
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

function IDECodeTabChild:OnHide()
	self._cursor:Hide()
end

function IDECodeTabChild:OnShow()
	self._cursor:Show()
end

function IDECodeTabChild:OnClose()
	self._cursor:Hide()
end

function IDECodeTabChild:OnOpen()
	local content = ALittle.File_ReadTextFromStdFile(self._user_info.path)
	if content ~= nil then
		self:SetText(content)
	end
end

function IDECodeTabChild:SetText(content)
	self._code_container:RemoveAllChild()
	self._line_list = {}
	self._line_count = 0
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
				char.text = ALittle.Text(g_Control)
				char.text.red = FONT_RED
				char.text.green = FONT_GREEN
				char.text.blue = FONT_BLUE
				char.text.font_path = FONT_PATH
				char.text.font_size = FONT_SIZE
				char.text.text = char_text
				char.text.x = pre_width
				char.width = self._ascii_width
			end
		else
			char.text = ALittle.Text(g_Control)
			char.text.red = FONT_RED
			char.text.green = FONT_GREEN
			char.text.blue = FONT_BLUE
			char.text.font_path = FONT_PATH
			char.text.font_size = FONT_SIZE
			char.text.text = char_text
			char.text.x = pre_width
			char.width = self._word_width
		end
		char.char = char_text
		char.pre_width = pre_width
		pre_width = pre_width + (char.width)
		if line == nil then
			line = {}
			line.char_count = 0
			line.char_list = {}
			line.quad = ALittle.Quad(g_Control)
			line.container = ALittle.DisplayLayout(g_Control)
			line.quad.red = SELECT_RED
			line.quad.green = SELECT_GREEN
			line.quad.blue = SELECT_BLUE
			line.quad.height = LINE_HEIGHT
			line.quad.visible = false
		end
		line.char_count = line.char_count + (1)
		line.char_list[line.char_count] = char
		if char.text ~= nil then
			line.container:AddChild(char.text)
		end
		if char_text == "\n" then
			self._line_count = self._line_count + (1)
			self._line_list[self._line_count] = line
			line = nil
			pre_width = 0
		end
	end
	if line ~= nil then
		self._line_count = self._line_count + (1)
		self._line_list[self._line_count] = line
		line = nil
	end
	local line_offset = 0
	local max_width = 0.0
	for i, line_info in ___ipairs(self._line_list) do
		local char_offset = 0.0
		local char_start = 1
		for j, char_info in ___ipairs(line_info.char_list) do
			if char_info.char == " " then
				char_offset = char_offset + (self._ascii_width)
			elseif char_info.char == "\t" then
				char_offset = char_offset + (self._ascii_width * 4)
			else
				char_start = j
				break
			end
		end
		line_info.quad.x = 0
		local line_text = ""
		local j = char_start
		while true do
			if not(j <= line_info.char_count) then break end
			local char_info = line_info.char_list[j]
			if char_info.char == "\r" or char_info.char == "\n" then
				break
			end
			if char_info.char == "\t" then
				line_text = line_text .. "    "
			else
				line_text = line_text .. char_info.char
			end
			j = j+(1)
		end
		line_info.quad.y = line_offset
		line_info.container.y = line_offset
		line_info.width = 0
		if line_info.char_count > 0 then
			local last_char = line_info.char_list[line_info.char_count]
			line_info.width = last_char.pre_width + last_char.width
			if max_width < line_info.width then
				max_width = line_info.width
			end
		end
		line_offset = line_offset + (LINE_HEIGHT)
		self._code_container:AddChild(line_info.quad)
		self._code_container:AddChild(line_info.container)
	end
	self._tab_screen.container.width = max_width
	self._tab_screen.container.height = line_offset
	self._tab_screen:RejustScrollBar()
	self._cursor.x = 0
	self._cursor.y = 0
	self._cursor:Show()
end

function IDECodeTabChild.__getter:tab_screen()
	return self._tab_screen
end

function IDECodeTabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	self._save = value
	self:UpdateTitle()
end

function IDECodeTabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function IDECodeTabChild:UpdateTitle()
	local text = self._name
	if self._save == false then
		text = text .. " *"
	end
	g_IDECenter.center.content_edit.main_tab:SetChildText(self._tab_screen, text)
end

function IDECodeTabChild.__getter:title()
	return self._name
end

function IDECodeTabChild:CreateBySelect(info)
	self._user_info = info
end

