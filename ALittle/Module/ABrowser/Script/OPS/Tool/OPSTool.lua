
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSTool = ALittle.Class(nil, "ABrowser.OPSTool")

function OPSTool:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSTool:ShowWeakNotice(content, succeed)
	if self._weak_notice == nil then
		self._weak_notice = OPSWeakNotice(self._center)
	end
	self._weak_notice:Show(content, succeed)
end

function OPSTool:ShowCenterWeakNotice(content, succeed)
	if self._center_weak_notice == nil then
		self._center_weak_notice = OPSCenterWeakNotice(self._center)
	end
	self._center_weak_notice:Show(content, succeed)
end

function OPSTool:ShowDateSelect(target, select_type, default_hour, default_min, default_sec)
	if self._date_select == nil then
		self._date_select = g_Control:CreateControl("ops_date")
	end
	self._date_select:Show(target, target.text, select_type, default_hour, default_min, default_sec)
end

function OPSTool:ShowCopyCutPasteMenu(text, target)
	if self._ccp_menu == nil then
		self._ccp_menu = g_Control:CreateControl("ops_ccp_menu", self)
	end
	self._ccp_menu.x = A_UISystem.mouse_x
	self._ccp_menu.y = A_UISystem.mouse_y
	local user_data = {}
	user_data.text = text
	user_data.target = target
	self._ccp_menu._user_data = user_data
	A_LayerManager:ShowFromRight(self._ccp_menu, false)
end

function OPSTool:HandleCopyCutPasteMenuCopy(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	if user_data.text ~= nil and user_data.text ~= "" then
		ALittle.System_SetClipboardText(user_data.text)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

function OPSTool:HandleCopyCutPasteMenuCut(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	if user_data.target ~= nil and user_data.target["CutText"] ~= nil then
		user_data.target["CutText"](user_data.target)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

function OPSTool:HandleCopyCutPasteMenuPaste(event)
	local user_data = self._ccp_menu._user_data
	self._ccp_menu._user_data = nil
	if user_data.target ~= nil and user_data.target["PasteText"] ~= nil then
		user_data.target["PasteText"](user_data.target)
	end
	A_LayerManager:HideFromRight(self._ccp_menu)
end

