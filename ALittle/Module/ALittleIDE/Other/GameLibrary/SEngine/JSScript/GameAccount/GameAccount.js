{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1121683527, "DataServer.GS2DATA_QLoadStruct", {
name : "DataServer.GS2DATA_QLoadStruct", ns_name : "DataServer", rl_name : "GS2DATA_QLoadStruct", hash_code : -1121683527,
name_list : ["account_id","hash_code"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(1821069430, "ALittle.ProtocolAnyStruct", {
name : "ALittle.ProtocolAnyStruct", ns_name : "ALittle", rl_name : "ProtocolAnyStruct", hash_code : 1821069430,
name_list : ["hash_code","value"],
type_list : ["int","any"],
option_map : {}
})
ALittle.RegStruct(1463647694, "DataServer.GS2DATA_NBackupStruct", {
name : "DataServer.GS2DATA_NBackupStruct", ns_name : "DataServer", rl_name : "GS2DATA_NBackupStruct", hash_code : 1463647694,
name_list : ["account_id","data"],
type_list : ["int","ALittle.ProtocolAnyStruct"],
option_map : {}
})
ALittle.RegStruct(-197564509, "ALittle.GS2C_NAccountInfo", {
name : "ALittle.GS2C_NAccountInfo", ns_name : "ALittle", rl_name : "GS2C_NAccountInfo", hash_code : -197564509,
name_list : ["session_code","account_id","gs_route_id"],
type_list : ["string","int","int"],
option_map : {}
})

ALittle.GameAccountStatus = {
	CREATE : 1,
	LOADING : 2,
	CACHE : 3,
	ONLINE : 4,
}

ALittle.GameModule = JavaScript.Class(undefined, {
	Ctor : function(account) {
		this._account = account;
		this._account.RegisterModule(this);
	},
	GetDataReflect : function() {
		return undefined;
	},
	Release : function() {
	},
	HasData : function() {
		return false;
	},
	LoadData : async function(session) {
	},
	BackupData : function(session) {
	},
	OnDataReady : function() {
	},
	OnSendData : function() {
	},
	OnLogout : function() {
	},
}, "ALittle.GameModule");

if (ALittle.GameModule === undefined) throw new Error(" extends class:ALittle.GameModule is undefined");
ALittle.GameModuleTemplate = JavaScript.Class(ALittle.GameModule, {
	GetDataReflect : function() {
		return this.__class.__element[0];
	},
	OnSendData : function() {
		this._account.SendMsg(this.__class.__element[0], this._data);
	},
	HasData : function() {
		return true;
	},
	LoadData : async function(session) {
		if (session === undefined) {
			ALittle.Error(lua.tostring(this) + " session == null");
			this._account.LoadOneCompleted(false);
			return;
		}
		let rflt = this.GetDataReflect();
		if (rflt === undefined) {
			ALittle.Error(lua.tostring(this) + ":GetDataReflect() == null");
			this._account.LoadOneCompleted(false);
			return;
		}
		let param = {};
		param.account_id = this._account.GetId();
		param.hash_code = rflt.hash_code;
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(-1121683527, session, param);
		if (error !== undefined) {
			ALittle.Error(lua.tostring(this) + " DataServer.HandleQLoadStruct() failed:" + error);
			this._account.LoadOneCompleted(false);
			return;
		}
		this._data = result.value;
		this._account.LoadOneCompleted(true);
	},
	BackupData : function(session) {
		if (session === undefined) {
			return;
		}
		let rflt = this.GetDataReflect();
		if (rflt === undefined) {
			ALittle.Error(lua.tostring(this) + ":GetDataReflect() == null");
			this._account.LoadOneCompleted(false);
			return;
		}
		let param = {};
		param.account_id = this._account.GetId();
		param.data = {};
		param.data.hash_code = rflt.hash_code;
		param.data.value = this._data;
		session.SendMsg(___all_struct.get(1463647694), param);
	},
}, "ALittle.GameModuleTemplate");

ALittle.GameAccount = JavaScript.Class(undefined, {
	Ctor : function(id) {
		this._id = id;
		this._loading_count = 0;
		this._loading_failed = false;
		this._status = ALittle.GameAccountStatus.CREATE;
		this._module_map = {};
		this._BACKUP_INTERVAL = 10 * 1000;
		this._CACHE_INTERVAL = 30 * 1000;
		this._session = lua.tostring(lua.math.random(10000, 99999));
	},
	Release : function() {
		let ___OBJECT_1 = this._module_map;
		for (let name in ___OBJECT_1) {
			let module = ___OBJECT_1[name];
			if (module === undefined) continue;
			module.Release();
		}
		this.StopBackupTimer();
		this.StopCacheTimer();
	},
	GetId : function() {
		return this._id;
	},
	SetClient : function(client) {
		this._client = client;
	},
	GetClient : function() {
		return this._client;
	},
	GetStatus : function() {
		return this._status;
	},
	SetStatus : function(status) {
		this._status = status;
	},
	GetSession : function() {
		return this._session;
	},
	RegisterModule : function(module) {
		let rflt = (module).__class;
		this._module_map[rflt.__name] = module;
	},
	GetAllDataReflect : function() {
		let map = new Map();
		let table_map = new Map();
		let ___OBJECT_2 = this._module_map;
		for (let name in ___OBJECT_2) {
			let module = ___OBJECT_2[name];
			if (module === undefined) continue;
			let rflt = module.GetDataReflect();
			if (rflt !== undefined) {
				table_map.set(rflt.hash_code, true);
				let error = ALittle.CollectStructReflect(rflt, map);
				if (error !== undefined) {
					ALittle.Error(error);
				}
			}
		}
		let rflt_list = [];
		let count = 0;
		for (let [hash_code, info] of map) {
			if (info === undefined) continue;
			++ count;
			rflt_list[count - 1] = info;
		}
		return [rflt_list, table_map];
	},
	StartLoading : function(session) {
		if (!A_GameAccountManager.IsSendModuleReflect(session)) {
			let [rflt_list, table_map] = this.GetAllDataReflect();
			A_GameAccountManager.SendModuleReflect(session, rflt_list, table_map);
		}
		this._loading_count = 0;
		let ___OBJECT_3 = this._module_map;
		for (let name in ___OBJECT_3) {
			let module = ___OBJECT_3[name];
			if (module === undefined) continue;
			if (module.HasData()) {
				++ this._loading_count;
			}
		}
		if (this._loading_count === 0) {
			this.LoadOneCompletedImpl();
			return;
		}
		let ___OBJECT_4 = this._module_map;
		for (let name in ___OBJECT_4) {
			let module = ___OBJECT_4[name];
			if (module === undefined) continue;
			module.LoadData(session);
		}
	},
	LoadOneCompleted : function(result) {
		-- this._loading_count;
		if (!result) {
			this._loading_failed = true;
		}
		if (this._loading_count > 0) {
			return;
		}
		this.LoadOneCompletedImpl();
	},
	LoadOneCompletedImpl : function() {
		let account = A_GameAccountManager.GetAccountById(this._id);
		if (account !== this) {
			return;
		}
		this.OnDataReady();
		if (this._client !== undefined) {
			this.SetStatus(ALittle.GameAccountStatus.ONLINE);
			this.LoginAction();
		} else {
			this.SetStatus(ALittle.GameAccountStatus.CACHE);
			this.StartCacheTimer();
		}
		this.StartBackupTimer();
	},
	StartBackupTimer : function() {
		ALittle.Log("StartBackupTimer, account_id:" + this._id);
		if (this._backup_timer !== undefined) {
			A_LoopSystem.RemoveTimer(this._backup_timer);
		}
		this._backup_timer = A_LoopSystem.AddTimer(this._BACKUP_INTERVAL, this.Backup.bind(this), 0, this._BACKUP_INTERVAL);
	},
	StopBackupTimer : function() {
		if (this._backup_timer === undefined) {
			return;
		}
		ALittle.Log("StopBackupTimer, account_id:" + this._id);
		A_LoopSystem.RemoveTimer(this._backup_timer);
		this._backup_timer = undefined;
	},
	StartCacheTimer : function() {
		ALittle.Log("StartCacheTimer, account_id:" + this._id);
		if (this._cache_timer !== undefined) {
			A_LoopSystem.RemoveTimer(this._cache_timer);
		}
		this._cache_timer = A_LoopSystem.AddTimer(this._CACHE_INTERVAL, this.CacheTimeout.bind(this));
	},
	StopCacheTimer : function() {
		if (this._cache_timer === undefined) {
			return;
		}
		ALittle.Log("StopCacheTimer, account_id:" + this._id);
		A_LoopSystem.RemoveTimer(this._cache_timer);
		this._cache_timer = undefined;
	},
	CacheTimeout : function() {
		ALittle.Log("CacheTimeout, account_id:" + this._id);
		this._cache_timer = undefined;
		this.Backup();
		ALittle.g_GameLeaseManager.ReleaseLease(this._id);
		A_GameAccountManager.DeleteAccount(this);
	},
	Backup : function() {
		ALittle.Log("Backup, account_id:" + this._id);
		let lease_info = ALittle.g_GameLeaseManager.GetLease(this._id);
		if (lease_info === undefined || lease_info.session === undefined) {
			return;
		}
		let ___OBJECT_5 = this._module_map;
		for (let name in ___OBJECT_5) {
			let module = ___OBJECT_5[name];
			if (module === undefined) continue;
			module.BackupData(lease_info.session);
		}
	},
	LogoutAction : function() {
		let ___OBJECT_6 = this._module_map;
		for (let name in ___OBJECT_6) {
			let module = ___OBJECT_6[name];
			if (module === undefined) continue;
			module.OnLogout();
		}
		this.Backup();
	},
	OnDataReady : function() {
		let ___OBJECT_7 = this._module_map;
		for (let name in ___OBJECT_7) {
			let module = ___OBJECT_7[name];
			if (module === undefined) continue;
			module.OnDataReady();
		}
	},
	LoginAction : function() {
		let param = {};
		param.account_id = this._id;
		param.gs_route_id = __CPPAPI_ServerSchedule.GetRouteId();
		param.session_code = this._session;
		this.SendMsg(___all_struct.get(-197564509), param);
		let ___OBJECT_8 = this._module_map;
		for (let name in ___OBJECT_8) {
			let module = ___OBJECT_8[name];
			if (module === undefined) continue;
			module.OnSendData();
		}
		this.SendMsg(___all_struct.get(-1836835016), {});
	},
	SendMsg : function(T, msg) {
		if (this._client === undefined) {
			return;
		}
		this._client.SendMsg(T, msg);
	},
}, "ALittle.GameAccount");

}