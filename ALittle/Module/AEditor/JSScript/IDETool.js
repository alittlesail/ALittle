{
if (typeof AEditor === "undefined") window.AEditor = {};


AEditor.IDETool = JavaScript.Class(undefined, {
	ShowNotice : function(title, content) {
		if (this._notice_dialog === undefined) {
			this._notice_dialog = AEditor.g_Control.CreateControl("ide_notice_dialog", this);
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
}, "AEditor.IDETool");

AEditor.g_IDETool = ALittle.NewObject(AEditor.IDETool);
}