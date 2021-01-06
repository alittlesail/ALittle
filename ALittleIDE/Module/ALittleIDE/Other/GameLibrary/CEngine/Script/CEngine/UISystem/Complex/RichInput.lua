-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1818243950, "ALittle.RichInputCharInfo", {
name = "ALittle.RichInputCharInfo", ns_name = "ALittle", rl_name = "RichInputCharInfo", hash_code = 1818243950,
name_list = {"acc_width","pre_width","text_info","text","password_text","text_object","ctrl_info","ctrl"},
type_list = {"double","double","ALittle.DisplayInfo","string","string","ALittle.Text","ALittle.DisplayInfo","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1640499878, "ALittle.UIRichInputLongClickEvent", {
name = "ALittle.UIRichInputLongClickEvent", ns_name = "ALittle", rl_name = "UIRichInputLongClickEvent", hash_code = 1640499878,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1424993548, "ALittle.RichInputMultiDragBeginEvent", {
name = "ALittle.RichInputMultiDragBeginEvent", ns_name = "ALittle", rl_name = "RichInputMultiDragBeginEvent", hash_code = 1424993548,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-884368490, "ALittle.RichInputMultiDragEndEvent", {
name = "ALittle.RichInputMultiDragEndEvent", ns_name = "ALittle", rl_name = "RichInputMultiDragEndEvent", hash_code = -884368490,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-683607428, "ALittle.RichInputCursorClickEvent", {
name = "ALittle.RichInputCursorClickEvent", ns_name = "ALittle", rl_name = "RichInputCursorClickEvent", hash_code = -683607428,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-605767802, "ALittle.RichInputMultiDragEvent", {
name = "ALittle.RichInputMultiDragEvent", ns_name = "ALittle", rl_name = "RichInputMultiDragEvent", hash_code = -605767802,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-256576702, "ALittle.RichInputFontChangedEvent", {
name = "ALittle.RichInputFontChangedEvent", ns_name = "ALittle", rl_name = "RichInputFontChangedEvent", hash_code = -256576702,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

local __byte = ALittle.String_Byte
local __sub = ALittle.String_Sub
local __find = ALittle.String_Find
local __floor = ALittle.Math_Floor
local __len = ALittle.String_Len
local __abs = ALittle.Math_Abs
local __type = ALittle.String_Type
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.RichInput = Lua.Class(ALittle.DisplayLayout, "ALittle.RichInput")

function ALittle.RichInput:CheckDisplayList(content)
	for k, v in ___ipairs(content) do
		if v.__class == nil then
			return false
		end
	end
	return true
end

function ALittle.RichInput:CharIsNumber(str)
	local c = __byte(str, 1)
	return c >= 48 and c <= 57
end

function ALittle.RichInput:CharIsLetter(str)
	local c = __byte(str, 1)
	return c >= 65 and c <= 90 or c >= 97 and c <= 122
end

function ALittle.RichInput:CompareTextInfo(a, b)
	if a.font_path ~= b.font_path then
		return false
	end
	if a.font_size ~= b.font_size then
		return false
	end
	if a.red ~= b.red then
		return false
	end
	if a.green ~= b.green then
		return false
	end
	if a.blue ~= b.blue then
		return false
	end
	if a.bold ~= b.bold then
		return false
	end
	if a.italic ~= b.italic then
		return false
	end
	if a.underline ~= b.underline then
		return false
	end
	if a.deleteline ~= b.deleteline then
		return false
	end
	return true
end

function ALittle.RichInput:CopyTextInfo(b)
	local a = {}
	a.__class = "Text"
	a.font_path = b.font_path
	a.font_size = b.font_size
	a.red = b.red
	a.green = b.green
	a.blue = b.blue
	a.bold = b.bold
	a.italic = b.italic
	a.underline = b.underline
	a.deleteline = b.deleteline
	return a
end

function ALittle.RichInput:InitTextInfo()
	local font_text = self._font_text
	local a = {}
	a.__class = "Text"
	a.font_path = font_text.font_path
	a.font_size = font_text.font_size
	a.red = font_text.red
	a.green = font_text.green
	a.blue = font_text.blue
	a.bold = font_text.bold
	a.italic = font_text.italic
	a.underline = font_text.underline
	a.deleteline = font_text.deleteline
	return a
end

function ALittle.RichInput:SetDrawText(font_text)
	local draw_text = self._draw_text
	draw_text.font_path = font_text.font_path
	draw_text.font_size = font_text.font_size
	draw_text.red = font_text.red
	draw_text.green = font_text.green
	draw_text.blue = font_text.blue
	draw_text.bold = font_text.bold
	draw_text.italic = font_text.italic
	draw_text.underline = font_text.underline
	draw_text.deleteline = font_text.deleteline
end

function ALittle.RichInput:SplitText(char_info, char_info_list, char_info_list_count)
	local text = char_info.text
	while true do
		local start_index_1 = __find(text, "\n")
		local start_index_2 = __find(text, "\t")
		if start_index_1 ~= nil and start_index_2 ~= nil then
			if start_index_1 < start_index_2 then
				start_index_2 = nil
			else
				start_index_1 = nil
			end
		end
		if start_index_1 ~= nil then
			local sub_text = __sub(text, 1, start_index_1 - 1)
			text = __sub(text, start_index_1 + 1)
			if sub_text ~= "" then
				local new_char_info = ALittle.String_CopyTable(char_info)
				new_char_info.text = sub_text
				char_info_list_count = char_info_list_count + 1
				char_info_list[char_info_list_count] = new_char_info
			end
		elseif start_index_2 ~= nil then
			local sub_text = __sub(text, 1, start_index_2 - 1)
			text = __sub(text, start_index_2 + 1)
			if sub_text ~= "" then
				local new_char_info = ALittle.String_CopyTable(char_info)
				new_char_info.text = sub_text
				char_info_list_count = char_info_list_count + 1
				char_info_list[char_info_list_count] = new_char_info
			end
		else
			if text ~= "" then
				local new_char_info = ALittle.String_CopyTable(char_info)
				new_char_info.text = text
				char_info_list_count = char_info_list_count + 1
				char_info_list[char_info_list_count] = new_char_info
			end
			break
		end
	end
	return char_info_list_count
end

function ALittle.RichInput:DisplayListToCharInfoList(display_list, default_text_info)
	local char_info_list = {}
	local char_info_list_count = 0
	local last_text_info = default_text_info
	for display_index, display_info in ___ipairs(display_list) do
		if display_info.__class == "Text" then
			local new_char_info = {}
			new_char_info.acc_width = 0
			new_char_info.pre_width = 0
			new_char_info.text_info = self:CopyTextInfo(display_info)
			new_char_info.text_object = nil
			new_char_info.text = display_info.text
			new_char_info.ctrl_info = nil
			new_char_info.ctrl = nil
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			last_text_info = new_char_info.text_info
		else
			if last_text_info == nil then
				last_text_info = self:InitTextInfo()
			end
			local new_char_info = {}
			new_char_info.acc_width = 0
			new_char_info.pre_width = 0
			new_char_info.text_info = last_text_info
			new_char_info.text_object = nil
			new_char_info.text = ""
			new_char_info.ctrl_info = display_info
			new_char_info.ctrl = nil
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
		end
	end
	return char_info_list
end

function ALittle.RichInput:CharInfoListToDisplayList(list)
	local display_list = {}
	local display_list_count = 0
	local text_info = nil
	local text_list = nil
	local text_list_count = 0
	for char_index, char_info in ___ipairs(list) do
		if char_info.ctrl_info == nil then
			if text_info == nil then
				text_info = char_info.text_info
				text_list = {}
				text_list_count = 1
				text_list[text_list_count] = char_info.text
			elseif text_info == char_info.text_info then
				text_list_count = text_list_count + 1
				text_list[text_list_count] = char_info.text
			else
				if self:CompareTextInfo(text_info, char_info.text_info) then
					text_list_count = text_list_count + 1
					text_list[text_list_count] = char_info.text
				else
					local text = ALittle.String_Join(text_list, "")
					if text ~= "" then
						local text_ctrl = ALittle.String_CopyTable(text_info)
						text_ctrl.__class = "Text"
						text_ctrl.text = text
						display_list_count = display_list_count + 1
						display_list[display_list_count] = text_ctrl
					end
					text_info = char_info.text_info
					text_list = {}
					text_list_count = 1
					text_list[text_list_count] = char_info.text
				end
			end
		else
			if text_info ~= nil then
				local text = ALittle.String_Join(text_list, "")
				if text ~= "" then
					local text_ctrl = ALittle.String_CopyTable(text_info)
					text_ctrl.__class = "Text"
					text_ctrl.text = text
					display_list_count = display_list_count + 1
					display_list[display_list_count] = text_ctrl
				end
				text_info = nil
				text_list = nil
				text_list_count = 0
			end
			display_list_count = display_list_count + 1
			display_list[display_list_count] = ALittle.String_CopyTable(char_info.ctrl_info)
		end
	end
	if text_info ~= nil then
		local text = ALittle.String_Join(text_list, "")
		if text ~= "" then
			local text_ctrl = ALittle.String_CopyTable(text_info)
			text_ctrl.__class = "Text"
			text_ctrl.text = text
			display_list_count = display_list_count + 1
			display_list[display_list_count] = text_ctrl
		end
	end
	return display_list
end

function ALittle.RichInput:CharInfoListToWord(list)
	local text_list = {}
	local text_list_count = 0
	for char_index, char_info in ___ipairs(list) do
		if char_info.ctrl_info == nil then
			text_list_count = text_list_count + 1
			text_list[text_list_count] = char_info.text
		end
	end
	return ALittle.String_Join(text_list, "")
end

function ALittle.RichInput:UpdateFontText()
	local char_info = self._char_info_list[self._char_cursor_it]
	local is_change = false
	local font_text = self._font_text
	local text_info = char_info.text_info
	if font_text.font_path ~= text_info.font_path then
		font_text.font_path = text_info.font_path
		is_change = true
	end
	if font_text.font_size ~= text_info.font_size then
		font_text.font_size = text_info.font_size
		is_change = true
	end
	if font_text.red ~= text_info.red then
		font_text.red = text_info.red
		is_change = true
	end
	if font_text.green ~= text_info.green then
		font_text.green = text_info.green
		is_change = true
	end
	if font_text.blue ~= text_info.blue then
		font_text.blue = text_info.blue
		is_change = true
	end
	if font_text.bold ~= text_info.bold then
		font_text.bold = text_info.bold
		is_change = true
	end
	if font_text.italic ~= text_info.italic then
		font_text.italic = text_info.italic
		is_change = true
	end
	if font_text.underline ~= text_info.underline then
		font_text.underline = text_info.underline
		is_change = true
	end
	if font_text.deleteline ~= text_info.deleteline then
		font_text.deleteline = text_info.deleteline
		is_change = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[-256576702], {})
	end
end

function ALittle.RichInput:GetCursorWidth(font_size)
	if font_size == nil or font_size < 15 then
		return 1
	end
	if font_size > 100 then
		return 10
	end
	return __floor((font_size / 100) * 10)
end

function ALittle.RichInput:Ctor(ctrl_sys)
	___rawset(self, "_char_info_list", {})
	___rawset(self, "_char_count", 0)
	___rawset(self, "_font_text", ALittle.Text(self._ctrl_sys))
	___rawset(self, "_draw_text", ALittle.Text(self._ctrl_sys))
	___rawset(self, "_char_cursor_it", 1)
	___rawset(self, "_char_select_it", 1)
	___rawset(self, "_display_view", ALittle.DisplayView(self._ctrl_sys))
	self._display_view.width_type = 4
	self._display_view.height_type = 4
	self._display_view.x_type = 3
	self._display_view.y_type = 3
	self:AddChild(self._display_view)
	___rawset(self, "_display_show", ALittle.DisplayLayout(self._ctrl_sys))
	self._display_show.width = 0
	self._display_show.height = 0
	self._display_show.x = 0
	self._display_show.y_type = 4
	self._display_show.y_value = 0
	self._display_view:AddChild(self._display_show)
	___rawset(self, "_current_flash_alpha", 1)
	___rawset(self, "_current_flash_dir", -0.05)
	___rawset(self, "_cursor", ALittle.Quad(self._ctrl_sys))
	self._cursor.width = 1
	self:AddChild(self._cursor)
	self._cursor.visible = false
	___rawset(self, "_select", ALittle.Quad(self._ctrl_sys))
	self:AddChild(self._select)
	self._select.visible = false
	self._select.alpha = 0.5
	___rawset(self, "_start_cursor", ALittle.Quad(self._ctrl_sys))
	self._start_cursor.width = 1
	self:AddChild(self._start_cursor)
	self._start_cursor.visible = false
	___rawset(self, "_end_cursor", ALittle.Quad(self._ctrl_sys))
	self._end_cursor.width = 1
	self:AddChild(self._end_cursor)
	self._end_cursor.visible = false
	___rawset(self, "_start_cursor_data", nil)
	___rawset(self, "_end_cursor_data", nil)
	___rawset(self, "_focus_cursor", true)
	___rawset(self, "_is_focus", false)
	___rawset(self, "_event_start_x", 0)
	___rawset(self, "_event_end_x", 0)
	___rawset(self, "_event_start_y", 0)
	___rawset(self, "_event_end_y", 0)
	___rawset(self, "_click_drag_delta_x", 0)
	___rawset(self, "_click_drag_delta_y", 0)
	___rawset(self, "_is_click", false)
	___rawset(self, "_is_longclick", false)
	___rawset(self, "_is_click_cursor", false)
	___rawset(self, "_is_click_cursor_name", "")
	___rawset(self, "_drag_delta_x", 0)
	___rawset(self, "_drag_delta_y", 0)
	___rawset(self, "_cursor_margin_up", 0)
	___rawset(self, "_cursor_margin_down", 0)
	___rawset(self, "_margin_halign", 0)
	___rawset(self, "_margin_valign", 0)
	___rawset(self, "_is_drag_begin", false)
	___rawset(self, "_password_mode", false)
	___rawset(self, "_ims_padding", 0)
	___rawset(self, "_default_text", ALittle.Text(self._ctrl_sys))
	self._default_text.y_type = 4
	self._default_text.y_value = 0
	self._display_view:AddChild(self._default_text)
	___rawset(self, "_default_font_height", 20)
	___rawset(self, "_link_map", ALittle.CreateValueWeakMap())
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", false)
	___rawset(self, "_pickup_this", true)
	___rawset(self, "_editable", true)
	___rawset(self, "_is_selecting", false)
	___rawset(self, "_can_drag_text", true)
	___rawset(self, "_auto_ims", true)
	___rawset(self, "_multi_cursor", false)
	___rawset(self, "_input_align", false)
	___rawset(self, "_regex", "")
	___rawset(self, "_limit_len", 0)
	self:AddEventListener(___all_struct[292776509], self, self.HandleFocusOut)
	self:AddEventListener(___all_struct[-644464135], self, self.HandleFocusIn)
	self:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[-1234078962], self, self.HandleTextInput)
	self:AddEventListener(___all_struct[-1604617962], self, self.HandleKeyDown)
	self:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self:AddEventListener(___all_struct[-439548260], self, self.HandleLongLButtonDown)
	self:ClearCharInfo()
	if self._loop == nil then
		___rawset(self, "_loop", ALittle.LoopFunction(Lua.Bind(self.Update, self), -1, 1, 1))
	end
	A_LoopSystem:AddUpdater(self._loop)
end

function ALittle.RichInput:GetCursor()
	return self._cursor
end

function ALittle.RichInput:ClearLinkMap()
	self._link_map = ALittle.CreateValueWeakMap()
end

function ALittle.RichInput.__getter:real_width()
	return self._char_info_list[self._char_count].acc_width
end

function ALittle.RichInput.__getter:real_height()
	return self._display_show.height
end

function ALittle.RichInput.__getter:can_drag_text()
	return self._can_drag_text
end

function ALittle.RichInput.__setter:can_drag_text(value)
	self._can_drag_text = value
end

function ALittle.RichInput.__setter:auto_ims(value)
	self._auto_ims = value
end

function ALittle.RichInput.__getter:auto_ims()
	return self._auto_ims
end

function ALittle.RichInput.__getter:multi_cursor()
	return self._multi_cursor
end

function ALittle.RichInput.__setter:width(value)
	if self.width == value then
		return
	end
	ALittle.DisplayLayout.__setter.width(self, value)
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput.__setter:height(value)
	if self.height == value then
		return
	end
	ALittle.DisplayLayout.__setter.height(self, value)
	self:ResetCursor()
end

function ALittle.RichInput.__setter:cursor_red(value)
	self._cursor.red = value
	self._select.red = value
end

function ALittle.RichInput.__getter:cursor_red()
	return self._cursor.red
end

function ALittle.RichInput.__setter:cursor_green(value)
	self._cursor.green = value
	self._select.green = value
end

function ALittle.RichInput.__getter:cursor_green()
	return self._cursor.green
end

function ALittle.RichInput.__setter:cursor_blue(value)
	self._cursor.blue = value
	self._select.blue = value
end

function ALittle.RichInput.__getter:cursor_blue()
	return self._cursor.blue
end

function ALittle.RichInput.__setter:font_bold(value)
	if self._font_text.bold == value then
		return
	end
	self._font_text.bold = value
	self._default_text.bold = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.bold = value
	end
end

function ALittle.RichInput.__setter:font_underline(value)
	if self._font_text.underline == value then
		return
	end
	self._font_text.underline = value
	self._default_text.underline = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.underline = value
	end
end

function ALittle.RichInput.__setter:font_deleteline(value)
	if self._font_text.deleteline == value then
		return
	end
	self._font_text.deleteline = value
	self._default_text.deleteline = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.deleteline = value
	end
end

function ALittle.RichInput.__setter:font_italic(value)
	if self._font_text.italic == value then
		return
	end
	self._font_text.italic = value
	self._default_text.italic = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.italic = value
	end
end

function ALittle.RichInput.__setter:font_path(value)
	if self._font_text.font_path == value then
		return
	end
	self._font_text.font_path = value
	self._default_text.font_path = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.font_path = value
	end
end

function ALittle.RichInput.__setter:font_size(value)
	if self._font_text.font_size == value then
		return
	end
	self._font_text.font_size = value
	self._default_text.font_size = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.font_size = value
	end
end

function ALittle.RichInput.__getter:font_path()
	return self._font_text.font_path
end

function ALittle.RichInput.__getter:font_size()
	return self._font_text.font_size
end

function ALittle.RichInput.__setter:font_red(value)
	if self._font_text.red == value then
		return
	end
	self._font_text.red = value
	self._default_text.red = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.red = value
	end
end

function ALittle.RichInput.__getter:font_red()
	return self._font_text.red
end

function ALittle.RichInput.__setter:font_green(value)
	if self._font_text.green == value then
		return
	end
	self._font_text.green = value
	self._default_text.green = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.green = value
	end
end

function ALittle.RichInput.__getter:font_green()
	return self._font_text.green
end

function ALittle.RichInput.__setter:font_blue(value)
	if self._font_text.blue == value then
		return
	end
	self._font_text.blue = value
	self._default_text.blue = value
	if self._char_info_list[1] ~= nil then
		self._char_info_list[1].text_info.blue = value
	end
end

function ALittle.RichInput.__getter:font_blue()
	return self._font_text.blue
end

function ALittle.RichInput.__setter:text(value)
	self:ClearCharInfo()
	self:InsertTextNative(value)
	self:ResetShowXByCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput.__getter:text()
	local displaylist = self:CharInfoListToDisplayList(self._char_info_list)
	local text = ""
	for k, v in ___ipairs(displaylist) do
		if v.__class == "Text" then
			text = text .. v.text
		end
	end
	return text
end

function ALittle.RichInput.__setter:default_text(value)
	self._default_text.text = value
end

function ALittle.RichInput.__getter:default_text()
	return self._default_text.text
end

function ALittle.RichInput.__setter:default_text_alpha(value)
	self._default_text.alpha = value
end

function ALittle.RichInput.__getter:default_text_alpha()
	return self._default_text.alpha
end

function ALittle.RichInput.__setter:display_list(value)
	local char_info_list = self:DisplayListToCharInfoList(value)
	self:ClearCharInfo()
	self:InsertCharInfo(char_info_list, false)
	self:ResetCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput.__getter:display_list()
	return self:CharInfoListToDisplayList(self._char_info_list)
end

function ALittle.RichInput.__setter:start_cursor(value)
	if value == nil then
		return
	end
	if value == self._start_cursor then
		return
	end
	self:RemoveChild(self._start_cursor)
	value.x_type = 1
	value.y_type = 1
	value.width_type = 1
	value.height_type = 1
	self._start_cursor = value
	self:AddChild(self._start_cursor)
	self._start_cursor.visible = false
	self:ResetCursor()
end

function ALittle.RichInput.__getter:start_cursor()
	return self._start_cursor
end

function ALittle.RichInput.__setter:end_cursor(value)
	if value == nil then
		return
	end
	if value == self._end_cursor then
		return
	end
	self:RemoveChild(self._end_cursor)
	value.x_type = 1
	value.y_type = 1
	value.width_type = 1
	value.height_type = 1
	self._end_cursor = value
	self:AddChild(self._end_cursor)
	self._end_cursor.visible = false
	self:ResetCursor()
end

function ALittle.RichInput.__getter:end_cursor()
	return self._end_cursor
end

function ALittle.RichInput.__setter:cursor_margin_up(value)
	if value == self._cursor_margin_up then
		return
	end
	self._cursor_margin_up = value
	self:ResetCursor()
end

function ALittle.RichInput.__getter:cursor_margin_up()
	return self._cursor_margin_up
end

function ALittle.RichInput.__setter:cursor_margin_down(value)
	if value == self._cursor_margin_down then
		return
	end
	self._cursor_margin_down = value
	self:ResetCursor()
end

function ALittle.RichInput.__getter:cursor_margin_down()
	return self._cursor_margin_down
end

function ALittle.RichInput.__setter:margin_halign(value)
	if value == self._margin_halign then
		return
	end
	self._margin_halign = value
	self._display_view.width_value = self._margin_halign * 2
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput.__getter:margin_halign()
	return self._margin_halign
end

function ALittle.RichInput.__setter:margin_valign(value)
	if value == self._margin_valign then
		return
	end
	self._margin_valign = value
	self._display_view.height_value = self._margin_valign * 2
	self:ResetCursor()
end

function ALittle.RichInput.__getter:margin_valign()
	return self._margin_valign
end

function ALittle.RichInput.__setter:focus_cursor(value)
	self._focus_cursor = value
end

function ALittle.RichInput.__getter:focus_cursor()
	return self._focus_cursor
end

function ALittle.RichInput.__getter:cursor_x()
	return self._cursor.x
end

function ALittle.RichInput.__getter:cursor_y()
	return self._cursor.y
end

function ALittle.RichInput.__getter:cursor_b()
	return (self._cursor.y + self._cursor.height) * self.scale_y + self._ims_padding
end

function ALittle.RichInput.__getter:start_cursor_x()
	return self._event_start_x
end

function ALittle.RichInput.__getter:start_cursor_y()
	return self._event_start_y
end

function ALittle.RichInput.__getter:end_cursor_x()
	return self._event_end_x
end

function ALittle.RichInput.__getter:end_cursor_y()
	return self._event_end_y
end

function ALittle.RichInput.__getter:is_input()
	return true
end

function ALittle.RichInput.__getter:is_empty()
	return self._char_count == 1
end

function ALittle.RichInput.__getter:editable()
	return self._editable
end

function ALittle.RichInput.__setter:editable(value)
	self._editable = value
end

function ALittle.RichInput.__setter:ims_padding(value)
	self._ims_padding = value
end

function ALittle.RichInput.__getter:ims_padding()
	return self._ims_padding
end

function ALittle.RichInput.__setter:password_mode(value)
	if self._password_mode == value then
		return
	end
	self._password_mode = value
	local display_list = self:CharInfoListToDisplayList(self._char_info_list)
	local char_info_list = self:DisplayListToCharInfoList(display_list)
	self:ClearCharInfo()
	self:InsertCharInfo(char_info_list, false)
	self:ResetCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput.__getter:password_mode()
	return self._password_mode
end

function ALittle.RichInput.__getter:regex()
	return self._regex
end

function ALittle.RichInput.__setter:regex(value)
	if value == nil then
		value = ""
	end
	self._regex = value
end

function ALittle.RichInput.__getter:limit_len()
	return self._limit_len
end

function ALittle.RichInput.__setter:limit_len(value)
	if value == nil then
		value = 0
	end
	self._limit_len = value
end

function ALittle.RichInput.__setter:input_align(value)
	if self._input_align == value then
		return
	end
	self._input_align = value
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput.__getter:input_align()
	return self._input_align
end

function ALittle.RichInput:Update()
	if self._cursor.abs_visible then
		self._current_flash_alpha = self._current_flash_alpha + self._current_flash_dir
		if (self._current_flash_dir < 0 and self._current_flash_alpha < -0.05) or (self._current_flash_dir > 0 and self._current_flash_alpha > 1.5) then
			self._current_flash_dir = -self._current_flash_dir
		end
		self._cursor.alpha = self._current_flash_alpha
	end
end

function ALittle.RichInput:Draw()
	if self._draw_loop ~= nil then
		return
	end
	self._draw_loop = ALittle.LoopFunction(Lua.Bind(self.DrawImpl, self), 1, 0, 1)
	A_LoopSystem:AddUpdater(self._draw_loop)
end

function ALittle.RichInput:DrawImpl()
	self._display_show:RemoveAllChild()
	local real_height = 0.0
	local offset_x = 0.0
	local last_child = nil
	for k, char_info in ___ipairs(self._char_info_list) do
		local child = char_info.text_object
		if child == nil then
			child = char_info.ctrl
		end
		if child ~= nil and child ~= last_child then
			last_child = child
			child.x_type = 2
			child.x_value = offset_x
			child.y_type = 4
			child.y_value = 0
			self._display_show:AddChild(child)
			offset_x = offset_x + child.width
			if child.height > real_height then
				real_height = child.height
			end
		end
	end
	self._display_show.height_value = real_height
	self._draw_loop = nil
end

function ALittle.RichInput:ClearCharInfo()
	self._char_info_list = {}
	self._char_count = 0
	local char_info = {}
	char_info.acc_width = 0
	char_info.pre_width = 0
	char_info.text_info = self:InitTextInfo()
	char_info.text_object = nil
	char_info.text = ""
	char_info.password_text = ""
	char_info.ctrl_info = nil
	char_info.ctrl = nil
	self._char_count = self._char_count + 1
	self._char_info_list[self._char_count] = char_info
	self._char_cursor_it = 1
	self._char_select_it = 2
	self:Draw()
end

function ALittle.RichInput:InsertCharInfo(char_info_list, selected)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	if char_info_list[1] == nil then
		return
	end
	local char_cursor_it_tmp = self._char_cursor_it
	local x_char_info_list = {}
	local x_char_info_list_count = 0
	for index, char_info in ___ipairs(char_info_list) do
		if char_info.ctrl_info == nil then
			x_char_info_list_count = self:SplitText(char_info, x_char_info_list, x_char_info_list_count)
		else
			x_char_info_list_count = x_char_info_list_count + 1
			x_char_info_list[x_char_info_list_count] = char_info
		end
	end
	char_info_list = x_char_info_list
	local new_char_info_list = {}
	local new_char_count = 0
	local text_info = nil
	local text_object = nil
	local char_acc_width = 0.0
	local i = 1
	while true do
		if not(i <= char_cursor_it_tmp) then break end
		local char_info = self._char_info_list[i]
		if i ~= 1 and char_info.ctrl_info == nil then
			text_info = char_info.text_info
			text_object = char_info.text_object
		else
			text_info = nil
			text_object = nil
		end
		char_acc_width = char_info.acc_width
		new_char_count = new_char_count + 1
		new_char_info_list[new_char_count] = char_info
		i = i+(1)
	end
	local insert_count = 0
	for key, display_info in ___ipairs(char_info_list) do
		if display_info.ctrl_info == nil then
			local display_object = nil
			if text_info ~= nil and self:CompareTextInfo(display_info.text_info, text_info) then
				display_object = text_object
			else
				text_info = display_info.text_info
				local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
				self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info))
				text_object = self._ctrl_sys:CreateControl(name, self._link_map)
				self._ctrl_sys:UnRegisterInfo(name)
				display_object = text_object
			end
			self:SetDrawText(display_object)
			local object_text = ""
			local calc_text = display_info.text
			local password_width = nil
			while calc_text ~= "" do
				local byte_count = ALittle.String_GetByteCount(calc_text, 1)
				local real_text = __sub(calc_text, 1, byte_count)
				local password_text = "*"
				local text_width = 0.0
				calc_text = __sub(calc_text, byte_count + 1)
				if self._password_mode then
					if password_width == nil then
						password_width = self._draw_text.native_show:CalcTextWidth(password_text)
					end
					text_width = password_width
				else
					password_text = real_text
					text_width = self._draw_text.native_show:CalcTextWidth(real_text)
				end
				local char_info = {}
				char_info.pre_width = char_acc_width
				char_info.acc_width = char_info.pre_width + text_width
				char_info.text_info = display_info.text_info
				char_info.text_object = display_object
				char_info.text = real_text
				char_info.password_text = password_text
				char_info.ctrl_info = nil
				char_info.ctrl = nil
				object_text = object_text .. char_info.password_text
				char_acc_width = char_info.acc_width
				new_char_count = new_char_count + 1
				new_char_info_list[new_char_count] = char_info
				insert_count = insert_count + 1
			end
		elseif display_info.ctrl_info ~= nil then
			text_info = nil
			text_object = nil
			local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
			self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info))
			local display_object = self._ctrl_sys:CreateControl(name, self._link_map)
			self._ctrl_sys:UnRegisterInfo(name)
			local char_info = {}
			char_info.pre_width = char_acc_width
			char_info.acc_width = char_info.pre_width + display_object.width
			char_info.text_info = display_info.text_info
			char_info.text_object = nil
			char_info.text = nil
			char_info.password_text = nil
			char_info.ctrl_info = display_info.ctrl_info
			char_info.ctrl = display_object
			char_acc_width = char_info.acc_width
			new_char_count = new_char_count + 1
			new_char_info_list[new_char_count] = char_info
			insert_count = insert_count + 1
		end
	end
	local i = char_cursor_it_tmp + 1
	while true do
		if not(i <= self._char_count) then break end
		local char_info = self._char_info_list[i]
		if char_info.ctrl_info == nil and text_info ~= nil and self:CompareTextInfo(char_info.text_info, text_info) then
			char_info.text_object = text_object
		else
			text_info = nil
			text_object = nil
		end
		local width = char_info.acc_width - char_info.pre_width
		char_info.pre_width = char_acc_width
		char_info.acc_width = char_info.pre_width + width
		char_acc_width = char_info.acc_width
		new_char_count = new_char_count + 1
		new_char_info_list[new_char_count] = char_info
		i = i+(1)
	end
	local text = ""
	local object = nil
	for i, char_info in ___ipairs(new_char_info_list) do
		if object == nil then
			if char_info.text_object ~= nil then
				object = char_info.text_object
				text = char_info.password_text
			end
		else
			if char_info.text_object == nil then
				object.text = text
				object = nil
				text = ""
			elseif char_info.text_object ~= object then
				object.text = text
				object = char_info.text_object
				text = char_info.password_text
			else
				text = text .. char_info.password_text
			end
		end
	end
	if object ~= nil then
		object.text = text
	end
	self._char_info_list = new_char_info_list
	self._char_count = new_char_count
	self._char_cursor_it = char_cursor_it_tmp + insert_count
	if selected then
		self._char_select_it = char_cursor_it_tmp
	else
		self._char_select_it = self._char_count + 1
	end
	self:Draw()
end

function ALittle.RichInput:DeleteCharInfo(begin_char_it, end_char_it)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	local new_char_info_list = {}
	local new_char_count = 0
	local text_info = nil
	local text_object = nil
	local char_acc_width = 0.0
	local i = 1
	while true do
		if not(i <= begin_char_it) then break end
		local char_info = self._char_info_list[i]
		if i ~= 1 and char_info.ctrl_info == nil then
			text_info = char_info.text_info
			text_object = char_info.text_object
		end
		char_acc_width = char_info.acc_width
		new_char_count = new_char_count + 1
		new_char_info_list[new_char_count] = char_info
		i = i+(1)
	end
	local i = end_char_it + 1
	while true do
		if not(i <= self._char_count) then break end
		local char_info = self._char_info_list[i]
		if char_info.ctrl_info == nil and text_info ~= nil and self:CompareTextInfo(char_info.text_info, text_info) then
			char_info.text_object = text_object
		else
			text_info = nil
			text_object = nil
		end
		local width = char_info.acc_width - char_info.pre_width
		char_info.pre_width = char_acc_width
		char_info.acc_width = char_info.pre_width + width
		char_acc_width = char_info.acc_width
		new_char_count = new_char_count + 1
		new_char_info_list[new_char_count] = char_info
		i = i+(1)
	end
	local text = ""
	local object = nil
	for i, char_info in ___ipairs(new_char_info_list) do
		if object == nil then
			if char_info.text_object ~= nil then
				object = char_info.text_object
				text = char_info.password_text
			end
		else
			if char_info.text_object == nil then
				object.text = text
				object = nil
				text = ""
			elseif char_info.text_object ~= object then
				object.text = text
				object = char_info.text_object
				text = char_info.password_text
			else
				text = text .. char_info.password_text
			end
		end
	end
	if object ~= nil then
		object.text = text
	end
	self._char_info_list = new_char_info_list
	self._char_count = new_char_count
	self._char_cursor_it = begin_char_it
	self._char_select_it = self._char_count + 1
	self:Draw()
end

function ALittle.RichInput:GetIteratorByOffset(offset_x)
	local real_offset_x = offset_x - self._display_show.x
	if real_offset_x < 0 then
		return 1
	end
	local char_it = 1
	local char_end_it = self._char_count + 1
	while char_it ~= char_end_it do
		local char_info = self._char_info_list[char_it]
		if real_offset_x <= char_info.acc_width then
			local half_char_width = (char_info.acc_width - char_info.pre_width) * 0.5
			if real_offset_x - char_info.pre_width < half_char_width and char_it ~= 1 then
				char_it = char_it - 1
			end
			break
		else
			char_it = char_it + 1
		end
	end
	if char_it == char_end_it then
		char_end_it = char_end_it - 1
		char_it = char_end_it
	end
	return char_it
end

function ALittle.RichInput:ClickCursorToHome()
	self._char_select_it = self._char_count + 1
	self._char_cursor_it = 1
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:ClickCursorToEnd()
	self._char_select_it = self._char_count + 1
	self._char_cursor_it = self._char_count
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:ClickCursor(offset_x)
	self._char_select_it = self._char_count + 1
	self._char_cursor_it = self:GetIteratorByOffset(offset_x)
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:ClickMultiCursor(offset_x, trans)
	local char_cursor_it
	if trans then
		char_cursor_it = self._char_cursor_it
	else
		char_cursor_it = self:GetIteratorByOffset(offset_x)
	end
	if char_cursor_it ~= 1 then
		self._char_cursor_it = char_cursor_it
		self._char_select_it = char_cursor_it - 1
	else
		if self._char_count ~= 1 then
			self._char_cursor_it = char_cursor_it + 1
			self._char_select_it = char_cursor_it
		else
			self._char_cursor_it = 1
			self._char_select_it = 2
		end
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:ClickWordCursor(offset_x)
	self._char_cursor_it = self:GetIteratorByOffset(offset_x)
	self._char_select_it = self._char_cursor_it
	while true do
		local str = self._char_info_list[self._char_select_it].password_text
		if str ~= nil and __len(str) == 1 and str ~= "_" and self:CharIsNumber(str) == false and self:CharIsLetter(str) == false then
			break
		end
		if self._char_select_it == 1 then
			break
		end
		self._char_select_it = self._char_select_it - 1
	end
	while true do
		local str = self._char_info_list[self._char_cursor_it].password_text
		if str ~= nil and __len(str) == 1 and str ~= "_" and self:CharIsNumber(str) == false and self:CharIsLetter(str) == false then
			self._char_cursor_it = self._char_cursor_it - 1
			break
		end
		if self._char_cursor_it == self._char_count then
			break
		end
		self._char_cursor_it = self._char_cursor_it + 1
	end
	if self._char_select_it < 1 then
		self._char_select_it = self._char_count + 1
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
	return self._char_select_it <= self._char_count
end

function ALittle.RichInput:SelectAll()
	self._char_select_it = 1
	self._char_cursor_it = self._char_count
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:CursorOffsetLR(left)
	if self._char_select_it <= self._char_count and self._char_select_it ~= self._char_cursor_it then
		if self._char_cursor_it > self._char_select_it and left then
			self._char_cursor_it = self._char_select_it
		elseif self._char_cursor_it < self._char_select_it and not left then
			self._char_cursor_it = self._char_select_it
		end
		self._char_select_it = self._char_count + 1
		return
	end
	if left then
		if self._char_cursor_it == 1 then
			return
		end
		self._char_cursor_it = self._char_cursor_it - 1
	else
		if self._char_cursor_it == self._char_count then
			return
		end
		self._char_cursor_it = self._char_cursor_it + 1
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:SelectCursorOffsetLR(left)
	if self._char_select_it > self._char_count then
		self._char_select_it = self._char_cursor_it
	end
	if left then
		if self._char_cursor_it == 1 then
			return
		end
		self._char_cursor_it = self._char_cursor_it - 1
	else
		if self._char_cursor_it == self._char_count then
			return
		end
		self._char_cursor_it = self._char_cursor_it + 1
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:DragCursorBegin()
	self._char_select_it = self._char_cursor_it
end

function ALittle.RichInput:DragCursor(offset_x)
	self._char_cursor_it = self:GetIteratorByOffset(offset_x)
	if self._char_info_list[self._char_cursor_it].pre_width == -self._display_show.x and self._char_cursor_it ~= 1 and offset_x < 0 then
		self._char_cursor_it = self._char_cursor_it - 1
	end
	if self._char_info_list[self._char_cursor_it].acc_width == self._display_view.width - self._display_show.x and self._char_cursor_it ~= self._char_count and offset_x > self._display_view.width then
		self._char_cursor_it = self._char_cursor_it - 1
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:DragMultiCursor(offset_x)
	offset_x = offset_x + self._drag_delta_x
	self._char_cursor_it = self:GetIteratorByOffset(offset_x)
	if self._char_info_list[self._char_cursor_it].pre_width == -self._display_show.x and self._char_cursor_it ~= 1 and offset_x < 0 then
		self._char_cursor_it = self._char_cursor_it - 1
	end
	if self._char_info_list[self._char_cursor_it].acc_width == self._display_view.width - self._display_show.x and self._char_cursor_it ~= self._char_count and offset_x > self._display_view.width then
		self._char_cursor_it = self._char_cursor_it - 1
	end
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:DragInput(delta_x)
	local display_show_x = self._display_show.x + delta_x
	local display_show_width = self._char_info_list[self._char_count].acc_width
	if self._display_show.width < self._display_view.width or display_show_x > 0 then
		display_show_x = 0
	elseif display_show_x < self._display_view.width - display_show_width then
		display_show_x = self._display_view.width - display_show_width
	end
	self._display_show.x = display_show_x
	self:ResetCursor()
end

function ALittle.RichInput:ResetShowXByCursor()
	local char_info = self._char_info_list[self._char_cursor_it]
	local next_char_info = self._char_info_list[self._char_cursor_it + 1]
	local max_char_info = self._char_info_list[self._char_count]
	if next_char_info == nil then
		next_char_info = char_info
	end
	local display_show_x = 0.0
	if char_info.pre_width < -self._display_show.x then
		self._display_show.x = -char_info.pre_width
	elseif next_char_info.acc_width > self._display_view.width - self._display_show.x then
		self._display_show.x = self._display_view.width - next_char_info.acc_width
	elseif max_char_info.acc_width + self._display_show.x < self._display_view.width and self._display_show.x < 0 then
		local display_x = self._display_view.width - max_char_info.acc_width
		if display_x > 0 then
			display_x = 0
		end
		self._display_show.x = display_x
	elseif self._input_align and max_char_info.acc_width < self._display_view.width then
		self._display_show.x = self._display_view.width - max_char_info.acc_width
	end
end

function ALittle.RichInput:ResetCursor()
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	local max_height = self._display_show.height
	if max_height > self._display_view.height then
		max_height = self._display_view.height
	end
	if self._char_select_it > self._char_count or self._char_select_it == self._char_cursor_it then
		self._select.visible = false
		self._start_cursor.visible = false
		self._end_cursor.visible = false
		self._start_cursor_data = nil
		self._end_cursor_data = nil
		self._event_start_x = 0
		self._event_end_x = 0
		self._event_start_y = 0
		self._event_end_y = 0
		if self._focus_cursor then
			self._cursor.visible = self._is_focus
		else
			self._cursor.visible = true
		end
		local cursor_x = self._display_view.x + self._char_info_list[self._char_cursor_it].acc_width + self._display_show.x
		if cursor_x < self._display_view.x or cursor_x > self._display_view.x + self._display_view.width then
			self._cursor.visible = false
		end
		local cursor_height = 0.0
		local cursor_width = 0.0
		local char = self._char_info_list[self._char_cursor_it]
		if char.ctrl ~= nil then
			cursor_height = char.ctrl.height
			cursor_width = 2
		else
			if char.text_object ~= nil then
				cursor_height = char.text_object.height
				cursor_width = self:GetCursorWidth(char.text_object.font_size)
			else
				local next_char = self._char_info_list[self._char_cursor_it + 1]
				if next_char ~= nil then
					if next_char.ctrl ~= nil then
						cursor_height = next_char.ctrl.height
						cursor_width = 2
					elseif next_char.text_object ~= nil then
						cursor_height = next_char.text_object.height
						cursor_width = self:GetCursorWidth(next_char.text_object.font_size)
					else
						cursor_height = self._font_text.native_show:GetFontHeight()
						cursor_width = self:GetCursorWidth(self._font_text.font_size)
					end
				else
					cursor_height = self._font_text.native_show:GetFontHeight()
					cursor_width = self:GetCursorWidth(self._font_text.font_size)
				end
			end
		end
		if cursor_height > max_height then
			cursor_height = max_height
		end
		if cursor_height == 0 then
			cursor_height = self._default_text.font_height
			if cursor_height == 0 then
				cursor_height = self._default_font_height
			end
		end
		self._cursor.width = cursor_width
		self._cursor.height = cursor_height
		self._cursor.x = cursor_x
		self._cursor.y = self._margin_valign + (self._display_view.height - cursor_height)
		return
	end
	if self._multi_cursor == false then
		self._cursor.visible = false
	end
	self._select.visible = true
	local select_x = self._display_view.x + self._char_info_list[self._char_select_it].acc_width + self._display_show.x
	local cursor_x = self._display_view.x + self._char_info_list[self._char_cursor_it].acc_width + self._display_show.x
	if self._char_cursor_it > self._char_select_it then
		if cursor_x < self._display_view.x then
			self._select.visible = false
		end
		if select_x > self._display_view.x + self._display_view.width then
			self._select.visible = false
		end
		local select_x_1 = select_x
		local cursor_x_1 = cursor_x
		if select_x_1 < self._display_view.x then
			select_x_1 = self._display_view.x
		end
		if cursor_x_1 > self._display_view.x + self._display_view.width then
			cursor_x_1 = self._display_view.x + self._display_view.width
		end
		self._select.y = self._margin_valign + (self._display_view.height - max_height)
		self._select.height = max_height
		self._select.x = select_x_1
		self._select.width = cursor_x_1 - select_x_1
		if self._multi_cursor == true then
			self._cursor.visible = false
			if select_x < self._display_view.x or select_x > self._display_view.x + self._display_view.width then
				self._start_cursor.visible = false
			else
				self._start_cursor.visible = true
				self._start_cursor.x = select_x - self._start_cursor.width
				self._start_cursor.height = self._select.height + self._cursor_margin_up + self._cursor_margin_down
				self._start_cursor.y = self._select.y - self._cursor_margin_up
			end
			if cursor_x > self._display_view.x + self._display_view.width or cursor_x < self._display_view.x then
				self._end_cursor.visible = false
			else
				self._end_cursor.visible = true
				self._end_cursor.x = cursor_x
				self._end_cursor.height = self._select.height + self._cursor_margin_up + self._cursor_margin_down
				self._end_cursor.y = self._select.y - self._cursor_margin_up
			end
			self._start_cursor_data = "select"
			self._end_cursor_data = "cursor"
			self._event_start_x = self._select.x
			self._event_start_y = self._select.y
			self._event_end_x = self._select.x + self._select.width
			self._event_end_y = self._select.y
		end
	elseif self._char_cursor_it < self._char_select_it then
		if select_x < self._display_view.x then
			self._select.visible = false
		end
		if cursor_x > self._display_view.x + self._display_view.width then
			self._select.visible = false
		end
		local select_x_1 = select_x
		local cursor_x_1 = cursor_x
		if cursor_x_1 < self._display_view.x then
			cursor_x_1 = self._display_view.x
		end
		if select_x_1 > self._display_view.x + self._display_view.width then
			select_x_1 = self._display_view.x + self._display_view.width
		end
		self._select.y = self._margin_valign + (self._display_view.height - max_height)
		self._select.height = max_height
		self._select.x = cursor_x_1
		self._select.width = select_x_1 - cursor_x_1
		if self._multi_cursor == true then
			self._cursor.visible = false
			if cursor_x < self._display_view.x or cursor_x > self._display_view.x + self._display_view.width then
				self._start_cursor.visible = false
			else
				self._start_cursor.visible = true
				self._start_cursor.x = cursor_x - self._start_cursor.width
				self._start_cursor.height = self._select.height + self._cursor_margin_up + self._cursor_margin_down
				self._start_cursor.y = self._select.y - self._cursor_margin_up
			end
			if select_x > self._display_view.x + self._display_view.width or select_x < self._display_view.x then
				self._end_cursor.visible = false
			else
				self._end_cursor.visible = true
				self._end_cursor.x = select_x
				self._end_cursor.height = self._select.height + self._cursor_margin_up + self._cursor_margin_down
				self._end_cursor.y = self._select.y - self._cursor_margin_up
			end
			self._start_cursor_data = "cursor"
			self._end_cursor_data = "select"
			self._event_start_x = self._select.x
			self._event_start_y = self._select.y
			self._event_end_x = self._select.x + self._select.width
			self._event_end_y = self._select.y
		end
	end
end

function ALittle.RichInput:ShowDefaultText()
	if self._is_focus == false then
		if self._focus_cursor and self.is_empty then
			self._default_text.visible = true
		else
			self._default_text.visible = false
		end
	else
		self._default_text.visible = false
	end
end

function ALittle.RichInput:DeleteSelectText()
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self._char_select_it > self._char_count then
		return false
	end
	if self._char_select_it == self._char_cursor_it then
		return false
	end
	local begin_char_it
	local end_char_it
	if self._char_select_it > self._char_cursor_it then
		begin_char_it = self._char_cursor_it
		end_char_it = self._char_select_it
	else
		end_char_it = self._char_cursor_it
		begin_char_it = self._char_select_it
	end
	self:DeleteCharInfo(begin_char_it, end_char_it)
	self:ResetCursor()
	return true
end

function ALittle.RichInput:CheckDisplayListRegexLimit(display_list)
	if self._regex == "" then
		return false
	end
	local text = ""
	for k, v in ___ipairs(display_list) do
		if v.__class ~= "Text" then
			return false
		end
		text = text .. v.text
	end
	return self:CheckTextRegexLimit(text)
end

function ALittle.RichInput:InsertDisplayListNative(display_list, selected)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:CheckDisplayListRegexLimit(display_list) == false then
		return false
	end
	self:DeleteSelectText()
	local char_info = self._char_info_list[self._char_cursor_it]
	local char_info_list = self:DisplayListToCharInfoList(display_list, char_info.text_info)
	self:InsertCharInfo(char_info_list, selected)
	return true
end

function ALittle.RichInput:CheckTextRegexLimit(text)
	if self._limit_len > 0 then
		local text_len = ALittle.String_GetWordCount(text)
		if text_len > self._limit_len then
			return false
		end
		local select_len = 0
		local displaylist = self:GetSelectText()
		for k, v in ___ipairs(displaylist) do
			if v.__class == "Text" then
				select_len = select_len + ALittle.String_GetWordCount(v.text)
			end
		end
		displaylist = self.display_list
		local total_len = 0
		for k, v in ___ipairs(displaylist) do
			if v.__class == "Text" then
				total_len = total_len + ALittle.String_GetWordCount(v.text)
			end
		end
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

function ALittle.RichInput:InsertTextNative(text)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:CheckTextRegexLimit(text) == false then
		return false
	end
	self:DeleteSelectText()
	local char_info_list = {}
	local new_char_info = {}
	new_char_info.acc_width = 0
	new_char_info.pre_width = 0
	new_char_info.text_info = self:InitTextInfo()
	new_char_info.text_object = nil
	new_char_info.text = text
	new_char_info.ctrl_info = nil
	new_char_info.ctrl = nil
	char_info_list[1] = new_char_info
	self:InsertCharInfo(char_info_list, false)
	return true
end

function ALittle.RichInput:GetSelectText()
	local select_text = {}
	local select_text_count = 0
	if self._char_select_it > self._char_count then
		return {}
	end
	if self._char_select_it == self._char_cursor_it then
		return {}
	end
	local char_it
	local char_end
	if self._char_select_it > self._char_cursor_it then
		char_it = self._char_cursor_it + 1
		char_end = self._char_select_it
	else
		char_end = self._char_cursor_it
		char_it = self._char_select_it + 1
	end
	while char_it <= char_end do
		select_text_count = select_text_count + 1
		select_text[select_text_count] = self._char_info_list[char_it]
		char_it = char_it + 1
	end
	return self:CharInfoListToDisplayList(select_text)
end

function ALittle.RichInput:GetSelectWord()
	local select_text = {}
	local select_text_count = 0
	if self._char_select_it > self._char_count then
		return ""
	end
	if self._char_select_it == self._char_cursor_it then
		return ""
	end
	local char_it
	local char_end
	if self._char_select_it > self._char_cursor_it then
		char_it = self._char_cursor_it + 1
		char_end = self._char_select_it
	else
		char_end = self._char_cursor_it
		char_it = self._char_select_it + 1
	end
	while char_it <= char_end do
		select_text_count = select_text_count + 1
		select_text[select_text_count] = self._char_info_list[char_it]
		char_it = char_it + 1
	end
	return self:CharInfoListToWord(select_text)
end

function ALittle.RichInput:DeleteText(left)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:DeleteSelectText() then
		return true
	end
	if left then
		if self._char_cursor_it == 1 then
			return false
		end
		local end_it = self._char_cursor_it
		local begin_it = self._char_cursor_it - 1
		self:DeleteCharInfo(begin_it, end_it)
	else
		if self._char_cursor_it == self._char_count then
			return false
		end
		local begin_it = self._char_cursor_it
		local end_it = self._char_cursor_it + 1
		self:DeleteCharInfo(begin_it, end_it)
	end
	return true
end

function ALittle.RichInput:SetCursor(rel_x, rel_y)
	if self._auto_ims then
		self:OpenIME()
	end
	self._is_selecting = false
	if self._multi_cursor then
		self._multi_cursor = false
		self._start_cursor.visible = false
		self._end_cursor.visible = false
		self._cursor.visible = true
		self:ClickCursor(rel_x - self._display_view.x)
	else
		self:ClickCursor(rel_x - self._display_view.x)
	end
end

function ALittle.RichInput:SetMultiCursor(rel_x, rel_y)
	if self._auto_ims then
		self:OpenIME()
	end
	self._is_selecting = true
	if self._multi_cursor == false then
		self._multi_cursor = true
		self._cursor.visible = false
		self._start_cursor.visible = true
		self._end_cursor.visible = true
		self:ClickMultiCursor(rel_x - self._display_view.x, false)
	else
		self:ClickMultiCursor(rel_x - self._display_view.x, false)
	end
end

function ALittle.RichInput:TransToCursor()
	if self._end_cursor_data == "select" then
		self._char_cursor_it = self._char_select_it
	end
	self._char_select_it = self._char_count + 1
	self._is_selecting = false
	self._multi_cursor = false
	self._start_cursor.visible = false
	self._end_cursor.visible = false
	self._cursor.visible = true
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
end

function ALittle.RichInput:TransToMulti()
	if self._multi_cursor then
		return
	end
	self._is_selecting = true
	self._multi_cursor = true
	self._cursor.visible = false
	self._start_cursor.visible = true
	self._end_cursor.visible = true
	self:ClickMultiCursor(nil, true)
end

function ALittle.RichInput:OpenIME(x, y, width, height)
	if self._editable then
		if x ~= nil and y ~= nil and width ~= nil and height ~= nil then
			ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height))
		else
			local global_x, global_y = self:LocalToGlobal()
			global_x = global_x + self.cursor_x
			global_y = global_y + (self.cursor_y + self.font_size) * self.scale_y
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + self._ims_padding))
		end
		ALittle.System_OpenIME()
		self:ResetCursor()
	end
end

function ALittle.RichInput:CloseIME()
	ALittle.System_CloseIME()
end

function ALittle.RichInput:InsertText(display_list, selected)
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self:InsertDisplayListNative(display_list, selected)
	self._is_selecting = false
	self._multi_cursor = false
	self:UpdateFontText()
	self:ResetShowXByCursor()
	self:ResetCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput:InsertWord(word_text)
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self:InsertTextNative(word_text)
	self._is_selecting = false
	self:TransToCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput:CopyText(return_cursor)
	if self._password_mode then
		return
	end
	local select_text = self:GetSelectText()
	if select_text[1] ~= nil then
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
	end
	if return_cursor then
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:CopyWord(return_cursor)
	if self._password_mode then
		return
	end
	local select_text = self:GetSelectWord()
	if select_text ~= nil then
		ALittle.System_SetClipboardText(select_text)
	end
	if return_cursor then
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:CutText()
	if self._password_mode then
		return
	end
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	local select_text = self:GetSelectText()
	if select_text[1] ~= nil then
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
		self:DeleteSelectText()
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:CutWord()
	if self._password_mode then
		return
	end
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	local select_text = self:GetSelectWord()
	if select_text ~= nil then
		ALittle.System_SetClipboardText(select_text)
		self:DeleteSelectText()
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:PasteText()
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	if ALittle.System_HasClipboardText() then
		local content = ALittle.System_GetClipboardText()
		local error, new_content = Lua.TCall(ALittle.String_JsonDecode, content)
		if error == nil and __type(new_content) == "table" and self:CheckDisplayList(new_content) then
			if self:CheckAtKeyInput(new_content) then
				return
			end
			self:InsertDisplayListNative(new_content, false)
		else
			if self:CheckAtKeyInput(content) then
				return
			end
			self:InsertTextNative(content)
		end
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:PasteWord()
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	if ALittle.System_HasClipboardText() then
		local content = ALittle.System_GetClipboardText()
		self:InsertTextNative(content)
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:Clear()
	self:ClearCharInfo()
	self:ShowDefaultText()
end

function ALittle.RichInput:Delete()
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	self:DeleteText(true)
	self:TransToCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput:GetWord()
	return self:CharInfoListToWord(self._char_info_list)
end

function ALittle.RichInput:HandleFocusOut(event)
	if self._auto_ims then
		ALittle.System_CloseIME()
	end
	self._is_focus = false
	if self._focus_cursor then
		if self._multi_cursor == false then
			self._cursor.visible = false
		end
	end
	self:ShowDefaultText()
end

function ALittle.RichInput:HandleFocusIn(event)
	if self._auto_ims then
		self:OpenIME()
	end
	self._is_focus = true
	self:ResetShowXByCursor()
	self:ResetCursor()
	self:ShowDefaultText()
end

function ALittle.RichInput:HandleMoveIn(event)
	ALittle.System_SetEditCursor()
end

function ALittle.RichInput:HandleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function ALittle.RichInput:HandleLButtonDown(event)
	if self._multi_cursor == false then
		self._is_longclick = false
		if event.rel_x > self._display_view.x and event.rel_x <= self._display_view.x + self._display_view.width and event.rel_y >= self._display_view.y and event.rel_y <= self._display_view.y + self._display_view.height then
			if event.count % 3 == 1 then
				self._is_selecting = false
				self:ClickCursor(event.rel_x - self._display_view.x)
				self:DispatchEvent(___all_struct[-683607428], {})
			elseif event.count % 3 == 2 then
				self._is_selecting = self:ClickWordCursor(event.rel_x - self._display_view.x)
			else
				self._is_selecting = true
				self:SelectAll()
			end
			self._is_click = true
		else
			self._is_click = false
		end
	else
		self._click_drag_delta_x = 0
		self._click_drag_delta_y = 0
		self._is_click = false
		self._is_click_cursor = false
		self._is_click_cursor_name = ""
		self._is_longclick = false
		if self._start_cursor.visible and event.rel_x >= self._start_cursor.x and event.rel_x <= self._start_cursor.x + self._start_cursor.width and event.rel_y >= self._start_cursor.y and event.rel_y <= self._start_cursor.y + self._start_cursor.height then
			self._is_click_cursor = true
			self._is_click_cursor_name = "start"
		elseif self._end_cursor.visible and event.rel_x >= self._end_cursor.x and event.rel_x <= self._end_cursor.x + self._end_cursor.width and event.rel_y >= self._end_cursor.y and event.rel_y <= self._end_cursor.y + self._end_cursor.height then
			self._is_click_cursor = true
			self._is_click_cursor_name = "end"
		else
			if event.rel_x >= self._display_view.x and event.rel_x <= self._display_view.x + self._display_view.width and event.rel_y >= self._display_view.y and event.rel_y <= self._display_view.y + self._display_view.height then
				self._is_click = true
			end
		end
	end
end

function ALittle.RichInput:HandleLButtonUp(event)
	if self._multi_cursor == true then
		if self._is_click and self._is_longclick == false and self._click_drag_delta_x < 2 and self._click_drag_delta_y < 2 then
			self._multi_cursor = false
			self._start_cursor.visible = false
			self._end_cursor.visible = false
			self._cursor.visible = true
			self:ClickCursor(event.rel_x - self._display_view.x)
			self:DispatchEvent(___all_struct[-683607428], {})
		end
	end
end

function ALittle.RichInput:CheckAtKeyInput(input_text)
	if input_text ~= "@" then
		return false
	end
	local char_cursor_it = self._char_cursor_it
	if self._char_cursor_it == 1 then
		self:DispatchEvent(___all_struct[1816229739], {})
		return true
	end
	local char_info = self._char_info_list[self._char_cursor_it]
	local forward_text = char_info.text
	if not (self:CharIsNumber(forward_text) or self:CharIsLetter(forward_text)) then
		self:DispatchEvent(___all_struct[1816229739], {})
		return true
	end
	return false
end

function ALittle.RichInput:HandleTextInput(event)
	local is_change = false
	if self._multi_cursor == false then
		if (self._editable or event.custom) then
			if self:CheckAtKeyInput(event.text) then
				return
			end
			self._is_selecting = false
			is_change = self:InsertTextNative(event.text)
		end
	else
		if self._is_selecting and self._editable then
			self._is_selecting = false
			is_change = self:InsertTextNative(event.text)
			self._multi_cursor = false
		end
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
		self:UpdateFontText()
		self:ResetShowXByCursor()
		self:ResetCursor()
		self:ShowDefaultText()
	end
end

function ALittle.RichInput:HandleKeyDown(event)
	local is_change = false
	if event.sym == 1073741904 then
		if self._multi_cursor == false then
			if event.mod & 0x0003 == 0 then
				self._is_selecting = false
				self:CursorOffsetLR(true)
			else
				self._is_selecting = true
				self:SelectCursorOffsetLR(true)
			end
		end
		event.handled = true
	elseif event.sym == 1073741903 then
		if self._multi_cursor == false then
			if event.mod & 0x0003 == 0 then
				self._is_selecting = false
				self:CursorOffsetLR(false)
			else
				self._is_selecting = true
				self:SelectCursorOffsetLR(false)
			end
		end
		event.handled = true
	elseif event.sym == 8 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:DeleteText(true)
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:DeleteText(true)
				self._multi_cursor = false
			end
		end
		event.handled = true
	elseif event.sym == 127 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:DeleteText(false)
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:DeleteText(false)
				self._multi_cursor = false
			end
		end
		event.handled = true
	elseif event.sym == 1073741898 then
		self._is_selecting = false
		self:ClickCursorToHome()
		event.handled = true
	elseif event.sym == 1073741901 then
		self._is_selecting = false
		self:ClickCursorToEnd()
		event.handled = true
	elseif event.sym == 13 or event.sym == 1073741912 then
		if self._editable or event.custom then
			self._is_selecting = false
			self:DispatchEvent(___all_struct[776398171], {})
			event.handled = true
		end
	elseif event.sym == 120 and event.mod & 0x00c0 ~= 0 then
		if self._multi_cursor == false then
			if (self._editable or event.custom) and not self._password_mode then
				self._is_selecting = false
				local select_text = self:GetSelectText()
				if select_text[1] ~= nil then
					ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
					is_change = self:DeleteSelectText()
				end
			end
		else
			if (self._is_selecting and self._editable) and not self._password_mode then
				self._is_selecting = false
				local select_text = self:GetSelectText()
				if select_text[1] ~= nil then
					ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
					is_change = self:DeleteSelectText()
				end
				self._multi_cursor = false
			end
		end
		event.handled = true
	elseif event.sym == 99 and event.mod & 0x00c0 ~= 0 then
		if not self._password_mode then
			local select_text = self:GetSelectText()
			if select_text[1] ~= nil then
				ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
			end
		end
		event.handled = true
	elseif event.sym == 118 and event.mod & 0x00c0 ~= 0 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				if ALittle.System_HasClipboardText() then
					local content = ALittle.System_GetClipboardText()
					local error, new_content = Lua.TCall(ALittle.String_JsonDecode, content)
					if error == nil and __type(new_content) == "table" and self:CheckDisplayList(new_content) then
						if self:CheckAtKeyInput(new_content) then
							return
						end
						is_change = self:InsertDisplayListNative(new_content, false)
					else
						if self:CheckAtKeyInput(content) then
							return
						end
						is_change = self:InsertTextNative(content)
					end
				end
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				if ALittle.System_HasClipboardText() then
					local content = ALittle.System_GetClipboardText()
					local error, new_content = Lua.TCall(ALittle.String_JsonDecode, content)
					if error == nil and __type(new_content) == "table" and self:CheckDisplayList(new_content) then
						is_change = self:InsertDisplayListNative(new_content, false)
					else
						is_change = self:InsertTextNative(content)
					end
				end
				self._multi_cursor = false
			end
		end
		event.handled = true
	elseif event.sym == 97 and event.mod & 0x00c0 ~= 0 then
		self._is_selecting = true
		self:SelectAll()
		event.handled = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
		self._current_flash_alpha = 1.5
		self:UpdateFontText()
		self:ResetShowXByCursor()
		self:ResetCursor()
		self:ShowDefaultText()
	end
end

function ALittle.RichInput:HandleDragBegin(event)
	if self._can_drag_text == false then
		return
	end
	if self._multi_cursor == false then
		if self._is_click then
			self._is_drag_begin = true
			self._is_selecting = true
			self:DragCursorBegin()
		else
			self._is_drag_begin = false
		end
	else
		if self._is_click_cursor then
			if (self._is_click_cursor_name == "start" and self._start_cursor_data == "select") or (self._is_click_cursor_name == "end" and self._end_cursor_data == "select") then
				local char_temp_it = self._char_select_it
				self._char_select_it = self._char_cursor_it
				self._char_cursor_it = char_temp_it
			end
			if self._is_click_cursor_name == "start" then
				self._drag_delta_x = self._start_cursor.x + self._start_cursor.width - event.rel_x
				self._drag_delta_y = self._start_cursor.y + self._cursor_margin_up + (self._start_cursor.height - self._cursor_margin_up - self._cursor_margin_down) / 2 - event.rel_y
			elseif self._is_click_cursor_name == "end" then
				self._drag_delta_x = self._end_cursor.x - event.rel_x
				self._drag_delta_y = self._end_cursor.y + self._cursor_margin_up + (self._end_cursor.height - self._cursor_margin_up - self._cursor_margin_down) / 2 - event.rel_y
			end
			self._is_drag_begin = true
			self:DispatchEvent(___all_struct[1424993548], {})
		elseif self._is_click then
			self._is_drag_begin = true
			self:DispatchEvent(___all_struct[1424993548], {})
		else
			self._is_drag_begin = false
		end
	end
end

function ALittle.RichInput:HandleDrag(event)
	if self._can_drag_text == false then
		return
	end
	if self._is_drag_begin == false then
		return
	end
	if self._multi_cursor == false then
		if self._is_selecting == false then
			return
		end
		self:DragCursor(event.rel_x - self._display_view.x)
	else
		if self._is_click_cursor then
			self:DragMultiCursor(event.rel_x - self._display_view.x)
		else
			self._click_drag_delta_x = self._click_drag_delta_x + __abs(event.delta_x)
			self._click_drag_delta_y = self._click_drag_delta_y + __abs(event.delta_y)
			self:DragInput(event.delta_x)
		end
		self:DispatchEvent(___all_struct[-605767802], {})
	end
end

function ALittle.RichInput:HandleDragEnd(event)
	if self._can_drag_text == false then
		return
	end
	if self._is_drag_begin == false then
		return
	end
	if self._multi_cursor then
		if self._cursor.visible then
			self._multi_cursor = false
		end
		self:DispatchEvent(___all_struct[-884368490], {})
	end
end

function ALittle.RichInput:HandleLongLButtonDown(event)
	if self._is_click then
		if self.editable == false then
			self._is_selecting = true
			if self._multi_cursor == false then
				self._multi_cursor = true
				self._cursor.visible = false
				self._start_cursor.visible = true
				self._end_cursor.visible = true
				self:ClickMultiCursor(event.rel_x - self._display_view.x, false)
			else
				self:ClickMultiCursor(event.rel_x - self._display_view.x, false)
			end
		else
			self._multi_cursor = false
			self._start_cursor.visible = false
			self._end_cursor.visible = false
			self._cursor.visible = true
			self:ClickCursor(event.rel_x - self._display_view.x)
		end
		local e = {}
		e.target = self
		e.abs_x = event.abs_x
		e.abs_y = event.abs_y
		e.rel_x = event.rel_x
		e.rel_y = event.rel_y
		self:DispatchEvent(___all_struct[1640499878], e)
		self._is_longclick = true
	end
end

end