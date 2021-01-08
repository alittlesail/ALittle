-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
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
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name = "ALittle.UISelectChangedEvent", ns_name = "ALittle", rl_name = "UISelectChangedEvent", hash_code = 444989011,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.UIEventDispatcher, " extends class:ALittle.UIEventDispatcher is nil")
ALittleDeploy.DPLTabChild = Lua.Class(ALittle.UIEventDispatcher, "ALittleDeploy.DPLTabChild")

function ALittleDeploy.DPLTabChild:Ctor(ctrl_sys, module, name, save)
	___rawset(self, "_name", name)
	___rawset(self, "_module", module)
	___rawset(self, "_save", save)
	___rawset(self, "_revoke_list", ALittle.RevokeList(10000))
end

function ALittleDeploy.DPLTabChild.__getter:id()
	return self._name
end

function ALittleDeploy.DPLTabChild.__getter:name()
	return self._name
end

function ALittleDeploy.DPLTabChild.__getter:module()
	return self._module
end

function ALittleDeploy.DPLTabChild.__getter:save()
	return self._save
end

function ALittleDeploy.DPLTabChild.__setter:save(value)
end

function ALittleDeploy.DPLTabChild:Save()
	self.save = true
end

function ALittleDeploy.DPLTabChild.__getter:revoke_list()
	return self._revoke_list
end

function ALittleDeploy.DPLTabChild.__getter:title()
	return self._name
end

function ALittleDeploy.DPLTabChild.__getter:tab_body()
	return nil
end

function ALittleDeploy.DPLTabChild:OnUndo()
end

function ALittleDeploy.DPLTabChild:OnRedo()
end

function ALittleDeploy.DPLTabChild:OnHide()
end

function ALittleDeploy.DPLTabChild:OnShow()
end

function ALittleDeploy.DPLTabChild:OnClose()
end

function ALittleDeploy.DPLTabChild:OnOpen()
end

function ALittleDeploy.DPLTabChild:OnTabRightMenu(menu)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleDeploy.DPLContentEdit = Lua.Class(ALittle.DisplayLayout, "ALittleDeploy.DPLContentEdit")

function ALittleDeploy.DPLContentEdit:TCtor()
	self._main_tab:AddEventListener(___all_struct[444989011], self, self.HandleMainTabSelectChange)
	self._main_tab:AddEventListener(___all_struct[-641444818], self, self.HandleMainTabRightClick)
	self._main_tab:AddEventListener(___all_struct[-1604617962], self, self.HandleMainTabKeyDown)
	self._main_tab.close_callback = Lua.Bind(self.MainTabTabCloseYesOrNot, self)
	self._main_tab.close_post_callback = Lua.Bind(self.MainTabTabClose, self)
end

function ALittleDeploy.DPLContentEdit.__getter:cur_tab()
	return self._cur_tab
end

function ALittleDeploy.DPLContentEdit.__getter:main_tab()
	return self._main_tab
end

function ALittleDeploy.DPLContentEdit.__getter:cur_tab_child()
	if self._cur_tab == nil then
		return nil
	end
	return self._cur_tab._user_data
end

function ALittleDeploy.DPLContentEdit:GetTabById(T, id)
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		local tab_child = ALittle.Cast(T, ALittleDeploy.DPLTabChild, child._user_data)
		if tab_child ~= nil and tab_child.id == id then
			return child
		end
	end
	return nil
end

function ALittleDeploy.DPLContentEdit:GetTabChildById(T, id)
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		local tab_child = ALittle.Cast(T, ALittleDeploy.DPLTabChild, child._user_data)
		if tab_child ~= nil and tab_child.id == id then
			return tab_child
		end
	end
	return nil
end

function ALittleDeploy.DPLContentEdit:GetTabIdMap(T)
	local info = {}
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		local tab_child = ALittle.Cast(T, ALittleDeploy.DPLTabChild, child._user_data)
		if tab_child ~= nil then
			info[tab_child.id] = tab_child
		end
	end
	return info
end

function ALittleDeploy.DPLContentEdit:GetCurTabIndex()
	return self._main_tab.tab_index
end

function ALittleDeploy.DPLContentEdit:SetCurTabIndex(index)
	if self._main_tab.tab_index == index then
		return
	end
	self._main_tab.tab_index = index
	self:ChangeTabEdit(self._cur_tab, self._main_tab.tab)
end

function ALittleDeploy.DPLContentEdit:IsSaveAll()
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		if child._user_data.save == false then
			return false
		end
	end
	return true
end

function ALittleDeploy.DPLContentEdit:ChangeTabEdit(child_from, child_to)
	if child_from == child_to then
		return
	end
	if child_from ~= nil then
		local tab_child = child_from._user_data
		tab_child:OnHide()
	end
	if child_to ~= nil then
		local tab_child = child_to._user_data
		tab_child:OnShow()
	end
	self._cur_tab = child_to
end

function ALittleDeploy.DPLContentEdit:CloseTab(child)
	local tab_child = child._user_data
	if self._main_tab.tab == child then
		tab_child:OnHide()
	end
	tab_child:OnClose()
	self._main_tab:RemoveChild(child)
	self:ChangeTabEdit(nil, self._main_tab.tab)
end

function ALittleDeploy.DPLContentEdit:CloseTabChild(tab_child)
	self:CloseTab(tab_child.tab_body)
end

function ALittleDeploy.DPLContentEdit:CloseTabByName(T, name)
	for index, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		local target_child = ALittle.Cast(T, ALittleDeploy.DPLTabChild, tab_child)
		if target_child ~= nil and self._main_tab:GetChildText(child) == name then
			self:CloseTab(tab_child.tab_body)
			break
		end
	end
end

function ALittleDeploy.DPLContentEdit:SaveTab(child)
	local tab_child = child._user_data
	tab_child.save = true
end

function ALittleDeploy.DPLContentEdit:CloseAllTab()
	self:ChangeTabEdit(self._main_tab.tab, nil)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:OnClose()
	end
	self._main_tab:RemoveAllChild()
end

function ALittleDeploy.DPLContentEdit:SaveAllTab()
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child.save = true
	end
end

function ALittleDeploy.DPLContentEdit:HandleMainTabSelectChange(event)
	self:ChangeTabEdit(self._cur_tab, self._main_tab.tab)
end

function ALittleDeploy.DPLContentEdit:MainTabTabClose(child)
	self:CloseTab(child)
end

function ALittleDeploy.DPLContentEdit:MainTabTabCloseYesOrNot(child)
	local tab_child = child._user_data
	if tab_child.save then
		if self._main_tab.tab == child then
			tab_child:OnHide()
		end
		tab_child:OnClose()
		return true
	end
	self:MainTabTabCloseImpl(tab_child, child)
	return false
end

function ALittleDeploy.DPLContentEdit:MainTabTabCloseImpl(tab_child, child)
	local cancel_callback = Lua.Bind(self.CloseTab, self, child)
	local result = g_AUITool:SaveNotice("提示", "是否保存?")
	if result == "CANCEL" then
		return
	end
	if result == "YES" then
		tab_child.save = true
	end
	self:CloseTab(child)
end
ALittleDeploy.DPLContentEdit.MainTabTabCloseImpl = Lua.CoWrap(ALittleDeploy.DPLContentEdit.MainTabTabCloseImpl)

function ALittleDeploy.DPLContentEdit:HandleMainTabRightClick(event)
	local tab_child = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("保存", Lua.Bind(tab_child.Save, tab_child))
	tab_child:OnTabRightMenu(menu)
	menu:AddItem("关闭自己", Lua.Bind(self.CloseTabWithAsk, self, tab_child.tab_body))
	menu:AddItem("关闭左侧", Lua.Bind(self.CloseLeftTab, self, tab_child.tab_body))
	menu:AddItem("关闭右侧", Lua.Bind(self.CloseRightTab, self, tab_child.tab_body))
	menu:Show()
end

function ALittleDeploy.DPLContentEdit:HandleMainTabKeyDown(event)
end
ALittleDeploy.DPLContentEdit.HandleMainTabKeyDown = Lua.CoWrap(ALittleDeploy.DPLContentEdit.HandleMainTabKeyDown)

function ALittleDeploy.DPLContentEdit:HandleTabRightExMenu(event)
	local tab_childs = self._main_tab.childs
	if tab_childs[1] == nil then
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	for index, child in ___ipairs(tab_childs) do
		local tab_child = child._user_data
		menu:AddItem(tab_child.title, Lua.Bind(self.SelectItemClick, self, child))
	end
	menu:Show()
end

function ALittleDeploy.DPLContentEdit:SelectItemClick(child_to)
	local child_from = self._main_tab.tab
	self._main_tab:SetChildIndex(child_to, 1)
	self._main_tab.tab = child_to
	self:ChangeTabEdit(child_from, child_to)
end

function ALittleDeploy.DPLContentEdit:CloseTabWithAsk(child)
	local tab_child = child._user_data
	if tab_child.save then
		self:CloseTab(child)
		return
	end
	local result = g_AUITool:SaveNotice("提示", "是否保存当前标签页?")
	if result == "CANCEL" then
		return
	end
	if result == "YES" then
		tab_child.save = true
	end
	self:CloseTab(child)
end
ALittleDeploy.DPLContentEdit.CloseTabWithAsk = Lua.CoWrap(ALittleDeploy.DPLContentEdit.CloseTabWithAsk)

function ALittleDeploy.DPLContentEdit:CloseLeftTab(child)
	local close_list = {}
	for index, child_v in ___ipairs(self._main_tab.childs) do
		if child_v == child then
			break
		end
		local tab_child = child_v._user_data
		if tab_child.save then
			ALittle.List_Push(close_list, child_v)
		end
	end
	for index, child_v in ___ipairs(close_list) do
		self:CloseTab(child_v)
	end
end

function ALittleDeploy.DPLContentEdit:CloseRightTab(child)
	local close_list = {}
	local child_list = self._main_tab.childs
	local cur_index = self._main_tab:GetChildIndex(child)
	local child_count = self._main_tab.child_count
	local index = cur_index + 1
	while true do
		if not(index <= child_count) then break end
		local child_v = child_list[index]
		local tab_child = child_v._user_data
		if tab_child.save then
			ALittle.List_Push(close_list, child_v)
		end
		index = index+(1)
	end
	for index, child_v in ___ipairs(close_list) do
		self:CloseTab(child_v)
	end
end

end