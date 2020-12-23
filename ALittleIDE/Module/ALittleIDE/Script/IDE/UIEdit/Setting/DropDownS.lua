-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextCheckButtonS, " extends class:ALittleIDE.TextCheckButtonS is nil")
ALittleIDE.DropDownS = Lua.Class(ALittleIDE.TextCheckButtonS, "ALittleIDE.DropDownS")

function ALittleIDE.DropDownS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_dropdown")
end

function ALittleIDE.DropDownS:LoadNatureBase()
	ALittleIDE.TextCheckButtonS.LoadNatureBase(self)
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

function ALittleIDE.DropDownS:HandleShowBackGFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_background", self._show_background.text, self._show_background_grid9.selected, false)
end

function ALittleIDE.DropDownS:HandleShowBackGSelect(event)
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
	self:ImagePathSelectCallback("show_background", self.HandleShowBackGFOCUSOUT, nil, path, false)
end
ALittleIDE.DropDownS.HandleShowBackGSelect = Lua.CoWrap(ALittleIDE.DropDownS.HandleShowBackGSelect)

function ALittleIDE.DropDownS:HandleShowScrollBarFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("show_scrollbar", self._show_scrollbar.text, false)
end

function ALittleIDE.DropDownS:HandleButtonStyleFOCUSOUT(event)
	self:DefaultNilStringInputChange("button_style", false)
end

function ALittleIDE.DropDownS:HandleShowCountFOCUSOUT(event)
	self:ValueNumZInputChange("show_count", false)
end

function ALittleIDE.DropDownS:HandleBodyMarginFOCUSOUT(event)
	self:ValueNumInputChange("body_margin", false)
end

function ALittleIDE.DropDownS:HandleScreenMarginLeftFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_left", false)
end

function ALittleIDE.DropDownS:HandleScreenMarginRightFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_right", false)
end

function ALittleIDE.DropDownS:HandleScreenMarginTopFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_top", false)
end

function ALittleIDE.DropDownS:HandleScreenMarginBottomFOCUSOUT(event)
	self:ValueNumInputChange("screen_margin_bottom", false)
end

function ALittleIDE.DropDownS:HandleDatalistFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("data_list", false)
end

end