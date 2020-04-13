
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = GetAllStruct()

RegStruct(976782632, "LogServer.LogEventInfo", {
name = "LogServer.LogEventInfo", ns_name = "LogServer", rl_name = "LogEventInfo", hash_code = 976782632,
name_list = {"account_id","main_type","sub_type","res_type","res_id","res_num","res_count","param_1","param_2","param_3","param_4","param_5","param_string","create_time","log_time"},
type_list = {"int","int","int","int","int","int","int","int","int","int","int","int","string","int","int"},
option_map = {index="account_id,main_type,sub_type,create_time"}
})
RegStruct(200159280, "LogServer.EmptyResult", {
name = "LogServer.EmptyResult", ns_name = "LogServer", rl_name = "EmptyResult", hash_code = 200159280,
name_list = {},
type_list = {},
option_map = {}
})
RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

LogEventMainType = {
	LEMT_OPS = 1,
}

LogEventSubType = {
	LEST_OPS_ADDRES = 1,
}

LogEventSystem = Class(nil, "ALittle.LogEventSystem")

function LogEventSystem:Ctor()
	___rawset(self, "_init", false)
	___rawset(self, "_list", {})
	___rawset(self, "_count", 0)
end

function LogEventSystem:HandleSessionConnected(event)
	if event.route_num ~= RouteType.RT_LOG and event.route_num ~= RouteNum.RN_DEFAULT then
		return
	end
	self._session = event.session
	self:Flush()
end
LogEventSystem.HandleSessionConnected = CoWrap(LogEventSystem.HandleSessionConnected)

function LogEventSystem:HandleSessionDisconnected(event)
	if event.route_num ~= RouteType.RT_LOG and event.route_num ~= RouteNum.RN_DEFAULT then
		return
	end
	self._session = nil
end

function LogEventSystem:Flush()
	for index, info in ___ipairs(self._list) do
		self:Send(info)
	end
	self._list = {}
	self._count = 0
end

function LogEventSystem:Send(info)
	local error, result = IMsgCommon.InvokeRPC(976782632, self._session, info)
	if error ~= nil then
		Warn("日志发送失败:" .. error .. " 数据:" .. json.encode(info))
	end
end

function LogEventSystem:SendLogEvent(info)
	if not self._init then
		A_SessionSystem:AddConnectSession(RouteType.RT_LOG, RouteNum.RN_DEFAULT)
		A_SessionSystem:AddEventListener(___all_struct[888437463], self, self.HandleSessionConnected)
		A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleSessionDisconnected)
		self._init = true
	end
	if self._session == nil then
		Push(self._list, info)
		self._count = self._count + 1
		if self._count > 1000 then
			Warn("消息队列太大，移除掉第一个, 数据:" .. json.encode(self._list[1]))
			table.remove(self._list, 1)
			self._count = self._count - 1
		end
	else
		self:Send(info)
	end
end
LogEventSystem.SendLogEvent = CoWrap(LogEventSystem.SendLogEvent)

_G.A_LogEventSystem = LogEventSystem()
