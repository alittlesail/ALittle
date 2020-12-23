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
ALittleIDE.ScrollListS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.ScrollListS")

function ALittleIDE.ScrollListS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrolllist")
end

function ALittleIDE.ScrollListS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	local list = ALittleIDE.g_IDEEnum.hv_type
	self:LoadTypeSelectData("type", list)
	self:LoadShowTypeDataForExtends("right_scrollbar")
	self:LoadValueData("gap")
	self:LoadBoolData("clip_atonce", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadBoolData("open_extends_drag", true, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.ScrollListS:HandleRightSFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("right_scrollbar", self._right_scrollbar.text, false)
end

function ALittleIDE.ScrollListS:HandleScrollListTypeSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.hv_rtype
	self:TypeSelectChange("type", list, true)
end

function ALittleIDE.ScrollListS:HandleGapFOCUSOUT(event)
	self:ValueNumInputChange("gap", false)
end

function ALittleIDE.ScrollListS:HandleClipClick(event)
	self._object:AdjustScrollBar()
	self._object:RefreshClipDisLine()
end

function ALittleIDE.ScrollListS:HandleClipAtonceSELECT_CHANGE(event)
	self:BoolSelectChange("clip_atonce", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.ScrollListS:HandleHandOpenExtendsDragSELECT_CHANGE(event)
	self:BoolSelectChange("open_extends_drag", false, ALittleIDE.g_IDEEnum.yn_type)
end

end