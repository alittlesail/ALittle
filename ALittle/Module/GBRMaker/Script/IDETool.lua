-- ALittle Generate Lua And Do Not Edit This Line!
module("GBRMaker", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDETool = Lua.Class(nil, "GBRMaker.IDETool")

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
	if text ~= "" then
		self._rename_input:SelectAll()
	end
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

function IDETool:HandleRenameCancel(event)
	if event.sym ~= 27 then
		return
	end
	local callback = self._rename_input._user_data
	self._rename_input._user_data = nil
	self._rename_input.visible = false
end

g_IDETool = IDETool()
