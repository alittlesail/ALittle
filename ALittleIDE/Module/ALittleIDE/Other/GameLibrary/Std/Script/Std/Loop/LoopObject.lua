-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.LoopObject = Lua.Class(nil, "ALittle.LoopObject")

function ALittle.LoopObject:IsCompleted()
	return true
end

function ALittle.LoopObject:Completed()
end

function ALittle.LoopObject:Update(frame_time)
end

function ALittle.LoopObject:Reset()
end

function ALittle.LoopObject:SetTime(time)
	return time, true
end

function ALittle.LoopObject:SetCompleted()
end

function ALittle.LoopObject:Dispose(deep)
	self:Stop()
end

function ALittle.LoopObject:Start()
	A_LuaLoopSystem:AddUpdater(self)
end

function ALittle.LoopObject:Stop()
	A_LuaLoopSystem:RemoveUpdater(self)
end

end