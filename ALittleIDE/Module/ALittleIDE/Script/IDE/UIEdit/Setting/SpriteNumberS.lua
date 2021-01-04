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
ALittleIDE.SpriteNumberS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.SpriteNumberS")

function ALittleIDE.SpriteNumberS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_sprite_number")
end

function ALittleIDE.SpriteNumberS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("text")
	self:LoadValueData("col_count")
	self:LoadValueData("cell_width")
end

function ALittleIDE.SpriteNumberS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.SpriteNumberS:HandleImageTextureNameSelect(event)
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
ALittleIDE.SpriteNumberS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.SpriteNumberS.HandleImageTextureNameSelect)

function ALittleIDE.SpriteNumberS:HandleColCountFOCUSOUT(event)
	self:ValueNumInputChange("col_count", false)
end

function ALittleIDE.SpriteNumberS:HandleCellWidthFOCUSOUT(event)
	self:ValueNumInputChange("cell_width", true)
end

function ALittleIDE.SpriteNumberS:HandleTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", true)
	self._tree_logic:UpdateDesc()
end

end