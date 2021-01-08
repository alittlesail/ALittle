-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2127477562, "ALittleDeploy.QSettingInfo", {
name = "ALittleDeploy.QSettingInfo", ns_name = "ALittleDeploy", rl_name = "QSettingInfo", hash_code = -2127477562,
name_list = {"data"},
type_list = {"ALittleDeploy.D_SettingInfo"},
option_map = {}
})
ALittle.RegStruct(1869312477, "ALittleDeploy.D_SettingInfo", {
name = "ALittleDeploy.D_SettingInfo", ns_name = "ALittleDeploy", rl_name = "D_SettingInfo", hash_code = 1869312477,
name_list = {"git_path","svn_path"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(1351115674, "ALittleDeploy.AGetSetting", {
name = "ALittleDeploy.AGetSetting", ns_name = "ALittleDeploy", rl_name = "AGetSetting", hash_code = 1351115674,
name_list = {"data"},
type_list = {"ALittleDeploy.D_SettingInfo"},
option_map = {}
})
ALittle.RegStruct(-777126020, "ALittleDeploy.QGetSetting", {
name = "ALittleDeploy.QGetSetting", ns_name = "ALittleDeploy", rl_name = "QGetSetting", hash_code = -777126020,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(50637560, "ALittleDeploy.ASettingInfo", {
name = "ALittleDeploy.ASettingInfo", ns_name = "ALittleDeploy", rl_name = "ASettingInfo", hash_code = 50637560,
name_list = {},
type_list = {},
option_map = {}
})

function ALittleDeploy.HandleQGetSetting(sender, msg)
	local ___COROUTINE = coroutine.running()
	local rsp = {}
	rsp.data = g_KeyValueManager:GetConfig(___all_struct[1869312477], "setting", nil)
	return rsp
end

ALittle.RegHttpCallback("ALittleDeploy.QGetSetting", ALittleDeploy.HandleQGetSetting)
function ALittleDeploy.HandleQSettingInfo(sender, msg)
	local ___COROUTINE = coroutine.running()
	g_KeyValueManager:SetConfig("setting", msg.data)
	return {}
end

ALittle.RegHttpCallback("ALittleDeploy.QSettingInfo", ALittleDeploy.HandleQSettingInfo)
end