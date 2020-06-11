-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextCheckButtonS, " extends class:ALittleIDE.TextCheckButtonS is nil")
DropDownS = Lua.Class(ALittleIDE.TextCheckButtonS, "ALittleIDE.DropDownS")

function DropDownS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_dropdown")
end

function DropDownS:LoadNatureBase()
	TextCheckButtonS.LoadNatureBase(self)
	self:LoadShowTypeDataForImage("show_background")
	self:LoadShowTypeDataForExtends("show_scrollbar")
	self:LoadDefaultNilString("button_style")
	self:LoadValueData("show_count")
	self:LoadValueData("body_margin")
	self:LoadValueData("screen_margin_left")
	self:LoadValueData("screen_margin_right")
	self:LoadValueData("screen_margin_top")
	self:LoadValueData("screen_margin_bottom")
	self:LoadShowTypeData("data_list")
end

function DropDownS:HandleShowBackGFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_background", self._show_background.text, self._show_background_grid9.selected, false)
end

function DropDownS:HandleShowBackGSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_background", self.HandleShowBackGFOCUSOUT, nil, path)
end
DropDownS.HandleShowBackGSelect = Lua.CoWrap(DropDownS.HandleShowBackGSelect)

function DropDownS:HandleShowScrollBarFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("show_scrollbar", self._show_scrollbar.text, false)
end

function DropDownS:HandleButtonStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("button_style", false)
end

function DropDownS:HandleShowCountFOCUSOUT(event)
	self:ValueNumZInputChange("show_count", false)
end

function DropDownS:HandleBodyMarginFOCUSOUT(event)
	self:ValueNumInputChange("body_margin", false)
end

function DropDownS:HandleScreenMarginLeftFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_left", false)
end

function DropDownS:HandleScreenMarginRightFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_right", false)
end

function DropDownS:HandleScreenMarginTopFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_top", false)
end

function DropDownS:HandleScreenMarginBottomFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_bottom", false)
end

function DropDownS:HandleDatalistFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("data_list", false)
end

