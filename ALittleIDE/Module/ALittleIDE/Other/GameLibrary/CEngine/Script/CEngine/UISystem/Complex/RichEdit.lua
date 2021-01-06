-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1949279026, "ALittle.RichEditFontChangedEvent", {
name = "ALittle.RichEditFontChangedEvent", ns_name = "ALittle", rl_name = "RichEditFontChangedEvent", hash_code = 1949279026,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1053992999, "ALittle.RichEditCursorClickEvent", {
name = "ALittle.RichEditCursorClickEvent", ns_name = "ALittle", rl_name = "RichEditCursorClickEvent", hash_code = -1053992999,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-923963966, "ALittle.RichEditCharInfo", {
name = "ALittle.RichEditCharInfo", ns_name = "ALittle", rl_name = "RichEditCharInfo", hash_code = -923963966,
name_list = {"acc_width","pre_width","text_info","text_object","text","ctrl_info","ctrl"},
type_list = {"double","double","ALittle.DisplayInfo","ALittle.Text","string","ALittle.DisplayInfo","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(774620468, "ALittle.UIRichEditLongClickEvent", {
name = "ALittle.UIRichEditLongClickEvent", ns_name = "ALittle", rl_name = "UIRichEditLongClickEvent", hash_code = 774620468,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(556044369, "ALittle.RichEditLineInfo", {
name = "ALittle.RichEditLineInfo", ns_name = "ALittle", rl_name = "RichEditLineInfo", hash_code = 556044369,
name_list = {"char_list","char_count","child_list","child_count","container","acc_height","pre_height","force_line"},
type_list = {"List<ALittle.RichEditCharInfo>","int","List<ALittle.DisplayObject>","int","ALittle.DisplayLayout","double","double","bool"},
option_map = {}
})
ALittle.RegStruct(291295687, "ALittle.RichEditMultiDragEvent", {
name = "ALittle.RichEditMultiDragEvent", ns_name = "ALittle", rl_name = "RichEditMultiDragEvent", hash_code = 291295687,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-203792390, "ALittle.RichEditMultiDragEndEvent", {
name = "ALittle.RichEditMultiDragEndEvent", ns_name = "ALittle", rl_name = "RichEditMultiDragEndEvent", hash_code = -203792390,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(9565867, "ALittle.RichEditMultiDragBeginEvent", {
name = "ALittle.RichEditMultiDragBeginEvent", ns_name = "ALittle", rl_name = "RichEditMultiDragBeginEvent", hash_code = 9565867,
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
ALittle.RichEdit = Lua.Class(ALittle.DisplayLayout, "ALittle.RichEdit")

function ALittle.RichEdit:CharIsNumber(str)
	local c = __byte(str, 1)
	return c >= 48 and c <= 57
end

function ALittle.RichEdit:CharIsLetter(str)
	local c = __byte(str, 1)
	return c >= 65 and c <= 90 or c >= 97 and c <= 122
end

function ALittle.RichEdit:CompareTextInfo(a, b)
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

function ALittle.RichEdit:CopyTextInfo(b)
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

function ALittle.RichEdit:InitTextInfo()
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

function ALittle.RichEdit:SetDrawText(font_text)
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

function ALittle.RichEdit:UpdateFontText()
	local line_list = self._line_list
	local char_info = line_list[self._line_cursor_it].char_list[self._char_cursor_it]
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
		self:DispatchEvent(___all_struct[1949279026], {})
	end
end

function ALittle.RichEdit:CheckDisplayList(content)
	for k, v in ___ipairs(content) do
		if v.__class == nil then
			return false
		end
	end
	return true
end

function ALittle.RichEdit:DisplayListToCharInfoList(display_list, default_text_info)
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

function ALittle.RichEdit:GetCharInfoList()
	local char_info_list = {}
	local char_info_list_count = 0
	for line_index, line_info in ___ipairs(self._line_list) do
		for char_index, char_info in ___ipairs(line_info.char_list) do
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = char_info
		end
	end
	return char_info_list
end

function ALittle.RichEdit:JoinCharInfoList(char_info_list)
	local new_char_info_list = {}
	local new_char_info_list_count = 0
	local text_info = nil
	local text_list = nil
	local text_list_count = 0
	for char_index, char_info in ___ipairs(char_info_list) do
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
						local new_char_info = {}
						new_char_info.acc_width = 0
						new_char_info.pre_width = 0
						new_char_info.text_info = text_info
						new_char_info.text_object = nil
						new_char_info.text = text
						new_char_info.ctrl_info = nil
						new_char_info.ctrl = nil
						new_char_info_list_count = new_char_info_list_count + 1
						new_char_info_list[new_char_info_list_count] = new_char_info
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
					local new_char_info = {}
					new_char_info.acc_width = 0
					new_char_info.pre_width = 0
					new_char_info.text_info = text_info
					new_char_info.text_object = nil
					new_char_info.text = text
					new_char_info.ctrl_info = nil
					new_char_info.ctrl = nil
					new_char_info_list_count = new_char_info_list_count + 1
					new_char_info_list[new_char_info_list_count] = new_char_info
				end
				text_info = nil
				text_list = nil
				text_list_count = 0
			end
			local new_char_info = {}
			new_char_info.acc_width = 0
			new_char_info.pre_width = 0
			new_char_info.text_info = text_info
			new_char_info.text_object = nil
			new_char_info.text = nil
			new_char_info.ctrl_info = char_info.ctrl_info
			new_char_info.ctrl = char_info.ctrl
			new_char_info_list_count = new_char_info_list_count + 1
			new_char_info_list[new_char_info_list_count] = new_char_info
		end
	end
	if text_info ~= nil then
		local text = ALittle.String_Join(text_list, "")
		if text ~= "" then
			local new_char_info = {}
			new_char_info.acc_width = 0
			new_char_info.pre_width = 0
			new_char_info.text_info = text_info
			new_char_info.text_object = nil
			new_char_info.text = text
			new_char_info.ctrl_info = nil
			new_char_info.ctrl = nil
			new_char_info_list_count = new_char_info_list_count + 1
			new_char_info_list[new_char_info_list_count] = new_char_info
		end
	end
	return new_char_info_list
end

function ALittle.RichEdit:CharInfoListToDisplayList(list)
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

function ALittle.RichEdit:CharInfoListToWord(list)
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

function ALittle.RichEdit:SplitText(char_info, char_info_list, char_info_list_count)
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
			local new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = __sub(text, 1, start_index_1 - 1)
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = "\n"
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			text = __sub(text, start_index_1 + 1)
		elseif start_index_2 ~= nil then
			local new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = __sub(text, 1, start_index_2 - 1)
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = "\t"
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			text = __sub(text, start_index_2 + 1)
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

function ALittle.RichEdit:GetCursorWidth(font_size)
	if font_size == nil or font_size < 15 then
		return 1
	end
	if font_size > 100 then
		return 10
	end
	return __floor((font_size / 100) * 10)
end

function ALittle.RichEdit:Ctor(ctrl_sys)
	___rawset(self, "_enter_key_height", 20)
	___rawset(self, "_line_list", {})
	___rawset(self, "_line_count", 0)
	___rawset(self, "_font_text", ALittle.Text(self._ctrl_sys))
	___rawset(self, "_draw_text", ALittle.Text(self._ctrl_sys))
	___rawset(self, "_line_start_it", nil)
	___rawset(self, "_line_cursor_it", nil)
	___rawset(self, "_char_cursor_it", nil)
	___rawset(self, "_line_select_it", nil)
	___rawset(self, "_char_select_it", nil)
	___rawset(self, "_scroll_list", ALittle.ScrollList(self._ctrl_sys))
	self._scroll_list.right_scrollbar = ALittle.ScrollBar(self._ctrl_sys)
	self._scroll_list.width_type = 4
	self._scroll_list.height_type = 4
	self._scroll_list.x_type = 3
	self._scroll_list.y_type = 3
	self:AddChild(self._scroll_list)
	___rawset(self, "_current_flash_alpha", 1)
	___rawset(self, "_current_flash_dir", -0.05)
	___rawset(self, "_cursor", ALittle.Quad(self._ctrl_sys))
	self:AddChild(self._cursor)
	self._cursor.visible = false
	self._cursor.width = 1
	___rawset(self, "_select_1", ALittle.Quad(self._ctrl_sys))
	self:AddChild(self._select_1)
	self._select_1.visible = false
	self._select_1.alpha = 0.5
	___rawset(self, "_select_2", ALittle.Quad(self._ctrl_sys))
	self:AddChild(self._select_2)
	self._select_2.visible = false
	self._select_2.alpha = 0.5
	___rawset(self, "_select_3", ALittle.Quad(self._ctrl_sys))
	self:AddChild(self._select_3)
	self._select_3.visible = false
	self._select_3.alpha = 0.5
	___rawset(self, "_start_cursor", ALittle.Quad(self._ctrl_sys))
	self._start_cursor.width = 1
	___rawset(self, "_end_cursor", ALittle.Quad(self._ctrl_sys))
	self._end_cursor.width = 1
	___rawset(self, "_start_cursor_data", nil)
	___rawset(self, "_end_cursor_data", nil)
	___rawset(self, "_focus_cursor", true)
	___rawset(self, "_is_focus", false)
	___rawset(self, "_event_start_x", 0)
	___rawset(self, "_event_end_x", 0)
	___rawset(self, "_event_start_y", 0)
	___rawset(self, "_event_end_y", 0)
	___rawset(self, "_start_it_delta", 0)
	___rawset(self, "_click_drag_delta_x", 0)
	___rawset(self, "_click_drag_delta_y", 0)
	___rawset(self, "_is_click", false)
	___rawset(self, "_is_longclick", false)
	___rawset(self, "_is_click_cursor", false)
	___rawset(self, "_is_click_cursor_name", "")
	___rawset(self, "_drag_delta_x", 0)
	___rawset(self, "_drag_delta_y", 0)
	self:AddChild(self._start_cursor)
	self:AddChild(self._end_cursor)
	self._start_cursor.visible = false
	self._end_cursor.visible = false
	___rawset(self, "_cursor_margin_up", 0)
	___rawset(self, "_cursor_margin_down", 0)
	___rawset(self, "_margin_halign", 0)
	___rawset(self, "_margin_valign", 0)
	___rawset(self, "_line_spacing", 0)
	___rawset(self, "_is_drag_begin", false)
	___rawset(self, "_ims_padding", 0)
	___rawset(self, "_default_text_area", ALittle.TextArea(self._ctrl_sys))
	self._default_text_area.width_type = 4
	self._default_text_area.height = 0
	self._default_text_area.x_type = 3
	self._default_text_area.y = 0
	self:AddChild(self._default_text_area)
	___rawset(self, "_link_map", ALittle.CreateValueWeakMap())
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", false)
	___rawset(self, "_pickup_this", true)
	___rawset(self, "_editable", true)
	___rawset(self, "_is_selecting", false)
	___rawset(self, "_can_drag_text", true)
	___rawset(self, "_auto_ims", true)
	___rawset(self, "_multi_cursor", false)
	___rawset(self, "_can_scroll", true)
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
	self:AddEventListener(___all_struct[-1737121315], self, self.HandleMButtonWheel)
	self:AddEventListener(___all_struct[-439548260], self, self.HandleLongLButtonDown)
	self:ClearText()
	if self._loop == nil then
		___rawset(self, "_loop", ALittle.LoopFunction(Lua.Bind(self.Update, self), -1, 1, 1))
	end
	A_LoopSystem:AddUpdater(self._loop)
end

function ALittle.RichEdit:GetCursor()
	return self._cursor
end

function ALittle.RichEdit.__getter:link_map()
	return self._link_map
end

function ALittle.RichEdit:ClearLinkMap()
	self._link_map = ALittle.CreateValueWeakMap()
end

function ALittle.RichEdit.__getter:real_height()
	return self._line_list[self._line_count].acc_height
end

function ALittle.RichEdit.__getter:real_edit_height()
	local line_list = self._line_list
	local last_line = line_list[self._line_count]
	if last_line.acc_height ~= last_line.pre_height then
		return last_line.acc_height
	end
	return last_line.acc_height + self._enter_key_height
end

function ALittle.RichEdit.__getter:can_drag_text()
	return self._can_drag_text
end

function ALittle.RichEdit.__setter:can_drag_text(value)
	self._can_drag_text = value
end

function ALittle.RichEdit.__setter:auto_ims(value)
	self._auto_ims = value
end

function ALittle.RichEdit.__getter:auto_ims()
	return self._auto_ims
end

function ALittle.RichEdit.__getter:multi_cursor()
	return self._multi_cursor
end

function ALittle.RichEdit.__setter:width(value)
	if self.width == value then
		return
	end
	ALittle.DisplayLayout.__setter.width(self, value)
	local char_info_list = self:GetCharInfoList()
	self:ClearText()
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursor()
end

function ALittle.RichEdit.__setter:height(value)
	if self.height == value then
		return
	end
	ALittle.DisplayLayout.__setter.height(self, value)
	self._default_text_area.y = self._scroll_list.y
	self._default_text_area.height = self._default_text_area.real_height
	if self._default_text_area.height > self._scroll_list.height then
		self._default_text_area.height = self._scroll_list.height
	end
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit.__setter:cursor_red(value)
	self._cursor.red = value
	self._select_1.red = value
	self._select_2.red = value
	self._select_3.red = value
end

function ALittle.RichEdit.__getter:cursor_red()
	return self._cursor.red
end

function ALittle.RichEdit.__setter:cursor_green(value)
	self._cursor.green = value
	self._select_1.green = value
	self._select_2.green = value
	self._select_3.green = value
end

function ALittle.RichEdit.__getter:cursor_green()
	return self._cursor.green
end

function ALittle.RichEdit.__setter:cursor_blue(value)
	self._cursor.blue = value
	self._select_1.blue = value
	self._select_2.blue = value
	self._select_3.blue = value
end

function ALittle.RichEdit.__getter:cursor_blue()
	return self._cursor.blue
end

function ALittle.RichEdit:ShowCursor(value)
	if self._multi_cursor == false then
		if value then
			if self._select_1.visible == false then
				self._cursor.visible = value
			else
				self._cursor.visible = false
			end
		else
			self._cursor.visible = (self._select_1.visible == false)
		end
	end
end

function ALittle.RichEdit.__setter:font_bold(value)
	if self._font_text.bold == value then
		return
	end
	self._font_text.bold = value
	self._default_text_area.bold = value
	local char_info_list = self:GetCharInfoList()
	self:ClearText()
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursor()
end

function ALittle.RichEdit.__setter:font_underline(value)
	if self._font_text.underline == value then
		return
	end
	self._font_text.underline = value
	self._default_text_area.underline = value
end

function ALittle.RichEdit.__setter:font_deleteline(value)
	if self._font_text.deleteline == value then
		return
	end
	self._font_text.deleteline = value
	self._default_text_area.deleteline = value
end

function ALittle.RichEdit.__setter:font_italic(value)
	if self._font_text.italic == value then
		return
	end
	self._font_text.italic = value
	self._default_text_area.italic = value
end

function ALittle.RichEdit.__setter:font_path(value)
	if self._font_text.font_path == value then
		return
	end
	self._font_text.font_path = value
	self._default_text_area.font_path = value
	self._default_text_area.height = self._default_text_area.real_height
	if self._default_text_area.height > self._scroll_list.height then
		self._default_text_area.height = self._scroll_list.height
	end
	if self._font_text.font_path ~= nil and self._font_text.font_size ~= nil then
		self._enter_key_height = self._font_text.native_show:GetFontHeight()
		local char_info_list = self:GetCharInfoList()
		self:ClearText()
		self:InsertTextImpl(char_info_list, false)
		self:ResetCursor()
	end
end

function ALittle.RichEdit.__setter:font_size(value)
	if self._font_text.font_size == value then
		return
	end
	self._font_text.font_size = value
	self._default_text_area.font_size = value
	self._default_text_area.height = self._default_text_area.real_height
	if self._default_text_area.height > self._scroll_list.height then
		self._default_text_area.height = self._scroll_list.height
	end
	if self._font_text.font_path ~= nil and self._font_text.font_size ~= nil then
		self._enter_key_height = self._font_text.native_show:GetFontHeight()
		local char_info_list = self:GetCharInfoList()
		self:ClearText()
		self:InsertTextImpl(char_info_list, false)
		self:ResetCursor()
	end
end

function ALittle.RichEdit.__getter:font_path()
	return self._font_text.font_path
end

function ALittle.RichEdit.__getter:font_size()
	return self._font_text.font_size
end

function ALittle.RichEdit.__setter:font_red(value)
	if self._font_text.red == value then
		return
	end
	self._font_text.red = value
	self._default_text_area.red = value
end

function ALittle.RichEdit.__getter:font_red()
	return self._font_text.red
end

function ALittle.RichEdit.__setter:font_green(value)
	if self._font_text.green == value then
		return
	end
	self._font_text.green = value
	self._default_text_area.green = value
end

function ALittle.RichEdit.__getter:font_green()
	return self._font_text.green
end

function ALittle.RichEdit.__setter:font_blue(value)
	if self._font_text.blue == value then
		return
	end
	self._font_text.blue = value
	self._default_text_area.blue = value
end

function ALittle.RichEdit.__getter:font_blue()
	return self._font_text.blue
end

function ALittle.RichEdit.__setter:default_text(value)
	self._default_text_area.text = value
	self._default_text_area.height = self._default_text_area.real_height
	if self._default_text_area.height > self._scroll_list.height then
		self._default_text_area.height = self._scroll_list.height
	end
end

function ALittle.RichEdit.__setter:text(value)
	self:ClearText()
	self:InsertTextNative(value)
	self:ShowDefaultText()
end

function ALittle.RichEdit.__getter:text()
	local displaylist = self:CharInfoListToDisplayList(self:GetCharInfoList())
	local text = ""
	for k, v in ___ipairs(displaylist) do
		if v.__class == "Text" then
			text = text .. v.text
		end
	end
	return text
end

function ALittle.RichEdit.__getter:default_text()
	return self._default_text_area.text
end

function ALittle.RichEdit.__setter:default_text_alpha(value)
	self._default_text_area.alpha = value
end

function ALittle.RichEdit.__getter:default_text_alpha()
	return self._default_text_area.alpha
end

function ALittle.RichEdit.__setter:display_list(value)
	local char_info_list = self:DisplayListToCharInfoList(value)
	self:ClearText()
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursor()
	self:ShowDefaultText()
end

function ALittle.RichEdit.__getter:display_list()
	return self:CharInfoListToDisplayList(self:GetCharInfoList())
end

function ALittle.RichEdit.__setter:start_cursor(value)
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

function ALittle.RichEdit.__getter:start_cursor()
	return self._start_cursor
end

function ALittle.RichEdit.__setter:end_cursor(value)
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

function ALittle.RichEdit.__getter:end_cursor()
	return self._end_cursor
end

function ALittle.RichEdit.__setter:cursor_margin_up(value)
	if value == self._cursor_margin_up then
		return
	end
	self._cursor_margin_up = value
	self:ResetCursor()
end

function ALittle.RichEdit.__getter:cursor_margin_up()
	return self._cursor_margin_up
end

function ALittle.RichEdit.__setter:cursor_margin_down(value)
	if value == self._cursor_margin_down then
		return
	end
	self._cursor_margin_down = value
	self:ResetCursor()
end

function ALittle.RichEdit.__getter:cursor_margin_down()
	return self._cursor_margin_down
end

function ALittle.RichEdit.__setter:margin_halign(value)
	if value == self._margin_halign then
		return
	end
	self._margin_halign = value
	self._scroll_list.width_value = self._margin_halign * 2
	self._default_text_area.width_value = self._margin_halign * 2
	local char_info_list = self:GetCharInfoList()
	self:ClearText()
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursor()
end

function ALittle.RichEdit.__getter:margin_halign()
	return self._margin_halign
end

function ALittle.RichEdit.__setter:margin_valign(value)
	if value == self._margin_valign then
		return
	end
	self._margin_valign = value
	self._scroll_list.height_value = self._margin_valign * 2
	self._default_text_area.y = self._scroll_list.y
	self._default_text_area.height = self._default_text_area.real_height
	if self._default_text_area.height > self._scroll_list.height then
		self._default_text_area.height = self._scroll_list.height
	end
	local char_info_list = self:GetCharInfoList()
	self:ClearText()
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursor()
end

function ALittle.RichEdit.__setter:line_spacing(value)
	if self._line_spacing == self._line_spacing then
		return
	end
	self._line_spacing = value
	self._scroll_list.gap = value
end

function ALittle.RichEdit.__getter:line_spacing()
	return self._line_spacing
end

function ALittle.RichEdit.__getter:margin_valign()
	return self._margin_valign
end

function ALittle.RichEdit.__setter:focus_cursor(value)
	self._focus_cursor = value
end

function ALittle.RichEdit.__getter:focus_cursor()
	return self._focus_cursor
end

function ALittle.RichEdit.__getter:cursor_x()
	return self._cursor.x
end

function ALittle.RichEdit.__getter:cursor_y()
	return self._cursor.y
end

function ALittle.RichEdit.__getter:cursor_b()
	return (self._cursor.y + self._cursor.height) * self.scale_y + self._ims_padding
end

function ALittle.RichEdit.__getter:start_cursor_x()
	return self._event_start_x
end

function ALittle.RichEdit.__getter:start_cursor_y()
	return self._event_start_y
end

function ALittle.RichEdit.__getter:end_cursor_x()
	return self._event_end_x
end

function ALittle.RichEdit.__getter:end_cursor_y()
	return self._event_end_y
end

function ALittle.RichEdit.__getter:regex()
	return self._regex
end

function ALittle.RichEdit.__setter:regex(value)
	if value == nil then
		value = ""
	end
	self._regex = value
end

function ALittle.RichEdit.__getter:limit_len()
	return self._limit_len
end

function ALittle.RichEdit.__setter:limit_len(value)
	if value == nil then
		value = 0
	end
	self._limit_len = value
end

function ALittle.RichEdit:GetLineWidth(value)
	local line = self._line_list[value]
	if line == nil then
		return 0
	end
	return line.char_list[line.char_count].acc_width
end

function ALittle.RichEdit:GetScrollOffset()
	if self._line_start_it == nil then
		return 0
	end
	return self._line_list[self._line_start_it].pre_height + self._start_it_delta
end

function ALittle.RichEdit:GetLineCount()
	return self._line_count
end

function ALittle.RichEdit:Update()
	if self._cursor.abs_visible then
		self._current_flash_alpha = self._current_flash_alpha + self._current_flash_dir
		if (self._current_flash_dir < 0 and self._current_flash_alpha < -0.05) or (self._current_flash_dir > 0 and self._current_flash_alpha > 1.5) then
			self._current_flash_dir = -self._current_flash_dir
		end
		self._cursor.alpha = self._current_flash_alpha
	end
end

function ALittle.RichEdit:GetSelectText()
	local line_list = self._line_list
	local select_text = {}
	local select_text_count = 0
	if self._char_select_it > line_list[self._line_select_it].char_count then
		return {}
	end
	if line_list[self._line_select_it].pre_height > line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_cursor_it
		while true do
			local char_it
			local char_end
			if line_it == self._line_cursor_it then
				char_it = self._char_cursor_it
				char_it = char_it + 1
			else
				char_it = 1
			end
			if line_it == self._line_select_it then
				char_end = self._char_select_it
				char_end = char_end + 1
			else
				char_end = line_list[line_it].char_count + 1
			end
			local line = line_list[line_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
			if line_it == self._line_select_it then
				break
			end
			line_it = line_it + 1
		end
	elseif line_list[self._line_select_it].pre_height < line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_select_it
		while true do
			local char_it
			local char_end
			if line_it == self._line_select_it then
				char_it = self._char_select_it
				char_it = char_it + 1
			else
				char_it = 1
			end
			if line_it == self._line_cursor_it then
				char_end = self._char_cursor_it
				char_end = char_end + 1
			else
				char_end = line_list[line_it].char_count + 1
			end
			local line = line_list[line_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
			if line_it == self._line_cursor_it then
				break
			end
			line_it = line_it + 1
		end
	else
		if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width > line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			local char_it = self._char_select_it
			local char_end = self._char_cursor_it
			char_end = char_end + 1
			char_it = char_it + 1
			local line = line_list[self._line_cursor_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
		elseif line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width < line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			local char_it = self._char_cursor_it
			local char_end = self._char_select_it
			char_end = char_end + 1
			char_it = char_it + 1
			local line = line_list[self._line_cursor_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
		end
	end
	return self:CharInfoListToDisplayList(select_text)
end

function ALittle.RichEdit:GetSelectWord()
	local line_list = self._line_list
	local select_text = {}
	local select_text_count = 0
	if self._char_select_it > line_list[self._line_select_it].char_count then
		return ""
	end
	if line_list[self._line_select_it].pre_height > line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_cursor_it
		while true do
			local char_it
			local char_end
			if line_it == self._line_cursor_it then
				char_it = self._char_cursor_it
				char_it = char_it + 1
			else
				char_it = 1
			end
			if line_it == self._line_select_it then
				char_end = self._char_select_it
				char_end = char_end + 1
			else
				char_end = line_list[line_it].char_count + 1
			end
			local line = line_list[line_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
			if line_it == self._line_select_it then
				break
			end
			line_it = line_it + 1
		end
	elseif line_list[self._line_select_it].pre_height < line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_select_it
		while true do
			local char_it
			local char_end
			if line_it == self._line_select_it then
				char_it = self._char_select_it
				char_it = char_it + 1
			else
				char_it = 1
			end
			if line_it == self._line_cursor_it then
				char_end = self._char_cursor_it
				char_end = char_end + 1
			else
				char_end = line_list[line_it].char_count + 1
			end
			local line = line_list[line_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
			if line_it == self._line_cursor_it then
				break
			end
			line_it = line_it + 1
		end
	else
		if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width > line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			local char_it = self._char_select_it
			local char_end = self._char_cursor_it
			char_end = char_end + 1
			char_it = char_it + 1
			local line = line_list[self._line_cursor_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
		elseif line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width < line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			local char_it = self._char_cursor_it
			local char_end = self._char_select_it
			char_end = char_end + 1
			char_it = char_it + 1
			local line = line_list[self._line_cursor_it]
			while char_it ~= char_end do
				select_text_count = select_text_count + 1
				select_text[select_text_count] = line.char_list[char_it]
				char_it = char_it + 1
			end
		end
	end
	return self:CharInfoListToWord(select_text)
end

function ALittle.RichEdit:DeleteSelectText()
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	local line_list = self._line_list
	if self._char_select_it > line_list[self._line_select_it].char_count then
		return false
	end
	local line_begin_it
	local begin_it
	local line_end_it
	local end_it
	if line_list[self._line_select_it].pre_height > line_list[self._line_cursor_it].pre_height then
		line_begin_it = self._line_cursor_it
		begin_it = self._char_cursor_it
		line_end_it = self._line_select_it
		end_it = self._char_select_it
	elseif line_list[self._line_select_it].pre_height < line_list[self._line_cursor_it].pre_height then
		line_begin_it = self._line_select_it
		begin_it = self._char_select_it
		line_end_it = self._line_cursor_it
		end_it = self._char_cursor_it
	else
		line_begin_it = self._line_select_it
		line_end_it = self._line_cursor_it
		begin_it = self._char_select_it
		end_it = self._char_cursor_it
		if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width > line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			begin_it = self._char_select_it
			end_it = self._char_cursor_it
		elseif line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width < line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			begin_it = self._char_cursor_it
			end_it = self._char_select_it
		end
	end
	if begin_it == 1 then
		if line_begin_it ~= 1 and line_list[line_begin_it].force_line == false then
			line_begin_it = line_begin_it - 1
			begin_it = line_list[line_begin_it].char_count + 1
			begin_it = begin_it - 1
		end
	end
	self:DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it)
	self:ResetCursor()
	return true
end

function ALittle.RichEdit:CheckTextRegexLimit(text)
	if self._limit_len ~= 0 then
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

function ALittle.RichEdit:InsertTextNative(text)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:CheckTextRegexLimit(text) == false then
		return false
	end
	self:DeleteSelectText()
	local char_info_list = {}
	local char_info_list_count = 0
	local new_char_info = {}
	new_char_info.acc_width = 0
	new_char_info.pre_width = 0
	new_char_info.text_info = self:InitTextInfo()
	new_char_info.text_object = nil
	new_char_info.text = text
	new_char_info.ctrl_info = nil
	new_char_info.ctrl = nil
	char_info_list_count = char_info_list_count + 1
	char_info_list[char_info_list_count] = new_char_info
	self:InsertTextImpl(char_info_list, false)
	self:ResetCursorLine()
	self:ResetCursor()
	return true
end

function ALittle.RichEdit:CheckDisplayListRegexLimit(display_list)
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

function ALittle.RichEdit:InsertDisplayListNative(display_list, selected)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:CheckDisplayListRegexLimit(display_list) == false then
		return false
	end
	self:DeleteSelectText()
	local line_list = self._line_list
	local char_info = line_list[self._line_cursor_it].char_list[self._char_cursor_it]
	local char_info_list = self:DisplayListToCharInfoList(display_list, char_info.text_info)
	self:InsertTextImpl(char_info_list, selected)
	self:UpdateFontText()
	self:ResetCursorLine()
	self:ResetCursor()
	return true
end

function ALittle.RichEdit:DeleteText(left)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return false
	end
	if self:DeleteSelectText() then
		return true
	end
	local line_list = self._line_list
	if left then
		if self._line_cursor_it == 1 and self._char_cursor_it == 1 then
			return false
		end
		local line_begin_it = self._line_cursor_it
		local begin_it = self._char_cursor_it
		local line_end_it = self._line_cursor_it
		local end_it = self._char_cursor_it
		if begin_it == 1 then
			if line_begin_it ~= 1 then
				line_begin_it = line_begin_it - 1
				begin_it = line_list[line_begin_it].char_count + 1
				begin_it = begin_it - 1
			end
		else
			begin_it = begin_it - 1
			if begin_it == 1 and line_list[line_begin_it].force_line == false then
				if line_begin_it ~= 1 then
					line_begin_it = line_begin_it - 1
					begin_it = line_list[line_begin_it].char_count + 1
					begin_it = begin_it - 1
				end
			end
		end
		self:DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it)
	else
		local end_line = self._line_count + 1
		end_line = end_line - 1
		local end_char = line_list[end_line].char_count + 1
		end_char = end_char - 1
		if self._line_cursor_it == end_line and self._char_cursor_it == end_char then
			return false
		end
		local line_begin_it = self._line_cursor_it
		local begin_it = self._char_cursor_it
		local line_end_it = self._line_cursor_it
		local end_it = self._char_cursor_it
		end_char = line_list[line_end_it].char_count + 1
		end_char = end_char - 1
		if end_it == end_char then
			if line_end_it ~= end_line then
				line_end_it = line_end_it + 1
				end_it = 1
				if line_list[line_end_it].force_line == false then
					end_it = end_it + 1
					if end_it > line_list[line_end_it].char_count then
						end_it = end_it - 1
					end
				end
			end
		else
			end_it = end_it + 1
		end
		self:DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it)
	end
	self:ResetCursorLine()
	self:ResetCursor()
	return true
end

function ALittle.RichEdit:ClearText()
	self._line_list = {}
	self._line_count = 0
	local line_info = {}
	line_info.char_list = {}
	line_info.child_list = {}
	line_info.char_count = 0
	line_info.child_count = 0
	line_info.pre_height = 0
	line_info.acc_height = 0
	line_info.force_line = false
	line_info.container = nil
	self._line_count = self._line_count + 1
	self._line_list[self._line_count] = line_info
	local char_info = {}
	char_info.acc_width = 0
	char_info.pre_width = 0
	char_info.text_info = self:InitTextInfo()
	char_info.text_object = nil
	char_info.text = ""
	char_info.ctrl_info = nil
	char_info.ctrl = nil
	line_info.char_count = line_info.char_count + 1
	line_info.char_list[line_info.char_count] = char_info
	self._line_start_it = 1
	self._start_it_delta = 0
	self._line_cursor_it = 1
	self._char_cursor_it = 1
	self._line_select_it = 1
	self._char_select_it = 2
	self:Draw()
end

function ALittle.RichEdit:SetStartIt(line_index)
	if line_index < 1 or line_index > self._line_count then
		return
	end
	self._line_start_it = line_index
	self._start_it_delta = 0
	self:AdjustContentY()
end

function ALittle.RichEdit:ResetCursor()
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	local line_list = self._line_list
	if (self._char_select_it > line_list[self._line_select_it].char_count) or (self._line_select_it == self._line_cursor_it and self._char_select_it == self._char_cursor_it) then
		self._select_1.visible = false
		self._select_2.visible = false
		self._select_3.visible = false
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
		local cursor_width = 0.0
		local line = line_list[self._line_cursor_it]
		local char = line.char_list[self._char_cursor_it]
		if char.ctrl ~= nil then
			self._cursor.height = char.ctrl.height
			cursor_width = 2
		else
			if char.text_object ~= nil then
				self._cursor.height = char.text_object.height
				cursor_width = self:GetCursorWidth(char.text_object.font_size)
			else
				local next_char = line.char_list[self._char_cursor_it + 1]
				if next_char ~= nil then
					if next_char.ctrl ~= nil then
						self._cursor.height = next_char.ctrl.height
						cursor_width = 2
					elseif next_char.text_object ~= nil then
						self._cursor.height = next_char.text_object.height
						cursor_width = self:GetCursorWidth(next_char.text_object.font_size)
					else
						self._cursor.height = self._font_text.native_show:GetFontHeight()
						cursor_width = self:GetCursorWidth(self._font_text.font_size)
					end
				else
					self._cursor.height = self._font_text.native_show:GetFontHeight()
					cursor_width = self:GetCursorWidth(self._font_text.font_size)
				end
			end
		end
		self._cursor.width = cursor_width
		local line_height = line_list[self._line_cursor_it].acc_height - line_list[self._line_cursor_it].pre_height
		local offset_y = line_height - self._cursor.height
		if offset_y <= 0 then
			offset_y = 0
		end
		self._cursor.y = self._scroll_list.y + line_list[self._line_cursor_it].pre_height - line_list[self._line_start_it].pre_height + offset_y - self._start_it_delta
		self._cursor.x = self._scroll_list.x + line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
		return
	end
	if self._multi_cursor == false then
		self._cursor.visible = false
	end
	if line_list[self._line_select_it].pre_height > line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_cursor_it
		self._select_1.visible = true
		local select_1_y = line_list[self._line_cursor_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_1_height = line_list[self._line_cursor_it].acc_height - line_list[self._line_cursor_it].pre_height
		if select_1_y < 0 then
			select_1_height = select_1_y + select_1_height
			select_1_y = 0
		end
		if select_1_y + select_1_height > self._scroll_list.height then
			select_1_height = self._scroll_list.height - select_1_y
		end
		if select_1_height <= 0 then
			self._select_1.visible = false
		end
		self._select_1.y = self._scroll_list.y + select_1_y
		self._select_1.x = self._scroll_list.x + line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
		self._select_1.height = select_1_height
		self._select_1.width = self._scroll_list.width - line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
		self._select_3.visible = (line_list[self._line_cursor_it].acc_height ~= line_list[self._line_select_it].pre_height)
		local select_3_y = line_list[self._line_cursor_it].acc_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_3_height = line_list[self._line_select_it].pre_height - line_list[self._line_cursor_it].acc_height
		if select_3_y < 0 then
			select_3_height = select_3_y + select_3_height
			select_3_y = 0
		end
		if select_3_y + select_3_height > self._scroll_list.height then
			select_3_height = self._scroll_list.height - select_3_y
		end
		if select_3_height <= 0 then
			self._select_3.visible = false
		end
		self._select_3.y = self._scroll_list.y + select_3_y
		self._select_3.x = self._scroll_list.x
		self._select_3.height = select_3_height
		self._select_3.width = self._scroll_list.width
		line_it = self._line_select_it
		self._select_2.visible = true
		local select_2_y = line_list[self._line_select_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_2_height = line_list[self._line_select_it].acc_height - line_list[self._line_select_it].pre_height
		if select_2_y < 0 then
			select_2_height = select_2_y + select_2_height
			select_2_y = 0
		end
		if select_2_y + select_2_height > self._scroll_list.height then
			select_2_height = self._scroll_list.height - select_2_y
		end
		if select_2_height <= 0 then
			self._select_2.visible = false
		end
		self._select_2.y = self._scroll_list.y + select_2_y
		self._select_2.x = self._scroll_list.x
		self._select_2.height = select_2_height
		self._select_2.width = line_list[self._line_select_it].char_list[self._char_select_it].acc_width
		if self._multi_cursor == true then
			self._cursor.visible = false
			self._start_cursor.x = self._select_1.x - self._start_cursor.width
			self._start_cursor.height = self._select_1.height + self._cursor_margin_up + self._cursor_margin_down
			self._start_cursor.y = self._select_1.y - self._cursor_margin_up
			self._end_cursor.x = self._select_2.x + self._select_2.width
			self._end_cursor.height = self._select_2.height + self._cursor_margin_up + self._cursor_margin_down
			self._end_cursor.y = self._select_2.y - self._cursor_margin_up
			self._start_cursor.visible = self._select_1.visible
			self._end_cursor.visible = self._select_2.visible
			self._start_cursor_data = "cursor"
			self._end_cursor_data = "select"
			self._event_start_x = self._select_1.x
			self._event_start_y = self._select_1.y
			self._event_end_x = self._select_2.x + self._select_2.width
			self._event_end_y = self._select_2.y + self._select_2.height
		end
	elseif line_list[self._line_select_it].pre_height < line_list[self._line_cursor_it].pre_height then
		local line_it = self._line_select_it
		self._select_1.visible = true
		local select_1_y = line_list[self._line_select_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_1_height = line_list[self._line_select_it].acc_height - line_list[self._line_select_it].pre_height
		if select_1_y < 0 then
			select_1_height = select_1_y + select_1_height
			select_1_y = 0
		end
		if select_1_y + select_1_height > self._scroll_list.height then
			select_1_height = self._scroll_list.height - select_1_y
		end
		if select_1_height <= 0 then
			self._select_1.visible = false
		end
		self._select_1.y = self._scroll_list.y + select_1_y
		self._select_1.x = self._scroll_list.x + line_list[self._line_select_it].char_list[self._char_select_it].acc_width
		self._select_1.height = select_1_height
		self._select_1.width = self._scroll_list.width - line_list[self._line_select_it].char_list[self._char_select_it].acc_width
		line_it = self._line_cursor_it
		self._select_2.visible = true
		local select_2_y = line_list[self._line_cursor_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_2_height = line_list[self._line_cursor_it].acc_height - line_list[self._line_cursor_it].pre_height
		if select_2_y < 0 then
			select_2_height = select_2_y + select_2_height
			select_2_y = 0
		end
		if select_2_y + select_2_height > self._scroll_list.height then
			select_2_height = self._scroll_list.height - select_2_y
		end
		if select_2_height <= 0 then
			self._select_2.visible = false
		end
		self._select_2.y = self._scroll_list.y + select_2_y
		self._select_2.x = self._scroll_list.x
		self._select_2.height = select_2_height
		self._select_2.width = line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
		self._select_3.visible = (line_list[self._line_select_it].acc_height ~= line_list[self._line_cursor_it].pre_height)
		local select_3_y = line_list[self._line_select_it].acc_height - line_list[self._line_start_it].pre_height - self._start_it_delta
		local select_3_height = line_list[self._line_cursor_it].pre_height - line_list[self._line_select_it].acc_height
		if select_3_y < 0 then
			select_3_height = select_3_y + select_3_height
			select_3_y = 0
		end
		if select_3_y + select_3_height > self._scroll_list.height then
			select_3_height = self._scroll_list.height - select_3_y
		end
		if select_3_height <= 0 then
			self._select_3.visible = false
		end
		self._select_3.y = self._scroll_list.y + select_3_y
		self._select_3.x = self._scroll_list.x
		self._select_3.width = self._scroll_list.width
		self._select_3.height = select_3_height
		if self._multi_cursor == true then
			self._cursor.visible = false
			self._start_cursor.x = self._select_1.x - self._start_cursor.width
			self._start_cursor.height = self._select_1.height + self._cursor_margin_up + self._cursor_margin_down
			self._start_cursor.y = self._select_1.y - self._cursor_margin_up
			self._end_cursor.x = self._select_2.x + self._select_2.width
			self._end_cursor.height = self._select_2.height + self._cursor_margin_up + self._cursor_margin_down
			self._end_cursor.y = self._select_2.y - self._cursor_margin_up
			self._start_cursor.visible = self._select_1.visible
			self._end_cursor.visible = self._select_2.visible
			self._start_cursor_data = "select"
			self._end_cursor_data = "cursor"
			self._event_start_x = self._select_1.x
			self._event_start_y = self._select_1.y
			self._event_end_x = self._select_2.x + self._select_2.width
			self._event_end_y = self._select_2.y + self._select_2.height
		end
	else
		self._select_1.visible = false
		self._select_2.visible = false
		self._select_3.visible = false
		if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width > line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			self._select_1.visible = true
			local select_1_y = line_list[self._line_cursor_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
			local select_1_height = line_list[self._line_cursor_it].acc_height - line_list[self._line_cursor_it].pre_height
			if select_1_y < 0 then
				select_1_height = select_1_y + select_1_height
				select_1_y = 0
			end
			if select_1_y + select_1_height > self._scroll_list.height then
				select_1_height = self._scroll_list.height - select_1_y
			end
			if select_1_height <= 0 then
				self._select_1.visible = false
			end
			self._select_1.x = self._scroll_list.x + line_list[self._line_select_it].char_list[self._char_select_it].acc_width
			self._select_1.y = self._scroll_list.y + select_1_y
			self._select_1.height = select_1_height
			self._select_1.width = line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width - line_list[self._line_select_it].char_list[self._char_select_it].acc_width
			if self._multi_cursor == true then
				self._cursor.visible = false
				self._start_cursor.x = self._select_1.x - self._start_cursor.width
				self._start_cursor.height = self._select_1.height + self._cursor_margin_up + self._cursor_margin_down
				self._start_cursor.y = self._select_1.y - self._cursor_margin_up
				self._end_cursor.x = self._select_1.x + self._select_1.width
				self._end_cursor.height = self._start_cursor.height
				self._end_cursor.y = self._start_cursor.y
				self._start_cursor.visible = self._select_1.visible
				self._end_cursor.visible = self._select_1.visible
				self._start_cursor_data = "select"
				self._end_cursor_data = "cursor"
				self._event_start_x = self._select_1.x
				self._event_start_y = self._select_1.y
				self._event_end_x = self._select_1.x + self._select_1.width
				self._event_end_y = self._select_1.y + self._select_1.height
			end
		elseif line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width < line_list[self._line_select_it].char_list[self._char_select_it].acc_width then
			self._select_1.visible = true
			local select_1_y = line_list[self._line_cursor_it].pre_height - line_list[self._line_start_it].pre_height - self._start_it_delta
			local select_1_height = line_list[self._line_cursor_it].acc_height - line_list[self._line_cursor_it].pre_height
			if select_1_y < 0 then
				select_1_height = select_1_y + select_1_height
				select_1_y = 0
			end
			if select_1_y + select_1_height > self._scroll_list.height then
				select_1_height = self._scroll_list.height - select_1_y
			end
			if select_1_height <= 0 then
				self._select_1.visible = false
			end
			self._select_1.x = self._scroll_list.x + line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
			self._select_1.y = self._scroll_list.y + select_1_y
			self._select_1.height = select_1_height
			self._select_1.width = line_list[self._line_select_it].char_list[self._char_select_it].acc_width - line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
			if self._multi_cursor == true then
				self._cursor.visible = false
				self._start_cursor.x = self._select_1.x - self._start_cursor.width
				self._start_cursor.height = self._select_1.height + self._cursor_margin_up + self._cursor_margin_down
				self._start_cursor.y = self._select_1.y - self._cursor_margin_up
				self._end_cursor.x = self._select_1.x + self._select_1.width
				self._end_cursor.height = self._start_cursor.height
				self._end_cursor.y = self._start_cursor.y
				self._start_cursor.visible = self._select_1.visible
				self._end_cursor.visible = self._select_1.visible
				self._start_cursor_data = "cursor"
				self._end_cursor_data = "select"
				self._event_start_x = self._select_1.x
				self._event_start_y = self._select_1.y
				self._event_end_x = self._select_1.x + self._select_1.width
				self._event_end_y = self._select_1.y + self._select_1.height
			end
		end
	end
end

function ALittle.RichEdit:DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	local line_list = self._line_list
	local line_delete_begin = line_begin_it
	local line_delete_end = line_end_it
	local char_delete_begin = begin_it
	local char_delete_end = end_it
	if line_list[line_begin_it].pre_height > line_list[line_end_it].pre_height then
		line_delete_begin = line_end_it
		char_delete_begin = end_it
		line_delete_end = line_begin_it
		char_delete_end = begin_it
	elseif line_list[line_begin_it].pre_height == line_list[line_end_it].pre_height then
		if line_list[line_begin_it].char_list[begin_it].acc_width > line_list[line_end_it].char_list[end_it].acc_width then
			char_delete_begin = end_it
			char_delete_end = begin_it
		end
	end
	if line_list[self._line_start_it].pre_height >= line_list[line_delete_begin].pre_height then
		self._line_start_it = line_delete_begin
		self._start_it_delta = 0
	end
	local calc_text_1 = {}
	local calc_text_1_count = 0
	local char_it = 1
	char_it = char_it + 1
	char_delete_begin = char_delete_begin + 1
	local line = line_list[line_delete_begin]
	while char_it ~= char_delete_begin do
		calc_text_1_count = calc_text_1_count + 1
		calc_text_1[calc_text_1_count] = line.char_list[char_it]
		char_it = char_it + 1
	end
	local calc_text_2 = {}
	local calc_text_2_count = 0
	char_it = char_delete_end
	char_it = char_it + 1
	line = line_list[line_delete_end]
	while char_it <= line.char_count do
		calc_text_2_count = calc_text_2_count + 1
		calc_text_2[calc_text_2_count] = line.char_list[char_it]
		char_it = char_it + 1
	end
	local line_it = line_delete_end
	line_it = line_it + 1
	local free_line_it = 0
	while line_it <= self._line_count do
		char_it = 1
		line = line_list[line_it]
		if line.force_line then
			free_line_it = line_it
			break
		end
		while char_it <= line.char_count do
			calc_text_2_count = calc_text_2_count + 1
			calc_text_2[calc_text_2_count] = line.char_list[char_it]
			char_it = char_it + 1
		end
		line_it = line_it + 1
	end
	local char_info = line_list[line_delete_begin].char_list[1]
	line_list[line_delete_begin].char_list = {}
	line_list[line_delete_begin].char_count = 1
	line_list[line_delete_begin].char_list[1] = char_info
	line_list[line_delete_begin].child_list = {}
	line_list[line_delete_begin].child_count = 0
	line_list[line_delete_begin].acc_height = line_list[line_delete_begin].pre_height
	line_list[line_delete_begin].container = nil
	local free_line_list = nil
	local free_line_list_count = 0
	if free_line_it > 0 then
		free_line_list = {}
		local i = free_line_it
		while true do
			if not(i <= self._line_count) then break end
			free_line_list_count = free_line_list_count + 1
			free_line_list[free_line_list_count] = line_list[i]
			i = i+(1)
		end
	end
	line_it = line_delete_begin
	line_it = line_it + 1
	local i = line_it
	while true do
		if not(i <= self._line_count) then break end
		line_list[i] = nil
		i = i+(1)
	end
	self._line_count = line_delete_begin
	calc_text_1 = self:JoinCharInfoList(calc_text_1)
	calc_text_2 = self:JoinCharInfoList(calc_text_2)
	self._line_cursor_it, self._char_cursor_it = self:InsertTextUtil(calc_text_1)
	self:InsertTextUtil(calc_text_2)
	if free_line_list ~= nil then
		local last_line = line_list[self._line_count]
		if last_line.char_count == 1 and last_line.force_line then
			last_line.acc_height = last_line.pre_height + self._enter_key_height
		end
		local start_y = last_line.acc_height
		for k, line_v in ___ipairs(free_line_list) do
			self._line_count = self._line_count + 1
			line_list[self._line_count] = line_v
			local line_height = line_v.acc_height - line_v.pre_height
			line_v.pre_height = start_y
			start_y = start_y + line_height
			line_v.acc_height = start_y
		end
	end
	self._line_select_it = self._line_count + 1
	self._line_select_it = self._line_select_it - 1
	self._char_select_it = line_list[self._line_select_it].char_count + 1
	self:Draw()
end

function ALittle.RichEdit:InsertTextImpl(char_info_list, selected)
	if self._font_text.font_path == nil or self._font_text.font_size == nil then
		return
	end
	if char_info_list[1] == nil then
		return
	end
	local line_list = self._line_list
	local line_cursor_it_tmp = self._line_cursor_it
	local char_cursor_it_tmp = self._char_cursor_it
	local calc_text_1 = {}
	local calc_text_1_count = 0
	local char_it = 1
	char_it = char_it + 1
	local char_end_it = self._char_cursor_it
	char_end_it = char_end_it + 1
	local line = line_list[self._line_cursor_it]
	while char_it ~= char_end_it do
		calc_text_1_count = calc_text_1_count + 1
		calc_text_1[calc_text_1_count] = line.char_list[char_it]
		char_it = char_it + 1
	end
	for k, v in ___ipairs(char_info_list) do
		calc_text_1_count = calc_text_1_count + 1
		calc_text_1[calc_text_1_count] = v
	end
	local calc_text_2 = {}
	local calc_text_2_count = 0
	char_it = self._char_cursor_it
	char_it = char_it + 1
	line = line_list[self._line_cursor_it]
	while char_it <= line.char_count do
		calc_text_2_count = calc_text_2_count + 1
		calc_text_2[calc_text_2_count] = line.char_list[char_it]
		char_it = char_it + 1
	end
	local line_it = self._line_cursor_it
	line_it = line_it + 1
	local free_line_it = 0
	while line_it <= self._line_count do
		char_it = 1
		line = line_list[line_it]
		if line.force_line then
			free_line_it = line_it
			break
		end
		while char_it <= line.char_count do
			calc_text_2_count = calc_text_2_count + 1
			calc_text_2[calc_text_2_count] = line.char_list[char_it]
			char_it = char_it + 1
		end
		line_it = line_it + 1
	end
	local char_info = line_list[self._line_cursor_it].char_list[1]
	line_list[self._line_cursor_it].char_list = {}
	line_list[self._line_cursor_it].char_count = 1
	line_list[self._line_cursor_it].char_list[1] = char_info
	line_list[self._line_cursor_it].child_list = {}
	line_list[self._line_cursor_it].child_count = 0
	line_list[self._line_cursor_it].acc_height = line_list[self._line_cursor_it].pre_height
	line_list[self._line_cursor_it].container = nil
	local free_line_list = nil
	local free_line_list_count = 0
	if free_line_it > 0 then
		free_line_list = {}
		local i = free_line_it
		while true do
			if not(i <= self._line_count) then break end
			free_line_list_count = free_line_list_count + 1
			free_line_list[free_line_list_count] = line_list[i]
			i = i+(1)
		end
	end
	line_it = self._line_cursor_it
	line_it = line_it + 1
	local i = line_it
	while true do
		if not(i <= self._line_count) then break end
		line_list[i] = nil
		i = i+(1)
	end
	self._line_count = self._line_cursor_it
	calc_text_1 = self:JoinCharInfoList(calc_text_1)
	calc_text_2 = self:JoinCharInfoList(calc_text_2)
	self._line_cursor_it, self._char_cursor_it = self:InsertTextUtil(calc_text_1)
	self:InsertTextUtil(calc_text_2)
	if free_line_list ~= nil then
		local last_line = line_list[self._line_count]
		if last_line.char_count == 1 and last_line.force_line then
			last_line.acc_height = last_line.pre_height + self._enter_key_height
		end
		local start_y = last_line.acc_height
		for k1, line_v in ___ipairs(free_line_list) do
			self._line_count = self._line_count + 1
			line_list[self._line_count] = line_v
			local line_height = line_v.acc_height - line_v.pre_height
			line_v.pre_height = start_y
			start_y = start_y + line_height
			line_v.acc_height = start_y
		end
	end
	if selected then
		self._line_select_it = line_cursor_it_tmp
		self._char_select_it = char_cursor_it_tmp
	else
		self._line_select_it = self._line_count + 1
		self._line_select_it = self._line_select_it - 1
		self._char_select_it = line_list[self._line_select_it].char_count + 1
	end
	self:Draw()
end

function ALittle.RichEdit:InsertTextUtil(char_info_list)
	local line_list = self._line_list
	local total_width = self._scroll_list.width
	local new_char_info_list = {}
	local new_char_info_list_count = 0
	for index, char_info in ___ipairs(char_info_list) do
		if char_info.ctrl_info == nil then
			new_char_info_list_count = self:SplitText(char_info, new_char_info_list, new_char_info_list_count)
		else
			new_char_info_list_count = new_char_info_list_count + 1
			new_char_info_list[new_char_info_list_count] = char_info
		end
	end
	char_info_list = new_char_info_list
	local line_it = self._line_count + 1
	line_it = line_it - 1
	local line_info = line_list[line_it]
	local begin_it = line_info.char_count + 1
	begin_it = begin_it - 1
	if line_it == 1 and begin_it == 1 then
		line_info.char_list[1].text_info = self:InitTextInfo()
	end
	local display_info = nil
	local display_object = nil
	local display_index = 1
	local remain_width = total_width - line_info.char_list[line_info.char_count].acc_width
	while true do
		if display_info == nil then
			display_info = char_info_list[display_index]
			if display_info == nil then
				break
			end
		end
		if display_info.ctrl_info == nil then
			if display_info.text == "\n" then
				if line_info.char_count == 1 then
					line_info.acc_height = line_info.pre_height + self._enter_key_height
				end
				local new_line_info = {}
				new_line_info.char_list = {}
				new_line_info.child_list = {}
				new_line_info.char_count = 0
				new_line_info.child_count = 0
				new_line_info.pre_height = line_info.acc_height + self._line_spacing
				new_line_info.acc_height = line_info.acc_height
				new_line_info.force_line = true
				new_line_info.container = nil
				self._line_count = self._line_count + 1
				line_list[self._line_count] = new_line_info
				local char_info = {}
				char_info.acc_width = 0
				char_info.pre_width = 0
				char_info.text_info = display_info.text_info
				char_info.text_object = nil
				char_info.text = "\n"
				char_info.ctrl_info = nil
				char_info.ctrl = nil
				new_line_info.char_count = new_line_info.char_count + 1
				new_line_info.char_list[new_line_info.char_count] = char_info
				line_info = new_line_info
				display_info = nil
				display_object = nil
				display_index = display_index + 1
				remain_width = total_width
			elseif display_info.text == "\t" then
				if display_object == nil then
					local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
					self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info))
					display_object = self._ctrl_sys:CreateControl(name, self._link_map)
					self._ctrl_sys:UnRegisterInfo(name)
					display_object.text = "    "
				end
				local object_width = display_object.width
				local object_height = display_object.height
				self:SetDrawText(display_object)
				local calc_text = "\t"
				while calc_text ~= "" do
					local byte_count = ALittle.String_GetByteCount(calc_text, 1)
					local sub_text = __sub(calc_text, 1, byte_count)
					local text_width = self._draw_text.native_show:CalcTextWidth("    ")
					local char_info = {}
					char_info.pre_width = line_info.char_list[line_info.char_count].acc_width
					char_info.acc_width = char_info.pre_width + text_width
					char_info.text_info = display_info.text_info
					char_info.text_object = display_object
					char_info.text = sub_text
					char_info.ctrl_info = nil
					char_info.ctrl = nil
					line_info.char_count = line_info.char_count + 1
					line_info.char_list[line_info.char_count] = char_info
					calc_text = __sub(calc_text, byte_count + 1)
				end
				line_info.child_count = line_info.child_count + 1
				line_info.child_list[line_info.child_count] = display_object
				if line_info.acc_height - line_info.pre_height < object_height then
					line_info.acc_height = line_info.pre_height + object_height
				end
				remain_width = remain_width - object_width
				if remain_width <= 0 then
					local new_line_info = {}
					new_line_info.char_list = {}
					new_line_info.child_list = {}
					new_line_info.char_count = 0
					new_line_info.child_count = 0
					new_line_info.pre_height = line_info.acc_height + self._line_spacing
					new_line_info.acc_height = line_info.acc_height
					new_line_info.force_line = false
					new_line_info.container = nil
					self._line_count = self._line_count + 1
					line_list[self._line_count] = new_line_info
					local char_info = {}
					char_info.acc_width = 0
					char_info.pre_width = 0
					char_info.text_info = display_info.text_info
					char_info.text_object = nil
					char_info.text = ""
					char_info.ctrl_info = nil
					char_info.ctrl = nil
					new_line_info.char_count = new_line_info.char_count + 1
					new_line_info.char_list[new_line_info.char_count] = char_info
					line_info = new_line_info
					remain_width = total_width
				end
				display_object = nil
				display_info = nil
				display_index = display_index + 1
			else
				while true do
					if display_info.text == "" then
						display_info = nil
						display_index = display_index + 1
						break
					end
					if display_object == nil then
						local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
						self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info))
						display_object = self._ctrl_sys:CreateControl(name, self._link_map)
						self._ctrl_sys:UnRegisterInfo(name)
					end
					local count = display_object._show:CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width))
					if count == 0 and line_info.char_count <= 1 then
						count = ALittle.String_GetByteCount(display_info.text, 1)
					end
					if count == 0 then
						remain_width = 0
					else
						local calc_text = __sub(display_info.text, 1, count)
						display_object.text = calc_text
						local object_width = display_object.width
						local object_height = display_object.height
						self:SetDrawText(display_object)
						local char_count = display_object._show:GetCutWidthListCount()
						local i = 1
						while true do
							if not(i <= char_count) then break end
							local byte_count = ALittle.String_GetByteCount(calc_text, 1)
							local sub_text = __sub(calc_text, 1, byte_count)
							local text_width = display_object._show:GetCutWidthByIndex(i - 1)
							local char_info = {}
							char_info.pre_width = line_info.char_list[line_info.char_count].acc_width
							char_info.acc_width = text_width
							char_info.text_info = display_info.text_info
							char_info.text_object = display_object
							char_info.text = sub_text
							char_info.ctrl_info = nil
							char_info.ctrl = nil
							line_info.char_count = line_info.char_count + 1
							line_info.char_list[line_info.char_count] = char_info
							calc_text = __sub(calc_text, byte_count + 1)
							i = i+(1)
						end
						remain_width = remain_width - object_width
						display_object._show:ClearCutWidthCache()
						local new_display_info = ALittle.String_CopyTable(display_info)
						new_display_info.text = __sub(display_info.text, count + 1)
						line_info.child_count = line_info.child_count + 1
						line_info.child_list[line_info.child_count] = display_object
						if line_info.acc_height - line_info.pre_height < object_height then
							line_info.acc_height = line_info.pre_height + object_height
						end
						display_info = new_display_info
						display_object = nil
					end
					if remain_width <= 0 then
						local new_line_info = {}
						new_line_info.char_list = {}
						new_line_info.child_list = {}
						new_line_info.char_count = 0
						new_line_info.child_count = 0
						new_line_info.pre_height = line_info.acc_height + self._line_spacing
						new_line_info.acc_height = line_info.acc_height
						new_line_info.force_line = false
						new_line_info.container = nil
						self._line_count = self._line_count + 1
						line_list[self._line_count] = new_line_info
						local char_info = {}
						char_info.acc_width = 0
						char_info.pre_width = 0
						char_info.text_info = display_info.text_info
						char_info.text_object = nil
						char_info.text = ""
						char_info.ctrl_info = nil
						char_info.ctrl = nil
						new_line_info.char_count = new_line_info.char_count + 1
						new_line_info.char_list[new_line_info.char_count] = char_info
						line_info = new_line_info
						remain_width = total_width
					end
				end
			end
		else
			if display_object == nil then
				if display_info.ctrl == nil then
					local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
					self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info))
					display_object = self._ctrl_sys:CreateControl(name, self._link_map)
					self._ctrl_sys:UnRegisterInfo(name)
				else
					display_object = display_info.ctrl
				end
			end
			local object_width = display_object.width
			local object_height = display_object.height
			if remain_width >= object_width or (line_info.char_count == 1 and total_width <= object_width) then
				local char_info = {}
				char_info.pre_width = line_info.char_list[line_info.char_count].acc_width
				char_info.acc_width = char_info.pre_width + display_object.width
				char_info.text_info = line_info.char_list[line_info.char_count].text_info
				char_info.text_object = nil
				char_info.text = nil
				char_info.ctrl_info = display_info.ctrl_info
				char_info.ctrl = display_object
				line_info.char_count = line_info.char_count + 1
				line_info.char_list[line_info.char_count] = char_info
				line_info.child_count = line_info.child_count + 1
				line_info.child_list[line_info.child_count] = display_object
				if line_info.acc_height - line_info.pre_height < object_height then
					line_info.acc_height = line_info.pre_height + object_height
				end
				remain_width = remain_width - object_width
				if remain_width <= 0 then
					local new_line_info = {}
					new_line_info.char_list = {}
					new_line_info.child_list = {}
					new_line_info.char_count = 0
					new_line_info.child_count = 0
					new_line_info.pre_height = line_info.acc_height + self._line_spacing
					new_line_info.acc_height = line_info.acc_height
					new_line_info.force_line = false
					new_line_info.container = nil
					self._line_count = self._line_count + 1
					line_list[self._line_count] = new_line_info
					char_info = {}
					char_info.acc_width = 0
					char_info.pre_width = 0
					char_info.text_info = line_info.char_list[line_info.char_count].text_info
					char_info.text_object = nil
					char_info.text = ""
					char_info.ctrl_info = nil
					char_info.ctrl = nil
					new_line_info.char_count = new_line_info.char_count + 1
					new_line_info.char_list[new_line_info.char_count] = char_info
					line_info = new_line_info
					remain_width = total_width
				end
				display_object = nil
				display_info = nil
				display_index = display_index + 1
			else
				local new_line_info = {}
				new_line_info.char_list = {}
				new_line_info.child_list = {}
				new_line_info.char_count = 0
				new_line_info.child_count = 0
				new_line_info.pre_height = line_info.acc_height + self._line_spacing
				new_line_info.acc_height = line_info.acc_height
				new_line_info.force_line = false
				new_line_info.container = nil
				self._line_count = self._line_count + 1
				line_list[self._line_count] = new_line_info
				local char_info = {}
				char_info.acc_width = 0
				char_info.pre_width = 0
				char_info.text_info = line_info.char_list[line_info.char_count].text_info
				char_info.text_object = nil
				char_info.text = ""
				char_info.ctrl_info = nil
				char_info.ctrl = nil
				new_line_info.char_count = new_line_info.char_count + 1
				new_line_info.char_list[new_line_info.char_count] = char_info
				line_info = new_line_info
				remain_width = total_width
			end
		end
	end
	if line_info.char_count == 1 then
		line_info.acc_height = line_info.pre_height + self._enter_key_height
	end
	local line_begin_it = self._line_count + 1
	line_begin_it = line_begin_it - 1
	begin_it = line_list[line_begin_it].char_count + 1
	begin_it = begin_it - 1
	return line_begin_it, begin_it
end

function ALittle.RichEdit:DrawImpl()
	self._scroll_list:RemoveAllChild()
	for line_index, line_info in ___ipairs(self._line_list) do
		local displayout = line_info.container
		if displayout == nil then
			displayout = ALittle.DisplayLayout(self._ctrl_sys)
			line_info.container = displayout
			displayout.width_type = 4
			displayout.height = line_info.acc_height - line_info.pre_height
			local offset_x = 0.0
			for child_index, child in ___ipairs(line_info.child_list) do
				child.x = offset_x
				offset_x = offset_x + child.width
				child.y = displayout.height - child.height
				displayout:AddChild(child)
			end
		end
		self._scroll_list:AddChild(displayout)
	end
	local child = self._scroll_list:GetChildByIndex(self._line_start_it)
	self._scroll_list.scroll_offset = -child.y - self._start_it_delta
	self._scroll_list:RefreshClipDisLine()
	self._scroll_list:AdjustScrollBar()
	self._draw_loop = nil
end

function ALittle.RichEdit:AdjustContentY()
	if self._draw_loop ~= nil then
		return
	end
	local child = self._scroll_list:GetChildByIndex(self._line_start_it)
	self._scroll_list.scroll_offset = -child.y - self._start_it_delta
	self._scroll_list:RefreshClipDisLine()
	self._scroll_list:AdjustScrollBar()
end

function ALittle.RichEdit:Draw()
	if self._draw_loop ~= nil then
		return
	end
	self._draw_loop = ALittle.LoopFunction(Lua.Bind(self.DrawImpl, self), 1, 0, 1)
	A_LoopSystem:AddUpdater(self._draw_loop)
end

function ALittle.RichEdit:CursorOffsetLR(left)
	local line_list = self._line_list
	if self._char_select_it <= line_list[self._line_select_it].char_count then
		self._char_select_it = line_list[self._line_select_it].char_count + 1
		self:ResetCursor()
		return
	end
	self:CursorOffsetLRImpl(left)
end

function ALittle.RichEdit:CursorOffsetUD(up)
	local line_list = self._line_list
	if self._char_select_it <= line_list[self._line_select_it].char_count then
		self._char_select_it = line_list[self._line_select_it].char_count + 1
		self:ResetCursor()
		return
	end
	self:CursorOffsetUDImpl(up)
end

function ALittle.RichEdit:SelectCursorOffsetLR(left)
	local line_list = self._line_list
	if self._char_select_it > line_list[self._line_select_it].char_count then
		self._line_select_it = self._line_cursor_it
		self._char_select_it = self._char_cursor_it
	end
	self:CursorOffsetLRImpl(left)
end

function ALittle.RichEdit:SelectCursorOffsetUD(up)
	local line_list = self._line_list
	if self._char_select_it > line_list[self._line_select_it].char_count then
		self._line_select_it = self._line_cursor_it
		self._char_select_it = self._char_cursor_it
	end
	self:CursorOffsetUDImpl(up)
end

function ALittle.RichEdit:SetCursorToHome()
	local line_list = self._line_list
	self._char_select_it = line_list[self._line_select_it].char_count + 1
	self._char_cursor_it = 1
	self:ResetCursor()
end

function ALittle.RichEdit:SetCursorToEnd()
	local line_list = self._line_list
	self._char_select_it = line_list[self._line_select_it].char_count + 1
	self._char_cursor_it = line_list[self._line_cursor_it].char_count + 1
	self._char_cursor_it = self._char_cursor_it - 1
	self:ResetCursor()
end

function ALittle.RichEdit:SelectAll()
	local line_list = self._line_list
	self._line_select_it = 1
	self._char_select_it = 1
	self._line_cursor_it = self._line_count + 1
	self._line_cursor_it = self._line_cursor_it - 1
	self._char_cursor_it = line_list[self._line_cursor_it].char_count + 1
	self._char_cursor_it = self._char_cursor_it - 1
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:ResetCursorLine()
	local line_list = self._line_list
	if self._line_cursor_it == self._line_count then
		if line_list[self._line_cursor_it].acc_height > self._scroll_list.height and self._scroll_list.scroll_offset < 0 then
			self._scroll_list.scroll_offset = self._scroll_list.height - line_list[self._line_cursor_it].acc_height
			self._scroll_list:RefreshClipDisLine()
			self._scroll_list:AdjustScrollBar()
			while line_list[self._line_start_it].pre_height > -self._scroll_list.scroll_offset do
				self._line_start_it = self._line_start_it - 1
			end
			self._start_it_delta = -self._scroll_list.scroll_offset - line_list[self._line_start_it].pre_height
			return
		end
		if line_list[self._line_cursor_it].acc_height <= self._scroll_list.height then
			self._scroll_list.scroll_offset = 0
			self._scroll_list:RefreshClipDisLine()
			self._scroll_list:AdjustScrollBar()
			self._line_start_it = 1
			self._start_it_delta = 0
			return
		end
	end
	if line_list[self._line_cursor_it].pre_height <= -self._scroll_list.scroll_offset then
		self._scroll_list.scroll_offset = -line_list[self._line_cursor_it].pre_height
		self._scroll_list:RefreshClipDisLine()
		self._scroll_list:AdjustScrollBar()
		self._line_start_it = self._line_cursor_it
	elseif line_list[self._line_cursor_it].acc_height >= self._scroll_list.height - self._scroll_list.scroll_offset then
		self._scroll_list.scroll_offset = self._scroll_list.height - line_list[self._line_cursor_it].acc_height
		self._scroll_list:RefreshClipDisLine()
		self._scroll_list:AdjustScrollBar()
		while line_list[self._line_start_it].acc_height <= -self._scroll_list.scroll_offset do
			self._line_start_it = self._line_start_it + 1
		end
	end
	self._start_it_delta = -self._scroll_list.scroll_offset - line_list[self._line_start_it].pre_height
end

function ALittle.RichEdit:ClickCursor(offset_x, offset_y)
	local line_list = self._line_list
	self._char_select_it = line_list[self._line_select_it].char_count + 1
	self._line_cursor_it, self._char_cursor_it = self:GetIteratorByOffset(offset_x, offset_y)
	self:ResetCursorLine()
	self:UpdateFontText()
	self:ResetCursor()
end

function ALittle.RichEdit:ClickWordCursor(offset_x, offset_y)
	local line_list = self._line_list
	self._line_cursor_it, self._char_cursor_it = self:GetIteratorByOffset(offset_x, offset_y)
	self._char_select_it = self._char_cursor_it
	self._line_select_it = self._line_cursor_it
	while true do
		local has_find = false
		while true do
			local str = line_list[self._line_cursor_it].char_list[self._char_cursor_it].text
			if str ~= nil and __len(str) == 1 and str ~= "_" and self:CharIsNumber(str) == false and self:CharIsLetter(str) == false then
				has_find = true
				break
			end
			if self._char_cursor_it == 1 then
				break
			end
			self._char_cursor_it = self._char_cursor_it - 1
		end
		if has_find then
			break
		end
		if self._line_cursor_it == 1 then
			break
		end
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = line_list[self._line_cursor_it].char_count + 1
		self._char_cursor_it = self._char_cursor_it - 1
	end
	local cursor_tmp = self._char_select_it
	local line_cursor_tmp = self._line_select_it
	while true do
		cursor_tmp = cursor_tmp + 1
		if cursor_tmp > line_list[self._line_select_it].char_count then
			line_cursor_tmp = line_cursor_tmp + 1
			if line_cursor_tmp > self._line_count then
				break
			end
			cursor_tmp = 1
		end
		local str = line_list[line_cursor_tmp].char_list[cursor_tmp].text
		if str ~= nil and __len(str) == 1 and str ~= "_" and self:CharIsNumber(str) == false and self:CharIsLetter(str) == false then
			break
		end
		self._char_select_it = cursor_tmp
		self._line_select_it = line_cursor_tmp
	end
	if self._line_select_it > self._line_count then
		self._line_select_it = self._line_select_it - 1
		self._char_select_it = line_list[self._line_select_it].char_count + 1
	end
	if self._char_select_it > line_list[self._line_select_it].char_count then
		self._char_select_it = self._char_select_it - 1
	end
	if self._line_select_it == self._line_cursor_it and self._char_select_it == self._char_cursor_it then
		self._char_select_it = line_list[self._line_select_it].char_count + 1
	end
	self:ResetCursorLine()
	self:UpdateFontText()
	self:ResetCursor()
	return self._char_select_it <= line_list[self._line_select_it].char_count
end

function ALittle.RichEdit:DragCursorBegin()
	local line_list = self._line_list
	self._line_select_it = self._line_cursor_it
	self._char_select_it = self._char_cursor_it
end

function ALittle.RichEdit:DragCursor(offset_x, offset_y)
	local line_list = self._line_list
	self._line_cursor_it, self._char_cursor_it = self:GetIteratorByOffset(offset_x, offset_y)
	if line_list[self._line_cursor_it].pre_height == -self._scroll_list.scroll_offset and self._line_cursor_it ~= 1 and offset_y < 0 then
		self._line_cursor_it = self._line_cursor_it - 1
		if self._char_cursor_it > line_list[self._line_cursor_it].char_count then
			self._char_cursor_it = line_list[self._line_cursor_it].char_count
		end
	end
	if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = line_list[self._line_cursor_it].char_count
	end
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:DragEdit(delta_y)
	local event = {}
	event.target = self._scroll_list
	event.delta_x = 0
	event.delta_y = delta_y
	self._scroll_list:HandleDrag(event)
	local line_list = self._line_list
	if line_list[self._line_start_it].acc_height <= -self._scroll_list.scroll_offset then
		self._line_start_it = self._line_start_it + 1
		while line_list[self._line_start_it].acc_height <= -self._scroll_list.scroll_offset do
			self._line_start_it = self._line_start_it + 1
		end
	elseif line_list[self._line_start_it].pre_height > -self._scroll_list.scroll_offset then
		self._line_start_it = self._line_start_it - 1
		while line_list[self._line_start_it].pre_height > -self._scroll_list.scroll_offset do
			self._line_start_it = self._line_start_it - 1
		end
	end
	self._start_it_delta = -self._scroll_list.scroll_offset - line_list[self._line_start_it].pre_height
	self:ResetCursor()
end

function ALittle.RichEdit:CheckMultiCursor(offset_x, offset_y, trans)
	local line_list = self._line_list
	local line_cursor_it
	local char_cursor_it
	if trans then
		line_cursor_it = self._line_cursor_it
		char_cursor_it = self._char_cursor_it
	else
		line_cursor_it, char_cursor_it = self:GetIteratorByOffset(offset_x, offset_y)
	end
	if char_cursor_it ~= 1 then
		self._line_cursor_it = line_cursor_it
		self._char_cursor_it = char_cursor_it
		self._line_select_it = line_cursor_it
		self._char_select_it = char_cursor_it - 1
	else
		if line_list[line_cursor_it].char_count > 1 then
			self._line_cursor_it = line_cursor_it
			self._char_cursor_it = char_cursor_it + 1
			self._line_select_it = line_cursor_it
			self._char_select_it = char_cursor_it
		else
			if line_cursor_it > 1 then
				self._line_cursor_it = line_cursor_it
				self._char_cursor_it = char_cursor_it
				self._line_select_it = line_cursor_it - 1
				self._char_select_it = line_list[self._line_select_it].char_count - 1
				if self._char_select_it == 0 then
					self._char_select_it = 1
				end
			else
				if self._line_count > 1 then
					self._line_cursor_it = line_cursor_it + 1
					if line_list[self._line_cursor_it].char_count == 1 then
						self._char_cursor_it = 1
					else
						self._char_cursor_it = 2
					end
					self._line_select_it = line_cursor_it
					self._char_select_it = char_cursor_it
				else
					return false
				end
			end
		end
	end
	return true
end

function ALittle.RichEdit:ClickMultiCursor()
	self:UpdateFontText()
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:DragMultiCursor(offset_x, offset_y)
	local line_list = self._line_list
	offset_x = offset_x + self._drag_delta_x
	offset_y = offset_y + self._drag_delta_y
	self._line_cursor_it, self._char_cursor_it = self:GetIteratorByOffset(offset_x, offset_y)
	if line_list[self._line_cursor_it].pre_height == -self._scroll_list.scroll_offset and self._line_cursor_it ~= 1 and offset_y < 0 then
		self._line_cursor_it = self._line_cursor_it - 1
		if self._char_cursor_it > line_list[self._line_cursor_it].char_count then
			self._char_cursor_it = line_list[self._line_cursor_it].char_count
		end
	end
	if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = line_list[self._line_cursor_it].char_count
	end
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:ShowDefaultText()
	if self._is_focus == false then
		if self._focus_cursor and self.is_empty then
			self._default_text_area.visible = true
		else
			self._default_text_area.visible = false
		end
	else
		self._default_text_area.visible = false
	end
end

function ALittle.RichEdit:CursorOffsetLRImpl(left)
	local line_list = self._line_list
	if left then
		if self._line_cursor_it == 1 and self._char_cursor_it == 1 then
			return
		end
		if self._line_cursor_it == self._line_start_it then
			if self._char_cursor_it == 1 then
				self._line_cursor_it = self._line_cursor_it - 1
				self._line_start_it = self._line_start_it - 1
				self._char_cursor_it = line_list[self._line_cursor_it].char_count + 1
				self._char_cursor_it = self._char_cursor_it - 1
			else
				self._char_cursor_it = self._char_cursor_it - 1
			end
		else
			if self._char_cursor_it == 1 then
				self._line_cursor_it = self._line_cursor_it - 1
				self._char_cursor_it = line_list[self._line_cursor_it].char_count + 1
				self._char_cursor_it = self._char_cursor_it - 1
			else
				self._char_cursor_it = self._char_cursor_it - 1
			end
		end
		if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
			self._line_cursor_it = self._line_cursor_it - 1
			self._char_cursor_it = line_list[self._line_cursor_it].char_count
		end
		self:ResetCursorLine()
		self:ResetCursor()
		return
	end
	local end_line_it = self._line_count + 1
	end_line_it = end_line_it - 1
	local end_char_it = line_list[end_line_it].char_count + 1
	end_char_it = end_char_it - 1
	if self._line_cursor_it == end_line_it and self._char_cursor_it == end_char_it then
		return
	end
	end_char_it = line_list[self._line_cursor_it].char_count + 1
	end_char_it = end_char_it - 1
	if self._char_cursor_it == end_char_it then
		self._line_cursor_it = self._line_cursor_it + 1
		self._char_cursor_it = 1
	else
		self._char_cursor_it = self._char_cursor_it + 1
	end
	if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = line_list[self._line_cursor_it].char_count
	end
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:CursorOffsetUDImpl(up)
	local line_list = self._line_list
	if up then
		if self._line_cursor_it == 1 then
			return
		end
		local offset_x = line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
		if self._line_cursor_it == self._line_start_it then
			self._line_start_it = self._line_start_it - 1
		end
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = 1
		local end_char_it = line_list[self._line_cursor_it].char_count + 1
		while self._char_cursor_it ~= end_char_it do
			if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width >= offset_x then
				break
			end
			self._char_cursor_it = self._char_cursor_it + 1
		end
		if self._char_cursor_it == end_char_it then
			end_char_it = end_char_it - 1
			self._char_cursor_it = end_char_it
		end
		if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
			self._line_cursor_it = self._line_cursor_it - 1
			self._char_cursor_it = line_list[self._line_cursor_it].char_count
		end
		self:ResetCursorLine()
		self:ResetCursor()
		return
	end
	local line_end_test_it = self._line_count + 1
	line_end_test_it = line_end_test_it - 1
	if self._line_cursor_it == line_end_test_it then
		self._char_cursor_it = line_list[self._line_cursor_it].char_count
		self:ResetCursorLine()
		self:ResetCursor()
		return
	end
	local offset_x = line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width
	self._line_cursor_it = self._line_cursor_it + 1
	self._char_cursor_it = 1
	local end_char_it = line_list[self._line_cursor_it].char_count + 1
	while self._char_cursor_it ~= end_char_it do
		if line_list[self._line_cursor_it].char_list[self._char_cursor_it].acc_width >= offset_x then
			break
		end
		self._char_cursor_it = self._char_cursor_it + 1
	end
	if self._char_cursor_it == end_char_it then
		end_char_it = end_char_it - 1
		self._char_cursor_it = end_char_it
	end
	if self._line_cursor_it == self._line_count and line_list[self._line_cursor_it].pre_height == line_list[self._line_cursor_it].acc_height and self._line_cursor_it ~= 1 then
		self._line_cursor_it = self._line_cursor_it - 1
		self._char_cursor_it = line_list[self._line_cursor_it].char_count
	end
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:GetIteratorByOffset(offset_x, offset_y)
	local line_list = self._line_list
	local line_it = self._line_start_it
	local line_end_it = self._line_count + 1
	local real_offset_y = offset_y + line_list[self._line_start_it].pre_height + self._start_it_delta
	while line_it ~= line_end_it do
		if real_offset_y <= line_list[line_it].acc_height then
			local half_line_height = (line_list[line_it].acc_height - line_list[line_it].pre_height) * 0.5
			if real_offset_y - line_list[line_it].acc_height > half_line_height then
				line_it = line_it + 1
			end
			break
		else
			line_it = line_it + 1
		end
	end
	if line_it == line_end_it then
		line_end_it = line_end_it - 1
		line_it = line_end_it
	end
	local line_it_result = line_it
	local real_offset_x = offset_x
	local char_it = 1
	local char_end_it = line_list[line_it].char_count + 1
	local line = line_list[line_it]
	while char_it ~= char_end_it do
		if real_offset_x <= line.char_list[char_it].acc_width then
			local half_char_width = (line.char_list[char_it].acc_width - line.char_list[char_it].pre_width) * 0.5
			if real_offset_x - line.char_list[char_it].pre_width < half_char_width and char_it ~= 1 then
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
	local char_it_result = char_it
	return line_it_result, char_it_result
end

function ALittle.RichEdit.__getter:is_input()
	return true
end

function ALittle.RichEdit.__getter:is_empty()
	return self._line_count == 1 and self._line_list[1].char_count == 1
end

function ALittle.RichEdit.__getter:editable()
	return self._editable
end

function ALittle.RichEdit.__setter:editable(value)
	self._editable = value
end

function ALittle.RichEdit.__setter:ims_padding(value)
	self._ims_padding = value
end

function ALittle.RichEdit.__getter:ims_padding()
	return self._ims_padding
end

function ALittle.RichEdit:SetCursor(rel_x, rel_y)
	if self._auto_ims then
		self:OpenIME()
	end
	self._is_selecting = false
	if self._multi_cursor then
		self._multi_cursor = false
		self._start_cursor.visible = false
		self._end_cursor.visible = false
		self._cursor.visible = true
		self:ClickCursor(rel_x - self._scroll_list.x, rel_y - self._scroll_list.y)
	else
		self:ClickCursor(rel_x - self._scroll_list.x, rel_y - self._scroll_list.y)
	end
end

function ALittle.RichEdit:SetMultiCursor(rel_x, rel_y)
	if self._auto_ims then
		self:OpenIME()
	end
	local result = self:CheckMultiCursor(rel_x - self._scroll_list.x, rel_y - self._scroll_list.y, false)
	if result == false then
		return false
	end
	self._is_selecting = true
	if self._multi_cursor == false then
		self._multi_cursor = true
		self._cursor.visible = false
		self._start_cursor.visible = true
		self._end_cursor.visible = true
		self:ClickMultiCursor()
	else
		self:ClickMultiCursor()
	end
	return true
end

function ALittle.RichEdit:TransToCursor()
	if self._multi_cursor == false then
		return
	end
	local line_list = self._line_list
	if self._end_cursor_data == "select" then
		self._line_cursor_it = self._line_select_it
		self._char_cursor_it = self._char_select_it
	end
	self._char_select_it = line_list[self._line_select_it].char_count + 1
	self._is_selecting = false
	self._multi_cursor = false
	self._start_cursor.visible = false
	self._end_cursor.visible = false
	self._cursor.visible = true
	self:UpdateFontText()
	self:ResetCursorLine()
	self:ResetCursor()
end

function ALittle.RichEdit:TransToMulti()
	if self._multi_cursor then
		return false
	end
	local result = self:CheckMultiCursor(nil, nil, true)
	if result == false then
		return false
	end
	self._is_selecting = true
	self._multi_cursor = true
	self._cursor.visible = false
	self._start_cursor.visible = true
	self._end_cursor.visible = true
	self:UpdateFontText()
	self:ResetCursorLine()
	self:ResetCursor()
	return true
end

function ALittle.RichEdit:OpenIME(x, y, width, height)
	if self._editable then
		self:ResetCursor()
		if x ~= nil and y ~= nil and width ~= nil and height ~= nil then
			ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height))
		else
			local global_x, global_y = self:LocalToGlobal()
			global_x = global_x + self.cursor_x
			global_y = global_y + (self.cursor_y + self.font_size) * self.scale_y
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + self._ims_padding))
		end
		ALittle.System_OpenIME()
	end
end

function ALittle.RichEdit:CloseIME()
	ALittle.System_CloseIME()
end

function ALittle.RichEdit:HandleFocusOut(event)
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

function ALittle.RichEdit:HandleFocusIn(event)
	if self._auto_ims then
		self:OpenIME()
	end
	self._is_focus = true
	if self._multi_cursor == false then
		self._cursor.visible = true
	end
	self:ShowDefaultText()
end

function ALittle.RichEdit:HandleLButtonDown(event)
	if self._multi_cursor == false then
		self._is_longclick = false
		if event.rel_x >= self._scroll_list.x and event.rel_x <= self._scroll_list.x + self._scroll_list.width and event.rel_y >= self._scroll_list.y and event.rel_y <= self._scroll_list.y + self._scroll_list.height then
			if event.count % 3 == 1 then
				self._is_selecting = false
				self:ClickCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
				self:DispatchEvent(___all_struct[-1053992999], {})
			elseif event.count % 3 == 2 then
				self._is_selecting = self:ClickWordCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
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
			if event.rel_x >= self._scroll_list.x and event.rel_x <= self._scroll_list.x + self._scroll_list.width and event.rel_y >= self._scroll_list.y and event.rel_y <= self._scroll_list.y + self._scroll_list.height then
				self._is_click = true
			end
		end
	end
end

function ALittle.RichEdit:HandleLButtonUp(event)
	if self._multi_cursor == true then
		if self._is_click and self._is_longclick == false and self._click_drag_delta_x < 2 and self._click_drag_delta_y < 2 then
			self._multi_cursor = false
			self._start_cursor.visible = false
			self._end_cursor.visible = false
			self._cursor.visible = true
			self:ClickCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
			self:DispatchEvent(___all_struct[-1053992999], {})
		end
	end
end

function ALittle.RichEdit:HandleLongLButtonDown(event)
	if self._is_click then
		if self.editable == false then
			local result = self:CheckMultiCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y, false)
			if result then
				self._is_selecting = true
				if self._multi_cursor == false then
					self._multi_cursor = true
					self._cursor.visible = false
					self._start_cursor.visible = true
					self._end_cursor.visible = true
					self:ClickMultiCursor()
				else
					self:ClickMultiCursor()
				end
			end
		else
			self._multi_cursor = false
			self._start_cursor.visible = false
			self._end_cursor.visible = false
			self._cursor.visible = true
			self:ClickCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
		end
		local e = {}
		e.target = self
		e.abs_x = event.abs_x
		e.abs_y = event.abs_y
		e.rel_x = event.rel_x
		e.rel_y = event.rel_y
		self:DispatchEvent(___all_struct[774620468], e)
		self._is_longclick = true
	end
end

function ALittle.RichEdit:CheckAtKeyInput(input_text)
	if input_text ~= "@" then
		return false
	end
	local line_list = self._line_list
	local line_cursor_it = self._line_cursor_it
	local char_cursor_it = self._char_cursor_it
	if self._line_cursor_it == 1 and self._char_cursor_it == 1 then
		self:DispatchEvent(___all_struct[1816229739], {})
		return true
	end
	if self._line_cursor_it > 1 and self._char_cursor_it == 1 then
		line_cursor_it = line_cursor_it - 1
		char_cursor_it = line_list[line_cursor_it].char_count
	end
	local char_info = line_list[self._line_cursor_it].char_list[self._char_cursor_it]
	local forward_text = char_info.text
	if forward_text == nil or not (self:CharIsNumber(forward_text) or self:CharIsLetter(forward_text)) then
		self:DispatchEvent(___all_struct[1816229739], {})
		return true
	end
	return false
end

function ALittle.RichEdit:HandleTextInput(event)
	if self._multi_cursor == false then
		if (self._editable or event.custom) then
			if self:CheckAtKeyInput(event.text) then
				return
			end
			self._is_selecting = false
			local is_change = self:InsertTextNative(event.text)
			if is_change then
				self:DispatchEvent(___all_struct[958494922], {})
				self:ShowDefaultText()
			end
		end
	else
		if self._is_selecting and self._editable then
			self._is_selecting = false
			local is_change = self:InsertTextNative(event.text)
			if is_change then
				self:DispatchEvent(___all_struct[958494922], {})
				self:ShowDefaultText()
			end
			self._multi_cursor = false
		end
	end
end

function ALittle.RichEdit:HandleDragBegin(event)
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
				local line_temp_it = self._line_select_it
				local char_temp_it = self._char_select_it
				self._line_select_it = self._line_cursor_it
				self._char_select_it = self._char_cursor_it
				self._line_cursor_it = line_temp_it
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
			self:DispatchEvent(___all_struct[9565867], {})
		elseif self._is_click then
			self._is_drag_begin = true
			self:DispatchEvent(___all_struct[9565867], {})
		else
			self._is_drag_begin = false
		end
	end
end

function ALittle.RichEdit:HandleDrag(event)
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
		self:DragCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
	else
		if self._is_click_cursor then
			self:DragMultiCursor(event.rel_x - self._scroll_list.x, event.rel_y - self._scroll_list.y)
		else
			if self._line_list[1] ~= nil and self._line_list[1].acc_height ~= self._line_list[1].pre_height then
				self._click_drag_delta_x = self._click_drag_delta_x + __abs(event.delta_x)
				self._click_drag_delta_y = self._click_drag_delta_y + __abs(event.delta_y)
				self:DragEdit(event.delta_y)
			end
		end
		self:DispatchEvent(___all_struct[291295687], {})
	end
end

function ALittle.RichEdit:HandleDragEnd(event)
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
		self:DispatchEvent(___all_struct[-203792390], {})
	end
end

function ALittle.RichEdit:HandleMButtonWheel(event)
	if self._multi_cursor == false then
		if event.delta_y > 0 then
			self._is_selecting = false
			self:CursorOffsetUD(true)
		elseif event.delta_y < 0 then
			self._is_selecting = false
			self:CursorOffsetUD(false)
		end
		if event.delta_x > 0 then
			self._is_selecting = false
			self:SelectCursorOffsetLR(true)
		elseif event.delta_x < 0 then
			self._is_selecting = false
			self:SelectCursorOffsetLR(false)
		end
	else
		self:DragEdit(event.delta_y)
	end
end

function ALittle.RichEdit:HandleMoveIn(event)
	ALittle.System_SetEditCursor()
end

function ALittle.RichEdit:HandleMoveOut(event)
	ALittle.System_SetNormalCursor()
end

function ALittle.RichEdit:HandleKeyDown(event)
	local is_change = false
	if event.sym == 9 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:InsertTextNative("\t")
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:InsertTextNative("\t")
				event.handled = true
				self._multi_cursor = false
			end
		end
	elseif event.sym == 1073741904 then
		if self._multi_cursor == false then
			if event.mod & 0x0003 == 0 then
				self._is_selecting = false
				self:CursorOffsetLR(true)
				self:UpdateFontText()
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
				self:UpdateFontText()
			else
				self._is_selecting = true
				self:SelectCursorOffsetLR(false)
			end
		end
		event.handled = true
	elseif event.sym == 1073741906 then
		if self._multi_cursor == false then
			if event.mod & 0x0003 == 0 then
				self._is_selecting = false
				self:CursorOffsetUD(true)
				self:UpdateFontText()
			else
				self._is_selecting = true
				self:SelectCursorOffsetUD(true)
			end
		end
		event.handled = true
	elseif event.sym == 1073741905 then
		if self._multi_cursor == false then
			if event.mod & 0x0003 == 0 then
				self._is_selecting = false
				self:CursorOffsetUD(false)
				self:UpdateFontText()
			else
				self._is_selecting = true
				self:SelectCursorOffsetUD(false)
			end
		end
		event.handled = true
	elseif event.sym == 8 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:DeleteText(true)
				event.handled = true
				self:UpdateFontText()
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:DeleteText(true)
				event.handled = true
				self:UpdateFontText()
				self._multi_cursor = false
			end
		end
	elseif event.sym == 127 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:DeleteText(false)
				event.handled = true
				self:UpdateFontText()
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:DeleteText(false)
				event.handled = true
				self:UpdateFontText()
				self._multi_cursor = false
			end
		end
	elseif event.sym == 1073741898 then
		self._is_selecting = false
		self:SetCursorToHome()
		event.handled = true
		self:UpdateFontText()
	elseif event.sym == 1073741901 then
		self._is_selecting = false
		self:SetCursorToEnd()
		event.handled = true
		self:UpdateFontText()
	elseif event.sym == 13 or event.sym == 1073741912 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				is_change = self:InsertTextNative("\n")
				event.handled = true
				self:UpdateFontText()
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				is_change = self:InsertTextNative("\n")
				event.handled = true
				self:UpdateFontText()
				self._multi_cursor = false
			end
		end
	elseif event.sym == 120 and event.mod & 0x00c0 ~= 0 then
		if self._multi_cursor == false then
			if self._editable or event.custom then
				self._is_selecting = false
				local select_text = self:GetSelectText()
				if select_text[1] ~= nil then
					ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
					is_change = self:DeleteSelectText()
				end
				self:UpdateFontText()
				event.handled = true
			end
		else
			if self._is_selecting and self._editable then
				self._is_selecting = false
				local select_text = self:GetSelectText()
				if select_text[1] ~= nil then
					ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
					is_change = self:DeleteSelectText()
				end
				self:UpdateFontText()
				event.handled = true
				self._multi_cursor = false
			end
		end
	elseif event.sym == 99 and event.mod & 0x00c0 ~= 0 then
		local select_text = self:GetSelectText()
		if select_text[1] ~= nil then
			ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
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
				event.handled = true
				self._multi_cursor = false
			end
		end
	elseif event.sym == 97 and event.mod & 0x00c0 ~= 0 then
		self._is_selecting = true
		self:SelectAll()
		event.handled = true
	end
	if is_change then
		self:DispatchEvent(___all_struct[958494922], {})
		self._current_flash_alpha = 1.5
		self:ShowDefaultText()
	end
end

function ALittle.RichEdit:InsertText(display_list, selected)
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	self:InsertDisplayListNative(display_list, selected)
	self._multi_cursor = false
	self:ShowDefaultText()
end

function ALittle.RichEdit:InsertWord(word_text)
	if self._editable == false then
		return
	end
	if self._multi_cursor and self._is_selecting == false then
		return
	end
	self._is_selecting = false
	self:InsertTextNative(word_text)
	self:TransToCursor()
	self:ShowDefaultText()
end

function ALittle.RichEdit:CopyText(return_cursor)
	local select_text = self:GetSelectText()
	if select_text[1] ~= nil then
		ALittle.System_SetClipboardText(ALittle.String_JsonEncode(select_text))
	end
	if return_cursor then
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichEdit:CopyWord(return_cursor)
	local select_text = self:GetSelectWord()
	if select_text ~= nil then
		ALittle.System_SetClipboardText(select_text)
	end
	if return_cursor then
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichEdit:CutText()
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
		self:UpdateFontText()
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichEdit:CutWord()
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
		self:UpdateFontText()
		self:TransToCursor()
	end
	self:ShowDefaultText()
end

function ALittle.RichEdit:PasteText()
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

function ALittle.RichEdit:PasteWord()
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

function ALittle.RichEdit:Clear()
	self:ClearText()
	self:ShowDefaultText()
end

function ALittle.RichEdit:Delete()
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

end