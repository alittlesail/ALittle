-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function BattleCity.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(520, 450, 0)
	if ALittle.System_GetPlatform() == "Web" then
		window_width = 520
		window_height = 450
		flag = 0
		scale = 1
	end
	ALittle.System_CreateView("BattleCity", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "BattleCity")
end
BattleCity.__Browser_Setup = Lua.CoWrap(BattleCity.__Browser_Setup)

function BattleCity.__Browser_AddModule(module_name, layer_group, module_info)
end

function BattleCity.__Browser_Shutdown()
end

BattleCity.g_Control = nil
BattleCity.g_LayerGroup = nil
BattleCity.g_ModuleBasePath = nil
function BattleCity.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	BattleCity.g_Control = control
	BattleCity.g_LayerGroup = layer_group
	BattleCity.g_ModuleBasePath = module_base_path
	Require(script_base_path, "GCenter")
	Require(script_base_path, "LoginScene")
	Require(script_base_path, "BattleSelectScene")
	Require(script_base_path, "BattleScene")
	Require(script_base_path, "EditScene")
	Require(script_base_path, "BattleDefine")
	Require(script_base_path, "BattleBullet")
	Require(script_base_path, "BattleRole")
	Require(script_base_path, "BattlePlayer")
	Require(script_base_path, "BattleEnemy")
	Require(script_base_path, "BattleItem")
	Require(script_base_path, "BattleSettlement")
	g_GCenter:Setup()
end
BattleCity.__Module_Setup = Lua.CoWrap(BattleCity.__Module_Setup)

function BattleCity.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function BattleCity.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "BattleCity"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end