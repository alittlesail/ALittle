-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


DeployServer.g_ConfigSystem = nil
function DeployServer.__Module_Setup(sengine_path, module_path, config_path)
	Require(sengine_path, "Script/WebAccount/WebPermission")
	Require(sengine_path, "Script/WebAccount/WebAccount")
	Require(sengine_path, "Script/WebAccount/WebAccountManager")
	Require(sengine_path, "Script/WebAccount/WebOPSManager")
	Require(module_path, "Script/DeployManager")
	math.randomseed(os.time())
	DeployServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = DeployServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = DeployServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = DeployServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartRouteSystem(9, 1)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, DeployServer.g_ConfigSystem:GetString("main_conn_ip", nil), DeployServer.g_ConfigSystem:GetString("main_conn_username", nil), DeployServer.g_ConfigSystem:GetString("main_conn_password", nil), DeployServer.g_ConfigSystem:GetInt("main_conn_port", nil), DeployServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1800 + port_offset, false)
	__CPPAPI_ServerSchedule:CreateClientServer(yun_ip, wan_ip, 1801 + port_offset, false)
	A_WebAccountManager:Setup()
	DeployServer.g_DeployManager:Setup()
end
DeployServer.__Module_Setup = Lua.CoWrap(DeployServer.__Module_Setup)

function DeployServer.__Module_Shutdown()
end

end