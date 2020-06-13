-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
TabS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TabS")

function TabS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_tab")
end

function TabS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
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

function TabS:HandleRBSttyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("radiobutton_style", false)
end

function TabS:HandleCBStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("closebutton_style", false)
end

function TabS:HandleTStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("text_style", false)
end

function TabS:HandleSCBStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("selected_closebutton_style", false)
end

function TabS:HandleSTStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("selected_text_style", false)
end

function TabS:HandleShowHeadBFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_head_background", self._show_head_background.text, self._show_head_background.selected, false)
end

function TabS:HandleShowHeadBSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_head_background", self.HandleShowHeadBFOCUSOUT, nil, path)
end
TabS.HandleShowHeadBSelect = Lua.CoWrap(TabS.HandleShowHeadBSelect)

function TabS:HandleBGapFOCUSOUT(event)
	self:ValueNumInputChange("button_gap", false)
end

function TabS:HandleBStartFOCUSOUT(event)
	self:ValueNumInputChange("button_start", false)
end

function TabS:HandleBMarginFOCUSOUT(event)
	self:ValueNumInputChange("button_margin", false)
end

function TabS:HandleHeadSizeFOCUSOUT(event)
	self:ValueNumInputChange("head_size", false)
end

function TabS:HandleTabIndexFOCUSOUT(event)
	self:ValueNumZInputChange("tab_index", false)
end

function TabS:HandleViewMarginFOCUSOUT(event)
	self:ValueNumInputChange("view_margin", false)
end

function TabS:HandleChildWidthMarginFOCUSOUT(event)
	self:ValueNumInputChange("child_width_margin", false)
end

