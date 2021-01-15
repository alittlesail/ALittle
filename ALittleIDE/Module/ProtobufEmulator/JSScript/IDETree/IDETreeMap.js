{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeMap = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, field_name, rflct, msg, field) {
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		let map_descriptor = lua.protobuf.fielddescriptor_messagetype(field);
		this._key_descriptor = lua.protobuf.messagedescriptor_findfieldbyname(map_descriptor, "key");
		this._value_descriptor = lua.protobuf.messagedescriptor_findfieldbyname(map_descriptor, "value");
		this._key_cpp_type = lua.protobuf.fielddescriptor_cpptype(this._key_descriptor);
		this._value_cpp_type = lua.protobuf.fielddescriptor_cpptype(this._value_descriptor);
		let key_type_name = lua.protobuf.fielddescriptor_cpptypename(this._key_descriptor);
		let value_type_name = lua.protobuf.fielddescriptor_cpptypename(this._value_descriptor);
		if (this._value_cpp_type === 10) {
			let value_msg_descriptor = lua.protobuf.fielddescriptor_messagetype(this._value_descriptor);
			value_type_name = lua.protobuf.messagedescriptor_name(value_msg_descriptor);
		}
		this._head = ctrl_sys.CreateControl("ide_common_tree_map", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		let msg_count = lua.protobuf.reflection_getrepeatedmessagecount(rflct, msg, field);
		for (let index = 0; index < msg_count; index += 1) {
			let sub_msg = lua.protobuf.reflection_getrepeatedmessage(rflct, msg, field, index);
			let sub_rflct = lua.protobuf.message_getreflection(sub_msg);
			if (this._key_cpp_type === 7) {
				if (this._value_cpp_type === 7) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 8) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 10) {
					this.AddChild(Emulator.UtilityCreateTreeBoolMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
				} else {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				}
			} else if (this._key_cpp_type === 8) {
				if (this._value_cpp_type === 7) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 8) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 10) {
					this.AddChild(Emulator.UtilityCreateTreeEnumMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
				} else {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				}
			} else {
				if (this._value_cpp_type === 7) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 8) {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				} else if (this._value_cpp_type === 10) {
					this.AddChild(Emulator.UtilityCreateTreeValueMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
				} else {
					this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
				}
			}
		}
		this._item_title.text = "[map<" + key_type_name + "," + value_type_name + ">] " + field_name + ": ";
		this._add_button.x = this._item_title.x + this._item_title.width;
		this._head.width = this._add_button.x + this._add_button.width + 2;
		this.Init();
		this._add_button.disabled = root.for_show;
	},
	HandleAddClick : function(event) {
		this.AddLine(this.child_count);
		this.fold = true;
		this.Save();
	},
	AddLine : function(index) {
		let sub_msg = lua.protobuf.reflection_insertrepeatedmessage(this._rflct, this._msg, this._field, index);
		let sub_rflct = lua.protobuf.message_getreflection(sub_msg);
		if (this._key_cpp_type === 7) {
			if (this._value_cpp_type === 7) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 8) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 10) {
				this.AddChild(Emulator.UtilityCreateTreeBoolMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
			} else {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeBoolMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			}
		} else if (this._key_cpp_type === 8) {
			if (this._value_cpp_type === 7) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 8) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 10) {
				this.AddChild(Emulator.UtilityCreateTreeEnumMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
			} else {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeEnumMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			}
		} else {
			if (this._value_cpp_type === 7) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapBool, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 8) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapEnum, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			} else if (this._value_cpp_type === 10) {
				this.AddChild(Emulator.UtilityCreateTreeValueMapMessage(this._root, this, sub_msg, this._key_descriptor, this._value_descriptor));
			} else {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeValueMapValue, Emulator.g_Control, this._root, this, sub_rflct, sub_msg, this._key_descriptor, this._value_descriptor));
			}
		}
	},
	CreateOneBefore : function(child) {
		let index = this.GetChildIndex(child) - 1;
		this.AddLine(index);
		this.Save();
	},
	Delete : function(child) {
		let index = this.GetChildIndex(child) - 1;
		this.RemoveChild(child);
		lua.protobuf.reflection_removerepeatedmessage(this._rflct, this._msg, this._field, index);
		this.Save();
	},
}, "Emulator.IDETreeMap");

}