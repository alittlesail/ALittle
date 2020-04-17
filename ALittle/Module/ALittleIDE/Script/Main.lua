
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	ALittle.DeleteLog(7)
	local window_width = 1200
	local window_height = 600
	local rate = 1.0
	local flag = 0
	flag = ALittle.BitOr(0x00000080, 0x00000020)
	if ALittle.System_IsPhone() then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		rate = screen_height / screen_width
		window_height = ALittle.Math_Floor(rate * window_width)
		flag = ALittle.BitOr(flag, 0x00000001)
	end
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, rate)
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
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_base_path
	g_ScriptBasePath = script_base_path
	Require(script_base_path .. "IDECenter")
	g_IDECenter:Setup(debug)
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_IDECenter:Shutdown()
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

function __Plugin_Setup(control, module_base_path, script_base_path)
end

