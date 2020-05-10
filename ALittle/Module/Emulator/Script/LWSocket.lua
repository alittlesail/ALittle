-- ALittle Generate Lua
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(Lua.ISocket, " extends class:Lua.ISocket is nil")
LWSocket = Lua.Class(Lua.ISocket, "Emulator.LWSocket")

function LWSocket:ReadMessage()
	local msg_type = 0
	local msg_size = 0
	local server_id = 0
	local server_type = 0
	local protobuf_msg = nil
	local error = nil
	while self:IsConnected() do
		error, msg_type = self:ReadUint16()
		if error ~= nil then
			break
		end
		error, msg_size = self:ReadUint16()
		if error ~= nil then
			break
		end
		error, server_id = self:ReadUint16()
		if error ~= nil then
			break
		end
		error, server_type = self:ReadUint16()
		if error ~= nil then
			break
		end
		local name = self:MsgId2MsgFullName(msg_type)
		if msg_size > 0 then
			error, protobuf_msg = self:ReadProtobuf(name, msg_size)
			if error ~= nil then
				break
			end
		end
		self:HandleMessage(msg_type, name, protobuf_msg)
		if protobuf_msg ~= nil then
			protobuf.freemessage(protobuf_msg)
			protobuf_msg = nil
		end
	end
end
LWSocket.ReadMessage = Lua.CoWrap(LWSocket.ReadMessage)

function LWSocket:WriteMessage(name, msg)
	local msg_type = self:MsgFullName2MsgId(name)
	if msg_type == nil then
		return false
	end
	local protobuf_msg = Lua.Table2Protobuf(name)
	if protobuf_msg == nil then
		return false
	end
	local msg_size = protobuf.message_getbytesize(protobuf_msg)
	local binary_value = memory.create(msg_size)
	local result = protobuf.message_serializetoarray(protobuf_msg, binary_value, msg_size)
	if result then
		self:WriteUint16(msg_type)
		self:WriteUint16(msg_size)
		self:WriteUint16(1)
		self:WriteUint16(1)
		self:WriteBinary(binary_value, msg_size)
	end
	protobuf.freemessage(protobuf_msg)
	memory.free(binary_value)
	return result
end

function LWSocket:MsgId2MsgFullName(id)
	return ""
end

function LWSocket:MsgFullName2MsgId(name)
	return nil
end

function LWSocket:HandleMessage(id, name, msg)
end

