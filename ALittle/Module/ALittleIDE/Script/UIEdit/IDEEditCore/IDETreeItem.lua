
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
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
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
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

assert(IDETreeLogic, " extends class:IDETreeLogic is nil")
IDETreeItem = ALittle.Class(IDETreeLogic, "ALittleIDE.IDETreeItem")

function IDETreeItem:Ctor(ctrl_sys, user_info, tab_child)
	if self._user_info.extends then
		___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_item_disabled", self))
	else
		___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_item", self))
	end
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_button.selected = false
	self._item_button.group_name = self._tab_child.group_name
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._item_button:AddEventListener(___all_struct[-1001723540], self, self.HandleMouseMove)
	self._item_button:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._item_button:AddEventListener(___all_struct[1301789264], self, self.HandleDragBegin)
	self._item_button:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self._item_button:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
	self._item_button:AddEventListener(___all_struct[-641444818], g_IDEControlTree, g_IDEControlTree.HandleControlTreeItemRightClick)
	self._item_button._user_data = self
end

function IDETreeItem.__getter:fold()
	return false
end

function IDETreeItem.__setter:fold(value)
end

function IDETreeItem:IsTree()
	return false
end

function IDETreeItem:GetDataListForAdd()
	return {}
end

function IDETreeItem:CalcInfo()
	return ALittle.String_CopyTable(self._user_info.base)
end

function IDETreeItem:SearchLink(name, list)
	if list == nil then
		list = {}
	end
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link ~= nil then
		if ALittle.Find(link, name) ~= nil then
			ALittle.Push(list, self)
			return list
		end
	end
	return list
end

function IDETreeItem:SearchEvent(name, list)
	if list == nil then
		list = {}
	end
	local event = self._user_info.base.__event
	if event == nil then
		event = self._user_info.default.__event
	end
	if event ~= nil then
		for k, v in ___ipairs(event) do
			if ALittle.Find(v.func, name) ~= nil then
				ALittle.Push(list, self)
				return list
			end
		end
	end
	return list
end

function IDETreeItem:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	local description = self._user_info.base.description
	if description == nil then
		description = self._user_info.default.description
	end
	if description ~= nil then
		if ALittle.Find(description, name) ~= nil then
			ALittle.Push(list, self)
			return list
		end
	end
	return list
end

function IDETreeItem:SearchTargetClass(name, list)
	if list == nil then
		list = {}
	end
	local target_class = self._user_info.base.__target_class
	if target_class == nil then
		target_class = self._user_info.default.__target_class
	end
	if target_class ~= nil then
		local target_class_str = ALittle.String_Join(target_class, ".")
		if ALittle.Find(target_class_str, name) ~= nil then
			ALittle.Push(list, self)
			return list
		end
	end
	return list
end

function IDETreeItem:SearchTextureName(name, list)
	if list == nil then
		list = {}
	end
	local texture_name = self._user_info.base.texture_name
	if texture_name == nil then
		texture_name = self._user_info.default.texture_name
	end
	if texture_name ~= nil then
		if ALittle.Find(texture_name, name) ~= nil then
			ALittle.Push(list, self)
			return list
		end
	end
	return list
end

function IDETreeItem:EditPickUp(x, y)
	if self._user_info.extends then
		return nil
	end
	local object = self._user_info.object
	local pick_this, rel_x, rel_y = object:PickUpSelf(x, y)
	if pick_this ~= nil then
		return self
	end
	return nil
end

function IDETreeItem:QuickPickUp(x, y, list)
end

function IDETreeItem:SelectPickUp(x, y)
	if self._user_info.extends then
		return nil, nil
	end
	local pick_this, rel_x, rel_y = self._item_button:PickUpSelf(x, y)
	if pick_this ~= nil then
		return nil, self
	end
	return nil, nil
end

