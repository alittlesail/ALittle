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
ALittleIDE.RichAreaS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.RichAreaS")

function ALittleIDE.RichAreaS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_richarea")
end

function ALittleIDE.RichAreaS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("line_spacing")
	self:LoadValueData("max_line_count")
	self:LoadTypeSelectData("halign", ALittleIDE.g_IDEEnum.HALIGN_type)
	self:LoadTypeSelectData("valign", ALittleIDE.g_IDEEnum.VALIGN_type)
	self:LoadShowTypeData("display_list")
end

function ALittleIDE.RichAreaS:HandleLineSpacingFOCUSOUT(event)
	self:ValueNumInputChange("line_spacing", true)
end

function ALittleIDE.RichAreaS:HandleMaxLineCountFOCUSOUT(event)
	self:ValueNumInputChange("max_line_count", true)
end

function ALittleIDE.RichAreaS:HandleHalignSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.HALIGN_rtype
	self:TypeSelectChange("halign", list, false)
end

function ALittleIDE.RichAreaS:HandleValignSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.VALIGN_rtype
	self:TypeSelectChange("valign", list, false)
end

function ALittleIDE.RichAreaS:HandleDisplayListFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("display_list", true)
end

end