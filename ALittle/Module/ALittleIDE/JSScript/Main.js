{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


ALittleIDE.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	ALittle.DeleteLog(7);
	let window_width = 1200;
	let window_height = 600;
	let rate = 1.0;
	let flag = lua.bit.bor(0x00000080, 0x00000020);
	if (ALittle.System_GetPlatform() !== "Windows") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		rate = screen_height / screen_width;
		window_height = lua.math.floor(rate * window_width);
		flag = lua.bit.bor(flag, 0x00000001);
	}
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, rate);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "ALittleIDE");
}

ALittleIDE.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

ALittleIDE.__Browser_Shutdown = function() {
}

ALittleIDE.g_Control = undefined;
ALittleIDE.g_LayerGroup = undefined;
ALittleIDE.g_ModuleBasePath = undefined;
ALittleIDE.g_ScriptBasePath = undefined;
ALittleIDE.g_ModuleBasePathEx = undefined;
ALittleIDE.g_IDEConfig = undefined;
ALittleIDE.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	ALittleIDE.g_Control = control;
	ALittleIDE.g_LayerGroup = layer_group;
	ALittleIDE.g_ModuleBasePath = module_base_path;
	ALittleIDE.g_ModuleBasePathEx = ALittle.File_BaseFilePath() + module_base_path;
	ALittleIDE.g_ScriptBasePath = script_base_path;
	await Require(script_base_path + "IDECenter");
	await ALittleIDE.g_IDECenter.Setup(script_base_path, debug);
}

ALittleIDE.__Module_Shutdown = function() {
	ALittleIDE.g_IDECenter.Shutdown();
}

ALittleIDE.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "ALittle集成开发环境";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

ALittleIDE.__Plugin_Setup = function(control, module_base_path, script_base_path) {
}

}