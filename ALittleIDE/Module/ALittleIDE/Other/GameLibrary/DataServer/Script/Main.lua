-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DataServer == nil then _G.DataServer = {} end
local DataServer = DataServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


DataServer.g_ConfigSystem = nil
DataServer.g_ConnectServerYunIp = ""
DataServer.g_ConnectServerWanIp = ""
DataServer.g_ConnectServerPort = 0
function DataServer.__Module_Setup(sengine_path, module_path, config_path)
	Require(module_path, "Script/DataManager")
	Require(module_path, "Script/LoginManager")
	Require(module_path, "Script/LeaseManager")
	math.randomseed(os.time())
	DataServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = DataServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = DataServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = DataServer.g_ConfigSystem:GetConfig("port_offset", 0)
	local route_offset = DataServer.g_ConfigSystem:GetConfig("route_offset", 0)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, DataServer.g_ConfigSystem:GetString("main_conn_ip", nil), DataServer.g_ConfigSystem:GetString("main_conn_username", nil), DataServer.g_ConfigSystem:GetString("main_conn_password", nil), DataServer.g_ConfigSystem:GetInt("main_conn_port", nil), DataServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(2, 1 + route_offset)
	DataServer.g_ConnectServerYunIp = yun_ip
	DataServer.g_ConnectServerWanIp = wan_ip
	DataServer.g_ConnectServerPort = 1600 + port_offset + route_offset
	__CPPAPI_ServerSchedule:CreateConnectServer(DataServer.g_ConnectServerYunIp, DataServer.g_ConnectServerWanIp, DataServer.g_ConnectServerPort)
	__CPPAPI_ServerSchedule:CreateConnectClient(wan_ip, 1001 + port_offset)
	DataServer.g_LeaseManager:Setup()
end
DataServer.__Module_Setup = Lua.CoWrap(DataServer.__Module_Setup)

function DataServer.__Module_Shutdown()
	DataServer.g_LeaseManager:Shutdown()
end

end