{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittleIDE.IDECodeTreeLogic === undefined) throw new Error(" extends class:ALittleIDE.IDECodeTreeLogic is undefined");
ALittleIDE.IDECodeTreeItem = JavaScript.Class(ALittleIDE.IDECodeTreeLogic, {
	Ctor : function(ctrl_sys, user_info) {
		this._item = ctrl_sys.CreateControl("ide_code_tree_item", this);
		this.AddChild(this._item);
		this.width = this._item.width;
		this.height = this._item.height;
		this._item_button.selected = false;
		this._item_button.group = user_info.group;
		this._item_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleClick);
		this._item_button.AddEventListener(___all_struct.get(-641444818), this, this.HandleRButtonDown);
		this._item_button._user_data = this;
		this._item_title.text = this._user_info.name;
	},
	get is_tree() {
		return false;
	},
	get fold() {
		return false;
	},
	set fold(value) {
	},
	HandleClick : function(event) {
		ALittleIDE.g_IDECenter.center.content_edit.StartEditCodeBySelect(this._user_info.name, this._user_info);
	},
	SearchFile : function(name, list) {
		if (list === undefined) {
			list = [];
		}
		if (ALittle.String_Find(this._user_info.name, name) !== undefined) {
			ALittle.List_Push(list, this);
		}
		return list;
	},
	FindFile : function(full_path) {
		if (this._user_info.path === full_path) {
			return this;
		}
		return undefined;
	},
	HandleRButtonDown : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		if (this._user_info.project !== undefined) {
			this._user_info.project.OnTreeItemMenu(this._user_info.path, menu);
		}
		menu.AddItem("重命名", this.HandleRenameFile.bind(this));
		menu.AddItem("删除", this.HandleDeleteFile.bind(this));
		menu.Show();
	},
	HandleDeleteFile : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除" + file_name + "吗?");
		if (result !== "YES") {
			return;
		}
		this.OnDelete();
		ALittle.File_DeleteFile(this._user_info.path);
		let parent = this.parent;
		this.RemoveFromParent();
		if (parent !== undefined) {
			parent.DispatchEvent(___all_struct.get(-431205740), {});
		}
		ALittleIDE.g_IDECenter.center.content_edit.CloseTabByName(ALittleIDE.IDECodeTabChild, this._user_info.name);
	},
	HandleRenameFile : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let [x, y] = this.LocalToGlobal();
		let new_name = await g_AUITool.ShowRename(file_name, x, y, 200);
		if (new_name === undefined || new_name === "") {
			return;
		}
		let old_name = this._user_info.name;
		let old_path = this._user_info.path;
		let new_path = ALittle.File_GetFilePathByPath(old_path) + "/" + new_name;
		this._user_info.path = new_path;
		this._user_info.name = new_name;
		this._item_title.text = this._user_info.name;
		if (this._user_info.project !== undefined) {
			this._user_info.project.RemoveFile(old_path);
		}
		ALittle.File_RenameFile(old_path, new_path);
		ALittleIDE.g_IDECenter.center.content_edit.RenameTabByName(ALittleIDE.IDECodeTabChild, old_name, this._user_info.name);
		if (this._user_info.project !== undefined) {
			this._user_info.project.UpdateFile(this._user_info.module_path, this._user_info.path);
		}
	},
	OnDelete : function() {
		if (this._user_info.project !== undefined) {
			this._user_info.project.RemoveFile(this._user_info.path);
		}
	},
}, "ALittleIDE.IDECodeTreeItem");

}