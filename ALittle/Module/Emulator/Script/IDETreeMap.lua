-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeMap = Lua.Class(Emulator.IDETree, "Emulator.IDETreeMap")

function IDETreeMap:Ctor(ctrl_sys, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local map_descriptor = protobuf.fielddescriptor_messagetype(field)
	___rawset(self, "_key_descriptor", protobuf.messagedescriptor_findfieldbyname(map_descriptor, "key"))
	___rawset(self, "_value_descriptor", protobuf.messagedescriptor_findfieldbyname(map_descriptor, "value"))
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_map", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self:Init()
	self._add_button.x = self._item_title.x + self._item_title.width
	self._head.width = self._add_button.x + self._add_button.width + 2
end

function IDETreeMap:HandleAddClick(event)
	self:AddLine(self.child_count)
	self.fold = true
end

function IDETreeMap:AddLine(index)
end

function IDETreeMap:CreateOneBefore(child)
	local index = self:GetChildIndex(child) - 1
	self:AddLine(index)
end

function IDETreeMap:Delete(child)
	local index = self:GetChildIndex(child) - 1
	self:RemoveChild(child)
	if self._cpp_type == 7 then
		protobuf.reflection_removerepeatedbool(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 1 then
		protobuf.reflection_removerepeatedint32(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 3 then
		protobuf.reflection_removerepeateduint32(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 2 then
		protobuf.reflection_removerepeatedint64(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 4 then
		protobuf.reflection_removerepeateduint64(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 5 then
		protobuf.reflection_removerepeateddouble(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 6 then
		protobuf.reflection_removerepeatedfloat(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 8 then
		protobuf.reflection_removerepeatedint32(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 9 then
		protobuf.reflection_removerepeatedstring(self._rflct, self._msg, self._field, index)
	elseif self._cpp_type == 10 then
		protobuf.reflection_removerepeatedmessage(self._rflct, self._msg, self._field, index)
	end
end

