-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local Emulator = Emulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
Emulator.IDETreeEnumMapEnum = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeEnumMapEnum")

function Emulator.IDETreeEnumMapEnum:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	local key = protobuf.reflection_getenumvalue(self._rflct, self._msg, self._key_field)
	local enum_descriptor = protobuf.fielddescriptor_enumtype(self._key_field)
	local value_count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local key_data_list = {}
	___rawset(self, "_key_enum_value_map", {})
	local key_string = ""
	local i = 0
	while true do
		if not(i < value_count) then break end
		local enum_value = protobuf.enumdescriptor_value(enum_descriptor, i)
		key_data_list[i + 1] = protobuf.enumvaluedescriptor_name(enum_value)
		local enum_number = protobuf.enumvaluedescriptor_number(enum_value)
		self._key_enum_value_map[key_data_list[i + 1]] = enum_number
		if enum_number == key then
			key_string = key_data_list[i + 1]
		end
		i = i+(1)
	end
	local value = protobuf.reflection_getenumvalue(self._rflct, self._msg, self._value_field)
	enum_descriptor = protobuf.fielddescriptor_enumtype(self._value_field)
	value_count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local value_data_list = {}
	___rawset(self, "_key_enum_value_map", {})
	local value_string = ""
	local i = 0
	while true do
		if not(i < value_count) then break end
		local enum_value = protobuf.enumdescriptor_value(enum_descriptor, i)
		value_data_list[i + 1] = protobuf.enumvaluedescriptor_name(enum_value)
		local enum_number = protobuf.enumvaluedescriptor_number(enum_value)
		self._key_enum_value_map[value_data_list[i + 1]] = enum_number
		if enum_number == value then
			value_string = value_data_list[i + 1]
		end
		i = i+(1)
	end
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_enum_map_enum", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	self._key_dropdown.data_list = key_data_list
	self._key_dropdown.text = key_string
	self._value_dropdown.data_list = value_data_list
	self._value_dropdown.text = value_string
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

function Emulator.IDETreeEnumMapEnum:HandleKeySelectChanegd(event)
	local value = self._key_enum_value_map[event.target.text]
	if value == nil then
		return
	end
	protobuf.reflection_setenumvalue(self._rflct, self._msg, self._key_field, value)
	self:Save()
end

function Emulator.IDETreeEnumMapEnum:HandleValueSelectChanegd(event)
	local value = self._value_enum_value_map[event.target.text]
	if value == nil then
		return
	end
	protobuf.reflection_setenumvalue(self._rflct, self._msg, self._value_field, value)
	self:Save()
end

function Emulator.IDETreeEnumMapEnum:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function Emulator.IDETreeEnumMapEnum:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end