{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeRepeatedValue = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, field, index) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		this._cpp_type = lua.protobuf.fielddescriptor_cpptype(field);
		let value = this.RefreshValue(index);
		this._item = ctrl_sys.CreateControl("ide_common_tree_repeated_value", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] : ";
		this._value_input.text = ALittle.String_ToString(value);
		this._value_input.width = this.width - this._item_title.width - this._item_title.x - 2 - this._insert_button.width - this._delete_button.width - 1;
		this._value_input.x = this._item_title.width + this._item_title.x;
		this._insert_button.x = this._value_input.x + this._value_input.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this.Init();
		this._value_input.editable = !root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	RefreshValue : function(index) {
		if (this._cpp_type === 1) {
			return lua.protobuf.reflection_getrepeatedint32(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 3) {
			return lua.protobuf.reflection_getrepeateduint32(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 2) {
			return lua.protobuf.reflection_getrepeatedint64(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 4) {
			return lua.protobuf.reflection_getrepeateduint64(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 5) {
			return lua.protobuf.reflection_getrepeateddouble(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 6) {
			return lua.protobuf.reflection_getrepeatedfloat(this._rflct, this._msg, this._field, index);
		} else if (this._cpp_type === 9) {
			return lua.protobuf.reflection_getrepeatedstring(this._rflct, this._msg, this._field, index);
		}
		return undefined;
	},
	HandleInputFocusOut : function(event) {
		let text = this._value_input.text;
		let index = this._parent.GetChildIndex(this) - 1;
		if (this._cpp_type === 1) {
			lua.protobuf.reflection_setrepeatedint32(this._rflct, this._msg, this._field, index, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 3) {
			lua.protobuf.reflection_setrepeateduint32(this._rflct, this._msg, this._field, index, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 2) {
			lua.protobuf.reflection_setrepeatedint64(this._rflct, this._msg, this._field, index, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 4) {
			lua.protobuf.reflection_setrepeateduint64(this._rflct, this._msg, this._field, index, ALittle.Math_ToIntOrZero(text));
		} else if (this._cpp_type === 5) {
			lua.protobuf.reflection_setrepeateddouble(this._rflct, this._msg, this._field, index, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._cpp_type === 6) {
			lua.protobuf.reflection_setrepeatedfloat(this._rflct, this._msg, this._field, index, ALittle.Math_ToDoubleOrZero(text));
		} else if (this._cpp_type === 9) {
			lua.protobuf.reflection_setrepeatedstring(this._rflct, this._msg, this._field, index, text);
		}
		let value = this.RefreshValue(index);
		this._value_input.text = ALittle.String_ToString(value);
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeRepeatedValue");

}