{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeEnumMapMessage = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, detail_info) {
		this._detail_info = detail_info;
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		let value = lua.protobuf.reflection_getenumvalue(this._rflct, this._msg, this._key_field);
		let enum_descriptor = lua.protobuf.fielddescriptor_enumtype(this._key_field);
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
		this._head = ctrl_sys.CreateControl("ide_common_tree_enum_map_message", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + detail_info.info.name + "] : ";
		this._key_dropdown.data_list = data_list;
		this._key_dropdown.text = value_string;
		this._key_dropdown.x = this._item_title.width + this._item_title.x + 1;
		this._insert_button.x = this._key_dropdown.x + this._key_dropdown.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this._head.width = this._delete_button.x + this._delete_button.width + 1;
		this.Init();
		this._key_dropdown.disabled = root.for_show;
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	GetDetailInfo : function() {
		return this._detail_info;
	},
	HandleKeySelectChanegd : function(event) {
		let value = this._enum_value_map[event.target.text];
		if (value === undefined) {
			return;
		}
		lua.protobuf.reflection_setenumvalue(this._rflct, this._msg, this._key_field, value);
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeEnumMapMessage");

}