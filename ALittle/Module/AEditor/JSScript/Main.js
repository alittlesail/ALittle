{
if (typeof AEditor === "undefined") window.AEditor = {};


AEditor.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, 0x00000020);
	ALittle.System_CreateView("AEditor", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "AEditor");
}

AEditor.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

AEditor.__Browser_Shutdown = function() {
}

AEditor.g_Control = undefined;
AEditor.g_LayerGroup = undefined;
AEditor.g_ModuleBasePath = undefined;
AEditor.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	AEditor.g_Control = control;
	AEditor.g_LayerGroup = layer_group;
	AEditor.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	await Require(script_base_path, "IDETool");
	await Require(script_base_path, "IDEIMEManager");
	AEditor.g_IDEIMEManager.Setup();
	g_GCenter.Setup();
}

AEditor.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
	AEditor.g_IDEIMEManager.Shutdown();
}

AEditor.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "AEditor";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}