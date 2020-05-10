-- ALittle Generate Lua
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeRepeatedBool = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeRepeatedBool")

function IDETreeRepeatedBool:Ctor(ctrl_sys, parent, rflct, msg, field, index)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local value = protobuf.reflection_getrepeatedbool(self._rflct, self._msg, self._field, index)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_repeated_bool", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] : "
	if value then
		self._value_dropdown.text = "true"
	else
		self._value_dropdown.text = "false"
	end
	self._value_dropdown.width = self.width - self._item_title.width - self._item_title.x - 2 - self._insert_button.width - self._delete_button.width - 1
	self._value_dropdown.x = self._item_title.width + self._item_title.x
	self._insert_button.x = self._value_dropdown.x + self._value_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
end

function IDETreeRepeatedBool:HandleSelectChanegd(event)
	local index = self._parent:GetChildIndex(self) - 1
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setrepeatedbool(self._rflct, self._msg, self._field, index, true)
	else
		protobuf.reflection_setrepeatedbool(self._rflct, self._msg, self._field, index, false)
	end
end

function IDETreeRepeatedBool:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeRepeatedBool:HandleDeleteClick(event)
	self._parent:Delete(self)
end

