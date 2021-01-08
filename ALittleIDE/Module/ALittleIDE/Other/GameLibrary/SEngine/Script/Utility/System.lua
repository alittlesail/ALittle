-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.RouteNum = {
	RN_DEFAULT = 1,
}

ALittle.RouteType = {
	RT_GATEWAY = 1,
	RT_DATA = 2,
	RT_VERSION = 3,
	RT_OPS = 4,
	RT_LOG = 5,
	RT_FILE = 6,
	RT_GAME = 7,
	RT_WEB = 8,
	RT_DEPLOY = 9,
}

ALittle.RoutePort = {
	RT_GATEWAY_HTTP = 1000,
	RT_GATEWAY_CONNECT = 1001,
	RT_VERSION_HTTP = 1100,
	RT_VERSION_CLIENT = 1101,
	RT_OPS_HTTP = 1200,
	RT_OPS_CLIENT = 1201,
	RT_LOG_CONNECT = 1300,
	RT_FILE_HTTP = 1400,
	RT_GAME_CLIENT_BEGIN = 1500,
	RT_DATA_BEGIN = 1600,
	RT_WEB_HTTP = 1700,
	RT_DEPLOY_HTTP = 1800,
	RT_DEPLOY_CLIENT = 1801,
}

function ALittle.GetRouteName(route_type, route_num)
	if route_type == 1 then
		return "Gateway_" .. route_num
	end
	if route_type == 2 then
		return "Data_" .. route_num
	end
	if route_type == 3 then
		return "Version_" .. route_num
	end
	if route_type == 4 then
		return "OPS_" .. route_num
	end
	if route_type == 5 then
		return "Log_" .. route_num
	end
	if route_type == 6 then
		return "File_" .. route_num
	end
	if route_type == 7 then
		return "Game_" .. route_num
	end
	if route_type == 8 then
		return "Web_" .. route_num
	end
	return "Unknow_" .. route_num
end

_G.SYSTEM_ACCOUNT_ID = 0x7FFFFFFF
_G.ACCOUNT_ID_MOD = 1000000
_G.GEN_ACCOUNT_ID_LEN = 6
function ALittle.GET_DATA_ROUTE_NUM_BY_ACCOUNT_ID(id)
	return math.floor(id / ACCOUNT_ID_MOD)
end

function ALittle.FINAL_ACCOUNT_ID(data_route_num, gen_account_id)
	return data_route_num * ACCOUNT_ID_MOD + gen_account_id
end

function ALittle.MAX_ACCOUNT_ID_BY_DATA_ROUTE_NUM(data_route_num)
	return (data_route_num + 1) * ACCOUNT_ID_MOD - 1
end

function ALittle.MIN_ACCOUNT_ID_BY_DATA_ROUTE_NUM(data_route_num)
	return data_route_num * ACCOUNT_ID_MOD
end

end