-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ADeeplearning.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcPortrait(950, 600, 0)
	ALittle.System_CreateView("深度学习", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "ADeeplearning")
end
ADeeplearning.__Browser_Setup = Lua.CoWrap(ADeeplearning.__Browser_Setup)

function ADeeplearning.__Browser_AddModule(module_name, layer_group, module_info)
end

function ADeeplearning.__Browser_Shutdown()
end

ADeeplearning.g_Control = nil
ADeeplearning.g_AUIPluinControl = nil
ADeeplearning.g_ModuleBasePath = nil
ADeeplearning.g_ScriptBasePath = nil
ADeeplearning.g_LayerGroup = nil
function ADeeplearning.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	ADeeplearning.g_Control = control
	ADeeplearning.g_ModuleBasePath = module_base_path
	ADeeplearning.g_ScriptBasePath = script_base_path
	ADeeplearning.g_LayerGroup = layer_group
	ADeeplearning.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	ADeeplearning.g_Control:RegisterPlugin("AUIPlugin", ADeeplearning.g_AUIPluinControl)
	if ALittle.System_GetPlatform() == "Windows" then
		package.cpath = package.cpath .. ";./" .. module_base_path .. "Other/?.dll"
		local path = ALittle.File_GetCurrentPath()
		ALittle.File_SetCurrentPath(path .. "/" .. module_base_path .. "Other")
		require("deeplearning")
		ALittle.File_SetCurrentPath(path)
	end
	RequireFromPaths(script_base_path, "Model/", {"CommonTrainLayout.alittle", "XorLayout.alittle", "SpeechLayout.alittle"
		, "MnistLayout.alittle"})
	Require(script_base_path, "GCenter")
	ADeeplearning.g_GCenter:Setup()
end
ADeeplearning.__Module_Setup = Lua.CoWrap(ADeeplearning.__Module_Setup)

function ADeeplearning.__Module_Shutdown()
	ADeeplearning.g_GCenter:Shutdown()
end

function ADeeplearning.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "深度学习"
	info.icon = nil
	info.width_type = 1
	info.width_value = 720
	info.height_type = 1
	info.height_value = 1280
	return info
end

function ADeeplearning.__Plugin_Setup(control, module_base_path, script_base_path)
	local ___COROUTINE = coroutine.running()
	ADeeplearning.g_Control = control
	ADeeplearning.g_ModuleBasePath = module_base_path
	ADeeplearning.g_ScriptBasePath = script_base_path
	ADeeplearning.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	ADeeplearning.g_Control:RegisterPlugin("AUIPlugin", ADeeplearning.g_AUIPluinControl)
	if ALittle.System_GetPlatform() == "Windows" then
		package.cpath = package.cpath .. ";./" .. module_base_path .. "Other/?.dll"
		require("deeplearning")
	end
	RequireFromPaths(script_base_path, "Mnist/", {"CommonTrainLayout.alittle", "XorLayout.alittle", "SpeechLayout.alittle"
		, "MnistLayout.alittle"})
end

function ADeeplearning.__Plugin_Shutdown()
end

end