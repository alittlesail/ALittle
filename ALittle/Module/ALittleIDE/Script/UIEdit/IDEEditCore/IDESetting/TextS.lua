
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(DisplayObjectS, " extends class:DisplayObjectS is nil")
TextS = ALittle.Class(DisplayObjectS, "ALittleIDE.TextS")

function TextS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_text")
end

function TextS:LoadNatureBase()
	DisplayObjectS.LoadNatureBase(self)
	self:LoadBoolData("bold", false, g_IDEEnum.yn_type)
	self:LoadBoolData("underline", false, g_IDEEnum.yn_type)
	self:LoadBoolData("outline", false, g_IDEEnum.yn_type)
	self:LoadBoolData("deleteline", false, g_IDEEnum.yn_type)
	self:LoadBoolData("italic", false, g_IDEEnum.yn_type)
	self:LoadValueData("text")
	self:LoadDefaultNilString("font_path")
	self:LoadDefaultNilString("font_size")
	self:LoadEnumData("flip", g_IDEEnum.flip_type)
end

function TextS:HandleBoldSELECT_CHANGE(event)
	self:BoolSelectChange("bold", false, g_IDEEnum.yn_type)
end

function TextS:HandleUnderLineSELECT_CHANGE(event)
	self:BoolSelectChange("underline", false, g_IDEEnum.yn_type)
end

function TextS:HandleOutLineSELECT_CHANGE(event)
	self:BoolSelectChange("outline", false, g_IDEEnum.yn_type)
end

function TextS:HandleDeleteLineSELECT_CHANGE(event)
	self:BoolSelectChange("deleteline", false, g_IDEEnum.yn_type)
end

function TextS:HandleItalicSELECT_CHANGE(event)
	self:BoolSelectChange("italic", false, g_IDEEnum.yn_type)
end

function TextS:HandleTextFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:DefaultNoStringInputChange("text", true)
	else
		self:DefaultNoStringInputChange("text", false)
	end
end

function TextS:HandleFontPathFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:SpecialFontPathInputChange("font_path", true)
	else
		self:SpecialFontPathInputChange("font_path", false)
	end
end

function TextS:HandleFontSizeFOCUSOUT(event)
	if self._default.__class == "Text" then
		self:ValueNumZInputChange("font_size", true)
	else
		self:ValueNumZInputChange("font_size", false)
	end
end

function TextS:HandleFlipSELECT_CHANGE(event)
	local list = g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

