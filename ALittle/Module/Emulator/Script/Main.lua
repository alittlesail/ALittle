-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcLandscape(1200, 600, 0x00000020)
	ALittle.System_CreateView("Emulator", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "Emulator")
end
__Browser_Setup = Lua.CoWrap(__Browser_Setup)

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_base_path
	if ALittle.System_GetPlatform() == "Windows" then
		package.path = package.path .. ";./" .. module_base_path .. "Other/?.dll"
		require("memory")
		require("protobuf")
		require("socket")
	end
	Require(script_base_path, "GCenter")
	Require(script_base_path, "IDETool")
	Require(script_base_path, "IDETree/IDETreeLogic")
	Require(script_base_path, "IDETree/IDETree")
	Require(script_base_path, "IDETree/IDETreeValue")
	Require(script_base_path, "IDETree/IDETreeEnum")
	Require(script_base_path, "IDETree/IDETreeBool")
	Require(script_base_path, "IDETree/IDETreeRepeatedValue")
	Require(script_base_path, "IDETree/IDETreeRepeatedEnum")
	Require(script_base_path, "IDETree/IDETreeRepeatedBool")
	Require(script_base_path, "IDETree/IDETreeRepeatedMessage")
	Require(script_base_path, "IDETree/IDETreeBoolMapBool")
	Require(script_base_path, "IDETree/IDETreeBoolMapEnum")
	Require(script_base_path, "IDETree/IDETreeBoolMapValue")
	Require(script_base_path, "IDETree/IDETreeBoolMapMessage")
	Require(script_base_path, "IDETree/IDETreeEnumMapBool")
	Require(script_base_path, "IDETree/IDETreeEnumMapEnum")
	Require(script_base_path, "IDETree/IDETreeEnumMapValue")
	Require(script_base_path, "IDETree/IDETreeEnumMapMessage")
	Require(script_base_path, "IDETree/IDETreeValueMapBool")
	Require(script_base_path, "IDETree/IDETreeValueMapEnum")
	Require(script_base_path, "IDETree/IDETreeValueMapValue")
	Require(script_base_path, "IDETree/IDETreeValueMapMessage")
	Require(script_base_path, "IDETree/IDETreeMessage")
	Require(script_base_path, "IDETree/IDETreeMap")
	Require(script_base_path, "IDETree/IDETreeRepeated")
	Require(script_base_path, "GUtility")
	Require(script_base_path, "IDEIMEManager")
	Require(script_base_path, "PluginSocket")
	g_IDEIMEManager:Setup()
	g_GCenter:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_GCenter:Shutdown()
	g_IDEIMEManager:Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "Emulator"
	info.icon = nil
	info.width_type = 1
	info.width_value = 1200
	info.height_type = 1
	info.height_value = 600
	return info
end

