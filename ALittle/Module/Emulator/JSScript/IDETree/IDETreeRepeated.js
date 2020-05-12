{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeRepeated = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, field_name, rflct, msg, field) {
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		this._head = ctrl_sys.CreateControl("ide_common_tree_repeated", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._cpp_type = lua.protobuf.fielddescriptor_cpptype(field);
		let sub_type = lua.protobuf.fielddescriptor_cpptypename(field);
		if (this._cpp_type === 7) {
			let value_count = lua.protobuf.reflection_getrepeatedboolcount(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedBool, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 1) {
			let value_count = lua.protobuf.reflection_getrepeatedint32count(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 3) {
			let value_count = lua.protobuf.reflection_getrepeateduint32count(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 2) {
			let value_count = lua.protobuf.reflection_getrepeatedint64count(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 4) {
			let value_count = lua.protobuf.reflection_getrepeateduint64count(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 5) {
			let value_count = lua.protobuf.reflection_getrepeateddoublecount(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 6) {
			let value_count = lua.protobuf.reflection_getrepeatedfloatcount(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 8) {
			let value_count = lua.protobuf.reflection_getrepeatedint32count(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedEnum, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 9) {
			let value_count = lua.protobuf.reflection_getrepeatedstringcount(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, rflct, msg, field, index));
			}
		} else if (this._cpp_type === 10) {
			let message_type = lua.protobuf.fielddescriptor_messagetype(field);
			sub_type = lua.protobuf.messagedescriptor_name(message_type);
			let value_count = lua.protobuf.reflection_getrepeatedmessagecount(rflct, msg, field);
			for (let index = 0; index < value_count; index += 1) {
				let value = lua.protobuf.reflection_getrepeatedmessage(rflct, msg, field, index);
				this.AddChild(Emulator.UtilityCreateTreeRepeatedMessage(this._root, this, value));
			}
		}
		this._item_title.text = "[repeated " + sub_type + "] " + field_name + " ";
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
		if (this._cpp_type === 7) {
			lua.protobuf.reflection_insertrepeatedbool(this._rflct, this._msg, this._field, index, false);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedBool, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 1) {
			lua.protobuf.reflection_insertrepeatedint32(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 3) {
			lua.protobuf.reflection_insertrepeateduint32(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 2) {
			lua.protobuf.reflection_insertrepeatedint64(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 4) {
			lua.protobuf.reflection_insertrepeateduint64(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 5) {
			lua.protobuf.reflection_insertrepeateddouble(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 6) {
			lua.protobuf.reflection_insertrepeatedfloat(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 8) {
			lua.protobuf.reflection_insertrepeatedint32(this._rflct, this._msg, this._field, index, 0);
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedEnum, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 9) {
			lua.protobuf.reflection_insertrepeatedstring(this._rflct, this._msg, this._field, index, "");
			this.AddChild(ALittle.NewObject(Emulator.IDETreeRepeatedValue, Emulator.g_Control, this._root, this, this._rflct, this._msg, this._field, index), index + 1);
		} else if (this._cpp_type === 10) {
			let value = lua.protobuf.reflection_insertrepeatedmessage(this._rflct, this._msg, this._field, index);
			this.AddChild(Emulator.UtilityCreateTreeRepeatedMessage(this._root, this, value), index + 1);
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
		if (this._cpp_type === 7) {
			lua.protobuf.reflection_removerepeatedbool(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 1) {
			lua.protobuf.reflection_removerepeatedint32(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 3) {
			lua.protobuf.reflection_removerepeateduint32(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 2) {
			lua.protobuf.reflection_removerepeatedint64(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 4) {
			lua.protobuf.reflection_removerepeateduint64(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 5) {
			lua.protobuf.reflection_removerepeateddouble(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 6) {
			lua.protobuf.reflection_removerepeatedfloat(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 8) {
			lua.protobuf.reflection_removerepeatedint32(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 9) {
			lua.protobuf.reflection_removerepeatedstring(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 10) {
			lua.protobuf.reflection_removerepeatedmessage(this._rflct, this._msg, this._field, index);
		}
		this.Save();
	},
}, "Emulator.IDETreeRepeated");

}