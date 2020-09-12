-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SuperMarioBros.StageScene = Lua.Class(ALittle.DisplayLayout, "SuperMarioBros.StageScene")

function SuperMarioBros.StageScene:Show(world, subworld)
	self.visible = true
	self._score.text = g_GCenter.player_data.score
	self._coin.text = 0
	self._stage.text = g_GCenter.player_data.world .. "-" .. g_GCenter.player_data.subworld
	self._time.text = 0
	self._stage_text.text = self._stage.text
	self._life_text.text = g_GCenter.player_data.life
	if self._loop ~= nil then
		self._loop:Stop()
	end
	self._loop = ALittle.LoopTimer(Lua.Bind(self.ShowTimeOut, self, world, subworld), 1000)
	self._loop:Start()
end

function SuperMarioBros.StageScene:ShowTimeOut(world, subworld)
	g_GCenter.battle_scene:Show(world, subworld)
	self:Hide()
end

function SuperMarioBros.StageScene:Hide()
	self.visible = false
end

end