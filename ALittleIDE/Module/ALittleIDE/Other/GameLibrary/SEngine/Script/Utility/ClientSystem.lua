-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1221484301, "ALittle.ClientConnectEvent", {
name = "ALittle.ClientConnectEvent", ns_name = "ALittle", rl_name = "ClientConnectEvent", hash_code = -1221484301,
name_list = {"target","msg_receiver"},
type_list = {"ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})
ALittle.RegStruct(-245025090, "ALittle.ClientDisconnectEvent", {
name = "ALittle.ClientDisconnectEvent", ns_name = "ALittle", rl_name = "ClientDisconnectEvent", hash_code = -245025090,
name_list = {"target","msg_receiver"},
type_list = {"ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})

assert(ALittle.IMsgCommonNative, " extends class:ALittle.IMsgCommonNative is nil")
ALittle.MsgReceiverNative = Lua.Class(ALittle.IMsgCommonNative, "ALittle.MsgReceiverNative")

function ALittle.MsgReceiverNative:SetID(id)
	self._client_id = id
end

function ALittle.MsgReceiverNative:GetID()
	return self._client_id
end

function ALittle.MsgReceiverNative:SendFactory(factory)
	__CPPAPI_ServerSchedule:ClientSend(self._client_id, factory)
end

function ALittle.MsgReceiverNative:Close()
	__CPPAPI_ServerSchedule:ClientClose(self._client_id)
	A_ClientSystem:RemoveMsgServer(self._client_id)
end

ALittle.MsgReceiver = Lua.Template(ALittle.MsgReceiverTemplate, "ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative, carp.CarpMessageWriteFactory>", ALittle.MsgReceiverNative, carp.CarpMessageWriteFactory);
assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
ALittle.ClientSystem = Lua.Class(ALittle.EventDispatcher, "ALittle.ClientSystem")

function ALittle.ClientSystem:Ctor()
	___rawset(self, "_client_map", {})
end

function ALittle.ClientSystem:RemoveMsgServer(client_id)
	self._client_map[client_id] = nil
end

function ALittle.ClientSystem:HandleClientConnect(client_id, remote_ip, remote_port)
	local client = ALittle.MsgReceiver(client_id, remote_ip, remote_port)
	self._client_map[client_id] = client
	client:HandleConnected()
	local event = {}
	event.target = self
	event.msg_receiver = client
	self:DispatchEvent(___all_struct[-1221484301], event)
end

function ALittle.ClientSystem:HandleClientDisconnect(client_id)
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

function ALittle.ClientSystem:HandleClientMessage(client_id, id, rpc_id, factory)
	local client = self._client_map[client_id]
	if client == nil then
		return
	end
	client:HandleMessage(id, rpc_id, factory)
end

_G.A_ClientSystem = ALittle.ClientSystem()
end