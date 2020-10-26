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
	PS_FALL = 3,
	PS_SQUAT = 4,
	PS_DEATH = 5,
	PS_FLAG = 6,
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
	___rawset(self, "_win", false)
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
	self._level_1_sprite_right.visible = false
	self._level_1_sprite_left.visible = false
	self._level_2_sprite_right.visible = false
	self._level_2_sprite_left.visible = false
	self._level_3_sprite_right.visible = false
	self._level_3_sprite_left.visible = false
	self.visible = true
	self._state = SuperMarioBros.PlayerState.PS_IDLE
	self._win = false
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

function SuperMarioBros.BattlePlayer:Fire()
end

function SuperMarioBros.BattlePlayer:SmallJump()
	self._state = SuperMarioBros.PlayerState.PS_JUMP
	self._vy = -3
end

function SuperMarioBros.BattlePlayer:Flag()
	if self._state == SuperMarioBros.PlayerState.PS_DEATH then
		return
	end
	if self._state == SuperMarioBros.PlayerState.PS_FLAG then
		return
	end
	self._state = SuperMarioBros.PlayerState.PS_FLAG
	self._vx = 0
	self._vy = 3
	self._ax = 0
	self._ay = 0
	self:UpdateFlag()
end

function SuperMarioBros.BattlePlayer.__getter:win()
	return self._win
end

function SuperMarioBros.BattlePlayer.__setter:win(value)
	self._win = value
end

function SuperMarioBros.BattlePlayer:Death()
	if self._state == SuperMarioBros.PlayerState.PS_DEATH then
		return
	end
	self._state = SuperMarioBros.PlayerState.PS_DEATH
	self._level_1_sprite_right.visible = false
	self._level_1_sprite_left.visible = false
	self._level_2_sprite_right.visible = false
	self._level_2_sprite_left.visible = false
	self._level_3_sprite_right.visible = false
	self._level_3_sprite_left.visible = false
	self._level_1_sprite_right.visible = true
	self.height = self._level_1_sprite_right.height
	self._level_1_sprite_right.col_index = 2
	self._level_1_sprite_right.row_index = 1
	local loop = ALittle.LoopList()
	loop:AddUpdater(ALittle.LoopLinear(self, "y", self.y - SuperMarioBros.TILE_HEIGHT * 5, 500, 0))
	loop:AddUpdater(ALittle.LoopLinear(self, "y", A_UISystem.view_height, 200, 500))
	loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.battle_scene.Restart, g_GCenter.battle_scene), 100))
	loop:Start()
end

function SuperMarioBros.BattlePlayer.__getter:state()
	return self._state
end

function SuperMarioBros.BattlePlayer.__getter:right()
	return self._right
end

function SuperMarioBros.BattlePlayer:Idle()
	self._state = SuperMarioBros.PlayerState.PS_IDLE
	self._vx = 0
	self._vy = 0
	self._ax = 0
	self._ay = 0
	self:UpdateIdle()
end

function SuperMarioBros.BattlePlayer:UpdateFrame(frame_time)
	if self._state == SuperMarioBros.PlayerState.PS_DEATH then
		return
	end
	self._vx = self._vx + (self._ax * frame_time)
	local walk_speedup = A_UISystem.sym_map[106] ~= nil and self._state == SuperMarioBros.PlayerState.PS_WALK
	if walk_speedup then
		if self._vx > SuperMarioBros.PLAYER_MAX_WALK_SPEED_2 then
			self._vx = SuperMarioBros.PLAYER_MAX_WALK_SPEED_2
		elseif self._vx < -SuperMarioBros.PLAYER_MAX_WALK_SPEED_2 then
			self._vx = -SuperMarioBros.PLAYER_MAX_WALK_SPEED_2
		end
	else
		if self._vx > SuperMarioBros.PLAYER_MAX_WALK_SPEED_1 then
			self._vx = SuperMarioBros.PLAYER_MAX_WALK_SPEED_1
		elseif self._vx < -SuperMarioBros.PLAYER_MAX_WALK_SPEED_1 then
			self._vx = -SuperMarioBros.PLAYER_MAX_WALK_SPEED_1
		end
	end
	self._vy = self._vy + (self._ay * frame_time)
	local walk_left = A_UISystem.sym_map[97] ~= nil
	local walk_right = A_UISystem.sym_map[100] ~= nil
	local squat_down = A_UISystem.sym_map[115] ~= nil
	local jump = A_UISystem.sym_map[107] ~= nil
	if self._win then
		walk_left = false
		walk_right = true
		squat_down = false
		jump = false
	end
	if self._state == SuperMarioBros.PlayerState.PS_IDLE then
		self.x = self.x + (self._vx)
		self.y = self.y + (self._vy)
		if walk_left then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
			self._right = false
			self:UpdateIdle()
		elseif walk_right then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
			self._right = true
			self:UpdateIdle()
		end
		if jump then
			self._state = SuperMarioBros.PlayerState.PS_JUMP
			self._vy = -SuperMarioBros.PLAYER_INIT_JUMP_SPEED
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE
			self:UpdateJump()
		elseif squat_down then
			self._state = SuperMarioBros.PlayerState.PS_SQUAT
		end
	elseif self._state == SuperMarioBros.PlayerState.PS_WALK then
		if walk_left then
			self._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
			if self._right then
				self._right = false
				self:UpdateLeftRight()
			end
		elseif walk_right then
			self._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
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
		if jump then
			self._state = SuperMarioBros.PlayerState.PS_JUMP
			self._vy = -SuperMarioBros.PLAYER_INIT_JUMP_SPEED
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE
			self:UpdateJump()
		elseif squat_down then
			self._state = SuperMarioBros.PlayerState.PS_SQUAT
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
		self.y = self.y + (self._vy)
	elseif self._state == SuperMarioBros.PlayerState.PS_JUMP then
		if walk_left then
			self._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
		elseif walk_right then
			self._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE
		else
			if self._vx ~= 0 then
				self._ax = 0
				if self._vx < 0.001 then
					self._vx = 0
				end
			end
		end
		if jump and self._vy < 0 then
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE / 3
		else
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE
		end
		self.y = self.y + (self._vy)
		if self._vy < 0 then
			local check_up, up_y = g_GCenter.battle_scene:CheckUp(self)
			if check_up then
				self._vy = -self._vy
				self.y = up_y
			end
		end
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if check_down then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._vy = 0
			self._ay = 0
			self.y = down_y - self.height
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
	elseif self._state == SuperMarioBros.PlayerState.PS_FALL then
		self.y = self.y + (self._vy)
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if check_down then
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._vy = 0
			self._ay = 0
			self.y = down_y - self.height
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
	elseif self._state == SuperMarioBros.PlayerState.PS_SQUAT then
		if walk_left then
			self._ax = 0
			if self._right then
				self._right = false
				self:UpdateLeftRight()
			end
		elseif walk_right then
			self._ax = 0
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
			end
		end
		if not squat_down then
			self._state = SuperMarioBros.PlayerState.PS_WALK
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
		self.y = self.y + (self._vy)
	else
		self.x = self.x + (self._vx)
		self.y = self.y + (self._vy)
	end
	if self._state == SuperMarioBros.PlayerState.PS_WALK or self._state == SuperMarioBros.PlayerState.PS_IDLE then
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if not check_down then
			self._state = SuperMarioBros.PlayerState.PS_FALL
			self._vy = 0
			self._vx = self._vx / (2)
			self._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE
		end
	end
	if self._state == SuperMarioBros.PlayerState.PS_FLAG then
		local check_down, down_y = g_GCenter.battle_scene:CheckDown(self)
		if check_down then
			self._win = true
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self._vy = 0
			self._ay = 0
			self.y = down_y - self.height
		end
	end
	if self._state == SuperMarioBros.PlayerState.PS_WALK then
		self:WalkUpdateFrame(frame_time)
	elseif self._state == SuperMarioBros.PlayerState.PS_SQUAT then
		self:UpdateSquat()
	elseif self._state == SuperMarioBros.PlayerState.PS_FLAG then
		self:UpdateFlag()
	end
end

function SuperMarioBros.BattlePlayer:UpdateFlag()
	self:UpdateLeftRight()
	if self._level == 1 then
		self._level_1_sprite_right.col_index = 1
		self._level_1_sprite_right.row_index = 2
		self._level_1_sprite_left.col_index = 7
		self._level_1_sprite_left.row_index = 2
	elseif self._level == 2 then
		self._level_2_sprite_right.col_index = 1
		self._level_2_sprite_right.row_index = 2
		self._level_2_sprite_left.col_index = 7
		self._level_2_sprite_left.row_index = 2
	elseif self._level == 3 then
		self._level_3_sprite_right.col_index = 1
		self._level_3_sprite_right.row_index = 2
		self._level_3_sprite_left.col_index = 7
		self._level_3_sprite_left.row_index = 2
	end
end

function SuperMarioBros.BattlePlayer:UpdateJump()
	self:UpdateLeftRight()
	if self._level == 1 then
		self._level_1_sprite_right.col_index = 7
		self._level_1_sprite_right.row_index = 1
		self._level_1_sprite_left.col_index = 1
		self._level_1_sprite_left.row_index = 1
	elseif self._level == 2 then
		self._level_2_sprite_right.col_index = 7
		self._level_2_sprite_right.row_index = 1
		self._level_2_sprite_left.col_index = 1
		self._level_2_sprite_left.row_index = 1
	elseif self._level == 3 then
		self._level_3_sprite_right.col_index = 7
		self._level_3_sprite_right.row_index = 1
		self._level_3_sprite_left.col_index = 1
		self._level_3_sprite_left.row_index = 1
	end
end

function SuperMarioBros.BattlePlayer:UpdateSquat()
	self:UpdateLeftRight()
	if self._level == 2 then
		self._level_2_sprite_right.col_index = 1
		self._level_2_sprite_right.row_index = 1
		self._level_2_sprite_left.col_index = 7
		self._level_2_sprite_left.row_index = 1
	elseif self._level == 3 then
		self._level_3_sprite_right.col_index = 1
		self._level_3_sprite_right.row_index = 1
		self._level_3_sprite_left.col_index = 7
		self._level_3_sprite_left.row_index = 1
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
	local rate = 0.006
	if self._level ~= 1 then
		rate = 0.004
	end
	self._walk_frame_change = self._walk_frame_change + (rate * frame_time * (1 + ALittle.Math_Abs(self._vx)))
	if self._walk_frame_change >= 1 then
		self._walk_frame_change = 0.0
		self._walk_frame = self._walk_frame + (1)
		if self._ax > 0 and self._vx < 0 then
			if self._level == 1 then
				self._walk_frame = 1
				self._level_1_sprite_right.row_index = 1
				self._level_1_sprite_right.col_index = 3
			elseif self._level == 2 then
				self._walk_frame = 1
				self._level_2_sprite_right.row_index = 1
				self._level_2_sprite_right.col_index = 3
			elseif self._level == 3 then
				self._walk_frame = 1
				self._level_3_sprite_right.row_index = 1
				self._level_3_sprite_right.col_index = 3
			end
		elseif self._ax < 0 and self._vx > 0 then
			if self._level == 1 then
				self._walk_frame = 1
				self._level_1_sprite_left.row_index = 1
				self._level_1_sprite_left.col_index = 5
			elseif self._level == 2 then
				self._walk_frame = 1
				self._level_2_sprite_left.row_index = 1
				self._level_2_sprite_left.col_index = 5
			elseif self._level == 3 then
				self._walk_frame = 1
				self._level_3_sprite_left.row_index = 1
				self._level_3_sprite_left.col_index = 5
			end
		elseif self._right then
			if self._level == 1 then
				self._level_1_sprite_right.row_index = 1
				if self._walk_frame == 2 then
					self._level_1_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_1_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_1_sprite_right.col_index = 4
				end
			elseif self._level == 2 then
				self._level_2_sprite_right.row_index = 1
				if self._walk_frame == 2 then
					self._level_2_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_2_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_2_sprite_right.col_index = 4
				end
			elseif self._level == 3 then
				self._level_3_sprite_right.row_index = 1
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
				self._level_1_sprite_left.row_index = 1
				if self._walk_frame == 2 then
					self._level_1_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_1_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_1_sprite_left.col_index = 2
				end
			elseif self._level == 2 then
				self._level_2_sprite_left.row_index = 1
				if self._walk_frame == 2 then
					self._level_2_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_2_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_2_sprite_left.col_index = 2
				end
			elseif self._level == 3 then
				self._level_3_sprite_left.row_index = 1
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