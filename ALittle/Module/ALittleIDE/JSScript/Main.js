{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.__Browser_Setup = async function(layer_group, control, module_base_path, script_base_path) {
	ALittle.DeleteLog(7);
	let [window_width, window_height, flag, scale] = ALittle.System_CalcLandscape(1200, 600, ALittle.BitOr(0x00000080, 0x00000020));
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, scale);
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
ALittleIDE.g_IDEServerConfig = undefined;
ALittleIDE.g_MainLayer = undefined;
ALittleIDE.g_DialogLayer = undefined;
ALittleIDE.__Module_Setup = async function(layer_group, control, module_base_path, script_base_path) {
	ALittleIDE.g_Control = control;
	ALittleIDE.g_LayerGroup = layer_group;
	ALittleIDE.g_ModuleBasePath = module_base_path;
	ALittleIDE.g_ModuleBasePathEx = ALittle.File_BaseFilePath() + module_base_path;
	ALittleIDE.g_ScriptBasePath = script_base_path;
	await A_ModuleSystem.LoadPlugin("AUIPlugin");
	ALittleIDE.g_IDEConfig = ALittle.CreateConfigSystem("ALittleIDE.cfg");
	ALittleIDE.g_IDEServerConfig = ALittle.CreateConfigSystem(ALittleIDE.g_ModuleBasePath + "/Other/Server.cfg");
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
	ALittle.System_SetThreadCount(5);
	ALittleIDE.g_MainLayer = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
	ALittleIDE.g_MainLayer.width_type = 4;
	ALittleIDE.g_MainLayer.height_type = 4;
	ALittleIDE.g_LayerGroup.AddChild(ALittleIDE.g_MainLayer);
	ALittleIDE.g_DialogLayer = ALittle.NewObject(ALittle.DisplayLayout, ALittleIDE.g_Control);
	ALittleIDE.g_DialogLayer.width_type = 4;
	ALittleIDE.g_DialogLayer.height_type = 4;
	ALittleIDE.g_LayerGroup.AddChild(ALittleIDE.g_DialogLayer);
	await RequireFromPaths(ALittleIDE.g_ScriptBasePath, "Data/", ["IDEEnum.alittle", "IDEProject.alittle", "IDEUIManager.alittle"]);
	await RequireFromPaths(script_base_path, "Dialog/", ["IDEExport.alittle", "IDEImageSelectDialog.alittle", "IDEProjectExportDialog.alittle", "IDEProjectNewDialog.alittle", "IDEProjectOpenDialog.alittle", "IDEProjectSettingDialog.alittle", "IDEVersionList.alittle"]);
	await RequireFromPaths(script_base_path, "IDE/", ["IDECenter.alittle", "IDEContentEdit.alittle", "IDERevocation.alittle", "IDEUIAccount.alittle", "IDEUICenter.alittle", "IDEUIControlList.alittle", "IDEUIMainMenu.alittle", "IDEUIProjectDropdown.alittle", "IDEUIProjectList.alittle", "IDEUtility.alittle", "UIEdit/IDEUIControlAnti.alittle", "UIEdit/IDEUIControlAttr.alittle", "UIEdit/IDEUIControlTree.alittle", "UIEdit/IDEUIRevocation.alittle", "UIEdit/IDEUITabChild.alittle", "UIEdit/IDEUIUtility.alittle", "UIEdit/Dialog/IDEAttrEventDialog.alittle", "UIEdit/Dialog/IDEAttrTextDialog.alittle", "UIEdit/Setting/DisplayObjectS.alittle", "UIEdit/Setting/DisplayViewS.alittle", "UIEdit/Setting/ImagePlayS.alittle", "UIEdit/Setting/ImageS.alittle", "UIEdit/Setting/QuadS.alittle", "UIEdit/Setting/SpriteS.alittle", "UIEdit/Setting/TextS.alittle", "UIEdit/Setting/TriangleS.alittle", "UIEdit/Setting/DisplayLayoutS.alittle", "UIEdit/Setting/FramePlayS.alittle", "UIEdit/Setting/Grid3S.alittle", "UIEdit/Setting/Grid9S.alittle", "UIEdit/Setting/LinearS.alittle", "UIEdit/Setting/PiechartS.alittle", "UIEdit/Setting/RichAreaS.alittle", "UIEdit/Setting/RichEditS.alittle", "UIEdit/Setting/RichInputS.alittle", "UIEdit/Setting/ScrollBarS.alittle", "UIEdit/Setting/ScrollButtonS.alittle", "UIEdit/Setting/ScrollListS.alittle", "UIEdit/Setting/ScrollScreenS.alittle", "UIEdit/Setting/SliderS.alittle", "UIEdit/Setting/SpringTextButtonS.alittle", "UIEdit/Setting/SpritePlayS.alittle", "UIEdit/Setting/TabS.alittle", "UIEdit/Setting/TextAreaS.alittle", "UIEdit/Setting/TextButtonS.alittle", "UIEdit/Setting/TextCheckButtonS.alittle", "UIEdit/Setting/TextEditS.alittle", "UIEdit/Setting/TextInputS.alittle", "UIEdit/Setting/TextRadioButtonS.alittle", "UIEdit/Setting/TileTableS.alittle", "UIEdit/Setting/DialogS.alittle", "UIEdit/Setting/DropDownS.alittle", "UIEdit/Setting/Grid9ImageS.alittle", "UIEdit/Setting/ImageEditS.alittle", "UIEdit/Setting/ImageInputS.alittle", "UIEdit/Tree/IDEUITreeLogic.alittle", "UIEdit/Tree/IDEUITree.alittle", "UIEdit/Tree/IDEUITreeItem.alittle"]);
	await ALittleIDE.g_IDECenter.Setup();
}

ALittleIDE.__Module_Shutdown = function() {
	ALittleIDE.g_IDECenter.Shutdown();
	ALittleIDE.g_IDEImageSelectDialog.Shutdown();
	ALittleIDE.g_IDEImageManagerDialog.Shutdown();
	ALittleIDE.g_IDEEditImageDialog.Shutdown();
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

}