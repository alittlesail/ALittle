{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeEnum = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, field_name, rflct, msg, field) {
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		let value = lua.protobuf.reflection_getenumvalue(this._rflct, this._msg, this._field);
		let enum_descriptor = lua.protobuf.fielddescriptor_enumtype(field);
		let value_count = lua.protobuf.enumdescriptor_valuecount(enum_descriptor);
		let data_list = [];
		this._enum_value_map = {};
		let value_string = "";
		for (let i = 0; i < value_count; i += 1) {
			let enum_value = lua.protobuf.enumdescriptor_value(enum_descriptor, i);
			data_list[i + 1 - 1] = lua.protobuf.enumvaluedescriptor_name(enum_value);
			let enum_number = lua.protobuf.enumvaluedescriptor_number(enum_value);
			this._enum_value_map[data_list[i + 1 - 1]] = enum_number;
			if (enum_number === value) {
				value_string = data_list[i + 1 - 1];
			}
		}
		this._item = ctrl_sys.CreateControl("ide_common_tree_enum", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] " + field_name + ": ";
		this._value_dropdown.data_list = data_list;
		this._value_dropdown.text = value_string;
		this._value_dropdown.width = this.width - this._item_title.width - this._item_title.x - 2;
		this._value_dropdown.x = this._item_title.width + this._item_title.x;
		this.Init();
		this._value_dropdown.disabled = root.for_show;
	},
	HandleSelectChanegd : function(event) {
		let value = this._enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		lua.protobuf.reflection_setenumvalue(this._rflct, this._msg, this._field, value);
		this.Save();
	},
}, "Emulator.IDETreeEnum");

}