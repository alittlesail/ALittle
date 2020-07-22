{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle->GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})

ALittleIDE.IDEAttrEventDialog = JavaScript.Class(undefined, {
	ShowDialog : function(target_panel, text, need_reset) {
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_event_edit_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
		}
		this._dialog.visible = true;
		this._target_panel = target_panel;
		this._target_text = text;
		this._target_need_reset = need_reset;
		this.ResetText();
		A_UISystem.focus = this._event_edit.show_edit;
	},
	HideDialog : function() {
		this._dialog.visible = false;
	},
	IsShow : function() {
		if (this._dialog === undefined) {
			return false;
		}
		return this._dialog.visible;
	},
	HandleEventConfirm : function(event) {
		let content = this._event_edit.text;
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
		let ___OBJECT_1 = event_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let event_string = ___OBJECT_1[index - 1];
			if (event_string === undefined) break;
			if (event_data === undefined) {
				event_data = [];
			}
			let event_info = undefined;
			let event_split = ALittle.String_Split(ALittle.String_Trim(event_string), ":");
			let event_count = ALittle.List_MaxN(event_split);
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
		let info = this._target_panel.base[this._target_text];
		if (info === undefined) {
			info = this._target_panel.default[this._target_text];
		}
		if (info === undefined) {
			info = [];
		}
		let content = [];
		let content_count = 0;
		let ___OBJECT_2 = info;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let event_info = ___OBJECT_2[index - 1];
			if (event_info === undefined) break;
			let data_type = event_info.type + ":";
			let event_string = data_type + event_info.func;
			++ content_count;
			content[content_count - 1] = event_string;
		}
		let content_str = ALittle.String_Join(content, "\n");
		this._event_edit.text = content_str;
		this._edit_old_text = content_str;
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList);
	},
	ShowEventSelectDialog : function(x, y) {
		if (this._select_dialog === undefined) {
			this._select_dialog = ALittleIDE.g_Control.CreateControl("ide_event_select_screen", this);
			let ___OBJECT_3 = ALittleIDE.g_IDEEnum.event_type_list;
			for (let k = 1; k <= ___OBJECT_3.length; ++k) {
				let v = ___OBJECT_3[k - 1];
				if (v === undefined) break;
				let button = ALittleIDE.g_Control.CreateControl("ide_common_item_button");
				button.text = v;
				button.AddEventListener(___all_struct.get(-449066808), this, this.HandleEventSelectClick);
				button.drag_trans_target = this._select_dialog;
				this._select_dialog.AddChild(button);
			}
		}
		this._select_dialog.x = x;
		this._select_dialog.y = y;
		A_LayerManager.ShowFromRight(this._select_dialog);
	},
	HandleEventSelectClick : function(event) {
		A_LayerManager.HideFromRight(this._select_dialog);
		let text = event.target.text;
		this._event_edit.InsertText("ALittle." + text);
	},
	HandleEventRightButtonDown : function(event) {
		this.ShowEventSelectDialog(A_UISystem.mouse_x, A_UISystem.mouse_y);
	},
	HandleEventChange : function(event) {
		let edit_new_text = this._event_edit.text;
		let revoke = ALittle.NewObject(ALittleIDE.IDETextEditRevoke, this._event_edit, this._edit_old_text, edit_new_text);
		this._edit_old_text = edit_new_text;
		this._revoke_list.PushRevoke(revoke);
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