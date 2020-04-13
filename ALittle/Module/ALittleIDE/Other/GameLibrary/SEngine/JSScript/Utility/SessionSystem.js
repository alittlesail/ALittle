{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(888437463, "ALittle.SessionConnectEvent", {
name : "ALittle.SessionConnectEvent", ns_name : "ALittle", rl_name : "SessionConnectEvent", hash_code : 888437463,
name_list : ["target","connect_key","route_type","route_num","session"],
type_list : ["ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,lua.__CPPAPIMessageWriteFactory>"],
option_map : {}
})
ALittle.RegStruct(-36908822, "ALittle.SessionDisconnectEvent", {
name : "ALittle.SessionDisconnectEvent", ns_name : "ALittle", rl_name : "SessionDisconnectEvent", hash_code : -36908822,
name_list : ["target","connect_key","route_type","route_num","session"],
type_list : ["ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,lua.__CPPAPIMessageWriteFactory>"],
option_map : {}
})
ALittle.RegStruct(-1417161474, "ALittle.ConnectSessionInfo", {
name : "ALittle.ConnectSessionInfo", ns_name : "ALittle", rl_name : "ConnectSessionInfo", hash_code : -1417161474,
name_list : ["route_type","route_num","connect_key","is_connecting"],
type_list : ["int","int","int","bool"],
option_map : {}
})

if (ALittle.IMsgCommonNative === undefined) throw new Error(" extends class:ALittle.IMsgCommonNative is undefined");
ALittle.MsgSessionNative = JavaScript.Class(ALittle.IMsgCommonNative, {
	SetID : function(id) {
		this._connect_key = id;
	},
	GetID : function() {
		return this._connect_key;
	},
	SendFactory : function(factory) {
		__CPPAPI_ServerSchedule.SessionSend(this._connect_key, factory);
	},
	Close : function() {
		__CPPAPI_ServerSchedule.SessionClose(this._connect_key);
		A_SessionSystem.RemoveSessionServer(this._connect_key);
	},
}, "ALittle.MsgSessionNative");

MsgSession = JavaScript.Template(ALittle.MsgSessionTemplate, "ALittle.MsgSessionTemplate<ALittle.MsgSessionNative, lua.__CPPAPIMessageWriteFactory>", ALittle.MsgSessionNative, lua.__CPPAPIMessageWriteFactory);
if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittle.SessionSystem = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
		this._session_map = new Map();
		this._connect_map = {};
		this._invoke_map = {};
	},
	GetSessionMap : function() {
		return this._session_map;
	},
	SendMsgToAll : function(T, msg) {
		for (let [connect_key, session] of this._session_map) {
			if (session === undefined) continue;
			session.SendMsg(T, msg);
		}
	},
	RemoveSessionServer : function(connect_key) {
		this._session_map.delete(connect_key);
	},
	AddConnectSession : function(route_type, route_num) {
		let key = route_type + "_" + route_num;
		let info = this._connect_map[key];
		if (info !== undefined) {
			return;
		}
		info = {};
		info.route_type = route_type;
		info.route_num = route_num;
		info.is_connecting = true;
		this._connect_map[key] = info;
		__CPPAPI_ServerSchedule.ConnectSession(route_type, route_num);
	},
	ConnectSession : function(route_type, route_num) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			let key = route_type + "_" + route_num;
			let info = this._connect_map[key];
			if (info !== undefined && !info.is_connecting) {
				let connect_key = __CPPAPI_ServerSchedule.CalcConnectKey(__CPPAPI_ServerSchedule.GetRouteType(), __CPPAPI_ServerSchedule.GetRouteNum(), route_type, route_num);
				let connect = this._session_map.get(connect_key);
				if (connect !== undefined) {
					___COROUTINE([undefined, connect]); return;
				}
				connect_key = __CPPAPI_ServerSchedule.CalcConnectKey(route_type, route_num, __CPPAPI_ServerSchedule.GetRouteType(), __CPPAPI_ServerSchedule.GetRouteNum());
				connect = this._session_map.get(connect_key);
				if (connect !== undefined) {
					___COROUTINE([undefined, connect]); return;
				}
				___COROUTINE(["连接居然不存在", undefined]); return;
			}
			if (info === undefined) {
				this.AddConnectSession(route_type, route_num);
			}
			let list = this._invoke_map[key];
			if (list === undefined) {
				list = [];
				this._invoke_map[key] = list;
			}
			ALittle.List_Push(list, ___COROUTINE);
			return;
			___COROUTINE();
		}).bind(this));
	},
	HandleSessionConnect : function(connect_key, route_type, route_num) {
		let session = ALittle.NewObject(ALittle.MsgSession, connect_key, route_type, route_num);
		this._session_map.set(connect_key, session);
		session.HandleConnected();
		let event = {};
		event.target = this;
		event.connect_key = connect_key;
		event.route_type = route_type;
		event.route_num = route_num;
		event.session = session;
		this.DispatchEvent(___all_struct.get(888437463), event);
	},
	HandleSessionDisconnect : function(connect_key, route_type, route_num) {
		let session = this._session_map.get(connect_key);
		if (session !== undefined) {
			this._session_map.delete(connect_key);
			session.HandleDisconnected();
		}
		let event = {};
		event.target = this;
		event.connect_key = connect_key;
		event.route_type = route_type;
		event.route_num = route_num;
		event.session = session;
		this.DispatchEvent(___all_struct.get(888437463), event);
		let key = route_type + "_" + route_num;
		let info = this._connect_map[key];
		if (info !== undefined && info.connect_key === connect_key) {
			info.is_connecting = true;
			A_LoopSystem.AddTimer(1000, this.ConnectSessionImpl.bind(this, info), undefined, undefined);
		}
	},
	HandleConnectSessionFailed : function(route_type, route_num, reason) {
		let key = route_type + "_" + route_num;
		let list = this._invoke_map[key];
		if (list !== undefined) {
			delete this._invoke_map[key];
			let ___OBJECT_1 = list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let thread = ___OBJECT_1[index - 1];
				if (thread === undefined) break;
				let [result, error] = lua.coroutine.resume(thread, reason);
				if (result !== true) {
					ALittle.Error(error);
				}
			}
		}
		let info = this._connect_map[key];
		if (info !== undefined) {
			info.is_connecting = true;
			A_LoopSystem.AddTimer(1000, this.ConnectSessionImpl.bind(this, info), undefined, undefined);
		}
	},
	HandleConnectSessionSucceed : function(connect_key, route_type, route_num) {
		let key = route_type + "_" + route_num;
		let info = this._connect_map[key];
		if (info !== undefined) {
			info.connect_key = connect_key;
			info.is_connecting = false;
		}
		let list = this._invoke_map[key];
		if (list !== undefined) {
			let session = this._session_map.get(connect_key);
			let error = undefined;
			if (session === undefined) {
				error = "连接居然不存在";
			}
			delete this._invoke_map[key];
			let ___OBJECT_2 = list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let thread = ___OBJECT_2[index - 1];
				if (thread === undefined) break;
				let [result, reason] = lua.coroutine.resume(thread, error, session);
				if (result !== true) {
					ALittle.Error(reason);
				}
			}
		}
	},
	HandleSessionMessage : function(connect_key, id, rpc_id, factory) {
		let session = this._session_map.get(connect_key);
		if (session === undefined) {
			return;
		}
		session.HandleMessage(id, rpc_id, factory);
	},
	ConnectSessionImpl : function(info) {
		__CPPAPI_ServerSchedule.ConnectSession(info.route_type, info.route_num);
	},
}, "ALittle.SessionSystem");

window.A_SessionSystem = ALittle.NewObject(ALittle.SessionSystem);
}