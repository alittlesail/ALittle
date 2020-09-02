-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(BattleCity.BattleRole, " extends class:BattleCity.BattleRole is nil")
BattleCity.BattlePlayer = Lua.Class(BattleCity.BattleRole, "BattleCity.BattlePlayer")

function BattleCity.BattlePlayer:Ctor()
	___rawset(self, "_walk_frame", 0)
end

function BattleCity.BattlePlayer:StartBorn(row, col, level, dir, speed)
	self._level = level
	self._dir = dir
	self._speed = speed
	self.x = col * g_GCenter.battle_scene.cell_size
	self.y = row * g_GCenter.battle_scene.cell_size
	self._effect_born.visible = true
	self._effect_born:Play()
	local loop = ALittle.LoopTimer(Lua.Bind(self.HandleBornEnd, self), 1000)
	loop:Start()
end

function BattleCity.BattlePlayer:HandleBornEnd()
	self._sprite.visible = true
	self._effect_born.visible = false
	self:UpdateFrame(0)
	self:UpdateWalk(0)
	self:StartShield()
end

function BattleCity.BattlePlayer:LevelUp()
	if self._level >= 4 then
		return
	end
	self._level = self._level + (1)
	self:UpdateWalk(0)
end

function BattleCity.BattlePlayer:UpdateWalk(frame_time)
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
	if self._walk_frame <= 1 then
		self._sprite.col_index = (self._level - 1) * 2 + 1
	else
		self._sprite.col_index = (self._level - 1) * 2 + 2
	end
end

end