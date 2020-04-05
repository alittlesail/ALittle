
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IMessageWriteFactory = Lua.Class(nil, "ALittle.IMessageWriteFactory")

function IMessageWriteFactory:SetID(id)
end

function IMessageWriteFactory:SetRpcID(id)
end

function IMessageWriteFactory:ResetOffset()
end

function IMessageWriteFactory:GetOffset()
	return 0
end

function IMessageWriteFactory:SetInt(offset, value)
end

function IMessageWriteFactory:WriteBool(value)
	return 0
end

function IMessageWriteFactory:WriteInt(value)
	return 0
end

function IMessageWriteFactory:WriteLong(value)
	return 0
end

function IMessageWriteFactory:WriteString(value)
	return 0
end

function IMessageWriteFactory:WriteDouble(value)
	return 0
end

IMessageReadFactory = Lua.Class(nil, "ALittle.IMessageReadFactory")

function IMessageReadFactory:GetTotalSize()
	return 0
end

function IMessageReadFactory:ReadBool()
	return false
end

function IMessageReadFactory:ReadInt()
	return 0
end

function IMessageReadFactory:ReadLong()
	return 0
end

function IMessageReadFactory:ReadString()
	return ""
end

function IMessageReadFactory:ReadDouble()
	return 0
end

function IMessageReadFactory:GetReadSize()
	return 0
end

IMsgCommon = Lua.Class(nil, "ALittle.IMsgCommon")

function IMsgCommon:IsConnected()
	return false
end

function IMsgCommon:HandleConnectSucceed()
end

function IMsgCommon:HandleDisconnect()
end

function IMsgCommon:HandleConnectFailed(reason)
end

function IMsgCommon:HandleMessage(id, rpc_id, factory)
end

function IMsgCommon:Send(msg_id, msg_body, rpc_id)
	Lua.Throw("not impl")
end

function IMsgCommon:SendRPC(thread, msg_id, msg_body)
end

function IMsgCommon.Invoke(msg_id, client, msg_body)
	client:Send(msg_id, msg_body, 0)
end

function IMsgCommon.InvokeRPC(msg_id, client, msg_body)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	if not client:IsConnected() then
		return "连接还没成功", nil
	end
	client:SendRPC(___COROUTINE, msg_id, msg_body)
	return coroutine.yield()
end

local __all_callback = {}
function RegMsgCallback(msg_id, callback)
	if __all_callback[msg_id] ~= nil then
		Error("RegMsgCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_callback[msg_id] = callback
end

function FindMsgCallback(msg_id)
	return __all_callback[msg_id]
end

local __all_rpc_callback = {}
local __all_rpc_return_id = {}
function RegMsgRpcCallback(msg_id, callback, return_id)
	if __all_rpc_callback[msg_id] ~= nil then
		Error("RegMsgRpcCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_rpc_callback[msg_id] = callback
	__all_rpc_return_id[msg_id] = return_id
end

function FindMsgRpcCallback(msg_id)
	return __all_rpc_callback[msg_id], __all_rpc_return_id[msg_id]
end

