-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-2062459143, "ALittleDeploy.QWebHook", {
name = "ALittleDeploy.QWebHook", ns_name = "ALittleDeploy", rl_name = "QWebHook", hash_code = -2062459143,
name_list = {"repository"},
type_list = {"ALittleDeploy.WebHookRepository"},
option_map = {}
})
ALittle.RegStruct(-1285017644, "ALittleDeploy.AWebHook", {
name = "ALittleDeploy.AWebHook", ns_name = "ALittleDeploy", rl_name = "AWebHook", hash_code = -1285017644,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(586662009, "ALittleDeploy.WebHookRepository", {
name = "ALittleDeploy.WebHookRepository", ns_name = "ALittleDeploy", rl_name = "WebHookRepository", hash_code = 586662009,
name_list = {"html_url"},
type_list = {"string"},
option_map = {}
})

function ALittleDeploy.HandleQWebHook(sender, msg)
	local ___COROUTINE = coroutine.running()
	ALittle.Log(ALittle.String_JsonEncode(msg))
	g_TaskManager:StartTaskByWebHook(msg.repository.html_url)
	return {}
end

ALittle.RegHttpCallback("ALittleDeploy.QWebHook", ALittleDeploy.HandleQWebHook)
end