-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ScrollListS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.ScrollListS")

function ScrollListS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrolllist")
end

function ScrollListS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	local list = g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadShowTypeDataForExtends("right_scrollbar")
	self:LoadValueData("gap")
	self:LoadBoolData("clip_atonce", false, g_IDEEnum.yn_type)
	self:LoadBoolData("open_extends_drag", true, g_IDEEnum.yn_type)
end

function ScrollListS:HandleRightSFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("right_scrollbar", self._right_scrollbar.text, false)
end

function ScrollListS:HandleScrollListTypeSELECT_CHANGE(event)
	local list = g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, true)
end

function ScrollListS:HandleGapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

function ScrollListS:HandleClipClick(event)
	self._object:RejustScrollBar()
	self._object:RefreshClipDisLine()
end

function ScrollListS:HandleClipAtonceSELECT_CHANGE(event)
	self:BoolSelectChange("clip_atonce", false, g_IDEEnum.yn_type)
end

function ScrollListS:HandleHandOpenExtendsDragSELECT_CHANGE(event)
	self:BoolSelectChange("open_extends_drag", false, g_IDEEnum.yn_type)
end

