
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


LoopObject = Lua.Class(nil, "ALittle.LoopObject")

function LoopObject:IsCompleted()
	return true
end

function LoopObject:Completed()
end

function LoopObject:Update(frame_time)
end

function LoopObject:Reset()
end

function LoopObject:SetTime(time)
	return time, true
end

function LoopObject:SetCompleted()
end

function LoopObject:Dispose(deep)
	self:Stop()
end

function LoopObject:Start()
	A_LuaLoopSystem:AddUpdater(self)
end

function LoopObject:Stop()
	A_LuaLoopSystem:RemoveUpdater(self)
end

