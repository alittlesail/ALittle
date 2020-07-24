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
ALittle.RegStruct(-1275923985, "AUIPlugin.AUICodeParamItemInfo", {
name = "AUIPlugin.AUICodeParamItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeParamItemInfo", hash_code = -1275923985,
name_list = {"text_list"},
type_list = {"List<ALittle.DisplayObject>"},
option_map = {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

AUICodeSigntruetureHelp = Lua.Class(nil, "AUIPlugin.AUICodeSigntruetureHelp")

function AUICodeSigntruetureHelp:Ctor(edit)
	___rawset(self, "_edit", edit)
end

function AUICodeSigntruetureHelp:Shutdown()
	self:Hide()
end

function AUICodeSigntruetureHelp:ShowSigntureHelp()
	if self._signture_help == nil then
		if not self:ReInit() then
			self:Hide()
			return
		end
	end
	self._line_start = self._edit.cursor.line
	self._char_start = self._edit.cursor.char
	local text = self._edit:GetTargetText(self._signture_help.line_start, self._signture_help.char_start - 1, self._edit.cursor.line, self._edit.cursor.char)
	if text == nil or text == "" then
		self:Hide()
		return
	end
	if not self:Fliter(0, 0) then
		self:Hide()
		if not self:ReInit() then
			return
		end
		self._line_start = self._edit.cursor.line
		self._char_start = self._edit.cursor.char
		text = self._edit:GetTargetText(self._signture_help.line_start, self._signture_help.char_start - 1, self._edit.cursor.line, self._edit.cursor.char)
		if text == nil or text == "" then
			return
		end
		if not self:Fliter(0, 0) then
			self:Hide()
		end
	end
end
AUICodeSigntruetureHelp.ShowSigntureHelp = Lua.CoWrap(AUICodeSigntruetureHelp.ShowSigntureHelp)

function AUICodeSigntruetureHelp:IsShow()
	return self._signture_help ~= nil
end

function AUICodeSigntruetureHelp:ReInit()
	local ___COROUTINE = coroutine.running()
	if self._edit.language == nil then
		return false
	end
	self._signture_help = self._edit.language:QuerySigntureHelp(self._edit.cursor.line, self._edit.cursor.char - 1)
	if self._signture_help == nil then
		return false
	end
	local x, y = self._edit:CalcPosition(self._signture_help.line_start, self._signture_help.char_start, true)
	y = y + (CODE_LINE_HEIGHT)
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_tool_signture_tip")
		self._dialog.width = 200
		self._dialog:AddEventListener(___all_struct[348388800], self, self.HandleHideEvent)
	end
	self._text_container:RemoveAllChild()
	self._dialog.x = x
	self._dialog.y = y
	self._item_list = {}
	local offset = 0.0
	for param_index, param in ___ipairs(self._signture_help.param_list) do
		local info = {}
		info.text_list = {}
		local text_count = 0
		local text_list = ALittle.String_SplitUTF8(param.name)
		local len = ALittle.List_MaxN(text_list)
		local index = len
		while true do
			if not(index >= 1) then break end
			local char = text_list[index]
			if char == "\t" then
				offset = offset + (self._edit.ascii_width * 4)
			elseif char == " " then
				offset = offset + (self._edit.ascii_width)
			elseif char ~= "\r" and char ~= "\n" then
				local is_asicc = true
				do
					local byte_count = utf8.bytecount(char, 0, 1)
					if byte_count > 1 then
						is_asicc = false
					end
				end
				local text = ALittle.Text(g_Control)
				text.red = CODE_SIGNTURE_RED
				text.green = CODE_SIGNTURE_GREEN
				text.blue = CODE_SIGNTURE_BLUE
				text.text = char
				text.x = offset
				text.font_path = CODE_FONT_PATH
				text.font_size = CODE_FONT_SIZE
				self._text_container:AddChild(text)
				if is_asicc then
					offset = offset + (self._edit.ascii_width)
				else
					offset = offset + (self._edit.word_width)
				end
				text_count = text_count + 1
				info.text_list[text_count] = text
			end
			index = index+(-1)
		end
		self._item_list[param_index] = info
	end
	self._dialog.width = offset
	A_LayerManager:ShowFromRight(self._dialog, false)
	return true
end

function AUICodeSigntruetureHelp:Fliter(line, char)
	local sort_list = {}
	local count = 0
	return true
end

function AUICodeSigntruetureHelp:Hide()
	self._signture_help = nil
	self._edit.help_container:RemoveChild(self._dialog)
end

function AUICodeSigntruetureHelp:TryHide()
	if self._signture_help == nil then
		return
	end
	if self._edit.cursor.line < self._signture_help.line_start or self._edit.cursor.line > self._line_start then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._signture_help.line_start and self._edit.cursor.char < self._signture_help.char_start then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._line_start and self._edit.cursor.char > self._char_start then
		self:Hide()
		return
	end
end

function AUICodeSigntruetureHelp:HandleHideEvent(event)
	self._edit = nil
	self._signture_help = nil
end

