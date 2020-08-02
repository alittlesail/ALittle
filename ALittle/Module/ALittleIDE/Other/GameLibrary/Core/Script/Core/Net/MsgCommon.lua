-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IMessageWriteFactory = Lua.Class(nil, "ALittle.IMessageWriteFactory")

function ALittle.IMessageWriteFactory:SetID(id)
end

function ALittle.IMessageWriteFactory:SetRpcID(id)
end

function ALittle.IMessageWriteFactory:ResetOffset()
end

function ALittle.IMessageWriteFactory:GetOffset()
	return 0
end

function ALittle.IMessageWriteFactory:SetInt(offset, value)
end

function ALittle.IMessageWriteFactory:WriteBool(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteInt(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteLong(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteString(value)
	return 0
end

function ALittle.IMessageWriteFactory:WriteDouble(value)
	return 0
end

ALittle.IMessageReadFactory = Lua.Class(nil, "ALittle.IMessageReadFactory")

function ALittle.IMessageReadFactory:GetDataSize()
	return 0
end

function ALittle.IMessageReadFactory:ReadBool()
	return false
end

function ALittle.IMessageReadFactory:ReadInt()
	return 0
end

function ALittle.IMessageReadFactory:ReadLong()
	return 0
end

function ALittle.IMessageReadFactory:ReadString()
	return ""
end

function ALittle.IMessageReadFactory:ReadDouble()
	return 0
end

function ALittle.IMessageReadFactory:GetReadSize()
	return 0
end

ALittle.IMsgCommon = Lua.Class(nil, "ALittle.IMsgCommon")

function ALittle.IMsgCommon:IsConnected()
	return false
end

function ALittle.IMsgCommon:Close(reason)
end

function ALittle.IMsgCommon:HandleConnectSucceed()
end

function ALittle.IMsgCommon:HandleDisconnect()
end

function ALittle.IMsgCommon:HandleConnectFailed(reason)
end

function ALittle.IMsgCommon:HandleMessage(id, rpc_id, factory)
end

function ALittle.IMsgCommon:SendMsg(T, msg)
	local rflt = T
	self:Send(rflt.hash_code, msg, 0)
end

function ALittle.IMsgCommon:Send(msg_id, msg_body, rpc_id)
	Lua.Throw("not impl")
end

function ALittle.IMsgCommon:SendRPC(thread, msg_id, msg_body)
end

function ALittle.IMsgCommon.Invoke(msg_id, client, msg_body)
	client:Send(msg_id, msg_body, 0)
end

function ALittle.IMsgCommon.InvokeRPC(msg_id, client, msg_body)
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
function ALittle.RegMsgCallback(msg_id, callback)
	if __all_callback[msg_id] ~= nil then
		ALittle.Error("RegMsgCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_callback[msg_id] = callback
end

function ALittle.FindMsgCallback(msg_id)
	return __all_callback[msg_id]
end

local __all_rpc_callback = {}
local __all_rpc_return_id = {}
function ALittle.RegMsgRpcCallback(msg_id, callback, return_id)
	if __all_rpc_callback[msg_id] ~= nil then
		ALittle.Error("RegMsgRpcCallback消息回调函数注册失败，名字为" .. msg_id .. "已存在")
		return
	end
	__all_rpc_callback[msg_id] = callback
	__all_rpc_return_id[msg_id] = return_id
end

function ALittle.FindMsgRpcCallback(msg_id)
	return __all_rpc_callback[msg_id], __all_rpc_return_id[msg_id]
end

end