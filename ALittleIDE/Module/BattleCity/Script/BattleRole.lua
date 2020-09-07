-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleRole = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleRole")

function BattleCity.BattleRole:Ctor()
	___rawset(self, "_level", 1)
	___rawset(self, "_dir", 1)
	___rawset(self, "_bullet_total", 1)
	___rawset(self, "_fire_count", 0)
	___rawset(self, "_speed", 0)
	___rawset(self, "_bullet_speed", 0.2)
end

function BattleCity.BattleRole:TCtor()
	self._sprite.visible = false
	self._effect_born.visible = false
	self._effect_shield.visible = false
	self._effect_explosion.visible = false
end

function BattleCity.BattleRole.__getter:is_enemy()
	return false
end

function BattleCity.BattleRole.__getter:alive()
	if self._effect_born.visible then
		return false
	end
	if self._effect_explosion.visible then
		return false
	end
	return true
end

function BattleCity.BattleRole.__getter:explosion()
	return self._effect_explosion.visible
end

function BattleCity.BattleRole.__getter:dir()
	return self._dir
end

function BattleCity.BattleRole.__getter:level()
	return self._level
end

function BattleCity.BattleRole:StartExplosion()
	self._sprite.visible = false
	self._effect_explosion.visible = true
	self._effect_explosion:Play()
	if self._effect_explosion_loop ~= nil then
		self._effect_explosion_loop:Stop()
	end
	self._effect_explosion_loop = ALittle.LoopTimer(Lua.Bind(self.HandleExplosionEnd, self), 1000)
	self._effect_explosion_loop:Start()
end

function BattleCity.BattleRole:StartShield()
	self._effect_shield.visible = true
	self._effect_shield:Play()
	if self._effect_shield_loop ~= nil then
		self._effect_shield_loop:Stop()
	end
	self._effect_shield_loop = ALittle.LoopTimer(Lua.Bind(self.HandleShieldStop, self), 5000)
	self._effect_shield_loop:Start()
end

function BattleCity.BattleRole:UpdateFrame(frame_time)
end

function BattleCity.BattleRole:UpdateWalk(frame_time)
end

function BattleCity.BattleRole:BeAttack()
	return true
end

function BattleCity.BattleRole:Fire()
	if self._fire_count >= self._bullet_total then
		return
	end
	self._fire_count = self._fire_count + (1)
	g_GCenter.battle_scene:FireBullet(self, self._bullet_speed)
end

function BattleCity.BattleRole:WalkImpl(dir, frame_time, adjust)
	if dir == BattleCity.DirType.DT_UP then
		local col_min = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local col_max = ALittle.Math_Floor((self.x + self.width - 1) / g_GCenter.battle_scene.cell_size)
		local cur_row = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local y = self.y - frame_time * self._speed
		if y <= 0 then
			y = 0
		end
		local next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size)
		local target = self.y
		local break_row = cur_row
		local row = cur_row
		while true do
			if not(row >= next_row) then break end
			local failed = false
			local col = col_min
			while true do
				if not(col <= col_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
					break_row = row
					failed = true
					break
				end
				col = col+(1)
			end
			if failed then
				break
			end
			target = row * g_GCenter.battle_scene.cell_size
			row = row+(-1)
		end
		if target < y then
			target = y
		end
		if not g_GCenter.battle_scene:CanWalkByEntity(self, self.x, target, self.x + self.width, target + self.height) then
			return false
		end
		if self.y == target then
			if not adjust then
				return false
			end
			local col = col_min + 1
			while true do
				if not(col < col_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(break_row, col) then
					return false
				end
				col = col+(1)
			end
			local left_check = g_GCenter.battle_scene:CanWalkByMap(break_row, col_min)
			local right_check = g_GCenter.battle_scene:CanWalkByMap(break_row, col_max)
			if not left_check then
				return self:WalkImpl(BattleCity.DirType.DT_RIGHT, frame_time, false)
			elseif not right_check then
				return self:WalkImpl(BattleCity.DirType.DT_LEFT, frame_time, false)
			end
			return false
		end
		self.y = target
		return true
	end
	if dir == BattleCity.DirType.DT_DOWN then
		local col_min = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local col_max = ALittle.Math_Floor((self.x + self.width - 1) / g_GCenter.battle_scene.cell_size)
		local bottom = self.y + self.height
		local cur_row = ALittle.Math_Floor(bottom / g_GCenter.battle_scene.cell_size)
		local y = bottom + frame_time * self._speed
		if y >= g_GCenter.battle_scene.map_size then
			y = g_GCenter.battle_scene.map_size
		end
		local next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size)
		local target = bottom
		local break_row = cur_row
		local row = cur_row
		while true do
			if not(row <= next_row) then break end
			local failed = false
			local col = col_min
			while true do
				if not(col <= col_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
					break_row = row
					failed = true
					break
				end
				col = col+(1)
			end
			if failed then
				break
			end
			target = (row + 1) * g_GCenter.battle_scene.cell_size
			row = row+(1)
		end
		if target > y then
			target = y
		end
		if not g_GCenter.battle_scene:CanWalkByEntity(self, self.x, target - self.height, self.x + self.width, target) then
			return false
		end
		if self.y == target - self.height then
			if not adjust then
				return false
			end
			local col = col_min + 1
			while true do
				if not(col < col_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(break_row, col) then
					return false
				end
				col = col+(1)
			end
			local left_check = g_GCenter.battle_scene:CanWalkByMap(break_row, col_min)
			local right_check = g_GCenter.battle_scene:CanWalkByMap(break_row, col_max)
			if not left_check then
				return self:WalkImpl(BattleCity.DirType.DT_RIGHT, frame_time, false)
			elseif not right_check then
				return self:WalkImpl(BattleCity.DirType.DT_LEFT, frame_time, false)
			end
			return false
		end
		self.y = target - self.height
		return true
	end
	if dir == BattleCity.DirType.DT_LEFT then
		local row_min = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local row_max = ALittle.Math_Floor((self.y + self.height - 1) / g_GCenter.battle_scene.cell_size)
		local cur_col = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local x = self.x - frame_time * self._speed
		if x <= 0 then
			x = 0
		end
		local next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size)
		local target = self.x
		local break_col = cur_col
		local col = cur_col
		while true do
			if not(col >= next_col) then break end
			local failed = false
			local row = row_min
			while true do
				if not(row <= row_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
					break_col = col
					failed = true
					break
				end
				row = row+(1)
			end
			if failed then
				break
			end
			target = col * g_GCenter.battle_scene.cell_size
			col = col+(-1)
		end
		if target < x then
			target = x
		end
		if not g_GCenter.battle_scene:CanWalkByEntity(self, target, self.y, target + self.width, self.y + self.height) then
			return false
		end
		if self.x == target then
			if not adjust then
				return false
			end
			local row = row_min + 1
			while true do
				if not(row < row_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, break_col) then
					return false
				end
				row = row+(1)
			end
			local up_check = g_GCenter.battle_scene:CanWalkByMap(row_min, break_col)
			local down_check = g_GCenter.battle_scene:CanWalkByMap(row_max, break_col)
			if not up_check then
				return self:WalkImpl(BattleCity.DirType.DT_DOWN, frame_time, false)
			elseif not down_check then
				return self:WalkImpl(BattleCity.DirType.DT_UP, frame_time, false)
			end
			return false
		end
		self.x = target
		return true
	end
	if dir == BattleCity.DirType.DT_RIGHT then
		local row_min = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local row_max = ALittle.Math_Floor((self.y + self.height - 1) / g_GCenter.battle_scene.cell_size)
		local right = self.x + self.width
		local cur_col = ALittle.Math_Floor(right / g_GCenter.battle_scene.cell_size)
		local x = right + frame_time * self._speed
		if x >= g_GCenter.battle_scene.map_size then
			x = g_GCenter.battle_scene.map_size
		end
		local next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size)
		local target = right
		local break_col = cur_col
		local col = cur_col
		while true do
			if not(col <= next_col) then break end
			local failed = false
			local row = row_min
			while true do
				if not(row <= row_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
					break_col = col
					failed = true
					break
				end
				row = row+(1)
			end
			if failed then
				break
			end
			target = (col + 1) * g_GCenter.battle_scene.cell_size
			col = col+(1)
		end
		if target > x then
			target = x
		end
		if not g_GCenter.battle_scene:CanWalkByEntity(self, target - self.width, self.y, target, self.y + self.height) then
			return false
		end
		if self.x == target - self.width then
			if not adjust then
				return false
			end
			local row = row_min + 1
			while true do
				if not(row < row_max) then break end
				if not g_GCenter.battle_scene:CanWalkByMap(row, break_col) then
					return false
				end
				row = row+(1)
			end
			local up_check = g_GCenter.battle_scene:CanWalkByMap(row_min, break_col)
			local down_check = g_GCenter.battle_scene:CanWalkByMap(row_max, break_col)
			if not up_check then
				return self:WalkImpl(BattleCity.DirType.DT_DOWN, frame_time, false)
			elseif not down_check then
				return self:WalkImpl(BattleCity.DirType.DT_UP, frame_time, false)
			end
			return false
		end
		self.x = target - self.width
		return true
	end
	return false
end

function BattleCity.BattleRole:Walk(dir, frame_time)
	self._dir = dir
	self:UpdateWalk(frame_time)
	return self:WalkImpl(dir, frame_time, true)
end

function BattleCity.BattleRole:HandleExplosionEnd()
	local loop = ALittle.LoopTimer(Lua.Bind(g_GCenter.battle_scene.RoleDeath, g_GCenter.battle_scene, self), 0)
	loop:Start()
end

function BattleCity.BattleRole:HandleShieldStop()
	self._effect_shield.visible = false
	self._effect_shield:Stop()
end

function BattleCity.BattleRole:AddBullet()
	if self._fire_count <= 0 then
		return
	end
	self._fire_count = self._fire_count - (1)
end

function BattleCity.BattleRole:Clear()
	self._effect_born:Stop()
	self._effect_shield:Stop()
	self._effect_explosion:Stop()
end

end