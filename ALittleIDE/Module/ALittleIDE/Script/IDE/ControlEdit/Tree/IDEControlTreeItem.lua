-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
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
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittleIDE.IDEControlTreeLogic, " extends class:ALittleIDE.IDEControlTreeLogic is nil")
ALittleIDE.IDEControlTreeItem = Lua.Class(ALittleIDE.IDEControlTreeLogic, "ALittleIDE.IDEControlTreeItem")

function ALittleIDE.IDEControlTreeItem:Ctor(ctrl_sys, user_info)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_control_tree_item", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_button.selected = false
	self._item_button.group = user_info.group
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
	self._item_button._user_data = self
	self._item_title.text = self._user_info.name
end

function ALittleIDE.IDEControlTreeItem.__getter:is_tree()
	return false
end

function ALittleIDE.IDEControlTreeItem.__getter:fold()
	return false
end

function ALittleIDE.IDEControlTreeItem.__setter:fold(value)
end

function ALittleIDE.IDEControlTreeItem:HandleClick(event)
end

function ALittleIDE.IDEControlTreeItem:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	if ALittle.String_Find(self._user_info.name, name) ~= nil then
		ALittle.List_Push(list, self)
	end
	return list
end

function ALittleIDE.IDEControlTreeItem:FindFile(full_path)
	if self._user_info.path == full_path then
		return self
	end
	return nil
end

function ALittleIDE.IDEControlTreeItem:HandleRButtonDown(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("重命名", Lua.Bind(self.HandleRenameFile, self))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteFile, self))
	menu:Show()
end

function ALittleIDE.IDEControlTreeItem:HandleDeleteFile()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local result = g_AUITool:DeleteNotice("删除", "确定要删除" .. file_name .. "吗?")
	if result ~= "YES" then
		return
	end
	self:OnDelete()
	ALittle.File_DeleteFile(self._user_info.path)
	local parent = self.parent
	self:RemoveFromParent()
	if parent ~= nil then
		parent:DispatchEvent(___all_struct[-431205740], {})
	end
	ALittleIDE.g_IDECenter.center.content_edit:CloseTabByName(ALittleIDE.IDECodeTabChild, self._user_info.name)
end
ALittleIDE.IDEControlTreeItem.HandleDeleteFile = Lua.CoWrap(ALittleIDE.IDEControlTreeItem.HandleDeleteFile)

function ALittleIDE.IDEControlTreeItem:HandleRenameFile()
	local file_name = ALittle.File_GetFileNameByPath(self._user_info.path)
	local x, y = self:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(file_name, x, y, 200)
	if new_name == nil or new_name == "" then
		return
	end
	local old_name = self._user_info.name
	local old_path = self._user_info.path
	local new_path = ALittle.File_GetFilePathByPath(old_path) .. "/" .. new_name
	self._user_info.path = new_path
	self._user_info.name = new_name
	self._item_title.text = self._user_info.name
	ALittle.File_RenameFile(old_path, new_path)
	ALittleIDE.g_IDECenter.center.content_edit:RenameTabByName(ALittleIDE.IDECodeTabChild, old_name, self._user_info.name)
end
ALittleIDE.IDEControlTreeItem.HandleRenameFile = Lua.CoWrap(ALittleIDE.IDEControlTreeItem.HandleRenameFile)

function ALittleIDE.IDEControlTreeItem:OnDelete()
end

end