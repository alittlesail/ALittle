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
Emulator.IDETreeEnum = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeEnum")

function Emulator.IDETreeEnum:Ctor(ctrl_sys, root, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local value = protobuf.reflection_getenumvalue(self._rflct, self._msg, self._field)
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
		local enum_number = protobuf.enumvaluedescriptor_number(enum_value)
		self._enum_value_map[data_list[i + 1]] = enum_number
		if enum_number == value then
			value_string = data_list[i + 1]
		end
		i = i+(1)
	end
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_enum", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] " .. field_name .. ": "
	self._value_dropdown.data_list = data_list
	self._value_dropdown.text = value_string
	self._value_dropdown.width = self.width - self._item_title.width - self._item_title.x - 2
	self._value_dropdown.x = self._item_title.width + self._item_title.x
	self:Init()
	self._value_dropdown.disabled = root.for_show
end

function Emulator.IDETreeEnum:HandleSelectChanegd(event)
	local value = self._enum_value_map[event.target.text]
	if value == nil then
		return
	end
	protobuf.reflection_setenumvalue(self._rflct, self._msg, self._field, value)
	self:Save()
end

end