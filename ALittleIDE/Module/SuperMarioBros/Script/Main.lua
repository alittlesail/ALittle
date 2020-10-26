-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function SuperMarioBros.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(560, 460, 0x00000020)
	ALittle.System_CreateView("SuperMarioBros", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "SuperMarioBros")
end
SuperMarioBros.__Browser_Setup = Lua.CoWrap(SuperMarioBros.__Browser_Setup)

function SuperMarioBros.__Browser_AddModule(module_name, layer_group, module_info)
end

function SuperMarioBros.__Browser_Shutdown()
end

SuperMarioBros.g_Control = nil
SuperMarioBros.g_LayerGroup = nil
SuperMarioBros.g_ModuleBasePath = nil
function SuperMarioBros.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	SuperMarioBros.g_Control = control
	SuperMarioBros.g_LayerGroup = layer_group
	SuperMarioBros.g_ModuleBasePath = module_base_path
	Require(script_base_path, "BattleDefine")
	Require(script_base_path, "LoginScene")
	Require(script_base_path, "EditScene")
	Require(script_base_path, "StageScene")
	Require(script_base_path, "BattleScene")
	Require(script_base_path, "BattlePlayer")
	Require(script_base_path, "BattleLifeMushroom")
	Require(script_base_path, "BattleEnemyMushroom")
	Require(script_base_path, "GCenter")
	g_GCenter:Setup()
end
SuperMarioBros.__Module_Setup = Lua.CoWrap(SuperMarioBros.__Module_Setup)

function SuperMarioBros.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function SuperMarioBros.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "SuperMarioBros"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end