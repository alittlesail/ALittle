-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleSelectScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleSelectScene")

function BattleCity.BattleSelectScene:Ctor()
	___rawset(self, "_stage", 1)
end

function BattleCity.BattleSelectScene:TCtor()
end

function BattleCity.BattleSelectScene.__getter:stage()
	return self._stage
end

function BattleCity.BattleSelectScene:Show(stage)
	if stage == nil then
		self._stage = 1
	else
		self._stage = stage
	end
	self.visible = true
	self._stage_num.text = self._stage
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
	if stage ~= nil then
		self._anti_loop:AddUpdater(ALittle.LoopAttribute(self._stage_container, "visible", false, 1000))
		group = ALittle.LoopGroup()
		group:AddUpdater(ALittle.LoopLinear(self._quad_up, "y", -self._quad_up.height, 500, 0))
		group:AddUpdater(ALittle.LoopLinear(self._quad_down, "y", A_UISystem.view_height, 500, 0))
		self._anti_loop:AddUpdater(group)
		self._anti_loop:AddUpdater(ALittle.LoopAttribute(self, "visible", false, 0))
		self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.StartBattle, g_GCenter, self._stage), 0))
	end
	self._anti_loop:Start()
	if stage == nil then
		A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
	end
end

function BattleCity.BattleSelectScene:Hide()
	if self._anti_loop ~= nil then
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	self._quad_up.y = 0
	self._quad_down.y = 0
	self._stage_container.visible = false
	self._anti_loop = ALittle.LoopList()
	local group = ALittle.LoopGroup()
	group:AddUpdater(ALittle.LoopLinear(self._quad_up, "y", -self._quad_up.height, 500, 0))
	group:AddUpdater(ALittle.LoopLinear(self._quad_down, "y", A_UISystem.view_height, 500, 0))
	self._anti_loop:AddUpdater(group)
	self._anti_loop:AddUpdater(ALittle.LoopAttribute(self, "visible", false, 0))
	self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(g_GCenter.StartBattle, g_GCenter, self._stage), 0))
	self._anti_loop:Start()
end

function BattleCity.BattleSelectScene:HandleKeyDown(mod, sym, scancode)
	if sym == 106 then
		if self._stage <= 1 then
			return
		end
		self._stage = self._stage - (1)
		self._stage_num.text = self._stage
	elseif sym == 107 then
		if self._stage >= 255 then
			return
		end
		self._stage = self._stage + (1)
		self._stage_num.text = self._stage
	elseif sym == 104 then
		self:Hide()
	end
end

end