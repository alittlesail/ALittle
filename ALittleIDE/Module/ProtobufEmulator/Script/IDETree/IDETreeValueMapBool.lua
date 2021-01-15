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
ProtobufEmulator.IDETreeValueMapBool = Lua.Class(ProtobufEmulator.IDETreeLogic, "ProtobufEmulator.IDETreeValueMapBool")

function ProtobufEmulator.IDETreeValueMapBool:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	___rawset(self, "_key_cpp_type", protobuf.fielddescriptor_cpptype(key_field))
	local key = self:RefreshValue()
	local value = protobuf.reflection_getbool(self._rflct, self._msg, self._value_field)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_value_map_bool", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	self._key_input.text = ALittle.String_ToString(key)
	if value then
		self._value_dropdown.text = "true"
	else
		self._value_dropdown.text = "false"
	end
	self._key_input.x = self._item_title.width + self._item_title.x + 1
	self._value_dropdown.x = self._key_input.width + self._key_input.x + 1
	self._insert_button.x = self._value_dropdown.x + self._value_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._item.width = self._delete_button.x + self._delete_button.width + 1
	self.width = self._item.width
	self:Init()
	self._key_input.editable = not root.for_show
	self._value_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function ProtobufEmulator.IDETreeValueMapBool:RefreshValue()
	if self._key_cpp_type == 1 then
		return protobuf.reflection_getint32(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 3 then
		return protobuf.reflection_getuint32(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 2 then
		return protobuf.reflection_getint64(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 4 then
		return protobuf.reflection_getuint64(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 5 then
		return protobuf.reflection_getdouble(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 6 then
		return protobuf.reflection_getfloat(self._rflct, self._msg, self._key_field)
	elseif self._key_cpp_type == 9 then
		return protobuf.reflection_getstring(self._rflct, self._msg, self._key_field)
	end
	return nil
end

function ProtobufEmulator.IDETreeValueMapBool:HandleKeyInputFocusOut(event)
	local text = self._key_input.text
	if self._key_cpp_type == 1 then
		protobuf.reflection_setint32(self._rflct, self._msg, self._key_field, ALittle.Math_ToIntOrZero(text))
	elseif self._key_cpp_type == 3 then
		protobuf.reflection_setuint32(self._rflct, self._msg, self._key_field, ALittle.Math_ToIntOrZero(text))
	elseif self._key_cpp_type == 2 then
		protobuf.reflection_setint64(self._rflct, self._msg, self._key_field, ALittle.Math_ToIntOrZero(text))
	elseif self._key_cpp_type == 4 then
		protobuf.reflection_setuint64(self._rflct, self._msg, self._key_field, ALittle.Math_ToIntOrZero(text))
	elseif self._key_cpp_type == 5 then
		protobuf.reflection_setdouble(self._rflct, self._msg, self._key_field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._key_cpp_type == 6 then
		protobuf.reflection_setfloat(self._rflct, self._msg, self._key_field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._key_cpp_type == 9 then
		protobuf.reflection_setstring(self._rflct, self._msg, self._key_field, text)
	end
	local value = self:RefreshValue()
	self._key_input.text = ALittle.String_ToString(value)
	self:Save()
end

function ProtobufEmulator.IDETreeValueMapBool:HandleValueSelectChanegd(event)
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, false)
	end
	self:Save()
end

function ProtobufEmulator.IDETreeValueMapBool:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function ProtobufEmulator.IDETreeValueMapBool:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end