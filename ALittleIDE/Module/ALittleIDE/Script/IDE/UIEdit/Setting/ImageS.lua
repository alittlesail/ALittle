-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
ALittleIDE.ImageS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.ImageS")

function ALittleIDE.ImageS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_image")
end

function ALittleIDE.ImageS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type)
end

function ALittleIDE.ImageS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.ImageS:HandleImageTextureNameSelect(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, nil, path, true)
end
ALittleIDE.ImageS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.ImageS.HandleImageTextureNameSelect)

function ALittleIDE.ImageS:SetTextureName(texture_name, revoke_bind)
	if texture_name == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name, true)
end

function ALittleIDE.ImageS:HandleFlipSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

end