-- ALittle Generate Lua
module("Lua", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IHeapTimer, " extends class:ALittle.IHeapTimer is nil")
LuaHeapTimer = Lua.Class(ALittle.IHeapTimer, "Lua.LuaHeapTimer")

function LuaHeapTimer:Ctor()
	___rawset(self, "_timer", timer.create())
end

function LuaHeapTimer:Add(delay_ms, loop, interval_ms)
	return timer.add(self._timer, delay_ms, loop, interval_ms)
end

function LuaHeapTimer:Remove(id)
	return timer.remove(self._timer, id) ~= 0
end

function LuaHeapTimer:Update(frame_ms)
	timer.update(self._timer, frame_ms)
end

function LuaHeapTimer:Poll()
	return timer.poll(self._timer)
end

