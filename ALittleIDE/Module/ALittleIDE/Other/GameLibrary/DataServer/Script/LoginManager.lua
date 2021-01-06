-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DataServer == nil then _G.DataServer = {} end
local DataServer = DataServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1922773679, "ALittle.DATA2GS_QSaveSession", {
name = "ALittle.DATA2GS_QSaveSession", ns_name = "ALittle", rl_name = "DATA2GS_QSaveSession", hash_code = -1922773679,
name_list = {"account_id","session"},
type_list = {"int","string"},
option_map = {}
})
ALittle.RegStruct(-1627449907, "ALittle.DATA2GS_QEmpty", {
name = "ALittle.DATA2GS_QEmpty", ns_name = "ALittle", rl_name = "DATA2GS_QEmpty", hash_code = -1627449907,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1343408203, "DataServer.GW2DATA_QLogin", {
name = "DataServer.GW2DATA_QLogin", ns_name = "DataServer", rl_name = "GW2DATA_QLogin", hash_code = -1343408203,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-963859571, "ALittle.GS2DATA_ASaveSession", {
name = "ALittle.GS2DATA_ASaveSession", ns_name = "ALittle", rl_name = "GS2DATA_ASaveSession", hash_code = -963859571,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-937945851, "DataServer.GW2DATA_ALogin", {
name = "DataServer.GW2DATA_ALogin", ns_name = "DataServer", rl_name = "GW2DATA_ALogin", hash_code = -937945851,
name_list = {"client_ip","client_port","session_id"},
type_list = {"string","int","string"},
option_map = {}
})
ALittle.RegStruct(726375194, "ALittle.GS2DATA_AEmpty", {
name = "ALittle.GS2DATA_AEmpty", ns_name = "ALittle", rl_name = "GS2DATA_AEmpty", hash_code = 726375194,
name_list = {},
type_list = {},
option_map = {}
})

function DataServer.HandleQLogin(client, msg)
	local ___COROUTINE = coroutine.running()
	local info = DataServer.g_LeaseManager:GetLease(msg.account_id)
	Lua.Assert(info, "租约信息获取失败")
	local gs_info = DataServer.g_LeaseManager:GetGameServerInfo(info.gs_route_num)
	Lua.Assert(gs_info, "GS连接不存在")
	if not info.confirm then
		local error, result = ALittle.IMsgCommon.InvokeRPC(-1627449907, gs_info.session, {})
		if error ~= nil then
			Lua.Throw("GS空包发送失败:" .. error)
		end
		info.confirm = true
	end
	local q_save_session = {}
	q_save_session.account_id = msg.account_id
	q_save_session.session = tostring(math.random(10000, 99999))
	local error, a_save_session = ALittle.IMsgCommon.InvokeRPC(-1922773679, gs_info.session, q_save_session)
	if error ~= nil then
		Lua.Throw("会话ID保存失败:" .. error)
	end
	local param = {}
	param.client_ip = gs_info.client_ip
	param.client_port = gs_info.client_port
	param.session_id = q_save_session.session
	return param
end

ALittle.RegMsgRpcCallback(-1343408203, DataServer.HandleQLogin, -937945851)
end