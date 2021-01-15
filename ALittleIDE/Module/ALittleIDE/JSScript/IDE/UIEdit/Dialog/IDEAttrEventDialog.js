{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2024735182, "ALittle.UITabKeyEvent", {
name : "ALittle.UITabKeyEvent", ns_name : "ALittle", rl_name : "UITabKeyEvent", hash_code : 2024735182,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEAttrEventItem = JavaScript.Class(ALittle.DisplayLayout, {
	Init : function(dialog, name, handle) {
		this._dialog = dialog;
		this._name.text = name;
		this._handle.text = handle;
		this._name.AddEventListener(___all_struct.get(2024735182), this, this.HandleTabKey);
	},
	HandleTabKey : function(event) {
		this._handle.focus = true;
	},
	HandleDeleteClick : function(event) {
		this._dialog.DeleteItem(this);
	},
	HandleGotoClick : async function(event) {
		let target_class = this._dialog.GetParentTargetClass();
		if (target_class === undefined) {
			return;
		}
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		let info = await ALittleIDE.g_IDEProject.project.code.FindGoto(target_class + "." + this._handle.text);
		if (info !== undefined) {
			ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(info.file_path, info.line_start, info.char_start, info.line_end, info.char_end);
		}
	},
	HandleNameChanged : function(event) {
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		g_AUICodeFilterScreen.ShowComplete(ALittleIDE.g_IDEProject.project.code, "", this._name);
	},
	HandleHandleChanged : function(event) {
		let target_class = this._dialog.GetParentTargetClass();
		if (target_class === undefined) {
			return;
		}
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		g_AUICodeFilterScreen.ShowComplete(ALittleIDE.g_IDEProject.project.code, target_class, this._handle);
	},
	GetContent : function() {
		if (this._name.text === "") {
			return undefined;
		}
		if (this._handle.text === "") {
			return undefined;
		}
		return this._name.text + ":" + this._handle.text;
	},
}, "ALittleIDE.IDEAttrEventItem");

ALittleIDE.IDEAttrEventDialog = JavaScript.Class(undefined, {
	ShowDialog : function(target_panel, text, need_reset, x, y) {
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_event_edit_dialog", this);
			ALittleIDE.g_DialogLayer.AddChild(this._dialog);
		}
		this._dialog.visible = true;
		this._dialog.MoveToTop();
		if (x !== undefined) {
			this._dialog.x = x;
		}
		if (y !== undefined) {
			this._dialog.y = y;
		}
		if (this._dialog.x + this._dialog.width > A_UISystem.view_width) {
			this._dialog.x = A_UISystem.view_width - this._dialog.width;
		}
		if (this._dialog.y + this._dialog.height > A_UISystem.view_height) {
			this._dialog.y = A_UISystem.view_height - this._dialog.height;
		}
		this._target_panel = target_panel;
		this._target_text = text;
		this._target_need_reset = need_reset;
		this.ResetText();
	},
	HideDialog : function() {
		if (this._dialog === undefined) {
			return;
		}
		this._dialog.visible = false;
	},
	IsShow : function() {
		if (this._dialog === undefined) {
			return false;
		}
		return this._dialog.visible;
	},
	GetParentTargetClass : function() {
		return this._target_panel.GetParentTargetClass();
	},
	HandleAddItem : function(event) {
		let item = ALittleIDE.g_Control.CreateControl("ide_event_item");
		item.Init(this, "", "");
		this._event_scroll_screen.AddChild(item);
	},
	DeleteItem : function(item) {
		this._event_scroll_screen.RemoveChild(item);
	},
	HandleEventConfirm : function(event) {
		let content_list = [];
		let ___OBJECT_1 = this._event_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			let text = child.GetContent();
			if (text !== undefined) {
				ALittle.List_Push(content_list, text);
			}
		}
		let content = ALittle.String_Join(content_list, "\r\n");
		if (content === "") {
			this._dialog.visible = false;
			let object = this._target_panel["_" + this._target_text];
			object.text = "";
			this._target_panel.TableDataSet(this._target_text, false);
			return;
		}
		let has_error = false;
		let event_list = ALittle.String_SplitSepList(content, ["\n", "\r"]);
		let event_data = undefined;
		let ___OBJECT_2 = event_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let event_string = ___OBJECT_2[index - 1];
			if (event_string === undefined) break;
			if (event_data === undefined) {
				event_data = [];
			}
			let event_info = undefined;
			let event_split = ALittle.String_Split(ALittle.String_Trim(event_string), ":");
			let event_count = ALittle.List_Len(event_split);
			if (event_count === 2) {
				event_info = {};
				event_info.type = event_split[1 - 1];
				event_info.func = event_split[2 - 1];
			}
			if (event_info !== undefined) {
				ALittle.List_Push(event_data, event_info);
			} else {
				has_error = true;
			}
		}
		if (event_data === undefined || has_error) {
			g_AUITool.ShowNotice("警告", "事件编辑有错误，请检查");
			return;
		}
		this._dialog.visible = false;
		if (event_data === undefined) {
			return;
		}
		this._target_panel["_" + this._target_text].text = ALittle.String_JsonEncode(event_data);
		this._target_panel.TableDataSet(this._target_text, false);
	},
	ResetText : function() {
		this._event_scroll_screen.RemoveAllChild();
		let info = this._target_panel.base[this._target_text];
		if (info === undefined) {
			info = this._target_panel.default[this._target_text];
		}
		if (info === undefined) {
			info = [];
		}
		let ___OBJECT_3 = info;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let event_info = ___OBJECT_3[index - 1];
			if (event_info === undefined) break;
			let item = ALittleIDE.g_Control.CreateControl("ide_event_item");
			item.Init(this, event_info.type, event_info.func);
			this._event_scroll_screen.AddChild(item);
		}
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList, 10000);
	},
	HandleEventKeyDown : function(event) {
		let ctrl = A_UISystem.sym_map.get(1073742048);
		if (ctrl === undefined) {
			return false;
		}
		let z = A_UISystem.sym_map.get(122);
		if (z) {
			this._revoke_list.UndoRevoke();
		}
		return true;
	},
}, "ALittleIDE.IDEAttrEventDialog");

ALittleIDE.g_IDEAttrEventDialog = ALittle.NewObject(ALittleIDE.IDEAttrEventDialog);
}