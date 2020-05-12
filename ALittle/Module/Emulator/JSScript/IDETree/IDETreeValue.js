{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeValue = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, field_name, rflct, msg, field) {
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		this._cpp_type = lua.protobuf.fielddescriptor_cpptype(field);
		let value = this.RefreshValue();
		this._item = ctrl_sys.CreateControl("ide_common_tree_value", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] " + field_name + ": ";
		this._value_input.text = ALittle.String_ToString(value);
		this._value_input.width = this.width - this._item_title.width - this._item_title.x - 2;
		this._value_input.x = this._item_title.width + this._item_title.x;
		this.Init();
		this._value_input.editable = !root.for_show;
	},
	RefreshValue : function() {
		if (this._cpp_type === 1) {
			return lua.protobuf.reflection_getint32(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 3) {
			return lua.protobuf.reflection_getuint32(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 2) {
			return lua.protobuf.reflection_getint64(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 4) {
			return lua.protobuf.reflection_getuint64(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 5) {
			return lua.protobuf.reflection_getdouble(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 6) {
			return lua.protobuf.reflection_getfloat(this._rflct, this._msg, this._field);
		} else if (this._cpp_type === 9) {
			return lua.protobuf.reflection_getstring(this._rflct, this._msg, this._field);
		}
		return undefined;
	},
	HandleInputFocusOut : function(event) {
		let text = this._value_input.text;
		if (this._cpp_type === 1) {
			lua.protobuf.reflection_setint32(this._rflct, this._msg, this._field, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 3) {
			lua.protobuf.reflection_setuint32(this._rflct, this._msg, this._field, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 2) {
			lua.protobuf.reflection_setint64(this._rflct, this._msg, this._field, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 4) {
			lua.protobuf.reflection_setuint64(this._rflct, this._msg, this._field, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 5) {
			lua.protobuf.reflection_setdouble(this._rflct, this._msg, this._field, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._cpp_type === 6) {
			lua.protobuf.reflection_setfloat(this._rflct, this._msg, this._field, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._cpp_type === 9) {
			lua.protobuf.reflection_setstring(this._rflct, this._msg, this._field, text);
		}
		let value = this.RefreshValue();
		this._value_input.text = ALittle.String_ToString(value);
		this.Save();
	},
}, "Emulator.IDETreeValue");

}