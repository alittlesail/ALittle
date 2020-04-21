
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	if ALittle.System_IsPhone() then
		local window_width = 720
		local window_height = 1280
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		local rate = screen_height / screen_width
		window_height = ALittle.Math_Floor(rate * window_width)
		local flag = ALittle.BitOr(0x00000001, 0x00000010)
		flag = ALittle.BitOr(flag, 0x00000020)
		ALittle.System_CreateView("A浏览器", window_width, window_height, flag, rate)
	else
		local flag = bit.bor(0x00000080, 0x00000020)
		ALittle.System_CreateView("A浏览器", 1200, 600, flag, 1)
	end
	A_ModuleSystem:LoadModule(module_base_path, "ABrowser")
end
__Browser_Setup = Lua.CoWrap(__Browser_Setup)

function __Browser_AddModule(module_name, layer_group, module_info)
	return g_ABrowser:AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Control = nil
g_LayerGroup = nil
g_ScriptBasePath = nil
g_ModuleBasePath = nil
g_ModuleBasePathEx = nil
g_ConfigSystem = nil
g_ConfigSystemUser = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	g_Control = control
	g_LayerGroup = layer_group
	g_ScriptBasePath = script_base_path
	g_ModuleBasePath = module_base_path
	g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_base_path
	Require(script_base_path .. "Script/ABrowser")
	g_ABrowser:Setup(debug)
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_ABrowser:Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "A浏览器"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

