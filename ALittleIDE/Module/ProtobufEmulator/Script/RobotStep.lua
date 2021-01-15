-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ProtobufEmulator.RobotStep = Lua.Class(nil, "ProtobufEmulator.RobotStep")

function ProtobufEmulator.RobotStep:Ctor(manager, info)
	___rawset(self, "_manager", manager)
	___rawset(self, "_info", info)
end

function ProtobufEmulator.RobotStep:ReceiveMessage(msg)
end

function ProtobufEmulator.RobotStep:GetMessage()
	return nil
end

function ProtobufEmulator.RobotStep:Execute()
	return true
end

function ProtobufEmulator.RobotStep:Trace()
	local ref = (self).__class
	g_GCenter._grobot:AddLog(ref.__name)
end

function ProtobufEmulator.RobotStep.__getter:info()
	return self._info
end

function ProtobufEmulator.RobotStep:Clear()
end

assert(ProtobufEmulator.RobotStep, " extends class:ProtobufEmulator.RobotStep is nil")
ProtobufEmulator.RobotStepStart = Lua.Class(ProtobufEmulator.RobotStep, "ProtobufEmulator.RobotStepStart")

function ProtobufEmulator.RobotStepStart:Execute()
	return true
end

function ProtobufEmulator.RobotStepStart:Trace()
	g_GCenter._grobot:AddLog("开始")
end

assert(ProtobufEmulator.RobotStep, " extends class:ProtobufEmulator.RobotStep is nil")
ProtobufEmulator.RobotStepReceiveMessage = Lua.Class(ProtobufEmulator.RobotStep, "ProtobufEmulator.RobotStepReceiveMessage")

function ProtobufEmulator.RobotStepReceiveMessage:ReceiveMessage(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	if descriptor == nil then
		return
	end
	local full_name = protobuf.messagedescriptor_fullname(descriptor)
	if full_name ~= self._info.full_name then
		return
	end
	self._message = msg
	local dst_json = protobuf.message_jsonencode(self._message, true, true)
	local error, dst_info = Lua.TCall(ALittle.String_JsonDecode, dst_json)
	if error ~= nil then
		g_GCenter._grobot:AddLog(error)
	else
		for index, log in ___ipairs(self._info.receive_log_list) do
			local dst_field_list = ALittle.String_Split(log.dst_field, ".")
			local dst_field_len = ALittle.List_Len(dst_field_list)
			local dst_temp = dst_info
			local i = 1
			while true do
				if not(i <= dst_field_len) then break end
				local field_name = dst_field_list[i]
				dst_temp = dst_temp[field_name]
				if dst_temp == nil then
					g_GCenter._grobot:AddLog("unique id:" .. self._info.full_name .. " can't find " .. log.dst_field .. ", error field:" .. field_name)
					break
				end
				i = i+(1)
			end
			if dst_temp ~= nil then
				if type(dst_temp) == "table" then
					g_GCenter._grobot:AddLog(self._manager.player_id .. ":[" .. log.dst_field .. "]" .. ALittle.String_JsonEncode(dst_temp))
				else
					g_GCenter._grobot:AddLog(self._manager.player_id .. ":[" .. log.dst_field .. "]" .. ALittle.String_ToString(dst_temp))
				end
			end
		end
	end
	self._manager:NextStep()
end

function ProtobufEmulator.RobotStepReceiveMessage:Trace()
	g_GCenter._grobot:AddLog("等待消息:" .. self._info.full_name)
end

function ProtobufEmulator.RobotStepReceiveMessage:GetMessage()
	return self._message
end

function ProtobufEmulator.RobotStepReceiveMessage:Execute()
	return false
end

assert(ProtobufEmulator.RobotStep, " extends class:ProtobufEmulator.RobotStep is nil")
ProtobufEmulator.RobotStepLog = Lua.Class(ProtobufEmulator.RobotStep, "ProtobufEmulator.RobotStepLog")

function ProtobufEmulator.RobotStepLog:Execute()
	if self._info.log ~= nil then
		g_GCenter._grobot:AddLog(self._manager.player_id .. ":" .. self._info.log)
	end
	return true
end

function ProtobufEmulator.RobotStepLog:Trace()
end

assert(ProtobufEmulator.RobotStep, " extends class:ProtobufEmulator.RobotStep is nil")
ProtobufEmulator.RobotStepSendMessage = Lua.Class(ProtobufEmulator.RobotStep, "ProtobufEmulator.RobotStepSendMessage")

function ProtobufEmulator.RobotStepSendMessage:Ctor(manager, info)
	___rawset(self, "_message", A_LuaProtobufSchedule:CreateMessageByJson(info.full_name, info.message_json))
end

function ProtobufEmulator.RobotStepSendMessage:Execute()
	if self._info.cmd_list[1] == nil then
		self._manager.socket:SendMessage(self._message)
		return true
	end
	local dst_json = protobuf.message_jsonencode(self._message, true, false)
	local error, dst_info = Lua.TCall(ALittle.String_JsonDecode, dst_json)
	if error ~= nil then
		g_GCenter._grobot:AddLog(error)
		return false
	end
	local src_map = {}
	for index, cmd in ___ipairs(self._info.cmd_list) do
		if cmd.src_id == nil then
			g_GCenter._grobot:AddLog("unique id in cmd is null")
			return false
		end
		local src_info = src_map[cmd.src_id]
		if src_info == nil then
			local src_msg = self._manager:GetMessage(cmd.src_id)
			if src_msg == nil then
				g_GCenter._grobot:AddLog("can't find message by unique id:" .. cmd.src_id)
				return false
			end
			local src_json = protobuf.message_jsonencode(src_msg, true, false)
			error, src_info = Lua.TCall(ALittle.String_JsonDecode, src_json)
			if error ~= nil then
				g_GCenter._grobot:AddLog(error)
				return false
			end
			src_map[cmd.src_id] = src_info
		end
		local src_field_list = ALittle.String_Split(cmd.src_field, ".")
		local src_field = nil
		for _, field_name in ___ipairs(src_field_list) do
			src_info = src_info[field_name]
			if src_info == nil then
				g_GCenter._grobot:AddLog("unique id:" .. cmd.src_id .. " can't find " .. cmd.src_field .. ", error field:" .. field_name)
				return false
			end
		end
		local dst_field_list = ALittle.String_Split(cmd.dst_field, ".")
		local dst_field_len = ALittle.List_Len(dst_field_list)
		local dst_temp = dst_info
		local i = 1
		while true do
			if not(i <= dst_field_len) then break end
			local field_name = dst_field_list[i]
			if dst_temp[field_name] == nil then
				g_GCenter._grobot:AddLog("unique id:" .. self._info.full_name .. " can't find " .. cmd.dst_field .. ", error field:" .. field_name)
				return false
			end
			if i < dst_field_len then
				dst_temp = dst_temp[field_name]
			end
			i = i+(1)
		end
		dst_temp[dst_field_list[dst_field_len]] = src_info
	end
	local new_message = A_LuaProtobufSchedule:CreateMessageByStruct(self._info.full_name, dst_info)
	if new_message == nil then
		return false
	end
	self._manager.socket:SendMessage(new_message)
	return true
end

function ProtobufEmulator.RobotStepSendMessage:Trace()
	g_GCenter._grobot:AddLog("发送消息:" .. self._info.full_name)
end

function ProtobufEmulator.RobotStepSendMessage:GetMessage()
	return self._message
end

assert(ProtobufEmulator.RobotStep, " extends class:ProtobufEmulator.RobotStep is nil")
ProtobufEmulator.RobotStepDelay = Lua.Class(ProtobufEmulator.RobotStep, "ProtobufEmulator.RobotStepDelay")

function ProtobufEmulator.RobotStepDelay:Execute()
	self:Clear()
	self._loop = ALittle.LoopTimer(Lua.Bind(self._manager.NextStep, self._manager), self._info.delay_ms)
	self._loop:Start()
	return false
end

function ProtobufEmulator.RobotStepDelay:Trace()
	g_GCenter._grobot:AddLog("延迟:" .. self._info.delay_ms)
end

function ProtobufEmulator.RobotStepDelay:Clear()
	if self._loop ~= nil then
		self._loop:Stop()
		self._loop = nil
	end
end

ProtobufEmulator.RobotStepManager = Lua.Class(nil, "ProtobufEmulator.RobotStepManager")

function ProtobufEmulator.RobotStepManager:Ctor(player_id, socket, file, trace)
	___rawset(self, "_trace", trace)
	___rawset(self, "_player_id", player_id)
	___rawset(self, "_socket", socket)
	___rawset(self, "_step_map", {})
	___rawset(self, "_unique_map", {})
	do
		local step = ProtobufEmulator.RobotStepStart(self, file.start_step)
		self._step_map[file.start_step.id] = step
		___rawset(self, "_cur_step", step)
	end
	for id, info in ___pairs(file.step_map) do
		local step = nil
		if info.type == 1 then
			step = ProtobufEmulator.RobotStepReceiveMessage(self, info)
		elseif info.type == 2 then
			step = ProtobufEmulator.RobotStepSendMessage(self, info)
		elseif info.type == 3 then
			step = ProtobufEmulator.RobotStepDelay(self, info)
		elseif info.type == 4 then
			step = ProtobufEmulator.RobotStepStart(self, info)
			___rawset(self, "_cur_step", step)
		elseif info.type == 5 then
			step = ProtobufEmulator.RobotStepLog(self, info)
		end
		if step ~= nil then
			self._step_map[id] = step
			if info.unique_id ~= nil then
				self._unique_map[info.unique_id] = step
			end
		end
	end
end

function ProtobufEmulator.RobotStepManager.__getter:player_id()
	return self._player_id
end

function ProtobufEmulator.RobotStepManager.__getter:trace()
	return self._trace
end

function ProtobufEmulator.RobotStepManager:GetMessage(unique_id)
	if unique_id == nil then
		return nil
	end
	local step = self._unique_map[unique_id]
	if step == nil then
		return nil
	end
	return step:GetMessage()
end

function ProtobufEmulator.RobotStepManager:Start()
	self:NextStep()
end

function ProtobufEmulator.RobotStepManager:Clear()
	if self._timer ~= nil then
		self._timer:Stop()
		self._timer = nil
	end
	for id, step in ___pairs(self._step_map) do
		step:Clear()
	end
	self._step_map = {}
end

function ProtobufEmulator.RobotStepManager.__getter:socket()
	return self._socket
end

function ProtobufEmulator.RobotStepManager:NextStep()
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
	if self._trace then
		self._cur_step:Trace()
	end
	if not self._cur_step:Execute() then
		return
	end
	self._timer = ALittle.LoopTimer(Lua.Bind(self.NextStep, self), 1)
	self._timer:Start()
end

function ProtobufEmulator.RobotStepManager:ReceiveMessage(msg)
	if self._cur_step == nil then
		return
	end
	self._cur_step:ReceiveMessage(msg)
end

end