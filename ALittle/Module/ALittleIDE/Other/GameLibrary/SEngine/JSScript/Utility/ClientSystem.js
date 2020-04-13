{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1221484301, "ALittle.ClientConnectEvent", {
name : "ALittle.ClientConnectEvent", ns_name : "ALittle", rl_name : "ClientConnectEvent", hash_code : -1221484301,
name_list : ["target","msg_receiver"],
type_list : ["ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative,lua.__CPPAPIMessageWriteFactory>"],
option_map : {}
})
ALittle.RegStruct(-245025090, "ALittle.ClientDisconnectEvent", {
name : "ALittle.ClientDisconnectEvent", ns_name : "ALittle", rl_name : "ClientDisconnectEvent", hash_code : -245025090,
name_list : ["target","msg_receiver"],
type_list : ["ALittle.EventDispatcher","ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative,lua.__CPPAPIMessageWriteFactory>"],
option_map : {}
})

if (ALittle.IMsgCommonNative === undefined) throw new Error(" extends class:ALittle.IMsgCommonNative is undefined");
ALittle.MsgReceiverNative = JavaScript.Class(ALittle.IMsgCommonNative, {
	SetID : function(id) {
		this._client_id = id;
	},
	GetID : function() {
		return this._client_id;
	},
	SendFactory : function(factory) {
		__CPPAPI_ServerSchedule.ClientSend(this._client_id, factory);
	},
	Close : function() {
		__CPPAPI_ServerSchedule.ClientClose(this._client_id);
		A_ClientSystem.RemoveMsgServer(this._client_id);
	},
}, "ALittle.MsgReceiverNative");

MsgReceiver = JavaScript.Template(ALittle.MsgReceiverTemplate, "ALittle.MsgReceiverTemplate<ALittle.MsgReceiverNative, lua.__CPPAPIMessageWriteFactory>", ALittle.MsgReceiverNative, lua.__CPPAPIMessageWriteFactory);
if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittle.ClientSystem = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
		this._client_map = new Map();
	},
	RemoveMsgServer : function(client_id) {
		this._client_map.delete(client_id);
	},
	HandleClientConnect : function(client_id, remote_ip, remote_port) {
		let client = ALittle.NewObject(ALittle.MsgReceiver, client_id, remote_ip, remote_port);
		this._client_map.set(client_id, client);
		client.HandleConnected();
		let event = {};
		event.target = this;
		event.msg_receiver = client;
		this.DispatchEvent(___all_struct.get(-1221484301), event);
	},
	HandleClientDisconnect : function(client_id) {
		let client = this._client_map.get(client_id);
		if (client === undefined) {
			return;
		}
		this._client_map.delete(client_id);
		client.HandleDisconnected();
		let event = {};
		event.target = this;
		event.msg_receiver = client;
		this.DispatchEvent(___all_struct.get(-245025090), event);
	},
	HandleClientMessage : function(client_id, id, rpc_id, factory) {
		let client = this._client_map.get(client_id);
		if (client === undefined) {
			return;
		}
		client.HandleMessage(id, rpc_id, factory);
	},
}, "ALittle.ClientSystem");

window.A_ClientSystem = ALittle.NewObject(ALittle.ClientSystem);
}