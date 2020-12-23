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
ALittleIDE.SpriteS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.SpriteS")

function ALittleIDE.SpriteS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_sprite")
end

function ALittleIDE.SpriteS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("row_count")
	self:LoadValueData("col_count")
	self:LoadValueData("row_index")
	self:LoadValueData("col_index")
	self:LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type)
end

function ALittleIDE.SpriteS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.SpriteS:HandleImageTextureNameSelect(event)
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
ALittleIDE.SpriteS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.SpriteS.HandleImageTextureNameSelect)

function ALittleIDE.SpriteS:HandleRowCountFOCUSOUT(event)
	self:ValueNumInputChange("row_count", false)
end

function ALittleIDE.SpriteS:HandleColCountFOCUSOUT(event)
	self:ValueNumInputChange("col_count", false)
end

function ALittleIDE.SpriteS:HandleRowIndexFOCUSOUT(event)
	self:ValueNumInputChange("row_index", false)
end

function ALittleIDE.SpriteS:HandleColIndexFOCUSOUT(event)
	self:ValueNumInputChange("col_index", false)
end

function ALittleIDE.SpriteS:HandleFlipSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

end