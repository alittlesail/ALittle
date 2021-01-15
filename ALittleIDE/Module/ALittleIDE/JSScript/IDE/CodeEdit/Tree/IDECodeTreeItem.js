{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name : "ALittle.UIKeyDownEvent", ns_name : "ALittle", rl_name : "UIKeyDownEvent", hash_code : -1604617962,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
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
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name : "ALittle.UIKeyEvent", ns_name : "ALittle", rl_name : "UIKeyEvent", hash_code : 882286932,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
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
name_list : ["target","is_drag","count"],
type_list : ["ALittle.DisplayObject","bool","int"],
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
		this._item_button.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this._item_button._user_data = this;
		this._item_button.text = this._user_info.name;
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
		if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(this._user_info.path) === this._user_info.project.upper_ext) {
			this._user_info.project.OnTreeItemMenu(this._user_info.path, menu);
		}
		menu.AddItem("重命名", this.HandleRenameFile.bind(this));
		menu.AddItem("剪切", this.HandleCutFile.bind(this));
		menu.AddItem("复制", this.HandleCopyFile.bind(this));
		menu.AddItem("删除", this.HandleDeleteFile.bind(this));
		menu.Show();
	},
	HandleKeyDown : function(event) {
		if (event.sym === 1073741883) {
			this.HandleRenameFile();
		}
	},
	HandleDeleteFile : async function() {
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除" + file_name + "吗?");
		if (result !== "YES") {
			return;
		}
		this.OnDelete();
		ALittle.File_DeleteFile(this._user_info.path);
		this.RemoveFromParent();
		ALittleIDE.g_IDECenter.center.content_edit.CloseTabByName(ALittleIDE.IDECodeTabChild, this._user_info.name);
	},
	HandleCutFile : function() {
		let old_name = this._user_info.name;
		let old_path = this._user_info.path;
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.GetTabChildById(ALittleIDE.IDECodeTabChild, old_path);
		if (tab_child !== undefined && tab_child.save !== true) {
			ALittleIDE.g_IDECenter.center.code_list.SetCutTreeItem(undefined);
			g_AUITool.ShowNotice("提示", "请先保存再重命名");
			return;
		}
		ALittleIDE.g_IDECenter.center.code_list.SetCutTreeItem(this);
	},
	HandleCopyFile : function() {
		ALittleIDE.g_IDECenter.center.code_list.SetCopyTreeItem(this);
	},
	HandleRenameFile : async function() {
		let old_name = this._user_info.name;
		let old_path = this._user_info.path;
		let tab_child = ALittleIDE.g_IDECenter.center.content_edit.GetTabChildById(ALittleIDE.IDECodeTabChild, old_path);
		if (tab_child !== undefined && tab_child.save !== true) {
			g_AUITool.ShowNotice("提示", "请先保存再重命名");
			return;
		}
		let file_name = ALittle.File_GetFileNameByPath(this._user_info.path);
		let [x, y] = this.LocalToGlobal();
		let new_name = await g_AUITool.ShowRename(file_name, x, y, 200);
		if (new_name === undefined || new_name === "") {
			return;
		}
		let new_path = ALittle.File_GetFilePathByPath(old_path) + "/" + new_name;
		if (new_path === old_path) {
			return;
		}
		if (ALittle.File_GetFileAttr(new_path) !== undefined) {
			g_AUITool.ShowNotice("提示", "文件名已存在");
			return;
		}
		this._user_info.path = new_path;
		this._user_info.name = new_name;
		this._item_button.text = this._user_info.name;
		if (tab_child !== undefined) {
			ALittleIDE.g_IDECenter.center.content_edit.CloseTab(tab_child.tab_body);
		}
		if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(old_path) === this._user_info.project.upper_ext) {
			this._user_info.project.RemoveFile(old_path);
		}
		ALittle.File_RenameFile(old_path, new_path);
		if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(old_path) === this._user_info.project.upper_ext) {
			this._user_info.project.UpdateFile(this._user_info.module_path, this._user_info.path);
		}
		if (tab_child !== undefined) {
			ALittleIDE.g_IDECenter.center.content_edit.StartEditCodeBySelect(this._user_info.name, this._user_info);
		}
	},
	OnDelete : function() {
		if (this._user_info.project !== undefined && ALittle.File_GetFileExtByPathAndUpper(this._user_info.path) === this._user_info.project.upper_ext) {
			this._user_info.project.RemoveFile(this._user_info.path);
		}
	},
}, "ALittleIDE.IDECodeTreeItem");

}