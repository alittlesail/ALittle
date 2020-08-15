{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeRepeatedMessage = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, parent, detail_info) {
		this._parent = parent;
		this._detail_info = detail_info;
		this._head = ctrl_sys.CreateControl("ide_common_tree_repeated_message", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._item_title.text = "[" + detail_info.info.name + "] ";
		this._insert_button.x = this._item_title.x + this._item_title.width + 1;
		this._delete_button.x = this._insert_button.x + this._insert_button.width + 1;
		this._head.width = this._delete_button.x + this._delete_button.width + 1;
		this.Init();
		this._insert_button.disabled = root.for_show;
		this._delete_button.disabled = root.for_show;
	},
	GetDetailInfo : function() {
		return this._detail_info;
	},
	HandleInsertClick : function(event) {
		this._parent.CreateOneBefore(this);
	},
	HandleDeleteClick : function(event) {
		this._parent.Delete(this);
	},
}, "Emulator.IDETreeRepeatedMessage");

}