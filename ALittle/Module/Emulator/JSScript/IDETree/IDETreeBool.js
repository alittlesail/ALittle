{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETreeLogic === undefined) throw new Error(" extends class:Emulator.IDETreeLogic is undefined");
Emulator.IDETreeBool = JavaScript.Class(Emulator.IDETreeLogic, {
	Ctor : function(ctrl_sys, root, field_name, rflct, msg, field) {
		this._rflct = rflct;
		this._msg = msg;
		this._field = field;
		let value = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._field);
		this._item = ctrl_sys.CreateControl("ide_common_tree_bool", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(field) + "] " + field_name + ": ";
		if (value) {
			this._value_dropdown.text = "true";
		} else {
			this._value_dropdown.text = "false";
		}
		this._value_dropdown.width = this.width - this._item_title.width - this._item_title.x - 2;
		this._value_dropdown.x = this._item_title.width + this._item_title.x;
		this.Init();
		this._value_dropdown.disabled = root.for_show;
	},
	HandleSelectChanegd : function(event) {
		if (this._value_dropdown.text === "true") {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._field, true);
		} else {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._field, false);
		}
		this.Save();
	},
}, "Emulator.IDETreeBool");

}