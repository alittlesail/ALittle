{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEControlTreeLogic = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys, user_info) {
		this._user_info = user_info;
	},
	get user_info() {
		return this._user_info;
	},
	get is_tree() {
		return false;
	},
	get is_root() {
		return this._user_info.root;
	},
	set fold(value) {
	},
	ShowSelect : function() {
		if (this._item_button !== undefined) {
			this._item_button.selected = true;
		}
	},
	Refresh : function() {
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		return list;
	},
	FindFile : function(full_path) {
		return undefined;
	},
	OnDelete : function() {
	},
}, "ALittleIDE.IDEControlTreeLogic");

}