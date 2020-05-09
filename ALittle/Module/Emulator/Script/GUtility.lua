-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


local UtilityCreateTreeMessage
UtilityCreateTreeMessage = function(msg, msg_field_name)
	local rflct = protobuf.message_getreflection(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local detail_info = {}
	detail_info.message = msg
	detail_info.reflection = rflct
	detail_info.info = A_LuaSocketSchedule:GetMessageInfo(protobuf.messagedescriptor_fullname(descriptor))
	local tree = IDETreeMessage(g_Control, msg_field_name, detail_info)
	detail_info.tree = tree
	local field_count = protobuf.messagedescriptor_fieldcount(detail_info.info.descriptor)
	local i = 0
	while true do
		if not(i < field_count) then break end
		local field_descriptor = protobuf.messagedescriptor_field(detail_info.info.descriptor, i)
		local field_name = protobuf.fielddescriptor_name(field_descriptor)
		if protobuf.fielddescriptor_ismap(field_descriptor) then
			local msg_list = protobuf.reflection_getrepeatedmessage(rflct, msg, field_descriptor)
			local map_descriptor = protobuf.fielddescriptor_messagetype(field_descriptor)
			local key_descriptor = protobuf.messagedescriptor_findfieldbyname(map_descriptor, "key")
			local key_type = protobuf.fielddescriptor_cpptypename(key_descriptor)
			local value_descriptor = protobuf.messagedescriptor_findfieldbyname(map_descriptor, "value")
			local value_type = protobuf.fielddescriptor_cpptypename(value_descriptor)
			local tree_map = IDETreeMap(g_Control, field_name, key_type, value_type)
			detail_info.tree:AddChild(tree_map)
			for index, sub_msg in ___ipairs(msg_list) do
				local sub_rflct = protobuf.message_getreflection(sub_msg)
				local key_cpp_type = protobuf.fielddescriptor_cpptype(key_descriptor)
				if key_cpp_type == 7 then
					local value = protobuf.reflection_getbool(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 1 then
					local value = protobuf.reflection_getint32(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 3 then
					local value = protobuf.reflection_getuint32(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 2 then
					local value = protobuf.reflection_getint64(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 4 then
					local value = protobuf.reflection_getuint64(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 5 then
					local value = protobuf.reflection_getdouble(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 6 then
					local value = protobuf.reflection_getfloat(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 8 then
					local value = protobuf.reflection_getenumvalue(sub_rflct, sub_msg, key_descriptor)
				elseif key_cpp_type == 9 then
					local value = protobuf.reflection_getstring(sub_rflct, sub_msg, key_descriptor)
				end
				local value_cpp_type = protobuf.fielddescriptor_cpptype(value_descriptor)
				if value_cpp_type == 7 then
					local value = protobuf.reflection_getbool(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 1 then
					local value = protobuf.reflection_getint32(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 3 then
					local value = protobuf.reflection_getuint32(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 2 then
					local value = protobuf.reflection_getint64(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 4 then
					local value = protobuf.reflection_getuint64(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 5 then
					local value = protobuf.reflection_getdouble(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 6 then
					local value = protobuf.reflection_getfloat(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 8 then
					local value = protobuf.reflection_getenumvalue(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 9 then
					local value = protobuf.reflection_getstring(sub_rflct, sub_msg, value_descriptor)
				elseif value_cpp_type == 10 then
					local value = protobuf.reflection_getmessage(sub_rflct, sub_msg, value_descriptor)
					detail_info.tree:AddChild(UtilityCreateTreeMessage(value, field_name))
				end
			end
		elseif protobuf.fielddescriptor_isrepeated(field_descriptor) then
			local sub_type = protobuf.fielddescriptor_cpptypename(field_descriptor)
			local tree_repeated = IDETreeRepeated(g_Control, field_name, sub_type)
			detail_info.tree:AddChild(tree_repeated)
			local cpp_type = protobuf.fielddescriptor_cpptype(field_descriptor)
			if cpp_type == 7 then
				local value_list = protobuf.reflection_getrepeatedbool(rflct, msg, field_descriptor)
			elseif cpp_type == 1 then
				local value_list = protobuf.reflection_getrepeatedint32(rflct, msg, field_descriptor)
			elseif cpp_type == 3 then
				local value_list = protobuf.reflection_getrepeateduint32(rflct, msg, field_descriptor)
			elseif cpp_type == 2 then
				local value_list = protobuf.reflection_getrepeatedint64(rflct, msg, field_descriptor)
			elseif cpp_type == 4 then
				local value_list = protobuf.reflection_getrepeateduint64(rflct, msg, field_descriptor)
			elseif cpp_type == 5 then
				local value_list = protobuf.reflection_getrepeateddouble(rflct, msg, field_descriptor)
			elseif cpp_type == 6 then
				local value_list = protobuf.reflection_getrepeatedfloat(rflct, msg, field_descriptor)
			elseif cpp_type == 8 then
				local value_list = protobuf.reflection_getrepeatedint32(rflct, msg, field_descriptor)
			elseif cpp_type == 9 then
				local value_list = protobuf.reflection_getrepeatedstring(rflct, msg, field_descriptor)
			elseif cpp_type == 10 then
				local value_list = protobuf.reflection_getrepeatedmessage(rflct, msg, field_descriptor)
				for index, value in ___ipairs(value_list) do
					detail_info.tree:AddChild(UtilityCreateTreeMessage(value, field_name))
				end
			end
		else
			local value_type = protobuf.fielddescriptor_cpptypename(field_descriptor)
			local cpp_type = protobuf.fielddescriptor_cpptype(field_descriptor)
			if cpp_type == 7 then
				local value = protobuf.reflection_getbool(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 1 then
				local value = protobuf.reflection_getint32(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 3 then
				local value = protobuf.reflection_getuint32(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 2 then
				local value = protobuf.reflection_getint64(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 4 then
				local value = protobuf.reflection_getuint64(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 5 then
				local value = protobuf.reflection_getdouble(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 6 then
				local value = protobuf.reflection_getfloat(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 8 then
				local value = protobuf.reflection_getenumvalue(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 9 then
				local value = protobuf.reflection_getstring(rflct, msg, field_descriptor)
				local tree_item = IDETreeItem(g_Control, field_name, value_type)
				detail_info.tree:AddChild(tree_item)
			elseif cpp_type == 10 then
				local value = protobuf.reflection_getmessage(rflct, msg, field_descriptor)
				detail_info.tree:AddChild(UtilityCreateTreeMessage(value, field_name))
			end
		end
		i = i+(1)
	end
	return tree
end

function Utility_CreateTree(info)
	local msg = A_LuaSocketSchedule:CreateMessage(info.full_name)
	if msg == nil then
		return nil
	end
	local json = g_GProtoCache:GetConfig(info.full_name, "{}")
	protobuf.message_jsondecode(msg, json)
	local tree = UtilityCreateTreeMessage(msg, "[ROOT]")
	tree.fold = true
	return tree:GetDetailInfo()
end

