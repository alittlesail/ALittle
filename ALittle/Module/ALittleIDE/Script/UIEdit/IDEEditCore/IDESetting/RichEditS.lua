-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
RichEditS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.RichEditS")

function RichEditS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_richedit")
end

function RichEditS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadDefaultNilString("font_path")
	self:LoadDefaultNilString("font_size")
	self:LoadShowTypeData("display_list")
	self:LoadBoolData("editable", true, g_IDEEnum.yn_type)
	self:LoadBoolData("can_drag_text", true, g_IDEEnum.yn_type)
	self:LoadBoolData("focus_cursor", true, g_IDEEnum.yn_type)
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

function RichEditS:HandleFontPathFOCUSOUT(event)
	self:SpecialFontPathInputChange("font_path", false)
end

function RichEditS:HandleFontSizeFOCUSOUT(event)
	self:ValueNumZInputChange("font_size", false)
end

function RichEditS:HandleFontRedFOCUSOUT(event)
	self:ColorValueInputChange("font_red", false)
end

function RichEditS:HandleFontGreenFOCUSOUT(event)
	self:ColorValueInputChange("font_green", false)
end

function RichEditS:HandleFontBlueFOCUSOUT(event)
	self:ColorValueInputChange("font_blue", false)
end

function RichEditS:HandleCursorRedFOCUSOUT(event)
	self:ColorValueInputChange("cursor_red", false)
end

function RichEditS:HandleCursorGreenFOCUSOUT(event)
	self:ColorValueInputChange("cursor_green", false)
end

function RichEditS:HandleCursorBlueFOCUSOUT(event)
	self:ColorValueInputChange("cursor_blue", false)
end

function RichEditS:HandleDisplayListFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:TableDataSet("display_list", true)
end

function RichEditS:HandleEditableSELECT_CHANGE(event)
	self:BoolSelectChange("editable", false, g_IDEEnum.yn_type)
end

function RichEditS:HandleFocusCurosrSELECT_CHANGE(event)
	self:BoolSelectChange("focus_cursor", false, g_IDEEnum.yn_type)
end

function RichEditS:HandleCanDragTextSELECT_CHANGE(event)
	self:BoolSelectChange("can_drag_text", false, g_IDEEnum.yn_type)
end

function RichEditS:HandleMarginHalignFOCUSOUT(event)
	self:ValueNumInputChange("margin_halign", false)
end

function RichEditS:HandleMarginValignFOCUSOUT(event)
	self:ValueNumInputChange("margin_valign", false)
end

function RichEditS:HandleCursorMarginUpFOCUSOUT(event)
	self:ValueNumInputChange("cursor_margin_up", false)
end

function RichEditS:HandleCursorMarginDownFOCUSOUT(event)
	self:ValueNumInputChange("cursor_margin_down", false)
end

function RichEditS:HandleStartCursorFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("start_cursor", self._start_cursor.text, false)
end

function RichEditS:HandleEndCursorFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("end_cursor", self._end_cursor.text, false)
end

function RichEditS:HandleDefaultTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("default_text", false)
end

function RichEditS:HandleDefaultTextAlphaFOCUSOUT(event)
	self:Z2OValueInputChange("default_text_alpha", false)
end

function RichEditS:HandleImsPaddingFOCUSOUT(event)
	self:ValueNumInputChange("ims_padding", false)
end

function RichEditS:HandleRegexFOCUSOUT(event)
	self:DefaultNoStringInputChange("regex", false)
end

function RichEditS:HandleLimitLenFOCUSOUT(event)
	self:ValueNumInputChange("limit_len", false)
end

