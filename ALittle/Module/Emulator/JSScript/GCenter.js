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
	},
	Shutdown : function() {
	},
}, "Emulator.GCenter");

Emulator.g_GCenter = ALittle.NewObject(Emulator.GCenter);
}