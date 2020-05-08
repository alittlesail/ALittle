-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IHeapTimer = Lua.Class(nil, "ALittle.IHeapTimer")

function IHeapTimer:Add(delay_ms, loop, interval_ms)
	return 0
end

function IHeapTimer:Remove(id)
	return false
end

function IHeapTimer:Update(ms)
end

function IHeapTimer:Poll()
	return 0
end

