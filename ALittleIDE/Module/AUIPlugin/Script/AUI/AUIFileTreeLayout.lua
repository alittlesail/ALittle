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

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name = "AUIPlugin.AUIFileSelectFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileEvent", hash_code = 2117383637,
name_list = {"target","info"},
type_list = {"ALittle.DisplayObject","AUIPlugin.AUIFileTreeUserInfo"},
option_map = {}
})
ALittle.RegStruct(-2082217254, "AUIPlugin.AUIFileCreateFileEvent", {
name = "AUIPlugin.AUIFileCreateFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileCreateFileEvent", hash_code = -2082217254,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-1718818319, "AUIPlugin.AUIFileDeleteDirEvent", {
name = "AUIPlugin.AUIFileDeleteDirEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteDirEvent", hash_code = -1718818319,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
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
ALittle.RegStruct(821610974, "AUIPlugin.AUIFileSearchInfo", {
name = "AUIPlugin.AUIFileSearchInfo", ns_name = "AUIPlugin", rl_name = "AUIFileSearchInfo", hash_code = 821610974,
name_list = {"list","count","index","name"},
type_list = {"List<AUIPlugin.AUIFileTreeLogic>","int","int","string"},
option_map = {}
})
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name = "AUIPlugin.AUIFileTreeUserInfo", ns_name = "AUIPlugin", rl_name = "AUIFileTreeUserInfo", hash_code = -686652419,
name_list = {"path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"},
type_list = {"string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-545221029, "AUIPlugin.AUIFileDeleteFileEvent", {
name = "AUIPlugin.AUIFileDeleteFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteFileEvent", hash_code = -545221029,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIFileTreeLogic = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIFileTreeLogic")

function AUIPlugin.AUIFileTreeLogic:Ctor(ctrl_sys, user_info)
	___rawset(self, "_user_info", user_info)
end

function AUIPlugin.AUIFileTreeLogic.__getter:user_info()
	return self._user_info
end

function AUIPlugin.AUIFileTreeLogic.__getter:is_tree()
	return false
end

function AUIPlugin.AUIFileTreeLogic.__getter:is_root()
	return self._user_info.root
end

function AUIPlugin.AUIFileTreeLogic.__setter:fold(value)
end

function AUIPlugin.AUIFileTreeLogic:ShowSelect()
	if self._item_button ~= nil then
		self._item_button.selected = true
	end
end

function AUIPlugin.AUIFileTreeLogic:Refresh()
end

function AUIPlugin.AUIFileTreeLogic:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	return list
end

function AUIPlugin.AUIFileTreeLogic:FindFile(full_path)
	return nil
end

assert(AUIPlugin.AUIFileTreeLogic, " extends class:AUIPlugin.AUIFileTreeLogic is nil")
AUIPlugin.AUIFileTree = Lua.Class(AUIPlugin.AUIFileTreeLogic, "AUIPlugin.AUIFileTree")

function AUIPlugin.AUIFileTree:Ctor(ctrl_sys, user_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("file_tree_head", self))
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
	self._item_button.text = self._user_info.name
	self:Refresh()
end

function AUIPlugin.AUIFileTree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function AUIPlugin.AUIFileTree:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建文件", Lua.Bind(self.HandleCreateFile, self))
	menu:AddItem("新建文件夹", Lua.Bind(self.HandleCreateDir, self))
	menu:AddItem("刷新", Lua.Bind(self.Refresh, self))
	if not self._user_info.root then
		menu:AddItem("删除", Lua.Bind(self.HandleDeleteDir, self))
	end
	menu:Show()
end

function AUIPlugin.AUIFileTree:HandleCreateFile()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	if ALittle.File_GetFileAttr(self._user_info.path .. "/" .. name) ~= nil then
		g_AUITool:ShowNotice("提示", "文件名已存在")
		return
	end
	ALittle.File_WriteTextToFile("", self._user_info.path .. "/" .. name)
	self:Refresh()
	if self._user_info.on_create_file ~= nil then
		self._user_info.on_create_file(self._user_info.path .. "/" .. name)
	end
end
AUIPlugin.AUIFileTree.HandleCreateFile = Lua.CoWrap(AUIPlugin.AUIFileTree.HandleCreateFile)

function AUIPlugin.AUIFileTree:HandleCreateDir()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittle.File_MakeDir(self._user_info.path .. "/" .. name)
	self:Refresh()
end
AUIPlugin.AUIFileTree.HandleCreateDir = Lua.CoWrap(AUIPlugin.AUIFileTree.HandleCreateDir)

function AUIPlugin.AUIFileTree:HandleDeleteDir()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "，以及子文件和子文件夹吗?")
	if result ~= "YES" then
		return
	end
	if self._user_info.on_delete_dir ~= nil then
		self._user_info.on_delete_dir(self._user_info.path)
	end
	ALittle.File_DeleteDeepDir(self._user_info.path)
	self:RemoveFromParent()
end
AUIPlugin.AUIFileTree.HandleDeleteDir = Lua.CoWrap(AUIPlugin.AUIFileTree.HandleDeleteDir)

function AUIPlugin.AUIFileTree.__getter:is_tree()
	return true
end

function AUIPlugin.AUIFileTree:Refresh()
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
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.root = false
			info.on_select_file = self._user_info.on_select_file
			info.on_create_file = self._user_info.on_create_file
			info.on_delete_file = self._user_info.on_delete_file
			info.on_delete_dir = self._user_info.on_delete_dir
			info.on_right_menu = self._user_info.on_right_menu
			self:AddChild(AUIPlugin.AUIFileTree(self._ctrl_sys, info))
		end
	end
	if add_file ~= nil then
		ALittle.List_Sort(add_file)
		for index, name in ___ipairs(add_file) do
			local attr = map[name]
			local info = {}
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.root = false
			info.on_select_file = self._user_info.on_select_file
			info.on_create_file = self._user_info.on_create_file
			info.on_delete_file = self._user_info.on_delete_file
			info.on_delete_dir = self._user_info.on_delete_dir
			info.on_right_menu = self._user_info.on_right_menu
			self:AddChild(AUIPlugin.AUIFileTreeItem(self._ctrl_sys, info))
		end
	end
	self:DispatchEvent(___all_struct[-431205740], {})
end

function AUIPlugin.AUIFileTree:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchFile(name, list)
	end
	return list
end

function AUIPlugin.AUIFileTree:FindFile(full_path)
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

function AUIPlugin.AUIFileTree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function AUIPlugin.AUIFileTree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function AUIPlugin.AUIFileTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function AUIPlugin.AUIFileTree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function AUIPlugin.AUIFileTree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function AUIPlugin.AUIFileTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function AUIPlugin.AUIFileTree.__getter:childs()
	return self._body.childs
end

function AUIPlugin.AUIFileTree.__getter:child_count()
	return self._body.child_count
end

function AUIPlugin.AUIFileTree:HasChild(child)
	return self._body:HasChild(child)
end

function AUIPlugin.AUIFileTree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function AUIPlugin.AUIFileTree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	child.group = nil
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function AUIPlugin.AUIFileTree:SpliceChild(index, count)
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

function AUIPlugin.AUIFileTree:RemoveAllChild()
	for index, child in ___ipairs(self.childs) do
		child.group = nil
	end
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function AUIPlugin.AUIFileTree.__getter:width()
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

function AUIPlugin.AUIFileTree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function AUIPlugin.AUIFileTree.__getter:fold()
	return self._body.visible
end

function AUIPlugin.AUIFileTree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function AUIPlugin.AUIFileTree.__getter:max_right()
	return self.width
end

function AUIPlugin.AUIFileTree.__getter:max_bottom()
	return self.height
end

assert(AUIPlugin.AUIFileTreeLogic, " extends class:AUIPlugin.AUIFileTreeLogic is nil")
AUIPlugin.AUIFileTreeItem = Lua.Class(AUIPlugin.AUIFileTreeLogic, "AUIPlugin.AUIFileTreeItem")

function AUIPlugin.AUIFileTreeItem:Ctor(ctrl_sys, user_info)
	___rawset(self, "_item", ctrl_sys:CreateControl("file_tree_item", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_button.selected = false
	self._item_button.group = user_info.group
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
	self._item_button:AddEventListener(___all_struct[-1604617962], self, self.HandleKeyDown)
	self._item_button._user_data = self
	self._item_button.text = self._user_info.name
end

function AUIPlugin.AUIFileTreeItem.__getter:is_tree()
	return false
end

function AUIPlugin.AUIFileTreeItem.__getter:fold()
	return false
end

function AUIPlugin.AUIFileTreeItem.__setter:fold(value)
end

function AUIPlugin.AUIFileTreeItem:HandleClick(event)
	if self._user_info.on_select_file ~= nil then
		self._user_info.on_select_file(self._user_info)
	end
end

function AUIPlugin.AUIFileTreeItem:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	if ALittle.String_Find(self._user_info.name, name) ~= nil then
		ALittle.List_Push(list, self)
	end
	return list
end

function AUIPlugin.AUIFileTreeItem:FindFile(full_path)
	if self._user_info.path == full_path then
		return self
	end
	return nil
end

function AUIPlugin.AUIFileTreeItem:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	if self._user_info.on_right_menu ~= nil then
		self._user_info.on_right_menu(self._user_info, menu)
	end
	menu:AddItem("重命名", Lua.Bind(self.HandleRenameFile, self))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteFile, self))
	menu:Show()
end

function AUIPlugin.AUIFileTreeItem:HandleKeyDown(event)
	if event.sym == 1073741883 then
		self:HandleRenameFile()
	end
end

function AUIPlugin.AUIFileTreeItem:HandleDeleteFile()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "吗?")
	if result ~= "YES" then
		return
	end
	if self._user_info.on_delete_file ~= nil then
		self._user_info.on_delete_file(self._user_info.path)
	end
	ALittle.File_DeleteFile(self._user_info.path)
	local parent = self.parent
	self:RemoveFromParent()
	if parent ~= nil then
		parent:DispatchEvent(___all_struct[-431205740], {})
	end
end
AUIPlugin.AUIFileTreeItem.HandleDeleteFile = Lua.CoWrap(AUIPlugin.AUIFileTreeItem.HandleDeleteFile)

function AUIPlugin.AUIFileTreeItem:HandleRenameFile()
	local old_name = self._user_info.name
	local old_path = self._user_info.path
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local x, y = self:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(file_name, x, y, 200)
	if new_name == nil or new_name == "" then
		return
	end
	local new_path = ALittle.File_GetFilePathByPath(old_path) .. "/" .. new_name
	if ALittle.File_GetFileAttr(new_path) ~= nil then
		g_AUITool:ShowNotice("提示", "文件名已存在")
		return
	end
	self._user_info.path = new_path
	self._user_info.name = new_name
	self._item_button.text = self._user_info.name
	if self._user_info.on_delete_file ~= nil then
		self._user_info.on_delete_file(old_path)
	end
	ALittle.File_RenameFile(old_path, new_path)
	local create_event = {}
	create_event.path = new_path
	self:DispatchEvent(___all_struct[-2082217254], create_event)
end
AUIPlugin.AUIFileTreeItem.HandleRenameFile = Lua.CoWrap(AUIPlugin.AUIFileTreeItem.HandleRenameFile)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIFileTreeLayout = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIFileTreeLayout")

function AUIPlugin.AUIFileTreeLayout:Ctor(ctrl_sys)
	___rawset(self, "_group", {})
end

function AUIPlugin.AUIFileTreeLayout:SetRoot(path, on_right_menu)
	self._file_scroll_screen:RemoveAllChild()
	if path == nil or path == "" then
		return
	end
	local attr = ALittle.File_GetFileAttr(path)
	if attr == nil or not attr.directory then
		return
	end
	local info = {}
	info.name = ALittle.File_GetFileNameByPath(path)
	info.path = path
	info.group = self._group
	info.root = true
	info.on_right_menu = on_right_menu
	info.on_select_file = Lua.Bind(self.HandleSelectFile, self)
	info.on_delete_file = Lua.Bind(self.HandleDeleteFile, self)
	info.on_create_file = Lua.Bind(self.HandleCreateFile, self)
	info.on_delete_dir = Lua.Bind(self.HandleDeleteDir, self)
	local tree = AUIPlugin.AUIFileTree(AUIPlugin.g_Control, info)
	self._file_scroll_screen:AddChild(tree)
end

function AUIPlugin.AUIFileTreeLayout:HandleSelectFile(user_info)
	local select_event = {}
	select_event.info = user_info
	self:DispatchEvent(___all_struct[2117383637], select_event)
end

function AUIPlugin.AUIFileTreeLayout:HandleCreateFile(path)
	local select_event = {}
	select_event.path = path
	self:DispatchEvent(___all_struct[-2082217254], select_event)
end

function AUIPlugin.AUIFileTreeLayout:HandleDeleteFile(path)
	local select_event = {}
	select_event.path = path
	self:DispatchEvent(___all_struct[-545221029], select_event)
end

function AUIPlugin.AUIFileTreeLayout:HandleDeleteDir(path)
	local select_event = {}
	select_event.path = path
	self:DispatchEvent(___all_struct[-1718818319], select_event)
end

function AUIPlugin.AUIFileTreeLayout:SetFold(index, fold)
	local tree = ALittle.Cast(AUIPlugin.AUIFileTree, ALittle.DisplayObject, self._file_scroll_screen:GetChildByIndex(index))
	if tree == nil then
		return
	end
	tree.fold = fold
end

function AUIPlugin.AUIFileTreeLayout:GetFileTree(full_path)
	for index, child in ___ipairs(self._file_scroll_screen.childs) do
		local item = child:FindFile(full_path)
		if item ~= nil then
			return item
		end
	end
	return nil
end

function AUIPlugin.AUIFileTreeLayout:ShowTreeItemFocus(target)
	target:ShowSelect()
	if target ~= self._file_scroll_screen then
		local parent = target.logic_parent
		while parent ~= nil and parent ~= self._file_scroll_screen do
			parent.fold = true
			parent = parent.logic_parent
		end
	end
	self._file_scroll_screen:AdjustScrollBar()
	local x, y = target:LocalToGlobal(self._file_scroll_screen.container)
	local target_x = (self._file_scroll_screen.view_width - target.width / 2) / 2 - x
	local target_y = (self._file_scroll_screen.view_height - target.height) / 2 - y
	if self._tree_loop_x ~= nil then
		self._tree_loop_x:Stop()
		self._tree_loop_x = nil
	end
	if self._tree_loop_y ~= nil then
		self._tree_loop_y:Stop()
		self._tree_loop_y = nil
	end
	self._tree_loop_x = ALittle.LoopLinear(self._file_scroll_screen, "container_x", target_x, 300, 0)
	self._tree_loop_x:Start()
	self._tree_loop_y = ALittle.LoopLinear(self._file_scroll_screen, "container_y", target_y, 300, 0)
	self._tree_loop_y:Start()
end

function AUIPlugin.AUIFileTreeLayout:HandleFileSearchClick(event)
	if self._search_info == nil or self._search_info.name ~= self._file_search_key.text then
		self._search_info = {}
		self._search_info.name = self._file_search_key.text
		self._search_info.index = 0
		self._search_info.list = {}
		for index, child in ___ipairs(self._file_scroll_screen.childs) do
			child:SearchFile(self._search_info.name, self._search_info.list)
		end
		self._search_info.count = ALittle.List_Len(self._search_info.list)
	end
	if self._search_info.count <= 0 then
		return
	end
	self._search_info.index = self._search_info.index + (1)
	if self._search_info.index > self._search_info.count then
		self._search_info.index = 1
	end
	local item = self._search_info.list[self._search_info.index]
	self:ShowTreeItemFocus(item)
end

end