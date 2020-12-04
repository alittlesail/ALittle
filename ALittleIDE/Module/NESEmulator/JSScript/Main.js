{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, 0x00000020);
	ALittle.System_CreateView("NESEmulator", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "/Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "NESEmulator");
}

NESEmulator.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

NESEmulator.__Browser_Shutdown = function() {
}

NESEmulator.g_Control = undefined;
NESEmulator.g_LayerGroup = undefined;
NESEmulator.g_ModuleBasePath = undefined;
NESEmulator.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	NESEmulator.g_Control = control;
	NESEmulator.g_LayerGroup = layer_group;
	NESEmulator.g_ModuleBasePath = module_base_path;
	await Require(script_base_path, "GCenter");
	await RequireFromPaths(script_base_path, "Core/", ["NesUtility.alittle", "NesCore.alittle", "NesController.alittle"
		, "NesCPU/NesCPUOpData.alittle", "NesCPU/NesCPU.alittle", "NesMapper/NesMapper.alittle"
		, "NesMapper/NesMapper0.alittle", "NesPAPU/NesPAPU.alittle", "NesPAPU/NesChannelTriangle.alittle"
		, "NesPAPU/NesChannelSquare.alittle", "NesPAPU/NesChannelNoise.alittle", "NesPAPU/NesChannelDM.alittle"
		, "NesPPU/NesPaletteTable.alittle", "NesPPU/NesPPU.alittle", "NesPPU/NesNameTable.alittle"
		, "NesRom/NesTile.alittle", "NesRom/NesRom.alittle"]);
	await Require(script_base_path, "GNes");
	g_GCenter.Setup();
}

NESEmulator.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
}

NESEmulator.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "NESEmulator";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}