-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1426212097, "ABrowser.CopyCutPasteUserData", {
name = "ABrowser.CopyCutPasteUserData", ns_name = "ABrowser", rl_name = "CopyCutPasteUserData", hash_code = 1426212097,
name_list = {"target","text"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

ATool = Lua.Class(nil, "ABrowser.ATool")

function ATool:Ctor()
end

function ATool:ShowNotice(title, content)
	if self._notice_dialog == nil then
		self._notice_dialog = g_Control:CreateControl(g_ABrowser.ui_pre .. "abrowser_notice_dialog", self)
		A_LayerManager:AddToModal(self._notice_dialog)
	end
	self._notice_dialog.visible = true
	self._notice_dialog.title = title
	self._notice_content.text = content
end

function ATool:ShowCopyCutPasteMenu(text, target)
	if self._ccp_menu == nil then
		self._ccp_menu = g_Control:CreateControl(g_ABrowser.ui_pre .. "abrowser_ccp_menu", self)
	end
	local x = A_UISystem.mouse_x
	local y = A_UISystem.mouse_y
	if y + self._ccp_menu.height > A_UISystem.view_height then
		self._ccp_menu.x = x
		self._ccp_menu.y = A_UISystem.view_height - self._ccp_menu.height
	else
		self._ccp_menu.x = x
		self._ccp_menu.y = y
	end
	local user_data = {}
	user_data.target = target
	user_data.text = text
	self._ccp_menu._user_data = user_data
	A_LayerManager:ShowFromRight(self._ccp_menu, false)
end

function ATool:HandleCopyCutPasteMenuCopy(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	local text = user_data.text
	if text ~= nil and text ~= "" then
		ALittle.System_SetClipboardText(text)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

function ATool:HandleCopyCutPasteMenuCut(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	if user_data.target ~= nil and user_data.target["CutText"] ~= nil then
		user_data.target["CutText"](user_data.target)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

function ATool:HandleCopyCutPasteMenuPaste(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	if user_data.target ~= nil and user_data.target["PasteText"] ~= nil then
		user_data.target["PasteText"](user_data.target)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

g_ATool = ATool()
