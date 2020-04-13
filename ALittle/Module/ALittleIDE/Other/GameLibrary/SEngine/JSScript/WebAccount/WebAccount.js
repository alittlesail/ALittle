{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(799192036, "ALittle.SessionInfo", {
name : "ALittle.SessionInfo", ns_name : "ALittle", rl_name : "SessionInfo", hash_code : 799192036,
name_list : ["new_client","old_client","time"],
type_list : ["string","string","int"],
option_map : {}
})
ALittle.RegStruct(1391512615, "ALittle.S2CWebForceLogout", {
name : "ALittle.S2CWebForceLogout", ns_name : "ALittle", rl_name : "S2CWebForceLogout", hash_code : 1391512615,
name_list : ["reason"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name : "ALittle.S2CWebAccountInfo", ns_name : "ALittle", rl_name : "S2CWebAccountInfo", hash_code : -417093574,
name_list : ["account_id","account_name","role_id","role_name","permission_map"],
type_list : ["string","string","string","string","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name : "ALittle.S2CWebServerInfo", ns_name : "ALittle", rl_name : "S2CWebServerInfo", hash_code : -300988017,
name_list : ["http_ip","http_port"],
type_list : ["string","int"],
option_map : {}
})
ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name : "ALittle.S2CWebSession", ns_name : "ALittle", rl_name : "S2CWebSession", hash_code : 1809602374,
name_list : ["session_id"],
type_list : ["string"],
option_map : {}
})

ALittle.WebAccount = JavaScript.Class(undefined, {
	Ctor : function(client, base_info, role_info) {
		this._session_info = {};
		this._session_info.old_client = "s" + lua.tostring(lua.math.random(100000, 999999));
		this._session_info.new_client = this._session_info.old_client;
		this._session_info.time = lua.os.time(undefined);
		this._client = client;
		this._base_info = base_info;
		this._role_info = role_info;
		this._permission_map = {};
		let ___OBJECT_1 = this._role_info.permission;
		for (let i = 1; i <= ___OBJECT_1.length; ++i) {
			let permission = ___OBJECT_1[i - 1];
			if (permission === undefined) break;
			this._permission_map[permission] = true;
		}
	},
	IsLogin : function() {
		return this._is_login;
	},
	IsDataReady : function() {
		return this._is_login;
	},
	GetID : function() {
		return this._base_info.account_id;
	},
	GetRoleID : function() {
		return this._role_info.role_id;
	},
	GetAccountName : function() {
		return this._base_info.account_name;
	},
	GetClient : function() {
		return this._client;
	},
	UpdateRoleInfo : function() {
		return new Promise((async function(___COROUTINE, ___) {
			{
				let [error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_id", this._base_info.account_id);
				if (error !== undefined) {
					ALittle.Error(error);
				}
				if (base_info === undefined) {
					___COROUTINE(); return;
				}
				this._base_info = base_info;
			}
			{
				this._role_info = {};
				this._permission_map = {};
				let [error, role_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-699725823), "role_id", this._base_info.role_id);
				if (error !== undefined) {
					ALittle.Error(error);
				}
				if (role_info === undefined) {
					___COROUTINE(); return;
				}
				this._role_info = role_info;
			}
			let ___OBJECT_2 = this._role_info.permission;
			for (let i = 1; i <= ___OBJECT_2.length; ++i) {
				let permission = ___OBJECT_2[i - 1];
				if (permission === undefined) break;
				this._permission_map[permission] = true;
			}
			___COROUTINE();
		}).bind(this));
	},
	CheckPermission : function(permission) {
		if (this._role_info.role_id === "alittle") {
			return true;
		}
		return this._permission_map[permission] !== undefined;
	},
	ForceLogout : function(reason) {
		let param = {};
		param.reason = reason;
		this._client.SendMsg(___all_struct.get(1391512615), param);
	},
	LogoutActionSystem : function() {
		this._is_login = false;
	},
	LoginActionSystem : function() {
		this._is_login = true;
		this.GenSessionCodeAndSync();
		{
			let param = {};
			param.account_id = this._base_info.account_id;
			param.account_name = this._base_info.account_name;
			param.role_id = this._role_info.role_id;
			param.role_name = this._role_info.role_name;
			param.permission_map = this._permission_map;
			this._client.SendMsg(___all_struct.get(-417093574), param);
		}
		{
			let param = {};
			param.http_ip = __CPPAPI_ServerSchedule.GetHttpServerYunIp();
			if (param.http_ip === undefined || param.http_ip === "") {
				param.http_ip = __CPPAPI_ServerSchedule.GetHttpServerIp();
			}
			param.http_port = __CPPAPI_ServerSchedule.GetHttpServerPort();
			this._client.SendMsg(___all_struct.get(-300988017), param);
		}
	},
	GenSessionCodeAndSync : function() {
		this._session_info.old_client = this._session_info.new_client;
		this._session_info.new_client = "s" + lua.tostring(lua.math.random(100000, 999999));
		this._session_info.time = lua.os.time(undefined);
		let param = {};
		param.session_id = this._session_info.new_client;
		this._client.SendMsg(___all_struct.get(1809602374), param);
	},
	CheckSessionCodeAndSync : function(session_code) {
		if (session_code === undefined || session_code === "") {
			return false;
		}
		session_code = lua.tostring(session_code);
		let result = this._session_info.old_client === session_code || this._session_info.new_client === session_code;
		if (lua.os.time(undefined) - this._session_info.time > 300) {
			this.GenSessionCodeAndSync();
		}
		return result;
	},
}, "ALittle.WebAccount");

}