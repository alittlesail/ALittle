-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


socket_type = {
	TIMER = 21,
}

assert(ALittle.ISchedule, " extends class:ALittle.ISchedule is nil")
SocketSchedule = Lua.Class(ALittle.ISchedule, "Lua.SocketSchedule")

function SocketSchedule:Ctor()
	___rawset(self, "_socket", socket.create())
end

function SocketSchedule:RunInFrame()
	while true do
		local event = socket.poll(self._socket)
		if event == nil then
			break
		end
		self:HandleEvent(event)
	end
end

function SocketSchedule:Run()
	socket.timer(self._socket, 16)
	while true do
		local event = socket.poll(self._socket)
		if event == nil then
			break
		end
		if event.type == socket_type.TIMER then
			if self._last_time ~= nil then
				A_LuaLoopSystem:Update(event.time - self._last_time)
				A_LuaWeakLoopSystem:Update(event.time - self._last_time)
			end
			self._last_time = event.time
			socket.timer(self._socket, 16)
		else
			self:HandleEvent(event)
		end
	end
end

function SocketSchedule:HandleEvent(event)
end

_G.A_SocketSchedule = SocketSchedule()
