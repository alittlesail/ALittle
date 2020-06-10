
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSLoading = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSLoading")

function OPSLoading:Play()
	if self._loop_1 == nil then
		self._loop_1 = ALittle.LoopFunction(ALittle.Bind(self.Update, self, self._c1, self._c1.x + self._c1.width / 2, self._c1.y + self._c1.height / 2), -1, 20, 1)
		if self._c1._user_data == nil then
			local user_data = {}
			user_data.flag = true
			self._c1._user_data = user_data
		end
		A_LoopSystem:AddUpdater(self._loop_1)
	end
	if self._loop_2 == nil then
		self._loop_2 = ALittle.LoopFunction(ALittle.Bind(self.Update, self, self._c2, self._c2.x + self._c2.width / 2, self._c2.y + self._c2.height / 2), -1, 20, 1)
		if self._c2._user_data == nil then
			local user_data = {}
			user_data.flag = true
			self._c2._user_data = user_data
		end
		A_LoopSystem:AddUpdater(self._loop_2)
	end
	if self._loop_3 == nil then
		self._loop_3 = ALittle.LoopFunction(ALittle.Bind(self.Update, self, self._c3, self._c3.x + self._c3.width / 2, self._c3.y + self._c3.height / 2), -1, 20, 1)
		if self._c3._user_data == nil then
			local user_data = {}
			user_data.flag = true
			self._c3._user_data = user_data
		end
		A_LoopSystem:AddUpdater(self._loop_3)
	end
end

function OPSLoading:Stop()
	if self._loop_1 ~= nil then
		A_LoopSystem:RemoveUpdater(self._loop_1)
		self._loop_1 = nil
	end
	if self._loop_2 ~= nil then
		A_LoopSystem:RemoveUpdater(self._loop_2)
		self._loop_2 = nil
	end
	if self._loop_3 ~= nil then
		A_LoopSystem:RemoveUpdater(self._loop_3)
		self._loop_3 = nil
	end
end

function OPSLoading:Update(object, center_x, center_y)
	local user_data = object._user_data
	local width = user_data.width
	if width == nil then
		width = object.width
	end
	if user_data.flag then
		width = width + 2
	else
		width = width - 2
	end
	user_data.width = width
	if width < 2 then
		user_data.flag = true
	elseif width > 35 then
		user_data.flag = false
	end
	if width > 30 then
		width = 30
	end
	object.width = width
	object.height = width
	object.x = center_x - width / 2
	object.y = center_y - width / 2
end

