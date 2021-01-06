-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1275923985, "AUIPlugin.AUICodeParamItemInfo", {
name = "AUIPlugin.AUICodeParamItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeParamItemInfo", hash_code = -1275923985,
name_list = {"text_list"},
type_list = {"List<ALittle.DisplayObject>"},
option_map = {}
})

AUIPlugin.AUICodeParamList = Lua.Class(nil, "AUIPlugin.AUICodeParamList")

function AUIPlugin.AUICodeParamList:Ctor(edit)
	___rawset(self, "_edit", edit)
end

function AUIPlugin.AUICodeParamList:ShowParamList()
	if self._param_info == nil then
		if not self:ReInit() then
			self:Hide()
			return
		end
	end
	local param_index, start_offset = self._edit.language:QueryParamIndex(self._edit.cursor.line, self._edit.cursor.char - 1)
	if param_index < 1 then
		self:Hide()
		return
	end
	if self._start_offset == nil then
		self._start_offset = start_offset
	elseif self._start_offset ~= start_offset then
		self:Hide()
		if not self:ReInit() then
			self:Hide()
			return
		end
		self._start_offset = start_offset
	end
	if self._param_index == param_index then
		return
	end
	if param_index > self._param_count then
		self:Hide()
		return
	end
	local item_info = self._item_list[self._param_index]
	if item_info ~= nil then
		for index, text in ___ipairs(item_info.text_list) do
			text.red = AUIPlugin.CODE_PARAMLIST_RED
			text.green = AUIPlugin.CODE_PARAMLIST_GREEN
			text.blue = AUIPlugin.CODE_PARAMLIST_BLUE
		end
	end
	self._param_index = param_index
	item_info = self._item_list[self._param_index]
	if item_info ~= nil then
		for index, text in ___ipairs(item_info.text_list) do
			text.red = AUIPlugin.CODE_PARAMLIST_FOCUS_RED
			text.green = AUIPlugin.CODE_PARAMLIST_FOCUS_GREEN
			text.blue = AUIPlugin.CODE_PARAMLIST_FOCUS_BLUE
		end
	end
end
AUIPlugin.AUICodeParamList.ShowParamList = Lua.CoWrap(AUIPlugin.AUICodeParamList.ShowParamList)

function AUIPlugin.AUICodeParamList:IsShow()
	return self._param_info ~= nil
end

function AUIPlugin.AUICodeParamList:ReInit()
	local ___COROUTINE = coroutine.running()
	if self._edit.language == nil then
		return false
	end
	self._param_info = self._edit.language:QueryParamList(self._edit.cursor.line, self._edit.cursor.char - 1)
	if self._param_info == nil then
		return false
	end
	self._param_count = ALittle.List_Len(self._param_info.param_list)
	if self._param_count == 0 then
		return false
	end
	local x, y = self._edit:CalcPosition(self._param_info.line_start, self._param_info.char_start, true)
	if self._dialog == nil then
		self._dialog = AUIPlugin.g_Control:CreateControl("code_paramlist_tip", self)
		self._dialog.width = 200
		self._dialog.height = AUIPlugin.CODE_LINE_HEIGHT + self._text_container.height_value
	end
	y = y - (self._dialog.height)
	self._text_container:RemoveAllChild()
	self._dialog.x = x
	self._dialog.y = y
	self._item_list = {}
	self._param_index = 0
	local offset = 0.0
	local param_len = ALittle.List_Len(self._param_info.param_list)
	for param_index, param in ___ipairs(self._param_info.param_list) do
		local info = {}
		info.text_list = {}
		local text_count = 0
		local param_name = param.name
		if param_index ~= param_len then
			param_name = param_name .. ", "
		end
		local text_list = ALittle.String_SplitUTF8(param_name)
		for index, char in ___ipairs(text_list) do
			if char == "\t" then
				offset = offset + (self._edit.ascii_width * 4)
			elseif char == " " then
				offset = offset + (self._edit.ascii_width)
			elseif char ~= "\r" and char ~= "\n" then
				local is_asicc = true
				do
					local byte_count = carp.UTF8ByteCount(char, 0, 1)
					if byte_count > 1 then
						is_asicc = false
					end
				end
				local text = ALittle.Text(AUIPlugin.g_Control)
				text.red = AUIPlugin.CODE_PARAMLIST_RED
				text.green = AUIPlugin.CODE_PARAMLIST_GREEN
				text.blue = AUIPlugin.CODE_PARAMLIST_BLUE
				text.text = char
				text.x = offset
				text.font_path = AUIPlugin.CODE_FONT_PATH
				text.font_size = AUIPlugin.CODE_FONT_SIZE
				self._text_container:AddChild(text)
				if is_asicc then
					offset = offset + (self._edit.ascii_width)
				else
					offset = offset + (self._edit.word_width)
				end
				text_count = text_count + 1
				info.text_list[text_count] = text
			end
		end
		self._item_list[param_index] = info
	end
	self._dialog.width = offset + self._text_container.width_value
	self._edit.help_container:AddChild(self._dialog)
	return true
end

function AUIPlugin.AUICodeParamList:Hide()
	self._param_info = nil
	self._start_offset = nil
	self._param_count = 0
	self._param_index = 0
	self._edit.help_container:RemoveChild(self._dialog)
end

function AUIPlugin.AUICodeParamList:TryHide()
	if self._param_info == nil then
		return
	end
	if self._edit.cursor.line < self._param_info.line_start or self._edit.cursor.line > self._param_info.line_end then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._param_info.line_start and self._edit.cursor.char < self._param_info.char_start then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._param_info.line_end and self._edit.cursor.char > self._param_info.char_end then
		self:Hide()
		return
	end
end

end