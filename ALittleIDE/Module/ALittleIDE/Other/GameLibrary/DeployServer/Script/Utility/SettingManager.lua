-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1161439561, "DeployServer.AGetSetting", {
name = "DeployServer.AGetSetting", ns_name = "DeployServer", rl_name = "AGetSetting", hash_code = 1161439561,
name_list = {"data"},
type_list = {"DeployServer.D_SettingInfo"},
option_map = {}
})
ALittle.RegStruct(955867961, "DeployServer.ASettingInfo", {
name = "DeployServer.ASettingInfo", ns_name = "DeployServer", rl_name = "ASettingInfo", hash_code = 955867961,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-777308643, "DeployServer.QGetSetting", {
name = "DeployServer.QGetSetting", ns_name = "DeployServer", rl_name = "QGetSetting", hash_code = -777308643,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(448683642, "DeployServer.D_SettingInfo", {
name = "DeployServer.D_SettingInfo", ns_name = "DeployServer", rl_name = "D_SettingInfo", hash_code = 448683642,
name_list = {"git_path","svn_path"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(103825275, "DeployServer.QSettingInfo", {
name = "DeployServer.QSettingInfo", ns_name = "DeployServer", rl_name = "QSettingInfo", hash_code = 103825275,
name_list = {"data"},
type_list = {"DeployServer.D_SettingInfo"},
option_map = {}
})

function DeployServer.HandleQGetSetting(sender, msg)
	local ___COROUTINE = coroutine.running()
	local rsp = {}
	rsp.data = g_KeyValueManager:GetConfig(___all_struct[448683642], "setting", nil)
	return rsp
end

ALittle.RegHttpCallback("DeployServer.QGetSetting", DeployServer.HandleQGetSetting)
function DeployServer.HandleQSettingInfo(sender, msg)
	local ___COROUTINE = coroutine.running()
	g_KeyValueManager:SetConfig("setting", msg.data)
	return {}
end

ALittle.RegHttpCallback("DeployServer.QSettingInfo", DeployServer.HandleQSettingInfo)
end