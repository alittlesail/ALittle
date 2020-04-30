-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


require(___thispath.."../../CEngine/Script/ALittle")
require(___thispath.."IDECenter")
g_Control = nil
g_LayerGroup = nil
g_ModuleBasePath = nil
g_ScriptBasePath = nil
g_ModuleBasePathEx = nil
g_IDEConfig = nil
local Init
Init = function(module_path, layer_group, control)
local ___COROUTINE = coroutine.running()
	g_Control = control
	g_LayerGroup = layer_group
	g_ModuleBasePath = module_path
	g_ModuleBasePathEx = ALittle.File_BaseFilePath() .. module_path
	ALittle.DeleteLog(7)
	local window_width = 1200
	local window_height = 600
	local rate = 1.0
	local flag = ALittle.BitOr(0x00000080, 0x00000020)
	if ALittle.System_GetPlatform() ~= "Windows" and ALittle.System_GetPlatform() ~= "Web" then
		local screen_width = ALittle.System_GetScreenWidth()
		local screen_height = ALittle.System_GetScreenHeight()
		if screen_width > 0 then
			rate = screen_height / screen_width
		end
		window_height = ALittle.Math_Floor(rate * window_width)
		flag = ALittle.BitOr(flag, 0x00000001)
	end
	if ALittle.System_GetPlatform() == "Web" then
		window_width = ALittle.System_GetScreenWidth()
		window_height = ALittle.System_GetScreenHeight()
	end
	ALittle.System_CreateView("ALittleIDE", window_width, window_height, flag, rate)
	ALittle.System_SetViewIcon(module_path .. "/Other/ic_launcher.png")
	g_IDECenter:Setup()
end

g_Application:Setup("ALittleIDE", Init)
g_Application:Run()
