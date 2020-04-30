-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
ImageS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.ImageS")

function ImageS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_image")
end

function ImageS:LoadNatureBase()
	DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadEnumData("flip", g_IDEEnum.flip_type)
end

function ImageS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ImageS:HandleImageTextureNameSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "texture_name", self.HandleImageTextureNameFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function ImageS:SetTextureName(texture_name, revoke_bind)
	if texture_name == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name)
end

function ImageS:HandleFlipSELECT_CHANGE(event)
	local list = g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

