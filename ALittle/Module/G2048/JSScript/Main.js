{
if (typeof G2048 === "undefined") window.G2048 = {};


G2048.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcPortrait(720, 1280, 0);
	ALittle.System_CreateView("2048", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "G2048");
}

G2048.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

G2048.__Browser_Shutdown = function() {
}

G2048.g_Control = undefined;
G2048.g_LayerGroup = undefined;
G2048.g_ModuleBasePath = undefined;
G2048.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	G2048.g_Control = control;
	G2048.g_LayerGroup = layer_group;
	G2048.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	G2048.g_GCenter.Setup();
}

G2048.__Module_Shutdown = function() {
	G2048.g_GCenter.Shutdown();
}

G2048.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "2048";
	info.icon = undefined;
	info.width_type = 1;
	info.width_value = 720;
	info.height_type = 1;
	info.height_value = 1280;
	return info;
}

}