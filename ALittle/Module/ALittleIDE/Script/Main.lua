-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path)
	ALittle.DeleteLog(7)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, ALittle.BitOr(0x00000080, 0x00000020))
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "ALittleIDE")
end
__Browser_Setup = Lua.CoWrap(__Browser_Setup)

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Control = nil
g_AUIPluinControl = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
g_ScriptBasePath = nil
g_ModuleBasePathEx = nil
g_IDEConfig = nil
g_IDEServerConfig = nil
g_MainLayer = nil
g_DialogLayer = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path)
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_base_path
	g_ScriptBasePath = script_base_path
	g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	g_IDEConfig = ALittle.CreateConfigSystem("ALittleIDE.cfg")
	g_IDEServerConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/Other/Server.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5)
	g_MainLayer = ALittle.DisplayLayout(g_Control)
	g_MainLayer.width_type = 4
	g_MainLayer.height_type = 4
	g_LayerGroup:AddChild(g_MainLayer)
	g_DialogLayer = ALittle.DisplayLayout(g_Control)
	g_DialogLayer.width_type = 4
	g_DialogLayer.height_type = 4
	g_LayerGroup:AddChild(g_DialogLayer)
	RequireFromPaths(g_ScriptBasePath, "Data/", {"IDEUIManager.alittle", "IDEProject.alittle", "IDEEnum.alittle"})
	RequireFromPaths(script_base_path, "Dialog/", {"IDEVersionList.alittle", "IDEProjectSettingDialog.alittle", "IDEProjectOpenDialog.alittle"
		, "IDEProjectNewDialog.alittle", "IDEProjectExportDialog.alittle", "IDEImageSelectDialog.alittle"
		, "IDEExport.alittle"})
	RequireFromPaths(script_base_path, "IDE/", {"IDEUtility.alittle", "IDEUIProjectList.alittle", "IDEUIProjectDropdown.alittle"
		, "IDEUIMainMenu.alittle", "IDEUIControlList.alittle", "IDEUICodeList.alittle"
		, "IDEUICenter.alittle", "IDEUIAccount.alittle", "IDEContentEdit.alittle"
		, "IDECenter.alittle", "CodeEdit/IDECodeUtility.alittle", "CodeEdit/IDECodeTabChild.alittle"
		, "CodeEdit/Tree/IDECodeTreeLogic.alittle", "CodeEdit/Tree/IDECodeTreeItem.alittle", "CodeEdit/Tree/IDECodeTree.alittle"
		, "UIEdit/IDEUIUtility.alittle", "UIEdit/IDEUITabChild.alittle", "UIEdit/IDEUIRevocation.alittle"
		, "UIEdit/IDEUIControlTree.alittle", "UIEdit/IDEUIControlAnti.alittle", "UIEdit/Dialog/IDEAttrTextDialog.alittle"
		, "UIEdit/Dialog/IDEAttrEventDialog.alittle", "UIEdit/Dialog/IDEAttrControlDialog.alittle", "UIEdit/Setting/DisplayObjectS.alittle"
		, "UIEdit/Setting/DisplayLayoutS.alittle", "UIEdit/Setting/DialogS.alittle", "UIEdit/Setting/TriangleS.alittle"
		, "UIEdit/Setting/TileTableS.alittle", "UIEdit/Setting/TextS.alittle", "UIEdit/Setting/TextEditS.alittle"
		, "UIEdit/Setting/TextCheckButtonS.alittle", "UIEdit/Setting/TextButtonS.alittle", "UIEdit/Setting/TextAreaS.alittle"
		, "UIEdit/Setting/TabS.alittle", "UIEdit/Setting/SpriteS.alittle", "UIEdit/Setting/SpritePlayS.alittle"
		, "UIEdit/Setting/SpringTextButtonS.alittle", "UIEdit/Setting/SliderS.alittle", "UIEdit/Setting/ScrollScreenS.alittle"
		, "UIEdit/Setting/ScrollListS.alittle", "UIEdit/Setting/ScrollButtonS.alittle", "UIEdit/Setting/RichInputS.alittle"
		, "UIEdit/Setting/RichEditS.alittle", "UIEdit/Setting/RichAreaS.alittle", "UIEdit/Setting/QuadS.alittle"
		, "UIEdit/Setting/PiechartS.alittle", "UIEdit/Setting/LinearS.alittle", "UIEdit/Setting/ImageS.alittle"
		, "UIEdit/Setting/ImagePlayS.alittle", "UIEdit/Setting/ImageEditS.alittle", "UIEdit/Setting/Grid9S.alittle"
		, "UIEdit/Setting/Grid9ImageS.alittle", "UIEdit/Setting/Grid3S.alittle", "UIEdit/Setting/FramePlayS.alittle"
		, "UIEdit/Setting/DropDownS.alittle", "UIEdit/Setting/DisplayViewS.alittle", "UIEdit/Setting/TextRadioButtonS.alittle"
		, "UIEdit/Setting/TextInputS.alittle", "UIEdit/Setting/ScrollBarS.alittle", "UIEdit/Setting/ImageInputS.alittle"
		, "UIEdit/Tree/IDEUITreeLogic.alittle", "UIEdit/Tree/IDEUITreeItem.alittle", "UIEdit/Tree/IDEUITree.alittle"})
	g_IDECenter:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_IDEProject:CloseProject()
	g_IDECenter:Shutdown()
	g_IDEImageSelectDialog:Shutdown()
	g_IDEImageManagerDialog:Shutdown()
	g_IDEEditImageDialog:Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "ALittle集成开发环境"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

