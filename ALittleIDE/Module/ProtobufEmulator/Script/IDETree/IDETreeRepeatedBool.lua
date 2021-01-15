-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ProtobufEmulator.IDETreeLogic, " extends class:ProtobufEmulator.IDETreeLogic is nil")
ProtobufEmulator.IDETreeRepeatedBool = Lua.Class(ProtobufEmulator.IDETreeLogic, "ProtobufEmulator.IDETreeRepeatedBool")

function ProtobufEmulator.IDETreeRepeatedBool:Ctor(ctrl_sys, root, parent, rflct, msg, field, index)
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
	self:Init()
	self._value_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function ProtobufEmulator.IDETreeRepeatedBool:HandleSelectChanegd(event)
	local index = self._parent:GetChildIndex(self) - 1
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setrepeatedbool(self._rflct, self._msg, self._field, index, true)
	else
		protobuf.reflection_setrepeatedbool(self._rflct, self._msg, self._field, index, false)
	end
	self:Save()
end

function ProtobufEmulator.IDETreeRepeatedBool:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function ProtobufEmulator.IDETreeRepeatedBool:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end