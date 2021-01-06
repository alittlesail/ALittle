-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GatewayServer == nil then _G.GatewayServer = {} end
local GatewayServer = GatewayServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


GatewayServer.g_ConfigSystem = nil
function GatewayServer.__Module_Setup(sengine_path, module_path, config_path)
	Require(module_path, "Script/ModuleRouteManager")
	Require(module_path, "Script/DataRouteManager")
	Require(module_path, "Script/PhoneCodeManager")
	Require(module_path, "Script/RegisterManager")
	math.randomseed(os.time())
	GatewayServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = GatewayServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = GatewayServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = GatewayServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartRouteSystem(1, 1)
	__CPPAPI_ServerSchedule:CreateConnectServer(yun_ip, wan_ip, 1001 + port_offset)
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1000 + port_offset, false)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, GatewayServer.g_ConfigSystem:GetString("main_conn_ip", nil), GatewayServer.g_ConfigSystem:GetString("main_conn_username", nil), GatewayServer.g_ConfigSystem:GetString("main_conn_password", nil), GatewayServer.g_ConfigSystem:GetInt("main_conn_port", nil), GatewayServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	GatewayServer.g_RegisterManager:Setup()
	GatewayServer.g_PhoneCodeManager:Setup()
end
GatewayServer.__Module_Setup = Lua.CoWrap(GatewayServer.__Module_Setup)

function GatewayServer.__Module_Shutdown()
	GatewayServer.g_RegisterManager:Shutdown()
	GatewayServer.g_PhoneCodeManager:Shutdown()
end

end