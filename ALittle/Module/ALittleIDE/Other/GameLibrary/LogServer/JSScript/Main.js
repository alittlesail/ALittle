{
if (typeof LogServer === "undefined") LogServer = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(976782632, "LogServer.LogEventInfo", {
name : "LogServer.LogEventInfo", ns_name : "LogServer", rl_name : "LogEventInfo", hash_code : 976782632,
name_list : ["account_id","main_type","sub_type","res_type","res_id","res_num","res_count","param_1","param_2","param_3","param_4","param_5","param_string","create_time","log_time"],
type_list : ["int","int","int","int","int","int","int","int","int","int","int","int","string","int","int"],
option_map : {index : "account_id,main_type,sub_type,create_time"}
})
ALittle.RegStruct(200159280, "LogServer.EmptyResult", {
name : "LogServer.EmptyResult", ns_name : "LogServer", rl_name : "EmptyResult", hash_code : 200159280,
name_list : [],
type_list : [],
option_map : {}
})

LogServer.g_ConfigSystem = undefined;
LogServer.__Module_Setup = async function(config_path) {
	lua.math.randomseed(lua.os.time(undefined));
	if (config_path === undefined || config_path === "") {
		config_path = "Module/ALittleIDE/Other/GameLibrary/LogServer.cfg";
	}
	LogServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true);
	let wan_ip = LogServer.g_ConfigSystem.GetConfig("wan_ip", "127.0.0.1");
	let yun_ip = LogServer.g_ConfigSystem.GetConfig("yun_ip", "");
	let port_offset = LogServer.g_ConfigSystem.GetConfig("port_offset", 0);
	__CPPAPI_ServerSchedule.StartMysqlQuery(1, LogServer.g_ConfigSystem.GetString("main_conn_ip", undefined), LogServer.g_ConfigSystem.GetString("main_conn_username", undefined), LogServer.g_ConfigSystem.GetString("main_conn_password", undefined), LogServer.g_ConfigSystem.GetInt("main_conn_port", undefined), LogServer.g_ConfigSystem.GetString("main_conn_dbname", undefined));
	__CPPAPI_ServerSchedule.StartRouteSystem(5, 1);
	__CPPAPI_ServerSchedule.CreateConnectServer(yun_ip, wan_ip, 1300 + port_offset);
}

LogServer.__Module_Shutdown = function() {
}

let g_CurDate = "";
LogServer.HandleLogEventInfo = function(client, msg) {
	return new Promise(async function(___COROUTINE, ___) {
		msg.log_time = lua.os.time(undefined);
		let cur_date = lua.os.date("%Y_%m_%d", msg.create_time);
		let info = ___all_struct.get(976782632);
		let table_name = info.rl_name + "_" + cur_date;
		if (g_CurDate !== cur_date) {
			let error = await A_MysqlSystem.CreateIfNotExit(___all_struct.get(976782632), table_name);
			if (error !== undefined) {
				throw new Error("日志表创建失败:" + table_name);
			}
			g_CurDate = cur_date;
		}
		let error = await A_MysqlSystem.InsertInto(___all_struct.get(976782632), msg, table_name);
		if (error !== undefined) {
			throw new Error("数据插入失败:" + error);
		}
		___COROUTINE({}); return;
		___COROUTINE();
	});
}

ALittle.RegMsgRpcCallback(976782632, HandleLogEventInfo, 200159280)
}