-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.G2048 == nil then _G.G2048 = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function G2048.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcPortrait(720, 1280, 0)
	ALittle.System_CreateView("2048", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "G2048")
end
G2048.__Browser_Setup = Lua.CoWrap(G2048.__Browser_Setup)

function G2048.__Browser_AddModule(module_name, layer_group, module_info)
end

function G2048.__Browser_Shutdown()
end

G2048.g_Control = nil
G2048.g_LayerGroup = nil
G2048.g_ModuleBasePath = nil
function G2048.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	G2048.g_Control = control
	G2048.g_LayerGroup = layer_group
	G2048.g_ModuleBasePath = module_base_path
	Require(script_base_path, "GCenter")
	G2048.g_GCenter:Setup()
end
G2048.__Module_Setup = Lua.CoWrap(G2048.__Module_Setup)

function G2048.__Module_Shutdown()
	G2048.g_GCenter:Shutdown()
end

function G2048.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "2048"
	info.icon = nil
	info.width_type = 1
	info.width_value = 720
	info.height_type = 1
	info.height_value = 1280
	return info
end

end