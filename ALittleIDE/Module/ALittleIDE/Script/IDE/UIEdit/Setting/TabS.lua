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
ALittleIDE.TabS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TabS")

function ALittleIDE.TabS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_tab")
end

function ALittleIDE.TabS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadDefaultNilString("radiobutton_style")
	self:LoadDefaultNilString("closebutton_style")
	self:LoadDefaultNilString("text_style")
	self:LoadDefaultNilString("selected_closebutton_style")
	self:LoadDefaultNilString("selected_text_style")
	self:LoadShowTypeDataForImage("show_head_background")
	self:LoadValueData("button_gap")
	self:LoadValueData("button_start")
	self:LoadValueData("button_margin")
	self:LoadValueData("head_size")
	self:LoadValueData("tab_index")
	self:LoadValueData("view_margin")
	self:LoadValueData("child_width_margin")
end

function ALittleIDE.TabS:HandleRBSttyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("radiobutton_style", false)
end

function ALittleIDE.TabS:HandleCBStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("closebutton_style", false)
end

function ALittleIDE.TabS:HandleTStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("text_style", false)
end

function ALittleIDE.TabS:HandleSCBStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("selected_closebutton_style", false)
end

function ALittleIDE.TabS:HandleSTStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("selected_text_style", false)
end

function ALittleIDE.TabS:HandleShowHeadBFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_head_background", self._show_head_background.text, self._show_head_background.selected, false)
end

function ALittleIDE.TabS:HandleShowHeadBSelect(event)
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
	self:ImagePathSelectCallback("show_head_background", self.HandleShowHeadBFOCUSOUT, nil, path, false)
end
ALittleIDE.TabS.HandleShowHeadBSelect = Lua.CoWrap(ALittleIDE.TabS.HandleShowHeadBSelect)

function ALittleIDE.TabS:HandleBGapFOCUSOUT(event)
	self:ValueNumInputChange("button_gap", false)
end

function ALittleIDE.TabS:HandleBStartFOCUSOUT(event)
	self:ValueNumInputChange("button_start", false)
end

function ALittleIDE.TabS:HandleBMarginFOCUSOUT(event)
	self:ValueNumInputChange("button_margin", false)
end

function ALittleIDE.TabS:HandleHeadSizeFOCUSOUT(event)
	self:ValueNumInputChange("head_size", false)
end

function ALittleIDE.TabS:HandleTabIndexFOCUSOUT(event)
	self:ValueNumZInputChange("tab_index", false)
end

function ALittleIDE.TabS:HandleViewMarginFOCUSOUT(event)
	self:ValueNumInputChange("view_margin", false)
end

function ALittleIDE.TabS:HandleChildWidthMarginFOCUSOUT(event)
	self:ValueNumInputChange("child_width_margin", false)
end

end