-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


local GetSchedule
GetSchedule = function()
	return A_LuaSchedule
end

_G.A_Schedule = GetSchedule()
