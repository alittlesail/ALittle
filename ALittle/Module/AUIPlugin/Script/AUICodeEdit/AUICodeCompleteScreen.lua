-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name = "lua.ABnfQueryCompleteInfo", ns_name = "lua", rl_name = "ABnfQueryCompleteInfo", hash_code = -1149003083,
name_list = {"display","insert","descriptor","tag"},
type_list = {"string","string","string","int"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1773085126, "AUIPlugin.AUICodeCompleteItemInfo", {
name = "AUIPlugin.AUICodeCompleteItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeCompleteItemInfo", hash_code = 1773085126,
name_list = {"_item_button","_item_title","_tag_image","_item","pos","upper","complete"},
type_list = {"ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","int","string","lua.ABnfQueryCompleteInfo"},
option_map = {}
})

AUICodeCompleteScreen = Lua.Class(nil, "AUIPlugin.AUICodeCompleteScreen")

function AUICodeCompleteScreen:Ctor()
	___rawset(self, "_item_pool", {})
	___rawset(self, "_item_pool_count", 0)
	___rawset(self, "_item_height", 0)
end

function AUICodeCompleteScreen.__getter:edit()
	return self._edit
end

function AUICodeCompleteScreen:Shutdown()
	self:Hide()
end

function AUICodeCompleteScreen:ShowComplete(edit)
	self._edit = edit
	if self._complete == nil then
		if not self:ReInit(edit) then
			self:Hide()
			return
		end
	end
	self._line_end = edit.cursor.line
	self._char_end = edit.cursor.char
	local text = edit:GetTargetText(self._complete.line_start, self._complete.char_start - 1, edit.cursor.line, edit.cursor.char)
	if text == nil or text == "" then
		self:Hide()
		return
	end
	if not self:Fliter(text) then
		self:Hide()
		self._edit = edit
		if not self:ReInit(edit) then
			return
		end
		self._line_end = edit.cursor.line
		self._char_end = edit.cursor.char
		text = edit:GetTargetText(self._complete.line_start, self._complete.char_start - 1, edit.cursor.line, edit.cursor.char)
		if text == nil or text == "" then
			return
		end
		if not self:Fliter(text) then
			self:Hide()
		end
	end
end
AUICodeCompleteScreen.ShowComplete = Lua.CoWrap(AUICodeCompleteScreen.ShowComplete)

function AUICodeCompleteScreen:IsShow()
	return self._complete ~= nil
end

function AUICodeCompleteScreen:SelectUp()
	local target = self:GetSelectIndex()
	target = target - (1)
	if target < 1 then
		return
	end
	local item = self._screen.childs[target]
	local info = item._user_data
	info._item_button.selected = true
	if info.complete.descriptor ~= nil then
		self:ShowTip(info.complete.descriptor)
	else
		self:HideTip()
	end
	local delta = self._screen.container.height - self._screen.height
	if delta > 0 then
		local offset = (target - 1) * self._item_height + self._screen.container_y
		if offset < 0 then
			self._screen.right_scrollbar.offset_rate = ((target - 1) * self._item_height) / delta
			self._screen:RejustScrollBar()
		end
	end
end

function AUICodeCompleteScreen:SelectDown()
	local target = self:GetSelectIndex()
	target = target + (1)
	if target > self._screen.child_count then
		return
	end
	local item = self._screen.childs[target]
	local info = item._user_data
	info._item_button.selected = true
	if info.complete.descriptor ~= nil then
		self:ShowTip(info.complete.descriptor)
	else
		self:HideTip()
	end
	local delta = self._screen.container.height - self._screen.height
	if delta > 0 then
		local offset = target * self._item_height + self._screen.container_y
		if offset > self._screen.height then
			self._screen.right_scrollbar.offset_rate = (target * self._item_height - self._screen.height) / delta
			self._screen:RejustScrollBar()
		end
	end
end

function AUICodeCompleteScreen:DoSelect()
	local target = self:GetSelectIndex()
	if target == nil then
		return false
	end
	self._edit.select_cursor:StartLineChar(self._complete.line_start, self._complete.char_start - 1)
	self._edit.select_cursor:UpdateLineChar(self._edit.cursor.line, self._edit.cursor.char)
	local item = self._screen.childs[target]
	local text
	local complete = item._user_data.complete
	if complete.insert ~= nil then
		text = complete.insert
	else
		text = complete.display
	end
	local result = self._edit:InsertText(text, true)
	self:Hide()
	return result
end

function AUICodeCompleteScreen:GetSelectIndex()
	local target = nil
	for index, child in ___ipairs(self._screen.childs) do
		if child._user_data._item_button.selected then
			target = index
			break
		end
	end
	return target
end

function AUICodeCompleteScreen:ReInit(edit)
	local ___COROUTINE = coroutine.running()
	if edit.language == nil then
		return false
	end
	self._complete = edit.language:QueryComplete(edit.cursor.line, edit.cursor.char - 1)
	if self._complete == nil then
		return false
	end
	local x, y = edit:CalcAbsPosition(self._complete.line_start, self._complete.char_start, true)
	y = y + (edit.line_height)
	if self._screen == nil then
		self._screen = g_Control:CreateControl("ide_code_scroll_screen")
		self._screen.width = 200
		self._screen:AddEventListener(___all_struct[348388800], self, self.HandleHideEvent)
	end
	self._screen:RemoveAllChild()
	self._screen.x = x
	self._screen.y = y
	if self._item_list ~= nil then
		for index, info in ___ipairs(self._item_list) do
			self._item_pool_count = self._item_pool_count + (1)
			self._item_pool[self._item_pool_count] = info
		end
	end
	local max_width = 200.0
	self._item_group = {}
	self._item_list = {}
	for index, info in ___ipairs(self._complete.complete_list) do
		local item_info
		if self._item_pool_count > 0 then
			item_info = self._item_pool[self._item_pool_count]
			self._item_pool[self._item_pool_count] = nil
			self._item_pool_count = self._item_pool_count - (1)
		else
			item_info = {}
			item_info._item = g_Control:CreateControl("ide_code_complete_item", item_info)
		end
		item_info._item_button.group = self._item_group
		item_info._item_title.text = info.display
		if info.insert == nil then
			item_info.upper = ALittle.String_Upper(info.display)
		else
			item_info.upper = ALittle.String_Upper(info.insert)
		end
		item_info._tag_image.texture_name = edit.language:QueryCompleteIcon(info.tag)
		item_info._item._user_data = item_info
		item_info.complete = info
		self._item_list[index] = item_info
		local title_wdith = edit.ascii_width * ALittle.String_Len(info.display)
		if max_width < title_wdith then
			max_width = title_wdith
		end
		self._item_height = item_info._item.height
	end
	self._screen.width = max_width
	A_LayerManager:ShowFromRight(self._screen, false)
	return true
end

function AUICodeCompleteScreen.ItemInfoSort(a, b)
	return a.pos < b.pos
end

function AUICodeCompleteScreen:Fliter(text)
	local descriptor
	local upper = ALittle.String_Upper(text)
	local sort_list = {}
	local count = 0
	self._screen:RemoveAllChild()
	for index, info in ___ipairs(self._item_list) do
		info.pos = ALittle.String_Find(info.upper, upper)
		if info.pos ~= nil then
			count = count + 1
			sort_list[count] = info
		end
	end
	ALittle.List_Sort(sort_list, AUICodeCompleteScreen.ItemInfoSort)
	count = 0
	for index, info in ___ipairs(sort_list) do
		if self._screen.child_count == 0 then
			info._item_button.selected = true
			descriptor = info.complete.descriptor
		end
		self._screen:AddChild(info._item)
		if count >= 50 then
			break
		end
	end
	if self._screen.child_count == 0 then
		return false
	end
	local height = self._screen.child_count * self._item_height
	if height < 200 then
		self._screen.height = height
	else
		self._screen.height = 200
	end
	if descriptor ~= nil then
		self:ShowTip(descriptor)
	else
		self:HideTip()
	end
	return true
end

function AUICodeCompleteScreen:Hide()
	self:HideTip()
	self._edit = nil
	self._complete = nil
	if self._screen ~= nil then
		self._screen:RemoveAllChild()
	end
	A_LayerManager:HideFromRight(self._screen)
end

function AUICodeCompleteScreen:TryHide(edit)
	if self._edit ~= edit then
		return
	end
	if edit.cursor.line < self._complete.line_start or edit.cursor.line > self._line_end then
		self:Hide()
		return
	end
	if edit.cursor.line == self._complete.line_start and edit.cursor.char < self._complete.char_start then
		self:Hide()
		return
	end
	if edit.cursor.line == self._line_end and edit.cursor.char > self._char_end then
		self:Hide()
		return
	end
end

function AUICodeCompleteScreen:HandleHideEvent(event)
	self:HideTip()
	self._edit = nil
	self._complete = nil
end

function AUICodeCompleteScreen:ShowTip(content)
	if self._tip_dialog == nil then
		self._tip_dialog = g_Control:CreateControl("ide_tool_area_tip", self)
		self._tip_dialog.width = 200
	end
	A_LayerManager:AddToTip(self._tip_dialog)
	self._tip_dialog.visible = true
	self._tip_text.text = content
	self._tip_dialog.height = self._tip_text.real_height + 6
	self._tip_dialog.x = self._screen.x
	self._tip_dialog.y = self._screen.y + self._screen.height
end

function AUICodeCompleteScreen:HideTip()
	if self._tip_dialog == nil then
		return
	end
	self._tip_dialog.visible = false
	A_LayerManager:RemoveFromTip(self._tip_dialog)
end

g_AUICodeCompleteScreen = AUICodeCompleteScreen()
