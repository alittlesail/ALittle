-- ALittle Generate Lua And Do Not Edit This Line!
do
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.SetLogFunc(carp.Log)
function _G.RequireSEngine(base_path)
	local ___COROUTINE = coroutine.running()
	Require(base_path, "Utility/Time")
	Require(base_path, "Utility/System")
	Require(base_path, "Utility/HttpSystem")
	Require(base_path, "Utility/HttpFileSystem")
	Require(base_path, "Utility/ClientSystem")
	Require(base_path, "Utility/SessionSystem")
	Require(base_path, "Utility/MysqlSystem")
	Require(base_path, "CacheData/CacheDataSet")
	Require(base_path, "CacheData/FullDataSet")
	Require(base_path, "Utility/LogEventSystem")
	Require(base_path, "Utility/GatewaySystem")
end

function _G.__ALITTLEAPI_SetupMainModule(sengine_path, module_path, module_name, config_path)
	local ___COROUTINE = coroutine.running()
	ALittle.Log("module_name:" .. module_name)
	Require(module_path, "Script/Main")
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
	setup_module(sengine_path, module_path, config_path)
end

function _G.__ALITTLEAPI_ShutdownMainModule(module_name)
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

function _G.__ALITTLEAPI_Update(frame_time)
	A_LoopSystem:Update(frame_time)
	A_WeakLoopSystem:Update(frame_time)
end

function _G.__ALITTLEAPI_HandleMysqlQueryTask(id, reason)
	A_MysqlSystem:HandleMysqlQueryTask(id, reason)
end

function _G.__ALITTLEAPI_HandleMysqlEmptyTask(id, reason)
	A_MysqlSystem:HandleMysqlEmptyTask(id, reason)
end

function _G.__ALITTLEAPI_HttpSucceed(id, response)
	A_HttpSystem:HandleHttpSucceed(id, response)
end

function _G.__ALITTLEAPI_HttpFailed(id, reason)
	A_HttpSystem:HandleHttpFailed(id, reason)
end

function _G.__ALITTLEAPI_HttpTask(http_id, path, param, content)
	local http_callback = ALittle.FindHttpCallback(path)
	if http_callback ~= nil then
		ALittle.HttpSystem.HandleHttpTask(path, http_id, http_callback, ALittle.String_HttpAnalysisValueMap(param, content))
		return
	end
	local http_download_callback = ALittle.FindHttpDownloadCallback(path)
	if http_download_callback ~= nil then
		ALittle.HttpSystem.HandleHttpDownloadTask(path, http_id, http_download_callback, ALittle.String_HttpAnalysisValueMap(param, content))
		return
	end
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function _G.__ALITTLEAPI_HttpFileTask(http_id, path, param, content)
	A_HttpFileSystem:HandleHttpFileTask(http_id, path, ALittle.FindHttpFileReceiverCallback(path), ALittle.String_HttpAnalysisValueMap(param, content))
end

function _G.__ALITTLEAPI_HttpFileCompletedTask(http_id, reason)
	A_HttpFileSystem:HandleHttpFileCompletedTask(http_id, reason)
end

function _G.__ALITTLEAPI_ClientConnect(client_id, remote_ip, remote_port)
	A_ClientSystem:HandleClientConnect(client_id, remote_ip, remote_port)
end

function _G.__ALITTLEAPI_ClientDisconnect(client_id)
	A_ClientSystem:HandleClientDisconnect(client_id)
end

function _G.__ALITTLEAPI_ClientMessage(client_id, id, rpc_id, factory)
	A_ClientSystem:HandleClientMessage(client_id, id, rpc_id, factory)
end

function _G.__ALITTLEAPI_SessionConnect(connect_key, route_type, route_num)
	A_SessionSystem:HandleSessionConnect(connect_key, route_type, route_num)
end

function _G.__ALITTLEAPI_SessionDisconnect(connect_key, route_type, route_num)
	A_SessionSystem:HandleSessionDisconnect(connect_key, route_type, route_num)
end

function _G.__ALITTLEAPI_SessionMessage(connect_key, id, rpc_id, factory)
	A_SessionSystem:HandleSessionMessage(connect_key, id, rpc_id, factory)
end

function _G.__ALITTLEAPI_ConnectSessionFailed(route_type, route_num, reason)
	A_SessionSystem:HandleConnectSessionFailed(route_type, route_num, reason)
end

function _G.__ALITTLEAPI_ConnectSessionSucceed(connect_key, route_type, route_num)
	A_SessionSystem:HandleConnectSessionSucceed(connect_key, route_type, route_num)
end

function _G.__ALITTLEAPI_HandleConsoleCmd(cmd)
	ALittle.ExecuteCommand(cmd)
end

end