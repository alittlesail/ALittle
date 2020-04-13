
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = GetAllStruct()

RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(-1221484301, "ALittle.ClientConnectEvent", {
name = "ALittle.ClientConnectEvent", ns_name = "ALittle", rl_name = "ClientConnectEvent", hash_code = -1221484301,
name_list = {"target","msg_receiver"},
type_list = {"ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative>"},
option_map = {}
})
RegStruct(-245025090, "ALittle.ClientDisconnectEvent", {
name = "ALittle.ClientDisconnectEvent", ns_name = "ALittle", rl_name = "ClientDisconnectEvent", hash_code = -245025090,
name_list = {"target","msg_receiver"},
type_list = {"ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative>"},
option_map = {}
})

assert(IMsgCommonNative, " extends class:IMsgCommonNative is nil")
MsgReceiverNative = Class(IMsgCommonNative, "ALittle.MsgReceiverNative")

function MsgReceiverNative:SetID(id)
	self._client_id = id
end

function MsgReceiverNative:GetID()
	return self._client_id
end

function MsgReceiverNative:SendFactory(factory)
	__CPPAPI_ServerSchedule:ClientSend(self._client_id, factory)
end

function MsgReceiverNative:Close()
	__CPPAPI_ServerSchedule:ClientClose(self._client_id)
	A_ClientSystem:RemoveMsgServer(self._client_id)
end

MsgReceiver = Template(MsgReceiverTemplate, "ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative>", MsgReceiverNative);
assert(EventDispatcher, " extends class:EventDispatcher is nil")
ClientSystem = Class(EventDispatcher, "ALittle.ClientSystem")

function ClientSystem:Ctor()
	___rawset(self, "_client_map", {})
end

function ClientSystem:RemoveMsgServer(client_id)
	self._client_map[client_id] = nil
end

function ClientSystem:HandleClientConnect(client_id, remote_ip, remote_port)
	local client = MsgReceiver(client_id, remote_ip, remote_port)
	self._client_map[client_id] = client
	client:HandleConnected()
	local event = {}
	event.target = self
	event.msg_receiver = client
	self:DispatchEvent(___all_struct[-1221484301], event)
end

function ClientSystem:HandleClientDisconnect(client_id)
	local client = self._client_map[client_id]
	if client == nil then
		return
	end
	self._client_map[client_id] = nil
	client:HandleDisconnected()
	local event = {}
	event.target = self
	event.msg_receiver = client
	self:DispatchEvent(___all_struct[-245025090], event)
end

function ClientSystem:HandleClientMessage(client_id, id, rpc_id, factory)
	local client = self._client_map[client_id]
	if client == nil then
		return
	end
	client:HandleMessage(id, rpc_id, factory)
end

_G.A_ClientSystem = ClientSystem()
