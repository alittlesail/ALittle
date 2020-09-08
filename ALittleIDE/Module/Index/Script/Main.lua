-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Index == nil then _G.Index = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function Index.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, 0x00000020)
	ALittle.System_CreateView("Index", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "Index")
end
Index.__Browser_Setup = Lua.CoWrap(Index.__Browser_Setup)

function Index.__Browser_AddModule(module_name, layer_group, module_info)
end

function Index.__Browser_Shutdown()
end

Index.g_Control = nil
Index.g_LayerGroup = nil
Index.g_ModuleBasePath = nil
function Index.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	Index.g_Control = control
	Index.g_LayerGroup = layer_group
	Index.g_ModuleBasePath = module_base_path
	Require(script_base_path, "GCenter")
	g_GCenter:Setup()
end
Index.__Module_Setup = Lua.CoWrap(Index.__Module_Setup)

function Index.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function Index.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "Index"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end