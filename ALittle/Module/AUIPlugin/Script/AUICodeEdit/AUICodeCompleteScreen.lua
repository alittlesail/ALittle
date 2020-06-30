-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1773085126, "AUIPlugin.AUICodeCompleteItemInfo", {
name = "AUIPlugin.AUICodeCompleteItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeCompleteItemInfo", hash_code = 1773085126,
name_list = {"_item_button","_item_title","_tag_image","_item"},
type_list = {"ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

AUICodeCompleteScreen = Lua.Class(nil, "AUIPlugin.AUICodeCompleteScreen")

function AUICodeCompleteScreen.__getter:edit()
	return self._edit
end

function AUICodeCompleteScreen:ShowComplete(edit)
	self._edit = edit
	if self._complete == nil then
		self._line_start = edit.cursor.line
		self._char_start = edit.cursor.char - 1
		self:ReInit(edit)
	end
	self._line_end = edit.cursor.line
	self._char_end = edit.cursor.char
	local text = edit:GetTargetText(self._line_start, self._char_start, edit.cursor.line, edit.cursor.char)
	if text == "" then
		self:Hide()
		return
	end
	self:Fliter(text)
end

function AUICodeCompleteScreen:IsShow()
	return self._complete ~= nil
end

function AUICodeCompleteScreen:ReInit(edit)
	self._complete = edit.language:QueryComplete(self._line_start, self._char_start)
	if self._complete == nil then
		return
	end
	local x, y = edit:CalcAbsPosition(self._complete.line_start, self._complete.char_start)
	y = y + (edit.line_height)
	if self._screen == nil then
		self._screen = g_Control:CreateControl("ide_code_scroll_screen")
		self._screen.width = 200
		self._screen:AddEventListener(___all_struct[348388800], self, self.HandleHideEvent)
	end
	self._screen.x = x
	self._screen.y = y
	self._item_group = {}
	self._item_list = {}
	for index, info in ___ipairs(self._complete.complete_list) do
		local item_info = {}
		item_info._item = g_Control:CreateControl("ide_code_complete_item", item_info)
		item_info._item_button.group = self._item_group
		item_info._item_title.text = info.complete
		item_info._tag_image.texture_name = edit.language:QueryCompleteIcon(info.tag)
		self._item_list[index] = item_info
		self._item_height = item_info._item.height
	end
	A_LayerManager:ShowFromRight(self._screen, false)
end

function AUICodeCompleteScreen:Fliter(text)
	if text == nil then
		text = ""
	end
	self._screen:RemoveAllChild()
	for index, info in ___ipairs(self._item_list) do
		local pos = ALittle.String_Find(info._item_title.text, text)
		if pos ~= nil then
			if self._screen.child_count == 0 then
				info._item_button.selected = true
			end
			self._screen:AddChild(info._item)
		end
	end
	local height = self._screen.child_count * self._item_height
	if height < 200 then
		self._screen.height = height
	else
		self._screen.height = 200
	end
end

function AUICodeCompleteScreen:Hide()
	self._edit = nil
	self._complete = nil
	A_LayerManager:HideFromRight(self._screen)
end

function AUICodeCompleteScreen:TryHide(edit)
	if self._edit ~= edit then
		return
	end
	if edit.cursor.line < self._line_start or edit.cursor.line > self._line_end then
		self:Hide()
		return
	end
	if edit.cursor.line == self._line_start and edit.cursor.char < self._char_start then
		self:Hide()
		return
	end
	if edit.cursor.line == self._line_end and edit.cursor.char > self._char_end then
		self:Hide()
		return
	end
end

function AUICodeCompleteScreen:HandleHideEvent(event)
	self._edit = nil
	self._complete = nil
end

g_AUICodeCompleteScreen = AUICodeCompleteScreen()
