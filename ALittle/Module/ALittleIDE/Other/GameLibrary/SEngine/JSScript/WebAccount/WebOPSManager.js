{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1334237987, "ALittle.QVersionCreateAccount", {
name : "ALittle.QVersionCreateAccount", ns_name : "ALittle", rl_name : "QVersionCreateAccount", hash_code : -1334237987,
name_list : ["__account_id","__session_id","account_name","account_pwd"],
type_list : ["string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(-52328307, "ALittle.AVersionCreateAccount", {
name : "ALittle.AVersionCreateAccount", ns_name : "ALittle", rl_name : "AVersionCreateAccount", hash_code : -52328307,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-216744240, "ALittle.QVersionDeleteAccount", {
name : "ALittle.QVersionDeleteAccount", ns_name : "ALittle", rl_name : "QVersionDeleteAccount", hash_code : -216744240,
name_list : ["__account_id","__session_id","account_id"],
type_list : ["string","string","string"],
option_map : {}
})
ALittle.RegStruct(-1217701648, "ALittle.AVersionDeleteAccount", {
name : "ALittle.AVersionDeleteAccount", ns_name : "ALittle", rl_name : "AVersionDeleteAccount", hash_code : -1217701648,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-1670031053, "ALittle.QVersionSetAccountPwd", {
name : "ALittle.QVersionSetAccountPwd", ns_name : "ALittle", rl_name : "QVersionSetAccountPwd", hash_code : -1670031053,
name_list : ["__account_id","__session_id","account_id","account_pwd"],
type_list : ["string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(1908089542, "ALittle.AVersionSetAccountPwd", {
name : "ALittle.AVersionSetAccountPwd", ns_name : "ALittle", rl_name : "AVersionSetAccountPwd", hash_code : 1908089542,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-2090346221, "ALittle.QVersionSetAccountRole", {
name : "ALittle.QVersionSetAccountRole", ns_name : "ALittle", rl_name : "QVersionSetAccountRole", hash_code : -2090346221,
name_list : ["__account_id","__session_id","account_id","role_id"],
type_list : ["string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(-1565382514, "ALittle.AVersionSetAccountRole", {
name : "ALittle.AVersionSetAccountRole", ns_name : "ALittle", rl_name : "AVersionSetAccountRole", hash_code : -1565382514,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-813534860, "ALittle.QVersionCreateRole", {
name : "ALittle.QVersionCreateRole", ns_name : "ALittle", rl_name : "QVersionCreateRole", hash_code : -813534860,
name_list : ["__account_id","__session_id","role_name","role_permission"],
type_list : ["string","string","string","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(662928143, "ALittle.AVersionCreateRole", {
name : "ALittle.AVersionCreateRole", ns_name : "ALittle", rl_name : "AVersionCreateRole", hash_code : 662928143,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1102339341, "ALittle.QVersionUpdateRole", {
name : "ALittle.QVersionUpdateRole", ns_name : "ALittle", rl_name : "QVersionUpdateRole", hash_code : 1102339341,
name_list : ["__account_id","__session_id","role_id","role_name","role_permission"],
type_list : ["string","string","string","string","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(-1341503137, "ALittle.AVersionUpdateRole", {
name : "ALittle.AVersionUpdateRole", ns_name : "ALittle", rl_name : "AVersionUpdateRole", hash_code : -1341503137,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1314376608, "ALittle.QVersionDeleteRole", {
name : "ALittle.QVersionDeleteRole", ns_name : "ALittle", rl_name : "QVersionDeleteRole", hash_code : 1314376608,
name_list : ["__account_id","__session_id","role_id"],
type_list : ["string","string","string"],
option_map : {}
})
ALittle.RegStruct(1169802891, "ALittle.AVersionDeleteRole", {
name : "ALittle.AVersionDeleteRole", ns_name : "ALittle", rl_name : "AVersionDeleteRole", hash_code : 1169802891,
name_list : [],
type_list : [],
option_map : {}
})

ALittle.HandleQVersionCreateAccount = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		JavaScript.Assert(msg.account_name !== undefined && msg.account_name !== "", "账号名不能为空");
		JavaScript.Assert(msg.account_pwd !== undefined && msg.account_pwd !== "", "密码不能为空");
		let [error, count] = await A_MysqlSystem.SelectCount(___all_struct.get(-192825113), "account_name", msg.account_name);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(count === 0, "账号名已存在");
		let base_info = {};
		base_info.account_id = ALittle.String_GenerateID("account_id");
		base_info.account_name = msg.account_name;
		base_info.account_pwd = ALittle.String_MD5("ALittle" + ALittle.String_MD5(msg.account_pwd) + "ALittle");
		let [time, index] = ALittle.NewTimeAndIndex();
		base_info.create_time = time;
		base_info.create_index = index;
		base_info.update_time = time;
		base_info.update_index = index;
		error = await A_MysqlSystem.InsertInto(___all_struct.get(-192825113), base_info);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1334237987, HandleQVersionCreateAccount, -52328307)
ALittle.HandleQVersionDeleteAccount = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let [error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(base_info !== undefined, "账号不存在");
		JavaScript.Assert(base_info.account_name !== "alittle", "超级管理员不能删除");
		error = await A_MysqlSystem.DeleteFromByKey(___all_struct.get(-192825113), "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-216744240, HandleQVersionDeleteAccount, -1217701648)
ALittle.HandleQVersionSetAccountPwd = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let [error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(base_info !== undefined, "账号不存在");
		let password = ALittle.String_MD5("ALittle" + ALittle.String_MD5(msg.account_pwd) + "ALittle");
		error = await A_MysqlSystem.UpdateSet(___all_struct.get(-192825113), "account_pwd", password, "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-1670031053, HandleQVersionSetAccountPwd, 1908089542)
ALittle.HandleQVersionSetAccountRole = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let error = undefined;
		let base_info = undefined;
		[error, base_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-192825113), "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(base_info !== undefined, "账号不存在");
		JavaScript.Assert(base_info.account_name !== "alittle", "超级管理员不能修改角色");
		let role_info = undefined;
		[error, role_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-699725823), "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(role_info !== undefined, "角色不存在");
		error = await A_MysqlSystem.UpdateSet(___all_struct.get(-192825113), "role_id", msg.role_id, "account_id", msg.account_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		await web_account.UpdateRoleInfo();
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-2090346221, HandleQVersionSetAccountRole, -1565382514)
ALittle.HandleQVersionCreateRole = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let permission_list = [];
		let ___OBJECT_1 = msg.role_permission;
		for (let permission in ___OBJECT_1) {
			let _ = ___OBJECT_1[permission];
			if (_ === undefined) continue;
			ALittle.List_Push(permission_list, permission);
		}
		let role_info = {};
		role_info.role_id = ALittle.String_GenerateID("role_id");
		role_info.permission = permission_list;
		role_info.role_name = msg.role_name;
		let [time, index] = ALittle.NewTimeAndIndex();
		role_info.create_time = time;
		role_info.create_index = index;
		role_info.update_time = time;
		role_info.update_index = index;
		let error = await A_MysqlSystem.InsertInto(___all_struct.get(-699725823), role_info);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(-813534860, HandleQVersionCreateRole, 662928143)
ALittle.HandleQVersionUpdateRole = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let [error, role_info] = await A_MysqlSystem.SelectOneFromByKey(___all_struct.get(-699725823), "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(role_info !== undefined, "角色不存在");
		let permission_list = [];
		let ___OBJECT_2 = msg.role_permission;
		for (let permission in ___OBJECT_2) {
			let _ = ___OBJECT_2[permission];
			if (_ === undefined) continue;
			ALittle.List_Push(permission_list, permission);
		}
		error = await A_MysqlSystem.UpdateSet(___all_struct.get(-699725823), "role_name", msg.role_name, "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		error = await A_MysqlSystem.UpdateSet(___all_struct.get(-699725823), "permission", permission_list, "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		let sql = "SELECT `account_id` FROM `WebBaseInfo` WHERE `role_id`=?";
		let query = ALittle.NewObject(ALittle.MysqlStatementQuery);
		query.sql = sql;
		query.value = msg.role_id;
		error = await query.Execute();
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		for (let i = 1; i <= query.count; i += 1) {
			let account_id = query.String;
			let account = A_WebAccountManager.GetAccountById(account_id);
			if (account !== undefined) {
				await account.UpdateRoleInfo();
			}
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(1102339341, HandleQVersionUpdateRole, -1341503137)
ALittle.HandleQVersionDeleteRole = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		let web_account = A_WebAccountManager.CheckLoginByClient(client);
		let [error, count] = await A_MysqlSystem.SelectCount(___all_struct.get(-192825113), "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		JavaScript.Assert(count === 0, "角色正在使用不能删除");
		error = await A_MysqlSystem.DeleteFromByKey(___all_struct.get(-699725823), "role_id", msg.role_id);
		if (error !== undefined) {
			throw new Error("数据库操作失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(1314376608, HandleQVersionDeleteRole, 1169802891)
}