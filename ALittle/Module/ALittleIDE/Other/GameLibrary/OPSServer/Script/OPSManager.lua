
module("OPSServer", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSManager = ALittle.Class(nil, "OPSServer.OPSManager")

function OPSManager:Ctor()
end

function OPSManager.__getter:ClientCfg()
	return self._ops_client
end

function OPSManager.__getter:ServerCfg()
	return self._ops_server
end

function OPSManager:Setup()
	self._ops_path = g_ConfigSystem:GetString("ops_path", "")
	self._ops_path = ALittle.File_PathEndWithSplit(self._ops_path)
	self:ReloadClientConfig()
	self:ReloadServerConfig()
end

function OPSManager:Shutdown()
end

function OPSManager:ReloadClientConfig()
	local loader = ALittle.NormalFileLoader()
	local client_file = loader:Load(self._ops_path .. "Client.cfg")
	if client_file == nil then
		ALittle.Error("文件加载失败:" .. self._ops_path .. "Client.cfg")
		return
	end
	local error, content = ALittle.TCall(json.decode, client_file)
	if error ~= nil then
		ALittle.Error("文件解析失败:" .. self._ops_path .. "Client.cfg")
		return
	end
	self._permission = content
	self._ops_client_md5 = ALittle.String_FileMD5(self._ops_path .. "Client.cfg")
	self._ops_client = content
	ALittle.Log(self._ops_path .. "Client.cfg reload succeed!")
end

function OPSManager:ReloadServerConfig()
	local loader = ALittle.NormalFileLoader()
	local server_file = loader:Load(self._ops_path .. "Server.cfg")
	if server_file == nil then
		ALittle.Error("文件加载失败:" .. self._ops_path .. "Server.cfg")
		return
	end
	local error, content = ALittle.TCall(json.decode, server_file)
	if error ~= nil then
		ALittle.Error("文件解析失败:" .. self._ops_path .. "Server.cfg")
		return
	end
	self._ops_server = content
	ALittle.Log(self._ops_path .. "Server.cfg reload succeed!")
end

function OPSManager:FillOPSPermission(cfg)
	for key, value in ___pairs(self._permission.permission) do
		cfg.permission[key] = ALittle.String_CopyTable(value)
	end
end

g_OPSManager = OPSManager()
function reloadClientCfg()
	g_OPSManager:ReloadClientConfig()
end

ALittle.RegCmdCallback("reloadClientCfg", reloadClientCfg, {}, {}, "重新加载客户端配置")
function reloadServerCfg()
	g_OPSManager:ReloadServerConfig()
end

ALittle.RegCmdCallback("reloadServerCfg", reloadServerCfg, {}, {}, "重新加载服务器配置")
local OPERATION_TABLE_DAY = "TABLE_DAY"
local OPERATION_ACCOUNT_ID = "ACCOUNT_ID"
function HandleQOPSInvoke(client, msg)
	local account = A_WebAccountManager:CheckLoginById(msg.__account_id, msg.__session_id)
end

ALittle.RegHttpCallback("OPSServer.QOPSInvoke", HandleQOPSInvoke)
