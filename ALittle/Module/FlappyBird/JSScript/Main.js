{
if (typeof FlappyBird === "undefined") FlappyBird = {};


FlappyBird.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let window_width = 288;
	let window_height = 512;
	let rate = 1;
	let flag = 0x00000020;
	if (ALittle.System_IsPhone()) {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		window_height = ALittle.Math_Floor(screen_height / screen_width * window_width);
		flag = ALittle.BitOr(flag, 0x00000001);
	}
	ALittle.System_CreateView("FlappyBird", window_width, window_height, flag, rate);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "FlappyBird");
}

FlappyBird.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

FlappyBird.__Browser_Shutdown = function() {
}

FlappyBird.g_Control = undefined;
FlappyBird.g_LayerGroup = undefined;
FlappyBird.g_ModuleBasePath = undefined;
FlappyBird.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	FlappyBird.g_Control = control;
	FlappyBird.g_LayerGroup = layer_group;
	FlappyBird.g_ModuleBasePath = module_base_path;
	await Require(script_base_path + "GCenter");
	FlappyBird.g_GCenter.Setup();
}

FlappyBird.__Module_Shutdown = function() {
	FlappyBird.g_GCenter.Shutdown();
}

FlappyBird.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "FlappyBird";
	info.icon = undefined;
	info.width_type = 1;
	info.width_value = 288;
	info.height_type = 1;
	info.height_value = 512;
	return info;
}

}