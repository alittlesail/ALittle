-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeValueMapMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeValueMapMessage")

function IDETreeValueMapMessage:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, detail_info)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_key_cpp_type", protobuf.fielddescriptor_cpptype(key_field))
	local key = self:RefreshValue()
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_value_map_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. detail_info.info.name .. "] : "
	self._key_input.text = ALittle.String_ToString(key)
	self._key_input.x = self._item_title.width + self._item_title.x + 1
	self._insert_button.x = self._key_input.x + self._key_input.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._head.width = self._delete_button.x + self._delete_button.width + 1
	self:Init()
	self._key_input.editable = not root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function IDETreeValueMapMessage:GetDetailInfo()
	return self._detail_info
end

function IDETreeValueMapMessage:RefreshValue()
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

function IDETreeValueMapMessage:HandleKeyInputFocusOut(event)
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

function IDETreeValueMapMessage:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeValueMapMessage:HandleDeleteClick(event)
	self._parent:Delete(self)
end

