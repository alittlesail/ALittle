{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


SuperMarioBros.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(560, 460, 0x00000020);
	ALittle.System_CreateView("SuperMarioBros", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "SuperMarioBros");
}

SuperMarioBros.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

SuperMarioBros.__Browser_Shutdown = function() {
}

SuperMarioBros.g_Control = undefined;
SuperMarioBros.g_LayerGroup = undefined;
SuperMarioBros.g_ModuleBasePath = undefined;
SuperMarioBros.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	SuperMarioBros.g_Control = control;
	SuperMarioBros.g_LayerGroup = layer_group;
	SuperMarioBros.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "BattleDefine");
	await Require(script_base_path, "LoginScene");
	await Require(script_base_path, "EditScene");
	await Require(script_base_path, "StageScene");
	await Require(script_base_path, "BattleScene");
	await Require(script_base_path, "BattlePlayer");
	await Require(script_base_path, "BattleLifeMushroom");
	await Require(script_base_path, "BattleEnemyMushroom");
	await Require(script_base_path, "GCenter");
	g_GCenter.Setup();
}

SuperMarioBros.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
}

SuperMarioBros.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "SuperMarioBros";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}