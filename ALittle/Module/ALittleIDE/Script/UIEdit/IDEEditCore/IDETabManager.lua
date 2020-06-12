-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name = "ALittle.UIKeyDownEvent", ns_name = "ALittle", rl_name = "UIKeyDownEvent", hash_code = -1604617962,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})

IDETabManager = Lua.Class(nil, "ALittleIDE.IDETabManager")

function IDETabManager:Setup(tab, tree, control, anti)
	self._main_tab = tab
	self._main_tree = tree
	self._main_control = control
	self._main_anti = anti
	self._main_tab:AddEventListener(___all_struct[444989011], self, self.HandleMainTabSelectChange)
	self._main_tab:AddEventListener(___all_struct[-641444818], self, self.HandleMainTabRightClick)
	self._main_tab:AddEventListener(___all_struct[-1604617962], self, self.HandleMainTabKeyDown)
	self._main_tab.close_callback = Lua.Bind(self.MainTabTabCloseYesOrNot, self)
	self._main_tab.close_post_callback = Lua.Bind(self.MainTabTabClose, self)
	self._cur_tab = nil
end

function IDETabManager:Shutdown()
end

function IDETabManager.__getter:main_control()
	return self._main_control
end

function IDETabManager.__getter:main_anti()
	return self._main_anti
end

function IDETabManager.__getter:main_tab()
	return self._main_tab
end

function IDETabManager.__getter:cur_tab()
	return self._cur_tab
end

function IDETabManager.__getter:cur_tab_child()
	if self._cur_tab == nil then
		return nil
	end
	return self._cur_tab._user_data
end

function IDETabManager:GetTabByName(name)
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		if child._user_data.name == name then
			return child
		end
	end
	return nil
end

function IDETabManager:GetTabNameMap()
	local info = {}
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		info[child._user_data.name] = true
	end
	return info
end

function IDETabManager:GetTabNameList()
	local info = {}
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		ALittle.List_Push(info, child._user_data.name)
	end
	return info
end

function IDETabManager:GetCurTabIndex()
	return self._main_tab.tab_index
end

function IDETabManager:SetCurTabIndex(index)
	if self._main_tab.tab_index == index then
		return
	end
	self._main_tab.tab_index = index
	self:ChangeTabEditControl(self._cur_tab, self._main_tab.tab)
end

function IDETabManager:IsSaveAll()
	local tab_childs = self._main_tab.childs
	for index, child in ___ipairs(tab_childs) do
		if child._user_data.save == false then
			return false
		end
	end
	return true
end

function IDETabManager:ChangeTabEditControl(child_from, child_to)
	if child_from == child_to then
		return
	end
	if child_from ~= nil then
		local tab_child = child_from._user_data
		tab_child.tree_screen.visible = false
		tab_child.control_screen.visible = false
		tab_child.anti_panel.visible = false
		g_IDEAttributeManager:SetTitle("")
	end
	if child_to ~= nil then
		local tab_child = child_to._user_data
		tab_child.tree_screen.visible = true
		tab_child.control_screen.visible = true
		tab_child.anti_panel.visible = true
		local panel_childs = tab_child.control_screen.childs
		if panel_childs[1] ~= nil then
			g_IDEAttributeManager:SetTitle(panel_childs[1]._user_data.title)
		end
		g_IDEUICenter:UpdateToolScale(tab_child:GetScale())
	end
	self._cur_tab = child_to
end

function IDETabManager:CloseTab(child)
	local tab_child = child._user_data
	self._main_tree:RemoveChild(tab_child.tree_screen)
	self._main_control:RemoveChild(tab_child.control_screen)
	self._main_anti:RemoveChild(tab_child.anti_panel)
	self._main_tab:RemoveChild(child)
	self:ChangeTabEditControl(child, self._main_tab.tab)
end

function IDETabManager:RefreshTab(child)
	local tab_child = child._user_data
	local tab_index = self._main_tab:GetChildIndex(child)
	self:CloseTab(child)
	local name = tab_child.name
	local control_info = g_IDEProject.project.ui.control_map[name]
	local new_tab_child = self:StartEditControlBySelect(control_info.name, control_info.info)
	self._main_tab:SetChildIndex(new_tab_child.tab_body, tab_index)
end

function IDETabManager:CloseAllTab()
	self:ChangeTabEditControl(self._main_tab.tab, nil)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		self._main_tree:RemoveChild(tab_child.tree_screen)
		self._main_control:RemoveChild(tab_child.control_screen)
		self._main_anti:RemoveChild(tab_child.anti_panel)
	end
	self._main_tab:RemoveAllChild()
end

function IDETabManager:SaveAllTab()
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:Save(true)
	end
end

function IDETabManager:SetTabChildWH(width, height)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:SetEditWH(width, height)
	end
end

function IDETabManager:ShowTabChildSelectLayer(value)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:ShowSelectLayer(value)
	end
end

function IDETabManager:ShowTabChildHandDragLayer(value)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:ShowHandDragLayer(value)
	end
end

function IDETabManager:ShowTabChildScaleLayer(value)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		tab_child:ShowScaleLayer(value)
	end
end

function IDETabManager:CanDelete(name)
	for k, child in ___ipairs(self._main_tab.childs) do
		local tab_child = child._user_data
		local error = tab_child:CanDeleteControl(name)
		if error ~= nil then
			return error
		end
	end
	return nil
end

function IDETabManager:HandleMainTabSelectChange(event)
	self:ChangeTabEditControl(self._cur_tab, self._main_tab.tab)
end

function IDETabManager:MainTabTabClose(child)
	self:CloseTab(child)
end

function IDETabManager:MainTabTabCloseYesOrNot(child)
	local tab_child = child._user_data
	if tab_child.save then
		return true
	end
	self:MainTabTabCloseImpl(tab_child, child)
	return false
end

function IDETabManager:MainTabTabCloseImpl(tab_child, child)
	local cancel_callback = Lua.Bind(self.CloseTab, self, child)
	local result = g_AUITool:SaveNotice("提示", "是否保存当前控件?")
	if result == "YES" then
		tab_child:Save(true)
	end
	self:CloseTab(child)
end
IDETabManager.MainTabTabCloseImpl = Lua.CoWrap(IDETabManager.MainTabTabCloseImpl)

function IDETabManager:HandleMainTabRightClick(event)
	self:ShowTabRightMenu(event.target)
end

function IDETabManager:HandleMainTabKeyDown(event)
	if event.sym == 1073741883 then
		self:ControlRename(event.target)
		event.handled = true
		return
	end
	if event.sym == 1073741886 then
		local child = event.target
		local tab_child = child._user_data
		if tab_child.save then
			self:RefreshTab(child)
			event.handled = true
			return
		end
		local result = g_AUITool:SaveNotice("提示", "是否保存当前控件?")
		if result == "YES" then
			tab_child:Save(true)
		end
		self:RefreshTab(child)
		event.handled = true
		return
	end
end
IDETabManager.HandleMainTabKeyDown = Lua.CoWrap(IDETabManager.HandleMainTabKeyDown)

function IDETabManager:ShowTabRightMenu(child)
	local tab_child = child._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("保存", Lua.Bind(tab_child.Save, tab_child, true))
	menu:AddItem("截图导出", Lua.Bind(A_OtherSystem.SystemSaveFile, A_OtherSystem, tab_child, tab_child.name .. ".png", nil))
	menu:AddItem("刷新", Lua.Bind(self.RefreshTabWithAsk, self, child))
	menu:AddItem("复制控件名", Lua.Bind(ALittle.System_SetClipboardText, tab_child.name))
	menu:AddItem("复制继承代码", Lua.Bind(self.CopyExtends, self, child))
	menu:AddItem("关闭自己", Lua.Bind(self.CloseTabWithAsk, self, child))
	menu:AddItem("关闭左侧", Lua.Bind(self.CloseLeftTab, self, child))
	menu:AddItem("关闭右侧", Lua.Bind(self.CloseRightTab, self, child))
	menu:AddItem("修改控件名", Lua.Bind(self.ControlRename, self, child))
	menu:Show()
end

function IDETabManager:ShowTabRightExMenu(x, y)
	local tab_childs = self._main_tab.childs
	if tab_childs[1] == nil then
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	for index, child in ___ipairs(tab_childs) do
		local tab_child = child._user_data
		menu:AddItem(tab_child.total_title, Lua.Bind(self.SelectItemClick, self, child))
	end
	menu:Show()
end

function IDETabManager:SelectItemClick(child_to)
	local child_from = self._main_tab.tab
	self._main_tab:SetChildIndex(child_to, 1)
	self._main_tab.tab = child_to
	self:ChangeTabEditControl(child_from, child_to)
end

function IDETabManager:RefreshTabWithAsk(child)
	local tab_child = child._user_data
	if tab_child.save then
		self:RefreshTab(child)
		return
	end
	local result = g_AUITool:SaveNotice("提示", "是否保存当前控件?")
	if result == "YES" then
		tab_child:Save(true)
	end
	self:RefreshTab(child)
end
IDETabManager.RefreshTabWithAsk = Lua.CoWrap(IDETabManager.RefreshTabWithAsk)

function IDETabManager:CloseTabWithAsk(child)
	local tab_child = child._user_data
	if tab_child.save then
		self:CloseTab(child)
		return
	end
	local result = g_AUITool:SaveNotice("提示", "是否保存当前控件?")
	if result == "YES" then
		tab_child:Save(true)
	end
	self:CloseTab(child)
end
IDETabManager.CloseTabWithAsk = Lua.CoWrap(IDETabManager.CloseTabWithAsk)

function IDETabManager:CloseLeftTab(child)
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

function IDETabManager:CloseRightTab(child)
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

function IDETabManager:CopyExtends(child)
	local tab_child = child._user_data
	local name = tab_child.name
	local display_info = {}
	display_info.__extends = name
	local copy_list = {}
	local info = {}
	info.index = 1
	info.info = display_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function IDETabManager:ControlRename(child)
	local tab_child = child._user_data
	local old_name = tab_child.name
	local error = g_IDEProject.project.ui:CanDelete(old_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	error = g_IDETabManager:CanDelete(old_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local layout = self._main_tab:GetChildHead(child)
	local x, y = layout:LocalToGlobal()
	local width = layout.width
	if width < 150 then
		width = 150
	end
	local new_name = g_AUITool:ShowRename(old_name, x, y, width)
	if new_name == nil or old_name == new_name then
		return
	end
	if old_name == new_name then
		return
	end
	error = g_IDEProject.project.ui:RenameControl(old_name, new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	tab_child:Rename(new_name)
end
IDETabManager.ControlRename = Lua.CoWrap(IDETabManager.ControlRename)

function IDETabManager:StartEditControlByNew(name, type)
	local child_from = self._main_tab.tab
	local tab_child = IDETabChild(name, false)
	tab_child:CreateByNew(type)
	self._main_tab:AddChild(tab_child.tab_body)
	self._main_tree:AddChild(tab_child.tree_screen)
	self._main_control:AddChild(tab_child.control_screen)
	self._main_anti:AddChild(tab_child.anti_panel)
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEditControl(child_from, tab_child.tab_body)
	tab_child:UpdateTitle()
	tab_child:ShowHandleQuad(tab_child.tree_object)
	return tab_child
end

function IDETabManager:StartEditControlByExtends(name, extends_v)
	local child_from = self._main_tab.tab
	local tab_child = IDETabChild(name, false)
	tab_child:CreateByExtends(extends_v)
	self._main_tab:AddChild(tab_child.tab_body)
	self._main_tree:AddChild(tab_child.tree_screen)
	self._main_control:AddChild(tab_child.control_screen)
	self._main_anti:AddChild(tab_child.anti_panel)
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEditControl(child_from, tab_child.tab_body)
	tab_child:UpdateTitle()
	tab_child:ShowHandleQuad(tab_child.tree_object)
	return tab_child
end

function IDETabManager:StartEditControlBySelect(name, info)
	local child = self:GetTabByName(name)
	if child ~= nil then
		local child_from = self._main_tab.tab
		self._main_tab.tab = child
		self:ChangeTabEditControl(child_from, child)
		return child._user_data
	end
	local child_from = self._main_tab.tab
	local tab_child = IDETabChild(name, true)
	tab_child:CreateBySelect(info)
	self._main_tab:AddChild(tab_child.tab_body, 1)
	self._main_tree:AddChild(tab_child.tree_screen)
	self._main_control:AddChild(tab_child.control_screen)
	self._main_anti:AddChild(tab_child.anti_panel)
	self._main_tab.tab = tab_child.tab_body
	self:ChangeTabEditControl(child_from, tab_child.tab_body)
	tab_child:UpdateTitle()
	if tab_child.tree_object:IsTree() == false then
		tab_child:ShowHandleQuad(tab_child.tree_object)
	end
	return tab_child
end

g_IDETabManager = IDETabManager()
