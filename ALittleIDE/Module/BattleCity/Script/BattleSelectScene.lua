-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleSelectScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleSelectScene")

function BattleCity.BattleSelectScene:Show(stage)
	self.visible = true
	self._stage_num.text = stage
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self._quad_up.y = -self._quad_up.height
	self._quad_down.y = A_UISystem.view_height
	self._stage_container.visible = true
	self._anti_loop = ALittle.LoopList()
	local group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopLinear(self._quad_up, "y", 0, 1000, 0))
	group:AddUpdater(ALittle.LoopLinear(self._quad_down, "y", 0, 1000, 0))
	self._anti_loop:AddUpdater(group)
	self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.battle_scene.Show, g_GCenter.battle_scene, stage), 0))
	self._anti_loop:AddUpdater(ALittle.LoopAttribute(self, "visible", false, 0))
	self._anti_loop:Start()
end

end