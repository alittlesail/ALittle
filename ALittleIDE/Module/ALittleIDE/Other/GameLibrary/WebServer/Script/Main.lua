-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.WebServer == nil then _G.WebServer = {} end
local WebServer = WebServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1776436342, "WebServer.QFileDownload", {
name = "WebServer.QFileDownload", ns_name = "WebServer", rl_name = "QFileDownload", hash_code = -1776436342,
name_list = {},
type_list = {},
option_map = {}
})

WebServer.g_ConfigSystem = nil
function WebServer.__Module_Setup(sengine_path, module_path, config_path)
	math.randomseed(os.time())
	WebServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = WebServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = WebServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = WebServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartRouteSystem(8, 1)
	__CPPAPI_ServerSchedule:CreateHttpServer(yun_ip, wan_ip, 1500 + port_offset, false)
	ALittle.RegHttpDownloadCallbackFactory(WebServer.HttpDownloadCallbackFactory)
	ALittle.Log("root_path:" .. WebServer.g_ConfigSystem:GetString("root_path", ""))
end
WebServer.__Module_Setup = Lua.CoWrap(WebServer.__Module_Setup)

function WebServer.HttpDownloadCallbackFactory(method)
	return WebServer.HandleFileDownload
end

function WebServer.__Module_Shutdown()
end

function WebServer.HandleFileDownload(client, msg)
	local ___COROUTINE = coroutine.running()
	return WebServer.g_ConfigSystem:GetString("root_path", "") .. client.method, 0
end

ALittle.RegHttpDownloadCallback("WebServer.QFileDownload", WebServer.HandleFileDownload)
end