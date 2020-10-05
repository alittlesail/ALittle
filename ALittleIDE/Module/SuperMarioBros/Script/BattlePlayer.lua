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
	___rawset(self, "_lr_speed", 0)
	___rawset(self, "_lr_speed_rate", 0)
	___rawset(self, "_ud_speed", 0)
	___rawset(self, "_ud_speed_rate", 0)
	___rawset(self, "_jump_height", 0)
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
	self._lr_speed = 0
	self._lr_speed_rate = 0
	self._ud_speed = 0
	self._ud_speed_rate = 0
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
	self._ud_speed_rate = 0.5
end

function SuperMarioBros.BattlePlayer:Fire()
end

function SuperMarioBros.BattlePlayer:UpdateFrame(frame_time)
	local walk_left = A_UISystem.sym_map[97] ~= nil
	local walk_right = A_UISystem.sym_map[100] ~= nil
	local jump = A_UISystem.sym_map[107] ~= nil
	if jump then
		if self._state == SuperMarioBros.PlayerState.PS_JUMP then
			self._ud_speed_rate = self._ud_speed_rate - (0.001)
			self._ud_speed = self._ud_speed + (self._ud_speed_rate * frame_time)
			if self._jump_height < SuperMarioBros.PLAYER_MAX_JUMP_HEIGHT then
				local delta = self._ud_speed
				self._jump_height = self._jump_height + (delta)
				if self._jump_height > SuperMarioBros.PLAYER_MAX_JUMP_HEIGHT then
					delta = SuperMarioBros.PLAYER_MAX_JUMP_HEIGHT - self._jump_height
					self._jump_height = SuperMarioBros.PLAYER_MAX_JUMP_HEIGHT
				end
				self.y = self.y - (delta)
			end
		elseif self._state == SuperMarioBros.PlayerState.PS_WALK or self._state == SuperMarioBros.PlayerState.PS_IDLE then
			self._state = SuperMarioBros.PlayerState.PS_JUMP
			self._ud_speed_rate = 0.01
			self._ud_speed = self._ud_speed + (self._ud_speed_rate * frame_time)
			self._jump_height = self._ud_speed
			self.y = self.y - (self._ud_speed)
		end
	elseif walk_left or walk_right then
		if self._state == SuperMarioBros.PlayerState.PS_JUMP then
			if self._level == 1 then
				if self._right then
					self._level_1_sprite_right.col_index = 7
				else
					self._level_1_sprite_left.col_index = 1
				end
			elseif self._level == 2 then
				if self._right then
					self._level_2_sprite_right.col_index = 7
				else
					self._level_2_sprite_left.col_index = 1
				end
			elseif self._level == 3 then
				if self._right then
					self._level_3_sprite_right.col_index = 7
				else
					self._level_3_sprite_left.col_index = 1
				end
			end
		elseif self._state == SuperMarioBros.PlayerState.PS_WALK or self._state == SuperMarioBros.PlayerState.PS_IDLE then
			if walk_right then
				if not self._right then
					self._right = true
					self:UpdateLeftRight()
				end
				if self._lr_speed_rate < 0 then
					self._lr_speed_rate = self._lr_speed_rate + (0.03)
				else
					self._lr_speed_rate = self._lr_speed_rate + (0.001)
				end
				if self._lr_speed_rate > SuperMarioBros.PLAYER_MAX_SPEED_RATE then
					self._lr_speed_rate = SuperMarioBros.PLAYER_MAX_SPEED_RATE
				end
			else
				if self._right then
					self._right = false
					self:UpdateLeftRight()
				end
				if self._lr_speed_rate >= 0 then
					self._lr_speed_rate = self._lr_speed_rate - (0.03)
				else
					self._lr_speed_rate = self._lr_speed_rate - (0.001)
				end
				if self._lr_speed_rate < -SuperMarioBros.PLAYER_MAX_SPEED_RATE then
					self._lr_speed_rate = -SuperMarioBros.PLAYER_MAX_SPEED_RATE
				end
			end
			self._lr_speed = self._lr_speed + (self._lr_speed_rate * frame_time)
			if self._lr_speed > SuperMarioBros.PLAYER_MAX_WALK_SPEED then
				self._lr_speed = SuperMarioBros.PLAYER_MAX_WALK_SPEED
			elseif self._lr_speed < -SuperMarioBros.PLAYER_MAX_WALK_SPEED then
				self._lr_speed = -SuperMarioBros.PLAYER_MAX_WALK_SPEED
			end
			self.x = self.x + (self._lr_speed)
			self._state = SuperMarioBros.PlayerState.PS_WALK
			self:WalkUpdateFrame(frame_time)
		end
		return
	end
	if self._state == SuperMarioBros.PlayerState.PS_WALK then
		if self._lr_speed > 0 then
			self._lr_speed = self._lr_speed - (0.01 * frame_time)
			if self._lr_speed >= 0 then
				self.x = self.x + (self._lr_speed)
				self:WalkUpdateFrame(frame_time)
				return
			end
		elseif self._lr_speed < 0 then
			self._lr_speed = self._lr_speed + (0.01 * frame_time)
			if self._lr_speed < 0 then
				self.x = self.x + (self._lr_speed)
				self:WalkUpdateFrame(frame_time)
				return
			end
		end
		self._lr_speed = 0
		self._state = SuperMarioBros.PlayerState.PS_IDLE
		if self._level == 1 then
			if self._right then
				self._level_1_sprite_right.col_index = 1
			else
				self._level_1_sprite_left.col_index = 7
			end
		elseif self._level == 2 then
			if self._right then
				self._level_2_sprite_right.col_index = 2
			else
				self._level_2_sprite_left.col_index = 6
			end
		elseif self._level == 3 then
			if self._right then
				self._level_3_sprite_right.col_index = 2
			else
				self._level_3_sprite_left.col_index = 6
			end
		end
	elseif self._state == SuperMarioBros.PlayerState.PS_JUMP then
		if self._level == 1 then
			if self._right then
				self._level_1_sprite_right.col_index = 7
			else
				self._level_1_sprite_left.col_index = 1
			end
		elseif self._level == 2 then
			if self._right then
				self._level_2_sprite_right.col_index = 7
			else
				self._level_2_sprite_left.col_index = 1
			end
		elseif self._level == 3 then
			if self._right then
				self._level_3_sprite_right.col_index = 7
			else
				self._level_3_sprite_left.col_index = 1
			end
		end
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
	self._walk_frame_change = self._walk_frame_change + (0.006 * frame_time * (1 + ALittle.Math_Abs(self._lr_speed)))
	if self._walk_frame_change >= 1 then
		self._walk_frame_change = 0.0
		self._walk_frame = self._walk_frame + (1)
		if self._right then
			if self._level == 1 then
				if self._lr_speed < 0 then
					self._walk_frame = 1
					self._level_1_sprite_right.col_index = 3
				elseif self._walk_frame == 2 then
					self._level_1_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_1_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_1_sprite_right.col_index = 4
				end
			elseif self._level == 2 then
				if self._lr_speed < 0 then
					self._walk_frame = 1
					self._level_2_sprite_right.col_index = 3
				elseif self._walk_frame == 2 then
					self._level_2_sprite_right.col_index = 5
				elseif self._walk_frame == 3 then
					self._level_2_sprite_right.col_index = 6
				else
					self._walk_frame = 1
					self._level_2_sprite_right.col_index = 4
				end
			elseif self._level == 3 then
				if self._lr_speed < 0 then
					self._walk_frame = 1
					self._level_3_sprite_right.col_index = 3
				elseif self._walk_frame == 2 then
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
				if self._lr_speed >= 0 then
					self._walk_frame = 1
					self._level_1_sprite_left.col_index = 5
				elseif self._walk_frame == 2 then
					self._level_1_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_1_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_1_sprite_left.col_index = 2
				end
			elseif self._level == 2 then
				if self._lr_speed >= 0 then
					self._walk_frame = 1
					self._level_2_sprite_left.col_index = 5
				elseif self._walk_frame == 2 then
					self._level_2_sprite_left.col_index = 4
				elseif self._walk_frame == 3 then
					self._level_2_sprite_left.col_index = 3
				else
					self._walk_frame = 1
					self._level_2_sprite_left.col_index = 2
				end
			elseif self._level == 3 then
				if self._lr_speed >= 0 then
					self._walk_frame = 1
					self._level_3_sprite_left.col_index = 5
				elseif self._walk_frame == 2 then
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