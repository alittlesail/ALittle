-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(Lua.ISocket, " extends class:Lua.ISocket is nil")
LWSocket = Lua.Class(Lua.ISocket, "Emulator.LWSocket")

function LWSocket:ReadMessage()
local ___COROUTINE = coroutine.running()
	local msg_type = 0
	local msg_size = 0
	local server_id = 0
	local server_type = 0
	local protobuf_msg = nil
	local error = nil
	error, msg_size = self:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	msg_size = msg_size - (8)
	error, msg_type = self:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	error, server_id = self:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	error, server_type = self:ReadUint16()
	if error ~= nil then
		return error, nil
	end
	if msg_size <= 0 then
		local full_name = g_LWProtobuf:MsgId2MsgFullName(msg_type)
		if full_name == nil then
			return "unknow msg type:" .. msg_type, nil
		end
		return nil, A_LuaSocketSchedule:CreateMessage(full_name)
	else
		local full_name = g_LWProtobuf:MsgId2MsgFullName(msg_type)
		if full_name == nil then
			full_name = ""
		end
		error, protobuf_msg = self:ReadProtobuf(full_name, msg_size)
		if error ~= nil then
			return error, nil
		end
		if protobuf_msg == nil then
			return "unknow msg type:" .. msg_type, nil
		end
		return nil, protobuf_msg
	end
end

function LWSocket:WriteMessage(full_name, protobuf_msg, protobuf_binary, protobuf_size)
	local msg_type = g_LWProtobuf:MsgFullName2MsgId(full_name)
	if msg_type == nil then
		return "MsgFullName2MsgId failed, full_name:" .. full_name
	end
	self:WriteUint16(protobuf_size + 8)
	self:WriteUint16(msg_type)
	self:WriteUint16(1)
	self:WriteUint16(1)
	self:WriteBinary(protobuf_binary, protobuf_size)
	if full_name ~= "ProtoMsg.MSG_CLIENT_KEEP_LIVE_RSP" then
		g_GCenter:AddLogMessage(protobuf_msg)
	end
	return nil
end

function LWSocket:HandleMessage(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local name = protobuf.messagedescriptor_name(descriptor)
	if name == "MSG_CLIENT_KEEP_LIVE_REQ" then
		self:SendStruct(___all_struct[754290029], "ProtoMsg.MSG_CLIENT_KEEP_LIVE_RSP", {})
		return
	end
	g_GCenter:AddLogMessage(msg)
end

