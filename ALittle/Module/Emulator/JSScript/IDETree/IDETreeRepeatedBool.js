{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeRepeatedBool = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, field, index) {
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		let value = lua.protobuf.reflection_getrepeatedbool(this._rflct, this._msg, this._field, index);
		this._item = ctrl_sys.CreateControl("ide_common_tree_repeated_bool", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] : ";
		if (value) {
			this._value_dropdown.text = "true";
		} else {
			this._value_dropdown.text = "false";
		}
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
		let index = this._parent.GetChildIndex(this) - 1;
		if (this._value_dropdown.text === "true") {
			lua.protobuf.reflection_setrepeatedbool(this._rflct, this._msg, this._field, index, true);
		} else {
			lua.protobuf.reflection_setrepeatedbool(this._rflct, this._msg, this._field, index, false);
		}
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeRepeatedBool");

}