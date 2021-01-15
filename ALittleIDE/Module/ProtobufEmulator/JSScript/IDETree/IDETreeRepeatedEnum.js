{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeRepeatedEnum = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, field, index) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		let value = lua.protobuf.reflection_getrepeatedint32(this._rflct, this._msg, this._field, index);
		let enum_descriptor = lua.protobuf.fielddescriptor_enumtype(field);
		let value_count = lua.protobuf.enumdescriptor_valuecount(enum_descriptor);
		let data_list = [];
		this._enum_value_map = {};
		let value_string = "";
		for (let i = 0; i < value_count; i += 1) {
			let enum_value = lua.protobuf.enumdescriptor_value(enum_descriptor, i);
			data_list[i + 1 - 1] = lua.protobuf.enumvaluedescriptor_name(enum_value);
			let number = lua.protobuf.enumvaluedescriptor_number(enum_value);
			this._enum_value_map[data_list[i + 1 - 1]] = number;
			if (value === number) {
				value_string = data_list[i + 1 - 1];
			}
		}
		this._item = ctrl_sys.CreateControl("ide_common_tree_repeated_enum", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] : ";
		this._value_dropdown.data_list = data_list;
		this._value_dropdown.text = value_string;
		this._value_dropdown.width = this.width - this._item_title.width - this._item_title.x - 2 - this._insert_button.width - this._delete_button.width - 1;
		this._value_dropdown.x = this._item_title.width + this._item_title.x;
		this._insert_button.x = this._value_dropdown.x + this._value_dropdown.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this.Init();
		this._value_dropdown.disabled = root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	HandleSelectChanegd : function(event) {
		let value = this._enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		let index = this._parent.GetChildIndex(this) - 1;
		lua.protobuf.reflection_setrepeatedint32(this._rflct, this._msg, this._field, index, value);
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeRepeatedEnum");

}