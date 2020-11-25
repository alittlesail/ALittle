{
if (typeof BattleCity === "undefined") window.BattleCity = {};


BattleCity.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(520, 450, 0);
	if (ALittle.System_GetPlatform() === "Web") {
		window_width = 520;
		window_height = 450;
		flag = 0;
		scale = 1;
	}
	ALittle.System_CreateView("BattleCity", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "BattleCity");
}

BattleCity.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

BattleCity.__Browser_Shutdown = function() {
}

BattleCity.g_Control = undefined;
BattleCity.g_LayerGroup = undefined;
BattleCity.g_ModuleBasePath = undefined;
BattleCity.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	BattleCity.g_Control = control;
	BattleCity.g_LayerGroup = layer_group;
	BattleCity.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	await Require(script_base_path, "LoginScene");
	await Require(script_base_path, "BattleSelectScene");
	await Require(script_base_path, "BattleScene");
	await Require(script_base_path, "EditScene");
	await Require(script_base_path, "BattleDefine");
	await Require(script_base_path, "BattleBullet");
	await Require(script_base_path, "BattleRole");
	await Require(script_base_path, "BattlePlayer");
	await Require(script_base_path, "BattleEnemy");
	await Require(script_base_path, "BattleItem");
	await Require(script_base_path, "BattleSettlement");
	g_GCenter.Setup();
}

BattleCity.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
}

BattleCity.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "BattleCity";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}