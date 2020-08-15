-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(361433949, "ALittle.MsgRPCInfo", {
name = "ALittle.MsgRPCInfo", ns_name = "ALittle", rl_name = "MsgRPCInfo", hash_code = 361433949,
name_list = {"rpc_id","thread"},
type_list = {"int","ALittle.Thread"},
option_map = {}
})

ALittle.IMsgCommonNative = Lua.Class(nil, "ALittle.IMsgCommonNative")

function ALittle.IMsgCommonNative:SetID(id)
end

function ALittle.IMsgCommonNative:GetID()
	return 0
end

function ALittle.IMsgCommonNative:Connect(ip, port)
end

function ALittle.IMsgCommonNative:IsConnected()
	return false
end

function ALittle.IMsgCommonNative:SendFactory(factory)
end

function ALittle.IMsgCommonNative:Close()
end

assert(ALittle.IMsgCommon, " extends class:ALittle.IMsgCommon is nil")
ALittle.IMsgCommonTemplate = Lua.Class(ALittle.IMsgCommon, "ALittle.IMsgCommonTemplate")

function ALittle.IMsgCommonTemplate:Ctor()
	___rawset(self, "_last_recv_time", 0)
	___rawset(self, "_id_creator", ALittle.SafeIDCreator())
	___rawset(self, "_id_map_rpc", {})
end

function ALittle.IMsgCommonTemplate:GetID()
	return self._interface:GetID()
end

function ALittle.IMsgCommonTemplate:Connect(ip, port)
	local ___COROUTINE = coroutine.running()
	return "not impl"
end

function ALittle.IMsgCommonTemplate:IsConnected()
	return self._interface:IsConnected()
end

function ALittle.IMsgCommonTemplate:MessageRead(factory, msg_id)
	local invoke = ALittle.CreateProtocolInvokeInfo(msg_id)
	local object, size = ALittle.PS_ReadMessageForReceive(factory, invoke, nil, factory:GetDataSize())
	return object
end

function ALittle.IMsgCommonTemplate:MessageWrite(msg_id, msg_body)
	local invoke = ALittle.CreateProtocolInvokeInfo(msg_id)
	self._write_factory:ResetOffset()
	ALittle.PS_WriteMessageForSend(self._write_factory, invoke, nil, msg_body)
	self._write_factory:SetID(msg_id)
end

function ALittle.IMsgCommonTemplate:HandleMessage(id, rpc_id, factory)
	if id == 0 then
		self._last_recv_time = ALittle.Time_GetCurTime()
		return
	end
	if rpc_id == 0 then
		local callback = ALittle.FindMsgCallback(id)
		if callback == nil then
			local name = "unknow"
			local rflt = ALittle.FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" .. id .. ", name:" .. name)
			return
		end
		local msg = self:MessageRead(factory, id)
		if msg == nil then
			local name = "unknow"
			local rflt = ALittle.FindStructById(id)
			if rflt ~= nil then
				name = rflt.name
			end
			ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id .. ", name:" .. name)
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
		ALittle.Log("MsgSystem.HandleMessage can't find rpc info by id:" .. id)
		return
	end
	self._id_map_rpc[rpc_id] = nil
	if id == 1 then
		local result, reason = ALittle.Coroutine.Resume(info.thread, factory:ReadString(), nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		local result, reason = ALittle.Coroutine.Resume(info.thread, "MsgSystem.HandleMessage MessageRead failed by id:" .. id, nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local result, reason = ALittle.Coroutine.Resume(info.thread, nil, msg)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.IMsgCommonTemplate:SendMsg(T, msg)
	local info = T
	self:Send(info.hash_code, msg, 0)
end

function ALittle.IMsgCommonTemplate:Send(msg_id, msg_body, rpc_id)
	if not self:IsConnected() then
		return
	end
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
end

function ALittle.IMsgCommonTemplate:SendRpcError(rpc_id, reason)
	if not self:IsConnected() then
		return
	end
	self._write_factory:ResetOffset()
	self._write_factory:SetID(1)
	self._write_factory:SetRpcID(-rpc_id)
	self._write_factory:WriteString(reason)
	self._interface:SendFactory(self._write_factory)
end

function ALittle.IMsgCommonTemplate:SendRPC(thread, msg_id, msg_body)
	local rpc_id = self._id_creator:CreateID()
	self._write_factory:SetRpcID(rpc_id)
	self:MessageWrite(msg_id, msg_body)
	self._interface:SendFactory(self._write_factory)
	local info = {}
	info.thread = thread
	info.rpc_id = rpc_id
	self._id_map_rpc[rpc_id] = info
end

function ALittle.IMsgCommonTemplate:HandleRPCRequest(id, rpc_id, factory)
	local callback, return_id = ALittle.FindMsgRpcCallback(id)
	if callback == nil then
		self:SendRpcError(rpc_id, "没有注册消息RPC回调函数")
		ALittle.Log("MsgSystem.HandleMessage can't find callback by id:" .. id)
		return
	end
	local msg = self:MessageRead(factory, id)
	if msg == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		ALittle.Log("MsgSystem.HandleMessage MessageRead failed by id:" .. id)
		return
	end
	local error, return_body = Lua.TCall(callback, self, msg)
	if error ~= nil then
		self:SendRpcError(rpc_id, error)
		ALittle.Log("MsgSystem.HandleMessage callback invoke failed! by id:" .. id .. ", reason:" .. error)
		return
	end
	if return_body == nil then
		self:SendRpcError(rpc_id, "MsgSystem.HandleMessage callback have not return! by id:" .. id)
		ALittle.Log("MsgSystem.HandleMessage callback have not return! by id:" .. id)
		return
	end
	self:Send(return_id, return_body, -rpc_id)
end
ALittle.IMsgCommonTemplate.HandleRPCRequest = Lua.CoWrap(ALittle.IMsgCommonTemplate.HandleRPCRequest)

function ALittle.IMsgCommonTemplate:ClearRPC(reason)
	local tmp = {}
	for rpc_id, info in ___pairs(self._id_map_rpc) do
		self._id_creator:ReleaseID(rpc_id)
		tmp[rpc_id] = info
	end
	self._id_map_rpc = {}
	for rpc_id, info in ___pairs(tmp) do
		local result, error = ALittle.Coroutine.Resume(info.thread, reason, nil)
		if result ~= true then
			ALittle.Error(error)
		end
	end
end

function ALittle.IMsgCommonTemplate:Close(reason)
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

end