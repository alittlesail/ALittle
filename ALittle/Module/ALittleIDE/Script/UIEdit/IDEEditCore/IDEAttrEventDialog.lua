
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

IDEAttrEventDialog = Lua.Class(nil, "ALittleIDE.IDEAttrEventDialog")

function IDEAttrEventDialog:ShowDialog(target_panel, text, need_reset)
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_event_edit_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._dialog.visible = true
	self._target_panel = target_panel
	self._target_text = text
	self._target_need_reset = need_reset
	self:ResetText()
	A_UISystem.focus = self._event_edit.show_edit
end

function IDEAttrEventDialog:HideDialog()
	self._dialog.visible = false
end

function IDEAttrEventDialog:IsShow()
	if self._dialog == nil then
		return false
	end
	return self._dialog.visible
end

function IDEAttrEventDialog:HandleEventConfirm(event)
	local content = self._event_edit.text
	if content == "" then
		self._dialog.visible = false
		local object = self._target_panel["_" .. self._target_text]
		object.text = ""
		self._target_panel:TableDataSet(self._target_text, false)
		return
	end
	local has_error = false
	local event_list = ALittle.String_SplitSepList(content, {"\n", "\r"})
	local event_data = nil
	for index, event_string in ___ipairs(event_list) do
		if event_data == nil then
			event_data = {}
		end
		local event_info = nil
		local event_split = ALittle.String_Split(ALittle.String_Trim(event_string), ":")
		local event_count = ALittle.List_MaxN(event_split)
		if event_count == 2 then
			event_info = {}
			event_info.type = event_split[1]
			event_info.func = event_split[2]
		end
		if event_info ~= nil then
			ALittle.List_Push(event_data, event_info)
		else
			has_error = true
		end
	end
	if event_data == nil or has_error then
		g_IDETool:ShowNotice("警告", "事件编辑有错误，请检查")
		return
	end
	self._dialog.visible = false
	if event_data == nil then
		return
	end
	self._target_panel["_" .. self._target_text].text = ALittle.String_JsonEncode(event_data)
	self._target_panel:TableDataSet(self._target_text, false)
end

function IDEAttrEventDialog:ResetText()
	local info = self._target_panel.base[self._target_text]
	if info == nil then
		info = self._target_panel.default[self._target_text]
	end
	if info == nil then
		info = {}
	end
	local content = {}
	local content_count = 0
	for index, event_info in ___ipairs(info) do
		local data_type = event_info.type .. ":"
		local event_string = data_type .. event_info.func
		content_count = content_count + 1
		content[content_count] = event_string
	end
	local content_str = ALittle.String_Join(content, "\n")
	self._event_edit.text = content_str
	self._edit_old_text = content_str
	self._revoke_list = IDERevokeList()
end

function IDEAttrEventDialog:ShowEventSelectDialog(x, y)
	if self._select_dialog == nil then
		self._select_dialog = g_Control:CreateControl("ide_event_select_screen", self)
		for k, v in ___ipairs(g_IDEEnum.event_type_list) do
			local button = g_Control:CreateControl("ide_common_item_button")
			button.text = v
			button:AddEventListener(___all_struct[-449066808], self, self.HandleEventSelectClick)
			button.drag_trans_target = self._select_dialog
			self._select_dialog:AddChild(button)
		end
	end
	self._select_dialog.x = x
	self._select_dialog.y = y
	A_LayerManager:ShowFromRight(self._select_dialog)
end

function IDEAttrEventDialog:HandleEventSelectClick(event)
	A_LayerManager:HideFromRight(self._select_dialog)
	local text = event.target.text
	self._event_edit:InsertText("ALittle." .. text)
end

function IDEAttrEventDialog:HandleEventRightButtonDown(event)
	self:ShowEventSelectDialog(A_UISystem.mouse_x, A_UISystem.mouse_y)
end

function IDEAttrEventDialog:HandleEventChange(event)
	local edit_new_text = self._event_edit.text
	local revoke = IDETextEditRevoke(self._event_edit, self._edit_old_text, edit_new_text)
	self._edit_old_text = edit_new_text
	self._revoke_list:PushRevoke(revoke)
end

function IDEAttrEventDialog:HandleEventKeyDown(event)
	local ctrl = A_UISystem.sym_map[1073742048]
	if ctrl == nil then
		return false
	end
	local z = A_UISystem.sym_map[122]
	if z then
		self._revoke_list:UndoRevoke()
	end
	return true
end

g_IDEAttrEventDialog = IDEAttrEventDialog()
