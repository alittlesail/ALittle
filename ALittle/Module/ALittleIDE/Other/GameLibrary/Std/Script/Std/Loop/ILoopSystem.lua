-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.ILoopSystem = Lua.Class(nil, "ALittle.ILoopSystem")

function ALittle.ILoopSystem:Update(frame_time)
end

function ALittle.ILoopSystem:AddTimer(delay_ms, callback, loop, interval_ms)
	return 0
end

function ALittle.ILoopSystem:RemoveTimer(id)
	return false
end

function ALittle.ILoopSystem:AddUpdater(object)
end

function ALittle.ILoopSystem:RemoveUpdater(object)
end

function ALittle.ILoopSystem:HasUpdater(object)
	return false
end

end