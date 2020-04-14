{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};

ALittle.RegStruct(-125023360, "ALittleIDE.IDECallbackUserData", {
name : "ALittleIDE.IDECallbackUserData", ns_name : "ALittleIDE", rl_name : "IDECallbackUserData", hash_code : -125023360,
name_list : ["cancel_callback","confirm_callback"],
type_list : ["Functor<()>","Functor<()>"],
option_map : {}
})

ALittleIDE.IDETool = JavaScript.Class(undefined, {
	ShowAlertDialog : function(title, content) {
		if (this._alert_dialog === undefined) {
			this._alert_dialog = ALittleIDE.g_Control.CreateControl("ide_alert_dialog", this);
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
			this._notice_dialog = ALittleIDE.g_Control.CreateControl("ide_notice_dialog", this);
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
	SaveNotice : function(title, content, cancel_callback, confirm_callback) {
		if (this._save_dialog === undefined) {
			this._save_dialog = ALittleIDE.g_Control.CreateControl("ide_save_dialog", this);
			A_LayerManager.AddToModal(this._save_dialog);
		}
		this._save_dialog.visible = true;
		this._save_dialog.MoveToTop();
		this._save_dialog.title = title;
		this._save_content.text = content;
		let user_data = {};
		user_data.cancel_callback = cancel_callback;
		user_data.confirm_callback = confirm_callback;
		this._save_dialog._user_data = user_data;
	},
	HandleSaveConfirmClick : function(event) {
		this._save_dialog.visible = false;
		let user_data = this._save_dialog._user_data;
		if (user_data.confirm_callback !== undefined) {
			user_data.confirm_callback();
		}
		if (user_data.cancel_callback !== undefined) {
			user_data.cancel_callback();
		}
		this._save_dialog._user_data = undefined;
	},
	HandleNoSaveClick : function(event) {
		this._save_dialog.visible = false;
		let user_data = this._save_dialog._user_data;
		if (user_data.cancel_callback !== undefined) {
			user_data.cancel_callback();
		}
		this._save_dialog._user_data = undefined;
	},
	HandleSaveCancelClick : function(event) {
		this._save_dialog.visible = false;
		this._save_dialog._user_data = undefined;
	},
	DeleteNotice : function(title, content, confirm_callback) {
		if (this._delete_dialog === undefined) {
			this._delete_dialog = ALittleIDE.g_Control.CreateControl("ide_delete_dialog", this);
			A_LayerManager.AddToModal(this._delete_dialog);
		}
		this._delete_dialog.visible = true;
		this._delete_dialog.MoveToTop();
		this._delete_dialog.title = title;
		this._delete_content.text = content;
		this._delete_dialog._user_data = confirm_callback;
	},
	HandleDeleteConfirmClick : function(event) {
		this._delete_dialog.visible = false;
		let callback = this._delete_dialog._user_data;
		if (callback !== undefined) {
			callback();
		}
		this._delete_dialog._user_data = undefined;
	},
	HandleDeleteCancelClick : function(event) {
		this._delete_dialog.visible = false;
		this._delete_dialog._user_data = undefined;
	},
	ShowRename : function(callback, text, x, y, width) {
		if (this._rename_input === undefined) {
			this._rename_input = ALittleIDE.g_Control.CreateControl("ide_rename_image_input", this);
			A_LayerManager.AddToModal(this._rename_input);
		}
		this._rename_input.visible = true;
		A_UISystem.focus = this._rename_input.show_input;
		this._rename_input.x = x;
		this._rename_input.y = y;
		this._rename_input.width = width;
		this._rename_input.text = text;
		this._rename_input.SelectAll();
		this._rename_input._user_data = callback;
	},
	HandleRenameConfirm : function(event) {
		let callback = this._rename_input._user_data;
		this._rename_input._user_data = undefined;
		if (callback === undefined) {
			return;
		}
		this._rename_input.visible = false;
		let text = this._rename_input.text;
		callback(text);
	},
	VersionNotice : function(title, content, confirm_callback) {
		if (this._version_dialog === undefined) {
			this._version_dialog = ALittleIDE.g_Control.CreateControl("ide_version_dialog", this);
			A_LayerManager.AddToModal(this._version_dialog);
		}
		this._version_dialog.visible = true;
		this._version_dialog.MoveToTop();
		this._version_dialog.title = title;
		this._version_content.text = content;
		this._version_dialog._user_data = confirm_callback;
	},
	HandleVersionConfirmClick : function(event) {
		this._version_dialog.visible = false;
		let callback = this._version_dialog._user_data;
		if (callback !== undefined) {
			callback();
		}
		this._version_dialog._user_data = undefined;
	},
	HandleVersionCancelClick : function(event) {
		this._version_dialog.visible = false;
		this._version_dialog._user_data = undefined;
	},
	ShowTipHelp : function(content, show_time) {
		if (this._tip_help_dialog === undefined) {
			this._tip_help_dialog = ALittleIDE.g_Control.CreateControl("ide_tip_help", this);
			ALittleIDE.g_IDECenter.dialog_layer.AddChild(this._tip_help_dialog);
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
}, "ALittleIDE.IDETool");

ALittleIDE.g_IDETool = ALittle.NewObject(ALittleIDE.IDETool);
}