{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.RouteNum = {
	RN_DEFAULT : 1,
}

ALittle.RouteType = {
	RT_GATEWAY : 1,
	RT_DATA : 2,
	RT_VERSION : 3,
	RT_OPS : 4,
	RT_LOG : 5,
	RT_FILE : 6,
	RT_GAME : 7,
}

ALittle.RoutePort = {
	RT_GATEWAY_HTTP : 1000,
	RT_GATEWAY_CONNECT : 1001,
	RT_VERSION_HTTP : 1100,
	RT_VERSION_CLIENT : 1101,
	RT_OPS_HTTP : 1200,
	RT_OPS_CLIENT : 1201,
	RT_LOG_CONNECT : 1300,
	RT_FILE_HTTP : 1400,
	RT_GAME_CLIENT_BEGIN : 1500,
	RT_DATA_BEGIN : 1600,
}

ALittle.GetRouteName = function(route_type, route_num) {
	if (route_type === ALittle.RouteType.RT_GATEWAY) {
		return "Gateway_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_DATA) {
		return "Data_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_VERSION) {
		return "Version_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_OPS) {
		return "OPS_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_LOG) {
		return "Log_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_FILE) {
		return "File_" + route_num;
	}
	if (route_type === ALittle.RouteType.RT_GAME) {
		return "Game_" + route_num;
	}
	return "Unknow_" + route_num;
}

window.SYSTEM_ACCOUNT_ID = 0x7FFFFFFF;
window.ACCOUNT_ID_MOD = 1000000;
window.GEN_ACCOUNT_ID_LEN = 6;
ALittle.GET_DATA_ROUTE_NUM_BY_ACCOUNT_ID = function(id) {
	return lua.math.floor(id / ACCOUNT_ID_MOD);
}

ALittle.FINAL_ACCOUNT_ID = function(data_route_num, gen_account_id) {
	return data_route_num * ACCOUNT_ID_MOD + gen_account_id;
}

ALittle.MAX_ACCOUNT_ID_BY_DATA_ROUTE_NUM = function(data_route_num) {
	return (data_route_num + 1) * ACCOUNT_ID_MOD - 1;
}

ALittle.MIN_ACCOUNT_ID_BY_DATA_ROUTE_NUM = function(data_route_num) {
	return data_route_num * ACCOUNT_ID_MOD;
}

}