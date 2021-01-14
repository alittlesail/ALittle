-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


function DeployClient.__Browser_Setup(layer_group, control, module_base_path, script_base_path)
	ALittle.DeleteLog(7)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, 0x00000080 | 0x00000020)
	ALittle.System_CreateView("DeployClient", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "DeployClient")
end
DeployClient.__Browser_Setup = Lua.CoWrap(DeployClient.__Browser_Setup)

function DeployClient.__Browser_AddModule(module_name, layer_group, module_info)
end

function DeployClient.__Browser_Shutdown()
end

DeployClient.g_Control = nil
DeployClient.g_AUIPluinControl = nil
DeployClient.g_LayerGroup = nil
DeployClient.g_ModuleBasePath = nil
DeployClient.g_ScriptBasePath = nil
DeployClient.g_ModuleBasePathEx = nil
DeployClient.g_DPLConfig = nil
DeployClient.g_DPLServerConfig = nil
DeployClient.g_MainLayer = nil
DeployClient.g_DialogLayer = nil
function DeployClient.__Module_Setup(layer_group, control, module_base_path, script_base_path)
	DeployClient.g_Control = control
	DeployClient.g_LayerGroup = layer_group
	DeployClient.g_ModuleBasePath = module_base_path
	DeployClient.g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_base_path
	DeployClient.g_ScriptBasePath = script_base_path
	DeployClient.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	DeployClient.g_DPLConfig = ALittle.CreateConfigSystem("ALittleDeploy.cfg")
	DeployClient.g_DPLServerConfig = ALittle.CreateConfigSystem(DeployClient.g_ModuleBasePath .. "/Other/Server.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(5)
	DeployClient.g_MainLayer = ALittle.DisplayLayout(DeployClient.g_Control)
	DeployClient.g_MainLayer.width_type = 4
	DeployClient.g_MainLayer.height_type = 4
	DeployClient.g_LayerGroup:AddChild(DeployClient.g_MainLayer)
	DeployClient.g_DialogLayer = ALittle.DisplayLayout(DeployClient.g_Control)
	DeployClient.g_DialogLayer.width_type = 4
	DeployClient.g_DialogLayer.height_type = 4
	DeployClient.g_LayerGroup:AddChild(DeployClient.g_DialogLayer)
	RequireFromPaths(script_base_path, "Dialog/", {"CommonJobDialog.alittle", "BatchJobDialog.alittle", "WaitProcessExitJobDialog.alittle"
		, "SendVirtualKeyJobDialog.alittle", "KillProcessJobDialog.alittle", "DeepCopyJobDialog.alittle"
		, "CreateProcessJobDialog.alittle", "CopyFileJobDialog.alittle"})
	RequireFromPaths(script_base_path, "IDE/", {"DPLUITaskDetail.alittle", "DPLUITaskCenter.alittle", "DPLUIMainMenu.alittle"
		, "DPLUICenter.alittle", "DPLUIAccount.alittle", "DPLCenter.alittle"})
	DeployClient.g_DPLCenter:Setup()
end
DeployClient.__Module_Setup = Lua.CoWrap(DeployClient.__Module_Setup)

function DeployClient.__Module_Shutdown()
	DeployClient.g_DPLCenter:Shutdown()
end

function DeployClient.__Module_GetInfo(control, module_base_path, script_base_path)
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