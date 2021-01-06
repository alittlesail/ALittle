{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


AUIPlugin.AUIToolOption = {
	NO : "NO",
	YES : "YES",
	CANCEL : "CANCEL",
}

AUIPlugin.AUITool = JavaScript.Class(undefined, {
	Shutdown : function() {
		if (this._alert_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._alert_dialog);
			this._alert_dialog = undefined;
		}
		if (this._notice_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._notice_dialog);
			this._notice_dialog = undefined;
		}
		if (this._save_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._save_dialog);
			this._save_dialog = undefined;
		}
		if (this._delete_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._delete_dialog);
			this._delete_dialog = undefined;
		}
		if (this._rename_input !== undefined) {
			A_LayerManager.RemoveFromModal(this._rename_input);
			this._rename_input = undefined;
		}
		if (this._tip_help_dialog !== undefined) {
			A_LayerManager.RemoveFromTip(this._tip_help_dialog);
			this._tip_help_dialog = undefined;
		}
		if (this._selectdir_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._selectdir_dialog);
			this._selectdir_dialog = undefined;
		}
	},
	ShowAlertDialog : function(title, content) {
		if (this._alert_dialog === undefined) {
			this._alert_dialog = AUIPlugin.g_Control.CreateControl("aui_alert_dialog", this);
			A_LayerManager.AddToModal(this._alert_dialog);
		}
		this._alert_dialog.visible = true;
		this._alert_dialog.MoveToTop();
		this._alert_dialog.title = title;
		this._content.text = content;
	},
	HideAlertDialog : function() {
		this._alert_dialog.visible = false;
	},
	ShowNotice : function(title, content) {
		if (this._notice_dialog === undefined) {
			this._notice_dialog = AUIPlugin.g_Control.CreateControl("aui_notice_dialog", this);
			A_LayerManager.AddToModal(this._notice_dialog);
			this._notice_min_size = this._notice_content.height;
		}
		this._notice_dialog.visible = true;
		this._notice_dialog.MoveToTop();
		this._notice_dialog.title = title;
		this._notice_content.text = content;
		let real_height = this._notice_content.real_height;
		if (real_height < this._notice_min_size) {
			real_height = this._notice_min_size;
		}
		let dialog_body_height = real_height + this._notice_content.y + this._notice_content.height_value;
		this._notice_dialog.height = dialog_body_height + this._notice_dialog.head_size;
	},
	HandleNoticeConfirmClick : function(event) {
		this._notice_dialog.visible = false;
	},
	SaveNotice : function(title, content) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._save_dialog === undefined) {
				this._save_dialog = AUIPlugin.g_Control.CreateControl("aui_save_dialog", this);
				A_LayerManager.AddToModal(this._save_dialog);
			}
			this._save_dialog.visible = true;
			this._save_dialog.MoveToTop();
			this._save_dialog.title = title;
			this._save_content.text = content;
			this._save_dialog._user_data = ___COROUTINE;
			return;
		}).bind(this));
	},
	HandleSaveConfirmClick : function(event) {
		this._save_dialog.visible = false;
		let thread = this._save_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._save_dialog._user_data = undefined;
		ALittle.Coroutine.Resume(thread, "YES");
	},
	HandleNoSaveClick : function(event) {
		this._save_dialog.visible = false;
		let thread = this._save_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._save_dialog._user_data = undefined;
		ALittle.Coroutine.Resume(thread, "NO");
	},
	HandleSaveCancelClick : function(event) {
		this._save_dialog.visible = false;
		let thread = this._save_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._save_dialog._user_data = undefined;
		ALittle.Coroutine.Resume(thread, "CANCEL");
	},
	DeleteNotice : function(title, content) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._delete_dialog === undefined) {
				this._delete_dialog = AUIPlugin.g_Control.CreateControl("aui_delete_dialog", this);
				A_LayerManager.AddToModal(this._delete_dialog);
				this._delete_delta_height = this._delete_dialog.height - this._delete_content.height;
			}
			this._delete_dialog.visible = true;
			this._delete_dialog.MoveToTop();
			this._delete_dialog.title = title;
			this._delete_content.text = content;
			this._delete_dialog.height = this._delete_delta_height + this._delete_content.real_height + 10;
			this._delete_dialog._user_data = ___COROUTINE;
			return;
		}).bind(this));
	},
	HandleDeleteConfirmClick : function(event) {
		this._delete_dialog.visible = false;
		let thread = this._delete_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._delete_dialog._user_data = undefined;
		ALittle.Coroutine.Resume(thread, "YES");
	},
	HandleDeleteCancelClick : function(event) {
		this._delete_dialog.visible = false;
		let thread = this._delete_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._delete_dialog._user_data = undefined;
		ALittle.Coroutine.Resume(thread, "CANCEL");
	},
	ShowRename : function(text, x, y, width) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._rename_input === undefined) {
				this._rename_input = AUIPlugin.g_Control.CreateControl("aui_rename_image_input", this);
				A_LayerManager.AddToModal(this._rename_input);
			}
			this._rename_input.visible = true;
			A_UISystem.focus = this._rename_input.show_input;
			this._rename_input.x = x;
			this._rename_input.y = y;
			this._rename_input.width = width;
			this._rename_input.text = text;
			if (text !== "") {
				this._rename_input.SelectAll();
			}
			this._rename_input._user_data = ___COROUTINE;
			return;
		}).bind(this));
	},
	HandleRenameConfirm : function(event) {
		this._rename_input.visible = false;
		let thread = this._rename_input._user_data;
		if (thread === undefined) {
			return;
		}
		this._rename_input._user_data = undefined;
		let text = this._rename_input.text;
		ALittle.Coroutine.Resume(thread, text);
	},
	HandleRenameCancel : function(event) {
		if (event.sym !== 27) {
			return;
		}
		let thread = this._rename_input._user_data;
		if (thread === undefined) {
			return;
		}
		this._rename_input._user_data = undefined;
		this._rename_input.visible = false;
		ALittle.Coroutine.Resume(thread, undefined);
	},
	ShowSelectDir : function(title, dir) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._selectdir_dialog === undefined) {
				this._selectdir_dialog = AUIPlugin.g_Control.CreateControl("aui_selectdir_dialog", this);
				A_LayerManager.AddToModal(this._selectdir_dialog);
			}
			this._selectdir_dialog.visible = true;
			this._selectdir_input.DelayFocus();
			if (dir !== undefined) {
				this._selectdir_input.text = dir;
			}
			this._selectdir_dialog._user_data = ___COROUTINE;
			return;
		}).bind(this));
	},
	HandleSelectDirConfirm : function(event) {
		this._selectdir_dialog.visible = false;
		let thread = this._selectdir_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._selectdir_dialog._user_data = undefined;
		let text = this._selectdir_input.text;
		ALittle.Coroutine.Resume(thread, text);
	},
	HandleSelectDirCancel : function(event) {
		let thread = this._selectdir_dialog._user_data;
		if (thread === undefined) {
			return;
		}
		this._selectdir_dialog._user_data = undefined;
		this._selectdir_dialog.visible = false;
		ALittle.Coroutine.Resume(thread, undefined);
	},
	HandleSelectDirClick : function(event) {
		if (event.path !== undefined) {
			this._selectdir_input.text = event.path;
		}
	},
	ShowTipHelp : function(content, show_time) {
		if (this._tip_help_dialog === undefined) {
			this._tip_help_dialog = AUIPlugin.g_Control.CreateControl("aui_tip_help", this);
			A_LayerManager.AddToTip(this._tip_help_dialog);
		}
		if (this._tip_help_loop !== undefined) {
			if (A_LoopSystem.HasUpdater(this._tip_help_loop)) {
				this._tip_help_loop.SetCompleted();
				A_LoopSystem.RemoveUpdater(this._tip_help_loop);
			}
			this._tip_help_loop = undefined;
		}
		this._tip_help_dialog.visible = true;
		this._tip_help_dialog.x = A_UISystem.view_width;
		this._tip_help_dialog.y = 0;
		this._tip_help_content.text = content;
		let target_x = A_UISystem.view_width - this._tip_help_dialog.width;
		if (show_time === undefined) {
			show_time = 10000;
		}
		this._tip_help_loop = ALittle.NewObject(ALittle.LoopList);
		let move_in = ALittle.NewObject(ALittle.LoopLinear, this._tip_help_dialog, "x", target_x, 1000, 0);
		this._tip_help_loop.AddUpdater(move_in);
		let move_out = ALittle.NewObject(ALittle.LoopLinear, this._tip_help_dialog, "x", A_UISystem.view_width, 1000, show_time);
		this._tip_help_loop.AddUpdater(move_out);
		let set_value = ALittle.NewObject(ALittle.LoopAttribute, this._tip_help_dialog, "visible", false, 1);
		this._tip_help_loop.AddUpdater(set_value);
		A_LoopSystem.AddUpdater(this._tip_help_loop);
	},
	HandleTipHelpCloseClick : function(event) {
		if (this._tip_help_loop !== undefined) {
			if (A_LoopSystem.HasUpdater(this._tip_help_loop)) {
				this._tip_help_loop.SetCompleted();
				A_LoopSystem.RemoveUpdater(this._tip_help_loop);
			}
			this._tip_help_loop = undefined;
		}
		this._tip_help_dialog.visible = false;
	},
	ShowTip : function(content) {
		if (this._tip_dialog === undefined) {
			this._tip_dialog = AUIPlugin.g_Control.CreateControl("aui_tool_tip", this);
			A_LayerManager.AddToTip(this._tip_dialog);
		}
		this._tip_dialog.visible = true;
		this._tip_text.text = content;
		this._tip_dialog.width = this._tip_text.width + 10;
		this._tip_dialog.height = this._tip_text.height + 10;
	},
	GetTipSize : function() {
		return [this._tip_dialog.width, this._tip_dialog.height];
	},
	MoveTip : function(x, y) {
		if (this._tip_dialog === undefined) {
			return;
		}
		this._tip_dialog.x = x;
		this._tip_dialog.y = y;
	},
	HideTip : function() {
		if (this._tip_dialog === undefined) {
			return;
		}
		this._tip_dialog.visible = false;
	},
}, "AUIPlugin.AUITool");

window.g_AUITool = ALittle.NewObject(AUIPlugin.AUITool);
}