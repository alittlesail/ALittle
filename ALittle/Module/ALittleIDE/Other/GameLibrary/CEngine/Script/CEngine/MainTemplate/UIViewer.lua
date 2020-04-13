
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(1225542858, "ALittle.UIViewModuleDebugInfo", {
name = "ALittle.UIViewModuleDebugInfo", ns_name = "ALittle", rl_name = "UIViewModuleDebugInfo", hash_code = 1225542858,
name_list = {"window_width","window_height","title","ui_name"},
type_list = {"int","int","string","string"},
option_map = {}
})

g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	local error, info = Lua.TCall(String_JsonDecode, debug)
	local screen_width = System_GetScreenWidth()
	local screen_height = System_GetScreenHeight()
	local window_width = info.window_width
	local window_height = info.window_height
	local rate = 1.0
	if System_GetPlatform() ~= "Windows" then
		window_width = Math_Floor(screen_width / screen_height * window_height)
	else
		if window_width > screen_width or window_height > screen_height then
			rate = 0.5
		end
	end
	System_CreateView(info.title, window_width, window_height, ALittle.UIEnumTypes.VIEW_RESIZABLE, rate)
	local layer = DisplayLayout(g_Control)
	layer.width_type = UIEnumTypes.SIZE_MARGIN
	layer.height_type = UIEnumTypes.SIZE_MARGIN
	g_LayerGroup:AddChild(layer)
	g_Control:CreateControl(info.ui_name, nil, layer)
end

function PreLoadFile(ui_name, layer, result)
end

function __Module_Shutdown()
end

function __Module_GetInfo(control, base_path)
	local info = {}
	info.title = "UIViewer"
	info.icon = nil
	info.width_type = UIEnumTypes.SIZE_MARGIN
	info.width_value = 0
	info.height_type = UIEnumTypes.SIZE_MARGIN
	info.height_value = 0
	return info
end

function __Plugin_Setup(control, module_base_path, script_base_path, debug)
end

function __Plugin_Shutdown()
end

