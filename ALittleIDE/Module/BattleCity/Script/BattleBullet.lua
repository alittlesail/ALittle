-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleBullet = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleBullet")

function BattleCity.BattleBullet:Ctor()
	___rawset(self, "_speed", 0.2)
end

function BattleCity.BattleBullet:TCtor()
	self._effect_explosion.visible = false
end

function BattleCity.BattleBullet:Init(dir, role, speed)
	self._dir = dir
	self._role = role
	self._alive = true
	self._speed = speed
	if self._dir == BattleCity.DirType.DT_UP then
		self._bullet.col_index = 1
	elseif self._dir == BattleCity.DirType.DT_RIGHT then
		self._bullet.col_index = 2
	elseif self._dir == BattleCity.DirType.DT_DOWN then
		self._bullet.col_index = 3
	else
		self._bullet.col_index = 4
	end
end

function BattleCity.BattleBullet.__getter:role()
	return self._role
end

function BattleCity.BattleBullet.__getter:alive()
	return self._alive
end

function BattleCity.BattleBullet:UpdateFrame(frame_time)
	local explosion = false
	if self._alive then
		if self._dir == BattleCity.DirType.DT_UP then
			self.y = self.y - (self._speed * frame_time)
			local check_collision, check_explosion = g_GCenter.battle_scene:BulletCollisionByEntity(self, self.x, self.y, self.x + self.width, self.y + self.height)
			if check_collision then
				if check_explosion then
					explosion = true
				else
					self:BulletEnd()
				end
			else
				local row = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
				local col_min = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
				local col_max = ALittle.Math_Floor((self.x + self.width - 1) / g_GCenter.battle_scene.cell_size)
				if g_GCenter.battle_scene:BulletCollisionByMap(row, col_min, true, self._dir) then
					explosion = true
				end
				if g_GCenter.battle_scene:BulletCollisionByMap(row, col_max, false, self._dir) then
					explosion = true
				end
				if self.y <= 0 then
					explosion = true
				end
			end
		elseif self._dir == BattleCity.DirType.DT_RIGHT then
			self.x = self.x + (self._speed * frame_time)
			local check_collision, check_explosion = g_GCenter.battle_scene:BulletCollisionByEntity(self, self.x, self.y, self.x + self.width, self.y + self.height)
			if check_collision then
				if check_explosion then
					explosion = true
				else
					self:BulletEnd()
				end
			else
				local row_min = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
				local row_max = ALittle.Math_Floor((self.y + self.height - 1) / g_GCenter.battle_scene.cell_size)
				local col = ALittle.Math_Floor((self.x + self.width) / g_GCenter.battle_scene.cell_size)
				if g_GCenter.battle_scene:BulletCollisionByMap(row_min, col, true, self._dir) then
					explosion = true
				end
				if g_GCenter.battle_scene:BulletCollisionByMap(row_max, col, false, self._dir) then
					explosion = true
				end
				if self.x + self.width >= g_GCenter.battle_scene.map_size then
					explosion = true
				end
			end
		elseif self._dir == BattleCity.DirType.DT_DOWN then
			self.y = self.y + (self._speed * frame_time)
			local check_collision, check_explosion = g_GCenter.battle_scene:BulletCollisionByEntity(self, self.x, self.y, self.x + self.width, self.y + self.height)
			if check_collision then
				if check_explosion then
					explosion = true
				else
					self:BulletEnd()
				end
			else
				local row = ALittle.Math_Floor((self.y + self.height) / g_GCenter.battle_scene.cell_size)
				local col_min = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
				local col_max = ALittle.Math_Floor((self.x + self.width - 1) / g_GCenter.battle_scene.cell_size)
				if g_GCenter.battle_scene:BulletCollisionByMap(row, col_min, true, self._dir) then
					explosion = true
				end
				if g_GCenter.battle_scene:BulletCollisionByMap(row, col_max, false, self._dir) then
					explosion = true
				end
				if self.y + self.height >= g_GCenter.battle_scene.map_size then
					explosion = true
				end
			end
		else
			self.x = self.x - (self._speed * frame_time)
			local check_collision, check_explosion = g_GCenter.battle_scene:BulletCollisionByEntity(self, self.x, self.y, self.x + self.width, self.y + self.height)
			if check_collision then
				if check_explosion then
					explosion = true
				else
					self:BulletEnd()
				end
			else
				local row_min = ALittle.Math_Floor(self.y / g_GCenter.battle_scene.cell_size)
				local row_max = ALittle.Math_Floor((self.y + self.height - 1) / g_GCenter.battle_scene.cell_size)
				local col = ALittle.Math_Floor(self.x / g_GCenter.battle_scene.cell_size)
				if g_GCenter.battle_scene:BulletCollisionByMap(row_min, col, true, self._dir) then
					explosion = true
				end
				if g_GCenter.battle_scene:BulletCollisionByMap(row_max, col, false, self._dir) then
					explosion = true
				end
				if self.x <= 0 then
					explosion = true
				end
			end
		end
	else
		if not self._effect_explosion:IsPlaying() then
			self:BulletEnd()
		end
	end
	if explosion then
		self:BulletExpision()
	end
end

function BattleCity.BattleBullet:BulletExpision()
	self._alive = false
	self._bullet.visible = false
	self._effect_explosion.visible = true
	self._effect_explosion:Play()
end

function BattleCity.BattleBullet:BulletEnd()
	self._alive = false
	self._effect_explosion:Stop()
	self._effect_explosion.visible = false
	local loop = ALittle.LoopTimer(Lua.Bind(g_GCenter.battle_scene.BulletDeath, g_GCenter.battle_scene, self), 0)
	loop:Start()
end

end