-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
TriangleS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.TriangleS")

function TriangleS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_triangle")
end

function TriangleS:LoadNatureBase()
	DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("u1")
	self:LoadValueData("v1")
	self:LoadValueData("u2")
	self:LoadValueData("v2")
	self:LoadValueData("u3")
	self:LoadValueData("v3")
	self:LoadValueData("x1")
	self:LoadValueData("y1")
	self:LoadValueData("x2")
	self:LoadValueData("y2")
	self:LoadValueData("x3")
	self:LoadValueData("y3")
end

function TriangleS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function TriangleS:HandleImageTextureNameSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "texture_name", self.HandleImageTextureNameFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TriangleS:SetTextureName(texture_name, revoke_bind)
	if texture_name == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name)
end

function TriangleS:HandleU1FOCUSOUT(event)
	self:ValueNumInputChange("u1", true)
end

function TriangleS:HandleV1FOCUSOUT(event)
	self:ValueNumInputChange("v1", true)
end

function TriangleS:HandleU2FOCUSOUT(event)
	self:ValueNumInputChange("u2", true)
end

function TriangleS:HandleV2FOCUSOUT(event)
	self:ValueNumInputChange("v2", true)
end

function TriangleS:HandleU3FOCUSOUT(event)
	self:ValueNumInputChange("u3", true)
end

function TriangleS:HandleV3FOCUSOUT(event)
	self:ValueNumInputChange("v3", true)
end

function TriangleS:HandleX1FOCUSOUT(event)
	self:ValueNumInputChange("x1", true)
end

function TriangleS:HandleY1FOCUSOUT(event)
	self:ValueNumInputChange("y1", true)
end

function TriangleS:HandleX2FOCUSOUT(event)
	self:ValueNumInputChange("x2", true)
end

function TriangleS:HandleY2FOCUSOUT(event)
	self:ValueNumInputChange("y2", true)
end

function TriangleS:HandleX3FOCUSOUT(event)
	self:ValueNumInputChange("x3", true)
end

function TriangleS:HandleY3FOCUSOUT(event)
	self:ValueNumInputChange("y3", true)
end

