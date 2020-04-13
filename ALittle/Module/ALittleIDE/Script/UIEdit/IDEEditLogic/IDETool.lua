
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-125023360, "ALittleIDE.IDECallbackUserData", {
name = "ALittleIDE.IDECallbackUserData", ns_name = "ALittleIDE", rl_name = "IDECallbackUserData", hash_code = -125023360,
name_list = {"cancel_callback","confirm_callback"},
type_list = {"Functor<()>","Functor<()>"},
option_map = {}
})

IDETool = Lua.Class(nil, "ALittleIDE.IDETool")

function IDETool:ShowAlertDialog(title, content)
	if self._alert_dialog == nil then
		self._alert_dialog = g_Control:CreateControl("ide_alert_dialog", self)
		A_LayerManager:AddToModal(self._alert_dialog)
	end
	self._alert_dialog.visible = true
	self._alert_dialog:MoveToTop()
	self._alert_dialog.title = title
	self._content.text = content
end

function IDETool:HideAlertDialog()
	self._alert_dialog.visible = false
end

function IDETool:ShowNotice(title, content)
	if self._notice_dialog == nil then
		self._notice_dialog = g_Control:CreateControl("ide_notice_dialog", self)
		A_LayerManager:AddToModal(self._notice_dialog)
		self._notice_min_size = self._notice_content.height
	end
	self._notice_dialog.visible = true
	self._notice_dialog:MoveToTop()
	self._notice_dialog.title = title
	self._notice_content.text = content
	local real_height = self._notice_content.real_height
	if real_height < self._notice_min_size then
		real_height = self._notice_min_size
	end
	local dialog_body_height = real_height + self._notice_content.y + self._notice_content.height_value
	self._notice_dialog.height = dialog_body_height + self._notice_dialog.head_size
end

function IDETool:HandleNoticeConfirmClick(event)
	self._notice_dialog.visible = false
end

function IDETool:SaveNotice(title, content, cancel_callback, confirm_callback)
	if self._save_dialog == nil then
		self._save_dialog = g_Control:CreateControl("ide_save_dialog", self)
		A_LayerManager:AddToModal(self._save_dialog)
	end
	self._save_dialog.visible = true
	self._save_dialog:MoveToTop()
	self._save_dialog.title = title
	self._save_content.text = content
	local user_data = {}
	user_data.cancel_callback = cancel_callback
	user_data.confirm_callback = confirm_callback
	self._save_dialog._user_data = user_data
end

function IDETool:HandleSaveConfirmClick(event)
	self._save_dialog.visible = false
	local user_data = self._save_dialog._user_data
	if user_data.confirm_callback ~= nil then
		user_data.confirm_callback()
	end
	if user_data.cancel_callback ~= nil then
		user_data.cancel_callback()
	end
	self._save_dialog._user_data = nil
end

function IDETool:HandleNoSaveClick(event)
	self._save_dialog.visible = false
	local user_data = self._save_dialog._user_data
	if user_data.cancel_callback ~= nil then
		user_data.cancel_callback()
	end
	self._save_dialog._user_data = nil
end

function IDETool:HandleSaveCancelClick(event)
	self._save_dialog.visible = false
	self._save_dialog._user_data = nil
end

function IDETool:DeleteNotice(title, content, confirm_callback)
	if self._delete_dialog == nil then
		self._delete_dialog = g_Control:CreateControl("ide_delete_dialog", self)
		A_LayerManager:AddToModal(self._delete_dialog)
	end
	self._delete_dialog.visible = true
	self._delete_dialog:MoveToTop()
	self._delete_dialog.title = title
	self._delete_content.text = content
	self._delete_dialog._user_data = confirm_callback
end

function IDETool:HandleDeleteConfirmClick(event)
	self._delete_dialog.visible = false
	local callback = self._delete_dialog._user_data
	if callback ~= nil then
		callback()
	end
	self._delete_dialog._user_data = nil
end

function IDETool:HandleDeleteCancelClick(event)
	self._delete_dialog.visible = false
	self._delete_dialog._user_data = nil
end

function IDETool:ShowRename(callback, text, x, y, width)
	if self._rename_input == nil then
		self._rename_input = g_Control:CreateControl("ide_rename_image_input", self)
		A_LayerManager:AddToModal(self._rename_input)
	end
	self._rename_input.visible = true
	A_UISystem.focus = self._rename_input.show_input
	self._rename_input.x = x
	self._rename_input.y = y
	self._rename_input.width = width
	self._rename_input.text = text
	self._rename_input:SelectAll()
	self._rename_input._user_data = callback
end

function IDETool:HandleRenameConfirm(event)
	local callback = self._rename_input._user_data
	self._rename_input._user_data = nil
	if callback == nil then
		return
	end
	self._rename_input.visible = false
	local text = self._rename_input.text
	callback(text)
end

function IDETool:VersionNotice(title, content, confirm_callback)
	if self._version_dialog == nil then
		self._version_dialog = g_Control:CreateControl("ide_version_dialog", self)
		A_LayerManager:AddToModal(self._version_dialog)
	end
	self._version_dialog.visible = true
	self._version_dialog:MoveToTop()
	self._version_dialog.title = title
	self._version_content.text = content
	self._version_dialog._user_data = confirm_callback
end

function IDETool:HandleVersionConfirmClick(event)
	self._version_dialog.visible = false
	local callback = self._version_dialog._user_data
	if callback ~= nil then
		callback()
	end
	self._version_dialog._user_data = nil
end

function IDETool:HandleVersionCancelClick(event)
	self._version_dialog.visible = false
	self._version_dialog._user_data = nil
end

function IDETool:ShowTipHelp(content, show_time)
	if self._tip_help_dialog == nil then
		self._tip_help_dialog = g_Control:CreateControl("ide_tip_help", self)
		g_IDECenter.dialog_layer:AddChild(self._tip_help_dialog)
	end
	if self._tip_help_loop ~= nil then
		if A_LoopSystem:HasUpdater(self._tip_help_loop) then
			self._tip_help_loop:SetCompleted()
			A_LoopSystem:RemoveUpdater(self._tip_help_loop)
		end
		self._tip_help_loop = nil
	end
	self._tip_help_dialog.visible = true
	self._tip_help_dialog.x = A_UISystem.view_width
	self._tip_help_dialog.y = 0
	self._tip_help_content.text = content
	local target_x = A_UISystem.view_width - self._tip_help_dialog.width
	if show_time == nil then
		show_time = 10000
	end
	self._tip_help_loop = ALittle.LoopList()
	local move_in = ALittle.LoopLinear(self._tip_help_dialog, "x", target_x, 1000, 0)
	self._tip_help_loop:AddUpdater(move_in)
	local move_out = ALittle.LoopLinear(self._tip_help_dialog, "x", A_UISystem.view_width, 1000, show_time)
	self._tip_help_loop:AddUpdater(move_out)
	local set_value = ALittle.LoopAttribute(self._tip_help_dialog, "visible", false, 1)
	self._tip_help_loop:AddUpdater(set_value)
	A_LoopSystem:AddUpdater(self._tip_help_loop)
end

function IDETool:HandleTipHelpCloseClick(event)
	if self._tip_help_loop ~= nil then
		if A_LoopSystem:HasUpdater(self._tip_help_loop) then
			self._tip_help_loop:SetCompleted()
			A_LoopSystem:RemoveUpdater(self._tip_help_loop)
		end
		self._tip_help_loop = nil
	end
	self._tip_help_dialog.visible = false
end

g_IDETool = IDETool()
