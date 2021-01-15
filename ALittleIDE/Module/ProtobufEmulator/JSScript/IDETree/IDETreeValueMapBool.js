{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeValueMapBool = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, value_field) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		this._value_field = value_field;
		this._key_cpp_type = lua.protobuf.fielddescriptor_cpptype(key_field);
		let key = this.RefreshValue();
		let value = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._value_field);
		this._item = ctrl_sys.CreateControl("ide_common_tree_value_map_bool", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + lua.protobuf.fielddescriptor_cpptypename(value_field) + "] : ";
		this._key_input.text = ALittle.String_ToString(key);
		if (value) {
			this._value_dropdown.text = "true";
		} else {
			this._value_dropdown.text = "false";
		}
		this._key_input.x = this._item_title.width + this._item_title.x + 1;
		this._value_dropdown.x = this._key_input.width + this._key_input.x + 1;
		this._insert_button.x = this._value_dropdown.x + this._value_dropdown.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this._item.width = this._delete_button.x + this._delete_button.width + 1;
		this.width = this._item.width;
		this.Init();
		this._key_input.editable = !root.for_show;
		this._value_dropdown.disabled = root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	RefreshValue : function() {
		if (this._key_cpp_type === 1) {
			return lua.protobuf.reflection_getint32(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 3) {
			return lua.protobuf.reflection_getuint32(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 2) {
			return lua.protobuf.reflection_getint64(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 4) {
			return lua.protobuf.reflection_getuint64(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 5) {
			return lua.protobuf.reflection_getdouble(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 6) {
			return lua.protobuf.reflection_getfloat(this._rflct, this._msg, this._key_field);
		} else if (this._key_cpp_type === 9) {
			return lua.protobuf.reflection_getstring(this._rflct, this._msg, this._key_field);
		}
		return undefined;
	},
	HandleKeyInputFocusOut : function(event) {
		let text = this._key_input.text;
		if (this._key_cpp_type === 1) {
			lua.protobuf.reflection_setint32(this._rflct, this._msg, this._key_field, ALittle.Math_ToIntOrZero(text));
		} else if (this._key_cpp_type === 3) {
			lua.protobuf.reflection_setuint32(this._rflct, this._msg, this._key_field, ALittle.Math_ToIntOrZero(text));
		} else if (this._key_cpp_type === 2) {
			lua.protobuf.reflection_setint64(this._rflct, this._msg, this._key_field, ALittle.Math_ToIntOrZero(text));
		} else if (this._key_cpp_type === 4) {
			lua.protobuf.reflection_setuint64(this._rflct, this._msg, this._key_field, ALittle.Math_ToIntOrZero(text));
		} else if (this._key_cpp_type === 5) {
			lua.protobuf.reflection_setdouble(this._rflct, this._msg, this._key_field, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._key_cpp_type === 6) {
			lua.protobuf.reflection_setfloat(this._rflct, this._msg, this._key_field, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._key_cpp_type === 9) {
			lua.protobuf.reflection_setstring(this._rflct, this._msg, this._key_field, text);
		}
		let value = this.RefreshValue();
		this._key_input.text = ALittle.String_ToString(value);
		this.Save();
	},
	HandleValueSelectChanegd : function(event) {
		if (this._value_dropdown.text === "true") {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._value_field, true);
		} else {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._value_field, false);
		}
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeValueMapBool");

}