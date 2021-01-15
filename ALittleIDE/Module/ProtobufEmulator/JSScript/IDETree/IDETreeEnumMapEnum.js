{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeEnumMapEnum = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, value_field) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		this._value_field = value_field;
		let key = lua.protobuf.reflection_getenumvalue(this._rflct, this._msg, this._key_field);
		let enum_descriptor = lua.protobuf.fielddescriptor_enumtype(this._key_field);
		let value_count = lua.protobuf.enumdescriptor_valuecount(enum_descriptor);
		let key_data_list = [];
		this._key_enum_value_map = {};
		let key_string = "";
		for (let i = 0; i < value_count; i += 1) {
			let enum_value = lua.protobuf.enumdescriptor_value(enum_descriptor, i);
			key_data_list[i + 1 - 1] = lua.protobuf.enumvaluedescriptor_name(enum_value);
			let enum_number = lua.protobuf.enumvaluedescriptor_number(enum_value);
			this._key_enum_value_map[key_data_list[i + 1 - 1]] = enum_number;
			if (enum_number === key) {
				key_string = key_data_list[i + 1 - 1];
			}
		}
		let value = lua.protobuf.reflection_getenumvalue(this._rflct, this._msg, this._value_field);
		enum_descriptor = lua.protobuf.fielddescriptor_enumtype(this._value_field);
		value_count = lua.protobuf.enumdescriptor_valuecount(enum_descriptor);
		let value_data_list = [];
		this._key_enum_value_map = {};
		let value_string = "";
		for (let i = 0; i < value_count; i += 1) {
			let enum_value = lua.protobuf.enumdescriptor_value(enum_descriptor, i);
			value_data_list[i + 1 - 1] = lua.protobuf.enumvaluedescriptor_name(enum_value);
			let enum_number = lua.protobuf.enumvaluedescriptor_number(enum_value);
			this._key_enum_value_map[value_data_list[i + 1 - 1]] = enum_number;
			if (enum_number === value) {
				value_string = value_data_list[i + 1 - 1];
			}
		}
		this._item = ctrl_sys.CreateControl("ide_common_tree_enum_map_enum", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + lua.protobuf.fielddescriptor_cpptypename(value_field) + "] : ";
		this._key_dropdown.data_list = key_data_list;
		this._key_dropdown.text = key_string;
		this._value_dropdown.data_list = value_data_list;
		this._value_dropdown.text = value_string;
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
		let value = this._key_enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		lua.protobuf.reflection_setenumvalue(this._rflct, this._msg, this._key_field, value);
		this.Save();
	},
	HandleValueSelectChanegd : function(event) {
		let value = this._value_enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		lua.protobuf.reflection_setenumvalue(this._rflct, this._msg, this._value_field, value);
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeEnumMapEnum");

}