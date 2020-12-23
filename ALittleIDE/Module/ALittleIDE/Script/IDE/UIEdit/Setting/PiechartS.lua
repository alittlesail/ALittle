-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.PiechartS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.PiechartS")

function ALittleIDE.PiechartS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_piechart")
end

function ALittleIDE.PiechartS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("start_degree")
	self:LoadValueData("end_degree")
end

function ALittleIDE.PiechartS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function ALittleIDE.PiechartS:HandleImageTextureNameSelect(event)
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
ALittleIDE.PiechartS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.PiechartS.HandleImageTextureNameSelect)

function ALittleIDE.PiechartS:HandleImageStartDegreeFOCUSOUT(event)
	self:ValueNumZInputChange("start_degree", false)
end

function ALittleIDE.PiechartS:HandleImageEndDegreeFOCUSOUT(event)
	self:ValueNumZInputChange("end_degree", false)
end

end