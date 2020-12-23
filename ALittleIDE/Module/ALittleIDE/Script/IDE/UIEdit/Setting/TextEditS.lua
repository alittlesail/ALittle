-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextS, " extends class:ALittleIDE.TextS is nil")
ALittleIDE.TextEditS = Lua.Class(ALittleIDE.TextS, "ALittleIDE.TextEditS")

function ALittleIDE.TextEditS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textedit")
end

function ALittleIDE.TextEditS:LoadNatureBase()
	ALittleIDE.TextS.LoadNatureBase(self)
	self:LoadBoolData("editable", true, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadColorData("cursor_red")
	self:LoadColorData("cursor_green")
	self:LoadColorData("cursor_blue")
	self:LoadDefaultNilString("default_text")
	self:LoadValueData("default_text_alpha")
	self:LoadValueData("ims_padding")
end

function ALittleIDE.TextEditS:HandleEditableSELECT_CHANGE(event)
	self:BoolSelectChange("editable", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextEditS:HandleCursorRedFOCUSOUT(event)
	self:ColorValueInputChange("cursor_red", false)
end

function ALittleIDE.TextEditS:HandleCursorGreenFOCUSOUT(event)
	self:ColorValueInputChange("cursor_green", false)
end

function ALittleIDE.TextEditS:HandleCursorBlueFOCUSOUT(event)
	self:ColorValueInputChange("cursor_blue", false)
end

function ALittleIDE.TextEditS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function ALittleIDE.TextEditS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function ALittleIDE.TextEditS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function ALittleIDE.TextEditS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function ALittleIDE.TextEditS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

end