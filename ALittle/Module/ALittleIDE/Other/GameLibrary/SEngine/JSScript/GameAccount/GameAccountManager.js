{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1010453448, "DataServer.GS2DATA_NRegStruct", {
name : "DataServer.GS2DATA_NRegStruct", ns_name : "DataServer", rl_name : "GS2DATA_NRegStruct", hash_code : -1010453448,
name_list : ["rflt_list","table_map"],
type_list : ["List<ALittle.StructInfo>","Map<int,bool>"],
option_map : {}
})
ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name : "ALittle.StructInfo", ns_name : "ALittle", rl_name : "StructInfo", hash_code : 1847150134,
name_list : ["name","ns_name","rl_name","hash_code","name_list","type_list","option_map"],
type_list : ["string","string","string","int","List<string>","List<string>","Map<string,string>"],
option_map : {}
})
ALittle.RegStruct(-660832923, "ALittle.GS2C_NForceLogout", {
name : "ALittle.GS2C_NForceLogout", ns_name : "ALittle", rl_name : "GS2C_NForceLogout", hash_code : -660832923,
name_list : ["reason"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(-1162432155, "ALittle.C2GS_QLogin", {
name : "ALittle.C2GS_QLogin", ns_name : "ALittle", rl_name : "C2GS_QLogin", hash_code : -1162432155,
name_list : ["account_id","session","device"],
type_list : ["int","string","string"],
option_map : {}
})
ALittle.RegStruct(1569725693, "ALittle.GS2C_ALogin", {
name : "ALittle.GS2C_ALogin", ns_name : "ALittle", rl_name : "GS2C_ALogin", hash_code : 1569725693,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-1836835016, "ALittle.GS2C_NDataReady", {
name : "ALittle.GS2C_NDataReady", ns_name : "ALittle", rl_name : "GS2C_NDataReady", hash_code : -1836835016,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-2092316375, "ALittle.SS2GS_QCheckSessionCode", {
name : "ALittle.SS2GS_QCheckSessionCode", ns_name : "ALittle", rl_name : "SS2GS_QCheckSessionCode", hash_code : -2092316375,
name_list : ["account_id","session_code"],
type_list : ["int","string"],
option_map : {}
})
ALittle.RegStruct(-1766835499, "ALittle.GS2SS_ACheckSessionCode", {
name : "ALittle.GS2SS_ACheckSessionCode", ns_name : "ALittle", rl_name : "GS2SS_ACheckSessionCode", hash_code : -1766835499,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.GameAccountManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._account_map = new Map();
		this._account_count = 0;
		this._client_map = new Map();
		this._reg_struct_map = new Map();
	},
	Setup : function(create_callback) {
		ALittle.g_GameLeaseManager.Setup();
		ALittle.g_GameLoginManager.Setup();
		this._create_callback = create_callback;
		A_ClientSystem.AddEventListener(___all_struct.get(-245025090), this, this.HandleClientDisconnected);
		A_SessionSystem.AddEventListener(___all_struct.get(-36908822), this, this.HandleAnySessionDisconnected);
		this._update_route = ALittle.NewObject(ALittle.GatewayUpdateRoute, __CPPAPI_ServerSchedule.GetClientServerYunIp(), __CPPAPI_ServerSchedule.GetClientServerIp(), __CPPAPI_ServerSchedule.GetClientServerPort(), __CPPAPI_ServerSchedule.GetHttpServerYunIp(), __CPPAPI_ServerSchedule.GetHttpServerIp(), __CPPAPI_ServerSchedule.GetHttpServerPort(), this._account_count);
	},
	Shutdown : function() {
		ALittle.g_GameLoginManager.Shutdown();
		ALittle.g_GameLeaseManager.Shutdown();
	},
	GetAccountByClient : function(client) {
		return this._client_map.get(client);
	},
	GetAccountById : function(account_id) {
		return this._account_map.get(account_id);
	},
	CreateAccount : function(account_id) {
		let account = this._account_map.get(account_id);
		if (account === undefined) {
			if (this._create_callback !== undefined) {
				account = this._create_callback(account_id);
			}
			if (account === undefined) {
				account = ALittle.NewObject(ALittle.GameAccount, account_id);
			}
			this._account_map.set(account_id, account);
			++ this._account_count;
			this._update_route.UpdateRouteWeight(this._account_count);
		}
		return account;
	},
	DeleteAccount : function(account) {
		let cur_account = this._account_map.get(account.GetId());
		if (cur_account === account) {
			account.Release();
			-- this._account_count;
			this._account_map.delete(account.GetId());
			this._update_route.UpdateRouteWeight(this._account_count);
		}
	},
	IsSendModuleReflect : function(session) {
		return this._reg_struct_map.get(session) === true;
	},
	SendModuleReflect : async function(session, rflt_list, table_map) {
		if (this._reg_struct_map.get(session)) {
			return;
		}
		this._reg_struct_map.set(session, true);
		let param = {};
		param.rflt_list = rflt_list;
		param.table_map = table_map;
		session.SendMsg(___all_struct.get(-1010453448), param);
	},
	SetAccountClient : function(account, client) {
		let old_client = account.GetClient();
		if (old_client !== undefined) {
			this._client_map.delete(old_client);
		}
		account.SetClient(client);
		if (client !== undefined) {
			this._client_map.set(client, account);
		}
	},
	HandleClientDisconnected : function(event) {
		let account = this._client_map.get(event.msg_receiver);
		if (account === undefined) {
			return;
		}
		let status = account.GetStatus();
		if (status === ALittle.GameAccountStatus.CREATE) {
			this.SetAccountClient(account, undefined);
			return;
		}
		if (status === ALittle.GameAccountStatus.LOADING) {
			this.SetAccountClient(account, undefined);
			return;
		}
		if (status === ALittle.GameAccountStatus.CACHE) {
			account.Backup();
			this.SetAccountClient(account, undefined);
			return;
		}
		if (status === ALittle.GameAccountStatus.ONLINE) {
			account.LogoutAction();
			account.SetStatus(ALittle.GameAccountStatus.CACHE);
			account.StartCacheTimer();
			this.SetAccountClient(account, undefined);
			return;
		}
		this.SetAccountClient(account, undefined);
	},
	HandleAnySessionDisconnected : function(event) {
		if (event.route_type !== ALittle.RouteType.RT_DATA) {
			return;
		}
		this._reg_struct_map.delete(event.session);
	},
	HandleLeaseTimeout : function(account_id) {
		let account = this._account_map.get(account_id);
		if (account === undefined) {
			return;
		}
		let status = account.GetStatus();
		if (status === ALittle.GameAccountStatus.CREATE) {
			this.SetAccountClient(account, undefined);
			this.DeleteAccount(account);
			return;
		}
		if (status === ALittle.GameAccountStatus.LOADING) {
			this.SetAccountClient(account, undefined);
			this.DeleteAccount(account);
			return;
		}
		if (status === ALittle.GameAccountStatus.CACHE) {
			account.Backup();
			this.SetAccountClient(account, undefined);
			this.DeleteAccount(account);
			return;
		}
		if (status === ALittle.GameAccountStatus.ONLINE) {
			account.LogoutAction();
			let param = {};
			param.reason = "租约超时";
			account.SendMsg(___all_struct.get(-660832923), param);
			this.SetAccountClient(account, undefined);
			this.DeleteAccount(account);
			return;
		}
		this.DeleteAccount(account);
	},
}, "ALittle.GameAccountManager");

window.A_GameAccountManager = ALittle.NewObject(ALittle.GameAccountManager);
ALittle.HandleQLogin = function(client, msg) {
	return new Promise(function(___COROUTINE, ___) {
		let lease_info = ALittle.g_GameLeaseManager.GetLease(msg.account_id);
		JavaScript.Assert(lease_info, "没有租约信息:" + msg.account_id);
		JavaScript.Assert(ALittle.g_GameLoginManager.ChcekSession(msg.account_id, msg.session), "会话ID错误");
		ALittle.g_GameLoginManager.RemoveSession(msg.account_id);
		let account = A_GameAccountManager.CreateAccount(msg.account_id);
		let status = account.GetStatus();
		if (status === ALittle.GameAccountStatus.CREATE) {
			account.SetStatus(ALittle.GameAccountStatus.LOADING);
			A_GameAccountManager.SetAccountClient(account, client);
			account.StartLoading(lease_info.session);
			___COROUTINE({}); return;
		}
		if (status === ALittle.GameAccountStatus.LOADING) {
			let param = {};
			param.reason = "您的账号在另一个地方登录";
			account.SendMsg(___all_struct.get(-660832923), param);
			A_GameAccountManager.SetAccountClient(account, client);
			___COROUTINE({}); return;
		}
		if (status === ALittle.GameAccountStatus.CACHE) {
			let param = {};
			param.reason = "您的账号在另一个地方登录";
			account.SendMsg(___all_struct.get(-660832923), param);
			A_GameAccountManager.SetAccountClient(account, client);
			account.SetStatus(ALittle.GameAccountStatus.ONLINE);
			account.StopCacheTimer();
			account.LoginAction();
			___COROUTINE({}); return;
		}
		if (status === ALittle.GameAccountStatus.ONLINE) {
			account.LogoutAction();
			let param = {};
			param.reason = "您的账号在另一个地方登录";
			account.SendMsg(___all_struct.get(-660832923), param);
			A_GameAccountManager.SetAccountClient(account, client);
			account.LoginAction();
			___COROUTINE({}); return;
		}
		throw new Error("未知的账号状态");
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1162432155, HandleQLogin, 1569725693)
ALittle.HandleQCheckSessionCode = function(client, msg) {
	return new Promise(function(___COROUTINE, ___) {
		let account = A_GameAccountManager.GetAccountById(msg.account_id);
		JavaScript.Assert(account, "账号不存在");
		JavaScript.Assert(account.GetSession() === msg.session_code, "验证码错误");
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-2092316375, HandleQCheckSessionCode, -1766835499)
}