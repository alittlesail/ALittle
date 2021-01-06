-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(-1149003083, "lua.ABnfQueryCompleteInfo", {
name = "lua.ABnfQueryCompleteInfo", ns_name = "lua", rl_name = "ABnfQueryCompleteInfo", hash_code = -1149003083,
name_list = {"display","insert","descriptor","tag"},
type_list = {"string","string","string","int"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-352292202, "AUIPlugin.AUICodeFilterItemInfo", {
name = "AUIPlugin.AUICodeFilterItemInfo", ns_name = "AUIPlugin", rl_name = "AUICodeFilterItemInfo", hash_code = -352292202,
name_list = {"_item_button","_item_title","_tag_image","_item","pos","upper","complete"},
type_list = {"ALittle.TextRadioButton","ALittle.Text","ALittle.Image","ALittle.DisplayObject","int","string","lua.ABnfQueryCompleteInfo"},
option_map = {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

AUIPlugin.AUICodeFilterScreen = Lua.Class(nil, "AUIPlugin.AUICodeFilterScreen")

function AUIPlugin.AUICodeFilterScreen:Ctor()
	___rawset(self, "_item_pool", {})
	___rawset(self, "_item_pool_count", 0)
	___rawset(self, "_item_height", 0)
end

function AUIPlugin.AUICodeFilterScreen:ShowComplete(project, pre_input, edit)
	if self._edit ~= edit then
		if self._edit ~= nil then
			self._edit:RemoveEventListener(___all_struct[-1604617962], self, self.HandleEditKeyDown)
		end
		self._edit = edit
		if self._edit ~= nil then
			self._edit:AddEventListener(___all_struct[-1604617962], self, self.HandleEditKeyDown)
		end
	end
	local text = self._edit.text
	local split = ALittle.String_Split(text, ".")
	local split_len = ALittle.List_Len(split)
	if split_len > 0 then
		if split[split_len] == "" then
			self._complete = nil
		end
		split[split_len] = nil
	end
	self._project = project
	if self._complete == nil then
		if not self:ReInit(pre_input, ALittle.String_Join(split, ".")) then
			self:Hide()
			return
		end
	end
	if not self:Fliter(text) then
		self:Hide()
		return
	end
end
AUIPlugin.AUICodeFilterScreen.ShowComplete = Lua.CoWrap(AUIPlugin.AUICodeFilterScreen.ShowComplete)

function AUIPlugin.AUICodeFilterScreen:HandleEditKeyDown(event)
	if event.sym == 13 then
		self:DoSelect()
	elseif event.sym == 1073741906 then
		self:SelectUp()
	elseif event.sym == 1073741905 then
		self:SelectDown()
	end
end

function AUIPlugin.AUICodeFilterScreen:IsShow()
	return self._edit ~= nil
end

function AUIPlugin.AUICodeFilterScreen:SelectUp()
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

function AUIPlugin.AUICodeFilterScreen:SelectDown()
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

function AUIPlugin.AUICodeFilterScreen:DoSelect()
	local target = self:GetSelectIndex()
	if target == nil then
		return false
	end
	local item = self._screen.childs[target]
	local text
	local complete = item._user_data.complete
	if complete.insert ~= nil then
		text = complete.insert
	else
		text = complete.display
	end
	self._edit.text = text
	self:Hide()
	return true
end

function AUIPlugin.AUICodeFilterScreen:GetSelectIndex()
	local target = nil
	for index, child in ___ipairs(self._screen.childs) do
		if child._user_data._item_button.selected then
			target = index
			break
		end
	end
	return target
end

function AUIPlugin.AUICodeFilterScreen:ReInit(pre_input, input)
	local ___COROUTINE = coroutine.running()
	if self._project == nil then
		return false
	end
	self._complete = self._project:FindDefine(pre_input, input)
	if self._complete == nil then
		return false
	end
	local x, y = self._edit:LocalToGlobal()
	y = y + (self._edit.height)
	if self._screen == nil then
		self._screen = AUIPlugin.g_Control:CreateControl("code_scroll_screen")
		self._screen.width = 200
		self._screen:AddEventListener(___all_struct[348388800], self, self.HandleHide)
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
	for index, info in ___ipairs(self._complete) do
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
		item_info._tag_image.texture_name = self._project:QueryCompleteIcon(info.tag)
		item_info._item._user_data = item_info
		item_info.complete = info
		self._item_list[index] = item_info
		local title_wdith = item_info._item_title.width + item_info._item_title.x + 5
		if max_width < title_wdith then
			max_width = title_wdith
		end
		self._item_height = item_info._item.height
	end
	self._screen.width = max_width
	A_LayerManager:ShowFromRight(self._screen, false)
	return true
end

function AUIPlugin.AUICodeFilterScreen:HandleHide(event)
	self:HideImpl()
end

function AUIPlugin.AUICodeFilterScreen.ItemInfoSort(a, b)
	return a.pos < b.pos
end

function AUIPlugin.AUICodeFilterScreen:Fliter(text)
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
	ALittle.List_Sort(sort_list, AUIPlugin.AUICodeFilterScreen.ItemInfoSort)
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

function AUIPlugin.AUICodeFilterScreen:Hide()
	self:HideImpl()
	A_LayerManager:HideFromRight(self._screen)
end

function AUIPlugin.AUICodeFilterScreen:HideImpl()
	self:HideTip()
	if self._edit ~= nil then
		self._edit:RemoveEventListener(___all_struct[-1604617962], self, self.HandleEditKeyDown)
	end
	self._edit = nil
	self._complete = nil
	if self._screen ~= nil then
		self._screen:RemoveAllChild()
	end
end

function AUIPlugin.AUICodeFilterScreen:ShowTip(content)
	if self._tip_dialog == nil then
		self._tip_dialog = AUIPlugin.g_Control:CreateControl("code_area_tip", self)
		self._tip_dialog.width = 200
	end
	A_LayerManager:AddToTip(self._tip_dialog)
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

function AUIPlugin.AUICodeFilterScreen:HideTip()
	if self._tip_dialog == nil then
		return
	end
	self._tip_dialog.visible = false
	A_LayerManager:RemoveFromTip(self._tip_dialog)
end

function AUIPlugin.AUICodeFilterScreen:Shutdown()
	self:Hide()
end

_G.g_AUICodeFilterScreen = AUIPlugin.AUICodeFilterScreen()
end