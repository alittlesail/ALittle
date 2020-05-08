-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


ILoopSystem = Lua.Class(nil, "ALittle.ILoopSystem")

function ILoopSystem:Update(frame_time)
end

function ILoopSystem:AddTimer(delay_ms, callback, loop, interval_ms)
	return 0
end

function ILoopSystem:RemoveTimer(id)
	return false
end

function ILoopSystem:AddUpdater(object)
end

function ILoopSystem:RemoveUpdater(object)
end

function ILoopSystem:HasUpdater(object)
	return false
end

