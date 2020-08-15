
module("OPSServer", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

g_ConfigSystem = nil
function __Module_Setup()
	math.randomseed(os.time())
	g_ConfigSystem = ALittle.NormalConfigSystem("Server/OPSServer/OPSServer.cfg")
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, g_ConfigSystem:GetString("main_conn_ip", nil), g_ConfigSystem:GetString("main_conn_username", nil), g_ConfigSystem:GetString("main_conn_password", nil), g_ConfigSystem:GetInt("main_conn_port", nil), g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(ALittle.RouteType.RT_OPS, ALittle.RouteNum.RN_DEFAULT)
	__CPPAPI_ServerSchedule:CreateHttpServer("", "127.0.0.1", ALittle.RoutePort.RT_OPS_HTTP, false)
	__CPPAPI_ServerSchedule:CreateClientServer("", "127.0.0.1", ALittle.RoutePort.RT_OPS_CLIENT)
	__CPPAPI_ServerSchedule:CreateConnectClient("127.0.0.1", ALittle.RoutePort.RT_GATEWAY_CONNECT)
	A_ScriptSystem:RunScriptFile("OPSManager")
	A_ScriptSystem:RunEngineScript("WebAccount/WebPermission")
	A_ScriptSystem:RunEngineScript("WebAccount/WebAccount")
	A_ScriptSystem:RunEngineScript("WebAccount/WebAccountManager")
	A_ScriptSystem:RunEngineScript("WebAccount/WebOPSManager")
	A_WebAccountManager:Setup("VersionServer")
	g_OPSManager:Setup()
end
__Module_Setup = ALittle.CoWrap(__Module_Setup)

function __Module_Shutdown()
	g_OPSManager:Shutdown()
end

