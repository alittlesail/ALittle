
module("FlappyBird", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width = 288
	local window_height = 512
	local rate = 1
	local flag = 0x00000020
	if ALittle.System_IsPhone() then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		window_height = ALittle.Math_Floor(screen_height / screen_width * window_width)
		flag = ALittle.BitOr(flag, 0x00000001)
	end
	ALittle.System_CreateView("FlappyBird", window_width, window_height, flag, rate)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "FlappyBird")
end
__Browser_Setup = Lua.CoWrap(__Browser_Setup)

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	Require(script_base_path .. "GCenter")
	g_GCenter:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_GCenter:Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "FlappyBird"
	info.icon = nil
	info.width_type = 1
	info.width_value = 288
	info.height_type = 1
	info.height_value = 512
	return info
end

