-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
BattleCity.BattleSelectScene = Lua.Class(ALittle.DisplayLayout, "BattleCity.BattleSelectScene")

function BattleCity.BattleSelectScene:Ctor()
	___rawset(self, "_stage", 1)
end

function BattleCity.BattleSelectScene.__getter:stage()
	return self._stage
end

function BattleCity.BattleSelectScene:Show(stage)
	self._stage = stage
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
	self._anti_loop:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.LoadScene, self), 0))
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
		self:LoadScene()
	end
end

function BattleCity.BattleSelectScene:LoadScene()
	self._battle_map = BattleCity.g_Control:LoadMessageFromFile(___all_struct[-922796193], "Other/Map/stage_" .. self._stage .. ".map")
	if self._battle_map == nil then
		ALittle.Error("map load filed! Other/Map/stage_" .. self._stage .. ".map")
		return
	end
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
BattleCity.BattleSelectScene.LoadScene = Lua.CoWrap(BattleCity.BattleSelectScene.LoadScene)

end