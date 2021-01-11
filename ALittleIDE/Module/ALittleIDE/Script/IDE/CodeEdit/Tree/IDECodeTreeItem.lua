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
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})

assert(ALittleIDE.IDECodeTreeLogic, " extends class:ALittleIDE.IDECodeTreeLogic is nil")
ALittleIDE.IDECodeTreeItem = Lua.Class(ALittleIDE.IDECodeTreeLogic, "ALittleIDE.IDECodeTreeItem")

function ALittleIDE.IDECodeTreeItem:Ctor(ctrl_sys, user_info)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_code_tree_item", self))
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

function ALittleIDE.IDECodeTreeItem.__getter:is_tree()
	return false
end

function ALittleIDE.IDECodeTreeItem.__getter:fold()
	return false
end

function ALittleIDE.IDECodeTreeItem.__setter:fold(value)
end

function ALittleIDE.IDECodeTreeItem:HandleClick(event)
	ALittleIDE.g_IDECenter.center.content_edit:StartEditCodeBySelect(self._user_info.name, self._user_info)
end

function ALittleIDE.IDECodeTreeItem:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	if ALittle.String_Find(self._user_info.name, name) ~= nil then
		ALittle.List_Push(list, self)
	end
	return list
end

function ALittleIDE.IDECodeTreeItem:FindFile(full_path)
	if self._user_info.path == full_path then
		return self
	end
	return nil
end

function ALittleIDE.IDECodeTreeItem:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(self._user_info.path) == self._user_info.project.upper_ext then
		self._user_info.project:OnTreeItemMenu(self._user_info.path, menu)
	end
	menu:AddItem("重命名", Lua.Bind(self.HandleRenameFile, self))
	menu:AddItem("剪切", Lua.Bind(self.HandleCutFile, self))
	menu:AddItem("复制", Lua.Bind(self.HandleCopyFile, self))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteFile, self))
	menu:Show()
end

function ALittleIDE.IDECodeTreeItem:HandleKeyDown(event)
	if event.sym == 1073741883 then
		self:HandleRenameFile()
	end
end

function ALittleIDE.IDECodeTreeItem:HandleDeleteFile()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "吗?")
	if result ~= "YES" then
		return
	end
	self:OnDelete()
	ALittle.File_DeleteFile(self._user_info.path)
	self:RemoveFromParent()
	ALittleIDE.g_IDECenter.center.content_edit:CloseTabByName(ALittleIDE.IDECodeTabChild, self._user_info.name)
end
ALittleIDE.IDECodeTreeItem.HandleDeleteFile = Lua.CoWrap(ALittleIDE.IDECodeTreeItem.HandleDeleteFile)

function ALittleIDE.IDECodeTreeItem:HandleCutFile()
	local old_name = self._user_info.name
	local old_path = self._user_info.path
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit:GetTabChildById(ALittleIDE.IDECodeTabChild, old_path)
	if tab_child ~= nil and tab_child.save ~= true then
		ALittleIDE.g_IDECenter.center.code_list:SetCutTreeItem(nil)
		g_AUITool:ShowNotice("提示", "请先保存再重命名")
		return
	end
	ALittleIDE.g_IDECenter.center.code_list:SetCutTreeItem(self)
end

function ALittleIDE.IDECodeTreeItem:HandleCopyFile()
	ALittleIDE.g_IDECenter.center.code_list:SetCopyTreeItem(self)
end

function ALittleIDE.IDECodeTreeItem:HandleRenameFile()
	local old_name = self._user_info.name
	local old_path = self._user_info.path
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit:GetTabChildById(ALittleIDE.IDECodeTabChild, old_path)
	if tab_child ~= nil and tab_child.save ~= true then
		g_AUITool:ShowNotice("提示", "请先保存再重命名")
		return
	end
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local x, y = self:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(file_name, x, y, 200)
	if new_name == nil or new_name == "" then
		return
	end
	local new_path = ALittle.File_GetFilePathByPath(old_path) .. "/" .. new_name
	if new_path == old_path then
		return
	end
	if ALittle.File_GetFileAttr(new_path) ~= nil then
		g_AUITool:ShowNotice("提示", "文件名已存在")
		return
	end
	self._user_info.path = new_path
	self._user_info.name = new_name
	self._item_button.text = self._user_info.name
	if tab_child ~= nil then
		ALittleIDE.g_IDECenter.center.content_edit:CloseTab(tab_child.tab_body)
	end
	if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(old_path) == self._user_info.project.upper_ext then
		self._user_info.project:RemoveFile(old_path)
	end
	ALittle.File_RenameFile(old_path, new_path)
	if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(old_path) == self._user_info.project.upper_ext then
		self._user_info.project:UpdateFile(self._user_info.module_path, self._user_info.path)
	end
	if tab_child ~= nil then
		ALittleIDE.g_IDECenter.center.content_edit:StartEditCodeBySelect(self._user_info.name, self._user_info)
	end
end
ALittleIDE.IDECodeTreeItem.HandleRenameFile = Lua.CoWrap(ALittleIDE.IDECodeTreeItem.HandleRenameFile)

function ALittleIDE.IDECodeTreeItem:OnDelete()
	if self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(self._user_info.path) == self._user_info.project.upper_ext then
		self._user_info.project:RemoveFile(self._user_info.path)
	end
end

end