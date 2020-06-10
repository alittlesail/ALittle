{
if (typeof AEditor === "undefined") window.AEditor = {};


AEditor.g_GConfig = undefined;
AEditor.g_GProtoCache = undefined;
AEditor.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		AEditor.g_GConfig = ALittle.CreateConfigSystem(AEditor.g_ModuleBasePath + "/User.cfg");
		AEditor.g_GProtoCache = ALittle.CreateConfigSystem(AEditor.g_ModuleBasePath + "/ProtoCache.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1, 2);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, AEditor.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		AEditor.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, AEditor.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		AEditor.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		AEditor.g_Control.CreateControl("main_scene", this, this._main_layer);
	},
	Shutdown : function() {
	},
}, "AEditor.GCenter");

window.g_GCenter = ALittle.NewObject(AEditor.GCenter);
}