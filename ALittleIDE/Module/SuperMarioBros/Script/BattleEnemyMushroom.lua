-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


SuperMarioBros.EnemyMushroomState = {
	EMS_IDLE = 0,
	EMS_WALK = 1,
	EMS_FALL = 2,
	EMS_DEATH = 3,
}

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.BattleEnemyMushroom = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.BattleEnemyMushroom")

function SuperMarioBros.BattleEnemyMushroom:Ctor()
	___rawset(self, "_vx", 0)
	___rawset(self, "_vy", 0)
	___rawset(self, "_ax", 0)
	___rawset(self, "_ay", 0)
	___rawset(self, "_walk_frame_change", 0.0)
	___rawset(self, "_walk_frame", 1)
end

function SuperMarioBros.BattleEnemyMushroom:Init(row, col)
	self._state = SuperMarioBros.EnemyMushroomState.EMS_IDLE
	self._vx = 0
	self._vy = 0
	self._ax = 0
	self._ay = 0
	self.x = col * SuperMarioBros.TILE_WIDTH
	self.y = row * SuperMarioBros.TILE_HEIGHT
end

function SuperMarioBros.BattleEnemyMushroom.__getter:state()
	return self._state
end

function SuperMarioBros.BattleEnemyMushroom:Death()
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_DEATH then
		return
	end
	self._state = SuperMarioBros.EnemyMushroomState.EMS_DEATH
	local group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopLinear(self._sprite, "height", 5, 100, 0))
	group:AddUpdater(ALittle.LoopLinear(self._sprite, "y", self.height - 5, 100, 0))
	group:Start()
end

function SuperMarioBros.BattleEnemyMushroom:TryWalk()
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_DEATH then
		return
	end
	if self._state ~= SuperMarioBros.EnemyMushroomState.EMS_IDLE then
		return
	end
	self._state = SuperMarioBros.EnemyMushroomState.EMS_WALK
	self._vx = -1
end

function SuperMarioBros.BattleEnemyMushroom:UpdateFrame(frame_time)
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_DEATH then
		return
	end
	self._vx = self._vx + (self._ax * frame_time)
	self._vy = self._vy + (self._ay * frame_time)
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_IDLE then
		self.x = self.x + (self._vx)
		self.y = self.y + (self._vy)
	elseif self._state == SuperMarioBros.EnemyMushroomState.EMS_WALK then
		self.x = self.x + (self._vx)
		local check_right, right_x = g_GCenter.battle_scene:CheckRight(self)
		if check_right then
			self.x = right_x - self.width
			self._vx = -self._vx
		end
		local check_left, left_x = g_GCenter.battle_scene:CheckLeft(self)
		if check_left then
			self.x = left_x
			self._vx = -self._vx
		end
		self.y = self.y + (self._vy)
	elseif self._state == SuperMarioBros.EnemyMushroomState.EMS_FALL then
		self.y = self.y + (self._vy)
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if check_down then
			self._state = SuperMarioBros.EnemyMushroomState.EMS_WALK
			self._vy = 0
			self._ay = 0
			self._vx = -1
			self.y = down_y - self.height
		end
		self.x = self.x + (self._vx)
		local check_right, right_x = g_GCenter.battle_scene:CheckRight(self)
		if check_right then
			self.x = right_x - self.width
			self._vx = -self._vx
		end
		local check_left, left_x = g_GCenter.battle_scene:CheckLeft(self)
		if check_left then
			self.x = left_x
			self._vx = -self._vx
		end
	else
		self.x = self.x + (self._vx)
		self.y = self.y + (self._vy)
	end
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_WALK or self._state == SuperMarioBros.EnemyMushroomState.EMS_IDLE then
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if not check_down then
			self._state = SuperMarioBros.EnemyMushroomState.EMS_FALL
			self._vy = 0
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE
		end
	end
	if self._state == SuperMarioBros.EnemyMushroomState.EMS_WALK then
		self:WalkUpdateFrame(frame_time)
	end
end

function SuperMarioBros.BattleEnemyMushroom:WalkUpdateFrame(frame_time)
	local rate = 0.003
	self._walk_frame_change = self._walk_frame_change + (rate * frame_time * (1 + ALittle.Math_Abs(self._vx)))
	if self._walk_frame_change >= 1 then
		self._walk_frame_change = 0.0
		self._walk_frame = self._walk_frame + (1)
		if self._walk_frame >= 3 then
			self._walk_frame = 1
		end
		self._sprite.col_index = self._walk_frame
	end
end

end