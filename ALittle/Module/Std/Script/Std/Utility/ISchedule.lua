-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


ISchedule = Lua.Class(nil, "ALittle.ISchedule")

function ISchedule:Run()
end

