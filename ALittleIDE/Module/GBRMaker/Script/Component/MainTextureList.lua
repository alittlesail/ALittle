-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(653852482, "AUIPlugin.AUIFileSelectClickUIEvent", {
name = "AUIPlugin.AUIFileSelectClickUIEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectClickUIEvent", hash_code = 653852482,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
GBRMaker.MainTextureList = Lua.Class(ALittle.DisplayLayout, "GBRMaker.MainTextureList")

function GBRMaker.MainTextureList:TCtor()
	self._layout:Init({"png"})
	self._layout:AddEventListener(___all_struct[653852482], self, self.HandleTextureSelectClick)
end

function GBRMaker.MainTextureList.__getter:base_path()
	return self._layout.base_path
end

function GBRMaker.MainTextureList:RefreshTexture()
	local setting_data = g_GCenter.setting_dialog.data
	local module_path = "Module/" .. setting_data.project_name
	self._layout:SetBasePath(module_path .. "/Texture")
	self._layout:Refresh()
end

function GBRMaker.MainTextureList:HandleTextureSelectClick(event)
	g_GCenter:SelectTexture(event.path)
end

function GBRMaker.MainTextureList:HandleDragRightQuadUD(event)
	g_GCenter.right_grad3_ud.up_size = g_GCenter.right_grad3_ud.up_size + (event.delta_y)
end

function GBRMaker.MainTextureList:HandleDragEndRightQuadUD(event)
	GBRMaker.g_GConfig:SetConfig("right_grid3_up_size", g_GCenter.right_grad3_ud.up_size)
end

function GBRMaker.MainTextureList:HandleSetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function GBRMaker.MainTextureList:HandleSetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function GBRMaker.MainTextureList:HandleSetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

end