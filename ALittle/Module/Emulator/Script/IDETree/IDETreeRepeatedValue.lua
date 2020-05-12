-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
IDETreeRepeatedValue = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeRepeatedValue")

function IDETreeRepeatedValue:Ctor(ctrl_sys, root, parent, rflct, msg, field, index)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	___rawset(self, "_cpp_type", protobuf.fielddescriptor_cpptype(field))
	local value = self:RefreshValue(index)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_repeated_value", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(field) .. "] : "
	self._value_input.text = ALittle.String_ToString(value)
	self._value_input.width = self.width - self._item_title.width - self._item_title.x - 2 - self._insert_button.width - self._delete_button.width - 1
	self._value_input.x = self._item_title.width + self._item_title.x
	self._insert_button.x = self._value_input.x + self._value_input.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self:Init()
	self._value_input.editable = not root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function IDETreeRepeatedValue:RefreshValue(index)
	if self._cpp_type == 1 then
		return protobuf.reflection_getrepeatedint32(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 3 then
		return protobuf.reflection_getrepeateduint32(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 2 then
		return protobuf.reflection_getrepeatedint64(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 4 then
		return protobuf.reflection_getrepeateduint64(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 5 then
		return protobuf.reflection_getrepeateddouble(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 6 then
		return protobuf.reflection_getrepeatedfloat(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 9 then
		return protobuf.reflection_getrepeatedstring(self._rflct, self._msg, self._field, index)
	end
	return nil
end

function IDETreeRepeatedValue:HandleInputFocusOut(event)
	local text = self._value_input.text
	local index = self._parent:GetChildIndex(self) - 1
	if self._cpp_type == 1 then
		protobuf.reflection_setrepeatedint32(self._rflct, self._msg, self._field, index, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 3 then
		protobuf.reflection_setrepeateduint32(self._rflct, self._msg, self._field, index, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 2 then
		protobuf.reflection_setrepeatedint64(self._rflct, self._msg, self._field, index, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 4 then
		protobuf.reflection_setrepeateduint64(self._rflct, self._msg, self._field, index, ALittle.Math_ToIntOrZero(text))
	elseif self._cpp_type == 5 then
		protobuf.reflection_setrepeateddouble(self._rflct, self._msg, self._field, index, ALittle.Math_ToDoubleOrZero(text))
	elseif self._cpp_type == 6 then
		protobuf.reflection_setrepeatedfloat(self._rflct, self._msg, self._field, index, ALittle.Math_ToDoubleOrZero(text))
	elseif self._cpp_type == 9 then
		protobuf.reflection_setrepeatedstring(self._rflct, self._msg, self._field, index, text)
	end
	local value = self:RefreshValue(index)
	self._value_input.text = ALittle.String_ToString(value)
	self:Save()
end

function IDETreeRepeatedValue:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeRepeatedValue:HandleDeleteClick(event)
	self._parent:Delete(self)
end

