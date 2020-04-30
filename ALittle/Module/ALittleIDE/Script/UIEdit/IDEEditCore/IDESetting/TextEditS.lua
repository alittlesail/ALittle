-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextS, " extends class:ALittleIDE.TextS is nil")
TextEditS = Lua.Class(ALittleIDE.TextS, "ALittleIDE.TextEditS")

function TextEditS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textedit")
end

function TextEditS:LoadNatureBase()
	TextS.LoadNatureBase(self)
	self:LoadBoolData("editable", true, g_IDEEnum.yn_type)
	self:LoadColorData("cursor_red")
	self:LoadColorData("cursor_green")
	self:LoadColorData("cursor_blue")
	self:LoadDefaultNilString("default_text")
	self:LoadValueData("default_text_alpha")
	self:LoadValueData("ims_padding")
end

function TextEditS:HandleEditableSELECT_CHANGE(event)
	self:BoolSelectChange("editable", false, g_IDEEnum.yn_type)
end

function TextEditS:HandleCursorRedFOCUSOUT(event)
	self:ColorValueInputChange("cursor_red", false)
end

function TextEditS:HandleCursorGreenFOCUSOUT(event)
	self:ColorValueInputChange("cursor_green", false)
end

function TextEditS:HandleCursorBlueFOCUSOUT(event)
	self:ColorValueInputChange("cursor_blue", false)
end

function TextEditS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function TextEditS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function TextEditS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function TextEditS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function TextEditS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

