
module("G2048", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


function __Browser_Setup(layer_group, script, control, base_path, debug)
	local window_width = 720
	local window_height = 1280
	local rate = 0.5
	local flag = 0x00000020
	if ALittle.System_GetPlatform() ~= "Windows" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		window_height = math.floor(screen_height / screen_width * window_width)
		flag = bit.bor(flag, 0x00000001)
	end
	ALittle.System_CreateView("2048", window_width, window_height, flag, rate)
	ALittle.System_SetViewIcon(base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule("G2048")
end

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Script = nil
g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
function __Module_Setup(layer_group, script, control, base_path, debug)
	g_Script = script
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = base_path
	g_Script:Require("GCenter")
	g_GCenter:Setup()
end

function __Module_Shutdown()
	g_GCenter:Shutdown()
end

function __Module_GetInfo(script, control, base_path)
	local info = {}
	info.title = "2048"
	info.icon = nil
	info.width_type = 1
	info.width_value = 720
	info.height_type = 1
	info.height_value = 1280
	return info
end

