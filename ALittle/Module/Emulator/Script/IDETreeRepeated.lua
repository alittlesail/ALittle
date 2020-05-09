-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeRepeated = Lua.Class(Emulator.IDETree, "Emulator.IDETreeRepeated")

function IDETreeRepeated:Ctor(ctrl_sys, field_name, sub_type)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_repeated", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[repeated " .. sub_type .. "] " .. field_name .. " "
	self._add_button.x = self._item_title.x + self._item_title.width
	self._head.width = self._add_button.x + self._add_button.width + 2
	self:Init()
end

function IDETreeRepeated:HandleAddClick(event)
end

