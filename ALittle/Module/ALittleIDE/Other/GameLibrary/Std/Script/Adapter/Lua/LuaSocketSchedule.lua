-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1628431371, "Lua.lua_socket_schedule_message_info", {
name = "Lua.lua_socket_schedule_message_info", ns_name = "Lua", rl_name = "lua_socket_schedule_message_info", hash_code = 1628431371,
name_list = {"descriptor","full_name","name"},
type_list = {"lua.protobuf_descriptor","string","string"},
option_map = {}
})
ALittle.RegStruct(-297098024, "lua.protobuf_descriptor", {
name = "lua.protobuf_descriptor", ns_name = "lua", rl_name = "protobuf_descriptor", hash_code = -297098024,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1908889092, "Lua.lua_socket_schedule_enum_info", {
name = "Lua.lua_socket_schedule_enum_info", ns_name = "Lua", rl_name = "lua_socket_schedule_enum_info", hash_code = -1908889092,
name_list = {"descriptor","full_name","name"},
type_list = {"lua.protobuf_enum_descriptor","string","string"},
option_map = {}
})
ALittle.RegStruct(1415684675, "lua.protobuf_enum_descriptor", {
name = "lua.protobuf_enum_descriptor", ns_name = "lua", rl_name = "protobuf_enum_descriptor", hash_code = 1415684675,
name_list = {},
type_list = {},
option_map = {}
})

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
	MSG_READ_BINARY = 44,
}

assert(ALittle.ISchedule, " extends class:ALittle.ISchedule is nil")
LuaSocketSchedule = Lua.Class(ALittle.ISchedule, "Lua.LuaSocketSchedule")

function LuaSocketSchedule:Ctor()
	___rawset(self, "_message_map", {})
	___rawset(self, "_upper_message_map", {})
	___rawset(self, "_enum_map", {})
	___rawset(self, "_upper_enum_map", {})
end

function LuaSocketSchedule:Setup()
	self._socket = socket.create()
end

function LuaSocketSchedule:LoadProto(root_path)
	self._message_map = {}
	self._upper_message_map = {}
	self._enum_map = {}
	self._upper_enum_map = {}
	self._importer = protobuf.createimporter(root_path)
	self._factory = protobuf.createfactory()
	local file_map = ALittle.File_GetFileAttrByDir(root_path)
	for file_path, _ in ___pairs(file_map) do
		if ALittle.File_GetFileExtByPathAndUpper(file_path) == "PROTO" then
			local file_descriptor = protobuf.importer_import(self._importer, ALittle.String_Sub(file_path, ALittle.String_Len(root_path) + 2))
			if file_descriptor == nil then
				return "文件加载失败:" .. file_path
			end
			local message_count = protobuf.filedescriptor_messagetypecount(file_descriptor)
			local i = 0
			while true do
				if not(i < message_count) then break end
				local message_descriptor = protobuf.filedescriptor_messagetype(file_descriptor, i)
				if message_descriptor ~= nil then
					local info = {}
					info.descriptor = message_descriptor
					info.full_name = protobuf.messagedescriptor_fullname(message_descriptor)
					info.name = protobuf.messagedescriptor_name(message_descriptor)
					self._message_map[info.full_name] = info
					self._upper_message_map[ALittle.String_Upper(info.name)] = info
				end
				i = i+(1)
			end
			local enum_count = protobuf.filedescriptor_enumtypecount(file_descriptor)
			local i = 0
			while true do
				if not(i < enum_count) then break end
				local enum_descriptor = protobuf.filedescriptor_enumtype(file_descriptor, i)
				if enum_descriptor ~= nil then
					local info = {}
					info.descriptor = enum_descriptor
					info.full_name = protobuf.enumdescriptor_fullname(enum_descriptor)
					info.name = protobuf.enumdescriptor_name(enum_descriptor)
					self._enum_map[info.full_name] = info
					self._upper_enum_map[ALittle.String_Upper(info.name)] = info
				end
				i = i+(1)
			end
		end
	end
	return nil
end

function LuaSocketSchedule:GetMessageInfo(full_name)
	return self._message_map[full_name]
end

function LuaSocketSchedule:FindMessageByUpperKey(key)
	local result = {}
	local count = 0
	for name, info in ___pairs(self._upper_message_map) do
		if ALittle.String_Find(name, key) ~= nil then
			count = count + 1
			result[count] = info
		end
	end
	return result
end

function LuaSocketSchedule:GetEnumDescriptor(full_name)
	local info = self._enum_map[full_name]
	if info == nil then
		return nil
	end
	return info.descriptor
end

function LuaSocketSchedule:CreateMessage(full_name)
	if self._factory == nil then
		return nil
	end
	local info = self._message_map[full_name]
	if info == nil then
		return nil
	end
	return protobuf.createmessage(self._factory, info.descriptor)
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
	elseif event.type >= socket_type.MSG_READ_BINARY then
		ISocket.HandleReadProtobuf(event.id, event.binary_value)
		socket.freebinary(event.binary_value)
	end
end

_G.A_LuaSocketSchedule = LuaSocketSchedule()
