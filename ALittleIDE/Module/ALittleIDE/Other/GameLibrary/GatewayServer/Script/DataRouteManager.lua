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

ALittle.RegStruct(1723229779, "GatewayServer.DataRouteInfo", {
name = "GatewayServer.DataRouteInfo", ns_name = "GatewayServer", rl_name = "DataRouteInfo", hash_code = 1723229779,
name_list = {"route_type","route_num","route_weight","route_info","session"},
type_list = {"int","int","int","GatewayServer.ConnectInfo","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-969892976, "GatewayServer.ConnectInfo", {
name = "GatewayServer.ConnectInfo", ns_name = "GatewayServer", rl_name = "ConnectInfo", hash_code = -969892976,
name_list = {"client_ip","client_port","http_ip","http_port"},
type_list = {"string","int","string","int"},
option_map = {}
})
ALittle.RegStruct(-36908822, "ALittle.SessionDisconnectEvent", {
name = "ALittle.SessionDisconnectEvent", ns_name = "ALittle", rl_name = "SessionDisconnectEvent", hash_code = -36908822,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})

GatewayServer.DataRouteManager = Lua.Class(nil, "GatewayServer.DataRouteManager")

function GatewayServer.DataRouteManager:Ctor()
	___rawset(self, "_route_map", {})
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleAnySessionDisconnected)
end

function GatewayServer.DataRouteManager:HandleAnySessionDisconnected(event)
	if event.route_type ~= 2 then
		return
	end
	local key = event.route_type .. "_" .. event.route_num
	self._route_map[key] = nil
end

function GatewayServer.DataRouteManager:HandleUpdateRouteInfo(client, msg)
	if client.route_type ~= 2 then
		return
	end
	local info = {}
	info.session = client
	info.route_type = client.route_type
	info.route_num = client.route_num
	info.route_weight = msg.route_weight
	info.route_info = msg.route_info
	local key = info.route_type .. "_" .. info.route_num
	self._route_map[key] = info
end

function GatewayServer.DataRouteManager:HandleUpdateRouteWeight(client, msg)
	if client.route_type ~= 2 then
		return
	end
	local key = client.route_type .. "_" .. client.route_num
	local info = self._route_map[key]
	if info == nil then
		return
	end
	info.route_weight = msg.route_weight
end

function GatewayServer.DataRouteManager:GetRouteInfo()
	local min_weight = 0
	local target = nil
	for key, info in ___pairs(self._route_map) do
		if target == nil or min_weight > info.route_weight then
			target = info
			min_weight = info.route_weight
		end
	end
	return target
end

function GatewayServer.DataRouteManager:FindRouteInfo(route_num)
	local key = 2 .. "_" .. route_num
	return self._route_map[key]
end

GatewayServer.g_DataRouteManager = GatewayServer.DataRouteManager()
end