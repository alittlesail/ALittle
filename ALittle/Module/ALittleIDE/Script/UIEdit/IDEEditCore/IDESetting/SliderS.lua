-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
SliderS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.SliderS")

function SliderS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_slider")
end

function SliderS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadTypeSelectData("type", g_IDEEnum.hv_type)
	self:LoadTypeSelectData("fixed", g_IDEEnum.fix_type)
	self:LoadValueData("grade")
	self:LoadValueData("offset_rate")
	self:LoadShowTypeDataForExtends("bar_button")
	self:LoadShowTypeDataForImage("bar_background")
end

function SliderS:HandleSliderTypeSELECT_CHANGE(event)
	local list = g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, false)
end

function SliderS:HandleOffsetRateFOCUSOUT(event)
	self:Z2OValueInputChange("offset_rate", false)
end

function SliderS:HandleGradeFOCUSOUT(event)
	self:ValueNumInputChange("grade", false)
end

function SliderS:HandleFixedSELECT_CHANGE(event)
	local list = g_IDEEnum.fix_rtype
	self:TypeSelectChange("fixed", list, false)
end

function SliderS:HandleBarButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bar_button", self._bar_button.text, false)
end

function SliderS:HandleBarBackFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("bar_background", self._bar_background.text, self._bar_background_grid9.selected, false)
end

function SliderS:HandleBarBackSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "bar_background", self.HandleBarBackFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

