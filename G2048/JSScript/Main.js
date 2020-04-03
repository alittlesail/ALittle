{
if (typeof G2048 === "undefined") G2048 = {};


G2048.__Browser_Setup = async function(layer_group, control, base_path, debug) {
	let window_width = 720;
	let window_height = 1280;
	let rate = 0.5;
	let flag = 0x00000020;
	ALittle.System_CreateView("2048", window_width, window_height, flag, rate);
	ALittle.System_SetViewIcon(base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(base_path, "G2048");
}

G2048.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

G2048.__Browser_Shutdown = function() {
}

G2048.g_Control = undefined;
G2048.g_LayerGroup = undefined;
G2048.g_ModuleBasePath = undefined;
G2048.__Module_Setup = async function(layer_group, control, base_path, debug) {
	G2048.g_Control = control;
	G2048.g_LayerGroup = layer_group;
	G2048.g_ModuleBasePath = base_path;
	{
		ALittle.Log(base_path);
		let name_list = ["item_2", "item_4", "item_8", "item_16", "item_32", "item_64", "item_128", "item_256", "item_512", "item_1024", "item_2048", "main_menu", "main_scene"];
		await G2048.g_Control.RegisterInfoByHttp(location.host, ALittle.Math_ToInt(location.port), base_path, name_list);
	}
	await Require(base_path + "GCenter");
	G2048.g_GCenter.Setup();
}

G2048.__Module_Shutdown = function() {
	G2048.g_GCenter.Shutdown();
}

G2048.__Module_GetInfo = function(control, base_path) {
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