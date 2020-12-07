-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function NESEmulator.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
	local window_width, window_height, flag, scale = ALittle.System_CalcPortrait(256 * 2, 240 * 2 + 33, 0x00000020)
	ALittle.System_CreateView("NESEmulator", window_width, window_height, flag, scale)
	ALittle.System_SetViewIcon(module_base_path .. "/Other/ic_launcher.png")
	A_ModuleSystem:LoadModule(module_base_path, "NESEmulator")
end
NESEmulator.__Browser_Setup = Lua.CoWrap(NESEmulator.__Browser_Setup)

function NESEmulator.__Browser_AddModule(module_name, layer_group, module_info)
end

function NESEmulator.__Browser_Shutdown()
end

NESEmulator.g_Control = nil
NESEmulator.g_AUIPluinControl = nil
NESEmulator.g_LayerGroup = nil
NESEmulator.g_ModuleBasePath = nil
NESEmulator.g_VersionManager = nil
function NESEmulator.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
	NESEmulator.g_Control = control
	NESEmulator.g_LayerGroup = layer_group
	NESEmulator.g_ModuleBasePath = module_base_path
	NESEmulator.g_AUIPluinControl = A_ModuleSystem:LoadPlugin("AUIPlugin")
	NESEmulator.g_VersionManager = AUIPlugin.AUIVersionManager("139.159.176.119", 1100, "alittle", "NESEmulator")
	Require(script_base_path, "GCenter")
	RequireFromPaths(script_base_path, "Core/", {"NesUtility.alittle", "NesCore.alittle", "NesController.alittle"
		, "NesCPU/NesCPUOpData.alittle", "NesCPU/NesCPU.alittle", "NesMapper/NesMapper.alittle"
		, "NesMapper/NesMapper0.alittle", "NesMapper/NesMapper94.alittle", "NesMapper/NesMapper7.alittle"
		, "NesMapper/NesMapper66.alittle", "NesMapper/NesMapper5.alittle", "NesMapper/NesMapper4.alittle"
		, "NesMapper/NesMapper38.alittle", "NesMapper/NesMapper34.alittle", "NesMapper/NesMapper3.alittle"
		, "NesMapper/NesMapper2.alittle", "NesMapper/NesMapper180.alittle", "NesMapper/NesMapper140.alittle"
		, "NesMapper/NesMapper11.alittle", "NesMapper/NesMapper1.alittle", "NesPAPU/NesPAPU.alittle"
		, "NesPAPU/NesChannelTriangle.alittle", "NesPAPU/NesChannelSquare.alittle", "NesPAPU/NesChannelNoise.alittle"
		, "NesPAPU/NesChannelDM.alittle", "NesPPU/NesPaletteTable.alittle", "NesPPU/NesPPU.alittle"
		, "NesPPU/NesNameTable.alittle", "NesRom/NesTile.alittle", "NesRom/NesRom.alittle"})
	Require(script_base_path, "GNes")
	Require(script_base_path, "GController")
	g_GCenter:Setup()
end
NESEmulator.__Module_Setup = Lua.CoWrap(NESEmulator.__Module_Setup)

function NESEmulator.__Module_Shutdown()
	g_GCenter:Shutdown()
end

function NESEmulator.__Module_GetInfo(control, module_base_path, script_base_path)
	local info = {}
	info.title = "NESEmulator"
	info.icon = nil
	info.width_type = 4
	info.width_value = 0
	info.height_type = 4
	info.height_value = 0
	return info
end

end