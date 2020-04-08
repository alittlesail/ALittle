
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(361433949, "ALittle.MsgRPCInfo", {
name = "ALittle.MsgRPCInfo", ns_name = "ALittle", rl_name = "MsgRPCInfo", hash_code = 361433949,
name_list = {"rpc_id","thread"},
type_list = {"int","ALittle.Thread"},
option_map = {}
})
RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})

IMsgCommonNative = Lua.Class(nil, "ALittle.IMsgCommonNative")

function IMsgCommonNative:SetID(id)
end

function IMsgCommonNative:GetID()
	return 0
end

function IMsgCommonNative:Connect(ip, port)
end

function IMsgCommonNative:IsConnected()
	return false
end

function IMsgCommonNative:SendFactory(factory)
end

function IMsgCommonNative:Close()
end

IMsgCommonTemplate = Lua.Class(nil, "ALittle.IMsgCommonTemplate")

function IMsgCommonTemplate:Ctor()
	___rawset(self, "_last_recv_time", 0)
	___rawset(self, "_id_creator", SafeIDCreator())
	___rawset(self, "_id_map_rpc", {})
end

function IMsgCommonTemplate:GetID()
	return self._interface:GetID()
end

function IMsgCommonTemplate:IsConnected()
	return self._interface:IsConnected()
end

function IMsgCommonTemplate:MessageRead(factory, msg_id)
	local invoke = CreateProtocolInvokeInfo(msg_id)
	local object, size = PS_ReadMessageForReceive(factory, invoke, nil, factory:GetTotalSize())
	return object
end

function IMsgCommonTemplate:MessageWrite(msg_id, msg_body)
	local invoke = CreateProtocolInvokeInfo(msg_id)
	self._write_factory:ResetOffset()
	PS_WriteMessageForSend(self._write_factory, invoke, nil, msg_body)
	self._write_factory:SetID(msg_id)
end

function IMsgCommonTemplate:HandleMessage(id, rpc_id, factory)
	if id == 0 then
		self._last_recv_time = Time_GetCurTime()
		return
	end
	if rpc_id == 0 then
		local callback = FindMsgCallback(id)
		if callback == nil then
			local name = "unknow"
			local rflt = FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			Log("MsgSystem.HandleMessage can't find callback by id:" .. id .. ", name:" .. name)
			return
		end
		local msg = self:MessageRead(factory, id)
		if msg == nil then
			local name = "unknow"
			local rflt = FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id .. ", name:" .. name)
			return
		end
		callback(self, msg)
		return
	end
	if rpc_id > 0 then
		self:HandleRPCRequest(id, rpc_id, factory)
		return
	end
	rpc_id = -rpc_id
	self._id_creator:ReleaseID(rpc_id)
	local info = self._id_map_rpc[rpc_id]
	if info == nil then
		Log("MsgSystem.HandleMessage can't find rpc info by id:" .. id)
		return
	end
	self._id_map_rpc[rpc_id] = nil
	if id == 1 then
		local result, reason = Coroutine.Resume(info.thread, factory:ReadString())
		if result ~= true then
			Error(reason)
		end
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		local result, reason = Coroutine.Resume(info.thread, "MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		if result ~= true then
			Error(reason)
		end
		Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local result, reason = Coroutine.Resume(info.thread, nil, msg)
	if result ~= true then
		Error(reason)
	end
end

function IMsgCommonTemplate:SendMsg(T, msg)
	local info = T
	self:Send(info.hash_code, msg, 0)
end

function IMsgCommonTemplate:Send(msg_id, msg_body, rpc_id)
	if not self:IsConnected() then
		return
	end
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
end

function IMsgCommonTemplate:SendRpcError(rpc_id, reason)
	if not self:IsConnected() then
		return
	end
	self._write_factory:ResetOffset()
	self._write_factory:SetID(1)
	self._write_factory:SetRpcID(-rpc_id)
	self._write_factory:WriteString(reason)
	self._interface:SendFactory(self._write_factory)
end

function IMsgCommonTemplate:SendRPC(thread, msg_id, msg_body)
	local rpc_id = self._id_creator:CreateID()
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
	local info = {}
	info.thread = thread
	info.rpc_id = rpc_id
	self._id_map_rpc[rpc_id] = info
end

function IMsgCommonTemplate:HandleRPCRequest(id, rpc_id, factory)
	local callback, return_id = FindMsgRpcCallback(id)
	if callback == nil then
		self:SendRpcError(rpc_id, "没有注册消息RPC回调函数")
		Log("MsgSystem.HandleMessage can't find callback by id:" .. id)
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local error, return_body = Lua.TCall(callback, self, msg)
	if error ~= nil then
		self:SendRpcError(rpc_id, error)
		Log("MsgSystem.HandleMessage callback invoke failed! by id:" .. id .. ", reason:" .. error)
		return
	end
	if return_body == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage callback have not return! by id:" .. id)
		Log("MsgSystem.HandleMessage callback have not return! by id:" .. id)
		return
	end
	self:Send(return_id, return_body, -rpc_id)
end
IMsgCommonTemplate.HandleRPCRequest = Lua.CoWrap(IMsgCommonTemplate.HandleRPCRequest)

function IMsgCommonTemplate:ClearRPC(reason)
	local tmp = {}
	for rpc_id, info in ___pairs(self._id_map_rpc) do
		self._id_creator:ReleaseID(rpc_id)
		tmp[rpc_id] = info
	end
	self._id_map_rpc = {}
	for rpc_id, info in ___pairs(tmp) do
		local result, error = Coroutine.Resume(info.thread, reason, nil)
		if result ~= true then
			Error(error)
		end
	end
end

function IMsgCommonTemplate:Close(reason)
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

