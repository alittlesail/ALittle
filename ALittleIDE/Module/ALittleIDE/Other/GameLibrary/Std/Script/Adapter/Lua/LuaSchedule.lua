-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs


Lua.net_type = {
	HTTP_SUCCEED = 1,
	HTTP_FAILED = 2,
	HTTP_FILE_SUCCEED = 11,
	HTTP_FILE_FAILED = 12,
	HTTP_FILE_PROGRESS = 13,
	TIMER = 21,
	MSG_CONNECT_SUCCEED = 31,
	MSG_CONNECT_FAILED = 32,
	MSG_DISCONNECTED = 33,
	MSG_MESSAGE = 34,
}

assert(ALittle.ISchedule, " extends class:ALittle.ISchedule is nil")
Lua.LuaSchedule = Lua.Class(ALittle.ISchedule, "Lua.LuaSchedule")

function Lua.LuaSchedule:Ctor()
end

function Lua.LuaSchedule:RunInFrame()
	if self._net == nil then
		self._net = net.create()
	end
	while true do
		local event = net.poll(self._net)
		if event == nil then
			break
		end
		self:HandleEvent(event)
	end
end

function Lua.LuaSchedule:Run()
	if self._net == nil then
		self._net = net.create()
	end
	net.timer(self._net, 16)
	while true do
		local event = net.poll(self._net)
		if event == nil then
			break
		end
		if event.type == Lua.net_type.TIMER then
			if self._last_time ~= nil then
				A_LuaLoopSystem:Update(event.time - self._last_time)
				A_LuaWeakLoopSystem:Update(event.time - self._last_time)
			end
			self._last_time = event.time
			net.timer(self._net, 16)
		else
			self:HandleEvent(event)
		end
	end
end

function Lua.LuaSchedule:HandleEvent(event)
	if event.type == Lua.net_type.MSG_MESSAGE then
		self._factory:SetFactory(event.factory)
		ALittle.__ALITTLEAPI_Message(event.id, event.msg_id, event.rpc_id, self._factory)
		net.rfactoryrelease(self._net, event.factory)
	elseif event.type == Lua.net_type.HTTP_SUCCEED then
		ALittle.__ALITTLEAPI_HttpClientSucceed(event.id)
	elseif event.type == Lua.net_type.HTTP_FAILED then
		ALittle.__ALITTLEAPI_HttpClientFailed(event.id, event.error)
	elseif event.type == Lua.net_type.HTTP_FILE_SUCCEED then
		ALittle.__ALITTLEAPI_HttpFileSucceed(event.id)
	elseif event.type == Lua.net_type.HTTP_FILE_FAILED then
		ALittle.__ALITTLEAPI_HttpFileFailed(event.id, event.error)
	elseif event.type == Lua.net_type.HTTP_FILE_PROGRESS then
		ALittle.__ALITTLEAPI_HttpFileProcess(event.id, event.cur_size, event.total_size)
	elseif event.type == Lua.net_type.MSG_CONNECT_SUCCEED then
		ALittle.__ALITTLEAPI_ConnectSucceed(event.id)
	elseif event.type == Lua.net_type.MSG_CONNECT_FAILED then
		ALittle.__ALITTLEAPI_ConnectFailed(event.id)
	elseif event.type == Lua.net_type.MSG_DISCONNECTED then
		ALittle.__ALITTLEAPI_Disconnect(event.id)
	end
end

_G.A_LuaSchedule = Lua.LuaSchedule()
end