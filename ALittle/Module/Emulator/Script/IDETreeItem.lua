-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

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

assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeItem = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeItem")

function IDETreeItem:Ctor(ctrl_sys, field_name, value_type)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_item", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_button.selected = false
	self._item_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
	self._item_button:AddEventListener(___all_struct[544684311], self, self.HandleMoveIn)
	self._item_button:AddEventListener(___all_struct[-1001723540], self, self.HandleMouseMove)
	self._item_button:AddEventListener(___all_struct[-1202439334], self, self.HandleMoveOut)
	self._item_button._user_data = self
	self._item_title.text = "[" .. value_type .. "] " .. field_name
end

function IDETreeItem:IsTree()
	return false
end

function IDETreeItem.__getter:fold()
	return false
end

function IDETreeItem.__setter:fold(value)
end

function IDETreeItem:GetDataListForAdd()
	return {}
end

function IDETreeItem:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	local description = ""
	if description ~= nil then
		if ALittle.String_Find(description, name) ~= nil then
			ALittle.List_Push(list, self)
			return list
		end
	end
	return list
end

