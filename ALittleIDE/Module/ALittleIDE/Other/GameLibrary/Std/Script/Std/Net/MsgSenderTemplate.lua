-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __MsgSenderMap = {}
assert(ALittle.IMsgCommonTemplate, " extends class:ALittle.IMsgCommonTemplate is nil")
ALittle.MsgSenderTemplate = Lua.Class(ALittle.IMsgCommonTemplate, "ALittle.MsgSenderTemplate")

function ALittle.MsgSenderTemplate:Ctor(heartbeat, check_heartbeat, loop_system, callback)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_write_factory", self.__class.__element[2]())
	___rawset(self, "_loop_system", loop_system)
	___rawset(self, "_heartbeat", heartbeat)
	___rawset(self, "_heartbeat_loop", nil)
	___rawset(self, "_check_heartbeat", nil)
	if self._heartbeat ~= nil then
		___rawset(self, "_check_heartbeat", check_heartbeat)
	end
	___rawset(self, "_last_recv_time", 0)
	___rawset(self, "_callback", callback)
end

function ALittle.MsgSenderTemplate:Connect(ip, port)
	local ___COROUTINE = coroutine.running()
	if ip == nil then
		ip = ""
	end
	if port == nil then
		port = 0
	end
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	self._co = ___COROUTINE
	__MsgSenderMap[self._interface:GetID()] = self
	self._ip = ip
	self._port = port
	self._interface:Connect(ip, port)
	return coroutine.yield()
end

function ALittle.MsgSenderTemplate:HandleConnectSucceed()
	self._last_recv_time = 0
	self:SendHeartbeat()
	self:StartHeartbeat()
	local result, reason = ALittle.Coroutine.Resume(self._co, nil)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.MsgSenderTemplate:HandleDisconnect()
	self:StopHeartbeat()
	__MsgSenderMap[self._interface:GetID()] = nil
	self:ClearRPC("连接断开了")
	if self._callback ~= nil then
		self._callback()
	end
end

function ALittle.MsgSenderTemplate:HandleConnectFailed(error)
	__MsgSenderMap[self._interface:GetID()] = nil
	if error == nil then
		error = self._ip .. ":" .. self._port .. "连接失败"
	end
	local result, reason = ALittle.Coroutine.Resume(self._co, error)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.MsgSenderTemplate:Close(reason)
	self:StopHeartbeat()
	self._interface:Close()
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	__MsgSenderMap[self._interface:GetID()] = nil
end

function ALittle.MsgSenderTemplate:SendHeartbeat(max_ms)
	if self._interface:IsConnected() == false then
		return
	end
	self._write_factory:ResetOffset()
	self._write_factory:SetID(0)
	self._write_factory:SetRpcID(0)
	self._interface:SendFactory(self._write_factory)
	if self._check_heartbeat then
		local send_time = ALittle.Time_GetCurTime()
		local default_delta = self._heartbeat / 2
		local delta_time = max_ms
		if delta_time == nil then
			delta_time = default_delta
		end
		if delta_time > default_delta then
			delta_time = default_delta
		end
		self._loop_system:AddTimer(ALittle.Math_Floor(delta_time) * 1000, Lua.Bind(self.CheckHeartbeat, self, send_time, ALittle.Math_Floor(delta_time)))
	end
end

function ALittle.MsgSenderTemplate:CheckHeartbeat(send_time, delta_time)
	local invoke_time = ALittle.Time_GetCurTime()
	local interval_time = invoke_time - send_time
	if interval_time > delta_time + 2 then
		return
	end
	if self._last_recv_time > 0 and send_time - self._last_recv_time > delta_time then
		if self._interface:IsConnected() == false then
			return
		end
		self:Close("心跳检测失败，主动断开连接")
		if self._callback ~= nil then
			self._callback()
		end
	end
end

function ALittle.MsgSenderTemplate:StartHeartbeat()
	if self._heartbeat == nil then
		return
	end
	if self._heartbeat <= 0 then
		return
	end
	if self._heartbeat_loop ~= nil then
		return
	end
	self._heartbeat_loop = self._loop_system:AddTimer(1, Lua.Bind(self.SendHeartbeat, self, nil), -1, self._heartbeat * 1000)
end

function ALittle.MsgSenderTemplate:StopHeartbeat()
	if self._heartbeat_loop == nil then
		return
	end
	self._last_recv_time = 0
	self._loop_system:RemoveTimer(self._heartbeat_loop)
	self._heartbeat_loop = nil
end

function ALittle.__ALITTLEAPI_ConnectSucceed(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleConnectSucceed()
end

function ALittle.__ALITTLEAPI_Disconnect(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleDisconnect()
end

function ALittle.__ALITTLEAPI_ConnectFailed(id)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleConnectFailed(nil)
end

function ALittle.__ALITTLEAPI_Message(id, msg_id, rpc_id, factory)
	local client = __MsgSenderMap[id]
	if client == nil then
		return
	end
	client:HandleMessage(msg_id, rpc_id, factory)
end

end