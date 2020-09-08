{
if (typeof Index === "undefined") window.Index = {};


Index.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, 0x00000020);
	ALittle.System_CreateView("Index", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "Index");
}

Index.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

Index.__Browser_Shutdown = function() {
}

Index.g_Control = undefined;
Index.g_LayerGroup = undefined;
Index.g_ModuleBasePath = undefined;
Index.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	Index.g_Control = control;
	Index.g_LayerGroup = layer_group;
	Index.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	g_GCenter.Setup();
}

Index.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
}

Index.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "Index";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}