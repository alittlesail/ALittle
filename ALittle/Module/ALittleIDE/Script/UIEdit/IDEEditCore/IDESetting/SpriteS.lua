-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
SpriteS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.SpriteS")

function SpriteS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_sprite")
end

function SpriteS:LoadNatureBase()
	DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("row_count")
	self:LoadValueData("col_count")
	self:LoadValueData("row_index")
	self:LoadValueData("col_index")
	self:LoadEnumData("flip", g_IDEEnum.flip_type)
end

function SpriteS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function SpriteS:HandleImageTextureNameSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "texture_name", self.HandleImageTextureNameFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function SpriteS:HandleRowCountFOCUSOUT(event)
	self:ValueNumInputChange("row_count", false)
end

function SpriteS:HandleColCountFOCUSOUT(event)
	self:ValueNumInputChange("col_count", false)
end

function SpriteS:HandleRowIndexFOCUSOUT(event)
	self:ValueNumInputChange("row_index", false)
end

function SpriteS:HandleColIndexFOCUSOUT(event)
	self:ValueNumInputChange("col_index", false)
end

function SpriteS:HandleFlipSELECT_CHANGE(event)
	local list = g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

