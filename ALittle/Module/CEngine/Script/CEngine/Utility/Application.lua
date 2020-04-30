-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.ISchedule, " extends class:ALittle.ISchedule is nil")
Application = Lua.Class(ALittle.ISchedule, "ALittle.Application")

function Application:Setup(name, init)
	local version_system = ALittle.VersionSystem.CreateVersionSystem("", name)
	if version_system ~= nil then
		version_system:UpdateModule()
	end
	local control = ControlSystem(name)
	local layer_group = DisplayLayout(control)
	A_LayerManager:AddChild(layer_group)
	if init ~= nil then
		init("Module/" .. name .. "/", layer_group, control)
	end
end
Application.Setup = Lua.CoWrap(Application.Setup)

_G.g_Application = Application()
