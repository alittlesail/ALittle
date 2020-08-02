-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	local field_count = protobuf.messagedescriptor_fieldcount(descriptor)
	local i = 0
	while true do
		if not(i < field_count) then break end
		local field_descriptor = protobuf.messagedescriptor_field(descriptor, i)
		local field_name = protobuf.fielddescriptor_name(field_descriptor)
		if protobuf.fielddescriptor_ismap(field_descriptor) then
			tree:AddChild(Emulator.IDETreeMap(Emulator.g_Control, root, field_name, rflct, msg, field_descriptor))
		elseif protobuf.fielddescriptor_isrepeated(field_descriptor) then
			tree:AddChild(Emulator.IDETreeRepeated(Emulator.g_Control, root, field_name, rflct, msg, field_descriptor))
		else
			local cpp_type = protobuf.fielddescriptor_cpptype(field_descriptor)
			if cpp_type == 7 then
				tree:AddChild(Emulator.IDETreeBool(Emulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			elseif cpp_type == 8 then
				tree:AddChild(Emulator.IDETreeEnum(Emulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			elseif cpp_type == 10 then
				tree:AddChild(Emulator.UtilityCreateTreeMessage(root, protobuf.reflection_getmessage(rflct, msg, field_descriptor), field_name))
			else
				tree:AddChild(Emulator.IDETreeValue(Emulator.g_Control, root, field_name, rflct, msg, field_descriptor))
			end
		end
		i = i+(1)
	end
end

function Emulator.UtilityCreateTreeMessage(root, msg, msg_field_name)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = msg
	detail_info.reflection = rflct
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(descriptor))
	local tree = Emulator.IDETreeMessage(Emulator.g_Control, root, msg_field_name, detail_info)
	detail_info.tree = tree
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function Emulator.UtilityCreateTreeRepeatedMessage(root, parent, msg)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = msg
	detail_info.reflection = rflct
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(descriptor))
	local tree = Emulator.IDETreeRepeatedMessage(Emulator.g_Control, root, parent, detail_info)
	detail_info.tree = tree
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function Emulator.UtilityCreateTreeBoolMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = Emulator.IDETreeBoolMapMessage(Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function Emulator.UtilityCreateTreeEnumMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = Emulator.IDETreeEnumMapMessage(Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function Emulator.UtilityCreateTreeValueMapMessage(root, parent, msg, key_field, value_field)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = protobuf.reflection_getmessage(rflct, msg, value_field)
	detail_info.reflection = protobuf.message_getreflection(detail_info.message)
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(protobuf.message_getdescriptor(detail_info.message)))
	local tree = Emulator.IDETreeValueMapMessage(Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info)
	detail_info.tree = tree
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg)
	return tree
end

function Emulator.Utility_CreateTreeForEdit(info)
	local msg = A_LuaSocketSchedule:CreateMessage(info.full_name)
	if msg == nil then
		return nil
	end
	local json = Emulator.g_GProtoCache:GetString(info.full_name, "{}")
	protobuf.message_jsondecode(msg, json)
	local root = {}
	root.for_show = false
	local tree = Emulator.UtilityCreateTreeMessage(root, msg, "")
	tree.fold = true
	root.detail_info = tree:GetDetailInfo()
	return root.detail_info
end

function Emulator.Utility_CreateTreeForShow(msg)
	local root = {}
	root.for_show = true
	local tree = Emulator.UtilityCreateTreeMessage(root, msg, "")
	tree.fold = true
	root.detail_info = tree:GetDetailInfo()
	return root.detail_info
end

end