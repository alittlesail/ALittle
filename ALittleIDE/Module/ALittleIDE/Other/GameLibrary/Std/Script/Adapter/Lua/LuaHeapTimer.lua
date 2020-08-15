-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IHeapTimer, " extends class:ALittle.IHeapTimer is nil")
Lua.LuaHeapTimer = Lua.Class(ALittle.IHeapTimer, "Lua.LuaHeapTimer")

function Lua.LuaHeapTimer:Ctor()
	___rawset(self, "_timer", timer.create())
end

function Lua.LuaHeapTimer:Add(delay_ms, loop, interval_ms)
	return timer.add(self._timer, delay_ms, loop, interval_ms)
end

function Lua.LuaHeapTimer:Remove(id)
	return timer.remove(self._timer, id) ~= 0
end

function Lua.LuaHeapTimer:Update(frame_ms)
	timer.update(self._timer, frame_ms)
end

function Lua.LuaHeapTimer:Poll()
	return timer.poll(self._timer)
end

end