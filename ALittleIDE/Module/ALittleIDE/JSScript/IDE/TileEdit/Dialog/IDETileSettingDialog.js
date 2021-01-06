{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDETileSettingDialog = JavaScript.Class(undefined, {
	CreateDialog : function() {
		this._dialog = ALittleIDE.g_Control.CreateControl("ide_tile_setting_dialog", this);
		A_LayerManager.AddToModal(this._dialog);
		this._dialog.visible = false;
		this._dialog.close_callback = this.HandleClose.bind(this);
	},
	ShowDialog : function(tile_map) {
		return new Promise((function(___COROUTINE, ___) {
			if (this._dialog === undefined) {
				this.CreateDialog();
			}
			this._dialog.visible = true;
			if (tile_map.tile_type === 1) {
				this._tile_type.text = "正方形";
			} else if (tile_map.tile_type === 3) {
				this._tile_type.text = "水平正六边形";
			} else if (tile_map.tile_type === 2) {
				this._tile_type.text = "垂直正六边形";
			} else {
				this._tile_type.text = "";
			}
			this._side_len.text = tile_map.side_len;
			this._tile_width.text = tile_map.tile_width;
			this._tile_height.text = tile_map.tile_height;
			this._tile_x.text = tile_map.tile_x;
			this._tile_y.text = tile_map.tile_y;
			this._tile_map = tile_map;
			this._thread = ___COROUTINE;
			return;
		}).bind(this));
	},
	HandleClose : function() {
		this.HandleTileSettingCancel(undefined);
		return true;
	},
	HandleTileSettingCancel : function(event) {
		this._dialog.visible = false;
		this._tile_map = undefined;
		let thread = this._thread;
		this._thread = undefined;
		if (thread !== undefined) {
			ALittle.Coroutine.Resume(thread, false);
		}
	},
	HandleTileSettingConfirm : function(event) {
		this._dialog.visible = false;
		let tile_map = this._tile_map;
		this._tile_map = undefined;
		let thread = this._thread;
		this._thread = undefined;
		if (this._tile_type.text === "正方形") {
			tile_map.tile_type = 1;
		} else if (this._tile_type.text === "水平正六边形") {
			tile_map.tile_type = 3;
		} else if (this._tile_type.text === "垂直正六边形") {
			tile_map.tile_type = 2;
		}
		tile_map.side_len = ALittle.Math_ToIntOrZero(this._side_len.text);
		tile_map.tile_width = ALittle.Math_ToIntOrZero(this._tile_width.text);
		tile_map.tile_height = ALittle.Math_ToIntOrZero(this._tile_height.text);
		tile_map.tile_x = ALittle.Math_ToIntOrZero(this._tile_x.text);
		tile_map.tile_y = ALittle.Math_ToIntOrZero(this._tile_y.text);
		if (thread !== undefined) {
			ALittle.Coroutine.Resume(thread, true);
		}
	},
}, "ALittleIDE.IDETileSettingDialog");

ALittleIDE.g_IDETileSettingDialog = ALittle.NewObject(ALittleIDE.IDETileSettingDialog);
}