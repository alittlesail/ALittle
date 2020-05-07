-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


SocketStatus = {
	SS_IDLE = 0,
	SS_CONNECTING = 1,
	SS_CONNECTED = 2,
}

local __MAX_ID = 0
local __SOCKET_MAP = {}
ISocket = Lua.Class(nil, "Lua.ISocket")

function ISocket:Ctor(disconnected_callback)
	__MAX_ID = __MAX_ID + 1
	___rawset(self, "_id", __MAX_ID)
	___rawset(self, "_status", SocketStatus.SS_IDLE)
	___rawset(self, "_disconnected_callback", disconnected_callback)
	___rawset(self, "_socket", A_LuaSocketSchedule._socket)
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
		return "已经连接，请先关闭连接"
	end
	self._status = SocketStatus.SS_CONNECTING
	socket.connect(self._socket, self._id, ip, port)
	self._connect_thread = ___COROUTINE
	__SOCKET_MAP[self._id] = self
	return coroutine.yield()
end

function ISocket:Close()
	socket.close(self._socket, self._id)
	__SOCKET_MAP[self._id] = nil
	self._status = SocketStatus.SS_IDLE
	if self._connect_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(self._connect_thread, "closed")
		if result ~= true then
			ALittle.Error(error)
		end
		self._connect_thread = nil
	end
	if self._read_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(self._read_thread, "closed")
		if result ~= true then
			ALittle.Error(error)
		end
		self._read_thread = nil
	end
end

function ISocket:ReadMessage()
end
ISocket.ReadMessage = Lua.CoWrap(ISocket.ReadMessage)

function ISocket:CalcProtobufSize(name, table)
	return socket.calcprotobufsize(self._socket, name, table)
end

function ISocket:ReadUint8()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readuint8(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadInt8()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readint8(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadUint16()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readuint16(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadInt16()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readint16(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadUint32()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readuint32(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadInt32()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readint32(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadUint64()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readuint64(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadInt64()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readint64(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadFloat()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readfloat(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadDouble()
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readdouble(self._socket, self._id)
	return coroutine.yield()
end

function ISocket:ReadProtobuf(name, len)
local ___COROUTINE = coroutine.running()
	if not self:IsConnected() then
		return "还未连接成功", 0
	end
	if self._read_thread ~= nil then
		return "已经正在读取", 0
	end
	self._read_thread = ___COROUTINE
	socket.readprotobuf(self._socket, self._id, name, len)
	return coroutine.yield()
end

function ISocket:WriteUint8(value)
	if not self:IsConnected() then
		return
	end
	socket.writeuint8(self._socket, self._id, value)
end

function ISocket:WriteInt8(value)
	if not self:IsConnected() then
		return
	end
	socket.writeint8(self._socket, self._id, value)
end

function ISocket:WriteUint16(value)
	if not self:IsConnected() then
		return
	end
	socket.writeuint16(self._socket, self._id, value)
end

function ISocket:WriteInt16(value)
	if not self:IsConnected() then
		return
	end
	socket.writeint16(self._socket, self._id, value)
end

function ISocket:WriteUint32(value)
	if not self:IsConnected() then
		return
	end
	socket.writeuint32(self._socket, self._id, value)
end

function ISocket:WriteInt32(value)
	if not self:IsConnected() then
		return
	end
	socket.writeint32(self._socket, self._id, value)
end

function ISocket:WriteUint64(value)
	if not self:IsConnected() then
		return
	end
	socket.writeuint64(self._socket, self._id, value)
end

function ISocket:WriteInt64(value)
	if not self:IsConnected() then
		return
	end
	socket.writeint64(self._socket, self._id, value)
end

function ISocket:WriteFloat(value)
	if not self:IsConnected() then
		return
	end
	socket.writefloat(self._socket, self._id, value)
end

function ISocket:WriteDouble(value)
	if not self:IsConnected() then
		return
	end
	socket.writedouble(self._socket, self._id, value)
end

function ISocket:WriteProtobuf(name, table)
	if not self:IsConnected() then
		return
	end
	socket.writeprotobuf(self._socket, self._id, name, table)
end

function ISocket.HandleConnectFailed(id)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	__SOCKET_MAP[id] = nil
	socket._status = SocketStatus.SS_IDLE
	local result, error = ALittle.Coroutine.Resume(socket._connect_thread, "connect failed")
	if result ~= true then
		ALittle.Error(error)
	end
	socket._connect_thread = nil
end

function ISocket.HandleConnectSucceed(id)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	socket._status = SocketStatus.SS_CONNECTED
	local result, error = ALittle.Coroutine.Resume(socket._connect_thread, nil)
	if result ~= true then
		ALittle.Error(error)
	end
	socket._connect_thread = nil
	socket:ReadMessage()
end

function ISocket.HandleDisconnected(id)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	__SOCKET_MAP[id] = nil
	socket._status = SocketStatus.SS_IDLE
	if socket._read_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(socket._read_thread, "disconnected")
		if result ~= true then
			ALittle.Error(error)
		end
		socket._read_thread = nil
	end
	if socket._disconnected_callback ~= nil then
		socket._disconnected_callback()
	end
end

function ISocket.HandleReadInt(id, value)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	__SOCKET_MAP[id] = nil
	if socket._read_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(socket._read_thread, value)
		if result ~= true then
			ALittle.Error(error)
		end
		socket._read_thread = nil
	end
end

function ISocket.HandleReadDouble(id, value)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	__SOCKET_MAP[id] = nil
	if socket._read_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(socket._read_thread, value)
		if result ~= true then
			ALittle.Error(error)
		end
		socket._read_thread = nil
	end
end

function ISocket.HandleReadProtobuf(id, value)
	local socket = __SOCKET_MAP[id]
	if socket == nil then
		return
	end
	__SOCKET_MAP[id] = nil
	if socket._read_thread ~= nil then
		local result, error = ALittle.Coroutine.Resume(socket._read_thread, value)
		if result ~= true then
			ALittle.Error(error)
		end
		socket._read_thread = nil
	end
end

