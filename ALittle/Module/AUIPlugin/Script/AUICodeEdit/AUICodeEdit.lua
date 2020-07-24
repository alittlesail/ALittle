-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name = "ALittle.UIKeyDownEvent", ns_name = "ALittle", rl_name = "UIKeyDownEvent", hash_code = -1604617962,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1234078962, "ALittle.UITextInputEvent", {
name = "ALittle.UITextInputEvent", ns_name = "ALittle", rl_name = "UITextInputEvent", hash_code = -1234078962,
name_list = {"target","text","custom"},
type_list = {"ALittle.DisplayObject","string","bool"},
option_map = {}
})
ALittle.RegStruct(1213009422, "ALittle.UIKeyUpEvent", {
name = "ALittle.UIKeyUpEvent", ns_name = "ALittle", rl_name = "UIKeyUpEvent", hash_code = 1213009422,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-644464135, "ALittle.UIFocusInEvent", {
name = "ALittle.UIFocusInEvent", ns_name = "ALittle", rl_name = "UIFocusInEvent", hash_code = -644464135,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name = "ALittle.UIDropFileEvent", ns_name = "ALittle", rl_name = "UIDropFileEvent", hash_code = -338112738,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(292776509, "ALittle.UIFocusOutEvent", {
name = "ALittle.UIFocusOutEvent", ns_name = "ALittle", rl_name = "UIFocusOutEvent", hash_code = 292776509,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeEdit = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeEdit")

function AUICodeEdit.Create()
	return g_Control:CreateControl("ide_code_tab_screen")
end

function AUICodeEdit:Ctor(ctrl_sys)
	___rawset(self, "_editable", true)
	___rawset(self, "_in_query_info", false)
	___rawset(self, "_move_in", false)
	___rawset(self, "_line_list", {})
	___rawset(self, "_line_count", 0)
	___rawset(self, "_in_drag", false)
	___rawset(self, "_force_query_error", false)
	___rawset(self, "_complete_screen", AUICodeCompleteScreen(self))
	___rawset(self, "_signture_help", AUICodeSigntruetureHelp(self))
end

function AUICodeEdit:TCtor()
	self._code_screen:AddEventListener(___all_struct[-644464135], self, self.HandleFocusIn)
	self._code_screen:AddEventListener(___all_struct[292776509], self, self.HandleFocusOut)
	self._code_screen:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._code_screen:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._code_screen:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self._code_screen:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self._code_screen:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self._code_screen:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self._code_screen:AddEventListener(___all_struct[-1604617962], self, self.HandleKeyDown)
	self._code_screen:AddEventListener(___all_struct[1213009422], self, self.HandleKeyUp)
	self._code_screen:AddEventListener(___all_struct[-1234078962], self, self.HandleTextInput)
	self._code_screen:AddEventListener(___all_struct[-1001723540], self, self.HandleMouseMove)
	self._code_screen:AddEventListener(___all_struct[-338112738], self, self.HandleDropFile)
	self:AddEventListener(___all_struct[958494922], self, self.HandleChangedEvent)
	self._find_dialog.visible = false
	self._find_dialog.close_callback = Lua.Bind(self.HandleFindEscClick, self, nil)
	self._error_btn.visible = false
	self._code_screen.container = AUICodeEditContainer(self._ctrl_sys)
	self._edit_quad._user_data = self
	self._goto_quad.visible = false
	self._code_screen.container._user_data = self._code_linear
	self._line_number = ALittle.Linear(self._ctrl_sys)
	self._line_number.type = 2
	self._line_number.width = CODE_LINE_NUMBER_WIDTH
	self._code_screen.static_object_v = self._line_number
	self._cursor = AUICodeCursor(self._ctrl_sys, self)
	self._cursor.width = 1
	self._cursor.height = CODE_LINE_HEIGHT
	self._cursor_container:AddChild(self._cursor)
	self._cursor.disabled = true
	self._cursor:Hide()
	self._select_cursor = AUICodeSelectCursor(self)
	self._text_show = ALittle.Text(self._ctrl_sys)
	self._text_show.font_path = "YaHei-Consolas.ttf"
	self._text_show.font_size = 14
	self._ascii_width = self._text_show.native_show:CalcTextWidth("A")
	self._word_width = self._text_show.native_show:CalcTextWidth("测")
end

function AUICodeEdit.__getter:is_input()
	return true
end

function AUICodeEdit.__getter:editable()
	return self._editable
end

function AUICodeEdit.__setter:editable(value)
	self._editable = value
end

function AUICodeEdit.__getter:cursor_x()
	return self._edit_quad.cursor_x
end

function AUICodeEdit.__getter:cursor_y()
	return self._edit_quad.cursor_y
end

function AUICodeEdit.__getter:cursor_b()
	return self._edit_quad.cursor_b
end

function AUICodeEdit.__getter:code_screen()
	return self._code_screen
end

function AUICodeEdit.__getter:code_linear()
	return self._code_linear
end

function AUICodeEdit.__getter:cursor()
	return self._cursor
end

function AUICodeEdit.__getter:select_cursor()
	return self._select_cursor
end

function AUICodeEdit.__getter:language()
	return self._language
end

function AUICodeEdit.__getter:ascii_width()
	return self._ascii_width
end

function AUICodeEdit.__getter:word_width()
	return self._word_width
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

function AUICodeEdit.__getter:revoke_list()
	return self._revoke_list
end

function AUICodeEdit.__getter:help_container()
	return self._help_container
end

function AUICodeEdit:DispatchJumEvent()
	local event = {}
	event.file_path = self._file_path
	event.it_line = self._cursor.line
	event.it_char = self._cursor.char
	self:DispatchEvent(___all_struct[-1898137181], event)
end

function AUICodeEdit:FocusLineCharToCenter(it_line, it_char)
	local line = self._line_list[it_line]
	if line == nil then
		return
	end
	local char = line.char_list[it_char]
	if char == nil then
		char = line.char_list[1]
	end
	local y = (it_line - 1) * CODE_LINE_HEIGHT
	local x = char.pre_width
	local real_width = self._code_screen.container.width - self._code_screen.view_width
	if real_width > 0 then
		local view_x = self._code_screen.view_width / 2
		local center_x = x
		self._code_screen.bottom_scrollbar.offset_rate = (center_x - view_x) / real_width
	end
	local real_height = self._code_screen.container.height - self._code_screen.view_height
	if real_height > 0 then
		local view_y = self._code_screen.view_height / 2
		local center_y = y
		self._code_screen.right_scrollbar.offset_rate = (center_y - view_y) / real_height
	end
	self._code_screen:RejustScrollBar()
end

function AUICodeEdit:FocusLineCharToUp(it_line, it_char)
	local line = self._line_list[it_line]
	if line == nil then
		return
	end
	local real_height = self._code_screen.container.height - self._code_screen.view_height
	if real_height > 0 then
		self._code_screen.right_scrollbar.offset_rate = (it_line - 1) * CODE_LINE_HEIGHT / real_height
		self._code_screen:RejustScrollBar()
	end
end

function AUICodeEdit:FocusLineCharToDown(it_line, it_char)
	local line = self._line_list[it_line]
	if line == nil then
		return
	end
	local real_height = self._code_screen.container.height - self._code_screen.view_height
	if real_height > 0 then
		self._code_screen.right_scrollbar.offset_rate = (it_line * CODE_LINE_HEIGHT - self._code_screen.view_height) / real_height
		self._code_screen:RejustScrollBar()
	end
end

function AUICodeEdit:HandleFocusIn(event)
	ALittle.System_OpenIME()
	self._cursor:Show()
end

function AUICodeEdit:HandleFocusOut(event)
	ALittle.System_CloseIME()
	self._cursor:Hide()
end

function AUICodeEdit:HandleMoveIn(event)
	self._move_in = true
	ALittle.System_SetEditCursor()
end

function AUICodeEdit:HandleMoveOut(event)
	self:StopQueryInfo()
	self._move_in = false
	ALittle.System_SetNormalCursor()
end

function AUICodeEdit:HandleLButtonDown(event)
	local rel_x = event.rel_x
	if event.target == self._code_screen then
		rel_x = rel_x - (self._code_linear.x)
	end
	self._select_cursor:Hide()
	self._cursor:SetOffsetXY(rel_x, event.rel_y)
	if event.count > 1 then
		local it_start, it_end = self._cursor:CalcSelectWord()
		if it_start == nil then
			return
		end
		self._cursor:SetLineChar(self._cursor.line, it_end)
		self._select_cursor:StartLineChar(self._cursor.line, it_start)
		self._select_cursor:UpdateLineChar(self._cursor.line, it_end)
	end
	if A_UISystem.sym_map[1073742048] and self._query_info ~= nil and self._language ~= nil then
		local it_line, it_char = self:CalcLineAndChar(rel_x, event.rel_y)
		self:DoQueryGoto(it_line, it_char)
		self:StopQueryInfo()
	end
	self._cursor:RejustShowCursor()
	self:DispatchJumEvent()
end

function AUICodeEdit:DoQueryGoto(it_line, it_char)
	local info = self._language:QueryGoto(it_line, it_char)
	if info ~= nil then
		if info.file_path == self._file_path then
			self._cursor:SetLineChar(info.line_start, info.char_start - 1)
			self._select_cursor:StartLineChar(info.line_start, info.char_start - 1)
			self._select_cursor:UpdateLineChar(info.line_end, info.char_end)
			self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
			self:DispatchJumEvent()
		else
			local goto_event = {}
			goto_event.file_path = info.file_path
			goto_event.line_start = info.line_start
			goto_event.char_start = info.char_start
			goto_event.line_end = info.line_end
			goto_event.char_end = info.char_end
			self:DispatchEvent(___all_struct[631224630], goto_event)
		end
	end
end
AUICodeEdit.DoQueryGoto = Lua.CoWrap(AUICodeEdit.DoQueryGoto)

function AUICodeEdit:HandleDragBegin(event)
	if self._error_quad_move_in ~= nil then
		g_AUITool:HideTip()
		self._error_quad_move_in = nil
	end
	local rel_x = event.rel_x
	if event.target == self._code_screen then
		rel_x = rel_x - (self._code_linear.x)
	end
	self._in_drag = true
	self._cursor:SetOffsetXY(rel_x, event.rel_y)
	self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
end

function AUICodeEdit:HandleDrag(event)
	local rel_x = event.rel_x
	if event.target == self._code_screen then
		rel_x = rel_x - (self._code_linear.x)
	end
	self._cursor:SetOffsetXY(rel_x, event.rel_y)
	self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
end

function AUICodeEdit:HandleDragEnd(event)
	self._select_cursor:TryHide()
	self._in_drag = false
end

function AUICodeEdit:HandleMouseMove(event)
	local rel_x = event.rel_x
	if event.target == self._code_screen then
		rel_x = rel_x - (self._code_linear.x)
	end
	if not self._in_drag then
		local it_line = ALittle.Math_Floor(event.rel_y / CODE_LINE_HEIGHT) + 1
		local line = self._line_list[it_line]
		if line ~= nil then
			local rel_y = event.rel_y - (it_line - 1) * CODE_LINE_HEIGHT
			local item = line.container._error:PickUp(rel_x, rel_y)
			if item ~= self._error_quad_move_in then
				if self._error_quad_move_in ~= nil then
					g_AUITool:HideTip()
				end
				self._error_quad_move_in = item
				if item ~= nil then
					local info = item._user_data
					local x, y = item:LocalToGlobal()
					local center_x = x + item.width / 2
					local center_y = y
					g_AUITool:ShowTip(info.error)
					local tip_width, tip_height = g_AUITool:GetTipSize()
					g_AUITool:MoveTip(center_x - tip_width / 2, center_y - tip_height)
				end
			end
		end
	end
	if not A_UISystem.sym_map[1073742048] then
		return
	end
	self:UpdateQueryInfo(rel_x, event.rel_y)
end

function AUICodeEdit:HandleDropFile(event)
	local goto_event = {}
	goto_event.file_path = event.path
	self:DispatchEvent(___all_struct[631224630], goto_event)
end

function AUICodeEdit:UpdateLineNumber()
	local child_count = self._line_count + CODE_PAD_LINES
	local delta = self._line_number.child_count - child_count
	if delta >= 0 and delta <= 10 then
		return
	end
	if delta > 0 then
		self._line_number:SpliceChild(child_count)
		return
	end
	local index = self._line_number.child_count + 1
	while true do
		if not(index <= child_count) then break end
		local text = AUICodeLineNumber(self._ctrl_sys, CODE_FONT_PATH, CODE_FONT_SIZE, self._ascii_width, self._word_width)
		text.height = CODE_LINE_HEIGHT
		text.red = CODE_LINE_NUMBER_RED
		text.green = CODE_LINE_NUMBER_GREEN
		text.blue = CODE_LINE_NUMBER_BLUE
		text.text = ALittle.String_ToString(index)
		self._line_number:AddChild(text)
		index = index+(1)
	end
end

function AUICodeEdit:UpdateQueryInfo(x, y)
	if self._language == nil then
		ALittle.System_SetEditCursor()
		return
	end
	if self._in_query_info then
		if self._query_info == nil then
			ALittle.System_SetEditCursor()
		else
			ALittle.System_SetHandCursor()
		end
		return
	end
	local it_line, it_char = self:CalcLineAndChar(x, y)
	self._in_query_info = true
	local info = self._language:QueryInfo(it_line, it_char)
	if self._in_query_info == false or info == nil then
		if self._query_info ~= nil then
			g_AUITool:HideTip()
			self._goto_quad.visible = false
			local line_container = self._code_linear:GetChildByIndex(self._query_info.line_start)
			if line_container ~= nil then
				line_container:RestoreColor()
			end
			self._query_info = nil
		end
		ALittle.System_SetEditCursor()
		return
	end
	self._in_query_info = false
	if self._query_info ~= nil and self._query_info.line_start == info.line_start and self._query_info.char_start == info.char_start and self._query_info.line_end == info.line_end and self._query_info.char_end == info.char_end and self._query_info_version == self._language.version then
		ALittle.System_SetHandCursor()
		return
	end
	if self._query_info ~= nil then
		g_AUITool:HideTip()
		self._goto_quad.visible = false
		local line_container = self._code_linear:GetChildByIndex(self._query_info.line_start)
		if line_container ~= nil then
			line_container:RestoreColor()
		end
		self._query_info = nil
	end
	local line = self._line_list[info.line_start]
	local quad_x, quad_y = self._edit_quad:LocalToGlobal()
	local char_end = info.char_end
	if line ~= nil and info.line_start ~= info.line_end then
		info.char_end = line.char_count
	end
	local rect_x, rect_y, rect_width = self:CalcRect(info.line_start, info.char_start, char_end)
	if A_UISystem.mouse_x < quad_x + rect_x or A_UISystem.mouse_x >= quad_x + rect_x + rect_width or A_UISystem.mouse_y < quad_y + rect_y or A_UISystem.mouse_y >= quad_y + rect_y + CODE_LINE_HEIGHT then
		ALittle.System_SetEditCursor()
		return
	end
	self._query_info_version = self._language.version
	self._query_info = info
	local line_container = self._code_linear:GetChildByIndex(info.line_start)
	if line ~= nil and line_container ~= nil then
		if info.line_start == info.line_end then
			line_container:SetColor(info.char_start, info.char_end, CODE_FOCUS_RED, CODE_FOCUS_GREEN, CODE_FOCUS_BLUE)
		else
			line_container:SetColor(info.char_start, line.char_count, CODE_FOCUS_RED, CODE_FOCUS_GREEN, CODE_FOCUS_BLUE)
		end
	end
	g_AUITool:ShowTip(info.info)
	local center_x = rect_x + rect_width / 2 + quad_x
	local center_y = rect_y + quad_y
	local tip_width, tip_height = g_AUITool:GetTipSize()
	g_AUITool:MoveTip(center_x - tip_width / 2, center_y - tip_height)
	self._goto_quad.x = rect_x
	self._goto_quad.y = rect_y
	self._goto_quad.width = rect_width
	self._goto_quad.height = CODE_LINE_HEIGHT
	self._goto_quad.visible = true
	ALittle.System_SetHandCursor()
end
AUICodeEdit.UpdateQueryInfo = Lua.CoWrap(AUICodeEdit.UpdateQueryInfo)

function AUICodeEdit:StopQueryInfo()
	if self._language == nil then
		return
	end
	self._in_query_info = false
	self._query_info_version = nil
	if self._query_info ~= nil then
		local line_container = self._code_linear:GetChildByIndex(self._query_info.line_start)
		if line_container ~= nil then
			line_container:RestoreColor()
		end
	end
	g_AUITool:HideTip()
	self._query_info = nil
	self._goto_quad.visible = false
end

function AUICodeEdit:UpdateErrorInfo()
	g_AUITool:HideTip()
	self._error_quad_move_in = nil
	if self._error_map ~= nil then
		for info, _ in ___pairs(self._error_map) do
			info.item:RemoveFromParent()
		end
	end
	self._error_map = nil
	local list = self._language:QueryError(self._force_query_error)
	if list == nil then
		self._error_btn.visible = false
		return
	end
	self._error_map = {}
	local error_count = 0
	for index, info in ___ipairs(list) do
		local item_info = {}
		local item = g_Control:CreateControl("ide_code_error_item", item_info)
		local line = self._line_list[info.line_start]
		local char_end = info.char_end
		if info.line_start ~= info.line_end then
			info.char_end = line.char_count
		end
		item_info.info = info
		local x, y, width = self:CalcRect(info.line_start, info.char_start, char_end)
		if width <= 0 then
			width = self._ascii_width
		end
		item.x = x
		item.width = width
		item.height = CODE_LINE_HEIGHT
		item_info._focus_quad._user_data = info
		item_info.item = item
		item_info.info = info
		line.container._error:AddChild(item)
		error_count = error_count + (1)
		self._error_map[item_info] = true
	end
	self._error_btn.visible = error_count > 0
end
AUICodeEdit.UpdateErrorInfo = Lua.CoWrap(AUICodeEdit.UpdateErrorInfo)

function AUICodeEdit:HandleErrorNextClick(event)
	if self:ErrorNextImpl(self._cursor.line, true) then
		return
	end
	self:ErrorNextImpl(1, false)
end

function AUICodeEdit:ErrorNextImpl(start_line, check_cursor)
	local line_index = start_line
	while line_index <= self._line_count do
		local line = self._line_list[line_index]
		for index, child in ___ipairs(line.container._error.childs) do
			local info = child._user_data
			if not check_cursor or line_index ~= self._cursor.line or info.char_start > self._cursor.char + 1 then
				self:EditFocus(info.line_start, info.char_start, nil, nil, false)
				return true
			end
		end
		line_index = line_index + (1)
	end
	return false
end

function AUICodeEdit:SetFindInput(text)
	self._find_input.text = text
	self:HandleFindInputChanged(nil)
end

function AUICodeEdit:HandleFindInputChanged(event)
	self:ClearFindInfo()
	local content = self._find_input.text
	self._find_text = ALittle.String_SplitUTF8(content)
	local find_len = ALittle.List_MaxN(self._find_text)
	if find_len == 0 then
		return
	end
	self._find_map = {}
	local first_info = nil
	for index, line in ___ipairs(self._line_list) do
		if line.char_count >= find_len then
			local char_index = 1
			while char_index <= line.char_count do
				local find = true
				for i, char in ___ipairs(self._find_text) do
					if char ~= line.char_list[char_index + i - 1].char then
						find = false
						break
					end
				end
				if find then
					local item = ALittle.Quad(g_Control)
					item.red = CODE_FIND_RED
					item.green = CODE_FIND_GREEN
					item.blue = CODE_FIND_BLUE
					item.x = line.char_list[char_index].pre_width
					item.width = line.char_list[char_index + find_len].pre_width - line.char_list[char_index].pre_width
					item.height = CODE_LINE_HEIGHT
					line.container._find:AddChild(item)
					local info = {}
					info._focus_quad = item
					info.it_line = index
					info.it_char_start = char_index
					info.it_char_end = char_index + find_len - 1
					item._user_data = info
					self._find_map[info] = true
					if first_info == nil then
						first_info = info
					end
					char_index = char_index + (find_len)
				else
					char_index = char_index + (1)
				end
			end
		end
	end
	if first_info ~= nil then
		self:EditFocus(first_info.it_line, first_info.it_char_start, first_info.it_line, first_info.it_char_end, false)
	end
end

function AUICodeEdit:HandleFindNextClick(event)
	self:FindNext(nil)
end

function AUICodeEdit:FindNext(content)
	if content ~= nil and self._find_input.text ~= content then
		self:SetFindInput(content)
	end
	if self:FindNextImpl(self._cursor.line, true) then
		return
	end
	self:FindNextImpl(1, false)
end

function AUICodeEdit:FindNextImpl(start_line, check_cursor)
	local line_index = start_line
	while line_index <= self._line_count do
		local line = self._line_list[line_index]
		for index, child in ___ipairs(line.container._find.childs) do
			local info = child._user_data
			if not check_cursor or line_index ~= self._cursor.line or info.it_char_start > self._cursor.char + 1 then
				self:EditFocus(info.it_line, info.it_char_start, info.it_line, info.it_char_end, false)
				return true
			end
		end
		line_index = line_index + (1)
	end
	return false
end

function AUICodeEdit:UpdateLineFind(it_line)
	if self._find_map == nil then
		return
	end
	local line = self._line_list[it_line]
	if line == nil then
		return
	end
	for index, child in ___ipairs(line.container._find.childs) do
		self._find_map[child._user_data] = nil
	end
	line.container._find:RemoveAllChild()
	local find_len = ALittle.List_MaxN(self._find_text)
	if find_len == 0 then
		return
	end
	if line.char_count >= find_len then
		local char_index = 1
		while char_index <= line.char_count do
			local find = true
			for i, char in ___ipairs(self._find_text) do
				if char ~= line.char_list[char_index + i - 1].char then
					find = false
					break
				end
			end
			if find then
				local item = ALittle.Quad(g_Control)
				item.red = CODE_FIND_RED
				item.green = CODE_FIND_GREEN
				item.blue = CODE_FIND_BLUE
				item.x = line.char_list[char_index].pre_width
				item.width = line.char_list[char_index + find_len].pre_width - line.char_list[char_index].pre_width
				item.height = CODE_LINE_HEIGHT
				line.container._find:AddChild(item)
				local info = {}
				info._focus_quad = item
				info.it_line = it_line
				info.it_char_start = char_index
				info.it_char_end = char_index + find_len - 1
				item._user_data = info
				self._find_map[info] = true
				char_index = char_index + (find_len)
			else
				char_index = char_index + (1)
			end
		end
	end
end

function AUICodeEdit:HandleFindEscClick(event)
	self._find_dialog.visible = false
	self:ClearFindInfo()
end

function AUICodeEdit:ClearFindInfo()
	if self._find_map ~= nil then
		for info, _ in ___pairs(self._find_map) do
			info._focus_quad:RemoveFromParent()
		end
	end
	self._find_map = nil
end

function AUICodeEdit:HandleChangedEvent(event)
	if self._language == nil then
		return
	end
	local map = self._code_linear:GetShowMap()
	for object, _ in ___pairs(map) do
		object:RestoreColor()
	end
	self:StartErrorLoop(false)
end

function AUICodeEdit:StartErrorLoop(force)
	if self._language == nil then
		return
	end
	self._force_query_error = force
	if self._error_loop == nil then
		self._error_loop = ALittle.LoopTimer(Lua.Bind(self.UpdateErrorInfo, self), 1000)
	end
	self._error_loop:Stop()
	self._error_loop:Reset()
	self._error_loop:Start()
end

function AUICodeEdit:CalcLineAndChar(x, y)
	local it_line = ALittle.Math_Floor(y / CODE_LINE_HEIGHT) + 1
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

function AUICodeEdit:CalcRect(it_line, char_start, char_end)
	local line = self._line_list[it_line]
	if line == nil then
		return 0, 0, 0
	end
	local y = (it_line - 1) * CODE_LINE_HEIGHT
	local x = 0.0
	if line.char_list[char_start] ~= nil then
		x = line.char_list[char_start].pre_width
	end
	local width = 0.0
	local char_e = line.char_list[char_end]
	if char_e ~= nil then
		width = char_e.pre_width + char_e.width - x
	end
	return x, y, width
end

function AUICodeEdit:CalcPosition(it_line, it_char, pre)
	local line = self._line_list[it_line]
	if line == nil then
		return 0, 0
	end
	local y = (it_line - 1) * CODE_LINE_HEIGHT
	local x = 0.0
	if it_char > 0 then
		x = line.char_list[it_char].pre_width
		if not pre then
			x = x + (line.char_list[it_char].width)
		end
	end
	return x, y
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
	local text = self._cursor.virtual_indent .. event.text
	if self:InsertText(text, true) then
		if self._language ~= nil then
			local auto_pair = self._language:QueryAutoPair(self._cursor.line, self._cursor.char, event.text)
			if auto_pair ~= nil then
				if self._cursor:GetNextCharInLine() ~= auto_pair then
					local old_line = self._cursor.line
					local old_char = self._cursor.char
					self:InsertText(auto_pair, true)
					self._cursor:SetLineChar(old_line, old_char)
				end
			elseif self._language:QueryAutoFormat(event.text) then
				self:MultiLineFormat(self._cursor.line, self._cursor.line)
			end
		end
		self:DispatchEvent(___all_struct[958494922], {})
		self._complete_screen:ShowComplete()
	end
end

function AUICodeEdit:HandleKeyDown(event)
	local is_change = false
	if event.sym == 1073741904 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetLeft(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			end
			self._cursor:RejustShowCursor()
			self._complete_screen:TryHide(self)
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetLeft(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetLeft(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 1073741906 then
		if self._complete_screen:IsShow() then
			self._complete_screen:SelectUp()
		else
			if ALittle.BitAnd(event.mod, 0x0003) == 0 then
				if self._select_cursor.line_start ~= nil then
					self._select_cursor:Hide()
				else
					self._cursor:OffsetUp()
				end
				self._cursor:RejustShowCursor()
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
			local offset_y = self._cursor.y + self._code_screen.container_y
			if offset_y < 0 then
				self:FocusLineCharToUp(self._cursor.line, self._cursor.char)
			end
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 1073741905 then
		if self._complete_screen:IsShow() then
			self._complete_screen:SelectDown()
		else
			if ALittle.BitAnd(event.mod, 0x0003) == 0 then
				if self._select_cursor.line_start ~= nil then
					self._select_cursor:Hide()
				else
					self._cursor:OffsetDown()
				end
				self._cursor:RejustShowCursor()
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
			local offset_y = self._cursor.y + self._cursor.height + self._code_screen.container_y
			if offset_y > self._code_screen.view_height then
				self:FocusLineCharToDown(self._cursor.line, self._cursor.char)
			end
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 1073741903 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetRight(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			end
			self._cursor:RejustShowCursor()
			self._complete_screen:TryHide(self)
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetRight(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			if self._cursor.line == self._select_cursor.line_start and self._cursor.char == self._select_cursor.char_start then
				self._cursor:OffsetRight(ALittle.BitAnd(event.mod, 0x00c0) ~= 0)
			end
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 8 then
		if self._editable then
			if self._select_cursor.line_start == nil then
				is_change = self._cursor:DeleteLeft(true)
				self._cursor:RejustShowCursor()
				self._complete_screen:TryHide(self)
				if self._complete_screen:IsShow() then
					self._complete_screen:ShowComplete()
				end
			else
				is_change = self:DeleteSelectText()
				self._complete_screen:Hide()
			end
			event.handled = true
		end
	elseif event.sym == 127 then
		if self._editable then
			if self._select_cursor.line_start == nil then
				is_change = self._cursor:DeleteRight(true)
			else
				is_change = self:DeleteSelectText()
			end
			event.handled = true
		end
	elseif event.sym == 1073741898 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetHome()
			end
			self._complete_screen:TryHide(self)
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetHome()
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 1073741901 then
		if ALittle.BitAnd(event.mod, 0x0003) == 0 then
			if self._select_cursor.line_start ~= nil then
				self._select_cursor:Hide()
			else
				self._cursor:OffsetEnd()
			end
			self._complete_screen:TryHide(self)
		else
			if self._select_cursor.line_start == nil then
				self._select_cursor:StartLineChar(self._cursor.line, self._cursor.char)
			end
			self._cursor:OffsetEnd()
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 13 or event.sym == 1073741912 then
		if self._editable then
			if self._complete_screen:IsShow() then
				is_change = self._complete_screen:DoSelect()
			else
				local old_line = self._cursor.line
				local old_char = self._cursor.char
				local revoke_bind = ALittle.RevokeBind()
				is_change = self:InsertText("\n", true, revoke_bind)
				if self._cursor:CurLineHasChar() then
					self._cursor:UpdateVirtualIndent()
					local text = self._cursor.virtual_indent
					if text ~= "" then
						is_change = self:InsertText(text, true, revoke_bind)
					end
					if self._cursor:GetCurCharInLine() == "}" then
						self._cursor:SetLineChar(old_line, old_char)
						is_change = self:InsertText("\n", true, revoke_bind)
						self._cursor:RejustShowCursor()
					end
				else
					self._cursor:RejustShowCursor()
				end
				revoke_bind.complete = Lua.Bind(self.DispatchChangedEvent, self)
				self._revoke_list:PushRevoke(revoke_bind)
			end
			event.handled = true
		end
	elseif event.sym == 9 then
		if self._editable then
			if self._select_cursor.line_start ~= self._select_cursor.line_end then
				if ALittle.BitAnd(event.mod, 0x0003) ~= 0 then
					is_change = self:MultiTabDelete(true)
				else
					is_change = self:MultiTabInsert(true)
				end
			else
				local text = self._cursor.virtual_indent .. "\t"
				is_change = self:InsertText(text, true)
			end
			self._complete_screen:Hide()
			event.handled = true
		end
	elseif event.sym == 120 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		if self._editable then
			local select_text = self._select_cursor:GetSelectText()
			if select_text ~= nil then
				ALittle.System_SetClipboardText(select_text)
			end
			is_change = self:DeleteSelectText()
			self._complete_screen:Hide()
			event.handled = true
		end
	elseif event.sym == 99 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		local select_text = self._select_cursor:GetSelectText()
		if select_text ~= nil then
			ALittle.System_SetClipboardText(select_text)
		end
		event.handled = true
	elseif event.sym == 118 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		if self._editable then
			if ALittle.System_HasClipboardText() then
				local old_line = self._cursor.line
				is_change = self:InsertText(ALittle.System_GetClipboardText(), true)
				local new_line = self._cursor.line
				self._complete_screen:Hide()
				self:MultiLineFormat(old_line, new_line)
			end
			event.handled = true
		end
	elseif event.sym == 97 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		if self._line_count > 0 then
			self._cursor:SetLineChar(self._line_count, self._line_list[self._line_count].char_count)
			self._select_cursor:StartLineChar(1, 0)
			self._select_cursor:UpdateLineChar(self._cursor.line, self._cursor.char)
			self._complete_screen:Hide()
		end
		event.handled = true
	elseif event.sym == 102 and ALittle.BitAnd(event.mod, 0x00c0) ~= 0 then
		self._find_dialog.visible = true
		self._find_input:DelayFocus()
		self._find_input:SelectAll()
	elseif event.sym == 1073742048 then
		if self._move_in and not self._in_query_info then
			local x, y = self._edit_quad:LocalToGlobal()
			self:UpdateQueryInfo(A_UISystem.mouse_x - x, A_UISystem.mouse_y - y)
		end
	elseif event.sym == 27 then
		if self._find_dialog ~= nil and self._find_dialog.visible then
			self._find_dialog.visible = false
			event.handled = true
		end
	elseif event.sym == 1073741893 then
		self:DoQueryGoto(self._cursor.line, self._cursor.char)
		self:StopQueryInfo()
		event.handled = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
	end
end

function AUICodeEdit:DispatchChangedEvent()
	self:DispatchEvent(___all_struct[958494922], {})
end

function AUICodeEdit:HandleKeyUp(event)
	if event.sym == 1073742048 then
		if self._move_in then
			ALittle.System_SetEditCursor()
			self:StopQueryInfo()
		else
			ALittle.System_SetNormalCursor()
		end
	end
end

function AUICodeEdit:OnUnDo()
	self._complete_screen:Hide()
end

function AUICodeEdit:OnTabRightMenu(menu)
	if self._language ~= nil then
		self._language:OnTabRightMenu(menu)
	end
end

function AUICodeEdit:OnHide()
	self._cursor:Hide()
	if self._language ~= nil then
		self._language:OnHide()
	end
end

function AUICodeEdit:OnShow()
	self._edit_quad:DelayFocus()
	if self._language ~= nil then
		self._language:OnShow()
	end
	self:StartErrorLoop(true)
end

function AUICodeEdit:OnSave()
	if self._language ~= nil then
		self._language:OnSave()
	end
end

function AUICodeEdit:OnClose()
	if self._error_loop ~= nil then
		self._error_loop:Stop()
		self._error_loop = nil
	end
	self._cursor:Hide()
	self._file_path = nil
	ALittle.System_CloseIME()
	if self._language ~= nil then
		self._language:OnClose()
	end
	collectgarbage("collect")
end

function AUICodeEdit:Load(file_path, content, revoke_list, language)
	self._language = language
	local upper_ext = ALittle.File_GetFileExtByPathAndUpper(file_path)
	if self._language == nil and upper_ext == "ABNF" then
		self._language = AUICodeABnf(nil, file_path)
	end
	if self._language == nil and AUICodeProject.SupportUpperExt(upper_ext) then
		self._language = AUICodeCommon(nil, file_path)
	end
	if self._language ~= nil then
		self._language:OnOpen(content)
	end
	if content == nil then
		content = ALittle.File_ReadTextFromStdFile(file_path)
	end
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
		char.red = CODE_FONT_RED
		char.green = CODE_FONT_GREEN
		char.blue = CODE_FONT_BLUE
		char.char = char_text
		char.pre_width = pre_width
		pre_width = pre_width + (char.width)
		if line == nil then
			line = {}
			line.edit = self
			line.char_count = 0
			line.char_list = {}
			line.container = AUICodeLineContainer(g_Control)
			line.container._user_data = line
			line.container.height = CODE_LINE_HEIGHT
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
		line.edit = self
		line.char_count = 0
		line.char_list = {}
		line.container = AUICodeLineContainer(g_Control)
		line.container._user_data = line
		line.container.height = CODE_LINE_HEIGHT
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
	self._code_screen.container.width = max_width + CODE_LINE_NUMBER_WIDTH
	self._code_screen.container.height = self._line_count * CODE_LINE_HEIGHT + CODE_PAD_LINES * CODE_LINE_HEIGHT
	self._code_screen:RejustScrollBar()
	self._cursor:SetLineChar(1, 0)
	if self._language ~= nil then
		self._language:SetText(content)
	end
	self:UpdateLineNumber()
end

function AUICodeEdit:MultiTabInsert(need_revoke, revoke_bind)
	local insert_revoke
	if need_revoke then
		insert_revoke = ALittle.RevokeBind()
	end
	if self._select_cursor.line_start == nil or self._select_cursor.line_end == nil then
		return false
	end
	local old_line_start = self._select_cursor.line_start
	local old_char_start = self._select_cursor.char_start
	local old_line_end = self._select_cursor.line_end
	local old_char_end = self._select_cursor.char_end
	local old_line = self._cursor.line
	local old_char = self._cursor.char
	local line_min = self._select_cursor.line_start
	local line_max = self._select_cursor.line_end
	if line_min > line_max then
		local temp = line_min
		line_min = line_max
		line_max = temp
	end
	local index = line_min
	while true do
		if not(index <= line_max) then break end
		if self._language ~= nil then
			self._language:InsertText("    ", index, 1)
		end
		local line = self._line_list[index]
		for char_index, char in ___ipairs(line.char_list) do
			char.pre_width = char.pre_width + (self._ascii_width * 4)
			if char.text ~= nil then
				char.text.x = char.text.x + (self._ascii_width * 4)
			end
		end
		line.container.width = line.container.width + (self._ascii_width * 4)
		local i = 1
		while true do
			if not(i <= 4) then break end
			local char = {}
			char.pre_width = (i - 1) * self._ascii_width
			char.char = " "
			char.width = self._ascii_width
			ALittle.List_Insert(line.char_list, i, char)
			i = i+(1)
		end
		line.char_count = line.char_count + (4)
		index = index+(1)
	end
	local max_width = 0.0
	for index, line in ___ipairs(self._line_list) do
		if line.container.width > max_width then
			max_width = line.container.width
		end
	end
	self._code_screen.container.width = max_width + CODE_LINE_NUMBER_WIDTH
	self._code_screen:RejustScrollBar()
	self._cursor:SetLineChar(old_line, old_char + 4)
	self._select_cursor:StartLineChar(old_line_start, old_char_start + 4)
	self._select_cursor:UpdateLineChar(old_line_end, old_char_end + 4)
	if need_revoke then
		local revoke = AUICodeMultiTabInsertRevoke(self, self._cursor, self._select_cursor, old_line_start, old_char_start, old_line_end, old_char_end, self._select_cursor.line_start, self._select_cursor.char_start, self._select_cursor.line_end, self._select_cursor.char_end, revoke_bind == nil)
		insert_revoke:PushRevoke(revoke)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(insert_revoke)
		else
			self._revoke_list:PushRevoke(insert_revoke)
		end
	end
	return true
end

function AUICodeEdit:MultiLineFormat(line_start, line_end)
	if self._language == nil or not self._language:NeedAutoFormat() then
		return
	end
	if line_start > line_end then
		local temp = line_start
		line_start = line_end
		line_end = temp
	end
	local old_line = self._cursor.line
	local old_char = self._cursor.char
	local revoke_bind = ALittle.RevokeBind()
	local old_indent_list = {}
	local indent_list = {}
	local delete_list = {}
	local index = line_start
	while true do
		if not(index <= line_end) then break end
		local line = self._line_list[index]
		local old_indent = 0
		local delete_count = 0
		for i, char in ___ipairs(line.char_list) do
			if char.char == " " then
				old_indent = old_indent + (1)
				delete_count = delete_count + (1)
			elseif char.char == "\t" then
				old_indent = old_indent + (4)
				delete_count = delete_count + (1)
			else
				break
			end
		end
		old_indent_list[index] = old_indent
		delete_list[index] = delete_count
		local first_char = line.char_list[1]
		if first_char == nil or first_char.char == "\r" or first_char.char == "\n" then
			indent_list[index] = 0
		else
			indent_list[index] = self._language:QueryFormateIndent(index, delete_count)
		end
		index = index+(1)
	end
	local changed = false
	local index = line_start
	while true do
		if not(index <= line_end) then break end
		local line = self._line_list[index]
		local old_indent = old_indent_list[index]
		local delete_count = delete_list[index]
		local indent = indent_list[index]
		if old_indent ~= indent then
			self._select_cursor:StartLineChar(index, 0)
			self._select_cursor:UpdateLineChar(index, delete_count)
			self._cursor:SetLineChar(index, 0)
			local new_indent = ""
			local i = 1
			while true do
				if not(i <= indent) then break end
				new_indent = new_indent .. " "
				i = i+(1)
			end
			self:InsertText(new_indent, true, revoke_bind)
			changed = true
			if old_line == index then
				old_char = old_char + (indent - delete_count)
			end
		end
		index = index+(1)
	end
	if changed then
		revoke_bind.complete = Lua.Bind(self.DispatchChangedEvent, self)
		self._revoke_list:PushRevoke(revoke_bind)
		self._cursor:SetLineChar(old_line, old_char)
	end
end

function AUICodeEdit:MultiTabDelete(need_revoke, revoke_bind)
	local insert_revoke
	if need_revoke then
		insert_revoke = ALittle.RevokeBind()
	end
	if self._select_cursor.line_start == nil or self._select_cursor.line_end == nil then
		return false
	end
	local old_line_start = self._select_cursor.line_start
	local old_char_start = self._select_cursor.char_start
	local old_line_end = self._select_cursor.line_end
	local old_char_end = self._select_cursor.char_end
	local old_line = self._cursor.line
	local old_char = self._cursor.char
	local line_min = self._select_cursor.line_start
	local line_max = self._select_cursor.line_end
	if line_min > line_max then
		local temp = line_min
		line_min = line_max
		line_max = temp
	end
	local changed = false
	local index = line_min
	while true do
		if not(index <= line_max) then break end
		local line = self._line_list[index]
		local delete_count = 0
		local i = 1
		while true do
			if not(i <= 4) then break end
			if line.char_list[i].char == "\t" then
				if i == 1 then
					delete_count = 1
					break
				else
					break
				end
			elseif line.char_list[i].char == " " then
				delete_count = delete_count + (1)
			else
				break
			end
			i = i+(1)
		end
		if delete_count > 0 then
			changed = true
			if self._language ~= nil then
				self._language:DeleteText(index, 1, index, delete_count)
			end
			for char_index, char in ___ipairs(line.char_list) do
				char.pre_width = char.pre_width - (self._ascii_width * 4)
				if char.text ~= nil then
					char.text.x = char.text.x - (self._ascii_width * 4)
				end
			end
			line.container.width = line.container.width - (self._ascii_width * 4)
			ALittle.List_Splice(line.char_list, 1, delete_count)
			line.char_count = line.char_count - (delete_count)
			if index == old_line_start then
				old_char_start = old_char_start - (delete_count)
			elseif index == old_line_end then
				old_char_end = old_char_end - (delete_count)
			end
			if index == old_line then
				old_char = old_char - (delete_count)
			end
		end
		index = index+(1)
	end
	if changed then
		self._cursor:SetLineChar(old_line, old_char)
		self._select_cursor:StartLineChar(old_line_start, old_char_start)
		self._select_cursor:UpdateLineChar(old_line_end, old_char_end)
		local max_width = 0.0
		for index, line in ___ipairs(self._line_list) do
			if line.container.width > max_width then
				max_width = line.container.width
			end
		end
		self._code_screen.container.width = max_width + CODE_LINE_NUMBER_WIDTH
		self._code_screen:RejustScrollBar()
		if need_revoke then
			local revoke = AUICodeMultiTabDeleteRevoke(self, self._cursor, self._select_cursor, old_line_start, old_char_start, old_line_end, old_char_end, self._select_cursor.line_start, self._select_cursor.char_start, self._select_cursor.line_end, self._select_cursor.char_end, revoke_bind == nil)
			insert_revoke:PushRevoke(revoke)
			if revoke_bind ~= nil then
				revoke_bind:PushRevoke(insert_revoke)
			else
				self._revoke_list:PushRevoke(insert_revoke)
			end
		end
	end
	return true
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
	if self._language ~= nil then
		self._language:InsertText(content, self._cursor.line, self._cursor.char)
	end
	local old_it_line = self._cursor.line
	local old_it_char = self._cursor.char
	local split_pre_line = self._line_list[self._cursor.line]
	local split_it_char = self._cursor.char
	local line_map = {}
	if split_pre_line == nil then
		split_pre_line = {}
		split_pre_line.edit = self
		split_pre_line.char_count = 0
		split_pre_line.char_list = {}
		split_pre_line.container = AUICodeLineContainer(g_Control)
		split_pre_line.container._user_data = split_pre_line
		split_pre_line.container.height = CODE_LINE_HEIGHT
		self._code_linear:AddChild(split_pre_line.container)
		self._line_count = self._line_count + (1)
		self._line_list[self._line_count] = split_pre_line
		line_map[self._line_count] = true
	end
	local split_next_line = split_pre_line
	local it_cursor_line = self._cursor.line
	local it_cursor_char = self._cursor.char
	line_map[self._cursor.line] = true
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
			split_next_line = {}
			split_next_line.edit = self
			split_next_line.char_count = 0
			split_next_line.char_list = {}
			split_next_line.container = AUICodeLineContainer(g_Control)
			split_next_line.container._user_data = split_next_line
			split_next_line.container.height = CODE_LINE_HEIGHT
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
			line_map[new_line_count] = true
			i = i+(1)
		end
		do
			self._code_linear:AddChild(split_next_line.container)
			new_line_count = new_line_count + (1)
			new_line_list[new_line_count] = split_next_line
			it_cursor_line = new_line_count
			it_cursor_char = 0
			line_map[new_line_count] = true
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
		split_pre_line.container._text:RemoveAllChild()
		local pre_width = 0.0
		local i = 1
		while true do
			if not(i <= split_it_char) then break end
			local char = split_pre_line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
			end
			split_pre_line.container:AddChar(char)
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
			end
			split_pre_line.container:AddChar(char)
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
			end
			split_pre_line.container:AddChar(char)
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
		split_next_line.container._text:RemoveAllChild()
		local pre_width = 0.0
		local i = 1
		while true do
			if not(i <= line.char_count) then break end
			local char = line.char_list[i]
			char.pre_width = pre_width
			if char.text ~= nil then
				char.text.x = pre_width
			end
			split_next_line.container:AddChar(char)
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
			end
			split_next_line.container:AddChar(char)
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
	self._code_screen.container.width = max_width + CODE_LINE_NUMBER_WIDTH
	self._code_screen.container.height = self._line_count * CODE_LINE_HEIGHT + CODE_PAD_LINES * CODE_LINE_HEIGHT
	self._code_screen:RejustScrollBar()
	self._cursor:SetLineChar(it_cursor_line, it_cursor_char)
	if need_revoke then
		local revoke = AUICodeInsertTextRevoke(self, self._cursor, self._select_cursor, old_it_line, old_it_char, it_cursor_line, it_cursor_char, content, revoke_bind == nil)
		insert_revoke:PushRevoke(revoke)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(insert_revoke)
		else
			self._revoke_list:PushRevoke(insert_revoke)
		end
	end
	if self._find_map ~= nil then
		for line_index, _ in ___pairs(line_map) do
			self:UpdateLineFind(line_index)
		end
	end
	self:UpdateLineNumber()
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

function AUICodeEdit:GetSelectText()
	return self._select_cursor:GetSelectText()
end

function AUICodeEdit:GetTargetText(line_start, char_start, line_end, char_end)
	return self._select_cursor:GetTargetText(line_start, char_start, line_end, char_end)
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
	self:OnSave()
	return true
end

function AUICodeEdit:EditFocus(line_start, char_start, line_end, char_end, edit_focus)
	if edit_focus then
		self._edit_quad:DelayFocus()
	end
	if self._line_count <= 0 then
		self._select_cursor:Hide()
		self._cursor:SetLineChar(1, 0)
		self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
		return
	end
	if line_start == nil or char_start == nil then
		return
	end
	if char_start > 0 then
		char_start = char_start - (1)
	end
	if line_end == nil or char_end == nil then
		self._select_cursor:Hide()
		if line_start > self._line_count then
			self._cursor:SetLineChar(1, 0)
			self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
			return
		end
		local line = self._line_list[line_start]
		local count = line.char_count
		while count > 0 and line.char_list[count].width <= 0 do
			count = count - 1
		end
		if char_start > count then
			char_start = count
		end
		self._cursor:SetLineChar(line_start, char_start)
		self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
		return
	end
	if line_start > self._line_count or line_end > self._line_count then
		self._select_cursor:Hide()
		self._cursor:SetLineChar(1, 0)
		self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
		return
	end
	do
		local line = self._line_list[line_start]
		local count = line.char_count
		while count > 0 and line.char_list[count].width <= 0 do
			count = count - 1
		end
		if char_start > count then
			char_start = count
		end
	end
	do
		local line = self._line_list[line_end]
		local count = line.char_count
		while count > 0 and line.char_list[count].width <= 0 do
			count = count - 1
		end
		if char_end > count then
			char_end = count
		end
	end
	if line_start == line_end and char_start == char_end then
		self._select_cursor:Hide()
		self._cursor:SetLineChar(line_start, char_start)
		self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
		return
	end
	self._cursor:SetLineChar(line_start, char_start)
	self._select_cursor:StartLineChar(line_start, char_start)
	self._select_cursor:UpdateLineChar(line_end, char_end)
	self:FocusLineCharToCenter(self._cursor.line, self._cursor.char)
end

