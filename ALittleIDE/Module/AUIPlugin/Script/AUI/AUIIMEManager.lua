-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


AUIPlugin.AUIIMEManager = Lua.Class(nil, "AUIPlugin.AUIIMEManager")

function AUIPlugin.AUIIMEManager:Ctor()
end

function AUIPlugin.AUIIMEManager:Setup()
	if A_UISystem.ime_callback ~= nil then
		return
	end
	if self._ime_dialog == nil then
		self._ime_dialog = AUIPlugin.g_Control:CreateControl("aui_ime_dialog", self)
		A_LayerManager:AddToTip(self._ime_dialog)
		self._ime_dialog.visible = false
		self._ime_dialog_init_width = self._ime_dialog.width
	end
	self._callback = Lua.Bind(self.HandleImeEditingCallback, self)
	A_UISystem.ime_callback = self._callback
end

function AUIPlugin.AUIIMEManager:Shutdown()
	if self._ime_dialog ~= nil then
		A_LayerManager:RemoveFromTip(self._ime_dialog)
		self._ime_dialog = nil
	end
	if A_UISystem.ime_callback == self._callback then
		A_UISystem.ime_callback = nil
	end
	self._callback = nil
end

function AUIPlugin.AUIIMEManager:HandleImeEditingCallback(open, text, start, list, target)
	if self._ime_dialog == nil then
		return
	end
	if open and target ~= nil then
		local class_info = (target).__class
		if class_info.__name == "ALittle.TextInput" and target.password_mode then
			return
		end
	end
	self._ime_dialog.visible = open
	if open and target ~= nil then
		self._ime_dialog.title = text
		local new_list = {}
		local new_list_count = 0
		for k, v in ___ipairs(list) do
			new_list_count = new_list_count + 1
			new_list[new_list_count] = k .. "." .. v
		end
		self._ime_editing_list.text = ALittle.String_Join(new_list, " ")
		local global_x, global_y = target:LocalToGlobal()
		local cursor_x = target.cursor_x
		local cursor_b = target.cursor_b
		if cursor_x ~= nil and cursor_b ~= nil then
			self._ime_dialog.x = global_x + cursor_x
			self._ime_dialog.y = global_y + cursor_b
		else
			self._ime_dialog.x = global_x
			self._ime_dialog.y = global_y + target.height
		end
		local width = self._ime_editing_list.width + self._ime_editing_list.x * 2
		if width < self._ime_dialog_init_width then
			width = self._ime_dialog_init_width
		end
		if self._ime_dialog.width ~= width then
			self._ime_dialog.width = width
		end
		if self._ime_dialog.y + self._ime_dialog.height > A_UISystem.view_height then
			self._ime_dialog.y = global_y - self._ime_dialog.height
		end
		if self._ime_dialog.x + self._ime_dialog.width > A_UISystem.view_width then
			self._ime_dialog.x = A_UISystem.view_width - self._ime_dialog.width
		end
	end
end

AUIPlugin.g_AUIIMEManager = AUIPlugin.AUIIMEManager()
end