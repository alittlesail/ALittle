-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDEAttrControlDialog = Lua.Class(nil, "ALittleIDE.IDEAttrControlDialog")

function IDEAttrControlDialog.__getter:dialog()
	if self._dialog == nil then
		self:CreateDialog()
	end
	return self._dialog
end

function IDEAttrControlDialog:CreateDialog()
	self._dialog = g_Control:CreateControl("ide_control_attr_dialog", self)
	g_DialogLayer:AddChild(self._dialog)
	self._dialog.visible = false
end

function IDEAttrControlDialog:SetTitle(title)
	if self._dialog == nil then
		self:CreateDialog()
	end
	self._dialog.title = title
end

function IDEAttrControlDialog:ShowDialog(target)
	if self._dialog == nil then
		self:CreateDialog()
	end
	self._dialog.visible = true
	self._dialog.x = A_UISystem.mouse_x + 50
	self._dialog.y = A_UISystem.mouse_y - (self._dialog.height - target.height) / 2
	if self._dialog.x + self._dialog.width > A_UISystem.view_width then
		self._dialog.x = A_UISystem.view_width - self._dialog.width
	end
	if self._dialog.y + self._dialog.height > A_UISystem.view_height then
		self._dialog.y = A_UISystem.view_height - self._dialog.height
	end
end

function IDEAttrControlDialog:HideDialog()
	if self._dialog == nil then
		return
	end
	self._dialog.visible = false
end

g_IDEAttrControlDialog = IDEAttrControlDialog()
