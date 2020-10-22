-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


Emulator.RobotStep = Lua.Class(nil, "Emulator.RobotStep")

function Emulator.RobotStep:Ctor(manager, info)
	___rawset(self, "_manager", manager)
	___rawset(self, "_info", info)
end

function Emulator.RobotStep:ReceiveMessage(msg)
	return true
end

function Emulator.RobotStep:Execute()
	return true
end

function Emulator.RobotStep.__getter:info()
	return self._info
end

function Emulator.RobotStep:Clear()
end

function Emulator.RobotStep:Print()
	ALittle.Log(self._info.id, self._info.type)
end

assert(Emulator.RobotStep, " extends class:Emulator.RobotStep is nil")
Emulator.RobotStepStart = Lua.Class(Emulator.RobotStep, "Emulator.RobotStepStart")

assert(Emulator.RobotStep, " extends class:Emulator.RobotStep is nil")
Emulator.RobotStepReceiveMessage = Lua.Class(Emulator.RobotStep, "Emulator.RobotStepReceiveMessage")

function Emulator.RobotStepReceiveMessage:Ctor(manager, info)
	___rawset(self, "_full_name", info.full_name)
end

function Emulator.RobotStepReceiveMessage:ReceiveMessage(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	if descriptor == nil then
		return false
	end
	local full_name = protobuf.messagedescriptor_fullname(descriptor)
	if full_name ~= self._full_name then
		return false
	end
	self._message = msg
	return true
end

function Emulator.RobotStepReceiveMessage:Execute()
	return false
end

assert(Emulator.RobotStep, " extends class:Emulator.RobotStep is nil")
Emulator.RobotStepLog = Lua.Class(Emulator.RobotStep, "Emulator.RobotStepLog")

function Emulator.RobotStepLog:Ctor(manager, info)
end

function Emulator.RobotStepLog:Execute()
	g_GCenter._grobot:AddLog(self._info.log)
	return true
end

assert(Emulator.RobotStep, " extends class:Emulator.RobotStep is nil")
Emulator.RobotStepSendMessage = Lua.Class(Emulator.RobotStep, "Emulator.RobotStepSendMessage")

function Emulator.RobotStepSendMessage:Ctor(manager, info)
	___rawset(self, "_message", A_LuaProtobufSchedule:CreateMessageByJson(info.full_name, info.message_json))
end

function Emulator.RobotStepSendMessage:Execute()
	self._manager.socket:SendMessage(self._message)
	return true
end

assert(Emulator.RobotStep, " extends class:Emulator.RobotStep is nil")
Emulator.RobotStepDelayMessage = Lua.Class(Emulator.RobotStep, "Emulator.RobotStepDelayMessage")

function Emulator.RobotStepDelayMessage:Ctor(manager, info)
end

function Emulator.RobotStepDelayMessage:Execute()
	self:Clear()
	self._loop = ALittle.LoopTimer(Lua.Bind(self._manager.NextStep, self._manager), self._info.delay_ms)
	self._loop:Start()
	return false
end

function Emulator.RobotStepDelayMessage:Clear()
	if self._loop ~= nil then
		self._loop:Stop()
		self._loop = nil
	end
end

Emulator.RobotStepManager = Lua.Class(nil, "Emulator.RobotStepManager")

function Emulator.RobotStepManager:Ctor(socket, file)
	___rawset(self, "_socket", socket)
	___rawset(self, "_step_map", {})
	do
		local step = Emulator.RobotStepStart(self, file.start_step)
		self._step_map[file.start_step.id] = step
		___rawset(self, "_cur_step", step)
	end
	for id, info in ___pairs(file.step_map) do
		if info.type == Emulator.RobotStepType.RST_RECEIVE_MESSAGE then
			local step = Emulator.RobotStepReceiveMessage(self, info)
			self._step_map[id] = step
		elseif info.type == Emulator.RobotStepType.RST_SEND_MESSAGE then
			local step = Emulator.RobotStepSendMessage(self, info)
			self._step_map[id] = step
		elseif info.type == Emulator.RobotStepType.RST_DELAY then
			local step = Emulator.RobotStepDelayMessage(self, info)
			self._step_map[id] = step
		elseif info.type == Emulator.RobotStepType.RST_START then
			local step = Emulator.RobotStepStart(self, info)
			self._step_map[id] = step
			___rawset(self, "_cur_step", step)
		elseif info.type == Emulator.RobotStepType.RST_LOG then
			local step = Emulator.RobotStepLog(self, info)
			self._step_map[id] = step
		end
	end
end

function Emulator.RobotStepManager:Start()
	self:NextStep()
end

function Emulator.RobotStepManager:Clear()
	if self._timer ~= nil then
		self._timer:Stop()
		self._timer = nil
	end
	for id, step in ___pairs(self._step_map) do
		step:Clear()
	end
	self._step_map = {}
end

function Emulator.RobotStepManager.__getter:socket()
	return self._socket
end

function Emulator.RobotStepManager:NextStep()
	if self._timer ~= nil then
		self._timer:Stop()
		self._timer = nil
	end
	if self._cur_step == nil then
		return
	end
	local next_id = self._cur_step.info.next_id
	if next_id == nil then
		return
	end
	self._cur_step = self._step_map[next_id]
	if self._cur_step == nil then
		return
	end
	if not self._cur_step:Execute() then
		return
	end
	self._timer = ALittle.LoopTimer(Lua.Bind(self.NextStep, self), 1)
	self._timer:Start()
end

function Emulator.RobotStepManager:ReceiveMessage(msg)
	if self._cur_step == nil then
		return
	end
	if not self._cur_step:ReceiveMessage(msg) then
		return
	end
	self:NextStep()
end

end