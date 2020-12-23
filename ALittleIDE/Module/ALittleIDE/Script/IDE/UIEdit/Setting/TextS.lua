-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
ALittleIDE.TextS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.TextS")

function ALittleIDE.TextS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_text")
end

function ALittleIDE.TextS:LoadNatureBase()
	ALittleIDE.DisplayObjectS.LoadNatureBase(self)
	self:LoadBoolData("bold", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadBoolData("underline", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadBoolData("deleteline", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadBoolData("italic", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadValueData("text")
	self:LoadDefaultNilString("font_path")
	self:LoadDefaultNilString("font_size")
	self:LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type)
end

function ALittleIDE.TextS:HandleBoldSELECT_CHANGE(event)
	self:BoolSelectChange("bold", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextS:HandleUnderLineSELECT_CHANGE(event)
	self:BoolSelectChange("underline", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextS:HandleDeleteLineSELECT_CHANGE(event)
	self:BoolSelectChange("deleteline", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextS:HandleItalicSELECT_CHANGE(event)
	self:BoolSelectChange("italic", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextS:HandleTextFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:DefaultNoStringInputChange("text", true)
	else
		self:DefaultNoStringInputChange("text", false)
	end
	self._tree_logic:UpdateDesc()
end

function ALittleIDE.TextS:HandleFontPathFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:SpecialFontPathInputChange("font_path", true)
	else
		self:SpecialFontPathInputChange("font_path", false)
	end
end

function ALittleIDE.TextS:HandleFontSizeFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:ValueNumZInputChange("font_size", true)
	else
		self:ValueNumZInputChange("font_size", false)
	end
end

function ALittleIDE.TextS:HandleFlipSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

end