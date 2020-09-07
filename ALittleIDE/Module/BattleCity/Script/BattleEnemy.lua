-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(BattleCity.BattleRole, " extends class:BattleCity.BattleRole is nil")
BattleCity.BattleEnemy = Lua.Class(BattleCity.BattleRole, "BattleCity.BattleEnemy")

function BattleCity.BattleEnemy:Ctor()
	___rawset(self, "_flash", false)
	___rawset(self, "_walk_frame", 0)
	___rawset(self, "_flash_frame", 0)
	___rawset(self, "_changed_frame", 0)
	___rawset(self, "_fire_frame", 0)
end

function BattleCity.BattleEnemy:StartBorn(row, col, level, dir, flash)
	self._level = level
	self._dir = dir
	self._flash = flash
	if self._level == 1 then
		self._speed = 0.08
	elseif self._level == 2 then
		self._speed = 0.1
	else
		self._speed = 0.06
	end
	self._fire_count = 0
	self.x = col * g_GCenter.battle_scene.cell_size
	self.y = row * g_GCenter.battle_scene.cell_size
	self._sprite.visible = false
	self._effect_explosion.visible = false
	self._effect_explosion:Stop()
	self._effect_born.visible = true
	self._effect_born:Play()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleBornEnd, self), 1000)
	loop:Start()
end

function BattleCity.BattleEnemy:HandleBornEnd()
	self._sprite.visible = true
	self._effect_born.visible = false
	self:UpdateFrame(0)
	self:UpdateWalk(0)
end

function BattleCity.BattleEnemy:BeAttack()
	if self._flash then
		self._flash = false
		g_GCenter.battle_scene:GenerateItem()
		return false
	end
	self:StartExplosion()
	return true
end

function BattleCity.BattleEnemy.__getter:is_enemy()
	return true
end

function BattleCity.BattleEnemy:UpdateFrame(frame_time)
	if self.alive and not g_GCenter.battle_scene:IsEnemyStopping() then
		self._changed_frame = self._changed_frame + (frame_time * 0.001)
		if self._changed_frame >= 2 then
			self._changed_frame = 0
		end
		if self._changed_frame > 1 and ALittle.Math_RandomInt(1, 100) > 95 then
			self:Walk(ALittle.Math_RandomInt(BattleCity.DirType.DT_UP, BattleCity.DirType.DT_RIGHT), frame_time)
		else
			if not self:Walk(self._dir, frame_time) then
				self._changed_frame = 1
			end
		end
		self._fire_frame = self._fire_frame + (frame_time * 0.001)
		if self._fire_frame >= 2 then
			self._fire_frame = 0
		end
		if self._fire_frame > 1 and ALittle.Math_RandomInt(1, 100) > 90 then
			self:Fire()
		end
	end
	self:UpdateSpriteCol(frame_time)
end

function BattleCity.BattleEnemy:UpdateWalk(frame_time)
	if self._dir == BattleCity.DirType.DT_UP then
		self._sprite.row_index = 1
	elseif self._dir == BattleCity.DirType.DT_RIGHT then
		self._sprite.row_index = 2
	elseif self._dir == BattleCity.DirType.DT_DOWN then
		self._sprite.row_index = 3
	elseif self._dir == BattleCity.DirType.DT_LEFT then
		self._sprite.row_index = 4
	end
	self._walk_frame = self._walk_frame + (0.01 * frame_time)
	if self._walk_frame > 2 then
		self._walk_frame = 0
	end
	self:UpdateSpriteCol(frame_time)
end

function BattleCity.BattleEnemy:UpdateSpriteCol(frame_time)
	self._flash_frame = self._flash_frame + (0.005 * frame_time)
	if self._flash_frame > 2 then
		self._flash_frame = 0
	end
	if self._flash and self._flash_frame <= 1 then
		if self._walk_frame <= 1 then
			self._sprite.col_index = (self._level - 1) * 4 + 2 + 1
		else
			self._sprite.col_index = (self._level - 1) * 4 + 2 + 2
		end
	else
		if self._walk_frame <= 1 then
			self._sprite.col_index = (self._level - 1) * 4 + 1
		else
			self._sprite.col_index = (self._level - 1) * 4 + 2
		end
	end
end

end