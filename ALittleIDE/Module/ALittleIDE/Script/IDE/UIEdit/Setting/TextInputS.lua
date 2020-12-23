-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextEditS, " extends class:ALittleIDE.TextEditS is nil")
ALittleIDE.TextInputS = Lua.Class(ALittleIDE.TextEditS, "ALittleIDE.TextInputS")

function ALittleIDE.TextInputS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textinput")
end

function ALittleIDE.TextInputS:LoadNatureBase()
	ALittleIDE.TextEditS.LoadNatureBase(self)
	self:LoadBoolData("password_mode", false, ALittleIDE.g_IDEEnum.yn_type)
	self:LoadDefaultNilString("default_text")
	self:LoadValueData("default_text_alpha")
	self:LoadValueData("ims_padding")
end

function ALittleIDE.TextInputS:HandlePasswordModeSELECT_CHANGE(event)
	self:BoolSelectChange("password_mode", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextInputS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function ALittleIDE.TextInputS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function ALittleIDE.TextInputS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function ALittleIDE.TextInputS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function ALittleIDE.TextInputS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

end