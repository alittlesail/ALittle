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

assert(ALittleIDE.IDECodeTreeLogic, " extends class:ALittleIDE.IDECodeTreeLogic is nil")
ALittleIDE.IDECodeTree = Lua.Class(ALittleIDE.IDECodeTreeLogic, "ALittleIDE.IDECodeTree")

function ALittleIDE.IDECodeTree:Ctor(ctrl_sys, user_info)
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
		self._item_button.text = "[" .. self._user_info.module_name .. "] " .. self._user_info.name
	else
		self._item_button.text = self._user_info.name
	end
	self:Refresh()
end

function ALittleIDE.IDECodeTree:HandleLButtonDown(event)
	if event.count == 1 then
		return
	end
	self.fold = not self.fold
end

function ALittleIDE.IDECodeTree:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	if self._user_info.project ~= nil then
		self._user_info.project:OnTreeMenu(self._user_info.path, menu)
	end
	menu:AddItem("新建ALittle文件", Lua.Bind(self.HandleCreateFile, self))
	menu:AddItem("新建文件夹", Lua.Bind(self.HandleCreateDir, self))
	menu:AddItem("刷新", Lua.Bind(self.Refresh, self))
	if ALittleIDE.g_IDECenter.center.code_list:GetCutTreeItem() ~= nil or ALittleIDE.g_IDECenter.center.code_list:GetCopyTreeItem() ~= nil then
		menu:AddItem("粘贴", Lua.Bind(self.PasteFile, self))
	end
	if not self._user_info.root then
		menu:AddItem("删除", Lua.Bind(self.HandleDeleteDir, self))
	end
	if self._user_info.root then
		menu:AddItem("添加模块", Lua.Bind(self.HandleAddModule, self))
		menu:AddItem("添加库", Lua.Bind(self.HandleAddLibrary, self))
	end
	local can_remove = self._user_info.root and self._user_info.module_name ~= "Std" and self._user_info.module_name ~= "Core" and self._user_info.module_name ~= "CEngine" and self._user_info.module_name ~= ALittleIDE.g_IDEProject.project.name
	if can_remove then
		menu:AddItem("移除模块", Lua.Bind(self.HandleRemoveModule, self))
	end
	menu:Show()
end

function ALittleIDE.IDECodeTree:HandleCreateFile()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	if ALittle.File_GetFileAttr(self._user_info.path .. "/" .. name .. ".alittle") ~= nil then
		g_AUITool:ShowNotice("提示", "文件名已存在")
		return
	end
	local content = "\nnamespace " .. ALittleIDE.g_IDEProject.project.name .. ";\n\nprotected class " .. name .. "\n{\n}\n"
	ALittle.File_WriteTextToFile(content, self._user_info.path .. "/" .. name .. ".alittle")
	self:Refresh()
end
ALittleIDE.IDECodeTree.HandleCreateFile = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleCreateFile)

function ALittleIDE.IDECodeTree:HandleCreateDir()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittle.File_MakeDir(self._user_info.path .. "/" .. name)
	self:Refresh()
end
ALittleIDE.IDECodeTree.HandleCreateDir = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleCreateDir)

function ALittleIDE.IDECodeTree:HandleAddModule()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittleIDE.g_IDECenter.center.code_list:AddModule(name)
end
ALittleIDE.IDECodeTree.HandleAddModule = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleAddModule)

function ALittleIDE.IDECodeTree:HandleAddLibrary()
	local x, y = self._head:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + self._head.height, 200)
	if name == nil or name == "" then
		return
	end
	ALittleIDE.g_IDECenter.center.code_list:AddLibrary(name)
end
ALittleIDE.IDECodeTree.HandleAddLibrary = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleAddLibrary)

function ALittleIDE.IDECodeTree:HandleDeleteDir()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "，以及子文件和子文件夹吗?")
	if result ~= "YES" then
		return
	end
	self:OnDelete()
	ALittle.File_DeleteDeepDir(self._user_info.path)
	self:RemoveFromParent()
end
ALittleIDE.IDECodeTree.HandleDeleteDir = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleDeleteDir)

function ALittleIDE.IDECodeTree:HandleRemoveModule()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("移除", "确定要移除" .. file_name .. "模块吗?")
	if result ~= "YES" then
		return
	end
	self:OnDelete()
	self:RemoveFromParent()
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("code_module", {})
	module_map[self._user_info.module_name] = nil
	ALittleIDE.g_IDEProject.project.config:SetConfig("code_module", module_map)
end
ALittleIDE.IDECodeTree.HandleRemoveModule = Lua.CoWrap(ALittleIDE.IDECodeTree.HandleRemoveModule)

function ALittleIDE.IDECodeTree.__getter:is_tree()
	return true
end

function ALittleIDE.IDECodeTree:PasteFile()
	local item = ALittleIDE.g_IDECenter.center.code_list:GetCutTreeItem()
	if item ~= nil then
		local path = ALittle.File_GetFilePathByPath(item.user_info.path)
		local name = ALittle.File_GetFileNameByPath(item.user_info.path)
		if path == self._user_info.path then
			return
		end
		ALittle.File_RenameFile(item.user_info.path, self._user_info.path .. "/" .. name)
		item:OnDelete()
		local parent = item.parent
		item:RemoveFromParent()
		if parent ~= nil then
			parent:DispatchEvent(___all_struct[-431205740], {})
		end
		ALittleIDE.g_IDECenter.center.content_edit:CloseTabByName(ALittleIDE.IDECodeTabChild, item.user_info.name)
		self:Refresh()
		ALittleIDE.g_IDECenter.center.code_list:ClearCutAndCopy()
		return
	end
	item = ALittleIDE.g_IDECenter.center.code_list:GetCopyTreeItem()
	if item ~= nil then
		local path = ALittle.File_GetFilePathByPath(item.user_info.path)
		local name = ALittle.File_GetFileNameByPath(item.user_info.path)
		if path == self._user_info.path then
			return
		end
		ALittle.File_CopyFile(item.user_info.path, self._user_info.path .. "/" .. name)
		self:Refresh()
		ALittleIDE.g_IDECenter.center.code_list:ClearCutAndCopy()
		return
	end
end

function ALittleIDE.IDECodeTree:Refresh()
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
			if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(child.user_info.path) == self._user_info.project.upper_ext then
				self._user_info.project:RemoveFile(child.user_info.path)
			end
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
			info.project = self._user_info.project
			info.root = false
			self:AddChild(ALittleIDE.IDECodeTree(self._ctrl_sys, info))
		end
	end
	if add_file ~= nil then
		ALittle.List_Sort(add_file)
		for index, name in ___ipairs(add_file) do
			local attr = map[name]
			local info = {}
			info.module_name = self._user_info.module_name
			info.module_path = self._user_info.module_path
			info.name = name
			info.path = self._user_info.path .. "/" .. name
			info.group = self._user_info.group
			info.project = self._user_info.project
			info.root = false
			self:AddChild(ALittleIDE.IDECodeTreeItem(self._ctrl_sys, info))
			if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(info.path) == self._user_info.project.upper_ext then
				self._user_info.project:UpdateFile(info.module_path, info.path)
			end
		end
	end
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDECodeTree:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	for k, child in ___ipairs(self._body.childs) do
		child:SearchFile(name, list)
	end
	return list
end

function ALittleIDE.IDECodeTree:FindFile(full_path)
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

function ALittleIDE.IDECodeTree:OnDelete()
	for index, child in ___ipairs(self.childs) do
		child:OnDelete()
	end
end

function ALittleIDE.IDECodeTree:HandleChildResize(event)
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDECodeTree:HandleHeadChanged(event)
	self._body.visible = event.target.selected
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDECodeTree:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function ALittleIDE.IDECodeTree:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function ALittleIDE.IDECodeTree:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittleIDE.IDECodeTree.__getter:childs()
	return self._body.childs
end

function ALittleIDE.IDECodeTree.__getter:child_count()
	return self._body.child_count
end

function ALittleIDE.IDECodeTree:HasChild(child)
	return self._body:HasChild(child)
end

function ALittleIDE.IDECodeTree:AddChild(child, index)
	if self._body:AddChild(child, index) == false then
		return false
	end
	child._logic_parent = self
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDECodeTree:RemoveChild(child)
	if self._body:RemoveChild(child) == false then
		return false
	end
	child.group = nil
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
	return true
end

function ALittleIDE.IDECodeTree:SpliceChild(index, count)
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

function ALittleIDE.IDECodeTree:RemoveAllChild()
	for index, child in ___ipairs(self.childs) do
		child.group = nil
	end
	self._body:RemoveAllChild()
	if self._body.abs_visible then
		self:DispatchEvent(___all_struct[-431205740], {})
	end
end

function ALittleIDE.IDECodeTree.__getter:width()
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

function ALittleIDE.IDECodeTree.__getter:height()
	local head_height = 0.0
	if self._head ~= nil then
		head_height = self._head.height
	end
	if self._body.visible then
		return head_height + self._body.height
	end
	return head_height
end

function ALittleIDE.IDECodeTree.__getter:fold()
	return self._body.visible
end

function ALittleIDE.IDECodeTree.__setter:fold(value)
	if value == self._body.visible then
		return
	end
	self._body.visible = value
	self._item_checkbutton.selected = value
	self:DispatchEvent(___all_struct[-431205740], {})
end

function ALittleIDE.IDECodeTree.__getter:max_right()
	return self.width
end

function ALittleIDE.IDECodeTree.__getter:max_bottom()
	return self.height
end

end