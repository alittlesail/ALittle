-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GatewayServer == nil then _G.GatewayServer = {} end
local GatewayServer = GatewayServer
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2090635487, "GatewayServer.ARouteInfo", {
name = "GatewayServer.ARouteInfo", ns_name = "GatewayServer", rl_name = "ARouteInfo", hash_code = 2090635487,
name_list = {"client_ip","client_port","http_ip","http_port"},
type_list = {"string","int","string","int"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1470077324, "GatewayServer.UpdateRouteInfo", {
name = "GatewayServer.UpdateRouteInfo", ns_name = "GatewayServer", rl_name = "UpdateRouteInfo", hash_code = -1470077324,
name_list = {"route_weight","route_info","route_type"},
type_list = {"int","GatewayServer.ConnectInfo","int"},
option_map = {}
})
ALittle.RegStruct(-1355264955, "GatewayServer.NRouteConnected", {
name = "GatewayServer.NRouteConnected", ns_name = "GatewayServer", rl_name = "NRouteConnected", hash_code = -1355264955,
name_list = {"route_type","route_num"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1006278988, "GatewayServer.NUpdateRouteWeight", {
name = "GatewayServer.NUpdateRouteWeight", ns_name = "GatewayServer", rl_name = "NUpdateRouteWeight", hash_code = 1006278988,
name_list = {"route_weight"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-974143213, "GatewayServer.QRouteInfo", {
name = "GatewayServer.QRouteInfo", ns_name = "GatewayServer", rl_name = "QRouteInfo", hash_code = -974143213,
name_list = {"route_type"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-969892976, "GatewayServer.ConnectInfo", {
name = "GatewayServer.ConnectInfo", ns_name = "GatewayServer", rl_name = "ConnectInfo", hash_code = -969892976,
name_list = {"client_ip","client_port","http_ip","http_port"},
type_list = {"string","int","string","int"},
option_map = {}
})
ALittle.RegStruct(888437463, "ALittle.SessionConnectEvent", {
name = "ALittle.SessionConnectEvent", ns_name = "ALittle", rl_name = "SessionConnectEvent", hash_code = 888437463,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})
ALittle.RegStruct(-370290946, "GatewayServer.NUpdateRouteInfo", {
name = "GatewayServer.NUpdateRouteInfo", ns_name = "GatewayServer", rl_name = "NUpdateRouteInfo", hash_code = -370290946,
name_list = {"route_weight","route_info"},
type_list = {"int","GatewayServer.ConnectInfo"},
option_map = {}
})
ALittle.RegStruct(-36908822, "ALittle.SessionDisconnectEvent", {
name = "ALittle.SessionDisconnectEvent", ns_name = "ALittle", rl_name = "SessionDisconnectEvent", hash_code = -36908822,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})

GatewayServer.ModuleRouteManager = Lua.Class(nil, "GatewayServer.ModuleRouteManager")

function GatewayServer.ModuleRouteManager:Ctor()
	___rawset(self, "_route_map", {})
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
	A_SessionSystem:AddEventListener(___all_struct[888437463], self, self.HandleAnySessionConnected)
end

function GatewayServer.ModuleRouteManager:HandleAnySessionConnected(event)
	local session_map = A_SessionSystem:GetSessionMap()
	for connect_key, session in ___pairs(session_map) do
		if session.route_type ~= event.route_type or session.route_num ~= event.route_num then
			local msg = {}
			msg.route_type = session.route_type
			msg.route_num = session.route_num
			event.session:SendMsg(___all_struct[-1355264955], msg)
		end
	end
	for connect_key, session in ___pairs(session_map) do
		if session.route_type ~= event.route_type or session.route_num ~= event.route_num then
			local msg = {}
			msg.route_type = event.route_type
			msg.route_num = event.route_num
			session:SendMsg(___all_struct[-1355264955], msg)
		end
	end
end

function GatewayServer.ModuleRouteManager:HandleAnySessionDisconnected(event)
	local info = self._route_map[event.connect_key]
	if info == nil then
		return
	end
	self._route_map[event.connect_key] = nil
	ALittle.Log("模块断开了, route:" .. ALittle.GetRouteName(event.route_type, event.route_num))
end

function GatewayServer.ModuleRouteManager:HandleUpdateRouteInfo(client, msg)
	ALittle.Log("新的模块连进来了, route:" .. ALittle.GetRouteName(client.route_type, client.route_num))
	local param = {}
	param.route_type = client.route_type
	param.route_weight = msg.route_weight
	param.route_info = msg.route_info
	self._route_map[client:GetID()] = param
end

function GatewayServer.ModuleRouteManager:HandleUpdateRouteWeight(client, msg)
	local info = self._route_map[client:GetID()]
	if info == nil then
		return
	end
	info.route_weight = msg.route_weight
end

function GatewayServer.ModuleRouteManager:GetRouteInfo(route_type)
	local min_weight = 0
	local target = nil
	for connect_key, info in ___pairs(self._route_map) do
		if target == nil or min_weight > info.route_weight then
			target = info
			min_weight = info.route_weight
		end
	end
	return target
end

GatewayServer.g_ModuleRouteManager = GatewayServer.ModuleRouteManager()
function GatewayServer.HandleSession_NUpdateRouteInfo(client, msg)
	GatewayServer.g_ModuleRouteManager:HandleUpdateRouteInfo(client, msg)
	GatewayServer.g_DataRouteManager:HandleUpdateRouteInfo(client, msg)
end

ALittle.RegMsgCallback(-370290946, GatewayServer.HandleSession_NUpdateRouteInfo)
function GatewayServer.HandleNUpdateRouteWeight(client, msg)
	GatewayServer.g_ModuleRouteManager:HandleUpdateRouteWeight(client, msg)
	GatewayServer.g_DataRouteManager:HandleUpdateRouteWeight(client, msg)
end

ALittle.RegMsgCallback(1006278988, GatewayServer.HandleNUpdateRouteWeight)
function GatewayServer.HandleQRouteInfo(client, msg)
	local ___COROUTINE = coroutine.running()
	local route_info = GatewayServer.g_ModuleRouteManager:GetRouteInfo(msg.route_type)
	Lua.Assert(route_info, "没有找到模块类型:" .. msg.route_type)
	local result = {}
	result.client_ip = route_info.route_info.client_ip
	result.client_port = route_info.route_info.client_port
	result.http_ip = route_info.route_info.http_ip
	result.http_port = route_info.route_info.http_port
	return result
end

ALittle.RegHttpCallback("GatewayServer.QRouteInfo", GatewayServer.HandleQRouteInfo)
end