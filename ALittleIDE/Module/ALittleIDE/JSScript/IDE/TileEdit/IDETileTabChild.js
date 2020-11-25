{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


if (ALittleIDE.IDETabChild === undefined) throw new Error(" extends class:ALittleIDE.IDETabChild is undefined");
ALittleIDE.IDETileTabChild = JavaScript.Class(ALittleIDE.IDETabChild, {
	Ctor : function(ctrl_sys, module, name, save, user_info) {
		this._user_info = user_info;
		this._tab_screen = ALittleIDE.g_Control.CreateControl("ide_tile_tab_screen", this);
		this._tab_screen._user_data = this;
	},
	OnUndo : function() {
	},
	OnRedo : function() {
	},
	OnHide : function() {
	},
	OnShow : function() {
	},
	OnClose : function() {
	},
	OnOpen : function() {
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList);
	},
	OnTabRightMenu : function(menu) {
		menu.AddItem("获取焦点", this.ShowTileFocus.bind(this));
	},
	ShowTileFocus : function() {
		let tree = ALittleIDE.g_IDECenter.center.tile_list.GetFileTree(this._user_info.info.path);
		if (tree === undefined) {
			return;
		}
		ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_list;
		ALittleIDE.g_IDECenter.center.tile_list.ShowTreeItemFocus(tree);
	},
	get tab_body() {
		return this._tab_screen;
	},
	set save(value) {
		if (this._save === value) {
			return;
		}
		if (value === false) {
			this._save = false;
			this.UpdateTitle();
			return;
		}
		this._save = value;
		this.UpdateTitle();
	},
	get id() {
		return this._user_info.info.path;
	},
	Rename : function(name) {
		this._name = name;
		this.UpdateTitle();
	},
	UpdateTitle : function() {
		let text = this._name;
		if (this._save === false) {
			text = text + " *";
		}
		ALittleIDE.g_IDECenter.center.content_edit.main_tab.SetChildText(this._tab_screen, text);
	},
	get title() {
		return this._name;
	},
	UpdateUserInfo : function(info) {
		this._user_info = info;
	},
	CreateBySelect : function(info) {
		this._user_info = info;
	},
}, "ALittleIDE.IDETileTabChild");

}