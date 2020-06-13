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
	A_ModuleSystem:LoadPlugin("AUIPlugin")
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
	RequireFromPaths(g_ScriptBasePath, "Data/", {"IDEEnum.alittle", "IDEProject.alittle", "IDEUIManager.alittle"})
	RequireFromPaths(script_base_path, "Dialog/", {"IDEExportDialog.alittle", "IDEImageSelectDialog.alittle", "IDEVersionList.alittle"})
	RequireFromPaths(script_base_path, "IDE/", {"IDECenter.alittle", "IDEUIAccount.alittle", "IDEUICenter.alittle", "IDEUIMainMenu.alittle", "IDEUIProjectDropdown.alittle", "UIEdit/IDEUIControlAnti.alittle", "UIEdit/IDEUIControlAttr.alittle", "UIEdit/IDEUIControlList.alittle", "UIEdit/IDEUIControlTree.alittle", "UIEdit/IDEUIProjectList.alittle", "UIEdit/IDEUIUtility.alittle", "UIEdit/Dialog/IDEAttrEventDialog.alittle", "UIEdit/Dialog/IDEAttrTextDialog.alittle"})
	g_IDECenter:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
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

