-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.FlappyBird == nil then _G.FlappyBird = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function FlappyBird.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcPortrait(288, 512, 0)
	ALittle.System_CreateView("FlappyBird", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "FlappyBird")
end
FlappyBird.__Browser_Setup = Lua.CoWrap(FlappyBird.__Browser_Setup)

function FlappyBird.__Browser_AddModule(module_name, layer_group, module_info)
end

function FlappyBird.__Browser_Shutdown()
end

FlappyBird.g_Control = nil
FlappyBird.g_LayerGroup = nil
FlappyBird.g_ModuleBasePath = nil
function FlappyBird.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	FlappyBird.g_Control = control
	FlappyBird.g_LayerGroup = layer_group
	FlappyBird.g_ModuleBasePath = module_base_path
	Require(script_base_path, "GCenter")
	FlappyBird.g_GCenter:Setup()
end
FlappyBird.__Module_Setup = Lua.CoWrap(FlappyBird.__Module_Setup)

function FlappyBird.__Module_Shutdown()
	FlappyBird.g_GCenter:Shutdown()
end

function FlappyBird.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "FlappyBird"
	info.icon = nil
	info.width_type = 1
	info.width_value = 288
	info.height_type = 1
	info.height_value = 512
	return info
end

end