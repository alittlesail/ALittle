{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Emulator.IDETree === undefined) throw new Error(" extends class:Emulator.IDETree is undefined");
Emulator.IDETreeMessage = JavaScript.Class(Emulator.IDETree, {
	Ctor : function(ctrl_sys, root, field_name, detail_info) {
		this._detail_info = detail_info;
		this._head = ctrl_sys.CreateControl("ide_common_tree_message", this);
		ALittle.DisplayGroup.AddChild.call(this, this._head, 1);
		this._item_title.text = "[" + detail_info.info.name + "] " + field_name + " ";
		this._head.width = this._item_title.x + this._item_title.width + 1;
		this.Init();
	},
	GetDetailInfo : function() {
		return this._detail_info;
	},
}, "Emulator.IDETreeMessage");

}