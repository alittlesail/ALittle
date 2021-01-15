{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeBoolMapBool = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, value_field) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		this._value_field = value_field;
		let key = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._key_field);
		let value = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._value_field);
		this._item = ctrl_sys.CreateControl("ide_common_tree_bool_map_bool", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + lua.protobuf.fielddescriptor_cpptypename(value_field) + "] : ";
		if (key) {
			this._key_dropdown.text = "true";
		} else {
			this._key_dropdown.text = "false";
		}
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
		if (this._key_dropdown.text === "true") {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._key_field, true);
		} else {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._key_field, false);
		}
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
}, "Emulator.IDETreeBoolMapBool");

}