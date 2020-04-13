{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-370290946, "GatewayServer.NUpdateRouteInfo", {
name : "GatewayServer.NUpdateRouteInfo", ns_name : "GatewayServer", rl_name : "NUpdateRouteInfo", hash_code : -370290946,
name_list : ["route_weight","route_info"],
type_list : ["int","GatewayServer.ConnectInfo"],
option_map : {}
})
ALittle.RegStruct(-969892976, "GatewayServer.ConnectInfo", {
name : "GatewayServer.ConnectInfo", ns_name : "GatewayServer", rl_name : "ConnectInfo", hash_code : -969892976,
name_list : ["client_ip","client_port","http_ip","http_port"],
type_list : ["string","int","string","int"],
option_map : {}
})
ALittle.RegStruct(1006278988, "GatewayServer.NUpdateRouteWeight", {
name : "GatewayServer.NUpdateRouteWeight", ns_name : "GatewayServer", rl_name : "NUpdateRouteWeight", hash_code : 1006278988,
name_list : ["route_weight"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1307158553, "DataServer.GS2DATA_NGameServerInfo", {
name : "DataServer.GS2DATA_NGameServerInfo", ns_name : "DataServer", rl_name : "GS2DATA_NGameServerInfo", hash_code : -1307158553,
name_list : ["client_ip","client_port"],
type_list : ["string","int"],
option_map : {}
})
ALittle.RegStruct(-1355264955, "GatewayServer.NRouteConnected", {
name : "GatewayServer.NRouteConnected", ns_name : "GatewayServer", rl_name : "NRouteConnected", hash_code : -1355264955,
name_list : ["route_type","route_num"],
type_list : ["int","int"],
option_map : {}
})

ALittle.GatewayUpdateRoute = JavaScript.Class(undefined, {
	Ctor : function(client_yun_ip, client_ip, client_port, http_yun_ip, http_ip, http_port, weight) {
		this._info = {};
		this._info.route_weight = weight;
		this._info.route_info = {};
		this._info.route_info.client_ip = client_yun_ip;
		if (client_yun_ip === undefined || client_yun_ip === "") {
			this._info.route_info.client_ip = client_ip;
		}
		this._info.route_info.client_port = client_port;
		this._info.route_info.http_ip = http_yun_ip;
		if (http_yun_ip === undefined || http_yun_ip === "") {
			this._info.route_info.http_ip = http_ip;
		}
		this._info.route_info.http_port = http_port;
		this._weight = {};
		this._weight.route_weight = weight;
		A_SessionSystem.AddEventListener(___all_struct.get(-36908822), this, this.HandleAnySessionDisconnected);
		A_SessionSystem.AddEventListener(___all_struct.get(888437463), this, this.HandleAnySessionConnected);
		A_SessionSystem.AddConnectSession(ALittle.RouteType.RT_GATEWAY, ALittle.RouteNum.RN_DEFAULT);
	},
	HandleAnySessionDisconnected : function(event) {
		if (event.route_type !== ALittle.RouteType.RT_GATEWAY) {
			return;
		}
		this._session = undefined;
		return;
	},
	HandleAnySessionConnected : function(event) {
		if (event.route_type !== ALittle.RouteType.RT_GATEWAY) {
			return;
		}
		this._session = event.session;
		this._session.SendMsg(___all_struct.get(-370290946), this._info);
	},
	UpdateRouteWeight : function(weight) {
		this._info.route_weight = weight;
		this._weight.route_weight = weight;
		if (this._session === undefined) {
			return;
		}
		this._session.SendMsg(___all_struct.get(1006278988), this._weight);
	},
}, "ALittle.GatewayUpdateRoute");

ALittle.GatewaySystem = JavaScript.Class(undefined, {
	Ctor : function() {
		A_SessionSystem.AddEventListener(___all_struct.get(888437463), this, this.HandleAnySessionConnected);
	},
	HandleAnySessionConnected : function(event) {
		if (__CPPAPI_ServerSchedule.GetRouteType() === ALittle.RouteType.RT_GAME && event.route_type === ALittle.RouteType.RT_DATA) {
			{
				let param = {};
				param.client_ip = __CPPAPI_ServerSchedule.GetClientServerYunIp();
				if (param.client_ip === "") {
					param.client_ip = __CPPAPI_ServerSchedule.GetClientServerIp();
				}
				param.client_port = __CPPAPI_ServerSchedule.GetClientServerPort();
				event.session.SendMsg(___all_struct.get(-1307158553), param);
			}
		}
	},
}, "ALittle.GatewaySystem");

window.A_GatewaySystem = ALittle.NewObject(ALittle.GatewaySystem);
ALittle.HandleNRouteConnected = function(client, msg) {
	if (__CPPAPI_ServerSchedule.GetRouteType() === ALittle.RouteType.RT_GAME && msg.route_type === ALittle.RouteType.RT_DATA) {
		A_SessionSystem.AddConnectSession(msg.route_type, msg.route_num);
	}
}

ALittle.RegMsgCallback(-1355264955, HandleNRouteConnected)
}