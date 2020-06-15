{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


AUIPlugin.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
}

AUIPlugin.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

AUIPlugin.__Browser_Shutdown = function() {
}

AUIPlugin.g_Control = undefined;
AUIPlugin.g_ModuleBasePath = undefined;
AUIPlugin.g_ScriptBasePath = undefined;
AUIPlugin.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path, debug) {
}

AUIPlugin.__Module_Shutdown = function() {
}

AUIPlugin.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	return undefined;
}

AUIPlugin.__Plugin_Setup = async function(control, module_base_path, script_base_path) {
	AUIPlugin.g_Control = control;
	AUIPlugin.g_ModuleBasePath = module_base_path;
	AUIPlugin.g_ScriptBasePath = script_base_path;
	await RequireFromPaths(script_base_path, "AUI/", ["AUIEditImageDialog.alittle", "AUIFileSelectDialog.alittle", "AUIImageCutPlugin.alittle", "AUIIMEManager.alittle", "AUIRightMenu.alittle", "AUITool.alittle", "AUIVersionManager.alittle", "AUIWebLoginManager.alittle"]);
	AUIPlugin.g_AUIIMEManager.Setup();
}

AUIPlugin.__Plugin_Shutdown = function() {
	AUIPlugin.g_AUIIMEManager.Shutdown();
	g_AUITool.Shutdown();
}

}