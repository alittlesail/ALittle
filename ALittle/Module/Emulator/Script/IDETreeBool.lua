-- ALittle Generate Lua
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeBool = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeBool")

function IDETreeBool:Ctor(ctrl_sys, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local value = protobuf.reflection_getbool(self._rflct, self._msg, self._field)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_bool", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] " .. field_name .. ": "
	if value then
		self._value_dropdown.text = "true"
	else
		self._value_dropdown.text = "false"
	end
	self._value_dropdown.width = self.width - self._item_title.width - self._item_title.x - 2
	self._value_dropdown.x = self._item_title.width + self._item_title.x
end

function IDETreeBool:HandleSelectChanegd(event)
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._field, false)
	end
end

