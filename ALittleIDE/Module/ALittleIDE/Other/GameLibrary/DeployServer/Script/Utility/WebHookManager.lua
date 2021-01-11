-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(2100150852, "DeployServer.AWebHook", {
name = "DeployServer.AWebHook", ns_name = "DeployServer", rl_name = "AWebHook", hash_code = 2100150852,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1363542185, "DeployServer.WebHookRepository", {
name = "DeployServer.WebHookRepository", ns_name = "DeployServer", rl_name = "WebHookRepository", hash_code = 1363542185,
name_list = {"html_url"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(1314669887, "DeployServer.QWebHook", {
name = "DeployServer.QWebHook", ns_name = "DeployServer", rl_name = "QWebHook", hash_code = 1314669887,
name_list = {"repository"},
type_list = {"DeployServer.WebHookRepository"},
option_map = {}
})

function DeployServer.HandleQWebHook(sender, msg)
	local ___COROUTINE = coroutine.running()
	ALittle.Log(ALittle.String_JsonEncode(msg))
	g_TaskManager:StartTaskByWebHook(msg.repository.html_url)
	return {}
end

ALittle.RegHttpCallback("DeployServer.QWebHook", DeployServer.HandleQWebHook)
end