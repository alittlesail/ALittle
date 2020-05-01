-- ALittle Generate Lua
module("DataServer", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_ConfigSystem = nil
g_ConnectServerYunIp = ""
g_ConnectServerWanIp = ""
g_ConnectServerPort = 0
function __Module_Setup(sengine_path, module_path)
	Require(module_path, "Script/DataManager")
	Require(module_path, "Script/LoginManager")
	Require(module_path, "Script/LeaseManager")
	math.randomseed(os.time())
	g_ConfigSystem = ALittle.CreateJsonConfig("Module/ALittleIDE/Other/GameLibrary/DataServer.cfg", true)
	local wan_ip = g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = g_ConfigSystem:GetConfig("port_offset", 0)
	local route_offset = g_ConfigSystem:GetConfig("route_offset", 0)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, g_ConfigSystem:GetString("main_conn_ip", nil), g_ConfigSystem:GetString("main_conn_username", nil), g_ConfigSystem:GetString("main_conn_password", nil), g_ConfigSystem:GetInt("main_conn_port", nil), g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(2, 1 + route_offset)
	g_ConnectServerYunIp = yun_ip
	g_ConnectServerWanIp = wan_ip
	g_ConnectServerPort = 1600 + port_offset + route_offset
	__CPPAPI_ServerSchedule:CreateConnectServer(g_ConnectServerYunIp, g_ConnectServerWanIp, g_ConnectServerPort)
	__CPPAPI_ServerSchedule:CreateConnectClient(wan_ip, 1001 + port_offset)
	g_LeaseManager:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_LeaseManager:Shutdown()
end

