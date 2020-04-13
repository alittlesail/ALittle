
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(TextEditS, " extends class:TextEditS is nil")
TextInputS = ALittle.Class(TextEditS, "ALittleIDE.TextInputS")

function TextInputS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textinput")
end

function TextInputS:LoadNatureBase()
	TextEditS.LoadNatureBase(self)
	self:LoadBoolData("password_mode", false, g_IDEEnum.yn_type)
	self:LoadDefaultNilString("default_text")
	self:LoadValueData("default_text_alpha")
	self:LoadValueData("ims_padding")
end

function TextInputS:HandlePasswordModeSELECT_CHANGE(event)
	self:BoolSelectChange("password_mode", false, g_IDEEnum.yn_type)
end

function TextInputS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function TextInputS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function TextInputS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function TextInputS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function TextInputS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

