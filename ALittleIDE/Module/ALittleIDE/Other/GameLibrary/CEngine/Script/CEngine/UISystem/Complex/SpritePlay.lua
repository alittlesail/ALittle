-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Sprite, " extends class:ALittle.Sprite is nil")
ALittle.SpritePlay = Lua.Class(ALittle.Sprite, "ALittle.SpritePlay")

function ALittle.SpritePlay:Ctor(ctrl_sys)
	___rawset(self, "_interval", 0)
	___rawset(self, "_play_index", 0)
end

function ALittle.SpritePlay.__setter:interval(value)
	if self._interval == value then
		return
	end
	self._interval = value
	self:Play()
end

function ALittle.SpritePlay.__getter:interval()
	return self._interval
end

function ALittle.SpritePlay:Play()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
	self._play_index = 0
	self._row_index = 1
	self._col_index = 1
	self._play_loop = ALittle.LoopFunction(Lua.Bind(self.PlayUpdate, self), -1, self._interval, 0)
	A_WeakLoopSystem:AddUpdater(self._play_loop)
end

function ALittle.SpritePlay:Stop()
	if self._play_loop ~= nil then
		A_WeakLoopSystem:RemoveUpdater(self._play_loop)
		self._play_loop = nil
	end
end

function ALittle.SpritePlay:PlayUpdate()
	local total_count = self._row_count * self._col_count
	self._play_index = self._play_index + 1
	self._play_index = self._play_index % total_count
	self.row_index = ALittle.Math_Floor(self._play_index / self._row_count) + 1
	self.col_index = self._play_index % self._col_count + 1
end

end