-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.VersionServer == nil then _G.VersionServer = {} end
local VersionServer = VersionServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


VersionServer.g_ConfigSystem = nil
function VersionServer.__Module_Setup(sengine_path, module_path, config_path)
	Require(sengine_path, "Script/WebAccount/WebPermission")
	Require(sengine_path, "Script/WebAccount/WebAccount")
	Require(sengine_path, "Script/WebAccount/WebAccountManager")
	Require(sengine_path, "Script/WebAccount/WebOPSManager")
	Require(module_path, "Script/VersionManager")
	math.randomseed(os.time())
	VersionServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = VersionServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = VersionServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = VersionServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartRouteSystem(3, 1)
	__CPPAPI_ServerSchedule:CreateConnectClient(wan_ip, 1001 + port_offset)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, VersionServer.g_ConfigSystem:GetString("main_conn_ip", nil), VersionServer.g_ConfigSystem:GetString("main_conn_username", nil), VersionServer.g_ConfigSystem:GetString("main_conn_password", nil), VersionServer.g_ConfigSystem:GetInt("main_conn_port", nil), VersionServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1100 + port_offset, false)
	__CPPAPI_ServerSchedule:CreateClientServer(yun_ip, wan_ip, 1101 + port_offset, false)
	A_WebAccountManager:Setup()
	VersionServer.g_VersionManager:Setup()
end
VersionServer.__Module_Setup = Lua.CoWrap(VersionServer.__Module_Setup)

function VersionServer.__Module_Shutdown()
end

end