{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1860871079, "ALittle.GameLeaseInfo", {
name : "ALittle.GameLeaseInfo", ns_name : "ALittle", rl_name : "GameLeaseInfo", hash_code : 1860871079,
name_list : ["account_id","session","timer"],
type_list : ["int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,lua.__CPPAPIMessageWriteFactory>","int"],
option_map : {}
})
ALittle.RegStruct(-1970485469, "DataServer.GS2DATA_NReleaseLease", {
name : "DataServer.GS2DATA_NReleaseLease", ns_name : "DataServer", rl_name : "GS2DATA_NReleaseLease", hash_code : -1970485469,
name_list : ["account_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1057357327, "DataServer.GS2DATA_QRenewLease", {
name : "DataServer.GS2DATA_QRenewLease", ns_name : "DataServer", rl_name : "GS2DATA_QRenewLease", hash_code : -1057357327,
name_list : ["account_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-276606114, "DataServer.DATA2GS_ARenewLease", {
name : "DataServer.DATA2GS_ARenewLease", ns_name : "DataServer", rl_name : "DATA2GS_ARenewLease", hash_code : -276606114,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(370639724, "ALittle.DATA2GS_NNewLease", {
name : "ALittle.DATA2GS_NNewLease", ns_name : "ALittle", rl_name : "DATA2GS_NNewLease", hash_code : 370639724,
name_list : ["account_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1627449907, "ALittle.DATA2GS_QEmpty", {
name : "ALittle.DATA2GS_QEmpty", ns_name : "ALittle", rl_name : "DATA2GS_QEmpty", hash_code : -1627449907,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(726375194, "ALittle.GS2DATA_AEmpty", {
name : "ALittle.GS2DATA_AEmpty", ns_name : "ALittle", rl_name : "GS2DATA_AEmpty", hash_code : 726375194,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.GS_LEASE_INTERVAL = 20 * 1000;
ALittle.GameLeaseManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._lease_map = new Map();
	},
	Setup : function() {
	},
	Shutdown : function() {
		for (let [account_id, info] of this._lease_map) {
			if (info === undefined) continue;
			if (info.timer !== undefined) {
				A_LoopSystem.RemoveTimer(info.timer);
			}
		}
		this._lease_map = new Map();
	},
	GetLease : function(account_id) {
		return this._lease_map.get(account_id);
	},
	NewLease : function(session, msg) {
		let info = this._lease_map.get(msg.account_id);
		if (info === undefined) {
			info = {};
			this._lease_map.set(msg.account_id, info);
		}
		info.session = session;
		info.account_id = msg.account_id;
		if (info.timer !== undefined) {
			A_LoopSystem.RemoveTimer(info.timer);
		}
		info.timer = A_LoopSystem.AddTimer(ALittle.GS_LEASE_INTERVAL, this.HandleRenewLease.bind(this, msg.account_id));
	},
	ReleaseLease : function(account_id) {
		let info = this._lease_map.get(account_id);
		if (info === undefined) {
			return;
		}
		if (info.session !== undefined) {
			let param = {};
			param.account_id = account_id;
			info.session.SendMsg(___all_struct.get(-1970485469), param);
		}
		this._lease_map.delete(account_id);
	},
	HandleRenewLease : async function(account_id) {
		let info = this._lease_map.get(account_id);
		if (info === undefined) {
			return;
		}
		if (info.session === undefined) {
			A_GameAccountManager.HandleLeaseTimeout(account_id);
			this._lease_map.delete(account_id);
			return;
		}
		info.timer = undefined;
		let begin_time = lua.os.time();
		let param = {};
		param.account_id = account_id;
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(-1057357327, info.session, param);
		info = this._lease_map.get(account_id);
		if (info === undefined) {
			return;
		}
		if (info.timer !== undefined) {
			return;
		}
		if (error !== undefined || lua.os.time() - begin_time >= 5) {
			A_GameAccountManager.HandleLeaseTimeout(account_id);
			this._lease_map.delete(account_id);
			return;
		}
		info.timer = A_LoopSystem.AddTimer(ALittle.GS_LEASE_INTERVAL, this.HandleRenewLease.bind(this, account_id));
	},
}, "ALittle.GameLeaseManager");

ALittle.g_GameLeaseManager = ALittle.NewObject(ALittle.GameLeaseManager);
ALittle.HandleNNewLease = function(client, msg) {
	ALittle.g_GameLeaseManager.NewLease(client, msg);
}

ALittle.RegMsgCallback(370639724, HandleNNewLease)
ALittle.HandleQEmpty = function(client, msg) {
	return new Promise(function(___COROUTINE, ___) {
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1627449907, HandleQEmpty, 726375194)
}