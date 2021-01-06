-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.FileServer == nil then _G.FileServer = {} end
local FileServer = FileServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


FileServer.g_ConfigSystem = nil
function FileServer.__Module_Setup(sengine_path, module_path, config_path)
	Require(module_path, "Script/HeadImageManager")
	Require(module_path, "Script/ClanImageManager")
	math.randomseed(os.time())
	FileServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = FileServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = FileServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = FileServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, FileServer.g_ConfigSystem:GetString("main_conn_ip", nil), FileServer.g_ConfigSystem:GetString("main_conn_username", nil), FileServer.g_ConfigSystem:GetString("main_conn_password", nil), FileServer.g_ConfigSystem:GetInt("main_conn_port", nil), FileServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(6, 1)
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1400 + port_offset, false)
	__CPPAPI_ServerSchedule:CreateConnectClient(wan_ip, 1001 + port_offset)
	FileServer.g_HeadImageManager:Setup()
	FileServer.g_ClanImageManager:Setup()
end
FileServer.__Module_Setup = Lua.CoWrap(FileServer.__Module_Setup)

function FileServer.__Module_Shutdown()
	FileServer.g_HeadImageManager:Shutdown()
	FileServer.g_ClanImageManager:Shutdown()
end

end