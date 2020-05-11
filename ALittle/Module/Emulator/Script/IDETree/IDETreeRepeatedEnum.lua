-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeRepeatedEnum = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeRepeatedEnum")

function IDETreeRepeatedEnum:Ctor(ctrl_sys, root, parent, rflct, msg, field, index)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local value = protobuf.reflection_getrepeatedint32(self._rflct, self._msg, self._field, index)
	local enum_descriptor = protobuf.fielddescriptor_enumtype(field)
	local value_count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local data_list = {}
	___rawset(self, "_enum_value_map", {})
	local value_string = ""
	local i = 0
	while true do
		if not(i < value_count) then break end
		local enum_value = protobuf.enumdescriptor_value(enum_descriptor, i)
		data_list[i + 1] = protobuf.enumvaluedescriptor_name(enum_value)
		local number = protobuf.enumvaluedescriptor_number(enum_value)
		self._enum_value_map[data_list[i + 1]] = number
		if value == number then
			value_string = data_list[i + 1]
		end
		i = i+(1)
	end
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_repeated_enum", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] : "
	self._value_dropdown.data_list = data_list
	self._value_dropdown.text = value_string
	self._value_dropdown.width = self.width - self._item_title.width - self._item_title.x - 2 - self._insert_button.width - self._delete_button.width - 1
	self._value_dropdown.x = self._item_title.width + self._item_title.x
	self._insert_button.x = self._value_dropdown.x + self._value_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
end

function IDETreeRepeatedEnum:HandleSelectChanegd(event)
	local value = self._enum_value_map[event.target.text]
	if value == nil then
		return
	end
	local index = self._parent:GetChildIndex(self) - 1
	protobuf.reflection_setrepeatedint32(self._rflct, self._msg, self._field, index, value)
	self:Save()
end

function IDETreeRepeatedEnum:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeRepeatedEnum:HandleDeleteClick(event)
	self._parent:Delete(self)
end

