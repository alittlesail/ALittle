-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


socket_type = {
	TIMER = 21,
	MSG_CONNECT_SUCCEED = 31,
	MSG_CONNECT_FAILED = 32,
	MSG_DISCONNECTED = 33,
	MSG_READ_UINT8 = 34,
	MSG_READ_INT8 = 35,
	MSG_READ_UINT16 = 36,
	MSG_READ_INT16 = 37,
	MSG_READ_UINT32 = 38,
	MSG_READ_INT32 = 39,
	MSG_READ_UINT64 = 40,
	MSG_READ_INT64 = 41,
	MSG_READ_FLOAT = 42,
	MSG_READ_DOUBLE = 43,
	MSG_READ_PROTOBUF = 44,
}

assert(ALittle.ISchedule, " extends class:ALittle.ISchedule is nil")
LuaSocketSchedule = Lua.Class(ALittle.ISchedule, "Lua.LuaSocketSchedule")

function LuaSocketSchedule:Ctor()
	___rawset(self, "_socket", socket.create())
end

function LuaSocketSchedule:LoadProto(root_path)
	local result = socket.setprotobufroot(self._socket, root_path)
	if not result then
		return "根路径设置失败"
	end
	local file_map = ALittle.File_GetFileAttrByDir(root_path)
	for file_path, _ in ___pairs(file_map) do
		if ALittle.File_GetFileExtByPathAndUpper(file_path) ~= "PROTO" then
			goto continue_1
		end
		result = socket.loadprotobuffile(self._socket, file_path)
		if not result then
			return "文件加载失败:" .. file_path
		end
		::continue_1::
	end
	return nil
end

function LuaSocketSchedule:RunInFrame()
	while true do
		local event = socket.poll(self._socket)
		if event == nil then
			break
		end
		self:HandleEvent(event)
	end
end

function LuaSocketSchedule:Run()
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

function LuaSocketSchedule:HandleEvent(event)
	if event.type == socket_type.MSG_CONNECT_FAILED then
		ISocket.HandleConnectFailed(event.id)
	elseif event.type == socket_type.MSG_CONNECT_SUCCEED then
		ISocket.HandleConnectSucceed(event.id)
	elseif event.type == socket_type.MSG_DISCONNECTED then
		ISocket.HandleDisconnected(event.id)
	elseif event.type >= socket_type.MSG_READ_INT8 and event.type <= socket_type.MSG_READ_INT64 then
		ISocket.HandleReadInt(event.id, event.int_value)
	elseif event.type >= socket_type.MSG_READ_FLOAT and event.type <= socket_type.MSG_READ_DOUBLE then
		ISocket.HandleReadDouble(event.id, event.double_value)
	elseif event.type >= socket_type.MSG_READ_PROTOBUF then
		ISocket.HandleReadProtobuf(event.id, event.protobuf_value)
	end
end

_G.A_LuaSocketSchedule = LuaSocketSchedule()
