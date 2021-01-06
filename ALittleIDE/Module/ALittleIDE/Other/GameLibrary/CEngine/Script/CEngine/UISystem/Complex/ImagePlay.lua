-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.ImagePlay = Lua.Class(ALittle.DisplayLayout, "ALittle.ImagePlay")

function ALittle.ImagePlay:Ctor(ctrl_sys)
	___rawset(self, "_interval", 0)
	___rawset(self, "_play_index", 0)
end

function ALittle.ImagePlay.__setter:path_list(value)
	self._path_list = value
	self:RemoveAllChild()
	if self._path_list == nil then
		if self._play_loop ~= nil then
			A_WeakLoopSystem:RemoveUpdater(self._play_loop)
			self._play_loop = nil
		end
		return
	end
	for k, v in ___ipairs(self._path_list) do
		local image = ALittle.Image(self._ctrl_sys)
		image.width_type = 4
		image.height_type = 4
		image.texture_name = v
		image.visible = false
		self:AddChild(image)
	end
	self:Play()
end

function ALittle.ImagePlay.__getter:path_list()
	return self._path_list
end

function ALittle.ImagePlay.__setter:interval(value)
	if self._interval == value then
		return
	end
	self._interval = value
	self:Play()
end

function ALittle.ImagePlay.__getter:interval()
	return self._interval
end

function ALittle.ImagePlay:Play()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
	if self._path_list == nil then
		return
	end
	self._play_index = 0
	for k, v in ___ipairs(self._childs) do
		v.visible = false
	end
	self._play_loop = ALittle.LoopFunction(Lua.Bind(self.PlayUpdate, self), -1, self._interval, 0)
	A_WeakLoopSystem:AddUpdater(self._play_loop)
end

function ALittle.ImagePlay:Stop()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
end

function ALittle.ImagePlay:PlayUpdate()
	if self._child_count == 0 then
		return
	end
	if self._play_index > 0 then
		self._childs[self._play_index].visible = false
	end
	self._play_index = self._play_index + 1
	if self._play_index > self._child_count then
		self._play_index = 1
	end
	self._childs[self._play_index].visible = true
end

end