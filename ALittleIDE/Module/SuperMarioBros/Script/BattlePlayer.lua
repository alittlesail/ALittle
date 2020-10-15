-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


SuperMarioBros.PlayerState = {
	PS_IDLE = 0,
	PS_WALK = 1,
	PS_JUMP = 2,
}

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.BattlePlayer = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.BattlePlayer")

function SuperMarioBros.BattlePlayer:Ctor()
	___rawset(self, "_level", 1)
	___rawset(self, "_right", true)
	___rawset(self, "_vx", 0)
	___rawset(self, "_vy", 0)
	___rawset(self, "_ax", 0)
	___rawset(self, "_ay", 0)
	___rawset(self, "_walk_frame_change", 0.0)
	___rawset(self, "_walk_frame", 1)
end

function SuperMarioBros.BattlePlayer:TCtor()
	self._level_1_sprite_right.visible = false
	self._level_1_sprite_left.visible = false
	self._level_2_sprite_right.visible = false
	self._level_2_sprite_left.visible = false
	self._level_3_sprite_right.visible = false
	self._level_3_sprite_left.visible = false
end

function SuperMarioBros.BattlePlayer:Init(row, col, level)
	self._state = SuperMarioBros.PlayerState.PS_IDLE
	self._right = true
	self._vx = 0
	self._vy = 0
	self._ax = 0
	self._ay = 0
	self._level = level
	if self._level == 1 then
		self._level_1_sprite_right.visible = true
		self.height = self._level_1_sprite_right.height
		self._level_1_sprite_right.col_index = 1
		self._level_1_sprite_right.row_index = 1
		self.x = col * SuperMarioBros.TILE_WIDTH
		self.y = row * SuperMarioBros.TILE_HEIGHT - self._level_1_sprite_right.height
	elseif self._level == 2 then
		self._level_2_sprite_right.visible = true
		self.height = self._level_2_sprite_right.height
		self._level_2_sprite_right.col_index = 2
		self.x = col * SuperMarioBros.TILE_WIDTH
		self.y = row * SuperMarioBros.TILE_HEIGHT - self._level_2_sprite_right.height
	elseif self._level == 3 then
		self._level_3_sprite_right.visible = true
		self.height = self._level_3_sprite_right.height
		self._level_3_sprite_right.col_index = 2
		self.x = col * SuperMarioBros.TILE_WIDTH
		self.y = row * SuperMarioBros.TILE_HEIGHT - self._level_3_sprite_right.height
	end
end

function SuperMarioBros.BattlePlayer:Jump()
	if self._state ~= SuperMarioBros.PlayerState.PS_WALK and self._state ~= SuperMarioBros.PlayerState.PS_IDLE then
		return
	end
	self._state = SuperMarioBros.PlayerState.PS_JUMP
	self._vy = 0.5
end

function SuperMarioBros.BattlePlayer:Fire()
end

function SuperMarioBros.BattlePlayer:UpdateFrame(frame_time)
	self._vx = self._vx + (self._ax * frame_time)
	if self._vx > SuperMarioBros.PLAYER_MAX_WALK_SPEED then
		self._vx = SuperMarioBros.PLAYER_MAX_WALK_SPEED
	elseif self._vx < -SuperMarioBros.PLAYER_MAX_WALK_SPEED then
		self._vx = -SuperMarioBros.PLAYER_MAX_WALK_SPEED
	end
	self._vy = self._vy + (self._ay * frame_time)
	self.x = self.x + (self._vx)
	self.y = self.y + (self._vy)
	local walk_left = A_UISystem.sym_map[97] ~= nil
	local walk_right = A_UISystem.sym_map[100] ~= nil
	local jump = A_UISystem.sym_map[107] ~= nil
	if self._state == SuperMarioBros.PlayerState.PS_IDLE then
		if walk_left then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._ax = -SuperMarioBros.PLAYER_INIT_SPEED_RATE
			self._right = false
			self:UpdateIdle()
		elseif walk_right then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._ax = SuperMarioBros.PLAYER_INIT_SPEED_RATE
			self._right = true
			self:UpdateIdle()
		end
	elseif self._state == SuperMarioBros.PlayerState.PS_WALK then
		if walk_left then
			self._ax = -SuperMarioBros.PLAYER_INIT_SPEED_RATE
			if self._right then
				self._right = false
				self:UpdateLeftRight()
			end
		elseif walk_right then
			self._ax = SuperMarioBros.PLAYER_INIT_SPEED_RATE
			if not self._right then
				self._right = true
				self:UpdateLeftRight()
			end
		else
			if self._vx ~= 0 then
				self._ax = 0
				self._vx = self._vx * (0.1)
				if self._vx < 0.001 then
					self._vx = 0
				end
			else
				self._state = SuperMarioBros.PlayerState.PS_IDLE
				self:UpdateIdle()
			end
		end
	end
	if self._state == SuperMarioBros.PlayerState.PS_WALK then
		self:WalkUpdateFrame(frame_time)
	end
end

function SuperMarioBros.BattlePlayer:UpdateIdle()
	self:UpdateLeftRight()
	if self._level == 1 then
		self._level_1_sprite_right.col_index = 1
		self._level_1_sprite_right.row_index = 1
		self._level_1_sprite_left.col_index = 7
		self._level_1_sprite_left.row_index = 1
	elseif self._level == 2 then
		self._level_2_sprite_right.col_index = 2
		self._level_2_sprite_right.row_index = 1
		self._level_2_sprite_left.col_index = 6
		self._level_2_sprite_left.row_index = 1
	elseif self._level == 3 then
		self._level_3_sprite_right.col_index = 2
		self._level_3_sprite_right.row_index = 1
		self._level_3_sprite_left.col_index = 6
		self._level_3_sprite_left.row_index = 1
	end
end

function SuperMarioBros.BattlePlayer:UpdateLeftRight()
	if self._level == 1 then
		self._level_1_sprite_right.visible = self._right
		self._level_1_sprite_left.visible = not self._right
	elseif self._level == 2 then
		self._level_2_sprite_right.visible = self._right
		self._level_2_sprite_left.visible = not self._right
	elseif self._level == 3 then
		self._level_3_sprite_right.visible = self._right
		self._level_3_sprite_left.visible = not self._right
	end
end

function SuperMarioBros.BattlePlayer:WalkUpdateFrame(frame_time)
	self._walk_frame_change = self._walk_frame_change + (0.006 * frame_time * (1 + ALittle.Math_Abs(self._vx)))
	if self._walk_frame_change >= 1 then
		self._walk_frame_change = 0.0
		self._walk_frame = self._walk_frame + (1)
		if self._ax > 0 and self._vx < 0 then
			if self._level == 1 then
				self._walk_frame = 1
				self._level_1_sprite_right.col_index = 3
			elseif self._level == 2 then
				self._walk_frame = 1
				self._level_2_sprite_right.col_index = 3
			elseif self._level == 3 then
				self._walk_frame = 1
				self._level_3_sprite_right.col_index = 3
			end
		elseif self._ax < 0 and self._vx > 0 then
			if self._level == 1 then
				self._walk_frame = 1
				self._level_1_sprite_left.col_index = 5
			elseif self._level == 2 then
				self._walk_frame = 1
				self._level_2_sprite_left.col_index = 5
			elseif self._level == 3 then
				self._walk_frame = 1
				self._level_3_sprite_left.col_index = 5
			end
		elseif self._right then
			if self._level == 1 then
				if self._walk_frame == 2 then
					self._level_1_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_1_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_1_sprite_right.col_index = 4
				end
			elseif self._level == 2 then
				if self._walk_frame == 2 then
					self._level_2_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_2_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_2_sprite_right.col_index = 4
				end
			elseif self._level == 3 then
				if self._walk_frame == 2 then
					self._level_3_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_3_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_3_sprite_right.col_index = 4
				end
			end
		else
			if self._level == 1 then
				if self._walk_frame == 2 then
					self._level_1_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_1_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_1_sprite_left.col_index = 2
				end
			elseif self._level == 2 then
				if self._walk_frame == 2 then
					self._level_2_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_2_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_2_sprite_left.col_index = 2
				end
			elseif self._level == 3 then
				if self._walk_frame == 2 then
					self._level_3_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_3_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_3_sprite_left.col_index = 2
				end
			end
		end
	end
end

end