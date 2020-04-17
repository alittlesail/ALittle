
module("G2048", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	ALittle.Log("__Browser_Setup111111")
	local window_width = 720
	local window_height = 1280
	local rate = 0.5
	local flag = 0x00000020
	if ALittle.System_IsPhone() then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		window_height = ALittle.Math_Floor(screen_height / screen_width * window_width)
		flag = ALittle.BitOr(flag, 0x00000001)
	end
	ALittle.Log("__Browser_Setup222222")
	ALittle.System_CreateView("2048", window_width, window_height, flag, rate)
	ALittle.Log("__Browser_Setup333333")
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	ALittle.Log("__Browser_Setup44444")
	A_ModuleSystem:LoadModule(module_base_path, "G2048")
	ALittle.Log("__Browser_Setup55555")
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
	ALittle.Log("__Module_Setup11111")
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	Require(script_base_path .. "GCenter")
	ALittle.Log("__Module_Setup22222")
	g_GCenter:Setup()
	ALittle.Log("__Module_Setup33333")
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_GCenter:Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "2048"
	info.icon = nil
	info.width_type = 1
	info.width_value = 720
	info.height_type = 1
	info.height_value = 1280
	return info
end

