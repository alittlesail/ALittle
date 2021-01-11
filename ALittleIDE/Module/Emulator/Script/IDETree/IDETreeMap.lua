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
Emulator.IDETreeMap = Lua.Class(Emulator.IDETree, "Emulator.IDETreeMap")

function Emulator.IDETreeMap:Ctor(ctrl_sys, root, field_name, rflct, msg, field)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_field", field)
	local map_descriptor = protobuf.fielddescriptor_messagetype(field)
	___rawset(self, "_key_descriptor", protobuf.messagedescriptor_findfieldbyname(map_descriptor, "key"))
	___rawset(self, "_value_descriptor", protobuf.messagedescriptor_findfieldbyname(map_descriptor, "value"))
	___rawset(self, "_key_cpp_type", protobuf.fielddescriptor_cpptype(self._key_descriptor))
	___rawset(self, "_value_cpp_type", protobuf.fielddescriptor_cpptype(self._value_descriptor))
	local key_type_name = protobuf.fielddescriptor_cpptypename(self._key_descriptor)
	local value_type_name = protobuf.fielddescriptor_cpptypename(self._value_descriptor)
	if self._value_cpp_type == 10 then
		local value_msg_descriptor = protobuf.fielddescriptor_messagetype(self._value_descriptor)
		value_type_name = protobuf.messagedescriptor_name(value_msg_descriptor)
	end
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_map", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	local msg_count = protobuf.reflection_getrepeatedmessagecount(rflct, msg, field)
	local index = 0
	while true do
		if not(index < msg_count) then break end
		local sub_msg = protobuf.reflection_getrepeatedmessage(rflct, msg, field, index)
		local sub_rflct = protobuf.message_getreflection(sub_msg)
		if self._key_cpp_type == 7 then
			if self._value_cpp_type == 7 then
				self:AddChild(Emulator.IDETreeBoolMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 8 then
				self:AddChild(Emulator.IDETreeBoolMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 10 then
				self:AddChild(Emulator.UtilityCreateTreeBoolMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
			else
				self:AddChild(Emulator.IDETreeBoolMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			end
		elseif self._key_cpp_type == 8 then
			if self._value_cpp_type == 7 then
				self:AddChild(Emulator.IDETreeEnumMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 8 then
				self:AddChild(Emulator.IDETreeEnumMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 10 then
				self:AddChild(Emulator.UtilityCreateTreeEnumMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
			else
				self:AddChild(Emulator.IDETreeEnumMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			end
		else
			if self._value_cpp_type == 7 then
				self:AddChild(Emulator.IDETreeValueMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 8 then
				self:AddChild(Emulator.IDETreeValueMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			elseif self._value_cpp_type == 10 then
				self:AddChild(Emulator.UtilityCreateTreeValueMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
			else
				self:AddChild(Emulator.IDETreeValueMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
			end
		end
		index = index+(1)
	end
	self._item_title.text = "[map<" .. key_type_name .. "," .. value_type_name .. ">] " .. field_name .. ": "
	self._add_button.x = self._item_title.x + self._item_title.width
	self._head.width = self._add_button.x + self._add_button.width + 2
	self:Init()
	self._add_button.disabled = root.for_show
end

function Emulator.IDETreeMap:HandleAddClick(event)
	self:AddLine(self.child_count)
	self.fold = true
	self:Save()
end

function Emulator.IDETreeMap:AddLine(index)
	local sub_msg = protobuf.reflection_insertrepeatedmessage(self._rflct, self._msg, self._field, index)
	local sub_rflct = protobuf.message_getreflection(sub_msg)
	if self._key_cpp_type == 7 then
		if self._value_cpp_type == 7 then
			self:AddChild(Emulator.IDETreeBoolMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 8 then
			self:AddChild(Emulator.IDETreeBoolMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 10 then
			self:AddChild(Emulator.UtilityCreateTreeBoolMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
		else
			self:AddChild(Emulator.IDETreeBoolMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		end
	elseif self._key_cpp_type == 8 then
		if self._value_cpp_type == 7 then
			self:AddChild(Emulator.IDETreeEnumMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 8 then
			self:AddChild(Emulator.IDETreeEnumMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 10 then
			self:AddChild(Emulator.UtilityCreateTreeEnumMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
		else
			self:AddChild(Emulator.IDETreeEnumMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		end
	else
		if self._value_cpp_type == 7 then
			self:AddChild(Emulator.IDETreeValueMapBool(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 8 then
			self:AddChild(Emulator.IDETreeValueMapEnum(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		elseif self._value_cpp_type == 10 then
			self:AddChild(Emulator.UtilityCreateTreeValueMapMessage(self._root, self, sub_msg, self._key_descriptor, self._value_descriptor))
		else
			self:AddChild(Emulator.IDETreeValueMapValue(Emulator.g_Control, self._root, self, sub_rflct, sub_msg, self._key_descriptor, self._value_descriptor))
		end
	end
end

function Emulator.IDETreeMap:CreateOneBefore(child)
	local index = self:GetChildIndex(child) - 1
	self:AddLine(index)
	self:Save()
end

function Emulator.IDETreeMap:Delete(child)
	local index = self:GetChildIndex(child) - 1
	self:RemoveChild(child)
	protobuf.reflection_removerepeatedmessage(self._rflct, self._msg, self._field, index)
	self:Save()
end

end