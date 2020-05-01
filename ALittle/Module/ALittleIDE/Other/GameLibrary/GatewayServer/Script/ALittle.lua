-- ALittle Generate Lua
module("GatewayServer", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_ConfigSystem = nil
function __Module_Setup(module_path)
	Require(module_path, "Script/ModuleRouteManager")
	Require(module_path, "Script/DataRouteManager")
	Require(module_path, "Script/PhoneCodeManager")
	Require(module_path, "Script/RegisterManager")
	math.randomseed(os.time())
	g_ConfigSystem = ALittle.CreateJsonConfig("Module/ALittleIDE/Other/GameLibrary/FileServer.cfg", true)
	local wan_ip = g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartRouteSystem(1, 1)
	__CPPAPI_ServerSchedule:CreateConnectServer(yun_ip, wan_ip, 1001 + port_offset)
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1000 + port_offset, false)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, g_ConfigSystem:GetString("main_conn_ip", nil), g_ConfigSystem:GetString("main_conn_username", nil), g_ConfigSystem:GetString("main_conn_password", nil), g_ConfigSystem:GetInt("main_conn_port", nil), g_ConfigSystem:GetString("main_conn_dbname", nil))
	g_RegisterManager:Setup()
	g_PhoneCodeManager:Setup()
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_RegisterManager:Shutdown()
	g_PhoneCodeManager:Shutdown()
end

