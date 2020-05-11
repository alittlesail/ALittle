-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeValue = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeValue")

function IDETreeValue:Ctor(ctrl_sys, root, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	___rawset(self, "_cpp_type", protobuf.fielddescriptor_cpptype(field))
	local value = self:RefreshValue()
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_value", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] " .. field_name .. ": "
	self._value_input.text = ALittle.String_ToString(value)
	self._value_input.width = self.width - self._item_title.width - self._item_title.x - 2
	self._value_input.x = self._item_title.width + self._item_title.x
end

function IDETreeValue:RefreshValue()
	if self._cpp_type == 1 then
		return protobuf.reflection_getint32(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 3 then
		return protobuf.reflection_getuint32(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 2 then
		return protobuf.reflection_getint64(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 4 then
		return protobuf.reflection_getuint64(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 5 then
		return protobuf.reflection_getdouble(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 6 then
		return protobuf.reflection_getfloat(self._rflct, self._msg, self._field)
	elseif self._cpp_type == 9 then
		return protobuf.reflection_getstring(self._rflct, self._msg, self._field)
	end
	return nil
end

function IDETreeValue:HandleInputFocusOut(event)
	local text = self._value_input.text
	if self._cpp_type == 1 then
		protobuf.reflection_setint32(self._rflct, self._msg, self._field, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 3 then
		protobuf.reflection_setuint32(self._rflct, self._msg, self._field, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 2 then
		protobuf.reflection_setint64(self._rflct, self._msg, self._field, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 4 then
		protobuf.reflection_setuint64(self._rflct, self._msg, self._field, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 5 then
		protobuf.reflection_setdouble(self._rflct, self._msg, self._field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._cpp_type == 6 then
		protobuf.reflection_setfloat(self._rflct, self._msg, self._field, ALittle.Math_ToDoubleOrZero(text))
	elseif self._cpp_type == 9 then
		protobuf.reflection_setstring(self._rflct, self._msg, self._field, text)
	end
	local value = self:RefreshValue()
	self._value_input.text = ALittle.String_ToString(value)
	self:Save()
end

