-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.SuperMarioBros == nil then _G.SuperMarioBros = {} end
local ___pairs = pairs
local ___ipairs = ipairs


SuperMarioBros.g_GConfig = nil
SuperMarioBros.GCenter = Lua.Class(nil, "SuperMarioBros.GCenter")

function SuperMarioBros.GCenter:Ctor()
end

function SuperMarioBros.GCenter:Setup()
	SuperMarioBros.g_GConfig = ALittle.CreateConfigSystem(SuperMarioBros.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(SuperMarioBros.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	SuperMarioBros.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(SuperMarioBros.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	SuperMarioBros.g_LayerGroup:AddChild(self._dialog_layer, nil)
	self._login_scene = SuperMarioBros.g_Control:CreateControl("login_scene")
	self._main_layer:AddChild(self._login_scene)
	self._login_scene.visible = false
	self._stage_scene = SuperMarioBros.g_Control:CreateControl("stage_scene")
	self._main_layer:AddChild(self._stage_scene)
	self._stage_scene.visible = false
	self._battle_scene = SuperMarioBros.g_Control:CreateControl("battle_scene")
	self._main_layer:AddChild(self._battle_scene)
	self._battle_scene.visible = false
	self._edit_scene = SuperMarioBros.g_Control:CreateControl("edit_scene")
	self._main_layer:AddChild(self._edit_scene)
	self._edit_scene.visible = false
	self:ReStart()
end

function SuperMarioBros.GCenter:ReStart()
	self._player_data = {}
	self._player_data.score = 0
	self._player_data.world = 1
	self._player_data.subworld = 1
	self._player_data.life = 3
	self._player_data.level = 1
	self._login_scene:Show()
end

function SuperMarioBros.GCenter.__getter:login_scene()
	return self._login_scene
end

function SuperMarioBros.GCenter.__getter:stage_scene()
	return self._stage_scene
end

function SuperMarioBros.GCenter.__getter:battle_scene()
	return self._battle_scene
end

function SuperMarioBros.GCenter.__getter:edit_scene()
	return self._edit_scene
end

function SuperMarioBros.GCenter.__getter:player_data()
	return self._player_data
end

function SuperMarioBros.GCenter:Shutdown()
	self._edit_scene:Save()
end

_G.g_GCenter = SuperMarioBros.GCenter()
end