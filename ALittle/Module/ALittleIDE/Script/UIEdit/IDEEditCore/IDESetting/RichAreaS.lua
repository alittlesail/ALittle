-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
RichAreaS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.RichAreaS")

function RichAreaS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_richarea")
end

function RichAreaS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("line_spacing")
	self:LoadValueData("max_line_count")
	self:LoadTypeSelectData("halign", g_IDEEnum.HALIGN_type)
	self:LoadTypeSelectData("valign", g_IDEEnum.VALIGN_type)
	self:LoadShowTypeData("display_list")
end

function RichAreaS:HandleLineSpacingFOCUSOUT(event)
	self:ValueNumInputChange("line_spacing", true)
end

function RichAreaS:HandleMaxLineCountFOCUSOUT(event)
	self:ValueNumInputChange("max_line_count", true)
end

function RichAreaS:HandleHalignSELECT_CHANGE(event)
	local list = g_IDEEnum.HALIGN_rtype
	self:TypeSelectChange("halign", list, false)
end

function RichAreaS:HandleValignSELECT_CHANGE(event)
	local list = g_IDEEnum.VALIGN_rtype
	self:TypeSelectChange("valign", list, false)
end

function RichAreaS:HandleDisplayListFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("display_list", true)
end

