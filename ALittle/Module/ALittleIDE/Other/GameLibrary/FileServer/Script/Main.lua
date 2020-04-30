
module("FileServer", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_ConfigSystem = nil
function __Module_Setup(config_path, engine_base_path, script_base_path)
	math.randomseed(os.time())
	if config_path == nil or config_path == "" then
		config_path = "Module/ALittleIDE/Other/GameLibrary/FileServer.cfg"
	end
	g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, g_ConfigSystem:GetString("main_conn_ip", nil), g_ConfigSystem:GetString("main_conn_username", nil), g_ConfigSystem:GetString("main_conn_password", nil), g_ConfigSystem:GetInt("main_conn_port", nil), g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(6, 1)
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1400 + port_offset, false)
	__CPPAPI_ServerSchedule:CreateConnectClient(wan_ip, 1001 + port_offset)
	Require(script_base_path, "HeadImageManager")
	Require(script_base_path, "ClanImageManager")
	g_HeadImageManager:Setup()
	g_ClanImageManager:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_HeadImageManager:Shutdown()
	g_ClanImageManager:Shutdown()
end

