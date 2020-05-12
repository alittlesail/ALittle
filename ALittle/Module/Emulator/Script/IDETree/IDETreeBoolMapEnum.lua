-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeBoolMapEnum = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeBoolMapEnum")

function IDETreeBoolMapEnum:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	local key = protobuf.reflection_getbool(self._rflct, self._msg, self._key_field)
	local value = protobuf.reflection_getint32(self._rflct, self._msg, self._value_field)
	local enum_descriptor = protobuf.fielddescriptor_enumtype(self._value_field)
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
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_bool_map_enum", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	if key then
		self._key_dropdown.text = "true"
	else
		self._key_dropdown.text = "false"
	end
	self._value_dropdown.data_list = data_list
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

function IDETreeBoolMapEnum:HandleKeySelectChanegd(event)
	if self._key_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, false)
	end
	self:Save()
end

function IDETreeBoolMapEnum:HandleValueSelectChanegd(event)
	local value = self._enum_value_map[event.target.text]
	if value == nil then
		return
	end
	local index = self._parent:GetChildIndex(self) - 1
	protobuf.reflection_setint32(self._rflct, self._msg, self._value_field, value)
	self:Save()
end

function IDETreeBoolMapEnum:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeBoolMapEnum:HandleDeleteClick(event)
	self._parent:Delete(self)
end

