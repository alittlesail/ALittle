-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


function ALittleDeploy.__Browser_Setup(layer_group, control, module_base_path, script_base_path)
	ALittle.DeleteLog(7)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, 0x00000080 | 0x00000020)
	ALittle.System_CreateView("ALittleDeploy", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "ALittleDeploy")
end
ALittleDeploy.__Browser_Setup = Lua.CoWrap(ALittleDeploy.__Browser_Setup)

function ALittleDeploy.__Browser_AddModule(module_name, layer_group, module_info)
end

function ALittleDeploy.__Browser_Shutdown()
end

ALittleDeploy.g_Control = nil
ALittleDeploy.g_AUIPluinControl = nil
ALittleDeploy.g_LayerGroup = nil
ALittleDeploy.g_ModuleBasePath = nil
ALittleDeploy.g_ScriptBasePath = nil
ALittleDeploy.g_ModuleBasePathEx = nil
ALittleDeploy.g_DPLConfig = nil
ALittleDeploy.g_DPLServerConfig = nil
ALittleDeploy.g_MainLayer = nil
ALittleDeploy.g_DialogLayer = nil
function ALittleDeploy.__Module_Setup(layer_group, control, module_base_path, script_base_path)
	ALittleDeploy.g_Control = control
	ALittleDeploy.g_LayerGroup = layer_group
	ALittleDeploy.g_ModuleBasePath = module_base_path
	ALittleDeploy.g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_base_path
	ALittleDeploy.g_ScriptBasePath = script_base_path
	ALittleDeploy.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	ALittleDeploy.g_DPLConfig = ALittle.CreateConfigSystem("ALittleDeploy.cfg")
	ALittleDeploy.g_DPLServerConfig = ALittle.CreateConfigSystem(ALittleDeploy.g_ModuleBasePath .. "/Other/Server.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5)
	ALittleDeploy.g_MainLayer = ALittle.DisplayLayout(ALittleDeploy.g_Control)
	ALittleDeploy.g_MainLayer.width_type = 4
	ALittleDeploy.g_MainLayer.height_type = 4
	ALittleDeploy.g_LayerGroup:AddChild(ALittleDeploy.g_MainLayer)
	ALittleDeploy.g_DialogLayer = ALittle.DisplayLayout(ALittleDeploy.g_Control)
	ALittleDeploy.g_DialogLayer.width_type = 4
	ALittleDeploy.g_DialogLayer.height_type = 4
	ALittleDeploy.g_LayerGroup:AddChild(ALittleDeploy.g_DialogLayer)
	RequireFromPaths(script_base_path, "Data/", {})
	RequireFromPaths(script_base_path, "Dialog/", {})
	RequireFromPaths(script_base_path, "IDE/", {"DPLUITaskCenter.alittle", "DPLUIMainMenu.alittle", "DPLUICenter.alittle"
		, "DPLUIAccount.alittle", "DPLCenter.alittle"})
	ALittleDeploy.g_DPLCenter:Setup()
end
ALittleDeploy.__Module_Setup = Lua.CoWrap(ALittleDeploy.__Module_Setup)

function ALittleDeploy.__Module_Shutdown()
	ALittleDeploy.g_DPLCenter:Shutdown()
end

function ALittleDeploy.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "ALittle部署中心"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end