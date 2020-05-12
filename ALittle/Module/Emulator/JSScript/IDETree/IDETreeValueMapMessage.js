{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeValueMapMessage = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, detail_info) {
		this._detail_info = detail_info;
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		this._key_cpp_type = lua.protobuf.fielddescriptor_cpptype(key_field);
		let key = this.RefreshValue();
		this._head = ctrl_sys.CreateControl("ide_common_tree_value_map_message", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + detail_info.info.name + "] : ";
		this._key_input.text = ALittle.String_ToString(key);
		this._key_input.x = this._item_title.width + this._item_title.x + 1;
		this._insert_button.x = this._key_input.x + this._key_input.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this._head.width = this._delete_button.x + this._delete_button.width + 1;
		this.Init();
		this._key_input.editable = !root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	GetDetailInfo : function() {
		return this._detail_info;
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
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeValueMapMessage");

}