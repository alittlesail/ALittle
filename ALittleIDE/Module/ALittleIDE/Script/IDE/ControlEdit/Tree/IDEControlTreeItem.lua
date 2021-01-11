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
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
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
	self._item_button:AddEventListener(___all_struct[1301789264], self, self.HandleControlDragBegin)
	self._item_button:AddEventListener(___all_struct[1337289812], self, self.HandleControlDrag)
	self._item_button:AddEventListener(___all_struct[150587926], self, self.HandleControlDragEnd)
	self._item_button._user_data = self
	self._item_button.text = self._user_info.name
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
	if event.is_drag then
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:StartEditControlBySelect(self._user_info.module_name, self._user_info.name)
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
	menu:AddItem("复制控件名", Lua.Bind(self.HandleCopyName, self))
	menu:AddItem("复制并新建控件", Lua.Bind(self.HandleCopyInfo, self))
	menu:AddItem("继承并新建控件", Lua.Bind(self.HandleExtendsInfo, self))
	menu:AddItem("复制继承代码", Lua.Bind(self.HandleCopyExtends, self))
	menu:AddItem("修改控件名", Lua.Bind(self.HandleControlRename, self))
	menu:AddItem("删除", Lua.Bind(self.HandleDelete, self))
	menu:Show()
end

function ALittleIDE.IDEControlTreeItem:HandleDelete()
	local error = self._user_info.ui:CanDelete(self._user_info.name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local del_result = g_AUITool:DeleteNotice("提示", "确定要删除" .. self._user_info.name .. "吗?")
	if del_result ~= "YES" then
		return
	end
	error = self._user_info.ui:DeleteControl(self._user_info.name)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	self:OnDelete()
	self:RemoveFromParent()
	ALittleIDE.g_IDECenter.center.content_edit:CloseTabByName(ALittleIDE.IDEUITabChild, self._user_info.name)
end
ALittleIDE.IDEControlTreeItem.HandleDelete = Lua.CoWrap(ALittleIDE.IDEControlTreeItem.HandleDelete)

function ALittleIDE.IDEControlTreeItem:HandleCopyName()
	ALittle.System_SetClipboardText(self._user_info.name)
end

function ALittleIDE.IDEControlTreeItem:HandleCopyInfo()
	local old_name = self._user_info.name
	local x, y = self:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(old_name, x, y, self.width)
	if new_name == nil or old_name == new_name then
		return
	end
	self:ControlCopyInfo(old_name, new_name)
end
ALittleIDE.IDEControlTreeItem.HandleCopyInfo = Lua.CoWrap(ALittleIDE.IDEControlTreeItem.HandleCopyInfo)

function ALittleIDE.IDEControlTreeItem:HandleExtendsInfo()
	ALittleIDE.g_IDECenter.center.control_list:ShowExtendsControl(nil, self._user_info.module_name, self._user_info.name)
end

function ALittleIDE.IDEControlTreeItem:ControlCopyInfo(target_name, new_name)
	local error = ALittleIDE.IDEUtility_CheckName(new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local info = self._user_info.ui.control_map[new_name]
	if info ~= nil then
		g_AUITool:ShowNotice("错误", "控件名已存在:" .. new_name)
		return
	end
	info = self._user_info.ui.control_map[target_name]
	if info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. target_name)
		return
	end
	self._user_info.ui:SaveControl(new_name, ALittle.String_CopyTable(info.info))
	self.parent:Refresh()
	ALittleIDE.g_IDECenter.center.content_edit:StartEditControlBySelect(self._user_info.module_name, new_name)
end

function ALittleIDE.IDEControlTreeItem:HandleControlRename()
	local error = self._user_info.ui:CanDelete(self._user_info.name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit:GetTabChildById(ALittleIDE.IDEUITabChild, self._user_info.name)
	if tab_child ~= nil and tab_child.save ~= true then
		g_AUITool:ShowNotice("提示", "请先保存再重命名")
		return
	end
	local x, y = self:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(self._user_info.name, x, y, self.width)
	if new_name == nil or self._user_info.name == new_name then
		return
	end
	error = self._user_info.ui:RenameControl(self._user_info.name, new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local old_name = self._user_info.name
	self._user_info.name = new_name
	self._user_info.path = ALittle.File_GetFilePathByPath(self._user_info.path) .. "/" .. self._user_info.name
	self._user_info.name = new_name
	self._item_button.text = self._user_info.name
	if tab_child ~= nil then
		tab_child:Rename(self._user_info.name)
	end
	ALittleIDE.g_IDECenter.center.content_edit.main_tab:SetChildText(tab_child.tab_body, self._user_info.name)
end
ALittleIDE.IDEControlTreeItem.HandleControlRename = Lua.CoWrap(ALittleIDE.IDEControlTreeItem.HandleControlRename)

function ALittleIDE.IDEControlTreeItem:HandleCopyExtends()
	local name = self._user_info.name
	local save_info = {}
	save_info["__extends"] = name
	save_info["__module"] = self._user_info.module_name
	local copy_list = {}
	local info = {}
	info["index"] = 1
	info["info"] = save_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function ALittleIDE.IDEControlTreeItem:OnDelete()
end

function ALittleIDE.IDEControlTreeItem:HandleControlDragBegin(event)
	self._drag_shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if self._drag_shift == false then
		event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen
		ALittleIDE.g_IDECenter.center.control_list.scroll_screen:DispatchEvent(___all_struct[1301789264], event)
		return
	end
	local x, y = event.target:LocalToGlobal()
	self._drag_effect = ALittle.EffectImage(ALittleIDE.g_Control)
	self._drag_effect:Action(event.target)
	A_LayerManager:AddToTip(self._drag_effect)
	self._drag_effect.x = x
	self._drag_effect.y = y
	self._drag_effect.alpha = 0.6
end

function ALittleIDE.IDEControlTreeItem:HandleControlDrag(event)
	if self._drag_shift == false then
		event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen
		ALittleIDE.g_IDECenter.center.control_list.scroll_screen:DispatchEvent(___all_struct[1337289812], event)
		return
	end
	if self._drag_effect == nil then
		return
	end
	self._drag_effect.x = self._drag_effect.x + event.delta_x
	self._drag_effect.y = self._drag_effect.y + event.delta_y
end

function ALittleIDE.IDEControlTreeItem:HandleControlDragEnd(event)
	if self._drag_shift == false then
		event.target = ALittleIDE.g_IDECenter.center.control_list.scroll_screen
		ALittleIDE.g_IDECenter.center.control_list.scroll_screen:DispatchEvent(___all_struct[150587926], event)
		return
	end
	if self._drag_effect ~= nil then
		A_LayerManager:RemoveFromTip(self._drag_effect)
		self._drag_effect:Clear()
		self._drag_effect = nil
	end
	local tab_child = ALittle.Cast(ALittleIDE.IDEUITabChild, ALittleIDE.IDETabChild, ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child)
	if tab_child == nil then
		return
	end
	tab_child:QuickDragAddControl(event.abs_x, event.abs_y, self._user_info.module_name, self._user_info.name)
end

end