{
if (typeof ALittle === "undefined") ALittle = {};

ALittle.RegStruct(-1864322361, "ALittle.LoginSessionInfo", {
name : "ALittle.LoginSessionInfo", ns_name : "ALittle", rl_name : "LoginSessionInfo", hash_code : -1864322361,
name_list : ["account_id","session","timer"],
type_list : ["int","string","int"],
option_map : {}
})
ALittle.RegStruct(-1922773679, "ALittle.DATA2GS_QSaveSession", {
name : "ALittle.DATA2GS_QSaveSession", ns_name : "ALittle", rl_name : "DATA2GS_QSaveSession", hash_code : -1922773679,
name_list : ["account_id","session"],
type_list : ["int","string"],
option_map : {}
})
ALittle.RegStruct(-963859571, "ALittle.GS2DATA_ASaveSession", {
name : "ALittle.GS2DATA_ASaveSession", ns_name : "ALittle", rl_name : "GS2DATA_ASaveSession", hash_code : -963859571,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.GameLoginManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._session_map = new Map();
	},
	Setup : function() {
	},
	Shutdown : function() {
		for (let [account_id, info] of this._session_map) {
			if (info === undefined) continue;
			if (info.timer !== undefined) {
				A_LoopSystem.RemoveTimer(info.timer);
			}
		}
		this._session_map = new Map();
	},
	ChcekSession : function(account_id, session) {
		let info = this._session_map.get(account_id);
		if (info === undefined) {
			return false;
		}
		return info.session === session;
	},
	RemoveSession : function(account_id) {
		let info = this._session_map.get(account_id);
		if (info === undefined) {
			return;
		}
		if (info.timer !== undefined) {
			A_LoopSystem.RemoveTimer(info.timer);
		}
		this._session_map.delete(account_id);
	},
	HandleQSaveSession : function(msg) {
		let info = this._session_map.get(msg.account_id);
		if (info !== undefined && info.timer !== undefined) {
			A_LoopSystem.RemoveTimer(info.timer);
		}
		info = {};
		info.account_id = msg.account_id;
		info.session = msg.session;
		info.timer = A_LoopSystem.AddTimer(30 * 1000, this.HandleSessionTimeout.bind(this, msg.account_id));
		this._session_map.set(msg.account_id, info);
	},
	HandleSessionTimeout : function(account_id) {
		this._session_map.delete(account_id);
	},
}, "ALittle.GameLoginManager");

ALittle.g_GameLoginManager = ALittle.NewObject(ALittle.GameLoginManager);
ALittle.HandleQSaveSession = function(client, msg) {
	return new Promise(function(___COROUTINE, ___) {
		ALittle.g_GameLoginManager.HandleQSaveSession(msg);
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1922773679, HandleQSaveSession, -963859571)
}