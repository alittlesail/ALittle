-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
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
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name = "ALittle.UIDropFileEvent", ns_name = "ALittle", rl_name = "UIDropFileEvent", hash_code = -338112738,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(ALittle.UIEventDispatcher, " extends class:ALittle.UIEventDispatcher is nil")
IDETabChild = Lua.Class(ALittle.UIEventDispatcher, "ALittleIDE.IDETabChild")

function IDETabChild:Ctor(ctrl_sys, name, save)
	___rawset(self, "_name", name)
	___rawset(self, "_save", save)
	___rawset(self, "_revoke_list", ALittle.RevokeList())
end

function IDETabChild.__getter:id()
	return self._name
end

function IDETabChild.__getter:name()
	return self._name
end

function IDETabChild.__getter:save()
	return self._save
end

function IDETabChild.__setter:save(value)
end

function IDETabChild:Save()
	self.save = true
end

function IDETabChild.__getter:revoke_list()
	return self._revoke_list
end

function IDETabChild:CanDelete(control_name)
	return nil
end

function IDETabChild.__getter:title()
	return self._name
end

function IDETabChild.__getter:tab_body()
	return nil
end

function IDETabChild:OnUndo()
end

function IDETabChild:OnRedo()
end

function IDETabChild:OnHide()
end

function IDETabChild:OnShow()
end

function IDETabChild:OnClose()
end

function IDETabChild:OnOpen()
end

function IDETabChild:OnTabRightMenu(menu)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEContentEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEContentEdit")

function IDEContentEdit:TCtor()
	self._main_tab:AddEventListener(___all_struct[444989011], self, self.HandleMainTabSelectChange)
	self._main_tab:AddEventListener(___all_struct[-641444818], self, self.HandleMainTabRightClick)
	self._main_tab:AddEventListener(___all_struct[-1604617962], self, self.HandleMainTabKeyDown)
	self._main_tab_bg:AddEventListener(___all_struct[-338112738], self, self.HandleMainTabDropFile)
	self._main_tab.close_callback = Lua.Bind(self.MainTabTabCloseYesOrNot, self)
	self._main_tab.close_post_callback = Lua.Bind(self.MainTabTabClose, self)
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function IDEContentEdit.__getter:cur_tab()
	return self._cur_tab
end

function IDEContentEdit.__getter:main_tab()
	return self._main_tab
end

function IDEContentEdit.__getter:cur_tab_child()
	if self._cur_tab == nil then
		return nil
	end
	return self._cur_tab._user_data
end

function IDEContentEdit:HandleProjectClose(event)
	self:CloseAllTab()
end

function IDEContentEdit:GetTabById(T, id)
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		local tab_child = ALittle.Cast(T, IDETabChild, child._user_data)
		if tab_child ~= nil and tab_child.id == id then
			return child
		end
	end
	return nil
end

function IDEContentEdit:GetTabIdMap(T)
	local info = {}
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		local tab_child = ALittle.Cast(T, IDETabChild, child._user_data)
		if tab_child ~= nil then
			info[tab_child.id] = true
		end
	end
	return info
end

function IDEContentEdit:GetCurTabIndex()
	return self._main_tab.tab_index
end

function IDEContentEdit:SetCurTabIndex(index)
	if self._main_tab.tab_index == index then
		return
	end
	self._main_tab.tab_index = index
	self:ChangeTabEdit(self._cur_tab, self._main_tab.tab)
end

function IDEContentEdit:IsSaveAll()
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		if child._user_data.save == false then
			return false
		end
	end
	return true
end

function IDEContentEdit:ChangeTabEdit(child_from, child_to)
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

function IDEContentEdit:CloseTab(child)
	local tab_child = child._user_data
	tab_child:OnClose()
	self._main_tab:RemoveChild(child)
	self:ChangeTabEdit(nil, self._main_tab.tab)
end

function IDEContentEdit:CloseTabByName(T, name)
	for index, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		local target_child = ALittle.Cast(T, IDETabChild, tab_child)
		if target_child ~= nil and target_child.name == name then
			self:CloseTab(tab_child.tab_body)
			break
		end
	end
end

function IDEContentEdit:RenameTabByName(T, old_name, new_name)
	for index, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		local target_child = ALittle.Cast(T, IDETabChild, tab_child)
		if target_child ~= nil and target_child.name == old_name then
			self._main_tab:SetChildText(tab_child.tab_body, new_name)
			break
		end
	end
end

function IDEContentEdit:SaveTab(child)
	local tab_child = child._user_data
	tab_child.save = true
end

function IDEContentEdit:CloseAllTab()
	self:ChangeTabEdit(self._main_tab.tab, nil)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:OnClose()
	end
	self._main_tab:RemoveAllChild()
end

function IDEContentEdit:SaveAllTab()
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child.save = true
	end
end

function IDEContentEdit:CanDelete(control_name)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		local error = tab_child:CanDelete(control_name)
		if error ~= nil then
			return error
		end
	end
	return nil
end

function IDEContentEdit:HandleMainTabSelectChange(event)
	self:ChangeTabEdit(self._cur_tab, self._main_tab.tab)
end

function IDEContentEdit:MainTabTabClose(child)
	self:CloseTab(child)
end

function IDEContentEdit:MainTabTabCloseYesOrNot(child)
	local tab_child = child._user_data
	if tab_child.save then
		return true
	end
	self:MainTabTabCloseImpl(tab_child, child)
	return false
end

function IDEContentEdit:MainTabTabCloseImpl(tab_child, child)
	local cancel_callback = Lua.Bind(self.CloseTab, self, child)
	local result = g_AUITool:SaveNotice("提示", "是否保存?")
	if result == "YES" then
		tab_child.save = true
	end
	self:CloseTab(child)
end
IDEContentEdit.MainTabTabCloseImpl = Lua.CoWrap(IDEContentEdit.MainTabTabCloseImpl)

function IDEContentEdit:HandleMainTabRightClick(event)
	local tab_child = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("保存", Lua.Bind(tab_child.Save, tab_child))
	tab_child:OnTabRightMenu(menu)
	menu:AddItem("关闭自己", Lua.Bind(g_IDECenter.center.content_edit.CloseTabWithAsk, g_IDECenter.center.content_edit, tab_child.tab_body))
	menu:AddItem("关闭左侧", Lua.Bind(g_IDECenter.center.content_edit.CloseLeftTab, g_IDECenter.center.content_edit, tab_child.tab_body))
	menu:AddItem("关闭右侧", Lua.Bind(g_IDECenter.center.content_edit.CloseRightTab, g_IDECenter.center.content_edit, tab_child.tab_body))
	menu:Show()
end

function IDEContentEdit:HandleMainTabKeyDown(event)
end
IDEContentEdit.HandleMainTabKeyDown = Lua.CoWrap(IDEContentEdit.HandleMainTabKeyDown)

function IDEContentEdit:HandleMainTabDropFile(event)
	local name = ALittle.File_GetFileNameByPath(event.path)
	local user_info = {}
	user_info.path = event.path
	user_info.name = name
	self:StartEditCodeBySelect(name, user_info)
end

function IDEContentEdit:HandleTabRightExMenu(event)
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

function IDEContentEdit:SelectItemClick(child_to)
	local child_from = self._main_tab.tab
	self._main_tab:SetChildIndex(child_to, 1)
	self._main_tab.tab = child_to
	self:ChangeTabEdit(child_from, child_to)
end

function IDEContentEdit:CloseTabWithAsk(child)
	local tab_child = child._user_data
	if tab_child.save then
		self:CloseTab(child)
		return
	end
	local result = g_AUITool:SaveNotice("提示", "是否保存当前标签页?")
	if result == "YES" then
		tab_child.save = true
	end
	self:CloseTab(child)
end
IDEContentEdit.CloseTabWithAsk = Lua.CoWrap(IDEContentEdit.CloseTabWithAsk)

function IDEContentEdit:CloseLeftTab(child)
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

function IDEContentEdit:CloseRightTab(child)
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

function IDEContentEdit:StartEditControlByNew(name, type)
	local child_from = self._main_tab.tab
	local tab_child = IDEUITabChild(g_Control, name, false)
	tab_child:CreateByNew(type)
	self._main_tab:AddChild(tab_child.tab_body)
	tab_child:OnOpen()
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEdit(child_from, self._main_tab.tab)
	tab_child:UpdateTitle()
	tab_child:ShowHandleQuad(tab_child.tree_object)
	return tab_child
end

function IDEContentEdit:StartEditControlByExtends(name, extends_v)
	local child_from = self._main_tab.tab
	local tab_child = IDEUITabChild(g_Control, name, false)
	tab_child:CreateByExtends(extends_v)
	self._main_tab:AddChild(tab_child.tab_body)
	tab_child:OnOpen()
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEdit(child_from, self._main_tab.tab)
	tab_child:UpdateTitle()
	tab_child:ShowHandleQuad(tab_child.tree_object)
	return tab_child
end

function IDEContentEdit:StartEditControlBySelect(name, info)
	local child = self:GetTabById(IDEUITabChild, name)
	if child ~= nil then
		local child_from = self._main_tab.tab
		self._main_tab.tab = child
		self:ChangeTabEdit(child_from, self._main_tab.tab)
		return child._user_data
	end
	local child_from = self._main_tab.tab
	local tab_child = IDEUITabChild(g_Control, name, true)
	tab_child:CreateBySelect(info)
	self._main_tab:AddChild(tab_child.tab_body, 1)
	tab_child:OnOpen()
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEdit(child_from, self._main_tab.tab)
	tab_child:UpdateTitle()
	if not tab_child.tree_object.is_tree then
		tab_child:ShowHandleQuad(tab_child.tree_object)
	end
	return tab_child
end

function IDEContentEdit:StartEditCodeBySelect(name, info)
	local child = self:GetTabById(IDECodeTabChild, info.path)
	if child ~= nil then
		local child_from = self._main_tab.tab
		self._main_tab.tab = child
		self:ChangeTabEdit(child_from, self._main_tab.tab)
		return child._user_data
	end
	local child_from = self._main_tab.tab
	local tab_child = IDECodeTabChild(g_Control, name, true, info)
	tab_child:CreateBySelect(info)
	self._main_tab:AddChild(tab_child.tab_body, 1)
	tab_child:OnOpen()
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEdit(child_from, self._main_tab.tab)
	tab_child:UpdateTitle()
	return tab_child
end

