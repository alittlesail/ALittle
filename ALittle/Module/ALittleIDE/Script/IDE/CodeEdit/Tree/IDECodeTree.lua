-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

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

assert(ALittleIDE.IDECodeTreeLogic, " extends class:ALittleIDE.IDECodeTreeLogic is nil")
IDECodeTree = Lua.Class(ALittleIDE.IDECodeTreeLogic, "ALittleIDE.IDECodeTree")

function IDECodeTree:Ctor(ctrl_sys, user_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_code_tree_head", self))
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
		self._item_title.text = self._user_info.module_name
	else
		self._item_title.text = self._user_info.name
	end
	self:Refresh()
end

function IDECodeTree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function IDECodeTree:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建文件", Lua.Bind(self.HandleCreateFile, self))
	menu:AddItem("刷新", Lua.Bind(self.Refresh, self))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteDir, self))
	menu:Show()
end

function IDECodeTree:HandleCreateFile()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittle.File_WriteTextToFile("", self._user_info.path .. "/" .. name)
	self:Refresh()
end
IDECodeTree.HandleCreateFile = Lua.CoWrap(IDECodeTree.HandleCreateFile)

function IDECodeTree:HandleDeleteDir()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "，以及子文件和子文件夹吗?")
	if result ~= "YES" then
		return
	end
	ALittle.File_DeleteDeepDir(self._user_info.path)
	self:RemoveFromParent()
end
IDECodeTree.HandleDeleteDir = Lua.CoWrap(IDECodeTree.HandleDeleteDir)

function IDECodeTree.__getter:is_tree()
	return true
end

function IDECodeTree:Refresh()
	local map = ALittle.File_GetFileNameListByDir(self._user_info.path)
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
	local add_file = nil
	local add_dir = nil
	for name, attr in ___pairs(map) do
		if attr.mode == "directory" then
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
	if add_file ~= nil then
		ALittle.List_Sort(add_file)
		for index, name in ___ipairs(add_file) do
			local attr = map[name]
			local info = {}
			info.module_name = self._user_info.module_name
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.project = self._user_info.project
			info.root = false
			self:AddChild(IDECodeTreeItem(self._ctrl_sys, info))
		end
	end
	if add_dir ~= nil then
		ALittle.List_Sort(add_dir)
		for index, name in ___ipairs(add_dir) do
			local attr = map[name]
			local info = {}
			info.module_name = self._user_info.module_name
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.project = self._user_info.project
			info.root = false
			self:AddChild(IDECodeTree(self._ctrl_sys, info))
		end
	end
end

function IDECodeTree:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchFile(name, list)
	end
	return list
end

function IDECodeTree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDECodeTree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function IDECodeTree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function IDECodeTree.__getter:childs()
	return self._body.childs
end

function IDECodeTree.__getter:child_count()
	return self._body.child_count
end

function IDECodeTree:HasChild(child)
	return self._body:HasChild(child)
end

function IDECodeTree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function IDECodeTree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	child.group = nil
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function IDECodeTree:SpliceChild(index, count)
	if count == nil then
		count = self._child_count
	end
	if count <= 0 then
		return 0
	end
	local endv = index + count
	local i = index
	while true do
		if not(i < endv) then break end
		local child = self._childs[index]
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

function IDECodeTree:RemoveAllChild()
	for index, child in ___ipairs(self.childs) do
		child.group = nil
	end
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function IDECodeTree.__getter:width()
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

function IDECodeTree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function IDECodeTree.__getter:fold()
	return self._body.visible
end

function IDECodeTree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function IDECodeTree.__getter:max_right()
	return self.width
end

function IDECodeTree.__getter:max_bottom()
	return self.height
end

