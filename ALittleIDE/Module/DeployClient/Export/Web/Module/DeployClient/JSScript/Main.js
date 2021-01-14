{
if (typeof DeployClient === "undefined") window.DeployClient = {};


DeployClient.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path) {
	ALittle.DeleteLog(7);
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, 0x00000080 | 0x00000020);
	ALittle.System_CreateView("DeployClient", window_width, window_height, flag, scale);
	ALittle.System_SetViewIcon(module_base_path + "Other/ic_launcher.png");
	await A_ModuleSystem.LoadModule(module_base_path, "DeployClient");
}

DeployClient.__Browser_AddModule = function(module_name, layer_group, module_info) {
}

DeployClient.__Browser_Shutdown = function() {
}

DeployClient.g_Control = undefined;
DeployClient.g_AUIPluinControl = undefined;
DeployClient.g_LayerGroup = undefined;
DeployClient.g_ModuleBasePath = undefined;
DeployClient.g_ScriptBasePath = undefined;
DeployClient.g_ModuleBasePathEx = undefined;
DeployClient.g_DPLConfig = undefined;
DeployClient.g_DPLServerConfig = undefined;
DeployClient.g_MainLayer = undefined;
DeployClient.g_DialogLayer = undefined;
DeployClient.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path) {
	DeployClient.g_Control = control;
	DeployClient.g_LayerGroup = layer_group;
	DeployClient.g_ModuleBasePath = module_base_path;
	DeployClient.g_ModuleBasePathEx = ALittle.File_BaseFilePath() + module_base_path;
	DeployClient.g_ScriptBasePath = script_base_path;
	DeployClient.g_AUIPluinControl = await A_ModuleSystem.LoadPlugin("AUIPlugin");
	DeployClient.g_DPLConfig = ALittle.CreateConfigSystem("ALittleDeploy.cfg");
	DeployClient.g_DPLServerConfig = ALittle.CreateConfigSystem(DeployClient.g_ModuleBasePath + "/Other/Server.cfg");
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
	ALittle.System_SetThreadCount(5);
	DeployClient.g_MainLayer = ALittle.NewObject(ALittle.DisplayLayout, DeployClient.g_Control);
	DeployClient.g_MainLayer.width_type = 4;
	DeployClient.g_MainLayer.height_type = 4;
	DeployClient.g_LayerGroup.AddChild(DeployClient.g_MainLayer);
	DeployClient.g_DialogLayer = ALittle.NewObject(ALittle.DisplayLayout, DeployClient.g_Control);
	DeployClient.g_DialogLayer.width_type = 4;
	DeployClient.g_DialogLayer.height_type = 4;
	DeployClient.g_LayerGroup.AddChild(DeployClient.g_DialogLayer);
	await RequireFromPaths(script_base_path, "Dialog/", ["CommonJobDialog.alittle", "BatchJobDialog.alittle", "WaitProcessExitJobDialog.alittle"
		, "SendVirtualKeyJobDialog.alittle", "KillProcessJobDialog.alittle", "DeepCopyJobDialog.alittle"
		, "CreateProcessJobDialog.alittle", "CopyFileJobDialog.alittle"]);
	await RequireFromPaths(script_base_path, "IDE/", ["DPLUITaskDetail.alittle", "DPLUITaskCenter.alittle", "DPLUIMainMenu.alittle"
		, "DPLUICenter.alittle", "DPLUIAccount.alittle", "DPLCenter.alittle"]);
	await DeployClient.g_DPLCenter.Setup();
}

DeployClient.__Module_Shutdown = function() {
	DeployClient.g_DPLCenter.Shutdown();
}

DeployClient.__Module_GetInfo = function(control, module_base_path, script_base_path) {
	let info = {};
	info.title = "ALittle部署中心";
	info.icon = undefined;
	info.width_type = 4;
	info.width_value = 0;
	info.height_type = 4;
	info.height_value = 0;
	return info;
}

}