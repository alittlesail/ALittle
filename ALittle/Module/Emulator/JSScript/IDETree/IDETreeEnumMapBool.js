{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeEnumMapBool = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, value_field) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		this._value_field = value_field;
		let key = lua.protobuf.reflection_getenumvalue(this._rflct, this._msg, this._key_field);
		let enum_descriptor = lua.protobuf.fielddescriptor_enumtype(this._key_field);
		let value_count = lua.protobuf.enumdescriptor_valuecount(enum_descriptor);
		let data_list = [];
		this._enum_value_map = {};
		let key_string = "";
		for (let i = 0; i < value_count; i += 1) {
			let enum_value = lua.protobuf.enumdescriptor_value(enum_descriptor, i);
			data_list[i + 1 - 1] = lua.protobuf.enumvaluedescriptor_name(enum_value);
			let enum_number = lua.protobuf.enumvaluedescriptor_number(enum_value);
			this._enum_value_map[data_list[i + 1 - 1]] = enum_number;
			if (enum_number === key) {
				key_string = data_list[i + 1 - 1];
			}
		}
		let value = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._value_field);
		this._item = ctrl_sys.CreateControl("ide_common_tree_enum_map_bool", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + lua.protobuf.fielddescriptor_cpptypename(value_field) + "] : ";
		this._key_dropdown.data_list = data_list;
		this._key_dropdown.text = key_string;
		if (value) {
			this._value_dropdown.text = "true";
		} else {
			this._value_dropdown.text = "false";
		}
		this._key_dropdown.x = this._item_title.width + this._item_title.x + 1;
		this._value_dropdown.x = this._key_dropdown.width + this._key_dropdown.x + 1;
		this._insert_button.x = this._value_dropdown.x + this._value_dropdown.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this._item.width = this._delete_button.x + this._delete_button.width + 1;
		this.width = this._item.width;
		this.Init();
		this._key_dropdown.disabled = root.for_show;
		this._value_dropdown.disabled = root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	HandleKeySelectChanegd : function(event) {
		let value = this._enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		lua.protobuf.reflection_setenumvalue(this._rflct, this._msg, this._key_field, value);
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
}, "Emulator.IDETreeEnumMapBool");

}