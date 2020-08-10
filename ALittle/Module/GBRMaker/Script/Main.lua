-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function GBRMaker.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, ALittle.BitOr(0x00000080, 0x00000020))
	ALittle.System_CreateView("GBRMaker", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "GBRMaker")
end
GBRMaker.__Browser_Setup = Lua.CoWrap(GBRMaker.__Browser_Setup)

function GBRMaker.__Browser_AddModule(module_name, layer_group, module_info)
end

function GBRMaker.__Browser_Shutdown()
end

GBRMaker.g_Control = nil
GBRMaker.g_AUIPluinControl = nil
GBRMaker.g_LayerGroup = nil
GBRMaker.g_ModuleBasePath = nil
function GBRMaker.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	GBRMaker.g_Control = control
	GBRMaker.g_LayerGroup = layer_group
	GBRMaker.g_ModuleBasePath = module_base_path
	GBRMaker.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	Require(script_base_path, "GCenter")
	Require(script_base_path, "GUtility")
	g_GCenter:Setup()
end
GBRMaker.__Module_Setup = Lua.CoWrap(GBRMaker.__Module_Setup)

function GBRMaker.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function GBRMaker.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "GBRMaker"
	info.icon = nil
	info.width_type = 1
	info.width_value = 1200
	info.height_type = 1
	info.height_value = 600
	return info
end

end