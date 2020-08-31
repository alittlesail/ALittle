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
end

function BattleCity.GCenter:Setup()
	BattleCity.g_GConfig = ALittle.CreateConfigSystem(BattleCity.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1, 2)
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
	BattleCity.g_LayerGroup:AddChild(self._login_scene)
	self._battle_select_scene = BattleCity.g_Control:CreateControl("battle_select")
	self._battle_select_scene.visible = false
	BattleCity.g_LayerGroup:AddChild(self._battle_select_scene)
	self:Restart()
end

function BattleCity.GCenter:Shutdown()
end

function BattleCity.GCenter.__getter:player_count()
	return self._player_count
end

function BattleCity.GCenter:Restart()
	self._login_scene:Show()
end

function BattleCity.GCenter:StartPlay(player_count)
	self._player_count = player_count
	self._battle_select_scene:Show(nil)
end

function BattleCity.GCenter:StartConstruction()
end

function BattleCity.GCenter:StartBattle(stage)
end

_G.g_GCenter = BattleCity.GCenter()
end