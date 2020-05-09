-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeMap = Lua.Class(Emulator.IDETree, "Emulator.IDETreeMap")

function IDETreeMap:Ctor(ctrl_sys, field_name, key_type, value_type)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_map", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[Map<" .. key_type .. ", " .. value_type .. ">] " .. field_name
	self:Init()
end

