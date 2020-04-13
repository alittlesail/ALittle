{


__LUAAPI_SEngine_Init = async function(script_base_path) {
	await Require(script_base_path + "Utility/System");
	await Require(script_base_path + "Utility/HttpSystem");
	await Require(script_base_path + "Utility/HttpFileSystem");
	await Require(script_base_path + "Utility/ClientSystem");
	await Require(script_base_path + "Utility/SessionSystem");
	await Require(script_base_path + "Utility/MysqlSystem");
	await Require(script_base_path + "CacheData/CacheDataSet");
	await Require(script_base_path + "CacheData/FullDataSet");
	await Require(script_base_path + "Utility/LogEventSystem");
	await Require(script_base_path + "Utility/GatewaySystem");
}

__LUAAPI_SetupMainModule = function(module_name, config_path) {
	ALittle.Log("module_name:" + module_name);
	let module = _G[module_name];
	if (module === undefined) {
		ALittle.Log("找不到模块:" + module_name);
		return;
	}
	let setup_module = module["__Module_Setup"];
	if (setup_module === undefined) {
		ALittle.Log("找不到模块__Module_Setup函数:" + module_name);
		return;
	}
	setup_module(config_path);
}

__LUAAPI_ShutdownMainModule = function(module_name) {
	let module = _G[module_name];
	if (module === undefined) {
		ALittle.Log("找不到模块:" + module_name);
		return;
	}
	let shutdown_module = module["__Module_Shutdown"];
	if (shutdown_module === undefined) {
		ALittle.Log("找不到模块__Module_Shutdown函数:" + module_name);
		return;
	}
	shutdown_module();
}

__LUAAPI_Update = function(frame_time) {
	A_LoopSystem.Update(frame_time);
}

__LUAAPI_HandleMysqlQueryTask = function(id, reason) {
	A_MysqlSystem.HandleMysqlQueryTask(id, reason);
}

__LUAAPI_HandleMysqlEmptyTask = function(id, reason) {
	A_MysqlSystem.HandleMysqlEmptyTask(id, reason);
}

__LUAAPI_HttpSucceed = function(id, response) {
	A_HttpSystem.HandleHttpSucceed(id, response);
}

__LUAAPI_HttpFailed = function(id, reason) {
	A_HttpSystem.HandleHttpFailed(id, reason);
}

__LUAAPI_HttpTask = function(http_id, path, param, content) {
	let http_callback = ALittle.FindHttpCallback(path);
	if (http_callback !== undefined) {
		ALittle.HttpSystem.HandleHttpTask(http_id, http_callback, ALittle.String_HttpAnalysisValueMap(param, content));
		return;
	}
	let http_download_callback = ALittle.FindHttpDownloadCallback(path);
	if (http_download_callback !== undefined) {
		ALittle.HttpSystem.HandleHttpDownloadTask(http_id, http_download_callback, ALittle.String_HttpAnalysisValueMap(param, content));
		return;
	}
	__CPPAPI_ServerSchedule.HttpClose(http_id);
}

__LUAAPI_HttpFileTask = function(http_id, path, param, content) {
	A_HttpFileSystem.HandleHttpFileTask(http_id, path, ALittle.FindHttpFileReceiverCallback(path), ALittle.String_HttpAnalysisValueMap(param, content));
}

__LUAAPI_HttpFileCompletedTask = function(http_id, reason) {
	A_HttpFileSystem.HandleHttpFileCompletedTask(http_id, reason);
}

__LUAAPI_ClientConnect = function(client_id, remote_ip, remote_port) {
	A_ClientSystem.HandleClientConnect(client_id, remote_ip, remote_port);
}

__LUAAPI_ClientDisconnect = function(client_id) {
	A_ClientSystem.HandleClientDisconnect(client_id);
}

__LUAAPI_ClientMessage = function(client_id, id, rpc_id, factory) {
	A_ClientSystem.HandleClientMessage(client_id, id, rpc_id, factory);
}

__LUAAPI_SessionConnect = function(connect_key, route_type, route_num) {
	A_SessionSystem.HandleSessionConnect(connect_key, route_type, route_num);
}

__LUAAPI_SessionDisconnect = function(connect_key, route_type, route_num) {
	A_SessionSystem.HandleSessionDisconnect(connect_key, route_type, route_num);
}

__LUAAPI_SessionMessage = function(connect_key, id, rpc_id, factory) {
	A_SessionSystem.HandleSessionMessage(connect_key, id, rpc_id, factory);
}

__LUAAPI_ConnectSessionFailed = function(route_type, route_num, reason) {
	A_SessionSystem.HandleConnectSessionFailed(route_type, route_num, reason);
}

__LUAAPI_ConnectSessionSucceed = function(connect_key, route_type, route_num) {
	A_SessionSystem.HandleConnectSessionSucceed(connect_key, route_type, route_num);
}

__LUAAPI_HandleConsoleCmd = function(cmd) {
	ALittle.ExecuteCommand(cmd);
}

}