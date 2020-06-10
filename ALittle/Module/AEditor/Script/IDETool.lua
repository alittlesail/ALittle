-- ALittle Generate Lua And Do Not Edit This Line!
module("AEditor", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDETool = Lua.Class(nil, "AEditor.IDETool")

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

g_IDETool = IDETool()
