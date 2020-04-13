
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


function __LUAAPI_Core_Init()
	A_ScriptSystem:RunEngineScript("Utility/System")
	A_ScriptSystem:RunEngineScript("Utility/HttpSystem")
	A_ScriptSystem:RunEngineScript("Utility/HttpFileSystem")
	A_ScriptSystem:RunEngineScript("Utility/ClientSystem")
	A_ScriptSystem:RunEngineScript("Utility/SessionSystem")
	A_ScriptSystem:RunEngineScript("Utility/MysqlSystem")
	A_ScriptSystem:RunEngineScript("CacheData/CacheDataSet")
	A_ScriptSystem:RunEngineScript("CacheData/FullDataSet")
	A_ScriptSystem:RunEngineScript("Utility/LogEventSystem")
	A_ScriptSystem:RunEngineScript("Utility/GatewaySystem")
end

function __LUAAPI_SetupMainModule(module_name, config_path)
	ALittle.Log("module_name:" .. module_name)
	local module = _G[module_name]
	if module == nil then
		ALittle.Log("找不到模块:" .. module_name)
		return
	end
	local setup_module = module["__Module_Setup"]
	if setup_module == nil then
		ALittle.Log("找不到模块__Module_Setup函数:" .. module_name)
		return
	end
	setup_module(config_path)
end

function __LUAAPI_ShutdownMainModule(module_name)
	local module = _G[module_name]
	if module == nil then
		ALittle.Log("找不到模块:" .. module_name)
		return
	end
	local shutdown_module = module["__Module_Shutdown"]
	if shutdown_module == nil then
		ALittle.Log("找不到模块__Module_Shutdown函数:" .. module_name)
		return
	end
	shutdown_module()
end

function __LUAAPI_Update(frame_time)
	A_LoopSystem:Update(frame_time)
	A_WeakLoopSystem:Update(frame_time)
end

function __LUAAPI_HandleMysqlQueryTask(id, reason)
	A_MysqlSystem:HandleMysqlQueryTask(id, reason)
end

function __LUAAPI_HandleMysqlEmptyTask(id, reason)
	A_MysqlSystem:HandleMysqlEmptyTask(id, reason)
end

function __LUAAPI_HttpSucceed(id, response)
	A_HttpSystem:HandleHttpSucceed(id, response)
end

function __LUAAPI_HttpFailed(id, reason)
	A_HttpSystem:HandleHttpFailed(id, reason)
end

function __LUAAPI_HttpTask(http_id, path, param, content)
	local http_callback = ALittle.FindHttpCallback(path)
	if http_callback ~= nil then
		ALittle.HttpSystem.HandleHttpTask(http_id, http_callback, ALittle.String_HttpAnalysisValueMap(param, content))
		return
	end
	local http_download_callback = ALittle.FindHttpDownloadCallback(path)
	if http_download_callback ~= nil then
		ALittle.HttpSystem.HandleHttpDownloadTask(http_id, http_download_callback, ALittle.String_HttpAnalysisValueMap(param, content))
		return
	end
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function __LUAAPI_HttpFileTask(http_id, path, param, content)
	A_HttpFileSystem:HandleHttpFileTask(http_id, path, ALittle.FindHttpFileReceiverCallback(path), ALittle.String_HttpAnalysisValueMap(param, content))
end

function __LUAAPI_HttpFileCompletedTask(http_id, reason)
	A_HttpFileSystem:HandleHttpFileCompletedTask(http_id, reason)
end

function __LUAAPI_ClientConnect(client_id, remote_ip, remote_port)
	A_ClientSystem:HandleClientConnect(client_id, remote_ip, remote_port)
end

function __LUAAPI_ClientDisconnect(client_id)
	A_ClientSystem:HandleClientDisconnect(client_id)
end

function __LUAAPI_ClientMessage(client_id, id, rpc_id, factory)
	A_ClientSystem:HandleClientMessage(client_id, id, rpc_id, factory)
end

function __LUAAPI_SessionConnect(connect_key, route_type, route_num)
	A_SessionSystem:HandleSessionConnect(connect_key, route_type, route_num)
end

function __LUAAPI_SessionDisconnect(connect_key, route_type, route_num)
	A_SessionSystem:HandleSessionDisconnect(connect_key, route_type, route_num)
end

function __LUAAPI_SessionMessage(connect_key, id, rpc_id, factory)
	A_SessionSystem:HandleSessionMessage(connect_key, id, rpc_id, factory)
end

function __LUAAPI_ConnectSessionFailed(route_type, route_num, reason)
	A_SessionSystem:HandleConnectSessionFailed(route_type, route_num, reason)
end

function __LUAAPI_ConnectSessionSucceed(connect_key, route_type, route_num)
	A_SessionSystem:HandleConnectSessionSucceed(connect_key, route_type, route_num)
end

function __LUAAPI_HandleConsoleCmd(cmd)
	ALittle.ExecuteCommand(cmd)
end

