-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
RichInputS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.RichInputS")

function RichInputS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_richinput")
end

function RichInputS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadDefaultNilString("font_path")
	self:LoadDefaultNilString("font_size")
	self:LoadShowTypeData("display_list")
	self:LoadBoolData("editable", true, g_IDEEnum.yn_type)
	self:LoadBoolData("can_drag_text", true, g_IDEEnum.yn_type)
	self:LoadBoolData("focus_cursor", true, g_IDEEnum.yn_type)
	self:LoadBoolData("password_mode", true, g_IDEEnum.yn_type)
	self:LoadBoolData("input_align", true, g_IDEEnum.yn_type)
	self:LoadDefaultNilString("default_text")
	self:LoadValueData("default_text_alpha")
	self:LoadColorData("cursor_red")
	self:LoadColorData("cursor_green")
	self:LoadColorData("cursor_blue")
	self:LoadColorData("font_red")
	self:LoadColorData("font_green")
	self:LoadColorData("font_blue")
	self:LoadValueData("margin_halign")
	self:LoadValueData("margin_valign")
	self:LoadValueData("cursor_margin_up")
	self:LoadValueData("cursor_margin_down")
	self:LoadValueData("ims_padding")
	self:LoadShowTypeDataForExtends("start_cursor")
	self:LoadShowTypeDataForExtends("end_cursor")
end

function RichInputS:HandleFontPathFOCUSOUT(event)
	self:SpecialFontPathInputChange("font_path", false)
end

function RichInputS:HandleFontSizeFOCUSOUT(event)
	self:ValueNumZInputChange("font_size", false)
end

function RichInputS:HandleFontRedFOCUSOUT(event)
	self:ColorValueInputChange("font_red", false)
end

function RichInputS:HandleFontGreenFOCUSOUT(event)
	self:ColorValueInputChange("font_green", false)
end

function RichInputS:HandleFontBlueFOCUSOUT(event)
	self:ColorValueInputChange("font_blue", false)
end

function RichInputS:HandleCursorRedFOCUSOUT(event)
	self:ColorValueInputChange("cursor_red", false)
end

function RichInputS:HandleCursorGreenFOCUSOUT(event)
	self:ColorValueInputChange("cursor_green", false)
end

function RichInputS:HandleCursorBlueFOCUSOUT(event)
	self:ColorValueInputChange("cursor_blue", false)
end

function RichInputS:HandleDisplayListFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("display_list", true)
end

function RichInputS:HandleEditableSELECT_CHANGE(event)
	self:BoolSelectChange("editable", false, g_IDEEnum.yn_type)
end

function RichInputS:HandleFocusCurosrSELECT_CHANGE(event)
	self:BoolSelectChange("focus_cursor", false, g_IDEEnum.yn_type)
end

function RichInputS:HandleCanDragTextSELECT_CHANGE(event)
	self:BoolSelectChange("can_drag_text", false, g_IDEEnum.yn_type)
end

function RichInputS:HandleMarginHalignFOCUSOUT(event)
	self:ValueNumInputChange("margin_halign", false)
end

function RichInputS:HandleMarginValignFOCUSOUT(event)
	self:ValueNumInputChange("margin_valign", false)
end

function RichInputS:HandleCursorMarginUpFOCUSOUT(event)
	self:ValueNumInputChange("cursor_margin_up", false)
end

function RichInputS:HandleCursorMarginDownFOCUSOUT(event)
	self:ValueNumInputChange("cursor_margin_down", false)
end

function RichInputS:HandleStartCursorFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("start_cursor", self._start_cursor.text, false)
end

function RichInputS:HandleEndCursorFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("end_cursor", self._end_cursor.text, false)
end

function RichInputS:HandlePasswordModeSELECT_CHANGE(event)
	self:BoolSelectChange("password_mode", false, g_IDEEnum.yn_type)
end

function RichInputS:HandleInputAlignSELECT_CHANGE(event)
	self:BoolSelectChange("input_align", false, g_IDEEnum.yn_type)
end

function RichInputS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function RichInputS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function RichInputS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function RichInputS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function RichInputS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

