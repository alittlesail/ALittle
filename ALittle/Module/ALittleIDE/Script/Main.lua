
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


function __Browser_Setup(layer_group, script, control, base_path, debug)
	ALittle.DeleteLog(7)
	local window_width = 1200
	local window_height = 600
	local rate = 1.0
	local flag = bit.bor(0x00000080, 0x00000020)
	if ALittle.System_GetPlatform() ~= "Windows" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		rate = screen_height / screen_width
		window_height = math.floor(rate * window_width)
		flag = bit.bor(flag, 0x00000001)
	end
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, rate)
	ALittle.System_SetViewIcon(base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule("ALittleIDE")
end

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Script = nil
g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
g_ModuleBasePathEx = nil
g_IDEConfig = nil
function __Module_Setup(layer_group, script, control, base_path, debug)
	g_Script = script
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = base_path
	g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. base_path
	g_Script:Require("IDECenter")
	g_IDECenter:Setup(debug)
end

function __Module_Shutdown()
	g_IDECenter:Shutdown()
end

function __Module_GetInfo(script, control, base_path)
	local info = {}
	info.title = "ALittle集成开发环境"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

function __Plugin_Setup(script, control, base_path)
end

