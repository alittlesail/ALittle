-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEAttrControlDialog = Lua.Class(nil, "ALittleIDE.IDEAttrControlDialog")

function ALittleIDE.IDEAttrControlDialog:CreateDialog()
	self._dialog = ALittleIDE.g_Control:CreateControl("ide_control_attr_dialog", self)
	ALittleIDE.g_DialogLayer:AddChild(self._dialog)
	self._dialog.visible = false
	self._dialog.close_callback = Lua.Bind(self.HandleClose, self)
end

function ALittleIDE.IDEAttrControlDialog.__getter:attr_container()
	if self._attr_container == nil then
		self:CreateDialog()
	end
	return self._attr_container
end

function ALittleIDE.IDEAttrControlDialog:HandleClose()
	ALittleIDE.g_IDEAttrEventDialog:HideDialog()
	return true
end

function ALittleIDE.IDEAttrControlDialog:SetTitle(title)
	if self._dialog == nil then
		self:CreateDialog()
	end
	self._dialog.title = title
end

function ALittleIDE.IDEAttrControlDialog:ShowDialog(target)
	if self._dialog == nil then
		self:CreateDialog()
	end
	self._dialog.visible = true
	local x, y = target:LocalToGlobal()
	self._dialog.x = x + target.width + 20
	self._dialog.y = A_UISystem.mouse_y - (self._dialog.height - target.height) / 2
	if self._dialog.y < 0 then
		self._dialog.y = 0
	end
	if self._dialog.x + self._dialog.width > A_UISystem.view_width then
		self._dialog.x = A_UISystem.view_width - self._dialog.width
	end
	if self._dialog.y + self._dialog.height > A_UISystem.view_height then
		self._dialog.y = A_UISystem.view_height - self._dialog.height
	end
end

function ALittleIDE.IDEAttrControlDialog:HideDialog()
	if self._dialog == nil then
		return
	end
	self._dialog.visible = false
	ALittleIDE.g_IDEAttrEventDialog:HideDialog()
end

function ALittleIDE.IDEAttrControlDialog:IsShow()
	if self._dialog == nil then
		return false
	end
	return self._dialog.visible
end

ALittleIDE.g_IDEAttrControlDialog = ALittleIDE.IDEAttrControlDialog()
end