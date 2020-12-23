-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEAttrTextDialog = Lua.Class(nil, "ALittleIDE.IDEAttrTextDialog")

function ALittleIDE.IDEAttrTextDialog:ShowDialog(target_panel, text, need_reset)
	if self._dialog == nil then
		self._dialog = ALittleIDE.g_Control:CreateControl("ide_text_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._dialog.visible = true
	self._target_panel = target_panel
	self._target_text = text
	self._target_need_reset = need_reset
	self:ResetText()
end

function ALittleIDE.IDEAttrTextDialog:HideDialog()
	self._dialog.visible = false
end

function ALittleIDE.IDEAttrTextDialog:ReadColor(text)
	local display_object = self["_" .. text]
	local value = ALittle.Math_ToDouble(display_object.text)
	if value == nil or value < 0 then
		display_object.text = "0"
		return 0
	elseif value > 255 then
		display_object.text = "255"
		return 1
	else
		value = value / 255
		return value
	end
end

function ALittleIDE.IDEAttrTextDialog:HandleEditChanged(event)
	local info = {}
	info.__class = "Text"
	if self._bold.text == "是" then
		info.bold = true
	end
	if self._underline.text == "是" then
		info.underline = true
	end
	if self._deleteline.text == "是" then
		info.deleteline = true
	end
	if self._italic.text == "是" then
		info.italic = true
	end
	if self._font_path.text ~= "" then
		info.font_path = self._font_path.text
	end
	if self._font_size.text ~= "" then
		info.font_size = ALittle.Math_ToInt(self._font_size.text)
	end
	info.red = self:ReadColor("red")
	if info.red == 1 then
		info.red = nil
	end
	info.green = self:ReadColor("green")
	if info.green == 1 then
		info.green = nil
	end
	info.blue = self:ReadColor("blue")
	if info.blue == 1 then
		info.blue = nil
	end
	local info_json = ALittle.String_JsonEncode(info)
	self._target_panel["_" .. self._target_text].text = info_json
	self._target_panel:RemoverToNilShowSet(self._target_text, info_json, self._target_need_reset)
end

function ALittleIDE.IDEAttrTextDialog:ResetText()
	local info = self._target_panel.base[self._target_text]
	if info == nil then
		info = self._target_panel.default[self._target_text]
	end
	if info == nil then
		info = {}
	end
	self._bold.text = "否"
	if info.bold then
		self._bold.text = "是"
	end
	self._underline.text = "否"
	if info.underline then
		self._underline.text = "是"
	end
	self._deleteline.text = "否"
	if info.deleteline then
		self._deleteline.text = "是"
	end
	self._italic.text = "否"
	if info.italic then
		self._italic.text = "是"
	end
	self._font_path.text = ""
	if ALittleIDE.g_IDEProject.project ~= nil then
		self._font_path.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_path", "")
	end
	if info.font_path ~= nil then
		self._font_path.text = info.font_path
	end
	self._font_size.text = ""
	if ALittleIDE.g_IDEProject.project ~= nil then
		self._font_size.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_size", 15)
	end
	if info.font_size ~= nil then
		self._font_size.text = info.font_size
	end
	if info.red == nil then
		self._red.text = 255
	else
		self._red.text = ALittle.Math_Floor(info.red * 255)
	end
	if info.green == nil then
		self._green.text = 255
	else
		self._green.text = ALittle.Math_Floor(info.green * 255)
	end
	if info.blue == nil then
		self._blue.text = 255
	else
		self._blue.text = ALittle.Math_Floor(info.blue * 255)
	end
end

ALittleIDE.g_IDEAttrTextDialog = ALittleIDE.IDEAttrTextDialog()
end