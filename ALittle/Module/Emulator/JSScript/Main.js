{
if (typeof Emulator === "undefined") window.Emulator = {};


Emulator.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, 0x00000020);
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
	await Require(script_base_path, "IDETree/IDETreeLogic");
	await Require(script_base_path, "IDETree/IDETree");
	await Require(script_base_path, "IDETree/IDETreeValue");
	await Require(script_base_path, "IDETree/IDETreeEnum");
	await Require(script_base_path, "IDETree/IDETreeBool");
	await Require(script_base_path, "IDETree/IDETreeRepeatedValue");
	await Require(script_base_path, "IDETree/IDETreeRepeatedEnum");
	await Require(script_base_path, "IDETree/IDETreeRepeatedBool");
	await Require(script_base_path, "IDETree/IDETreeRepeatedMessage");
	await Require(script_base_path, "IDETree/IDETreeBoolMapBool");
	await Require(script_base_path, "IDETree/IDETreeBoolMapEnum");
	await Require(script_base_path, "IDETree/IDETreeBoolMapValue");
	await Require(script_base_path, "IDETree/IDETreeBoolMapMessage");
	await Require(script_base_path, "IDETree/IDETreeEnumMapBool");
	await Require(script_base_path, "IDETree/IDETreeEnumMapEnum");
	await Require(script_base_path, "IDETree/IDETreeEnumMapValue");
	await Require(script_base_path, "IDETree/IDETreeEnumMapMessage");
	await Require(script_base_path, "IDETree/IDETreeValueMapBool");
	await Require(script_base_path, "IDETree/IDETreeValueMapEnum");
	await Require(script_base_path, "IDETree/IDETreeValueMapValue");
	await Require(script_base_path, "IDETree/IDETreeValueMapMessage");
	await Require(script_base_path, "IDETree/IDETreeMessage");
	await Require(script_base_path, "IDETree/IDETreeMap");
	await Require(script_base_path, "IDETree/IDETreeRepeated");
	await Require(script_base_path, "GUtility");
	await Require(script_base_path, "IDEIMEManager");
	await Require(script_base_path, "PluginSocket");
	Emulator.g_IDEIMEManager.Setup();
	g_GCenter.Setup();
}

Emulator.__Module_Shutdown = function() {
	g_GCenter.Shutdown();
	Emulator.g_IDEIMEManager.Shutdown();
}

Emulator.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "Emulator";
	info.icon = undefined;
	info.width_type = 1;
	info.width_value = 1200;
	info.height_type = 1;
	info.height_value = 600;
	return info;
}

}