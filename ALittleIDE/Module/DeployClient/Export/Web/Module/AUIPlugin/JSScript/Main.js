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

AUIPlugin.__Plugin_Setup = function(control, module_base_path, script_base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		AUIPlugin.g_Control = control;
		AUIPlugin.g_ModuleBasePath = module_base_path;
		AUIPlugin.g_ScriptBasePath = script_base_path;
		await RequireFromPaths(script_base_path, "AUI/", ["AUIWebLoginManager.alittle", "AUIVersionManager.alittle", "AUITool.alittle"
			, "AUIStatLayout.alittle", "AUIRightMenu.alittle", "AUIImageCutPlugin.alittle"
			, "AUIIMEManager.alittle", "AUIFileTreeLayout.alittle", "AUIFileSelectLayout.alittle"
			, "AUIFileSelectDialog.alittle", "AUIEditImageDialog.alittle", "AUIDrawingBoard.alittle"]);
		await RequireFromPaths(script_base_path, "AUICodeEdit/", ["AUICodeSelectCursor.alittle", "AUICodeRevocation.alittle", "AUICodeProject.alittle"
			, "AUICodeParamList.alittle", "AUICodeLineNumber.alittle", "AUICodeLineContainer.alittle"
			, "AUICodeLanguage.alittle", "AUICodeFilterScreen.alittle", "AUICodeEdit.alittle"
			, "AUICodeDefine.alittle", "AUICodeCursor.alittle", "AUICodeComponent.alittle"
			, "AUICodeCompleteScreen.alittle", "ABnf/AUICodeCommon.alittle", "ABnf/AUICodeALittleScript.alittle"
			, "ABnf/AUICodeABnf.alittle"]);
		AUIPlugin.g_AUIIMEManager.Setup();
		___COROUTINE();
	});
}

AUIPlugin.__Plugin_Shutdown = function() {
	AUIPlugin.g_AUIIMEManager.Shutdown();
	g_AUITool.Shutdown();
	g_AUICodeFilterScreen.Shutdown();
	AUIPlugin.AUICodeProject.Shutdown();
}

}