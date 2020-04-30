-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.Grid3S, " extends class:ALittleIDE.Grid3S is nil")
ScrollBarS = Lua.Class(ALittleIDE.Grid3S, "ALittleIDE.ScrollBarS")

function ScrollBarS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrollbar")
end

function ScrollBarS:LoadNatureBase()
	Grid3S.LoadNatureBase(self)
	self:LoadValueData("total_size")
	self:LoadValueData("show_size")
	self:LoadValueData("offset_rate")
	self:LoadValueData("offset_step")
	self:LoadShowTypeDataForExtends("up_button")
	self:LoadShowTypeDataForExtends("down_button")
	self:LoadShowTypeDataForExtends("bar_button")
	self:LoadShowTypeDataForImage("bar_background")
end

function ScrollBarS:HandleTotleSizeFOCUSOUT(event)
	self:ValueNumInputChange("total_size", false)
end

function ScrollBarS:HandleShowSizeFOCUSOUT(event)
	self:ValueNumInputChange("show_size", false)
end

function ScrollBarS:HandleOffsetRateFOCUSOUT(event)
	self:Z2OValueInputChange("offset_rate", false)
end

function ScrollBarS:HandleOffsetStepFOCUSOUT(event)
	self:Z2OValueInputChange("offset_step", false)
end

function ScrollBarS:HandleUpButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("up_button", self._up_button.text, false)
end

function ScrollBarS:HandleDownButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("down_button", self._down_button.text, false)
end

function ScrollBarS:HandleBarButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bar_button", self._bar_button.text, false)
end

function ScrollBarS:HandleBarBackFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("bar_background", self._bar_background.text, self._bar_background_grid9.selected, false)
end

function ScrollBarS:HandleBarBackSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "bar_background", self.HandleBarBackFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

