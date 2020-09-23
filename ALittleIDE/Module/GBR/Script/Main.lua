-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBR == nil then _G.GBR = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function GBR.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, 0x00000020)
	ALittle.System_CreateView("GBR", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "GBR")
end
GBR.__Browser_Setup = Lua.CoWrap(GBR.__Browser_Setup)

function GBR.__Browser_AddModule(module_name, layer_group, module_info)
end

function GBR.__Browser_Shutdown()
end

GBR.g_Control = nil
GBR.g_LayerGroup = nil
GBR.g_ModuleBasePath = nil
function GBR.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	GBR.g_Control = control
	GBR.g_LayerGroup = layer_group
	GBR.g_ModuleBasePath = module_base_path
	Require(script_base_path, "GCenter")
	g_GCenter:Setup()
end
GBR.__Module_Setup = Lua.CoWrap(GBR.__Module_Setup)

function GBR.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function GBR.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "GBR"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end