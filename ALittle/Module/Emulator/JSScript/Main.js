{
if (typeof Emulator === "undefined") window.Emulator = {};


Emulator.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 800, 0x00000020);
	ALittle.System_CreateView("Emulator", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "Emulator");
}

Emulator.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

Emulator.__Browser_Shutdown = function() {
}

Emulator.g_Control = undefined;
Emulator.g_LayerGroup = undefined;
Emulator.g_ModuleBasePath = undefined;
Emulator.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	Emulator.g_Control = control;
	Emulator.g_LayerGroup = layer_group;
	Emulator.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	await Require(script_base_path, "IDETool");
	await Require(script_base_path, "ISocket");
	Emulator.g_GCenter.Setup();
}

Emulator.__Module_Shutdown = function() {
	Emulator.g_GCenter.Shutdown();
}

Emulator.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "Emulator";
	info.icon = undefined;
	info.width_type = 1;
	info.width_value = 1200;
	info.height_type = 1;
	info.height_value = 800;
	return info;
}

}