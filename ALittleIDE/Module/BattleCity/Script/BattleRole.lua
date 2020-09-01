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
	___rawset(self, "_frame", 0)
	___rawset(self, "_speed", 0)
end

function BattleCity.BattleRole:TCtor()
	self._sprite.visible = false
	self._effect_born.visible = false
	self._effect_shield.visible = false
	self._effect_explosion.visible = false
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

function BattleCity.BattleRole:StartBorn(row, col, level, dir, speed)
	self._level = level
	self._dir = dir
	self._speed = speed
	self.x = col * g_GCenter.battle_scene.cell_size
	self.y = row * g_GCenter.battle_scene.cell_size
	self._effect_born.visible = true
	self._effect_born:Play()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleShow, self), 1000)
	loop:Start()
end

function BattleCity.BattleRole:StartExplosion()
	self._sprite.visible = false
	self._effect_explosion.visible = true
	self._effect_explosion:Play()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleExplosionEnd, self), 1000)
	loop:Start()
end

function BattleCity.BattleRole:Walk(dir, frame_time)
	local walk = (self._dir == dir)
	self._dir = dir
	self:UpdateSprite(frame_time)
	if self._dir == BattleCity.DirType.DT_UP then
		local col = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local col_ex = self.x - col * g_GCenter.battle_scene.cell_size > 2
		local cur_row = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local y = self.y - frame_time * self._speed
		if y <= 0 then
			y = 0
		end
		local next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size)
		local target = self.y
		local row = cur_row
		while true do
			if not(row >= next_row) then break end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 1) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 2) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 3) then
				break
			end
			if col_ex and not g_GCenter.battle_scene:CanWalkByMap(row, col + 4) then
				break
			end
			target = row * g_GCenter.battle_scene.cell_size
			row = row+(-1)
		end
		if target < y then
			target = y
		end
		self.y = target
		return
	end
	if self._dir == BattleCity.DirType.DT_DOWN then
		local bottom = self.y + self.height
		local col = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local col_ex = self.x - col * g_GCenter.battle_scene.cell_size > 2
		local cur_row = ALittle.Math_Floor(bottom / g_GCenter.battle_scene.cell_size)
		local y = bottom + frame_time * self._speed
		if y >= g_GCenter.battle_scene.map_size then
			y = g_GCenter.battle_scene.map_size
		end
		local next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size)
		local target = bottom
		local row = cur_row
		while true do
			if not(row <= next_row) then break end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 1) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 2) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col + 3) then
				break
			end
			if col_ex and not g_GCenter.battle_scene:CanWalkByMap(row, col + 4) then
				break
			end
			target = (row + 1) * g_GCenter.battle_scene.cell_size
			row = row+(1)
		end
		if target > y then
			target = y
		end
		self.y = target - self.height
		return
	end
	if self._dir == BattleCity.DirType.DT_LEFT then
		local row = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local row_ex = self.y - row * g_GCenter.battle_scene.cell_size > 2
		local cur_col = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
		local x = self.x - frame_time * self._speed
		if x <= 0 then
			x = 0
		end
		local next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size)
		local target = self.x
		local col = cur_col
		while true do
			if not(col >= next_col) then break end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 1, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 2, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 3, col) then
				break
			end
			if row_ex and not g_GCenter.battle_scene:CanWalkByMap(row + 4, col) then
				break
			end
			target = col * g_GCenter.battle_scene.cell_size
			col = col+(-1)
		end
		if target < x then
			target = x
		end
		self.x = target
		return
	end
	if self._dir == BattleCity.DirType.DT_RIGHT then
		local right = self.x + self.width
		local row = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
		local row_ex = self.y - row * g_GCenter.battle_scene.cell_size > 2
		local cur_col = ALittle.Math_Floor(right / g_GCenter.battle_scene.cell_size)
		local x = right + frame_time * self._speed
		if x >= g_GCenter.battle_scene.map_size then
			x = g_GCenter.battle_scene.map_size
		end
		local next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size)
		local target = right
		local col = cur_col
		while true do
			if not(col <= next_col) then break end
			if not g_GCenter.battle_scene:CanWalkByMap(row, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 1, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 2, col) then
				break
			end
			if not g_GCenter.battle_scene:CanWalkByMap(row + 3, col) then
				break
			end
			if row_ex and not g_GCenter.battle_scene:CanWalkByMap(row + 4, col) then
				break
			end
			target = (col + 1) * g_GCenter.battle_scene.cell_size
			col = col+(1)
		end
		if target > x then
			target = x
		end
		self.x = target - self.width
		return
	end
end

function BattleCity.BattleRole:UpdateSprite(frame_time)
	if self._dir == BattleCity.DirType.DT_UP then
		self._sprite.row_index = 1
	elseif self._dir == BattleCity.DirType.DT_RIGHT then
		self._sprite.row_index = 2
	elseif self._dir == BattleCity.DirType.DT_DOWN then
		self._sprite.row_index = 3
	elseif self._dir == BattleCity.DirType.DT_LEFT then
		self._sprite.row_index = 4
	end
	self._frame = self._frame + (0.01 * frame_time)
	if self._frame > 2 then
		self._frame = 0
	end
	if self._frame <= 1 then
		self._sprite.col_index = (self._level - 1) * 2 + 1
	else
		self._sprite.col_index = (self._level - 1) * 2 + 2
	end
end

function BattleCity.BattleRole:HandleShow()
	self._sprite.visible = true
	self:UpdateSprite(0)
	self._effect_born.visible = false
	self._effect_shield.visible = true
	self._effect_shield:Play()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleShieldStop, self), 5000)
	loop:Start()
end

function BattleCity.BattleRole:HandleExplosionEnd()
	g_GCenter.battle_scene:RoleDeath(self)
end

function BattleCity.BattleRole:HandleShieldStop()
	self._effect_shield.visible = false
	self._effect_shield:Stop()
end

function BattleCity.BattleRole:Clear()
	self._effect_born:Stop()
	self._effect_shield:Stop()
	self._effect_explosion:Stop()
end

end