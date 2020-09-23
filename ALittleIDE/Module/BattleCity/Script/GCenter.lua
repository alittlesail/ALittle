-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.BattleCity == nil then _G.BattleCity = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


BattleCity.g_GConfig = nil
BattleCity.GCenter = Lua.Class(nil, "BattleCity.GCenter")

function BattleCity.GCenter:Ctor()
	___rawset(self, "_player_count", 1)
	___rawset(self, "_stage", 1)
end

function BattleCity.GCenter:Setup()
	BattleCity.g_GConfig = ALittle.CreateConfigSystem(BattleCity.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(BattleCity.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	BattleCity.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(BattleCity.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	BattleCity.g_LayerGroup:AddChild(self._dialog_layer, nil)
	self._login_scene = BattleCity.g_Control:CreateControl("login_scene")
	self._login_scene.visible = false
	self._main_layer:AddChild(self._login_scene)
	self._battle_select_scene = BattleCity.g_Control:CreateControl("battle_select")
	self._battle_select_scene.visible = false
	self._main_layer:AddChild(self._battle_select_scene)
	self._battle_scene = BattleCity.g_Control:CreateControl("battle_scene")
	self._battle_scene.visible = false
	self._main_layer:AddChild(self._battle_scene)
	self._battle_settlement = BattleCity.g_Control:CreateControl("battle_settlement")
	self._battle_settlement.visible = false
	self._main_layer:AddChild(self._battle_settlement)
	self._edit_scene = BattleCity.g_Control:CreateControl("edit_scene")
	self._edit_scene.visible = false
	self._main_layer:AddChild(self._edit_scene)
	self:Restart()
end

function BattleCity.GCenter:Shutdown()
end

function BattleCity.GCenter.__getter:player_count()
	return self._player_count
end

function BattleCity.GCenter.__getter:player1_data()
	return self._player1
end

function BattleCity.GCenter.__getter:player2_data()
	return self._player2
end

function BattleCity.GCenter.__getter:battle_scene()
	return self._battle_scene
end

function BattleCity.GCenter.__getter:battle_settlement()
	return self._battle_settlement
end

function BattleCity.GCenter.__getter:edit_scene()
	return self._edit_scene
end

function BattleCity.GCenter.__getter:stage()
	return self._stage
end

function BattleCity.GCenter:Restart()
	self._battle_scene:Hide()
	self._player1 = {}
	self._player1.level = 1
	self._player1.life = 3
	self._player1.score = 0
	self._player2 = {}
	self._player2.level = 1
	self._player2.life = 3
	self._player2.score = 0
	self._login_scene:Show()
end

function BattleCity.GCenter:StartPlay(player_count)
	self._player_count = player_count
	self._stage = 1
	self._battle_select_scene:Show(self._stage)
end

function BattleCity.GCenter:NextStage()
	self._stage = self._stage + (1)
	if self._stage > 10 then
		self._stage = 1
	end
	self._battle_select_scene:Show(self._stage)
end

_G.g_GCenter = BattleCity.GCenter()
end