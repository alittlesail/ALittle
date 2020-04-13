{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-192825113, "ALittle.WebBaseInfo", {
name : "ALittle.WebBaseInfo", ns_name : "ALittle", rl_name : "WebBaseInfo", hash_code : -192825113,
name_list : ["account_id","account_name","account_pwd","role_id","creator_id","create_time","create_index","update_time","update_index"],
type_list : ["string","string","string","string","string","int","int","int","int"],
option_map : {primary : "account_id",unique : "account_name"}
})
ALittle.RegStruct(-699725823, "ALittle.WebRoleInfo", {
name : "ALittle.WebRoleInfo", ns_name : "ALittle", rl_name : "WebRoleInfo", hash_code : -699725823,
name_list : ["role_id","role_name","permission","creator_id","create_time","create_index","update_time","update_index"],
type_list : ["string","string","List<string>","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name : "ALittle.QWebLogin", ns_name : "ALittle", rl_name : "QWebLogin", hash_code : 898014419,
name_list : ["device_id","client_platform","third_platform","account_name","account_pwd"],
type_list : ["string","string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name : "ALittle.AWebLogin", ns_name : "ALittle", rl_name : "AWebLogin", hash_code : -303211063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name : "ALittle.QWebLogout", ns_name : "ALittle", rl_name : "QWebLogout", hash_code : 1598450085,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name : "ALittle.AWebLogout", ns_name : "ALittle", rl_name : "AWebLogout", hash_code : -344058063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name : "ALittle.QWebChangePassword", ns_name : "ALittle", rl_name : "QWebChangePassword", hash_code : -1373673802,
name_list : ["old_password","new_password"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name : "ALittle.AWebChangePassword", ns_name : "ALittle", rl_name : "AWebChangePassword", hash_code : 1652964636,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.WebAccountManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_map_account = {};
		this._client_map_account = new Map();
		this._account_count = 0;
	},
	Setup : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let error = await A_MysqlSystem.CreateIfNotExit(___all_struct.get(-192825113));
			JavaScript.Assert(error === undefined, error);
			error = await A_MysqlSystem.CreateIfNotExit(___all_struct.get(-699725823));
			JavaScript.Assert(error === undefined, error);
			let count = 0;
			[error, count] = await A_MysqlSystem.SelectCount(___all_struct.get(-699725823), "role_id", "alittle");
			if (error !== undefined) {
				ALittle.Error(error);
			}
			if (count === 0) {
				let role_info = {};
				role_info.role_id = "alittle";
				role_info.role_name = "alittle";
				role_info.permission = [];
				role_info.creator_id = "alittle";
				let [time, index] = ALittle.NewTimeAndIndex();
				role_info.create_time = time;
				role_info.create_index = index;
				role_info.update_time = time;
				role_info.update_index = index;
				error = await A_MysqlSystem.InsertInto(___all_struct.get(-699725823), role_info);
				if (error !== undefined) {
					ALittle.Error(error);
				}
			}
			[error, count] = await A_MysqlSystem.SelectCount(___all_struct.get(-192825113), "account_name", "alittle");
			if (error !== undefined) {
				ALittle.Error(error);
			}
			if (count === 0) {
				let base_info = {};
				base_info.account_id = ALittle.String_MD5("alittle");
				base_info.account_name = "alittle";
				base_info.account_pwd = ALittle.String_MD5("ALittle" + ALittle.String_MD5("alittle") + "ALittle");
				base_info.role_id = "alittle";
				let [time, index] = ALittle.NewTimeAndIndex();
				base_info.create_time = time;
				base_info.create_index = index;
				base_info.update_time = time;
				base_info.update_index = index;
				error = await A_MysqlSystem.InsertInto(___all_struct.get(-192825113), base_info);
				if (error !== undefined) {
					ALittle.Error(error);
				}
			}
			this._update_route = ALittle.NewObject(ALittle.GatewayUpdateRoute, __CPPAPI_ServerSchedule.GetClientServerYunIp(), __CPPAPI_ServerSchedule.GetClientServerIp(), __CPPAPI_ServerSchedule.GetClientServerPort(), __CPPAPI_ServerSchedule.GetHttpServerYunIp(), __CPPAPI_ServerSchedule.GetHttpServerIp(), __CPPAPI_ServerSchedule.GetHttpServerPort(), this._account_count);
			A_ClientSystem.AddEventListener(___all_struct.get(-245025090), this, this.HandleClientDisconnect);
			A_ClientSystem.AddEventListener(___all_struct.get(-1221484301), this, this.HandleClientConnect);
			___COROUTINE();
		}).bind(this));
	},
	GetAccountById : function(account_id) {
		return this._id_map_account[account_id];
	},
	GetAccountByClient : function(client) {
		return this._client_map_account.get(client);
	},
	AddAccount : function(account) {
		this._client_map_account.set(account.GetClient(), account);
		this._id_map_account[account.GetID()] = account;
		++ this._account_count;
	},
	RemoveAccount : function(account_id) {
		let account = this._id_map_account[account_id];
		if (account === undefined) {
			return;
		}
		delete this._id_map_account[account_id];
		this._client_map_account.delete(account.GetClient());
		-- this._account_count;
		this._update_route.UpdateRouteWeight(this._account_count);
	},
	ForceLogout : function(account_id, reason) {
		let account = this._id_map_account[account_id];
		if (account === undefined) {
			return false;
		}
		account.ForceLogout(reason);
		account.LogoutActionSystem();
		this.RemoveAccount(account_id);
		return true;
	},
	CheckLoginById : function(account_id, session_id) {
		let account = this.GetAccountById(account_id);
		JavaScript.Assert(account !== undefined, "请先登录");
		JavaScript.Assert(account.CheckSessionCodeAndSync(session_id), "请先登录");
		return account;
	},
	CheckLoginByClient : function(client) {
		let account = this.GetAccountByClient(client);
		JavaScript.Assert(account !== undefined, "请先登录");
		return account;
	},
	Shutdown : function() {
	},
	HandleClientDisconnect : function(event) {
		event.msg_receiver._web_is_logining = false;
		let account = this.GetAccountById(event.msg_receiver._web_account_id);
		if (account === undefined) {
			return;
		}
		event.msg_receiver._web_account_id = "";
		account.LogoutActionSystem();
		this.RemoveAccount(account.GetID());
	},
	HandleClientConnect : function(event) {
	},
}, "ALittle.WebAccountManager");

window.A_WebAccountManager = ALittle.NewObject(ALittle.WebAccountManager);
ALittle.HandleQWebLogin = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let receiver = client;
		JavaScript.Assert(receiver._web_account_id === "" || receiver._web_account_id === undefined, "当前连接已经登录");
		let error = undefined;
		let base_info = undefined;
		[error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_name", msg.account_name);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(base_info !== undefined, "账号或密码错误");
		JavaScript.Assert(base_info.account_pwd === ALittle.String_MD5("ALittle" + msg.account_pwd + "ALittle"), "账号或密码错误");
		let role_info = undefined;
		[error, role_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-699725823), "role_id", base_info.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(role_info !== undefined, "您没有登录权限");
		let permission_map = {};
		let ___OBJECT_1 = role_info.permission;
		for (let i = 1; i <= ___OBJECT_1.length; ++i) {
			let permission = ___OBJECT_1[i - 1];
			if (permission === undefined) break;
			permission_map[permission] = true;
		}
		JavaScript.Assert(msg.account_name === "alittle" || permission_map[ALittle.WebPermission.PERMISSION_ACCOUNT_LOGIN] !== undefined, "您没有登录权限");
		let other_account = A_WebAccountManager.GetAccountById(base_info.account_id);
		if (other_account !== undefined) {
			other_account.ForceLogout("您的账号再另一个地方登录了");
			other_account.LogoutActionSystem();
			A_WebAccountManager.RemoveAccount(base_info.account_id);
		}
		let web_account = ALittle.NewObject(ALittle.WebAccount, receiver, base_info, role_info);
		A_WebAccountManager.AddAccount(web_account);
		receiver._web_account_id = base_info.account_id;
		web_account.LoginActionSystem();
		A_WebAccountManager._update_route.UpdateRouteWeight(A_WebAccountManager._account_count);
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(898014419, HandleQWebLogin, -303211063)
ALittle.HandleQWebLogout = function(client, msg) {
	return new Promise(function(___COROUTINE, ___) {
		let receiver = client;
		JavaScript.Assert(receiver._web_account_id !== undefined && receiver._web_account_id !== "", "当前连接还未登录");
		let web_account = A_WebAccountManager.GetAccountByClient(receiver);
		JavaScript.Assert(web_account !== undefined, "账号还未登录");
		receiver._web_account_id = "";
		web_account.LogoutActionSystem();
		A_WebAccountManager.RemoveAccount(web_account.GetID());
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(1598450085, HandleQWebLogout, -344058063)
ALittle.HandleQWebChangePassword = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let error = undefined;
		let base_info = undefined;
		[error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_id", web_account.GetID());
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(base_info !== undefined, "账号不存在");
		JavaScript.Assert(ALittle.String_MD5("ALittle" + msg.old_password + "ALittle") === base_info.account_pwd, "原密码错误");
		let new_password = ALittle.String_MD5("ALittle" + msg.new_password + "ALittle");
		error = await A_MysqlSystem.UpdateSet(___all_struct.get(-192825113), "account_pwd", new_password, "account_id", base_info.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1373673802, HandleQWebChangePassword, 1652964636)
}