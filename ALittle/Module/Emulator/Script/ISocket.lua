-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __MAX_ID = 0
SocketStatus = {
	SS_IDLE = 0,
	SS_CONNECTING = 1,
	SS_CONNECTED = 1,
}

local __SOCKET_MAP = {}
ISocket = Lua.Class(nil, "Emulator.ISocket")

function ISocket:Ctor(socket_system)
	__MAX_ID = __MAX_ID + 1
	___rawset(self, "_id", __MAX_ID)
	___rawset(self, "_socket_system", socket_system)
	___rawset(self, "_status", SocketStatus.SS_IDLE)
end

function ISocket:IsConnected()
	return self._status == SocketStatus.SS_CONNECTED
end

function ISocket:IsConnecting()
	return self._status == SocketStatus.SS_CONNECTING
end

function ISocket:Connect(ip, port)
local ___COROUTINE = coroutine.running()
	if self:IsConnecting() then
		return "已经正在连接"
	end
	if self:IsConnected() then
		return "已经连接成，请先关闭连接"
	end
	self._connect_thread = ___COROUTINE
	self._status = SocketStatus.SS_CONNECTING
	socket.connect(self._socket_system, self._id, ip, port)
	return coroutine.yield()
end

