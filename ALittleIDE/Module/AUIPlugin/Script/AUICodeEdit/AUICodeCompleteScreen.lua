-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1773085126, "AUIPlugin.AUICodeCompleteItemInfo", {
name = "AUIPlugin.AUICodeCompleteItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeCompleteItemInfo", hash_code = 1773085126,
name_list = {"_item_button","_item_title","_tag_image","_item","pos","upper","complete"},
type_list = {"ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","List<int>","string","lua.ABnfQueryCompleteInfo"},
option_map = {}
})
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name = "lua.ABnfQueryCompleteInfo", ns_name = "lua", rl_name = "ABnfQueryCompleteInfo", hash_code = -1149003083,
name_list = {"display","insert","descriptor","tag"},
type_list = {"string","string","string","int"},
option_map = {}
})

AUIPlugin.AUICodeCompleteScreen = Lua.Class(nil, "AUIPlugin.AUICodeCompleteScreen")

function AUIPlugin.AUICodeCompleteScreen:Ctor(edit)
	___rawset(self, "_item_pool", {})
	___rawset(self, "_item_pool_count", 0)
	___rawset(self, "_item_height", 0)
	___rawset(self, "_edit", edit)
end

function AUIPlugin.AUICodeCompleteScreen:ShowComplete()
	if self._complete == nil then
		if not self:ReInit() then
			self:Hide()
			return
		end
	end
	self._line_end = self._edit.cursor.line
	self._char_end = self._edit.cursor.char
	local text = self._edit:GetTargetText(self._complete.line_start, self._complete.char_start - 1, self._edit.cursor.line, self._edit.cursor.char)
	if text == nil or text == "" then
		self:Hide()
		return
	end
	if not self:Fliter(text) then
		self:Hide()
		if not self:ReInit() then
			return
		end
		self._line_end = self._edit.cursor.line
		self._char_end = self._edit.cursor.char
		text = self._edit:GetTargetText(self._complete.line_start, self._complete.char_start - 1, self._edit.cursor.line, self._edit.cursor.char)
		if text == nil or text == "" then
			return
		end
		if not self:Fliter(text) then
			self:Hide()
		end
	end
end
AUIPlugin.AUICodeCompleteScreen.ShowComplete = Lua.CoWrap(AUIPlugin.AUICodeCompleteScreen.ShowComplete)

function AUIPlugin.AUICodeCompleteScreen:IsShow()
	return self._complete ~= nil
end

function AUIPlugin.AUICodeCompleteScreen:SelectUp()
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
			self._screen:AdjustScrollBar()
		end
	end
end

function AUIPlugin.AUICodeCompleteScreen:SelectDown()
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
			self._screen:AdjustScrollBar()
		end
	end
end

function AUIPlugin.AUICodeCompleteScreen:DoSelect()
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

function AUIPlugin.AUICodeCompleteScreen:GetSelectIndex()
	local target = nil
	for index, child in ___ipairs(self._screen.childs) do
		if child._user_data._item_button.selected then
			target = index
			break
		end
	end
	return target
end

function AUIPlugin.AUICodeCompleteScreen:ReInit()
	local ___COROUTINE = coroutine.running()
	if self._edit.language == nil then
		return false
	end
	self._complete = self._edit.language:QueryComplete(self._edit.cursor.line, self._edit.cursor.char - 1)
	if self._complete == nil then
		return false
	end
	local x, y = self._edit:CalcPosition(self._complete.line_start, self._complete.char_start, true)
	y = y + (AUIPlugin.CODE_LINE_HEIGHT)
	if self._screen == nil then
		self._screen = AUIPlugin.g_Control:CreateControl("code_scroll_screen")
		self._screen.width = 200
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
			item_info._item = AUIPlugin.g_Control:CreateControl("code_complete_item", item_info)
		end
		item_info._item_button.group = self._item_group
		item_info._item_title.text = info.display
		if info.insert == nil then
			item_info.upper = ALittle.String_Upper(info.display)
		else
			item_info.upper = ALittle.String_Upper(info.insert)
		end
		item_info._tag_image.texture_name = self._edit.language:QueryCompleteIcon(info.tag)
		item_info._item._user_data = item_info
		item_info.complete = info
		self._item_list[index] = item_info
		local title_wdith = item_info._item_title.width + item_info._item_title.x + 5
		if max_width < title_wdith then
			max_width = title_wdith
		end
		self._item_height = item_info._item.height
	end
	self._screen.width = max_width + self._screen.right_scrollbar.width
	self._edit.help_container:AddChild(self._screen)
	return true
end

function AUIPlugin.AUICodeCompleteScreen.ItemInfoSort(a, b)
	for index, pos in ___ipairs(a.pos) do
		if b.pos[index] == nil then
			return true
		end
		if pos ~= b.pos[index] then
			return pos < b.pos[index]
		end
	end
	return false
end

function AUIPlugin.AUICodeCompleteScreen:Fliter(text)
	local upper_text = ALittle.String_Upper(text)
	local first_split = ALittle.String_Find(upper_text, "_")
	if first_split == nil then
		first_split = 1
	else
		first_split = first_split + (1)
	end
	local upper_list = ALittle.String_Split(upper_text, "_", first_split)
	if first_split > 1 then
		ALittle.List_Insert(upper_list, 1, ALittle.String_Sub(upper_text, 1, first_split - 1))
	end
	local upper_list_count = ALittle.List_Len(upper_list)
	if upper_list_count > 1 and upper_list[upper_list_count] == "" then
		upper_list[upper_list_count] = nil
	end
	local sort_list = {}
	local count = 0
	self._screen:RemoveAllChild()
	for index, info in ___ipairs(self._item_list) do
		info.pos = nil
		local pos = 1
		for _, upper in ___ipairs(upper_list) do
			pos = ALittle.String_Find(info.upper, upper, pos)
			if pos ~= nil then
				if info.pos == nil then
					info.pos = {}
					count = count + 1
					sort_list[count] = info
				end
				ALittle.List_Push(info.pos, pos)
			end
		end
	end
	ALittle.List_Sort(sort_list, AUIPlugin.AUICodeCompleteScreen.ItemInfoSort)
	count = 0
	local descriptor
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

function AUIPlugin.AUICodeCompleteScreen:Hide()
	self:HideTip()
	self._complete = nil
	if self._screen ~= nil then
		self._screen:RemoveAllChild()
	end
	self._edit.help_container:RemoveChild(self._screen)
end

function AUIPlugin.AUICodeCompleteScreen:TryHide()
	if self._complete == nil then
		return
	end
	if self._edit.cursor.line < self._complete.line_start or self._edit.cursor.line > self._line_end then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._complete.line_start and self._edit.cursor.char < self._complete.char_start then
		self:Hide()
		return
	end
	if self._edit.cursor.line == self._line_end and self._edit.cursor.char > self._char_end then
		self:Hide()
		return
	end
end

function AUIPlugin.AUICodeCompleteScreen:ShowTip(content)
	if self._tip_dialog == nil then
		self._tip_dialog = AUIPlugin.g_Control:CreateControl("code_area_tip", self)
		self._tip_dialog.width = 200
	end
	self._edit.help_container:AddChild(self._tip_dialog)
	self._tip_dialog.visible = true
	self._tip_text.text = content
	self._tip_dialog.height = self._tip_text.real_height + 16
	self._tip_dialog.x = self._screen.x + self._screen.width
	self._tip_dialog.y = self._screen.y
	if self._tip_dialog.x + self._tip_dialog.width > A_UISystem.view_width then
		self._tip_dialog.x = self._screen.x
		self._tip_dialog.y = self._screen.y + self._screen.height
	end
end

function AUIPlugin.AUICodeCompleteScreen:HideTip()
	if self._tip_dialog == nil then
		return
	end
	self._tip_dialog.visible = false
	self._edit.help_container:RemoveChild(self._tip_dialog)
end

end