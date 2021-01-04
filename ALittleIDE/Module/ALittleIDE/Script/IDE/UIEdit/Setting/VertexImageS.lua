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
ALittleIDE.VertexImageS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.VertexImageS")

function ALittleIDE.VertexImageS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_verteximage")
end

function ALittleIDE.VertexImageS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("u1")
	self:LoadValueData("v1")
	self:LoadValueData("u2")
	self:LoadValueData("v2")
	self:LoadValueData("u3")
	self:LoadValueData("v3")
	self:LoadValueData("u4")
	self:LoadValueData("v4")
	self:LoadValueData("x1")
	self:LoadValueData("y1")
	self:LoadValueData("x2")
	self:LoadValueData("y2")
	self:LoadValueData("x3")
	self:LoadValueData("y3")
	self:LoadValueData("x4")
	self:LoadValueData("y4")
end

function ALittleIDE.VertexImageS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.VertexImageS:HandleImageTextureNameSelect(event)
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
ALittleIDE.VertexImageS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.VertexImageS.HandleImageTextureNameSelect)

function ALittleIDE.VertexImageS:SetTextureName(texture_name, revoke_bind)
	if texture_name == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, revoke_bind, texture_name, true)
end

function ALittleIDE.VertexImageS:HandleU1FOCUSOUT(event)
	self:ValueNumInputChange("u1", true)
end

function ALittleIDE.VertexImageS:HandleV1FOCUSOUT(event)
	self:ValueNumInputChange("v1", true)
end

function ALittleIDE.VertexImageS:HandleU2FOCUSOUT(event)
	self:ValueNumInputChange("u2", true)
end

function ALittleIDE.VertexImageS:HandleV2FOCUSOUT(event)
	self:ValueNumInputChange("v2", true)
end

function ALittleIDE.VertexImageS:HandleU3FOCUSOUT(event)
	self:ValueNumInputChange("u3", true)
end

function ALittleIDE.VertexImageS:HandleV3FOCUSOUT(event)
	self:ValueNumInputChange("v3", true)
end

function ALittleIDE.VertexImageS:HandleU4FOCUSOUT(event)
	self:ValueNumInputChange("u4", true)
end

function ALittleIDE.VertexImageS:HandleV4FOCUSOUT(event)
	self:ValueNumInputChange("v4", true)
end

function ALittleIDE.VertexImageS:HandleX1FOCUSOUT(event)
	self:ValueNumInputChange("x1", true)
end

function ALittleIDE.VertexImageS:HandleY1FOCUSOUT(event)
	self:ValueNumInputChange("y1", true)
end

function ALittleIDE.VertexImageS:HandleX2FOCUSOUT(event)
	self:ValueNumInputChange("x2", true)
end

function ALittleIDE.VertexImageS:HandleY2FOCUSOUT(event)
	self:ValueNumInputChange("y2", true)
end

function ALittleIDE.VertexImageS:HandleX3FOCUSOUT(event)
	self:ValueNumInputChange("x3", true)
end

function ALittleIDE.VertexImageS:HandleY3FOCUSOUT(event)
	self:ValueNumInputChange("y3", true)
end

function ALittleIDE.VertexImageS:HandleX4FOCUSOUT(event)
	self:ValueNumInputChange("x4", true)
end

function ALittleIDE.VertexImageS:HandleY4FOCUSOUT(event)
	self:ValueNumInputChange("y4", true)
end

end