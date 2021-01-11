-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local Emulator = Emulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
Emulator.IDETreeEnumMapMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeEnumMapMessage")

function Emulator.IDETreeEnumMapMessage:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, detail_info)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	local value = protobuf.reflection_getenumvalue(self._rflct, self._msg, self._key_field)
	local enum_descriptor = protobuf.fielddescriptor_enumtype(self._key_field)
	local value_count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local data_list = {}
	___rawset(self, "_enum_value_map", {})
	local value_string = ""
	local i = 0
	while true do
		if not(i < value_count) then break end
		local enum_value = protobuf.enumdescriptor_value(enum_descriptor, i)
		data_list[i + 1] = protobuf.enumvaluedescriptor_name(enum_value)
		local enum_number = protobuf.enumvaluedescriptor_number(enum_value)
		self._enum_value_map[data_list[i + 1]] = enum_number
		if enum_number == value then
			value_string = data_list[i + 1]
		end
		i = i+(1)
	end
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_enum_map_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. detail_info.info.name .. "] : "
	self._key_dropdown.data_list = data_list
	self._key_dropdown.text = value_string
	self._key_dropdown.x = self._item_title.width + self._item_title.x + 1
	self._insert_button.x = self._key_dropdown.x + self._key_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._head.width = self._delete_button.x + self._delete_button.width + 1
	self:Init()
	self._key_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function Emulator.IDETreeEnumMapMessage:GetDetailInfo()
	return self._detail_info
end

function Emulator.IDETreeEnumMapMessage:HandleKeySelectChanegd(event)
	local value = self._enum_value_map[event.target.text]
	if value == nil then
		return
	end
	protobuf.reflection_setenumvalue(self._rflct, self._msg, self._key_field, value)
	self:Save()
end

function Emulator.IDETreeEnumMapMessage:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function Emulator.IDETreeEnumMapMessage:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end