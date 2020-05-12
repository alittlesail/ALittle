{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeBoolMapMessage = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, parent, rflct, msg, key_field, detail_info) {
		this._detail_info = detail_info;
		this._parent = parent;
		this._rflct = rflct;
		this._msg = msg;
		this._key_field = key_field;
		let key = lua.protobuf.reflection_getbool(this._rflct, this._msg, this._key_field);
		this._head = ctrl_sys.CreateControl("ide_common_tree_bool_map_message", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._item_title.text = "[" + lua.protobuf.fielddescriptor_cpptypename(key_field) + " " + detail_info.info.name + "] : ";
		if (key) {
			this._key_dropdown.text = "true";
		} else {
			this._key_dropdown.text = "false";
		}
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
		if (this._key_dropdown.text === "true") {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._key_field, true);
		} else {
			lua.protobuf.reflection_setbool(this._rflct, this._msg, this._key_field, false);
		}
		this.Save();
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeBoolMapMessage");

}