-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.FramePlay = Lua.Class(ALittle.DisplayLayout, "ALittle.FramePlay")

function ALittle.FramePlay:Ctor(ctrl_sys)
	___rawset(self, "_interval", 0)
	___rawset(self, "_play_child_index", 0)
	___rawset(self, "_play_loop_count", 1)
	___rawset(self, "_play_loop_index", 0)
	___rawset(self, "_auto_play", false)
end

function ALittle.FramePlay.__setter:base_y(value)
	self._base_y = value
end

function ALittle.FramePlay.__getter:base_y()
	if self._base_y ~= nil then
		return self._base_y
	end
	return self.height
end

function ALittle.FramePlay.__setter:auto_play(value)
	self._auto_play = value
	if value then
		self:Play()
	end
end

function ALittle.FramePlay.__getter:auto_play()
	return self._auto_play
end

function ALittle.FramePlay:AddChild(child, index)
	if ALittle.DisplayLayout.AddChild(self, child, index) == false then
		return false
	end
	child.visible = false
	return true
end

function ALittle.FramePlay.__setter:interval(value)
	if self._interval == value then
		return
	end
	self._interval = value
	if self._play_loop ~= nil then
		self:Play()
	end
end

function ALittle.FramePlay.__getter:interval()
	return self._interval
end

function ALittle.FramePlay.__setter:play_loop_count(value)
	if self._play_loop_count == value then
		return
	end
	self._play_loop_count = value
	if self._play_loop ~= nil then
		self:Play()
	end
end

function ALittle.FramePlay.__getter:play_loop_count()
	return self._play_loop_count
end

function ALittle.FramePlay:IsPlaying()
	return self._play_loop ~= nil
end

function ALittle.FramePlay:Play()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
	self._play_child_index = 0
	self._play_loop_index = 0
	self:HideAllChild()
	self._play_loop = ALittle.LoopFunction(Lua.Bind(self.PlayUpdateLoop, self), -1, self._interval, 0)
	A_WeakLoopSystem:AddUpdater(self._play_loop)
end

function ALittle.FramePlay:Stop()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
end

function ALittle.FramePlay:HideAllChild()
	for index, child in ___ipairs(self._childs) do
		child.visible = false
		if (child).__class == ALittle.FramePlay then
			child:HideAllChild()
		end
	end
end

function ALittle.FramePlay:ShowAllChild()
	for index, child in ___ipairs(self._childs) do
		child.visible = true
		if (child).__class == ALittle.FramePlay then
			child:ShowAllChild()
		end
	end
end

function ALittle.FramePlay:PlayUpdateLoop()
	self:PlayUpdate()
end

function ALittle.FramePlay:PlayUpdate()
	if self._child_count == 0 or (self._play_loop_count > 0 and self._play_loop_index > self._play_loop_count) then
		if self._play_loop ~= nil then
			self._play_loop:SetCompleted()
			self._play_loop = nil
		end
		return false
	end
	if self._play_child_index > 0 then
		local child = self._childs[self._play_child_index]
		if (child).__class == ALittle.FramePlay then
			if child:PlayUpdate() then
				return true
			end
		end
		child = self._childs[self._play_child_index]
		if child ~= nil then
			child.visible = false
		end
	end
	self._play_child_index = self._play_child_index + 1
	if self._play_child_index > self._child_count then
		self._play_child_index = 1
		if self._play_loop_count > 0 then
			self._play_loop_index = self._play_loop_index + 1
			if self._play_loop_index >= self._play_loop_count then
				if self._play_loop ~= nil then
					self._play_loop:SetCompleted()
					self._play_loop = nil
				end
				return false
			end
		end
	end
	self._childs[self._play_child_index].visible = true
	local child = self._childs[self._play_child_index]
	if (child).__class == ALittle.FramePlay then
		child._play_loop_index = 0
		child._play_child_index = 0
		if child:PlayUpdate() then
			return true
		end
	end
	return true
end

end