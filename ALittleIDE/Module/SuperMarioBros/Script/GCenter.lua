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
	ALittle.System_SetThreadCount(1, 2)
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
	self._edit_scene = SuperMarioBros.g_Control:CreateControl("edit_scene")
	self._main_layer:AddChild(self._edit_scene)
	self._edit_scene.visible = false
	self._login_scene:Show()
end

function SuperMarioBros.GCenter.__getter:login_scene()
	return self._login_scene
end

function SuperMarioBros.GCenter.__getter:edit_scene()
	return self._edit_scene
end

function SuperMarioBros.GCenter:Shutdown()
	self._edit_scene:Save()
end

_G.g_GCenter = SuperMarioBros.GCenter()
end