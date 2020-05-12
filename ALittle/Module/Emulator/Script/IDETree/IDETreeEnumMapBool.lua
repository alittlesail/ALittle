-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeEnumMapBool = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeEnumMapBool")

function IDETreeEnumMapBool:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	local key = protobuf.reflection_getenumvalue(self._rflct, self._msg, self._key_field)
	local enum_descriptor = protobuf.fielddescriptor_enumtype(self._key_field)
	local value_count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local data_list = {}
	___rawset(self, "_enum_value_map", {})
	local key_string = ""
	local i = 0
	while true do
		if not(i < value_count) then break end
		local enum_value = protobuf.enumdescriptor_value(enum_descriptor, i)
		data_list[i + 1] = protobuf.enumvaluedescriptor_name(enum_value)
		local enum_number = protobuf.enumvaluedescriptor_number(enum_value)
		self._enum_value_map[data_list[i + 1]] = enum_number
		if enum_number == key then
			key_string = data_list[i + 1]
		end
		i = i+(1)
	end
	local value = protobuf.reflection_getbool(self._rflct, self._msg, self._value_field)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_enum_map_bool", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	self._key_dropdown.data_list = data_list
	self._key_dropdown.text = key_string
	if value then
		self._value_dropdown.text = "true"
	else
		self._value_dropdown.text = "false"
	end
	self._key_dropdown.x = self._item_title.width + self._item_title.x + 1
	self._value_dropdown.x = self._key_dropdown.width + self._key_dropdown.x + 1
	self._insert_button.x = self._value_dropdown.x + self._value_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._item.width = self._delete_button.x + self._delete_button.width + 1
	self.width = self._item.width
	self:Init()
	self._key_dropdown.disabled = root.for_show
	self._value_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function IDETreeEnumMapBool:HandleKeySelectChanegd(event)
	local value = self._enum_value_map[event.target.text]
	if value == nil then
		return
	end
	protobuf.reflection_setenumvalue(self._rflct, self._msg, self._key_field, value)
	self:Save()
end

function IDETreeEnumMapBool:HandleValueSelectChanegd(event)
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, false)
	end
	self:Save()
end

function IDETreeEnumMapBool:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeEnumMapBool:HandleDeleteClick(event)
	self._parent:Delete(self)
end

