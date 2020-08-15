{
if (typeof Emulator === "undefined") window.Emulator = {};


Emulator.UitlityCreateChildMessage = function(root, tree, descriptor, rflct, msg) {
	let field_count = lua.protobuf.messagedescriptor_fieldcount(descriptor);
	for (let i = 0; i < field_count; i += 1) {
		let field_descriptor = lua.protobuf.messagedescriptor_field(descriptor, i);
		let field_name = lua.protobuf.fielddescriptor_name(field_descriptor);
		if (lua.protobuf.fielddescriptor_ismap(field_descriptor)) {
			tree.AddChild(ALittle.NewObject(Emulator.IDETreeMap, Emulator.g_Control, root, field_name, rflct, msg, field_descriptor));
		} else if (lua.protobuf.fielddescriptor_isrepeated(field_descriptor)) {
			tree.AddChild(ALittle.NewObject(Emulator.IDETreeRepeated, Emulator.g_Control, root, field_name, rflct, msg, field_descriptor));
		} else {
			let cpp_type = lua.protobuf.fielddescriptor_cpptype(field_descriptor);
			if (cpp_type === 7) {
				tree.AddChild(ALittle.NewObject(Emulator.IDETreeBool, Emulator.g_Control, root, field_name, rflct, msg, field_descriptor));
			} else if (cpp_type === 8) {
				tree.AddChild(ALittle.NewObject(Emulator.IDETreeEnum, Emulator.g_Control, root, field_name, rflct, msg, field_descriptor));
			} else if (cpp_type === 10) {
				tree.AddChild(Emulator.UtilityCreateTreeMessage(root, lua.protobuf.reflection_getmessage(rflct, msg, field_descriptor), field_name));
			} else {
				tree.AddChild(ALittle.NewObject(Emulator.IDETreeValue, Emulator.g_Control, root, field_name, rflct, msg, field_descriptor));
			}
		}
	}
}

Emulator.UtilityCreateTreeMessage = function(root, msg, msg_field_name) {
	let rflct = lua.protobuf.message_getreflection(msg);
	let descriptor = lua.protobuf.message_getdescriptor(msg);
	let detail_info = {};
	detail_info.message = msg;
	detail_info.reflection = rflct;
	detail_info.info = A_LuaSocketSchedule.GetMessageInfo(lua.protobuf.messagedescriptor_fullname(descriptor));
	let tree = ALittle.NewObject(Emulator.IDETreeMessage, Emulator.g_Control, root, msg_field_name, detail_info);
	detail_info.tree = tree;
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg);
	return tree;
}

Emulator.UtilityCreateTreeRepeatedMessage = function(root, parent, msg) {
	let rflct = lua.protobuf.message_getreflection(msg);
	let descriptor = lua.protobuf.message_getdescriptor(msg);
	let detail_info = {};
	detail_info.message = msg;
	detail_info.reflection = rflct;
	detail_info.info = A_LuaSocketSchedule.GetMessageInfo(lua.protobuf.messagedescriptor_fullname(descriptor));
	let tree = ALittle.NewObject(Emulator.IDETreeRepeatedMessage, Emulator.g_Control, root, parent, detail_info);
	detail_info.tree = tree;
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg);
	return tree;
}

Emulator.UtilityCreateTreeBoolMapMessage = function(root, parent, msg, key_field, value_field) {
	let rflct = lua.protobuf.message_getreflection(msg);
	let descriptor = lua.protobuf.message_getdescriptor(msg);
	let detail_info = {};
	detail_info.message = lua.protobuf.reflection_getmessage(rflct, msg, value_field);
	detail_info.reflection = lua.protobuf.message_getreflection(detail_info.message);
	detail_info.info = A_LuaSocketSchedule.GetMessageInfo(lua.protobuf.messagedescriptor_fullname(lua.protobuf.message_getdescriptor(detail_info.message)));
	let tree = ALittle.NewObject(Emulator.IDETreeBoolMapMessage, Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info);
	detail_info.tree = tree;
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg);
	return tree;
}

Emulator.UtilityCreateTreeEnumMapMessage = function(root, parent, msg, key_field, value_field) {
	let rflct = lua.protobuf.message_getreflection(msg);
	let descriptor = lua.protobuf.message_getdescriptor(msg);
	let detail_info = {};
	detail_info.message = lua.protobuf.reflection_getmessage(rflct, msg, value_field);
	detail_info.reflection = lua.protobuf.message_getreflection(detail_info.message);
	detail_info.info = A_LuaSocketSchedule.GetMessageInfo(lua.protobuf.messagedescriptor_fullname(lua.protobuf.message_getdescriptor(detail_info.message)));
	let tree = ALittle.NewObject(Emulator.IDETreeEnumMapMessage, Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info);
	detail_info.tree = tree;
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg);
	return tree;
}

Emulator.UtilityCreateTreeValueMapMessage = function(root, parent, msg, key_field, value_field) {
	let rflct = lua.protobuf.message_getreflection(msg);
	let descriptor = lua.protobuf.message_getdescriptor(msg);
	let detail_info = {};
	detail_info.message = lua.protobuf.reflection_getmessage(rflct, msg, value_field);
	detail_info.reflection = lua.protobuf.message_getreflection(detail_info.message);
	detail_info.info = A_LuaSocketSchedule.GetMessageInfo(lua.protobuf.messagedescriptor_fullname(lua.protobuf.message_getdescriptor(detail_info.message)));
	let tree = ALittle.NewObject(Emulator.IDETreeValueMapMessage, Emulator.g_Control, root, parent, rflct, msg, key_field, detail_info);
	detail_info.tree = tree;
	Emulator.UitlityCreateChildMessage(root, tree, descriptor, rflct, msg);
	return tree;
}

Emulator.Utility_CreateTreeForEdit = function(info) {
	let msg = A_LuaSocketSchedule.CreateMessage(info.full_name);
	if (msg === undefined) {
		return undefined;
	}
	let json = Emulator.g_GProtoCache.GetString(info.full_name, "{}");
	lua.protobuf.message_jsondecode(msg, json);
	let root = {};
	root.for_show = false;
	let tree = Emulator.UtilityCreateTreeMessage(root, msg, "");
	tree.fold = true;
	root.detail_info = tree.GetDetailInfo();
	return root.detail_info;
}

Emulator.Utility_CreateTreeForShow = function(msg) {
	let root = {};
	root.for_show = true;
	let tree = Emulator.UtilityCreateTreeMessage(root, msg, "");
	tree.fold = true;
	root.detail_info = tree.GetDetailInfo();
	return root.detail_info;
}

}