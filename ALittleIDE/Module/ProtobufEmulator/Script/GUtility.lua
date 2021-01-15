-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


function ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	local field_count = protobuf.messagedescriptor_fieldcount(descriptor)
	local i = 0
	while true do
		if not(i < field_count) then break end
		local field_descriptor = protobuf.messagedescriptor_field(descriptor, i)
		local field_name = protobuf.fielddescriptor_name(field_descriptor)
		if protobuf.fielddescriptor_ismap(field_descriptor) then
			tree:AddChild(ProtobufEmulator.IDETreeMap(ProtobufEmulator.g_Control, root, field_name, rflct, msg, field_descriptor))
		elseif protobuf.fielddescriptor_isrepeated(field_descriptor) then
			tree:AddChild(ProtobufEmulator.IDETreeRepeated(ProtobufEmulator.g_Control, root, field_name, rflct, msg, field_descriptor))
		else
			local cpp_type = protobuf.fielddescriptor_cpptype(field_descriptor)
			if cpp_type == 7 then
				tree:AddChild(ProtobufEmulator.IDETreeBool(ProtobufEmulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			elseif cpp_type == 8 then
				tree:AddChild(ProtobufEmulator.IDETreeEnum(ProtobufEmulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			elseif cpp_type == 10 then
				tree:AddChild(ProtobufEmulator.UtilityCreateTreeMessage(root, protobuf.reflection_getmessage(rflct, msg, field_descriptor), field_name))
			else
				tree:AddChild(ProtobufEmulator.IDETreeValue(ProtobufEmulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			end
		end
		i = i+(1)
	end
end

function ProtobufEmulator.UtilityCreateTreeMessage(root, msg, msg_field_name)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = msg
	detail_info.reflection = rflct
	detail_info.info = A_LuaProtobufSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(descriptor))
	local tree = ProtobufEmulator.IDETreeMessage(ProtobufEmulator.g_Control, root, msg_field_name, detail_info)
	detail_info.tree = tree
	ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function ProtobufEmulator.UtilityCreateTreeRepeatedMessage(root, parent, msg)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = msg
	detail_info.reflection = rflct
	detail_info.info = A_LuaProtobufSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(descriptor))
	local tree = ProtobufEmulator.IDETreeRepeatedMessage(ProtobufEmulator.g_Control, root, parent, detail_info)
	detail_info.tree = tree
	ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function ProtobufEmulator.UtilityCreateTreeBoolMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaProtobufSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = ProtobufEmulator.IDETreeBoolMapMessage(ProtobufEmulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function ProtobufEmulator.UtilityCreateTreeEnumMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaProtobufSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = ProtobufEmulator.IDETreeEnumMapMessage(ProtobufEmulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function ProtobufEmulator.UtilityCreateTreeValueMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaProtobufSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = ProtobufEmulator.IDETreeValueMapMessage(ProtobufEmulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	ProtobufEmulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function ProtobufEmulator.Utility_CreateTreeForEdit(info, json)
	local msg = A_LuaProtobufSchedule:CreateMessage(info.full_name)
	if msg == nil then
		return nil
	end
	if json == nil then
		json = ProtobufEmulator.g_GProtoCache:GetString(info.full_name, "{}")
	end
	protobuf.message_jsondecode(msg, json)
	local root = {}
	root.for_show = false
	local tree = ProtobufEmulator.UtilityCreateTreeMessage(root, msg, "")
	tree.fold = true
	root.detail_info = tree:GetDetailInfo()
	return root.detail_info
end

function ProtobufEmulator.Utility_CreateTreeForShow(msg)
	local root = {}
	root.for_show = true
	local tree = ProtobufEmulator.UtilityCreateTreeMessage(root, msg, "")
	tree.fold = true
	root.detail_info = tree:GetDetailInfo()
	return root.detail_info
end

end