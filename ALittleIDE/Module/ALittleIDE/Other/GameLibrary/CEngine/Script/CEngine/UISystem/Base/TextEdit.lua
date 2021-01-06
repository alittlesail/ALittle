-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


local __type = ALittle.String_Type
local __tonumber = ALittle.Math_ToDouble
local __tostring = ALittle.String_ToString
local __floor = ALittle.Math_Floor
local __sub = ALittle.String_Sub
local __find = ALittle.String_Find
assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.TextEdit = Lua.Class(ALittle.DisplayObject, "ALittle.TextEdit")

function ALittle.TextEdit:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPITextEdit())
	___rawset(self, "_cursor_red", 1)
	___rawset(self, "_cursor_green", 1)
	___rawset(self, "_cursor_blue", 1)
	___rawset(self, "_bold", false)
	___rawset(self, "_italic", false)
	___rawset(self, "_underline", false)
	___rawset(self, "_deleteline", false)
	___rawset(self, "_default_text", "")
	___rawset(self, "_default_text_alpha", 1)
	___rawset(self, "_flip", 0)
	___rawset(self, "_current_flash_alpha", 1)
	___rawset(self, "_current_flash_dir", -0.05)
	___rawset(self, "_is_selecting", false)
	___rawset(self, "_can_scroll", true)
	___rawset(self, "_editable", true)
	___rawset(self, "_ims_padding", 0)
	___rawset(self, "_regex", "")
	___rawset(self, "_limit_len", 0)
	self:AddEventListener(___all_struct[-644464135], self, self.HandleFocusIn)
	self:AddEventListener(___all_struct[292776509], self, self.HandleFocusOut)
	self:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self:AddEventListener(___all_struct[-1234078962], self, self.HandleTextInput)
	self:AddEventListener(___all_struct[-1604617962], self, self.HandleKeyDown)
	self:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self:AddEventListener(___all_struct[-1737121315], self, self.HandleMButtonWheel)
	A_LoadTextureManager:RegisterRedrawControl(self)
end

function ALittle.TextEdit:Redraw()
	self._show:NeedDraw()
end

function ALittle.TextEdit:Update()
	if self._is_selecting == false then
		self._current_flash_alpha = self._current_flash_alpha + self._current_flash_dir
		if (self._current_flash_dir < 0 and self._current_flash_alpha < -0.05) or (self._current_flash_dir > 0 and self._current_flash_alpha > 1.5) then
			self._current_flash_dir = -self._current_flash_dir
		end
	else
		self._current_flash_alpha = 0.5
	end
	self._show:SetCursorAlpha(self._current_flash_alpha)
end

function ALittle.TextEdit.__getter:is_input()
	return true
end

function ALittle.TextEdit:GetRealHeight()
	return self._show:GetRealHeight()
end

function ALittle.TextEdit:GetLineWidth(line_index)
	line_index = line_index - 1
	return self._show:GetLineWidth(line_index)
end

function ALittle.TextEdit:GetLineCount()
	return self._show:GetLineCount()
end

function ALittle.TextEdit:GetScrollOffset()
	return self._show:GetScrollOffset()
end

function ALittle.TextEdit.__setter:default_text(value)
	self._default_text = value
	if self._default_text == nil then
		self._default_text = ""
	end
	if self._show:IsDefaultText() then
		self._show:SetDefaultText(true, self._default_text)
	end
end

function ALittle.TextEdit.__getter:default_text()
	return self._default_text
end

function ALittle.TextEdit.__setter:default_text_alpha(value)
	if __type(value) ~= "number" then
		value = __tonumber(value)
	end
	if value == nil or self._default_text_alpha == value then
		return
	end
	self._default_text_alpha = value
	self._show:SetDefaultTextAlpha(value)
end

function ALittle.TextEdit.__getter:default_text_alpha()
	return self._default_text_alpha
end

function ALittle.TextEdit.__getter:cursor_x()
	return self._show:GetCursorX()
end

function ALittle.TextEdit.__getter:cursor_y()
	return self._show:GetCursorY()
end

function ALittle.TextEdit.__getter:cursor_b()
	return (self._show:GetCursorY() + self._show:GetCursorHeight()) * self.scale_y + self._ims_padding
end

function ALittle.TextEdit.__setter:editable(value)
	self._editable = value
end

function ALittle.TextEdit.__getter:editable()
	return self._editable
end

function ALittle.TextEdit.__setter:font_path(value)
	self._font_path = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
end

function ALittle.TextEdit.__setter:font_size(value)
	self._font_size = value
	if self._font_path == nil or self._font_size == nil then
		return
	end
	self._ctrl_sys:SetFont(self, self._font_path, self._font_size)
end

function ALittle.TextEdit.__getter:font_path()
	return self._font_path
end

function ALittle.TextEdit.__getter:font_size()
	return self._font_size
end

function ALittle.TextEdit.__setter:text(value)
	if value == nil then
		return
	end
	value = __tostring(value)
	self._is_selecting = false
	if value == "" then
		if self._default_text == nil then
			self._default_text = ""
		end
		self._show:SetDefaultText(true, self._default_text)
	else
		self._show:SetDefaultText(false, "")
		self._show:SetText(value)
	end
end

function ALittle.TextEdit.__getter:text()
	if self._show:IsDefaultText() then
		return ""
	end
	return self._show:GetText()
end

function ALittle.TextEdit.__setter:bold(value)
	if self._bold == value then
		return
	end
	self._bold = value
	self._show:SetBold(value)
end

function ALittle.TextEdit.__getter:bold()
	return self._bold
end

function ALittle.TextEdit.__setter:italic(value)
	if self._italic == value then
		return
	end
	self._italic = value
	self._show:SetItalic(value)
end

function ALittle.TextEdit.__getter:italic()
	return self._italic
end

function ALittle.TextEdit.__setter:underline(value)
	if self._underline == value then
		return
	end
	self._underline = value
	self._show:SetUnderline(value)
end

function ALittle.TextEdit.__getter:underline()
	return self._underline
end

function ALittle.TextEdit.__setter:deleteline(value)
	if self._deleteline == value then
		return
	end
	self._deleteline = value
	self._show:SetDeleteline(value)
end

function ALittle.TextEdit.__getter:deleteline()
	return self._deleteline
end

function ALittle.TextEdit:SetCursorToEnd()
	self._is_selecting = false
	self._show:SetCursorToEnd()
end

function ALittle.TextEdit:SetCursorToHome()
	self._is_selecting = false
	self._show:SetCursorToHome()
end

function ALittle.TextEdit.__setter:ims_padding(value)
	self._ims_padding = value
end

function ALittle.TextEdit.__getter:ims_padding()
	return self._ims_padding
end

function ALittle.TextEdit.__getter:regex()
	return self._regex
end

function ALittle.TextEdit.__setter:regex(value)
	if value == nil then
		value = ""
	end
	self._regex = value
end

function ALittle.TextEdit.__getter:limit_len()
	return self._limit_len
end

function ALittle.TextEdit.__setter:limit_len(value)
	if value == nil then
		value = 0
	end
	self._limit_len = value
end

function ALittle.TextEdit:HandleFocusIn(event)
	self._show:ShowCursor(true)
	if self._loop == nil then
		self._loop = ALittle.LoopFunction(Lua.Bind(self.Update, self), -1, 1, 1)
	end
	A_LoopSystem:AddUpdater(self._loop)
	if self._editable then
		local global_x, global_y = self:LocalToGlobal()
		global_x = global_x + (self.cursor_x)
		global_y = global_y + ((self.cursor_y + self.font_size) * self.scale_y)
		ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, 5 + self._ims_padding)
		ALittle.System_OpenIME()
	end
	if self._show:IsDefaultText() then
		self._show:SetDefaultText(false, "")
	end
end

function ALittle.TextEdit:HandleFocusOut(event)
	self._is_selecting = false
	self._show:ShowCursor(false)
	A_LoopSystem:RemoveUpdater(self._loop)
	ALittle.System_CloseIME()
	if self.text == "" then
		if self._default_text == nil then
			self._default_text = ""
		end
		self._show:SetDefaultText(true, self._default_text)
	end
end

function ALittle.TextEdit:HandleLButtonDown(event)
	if self._editable then
		local global_x, global_y = self:LocalToGlobal()
		global_x = global_x + (self.cursor_x)
		global_y = global_y + ((self.cursor_y + self.font_size) * self.scale_y)
		ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, 5 + self._ims_padding)
		ALittle.System_OpenIME()
	end
	if event.count % 3 == 1 then
		self._is_selecting = false
		self._show:ClickCursor(event.rel_x, event.rel_y)
	elseif event.count % 3 == 2 then
		self._is_selecting = self._show:ClickWordCursor(event.rel_x, event.rel_y)
	else
		self._is_selecting = true
		self._show:SelectAll()
	end
end

function ALittle.TextEdit:CheckTextRegexLimit(text)
	if self._limit_len > 0 then
		local text_len = ALittle.String_GetWordCount(text)
		if text_len > self._limit_len then
			return false
		end
		local select_len = ALittle.String_GetWordCount(self._show:GetSelectText())
		local total_len = ALittle.String_GetWordCount(self.text)
		if total_len - select_len + text_len > self._limit_len then
			return false
		end
	end
	if self._regex ~= "" then
		while text ~= "" do
			local byte_count = ALittle.String_GetByteCount(text, 1)
			local sub_text = __sub(text, 1, byte_count)
			local start_it = __find(sub_text, self._regex)
			if start_it == nil then
				return false
			end
			text = __sub(text, byte_count + 1)
		end
	end
	return true
end

function ALittle.TextEdit:HandleTextInput(event)
	if self._editable or event.custom then
		self._is_selecting = false
		if self:CheckTextRegexLimit(event.text) == false then
			return
		end
		local is_change = self._show:InsertText(event.text)
		if is_change then
			self:DispatchEvent(___all_struct[958494922], {})
		end
	end
end

function ALittle.TextEdit:HandleKeyDown(event)
	local is_change = false
	if event.sym == 9 then
		if self._editable or event.custom then
			self._is_selecting = false
			if self:CheckTextRegexLimit("\t") == false then
				return
			end
			is_change = self._show:InsertText("\t")
			if is_change then
				self:DispatchEvent(___all_struct[958494922], {})
			end
			event.handled = true
		end
	elseif event.sym == 1073741904 then
		if event.mod & 0x0003 == 0 then
			self._is_selecting = false
			self._show:CursorOffsetLR(true)
		else
			self._is_selecting = true
			self._show:SelectCursorOffsetLR(true)
		end
		event.handled = true
	elseif event.sym == 1073741903 then
		if event.mod & 0x0003 == 0 then
			self._is_selecting = false
			self._show:CursorOffsetLR(false)
		else
			self._is_selecting = true
			self._show:SelectCursorOffsetLR(false)
		end
		event.handled = true
	elseif event.sym == 1073741906 then
		if event.mod & 0x0003 == 0 then
			self._is_selecting = false
			self._show:CursorOffsetUD(true)
		else
			self._is_selecting = true
			self._show:SelectCursorOffsetUD(true)
		end
		event.handled = true
	elseif event.sym == 1073741905 then
		if event.mod & 0x0003 == 0 then
			self._is_selecting = false
			self._show:CursorOffsetUD(false)
		else
			self._is_selecting = true
			self._show:SelectCursorOffsetUD(false)
		end
		event.handled = true
	elseif event.sym == 8 then
		if self._editable or event.custom then
			self._is_selecting = false
			is_change = self._show:DeleteText(true)
			event.handled = true
		end
	elseif event.sym == 127 then
		if self._editable or event.custom then
			self._is_selecting = false
			is_change = self._show:DeleteText(false)
			event.handled = true
		end
	elseif event.sym == 1073741898 then
		self._is_selecting = false
		self._show:SetCursorToHome()
		event.handled = true
	elseif event.sym == 1073741901 then
		self._is_selecting = false
		self._show:SetCursorToEnd()
		event.handled = true
	elseif event.sym == 13 or event.sym == 1073741912 then
		if self._editable or event.custom then
			self._is_selecting = false
			if self:CheckTextRegexLimit("\n") == false then
				return
			end
			is_change = self._show:InsertText("\n")
			if is_change then
				self:DispatchEvent(___all_struct[958494922], {})
			end
			event.handled = true
		end
	elseif event.sym == 120 and event.mod & 0x00c0 ~= 0 then
		if self._editable or event.custom then
			self._is_selecting = false
			local select_text = self._show:GetSelectText()
			if select_text ~= "" then
				ALittle.System_SetClipboardText(select_text)
				is_change = self._show:DeleteSelectText()
			end
			event.handled = true
		end
	elseif event.sym == 99 and event.mod & 0x00c0 ~= 0 then
		local select_text = self._show:GetSelectText()
		if select_text ~= "" then
			ALittle.System_SetClipboardText(select_text)
		end
		event.handled = true
	elseif event.sym == 118 and event.mod & 0x00c0 ~= 0 then
		if self._editable or event.custom then
			self._is_selecting = false
			if ALittle.System_HasClipboardText() then
				local clip_board_text = ALittle.System_GetClipboardText()
				if self:CheckTextRegexLimit(clip_board_text) == false then
					return
				end
				is_change = self._show:InsertText(clip_board_text)
			end
			event.handled = true
		end
	elseif event.sym == 97 and event.mod & 0x00c0 ~= 0 then
		self._is_selecting = true
		self._show:SelectAll()
		event.handled = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
		self._current_flash_alpha = 1.5
	end
end

function ALittle.TextEdit:SelectAll()
	self._is_selecting = true
	self._show:SelectAll()
end

function ALittle.TextEdit:CopyText()
	local select_text = self._show:GetSelectText()
	if select_text == "" then
		select_text = self.text
	end
	if select_text ~= "" then
		ALittle.System_SetClipboardText(select_text)
	end
end

function ALittle.TextEdit:PasteText()
	if self._editable == false then
		return
	end
	if self._show:IsDefaultText() then
		self._show:SetDefaultText(false, "")
	end
	self._is_selecting = false
	if ALittle.System_HasClipboardText() then
		local clip_board_text = ALittle.System_GetClipboardText()
		if self:CheckTextRegexLimit(clip_board_text) == false then
			return
		end
		self._show:InsertText(clip_board_text)
	end
end

function ALittle.TextEdit:CutText()
	if self._editable == false then
		return
	end
	self._is_selecting = false
	local select_text = self._show:GetSelectText()
	if select_text ~= "" then
		ALittle.System_SetClipboardText(select_text)
		self._show:DeleteSelectText()
	end
end

function ALittle.TextEdit:InsertText(text)
	if self._editable == false then
		return
	end
	if self._show:IsDefaultText() then
		self._show:SetDefaultText(false, "")
	end
	self._is_selecting = false
	if text ~= nil then
		if self:CheckTextRegexLimit(text) == false then
			return
		end
		self._show:InsertText(text)
	end
end

function ALittle.TextEdit:HandleDragBegin(event)
	self._is_selecting = true
	self._show:DragCursorBegin()
end

function ALittle.TextEdit:HandleDrag(event)
	if self._is_selecting == false then
		return
	end
	self._show:DragCursor(event.rel_x, event.rel_y)
end

function ALittle.TextEdit:HandleMButtonWheel(event)
	if event.delta_y > 0 then
		self._is_selecting = false
		self._show:CursorOffsetUD(true)
	elseif event.delta_y < 0 then
		self._is_selecting = false
		self._show:CursorOffsetUD(false)
	end
	if event.delta_x > 0 then
		self._is_selecting = false
		self._show:SelectCursorOffsetLR(true)
	elseif event.delta_x < 0 then
		self._is_selecting = false
		self._show:SelectCursorOffsetLR(false)
	end
end

function ALittle.TextEdit:HandleMoveIn(event)
	ALittle.System_SetEditCursor()
end

function ALittle.TextEdit:HandleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function ALittle.TextEdit.__setter:cursor_red(value)
	if self._cursor_red == value then
		return
	end
	self._cursor_red = value
	self._show:SetCursorRed(value)
end

function ALittle.TextEdit.__getter:cursor_red()
	return self._cursor_red
end

function ALittle.TextEdit.__setter:cursor_green(value)
	if self._cursor_green == value then
		return
	end
	self._cursor_green = value
	self._show:SetCursorGreen(value)
end

function ALittle.TextEdit.__getter:cursor_green()
	return self._cursor_green
end

function ALittle.TextEdit.__setter:cursor_blue(value)
	if self._cursor_blue == value then
		return
	end
	self._cursor_blue = value
	self._show:SetCursorBlue(value)
end

function ALittle.TextEdit.__getter:cursor_blue()
	return self._cursor_blue
end

function ALittle.TextEdit.__getter:flip()
	return self._flip
end

function ALittle.TextEdit.__setter:flip(value)
	self._flip = value
	self._show:SetFlip(value)
end

end