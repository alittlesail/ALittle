-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeRepeated = Lua.Class(Emulator.IDETree, "Emulator.IDETreeRepeated")

function IDETreeRepeated:Ctor(ctrl_sys, root, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_repeated", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	___rawset(self, "_cpp_type", protobuf.fielddescriptor_cpptype(field))
	local sub_type = protobuf.fielddescriptor_cpptypename(field)
	if self._cpp_type == 7 then
		local value_count = protobuf.reflection_getrepeatedboolcount(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedBool(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 1 then
		local value_count = protobuf.reflection_getrepeatedint32count(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 3 then
		local value_count = protobuf.reflection_getrepeateduint32count(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 2 then
		local value_count = protobuf.reflection_getrepeatedint64count(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 4 then
		local value_count = protobuf.reflection_getrepeateduint64count(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 5 then
		local value_count = protobuf.reflection_getrepeateddoublecount(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 6 then
		local value_count = protobuf.reflection_getrepeatedfloatcount(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 8 then
		local value_count = protobuf.reflection_getrepeatedint32count(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedEnum(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 9 then
		local value_count = protobuf.reflection_getrepeatedstringcount(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, rflct, msg, field, index))
			index = index+(1)
		end
	elseif self._cpp_type == 10 then
		local message_type = protobuf.fielddescriptor_messagetype(field)
		sub_type = protobuf.messagedescriptor_name(message_type)
		local value_count = protobuf.reflection_getrepeatedmessagecount(rflct, msg, field)
		local index = 0
		while true do
			if not(index < value_count) then break end
			local value = protobuf.reflection_getrepeatedmessage(rflct, msg, field, index)
			self:AddChild(UtilityCreateTreeRepeatedMessage(self._root, self, value))
			index = index+(1)
		end
	end
	self._item_title.text = "[repeated " .. sub_type .. "] " .. field_name .. " "
	self._add_button.x = self._item_title.x + self._item_title.width
	self._head.width = self._add_button.x + self._add_button.width + 2
	self:Init()
end

function IDETreeRepeated:HandleAddClick(event)
	self:AddLine(self.child_count)
	self.fold = true
	self:Save()
end

function IDETreeRepeated:AddLine(index)
	if self._cpp_type == 7 then
		protobuf.reflection_insertrepeatedbool(self._rflct, self._msg, self._field, index, false)
		self:AddChild(IDETreeRepeatedBool(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 1 then
		protobuf.reflection_insertrepeatedint32(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 3 then
		protobuf.reflection_insertrepeateduint32(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 2 then
		protobuf.reflection_insertrepeatedint64(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 4 then
		protobuf.reflection_insertrepeateduint64(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 5 then
		protobuf.reflection_insertrepeateddouble(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 6 then
		protobuf.reflection_insertrepeatedfloat(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 8 then
		protobuf.reflection_insertrepeatedint32(self._rflct, self._msg, self._field, index, 0)
		self:AddChild(IDETreeRepeatedEnum(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 9 then
		protobuf.reflection_insertrepeatedstring(self._rflct, self._msg, self._field, index, "")
		self:AddChild(IDETreeRepeatedValue(g_Control, self._root, self, self._rflct, self._msg, self._field, index), index + 1)
	elseif self._cpp_type == 10 then
		local value = protobuf.reflection_insertrepeatedmessage(self._rflct, self._msg, self._field, index)
		self:AddChild(UtilityCreateTreeRepeatedMessage(self._root, self, value), index + 1)
	end
end

function IDETreeRepeated:CreateOneBefore(child)
	local index = self:GetChildIndex(child) - 1
	self:AddLine(index)
	self:Save()
end

function IDETreeRepeated:Delete(child)
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
	self:Save()
end

