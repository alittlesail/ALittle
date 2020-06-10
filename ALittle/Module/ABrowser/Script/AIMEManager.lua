-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


AIMEManager = Lua.Class(nil, "ABrowser.AIMEManager")

function AIMEManager:Ctor()
end

function AIMEManager:Setup()
	if A_UISystem.ime_callback ~= nil then
		return
	end
	if self._ime_dialog == nil then
		self._ime_dialog = g_Control:CreateControl("abrowser_ime_dialog", self)
		A_LayerManager:AddToTip(self._ime_dialog)
		self._ime_dialog.visible = false
		self._ime_dialog_init_width = self._ime_dialog.width
	end
	self._callback = Lua.Bind(self.HandleImeEditingCallback, self)
	A_UISystem.ime_callback = self._callback
end

function AIMEManager:Shutdown()
	if self._ime_dialog ~= nil then
		A_LayerManager:RemoveFromTip(self._ime_dialog)
		self._ime_dialog = nil
	end
	if A_UISystem.ime_callback == self._callback then
		A_UISystem.ime_callback = nil
	end
	self._callback = nil
end

function AIMEManager:HandleImeEditingCallback(open, text, start, list, target)
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
		local height = target.height
		self._ime_dialog.x = global_x
		self._ime_dialog.y = global_y + height
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

g_AIMEManager = AIMEManager()
