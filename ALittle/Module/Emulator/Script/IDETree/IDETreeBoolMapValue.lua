-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeBoolMapValue = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeBoolMapValue")

function IDETreeBoolMapValue:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	___rawset(self, "_value_cpp_type", protobuf.fielddescriptor_cpptype(value_field))
	local key = protobuf.reflection_getbool(self._rflct, self._msg, self._key_field)
	local value = self:RefreshValue()
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_bool_map_value", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	if key then
		self._key_dropdown.text = "true"
	else
		self._key_dropdown.text = "false"
	end
	self._value_input.text = ALittle.String_ToString(value)
	self._key_dropdown.x = self._item_title.width + self._item_title.x + 1
	self._value_input.x = self._key_dropdown.width + self._key_dropdown.x + 1
	self._insert_button.x = self._value_input.x + self._value_input.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._item.width = self._delete_button.x + self._delete_button.width + 1
	self.width = self._item.width
end

function IDETreeBoolMapValue:RefreshValue()
	if self._value_cpp_type == 1 then
		return protobuf.reflection_getint32(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 3 then
		return protobuf.reflection_getuint32(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 2 then
		return protobuf.reflection_getint64(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 4 then
		return protobuf.reflection_getuint64(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 5 then
		return protobuf.reflection_getdouble(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 6 then
		return protobuf.reflection_getfloat(self._rflct, self._msg, self._value_field)
	elseif self._value_cpp_type == 9 then
		return protobuf.reflection_getstring(self._rflct, self._msg, self._value_field)
	end
	return nil
end

function IDETreeBoolMapValue:HandleKeySelectChanegd(event)
	if self._key_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, false)
	end
	self:Save()
end

function IDETreeBoolMapValue:HandleValueFocusOut(event)
	local text = self._value_input.text
	if self._value_cpp_type == 1 then
		protobuf.reflection_setint32(self._rflct, self._msg, self._value_field, ALittle.Math_ToIntOrZero(text))
	elseif self._value_cpp_type == 3 then
		protobuf.reflection_setuint32(self._rflct, self._msg, self._value_field, ALittle.Math_ToIntOrZero(text))
	elseif self._value_cpp_type == 2 then
		protobuf.reflection_setint64(self._rflct, self._msg, self._value_field, ALittle.Math_ToIntOrZero(text))
	elseif self._value_cpp_type == 4 then
		protobuf.reflection_setuint64(self._rflct, self._msg, self._value_field, ALittle.Math_ToIntOrZero(text))
	elseif self._value_cpp_type == 5 then
		protobuf.reflection_setdouble(self._rflct, self._msg, self._value_field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._value_cpp_type == 6 then
		protobuf.reflection_setfloat(self._rflct, self._msg, self._value_field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._value_cpp_type == 9 then
		protobuf.reflection_setstring(self._rflct, self._msg, self._value_field, text)
	end
	local value = self:RefreshValue()
	self._value_input.text = ALittle.String_ToString(value)
	self:Save()
end

function IDETreeBoolMapValue:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeBoolMapValue:HandleDeleteClick(event)
	self._parent:Delete(self)
end

