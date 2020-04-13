
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


IDEAttrTextDialog = ALittle.Class(nil, "ALittleIDE.IDEAttrTextDialog")

function IDEAttrTextDialog:ShowDialog(target_panel, text, need_reset)
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_text_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._dialog.visible = true
	self._target_panel = target_panel
	self._target_text = text
	self._target_need_reset = need_reset
	self:ResetText()
end

function IDEAttrTextDialog:HideDialog()
	self._dialog.visible = false
end

function IDEAttrTextDialog:ReadColor(text)
	local display_object = self["_" .. text]
	local value = tonumber(display_object.text)
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

function IDEAttrTextDialog:HandleEditChanged(event)
	local info = {}
	info.__class = "Text"
	if self._bold.text == "是" then
		info.bold = true
	end
	if self._underline.text == "是" then
		info.underline = true
	end
	if self._outline.text == "是" then
		info.outline = true
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
		info.font_size = math.floor(tonumber(self._font_size.text))
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
	local info_json = json.encode(info)
	self._target_panel["_" .. self._target_text].text = info_json
	self._target_panel:RemoverToNilShowSet(self._target_text, info_json, self._target_need_reset)
end

function IDEAttrTextDialog:ResetText()
	local info = self._target_panel.base[self._target_text]
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
	self._outline.text = "否"
	if info.outline then
		self._outline.text = "是"
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
	if g_IDEProject.project ~= nil then
		self._font_path.text = g_IDEProject.project.config:GetConfig("default_font_path", "")
	end
	if info.font_path ~= nil then
		self._font_path.text = info.font_path
	end
	self._font_size.text = ""
	if g_IDEProject.project ~= nil then
		self._font_size.text = g_IDEProject.project.config:GetConfig("default_font_size", 15)
	end
	if info.font_size ~= nil then
		self._font_size.text = info.font_size
	end
	if info.red == nil then
		self._red.text = 255
	else
		self._red.text = info.red * 255
	end
	if info.green == nil then
		self._green.text = 255
	else
		self._green.text = info.green * 255
	end
	if info.blue == nil then
		self._blue.text = 255
	else
		self._blue.text = info.blue * 255
	end
end

g_IDEAttrTextDialog = IDEAttrTextDialog()
