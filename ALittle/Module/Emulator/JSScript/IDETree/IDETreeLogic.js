{
if (typeof Emulator === "undefined") window.Emulator = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
Emulator.IDETreeLogic = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys, root) {
		this._root = root;
	},
	Init : function() {
		this._upper_description = ALittle.String_Upper(this._item_title.text);
	},
	IsTree : function() {
		return false;
	},
	get title() {
		return this._item_title.text;
	},
	set fold(value) {
	},
	get fold() {
		return false;
	},
	set light(value) {
		this._light.visible = value;
	},
	get light() {
		return this._light.visible;
	},
	SearchBegin : function() {
		this.light = false;
	},
	SearchEnd : function(list) {
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let parent = ___OBJECT_1[index - 1];
			if (parent === undefined) break;
			parent.light = true;
			if (parent !== this) {
				parent = parent.logic_parent;
				while (parent !== undefined) {
					parent.fold = true;
					if (parent === this) {
						break;
					}
					parent = parent.logic_parent;
				}
			}
		}
	},
	SearchDescription : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		this.light = false;
		if (ALittle.String_Find(this._upper_description, name) !== undefined) {
			ALittle.List_Push(list, this);
		}
		return list;
	},
	Save : function() {
		let content = lua.protobuf.message_jsonencode(this._root.detail_info.message);
		if (content === undefined) {
			return;
		}
		Emulator.g_GProtoCache.SetConfig(this._root.detail_info.info.full_name, content);
	},
}, "Emulator.IDETreeLogic");

}