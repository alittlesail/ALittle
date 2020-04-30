
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()

RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
RegStruct(-370290946, "GatewayServer.NUpdateRouteInfo", {
name = "GatewayServer.NUpdateRouteInfo", ns_name = "GatewayServer", rl_name = "NUpdateRouteInfo", hash_code = -370290946,
name_list = {"route_weight","route_info"},
type_list = {"int","GatewayServer.ConnectInfo"},
option_map = {}
})
RegStruct(-969892976, "GatewayServer.ConnectInfo", {
name = "GatewayServer.ConnectInfo", ns_name = "GatewayServer", rl_name = "ConnectInfo", hash_code = -969892976,
name_list = {"client_ip","client_port","http_ip","http_port"},
type_list = {"string","int","string","int"},
option_map = {}
})
RegStruct(1006278988, "GatewayServer.NUpdateRouteWeight", {
name = "GatewayServer.NUpdateRouteWeight", ns_name = "GatewayServer", rl_name = "NUpdateRouteWeight", hash_code = 1006278988,
name_list = {"route_weight"},
type_list = {"int"},
option_map = {}
})
RegStruct(-1307158553, "DataServer.GS2DATA_NGameServerInfo", {
name = "DataServer.GS2DATA_NGameServerInfo", ns_name = "DataServer", rl_name = "GS2DATA_NGameServerInfo", hash_code = -1307158553,
name_list = {"client_ip","client_port"},
type_list = {"string","int"},
option_map = {}
})
RegStruct(-1355264955, "GatewayServer.NRouteConnected", {
name = "GatewayServer.NRouteConnected", ns_name = "GatewayServer", rl_name = "NRouteConnected", hash_code = -1355264955,
name_list = {"route_type","route_num"},
type_list = {"int","int"},
option_map = {}
})

GatewayUpdateRoute = Lua.Class(nil, "ALittle.GatewayUpdateRoute")

function GatewayUpdateRoute:Ctor(client_yun_ip, client_ip, client_port, http_yun_ip, http_ip, http_port, weight)
	___rawset(self, "_info", {})
	self._info.route_weight = weight
	self._info.route_info = {}
	self._info.route_info.client_ip = client_yun_ip
	if client_yun_ip == nil or client_yun_ip == "" then
		self._info.route_info.client_ip = client_ip
	end
	self._info.route_info.client_port = client_port
	self._info.route_info.http_ip = http_yun_ip
	if http_yun_ip == nil or http_yun_ip == "" then
		self._info.route_info.http_ip = http_ip
	end
	self._info.route_info.http_port = http_port
	___rawset(self, "_weight", {})
	self._weight.route_weight = weight
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
	A_SessionSystem:AddEventListener(___all_struct[888437463], self, self.HandleAnySessionConnected)
	A_SessionSystem:AddConnectSession(RouteType.RT_GATEWAY, RouteNum.RN_DEFAULT)
end

function GatewayUpdateRoute:HandleAnySessionDisconnected(event)
	if event.route_type ~= RouteType.RT_GATEWAY then
		return
	end
	self._session = nil
	return
end

function GatewayUpdateRoute:HandleAnySessionConnected(event)
	if event.route_type ~= RouteType.RT_GATEWAY then
		return
	end
	self._session = event.session
	self._session:SendMsg(___all_struct[-370290946], self._info)
end

function GatewayUpdateRoute:UpdateRouteWeight(weight)
	self._info.route_weight = weight
	self._weight.route_weight = weight
	if self._session == nil then
		return
	end
	self._session:SendMsg(___all_struct[1006278988], self._weight)
end

GatewaySystem = Lua.Class(nil, "ALittle.GatewaySystem")

function GatewaySystem:Ctor()
	A_SessionSystem:AddEventListener(___all_struct[888437463], self, self.HandleAnySessionConnected)
end

function GatewaySystem:HandleAnySessionConnected(event)
	if __CPPAPI_ServerSchedule:GetRouteType() == RouteType.RT_GAME and event.route_type == RouteType.RT_DATA then
		do
			local param = {}
			param.client_ip = __CPPAPI_ServerSchedule:GetClientServerYunIp()
			if param.client_ip == "" then
				param.client_ip = __CPPAPI_ServerSchedule:GetClientServerIp()
			end
			param.client_port = __CPPAPI_ServerSchedule:GetClientServerPort()
			event.session:SendMsg(___all_struct[-1307158553], param)
		end
	end
end

_G.A_GatewaySystem = GatewaySystem()
function HandleNRouteConnected(client, msg)
	if __CPPAPI_ServerSchedule:GetRouteType() == RouteType.RT_GAME and msg.route_type == RouteType.RT_DATA then
		A_SessionSystem:AddConnectSession(msg.route_type, msg.route_num)
	end
end

RegMsgCallback(-1355264955, HandleNRouteConnected)
