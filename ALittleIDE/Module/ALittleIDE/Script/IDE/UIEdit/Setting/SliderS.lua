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
ALittleIDE.SliderS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.SliderS")

function ALittleIDE.SliderS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_slider")
end

function ALittleIDE.SliderS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadTypeSelectData("type", ALittleIDE.g_IDEEnum.hv_type)
	self:LoadTypeSelectData("fixed", ALittleIDE.g_IDEEnum.fix_type)
	self:LoadValueData("grade")
	self:LoadValueData("offset_rate")
	self:LoadShowTypeDataForExtends("bar_button")
	self:LoadShowTypeDataForImage("bar_background")
end

function ALittleIDE.SliderS:HandleSliderTypeSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, false)
end

function ALittleIDE.SliderS:HandleOffsetRateFOCUSOUT(event)
	self:Z2OValueInputChange("offset_rate", false)
end

function ALittleIDE.SliderS:HandleGradeFOCUSOUT(event)
	self:ValueNumInputChange("grade", false)
end

function ALittleIDE.SliderS:HandleFixedSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.fix_rtype
	self:TypeSelectChange("fixed", list, false)
end

function ALittleIDE.SliderS:HandleBarButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bar_button", self._bar_button.text, false)
end

function ALittleIDE.SliderS:HandleBarBackFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("bar_background", self._bar_background.text, self._bar_background_grid9.selected, false)
end

function ALittleIDE.SliderS:HandleBarBackSelect(event)
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
	self:ImagePathSelectCallback("bar_background", self.HandleBarBackFOCUSOUT, nil, path, false)
end
ALittleIDE.SliderS.HandleBarBackSelect = Lua.CoWrap(ALittleIDE.SliderS.HandleBarBackSelect)

end