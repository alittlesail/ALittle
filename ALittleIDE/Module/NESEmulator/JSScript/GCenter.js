{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.g_GConfig = undefined;
NESEmulator.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		NESEmulator.g_GConfig = ALittle.CreateConfigSystem(NESEmulator.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, NESEmulator.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		NESEmulator.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, NESEmulator.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		NESEmulator.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		let screen = ALittle.NewObject(ALittle.DynamicImage, NESEmulator.g_Control);
		screen.width = NESEmulator.SCREEN_WIDTH;
		screen.height = NESEmulator.SCREEN_HEIGHT;
		screen.SetSurfaceSize(NESEmulator.SCREEN_WIDTH, NESEmulator.SCREEN_HEIGHT, 0);
		this._main_layer.AddChild(screen);
		g_GNes.Setup(screen);
		g_GNes.LoadROM("maxmetal_doubledr.nes");
	},
	Shutdown : function() {
		g_GNes.Shutdown();
	},
}, "NESEmulator.GCenter");

window.g_GCenter = ALittle.NewObject(NESEmulator.GCenter);
}