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
ALittleIDE.TriangleS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.TriangleS")

function ALittleIDE.TriangleS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_triangle")
end

function ALittleIDE.TriangleS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
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

function ALittleIDE.TriangleS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.TriangleS:HandleImageTextureNameSelect(event)
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
ALittleIDE.TriangleS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.TriangleS.HandleImageTextureNameSelect)

function ALittleIDE.TriangleS:SetTextureName(texture_name, revoke_bind)
	if texture_name == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name, true)
end

function ALittleIDE.TriangleS:HandleU1FOCUSOUT(event)
	self:ValueNumInputChange("u1", true)
end

function ALittleIDE.TriangleS:HandleV1FOCUSOUT(event)
	self:ValueNumInputChange("v1", true)
end

function ALittleIDE.TriangleS:HandleU2FOCUSOUT(event)
	self:ValueNumInputChange("u2", true)
end

function ALittleIDE.TriangleS:HandleV2FOCUSOUT(event)
	self:ValueNumInputChange("v2", true)
end

function ALittleIDE.TriangleS:HandleU3FOCUSOUT(event)
	self:ValueNumInputChange("u3", true)
end

function ALittleIDE.TriangleS:HandleV3FOCUSOUT(event)
	self:ValueNumInputChange("v3", true)
end

function ALittleIDE.TriangleS:HandleX1FOCUSOUT(event)
	self:ValueNumInputChange("x1", true)
end

function ALittleIDE.TriangleS:HandleY1FOCUSOUT(event)
	self:ValueNumInputChange("y1", true)
end

function ALittleIDE.TriangleS:HandleX2FOCUSOUT(event)
	self:ValueNumInputChange("x2", true)
end

function ALittleIDE.TriangleS:HandleY2FOCUSOUT(event)
	self:ValueNumInputChange("y2", true)
end

function ALittleIDE.TriangleS:HandleX3FOCUSOUT(event)
	self:ValueNumInputChange("x3", true)
end

function ALittleIDE.TriangleS:HandleY3FOCUSOUT(event)
	self:ValueNumInputChange("y3", true)
end

end