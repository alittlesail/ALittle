{
if (typeof Emulator === "undefined") window.Emulator = {};


Emulator.g_GConfig = undefined;
Emulator.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		Emulator.g_GConfig = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1, 2);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, Emulator.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		Emulator.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, Emulator.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		Emulator.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		Emulator.g_Control.CreateControl("main_scene", this, this._main_layer);
		this._setting_dialog = Emulator.g_Control.CreateControl("main_setting_dialog", this);
		A_LayerManager.AddToModal(this._setting_dialog);
		this._socket_system = lua.socket.create();
		this._frame_loop = ALittle.NewObject(ALittle.LoopFrame, this.UpdateFrame.bind(this));
		this._frame_loop.Start();
	},
	UpdateFrame : function(frame_time) {
		while (true) {
			let event = lua.socket.poll(this._socket_system);
			if (event === undefined) {
				break;
			}
		}
	},
	HandleShowSettingDialog : function(event) {
		this._setting_dialog.visible = true;
		this._proto_root_input.text = Emulator.g_GConfig.GetString("proto_root", "");
	},
	HandleSettingConfirmClick : function(event) {
		let attr = ALittle.File_GetFileAttr(this._proto_root_input.text);
		if (attr === undefined || attr.mode !== "directory") {
			Emulator.g_IDETool.ShowNotice("错误", "文件夹不存在");
			return;
		}
		this._setting_dialog.visible = false;
		Emulator.g_GConfig.SetConfig("proto_root", this._proto_root_input.text);
	},
	HandleSettingCancelClick : function(event) {
		this._setting_dialog.visible = false;
	},
	Shutdown : function() {
		this._frame_loop.Stop();
	},
}, "Emulator.GCenter");

Emulator.g_GCenter = ALittle.NewObject(Emulator.GCenter);
}