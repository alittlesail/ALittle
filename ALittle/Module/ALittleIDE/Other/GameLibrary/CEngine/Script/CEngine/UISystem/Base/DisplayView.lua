
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
DisplayView = Lua.Class(ALittle.DisplayLayout, "ALittle.DisplayView")

function DisplayView:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPIDisplayView())
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
end

