-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittleIDE.IDEControlTreeLogic, " extends class:ALittleIDE.IDEControlTreeLogic is nil")
ALittleIDE.IDEControlTree = Lua.Class(ALittleIDE.IDEControlTreeLogic, "ALittleIDE.IDEControlTree")

function ALittleIDE.IDEControlTree:Ctor(ctrl_sys, user_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_control_tree_head", self))
	ALittle.DisplayGroup.AddChild(self, self._head)
	self._item_button.selected = false
	self._item_button.group = user_info.group
	self._item_button:AddEventListener(___all_struct[1883782801], self, self.HandleLButtonDown)
	self._item_button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
	self._item_button._user_data = self
	___rawset(self, "_body", ALittle.Linear(ctrl_sys))
	self._body.type = 2
	self._body.x = 8
	self._body.y = self._head.height
	self._body.width = self._head.width
	self._item_checkbutton.selected = true
	ALittle.DisplayGroup.AddChild(self, self._body)
	self._body:AddEventListener(___all_struct[-431205740], self, self.HandleChildResize)
	___rawset(self, "_pickup_rect", false)
	___rawset(self, "_pickup_child", true)
	self.fold = false
	if user_info.root then
		self._item_button.text = "[" .. self._user_info.module_name .. "] " .. self._user_info.name
	else
		self._item_button.text = self._user_info.name
	end
	self:Refresh()
end

function ALittleIDE.IDEControlTree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function ALittleIDE.IDEControlTree:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	if self._user_info.root then
		menu:AddItem("添加模块", Lua.Bind(self.HandleAddModule, self))
	end
	menu:AddItem("新建控件", Lua.Bind(self.HandleNewControl, self))
	menu:AddItem("继承控件", Lua.Bind(self.HandleExtendsControl, self))
	local can_remove = self._user_info.root and self._user_info.module_name ~= ALittleIDE.g_IDEProject.project.name
	if can_remove then
		menu:AddItem("移除模块", Lua.Bind(self.HandleRemoveModule, self))
	end
	menu:Show()
end

function ALittleIDE.IDEControlTree:HandleAddModule()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittleIDE.g_IDECenter.center.control_list:AddModule(name)
end
ALittleIDE.IDEControlTree.HandleAddModule = Lua.CoWrap(ALittleIDE.IDEControlTree.HandleAddModule)

function ALittleIDE.IDEControlTree:HandleRemoveModule()
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(nil)
	if ui_manager == nil then
		return
	end
	local remove_list = {}
	local tab_child_map = ALittleIDE.g_IDECenter.center.content_edit:GetTabIdMap(ALittleIDE.IDEUITabChild)
	for id, tab_child in ___pairs(tab_child_map) do
		if tab_child.module == self._user_info.module_name then
			if not tab_child.save then
				g_AUITool:ShowNotice("错误", "还有UI正在编辑并为保存")
				return
			end
			ALittle.List_Push(remove_list, tab_child)
		end
	end
	for index, tab_child in ___ipairs(remove_list) do
		ALittleIDE.g_IDECenter.center.content_edit:CloseTabByName(ALittleIDE.IDEUITabChild, tab_child.name)
	end
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("移除", "确定要移除" .. file_name .. "模块吗?")
	if result ~= "YES" then
		return
	end
	self:OnDelete()
	self:RemoveFromParent()
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("control_module", {})
	module_map[self._user_info.module_name] = nil
	ALittleIDE.g_IDEProject.project.config:SetConfig("control_module", module_map)
	ALittleIDE.g_IDEProject.project.ui[self._user_info.module_name] = nil
	ui_manager.control:UnRegisterPlugin(self._user_info.module_name)
end
ALittleIDE.IDEControlTree.HandleRemoveModule = Lua.CoWrap(ALittleIDE.IDEControlTree.HandleRemoveModule)

function ALittleIDE.IDEControlTree:HandleNewControl()
	ALittleIDE.g_IDECenter.center.control_list:ShowNewControl(self._user_info.module_name)
end

function ALittleIDE.IDEControlTree:HandleExtendsControl()
	ALittleIDE.g_IDECenter.center.control_list:ShowExtendsControl(self._user_info.module_name)
end

function ALittleIDE.IDEControlTree.__getter:is_tree()
	return true
end

function ALittleIDE.IDEControlTree:Refresh()
	local map = ALittle.File_GetNameListByDir(self._user_info.path)
	local remove = nil
	for index, child in ___ipairs(self.childs) do
		local attr = map[child._user_info.name]
		if attr == nil then
			if remove == nil then
				remove = {}
			end
			ALittle.List_Push(remove, child)
		end
		map[child._user_info.name] = nil
		child:Refresh()
	end
	if remove ~= nil then
		for index, child in ___ipairs(remove) do
			self:RemoveChild(child)
		end
	end
	local add_file = nil
	local add_dir = nil
	for name, attr in ___pairs(map) do
		if attr.directory then
			if add_dir == nil then
				add_dir = {}
			end
			ALittle.List_Push(add_dir, name)
		else
			if add_file == nil then
				add_file = {}
			end
			ALittle.List_Push(add_file, name)
		end
	end
	if add_dir ~= nil then
		ALittle.List_Sort(add_dir)
		for index, name in ___ipairs(add_dir) do
			local attr = map[name]
			local info = {}
			info.module_name = self._user_info.module_name
			info.module_path = self._user_info.module_path
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.root = false
			info.ui = self._user_info.ui
			self:AddChild(ALittleIDE.IDEControlTree(self._ctrl_sys, info))
		end
	end
	if add_file ~= nil then
		ALittle.List_Sort(add_file)
		for index, name in ___ipairs(add_file) do
			local attr = map[name]
			local info = {}
			info.module_name = self._user_info.module_name
			info.module_path = self._user_info.module_path
			info.name = ALittle.File_GetJustFileNameByPath(name)
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.root = false
			info.ui = self._user_info.ui
			self:AddChild(ALittleIDE.IDEControlTreeItem(self._ctrl_sys, info))
		end
	end
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEControlTree:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchFile(name, list)
	end
	return list
end

function ALittleIDE.IDEControlTree:FindFile(full_path)
	if ALittle.String_Find(full_path, self._user_info.path) ~= 1 then
		return nil
	end
	for k, child in ___ipairs(self._body.childs) do
		local item = child:FindFile(full_path)
		if item ~= nil then
			return item
		end
	end
	return nil
end

function ALittleIDE.IDEControlTree:OnDelete()
	for index, child in ___ipairs(self.childs) do
		child:OnDelete()
	end
end

function ALittleIDE.IDEControlTree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEControlTree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEControlTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDEControlTree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function ALittleIDE.IDEControlTree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function ALittleIDE.IDEControlTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDEControlTree.__getter:childs()
	return self._body.childs
end

function ALittleIDE.IDEControlTree.__getter:child_count()
	return self._body.child_count
end

function ALittleIDE.IDEControlTree:HasChild(child)
	return self._body:HasChild(child)
end

function ALittleIDE.IDEControlTree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDEControlTree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	child.group = nil
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDEControlTree:SpliceChild(index, count)
	local remain_count = self._child_count - index + 1
	if count == nil then
		count = remain_count
	elseif count > remain_count then
		count = remain_count
	end
	if count <= 0 then
		return 0
	end
	local endv = index + count
	local i = index
	while true do
		if not(i < endv) then break end
		local child = self._childs[i]
		if child == nil then
			break
		end
		child.group = nil
		i = i+(1)
	end
	local result = self._body:SpliceChild(index, count)
	if result == 0 then
		return 0
	end
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return result
end

function ALittleIDE.IDEControlTree:RemoveAllChild()
	for index, child in ___ipairs(self.childs) do
		child.group = nil
	end
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function ALittleIDE.IDEControlTree.__getter:width()
	local head_width = 0.0
	if self._head ~= nil then
		head_width = self._head.width
	end
	local body_width = 0.0
	if self._body.visible then
		local start_x = self._body.x
		body_width = start_x + self._body.width
		local childs = self._body.childs
		for k, v in ___ipairs(childs) do
			local child_width = start_x + v.x + v.width
			if body_width < child_width then
				body_width = child_width
			end
		end
	end
	if head_width > body_width then
		return head_width
	end
	return body_width
end

function ALittleIDE.IDEControlTree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function ALittleIDE.IDEControlTree.__getter:fold()
	return self._body.visible
end

function ALittleIDE.IDEControlTree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDEControlTree.__getter:max_right()
	return self.width
end

function ALittleIDE.IDEControlTree.__getter:max_bottom()
	return self.height
end

end