-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


SuperMarioBros.LifeMushroomState = {
	LMS_BORN = 0,
	LMS_WALK = 1,
}

assert(ALittle.Image, " extends class:ALittle.Image is nil")
SuperMarioBros.BattleLifeMushroom = Lua.Class(ALittle.Image, "SuperMarioBros.BattleLifeMushroom")

function SuperMarioBros.BattleLifeMushroom:Ctor()
	___rawset(self, "_level", 1)
	___rawset(self, "_vx", 0)
	___rawset(self, "_vy", 0)
	___rawset(self, "_ax", 0)
	___rawset(self, "_ay", 0)
	___rawset(self, "_born_y", 0)
end

function SuperMarioBros.BattleLifeMushroom:Born(row, col)
	self._state = SuperMarioBros.LifeMushroomState.LMS_BORN
	self._vx = 0
	self._vy = 0
	self._ax = 0
	self._ay = 0
	self.x = col * SuperMarioBros.TILE_WIDTH
	self.y = row * SuperMarioBros.TILE_HEIGHT
	self._born_y = self.y - SuperMarioBros.TILE_HEIGHT
end

function SuperMarioBros.BattleLifeMushroom:UpdateFrame(frame_time)
	self._vx = self._vx + (self._ax * frame_time)
	self._vy = self._vy + (self._ay * frame_time)
	if self._state == SuperMarioBros.LifeMushroomState.LMS_BORN then
		self.y = self.y - (0.03 * frame_time)
		if self.y <= self._born_y then
			self.y = self._born_y
			self._state = SuperMarioBros.LifeMushroomState.LMS_WALK
			self._vx = 1
			self._ay = 0.01
		end
	elseif self._state == SuperMarioBros.LifeMushroomState.LMS_WALK then
		self.y = self.y + (self._vy)
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if check_down then
			self.y = down_y - self.height
			self._vy = 0
		end
		self.x = self.x + (self._vx)
		local check_right, right_x = g_GCenter.battle_scene:CheckRight(self)
		if check_right then
			self.x = right_x - self.width
		end
		local check_left, left_x = g_GCenter.battle_scene:CheckLeft(self)
		if check_left then
			self.x = left_x
		end
	end
end

end