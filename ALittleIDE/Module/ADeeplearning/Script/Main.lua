-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ADeeplearning == nil then _G.ADeeplearning = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ADeeplearning.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
ADeeplearning.__Browser_Setup = Lua.CoWrap(ADeeplearning.__Browser_Setup)

function ADeeplearning.__Browser_AddModule(module_name, layer_group, module_info)
end

function ADeeplearning.__Browser_Shutdown()
end

ADeeplearning.g_Control = nil
ADeeplearning.g_ModuleBasePath = nil
ADeeplearning.g_ScriptBasePath = nil
function ADeeplearning.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
ADeeplearning.__Module_Setup = Lua.CoWrap(ADeeplearning.__Module_Setup)

function ADeeplearning.__Module_Shutdown()
end

function ADeeplearning.__Module_GetInfo(control, module_base_path, script_base_path)
	return nil
end

function ADeeplearning.__Plugin_Setup(control, module_base_path, script_base_path)
	local ___COROUTINE = coroutine.running()
	ADeeplearning.g_Control = control
	ADeeplearning.g_ModuleBasePath = module_base_path
	ADeeplearning.g_ScriptBasePath = script_base_path
	if ALittle.System_GetPlatform() == "Windows" then
		package.cpath = package.cpath .. ";./" .. module_base_path .. "Other/?.dll"
		require("deeplearning")
		deeplearning.Initialize()
	end
end

function ADeeplearning.__Plugin_Shutdown()
	if deeplearning ~= nil then
		deeplearning.Cleanup()
	end
end

end