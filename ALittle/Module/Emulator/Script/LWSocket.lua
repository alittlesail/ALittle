-- ALittle Generate Lua And Do Not Edit This Line!
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
		local name = self:MsgId2ProtobufName(msg_type)
		if name == nil then
			name = ""
		end
		if msg_size > 0 then
			local binary_value = nil
			error, binary_value = self:ReadProtobuf(name, msg_size)
			if error ~= nil then
				break
			end
		else
			protobuf_msg = {}
		end
		self:HandleMessage(msg_type, name, protobuf_msg)
	end
end
LWSocket.ReadMessage = Lua.CoWrap(LWSocket.ReadMessage)

function LWSocket:WriteMessage(name, msg)
	local msg_type = self:ProtobufName2MsgId(name)
	if msg_type == nil then
		return
	end
	local size = 0
	local buffer = nil
	self:WriteUint16(msg_type)
	self:WriteUint16(size)
	self:WriteUint16(1)
	self:WriteUint16(1)
	self:WriteBinary(buffer, size)
end

function LWSocket:MsgId2ProtobufName(id)
	return nil
end

function LWSocket:ProtobufName2MsgId(name)
	return nil
end

function LWSocket:HandleMessage(id, name, msg)
end

