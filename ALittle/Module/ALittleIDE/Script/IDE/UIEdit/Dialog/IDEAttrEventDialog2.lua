-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAttrEventItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAttrEventItem")

function ALittleIDE.IDEAttrEventItem:Init(dialog, name, handle)
	self._dialog = dialog
	self._name.text = name
	self._handle.text = handle
end

function ALittleIDE.IDEAttrEventItem:HandleDeleteClick(event)
	self._dialog:DeleteItem(self)
end

function ALittleIDE.IDEAttrEventItem:HandleGotoClick(event)
	local target_class = self._dialog:GetParentTargetClass()
	if target_class == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	local info = ALittleIDE.g_IDEProject.project.code:FindGoto(target_class .. "." .. self._name.text .. "." .. self._handle.text)
	if info ~= nil then
		ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(info.file_path, info.line_start, info.char_start, info.line_end, info.char_end)
	end
end
ALittleIDE.IDEAttrEventItem.HandleGotoClick = Lua.CoWrap(ALittleIDE.IDEAttrEventItem.HandleGotoClick)

function ALittleIDE.IDEAttrEventItem:HandleNameChanged(event)
	local target_class = self._dialog:GetParentTargetClass()
	if target_class == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	g_AUICodeFilterScreen:ShowComplete(ALittleIDE.g_IDEProject.project.code, target_class, self._name)
end

function ALittleIDE.IDEAttrEventItem:HandleHandleChanged(event)
	local target_class = self._dialog:GetParentTargetClass()
	if target_class == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	g_AUICodeFilterScreen:ShowComplete(ALittleIDE.g_IDEProject.project.code, target_class, self._handle)
end

function ALittleIDE.IDEAttrEventItem:GetContent()
	if self._name.text == "" then
		return nil
	end
	if self._handle.text == "" then
		return nil
	end
	return self._name.text .. ":" .. self._handle.text
end

ALittleIDE.IDEAttrEventDialog2 = Lua.Class(nil, "ALittleIDE.IDEAttrEventDialog2")

function ALittleIDE.IDEAttrEventDialog2:ShowDialog(target_panel, text, need_reset)
	if self._dialog == nil then
		self._dialog = ALittleIDE.g_Control:CreateControl("ide_event_edit_dialog2", self)
		A_LayerManager:AddToModal(self._dialog)
	end
	self._dialog.visible = true
	self._target_panel = target_panel
	self._target_text = text
	self._target_need_reset = need_reset
	self:ResetText()
end

function ALittleIDE.IDEAttrEventDialog2:HideDialog()
	self._dialog.visible = false
end

function ALittleIDE.IDEAttrEventDialog2:IsShow()
	if self._dialog == nil then
		return false
	end
	return self._dialog.visible
end

function ALittleIDE.IDEAttrEventDialog2:GetParentTargetClass()
	return self._target_panel:GetParentTargetClass()
end

function ALittleIDE.IDEAttrEventDialog2:HandleAddItem(event)
	local item = ALittleIDE.g_Control:CreateControl("ide_event_item")
	item:Init(self, "", "")
	self._event_scroll_screen:AddChild(item)
end

function ALittleIDE.IDEAttrEventDialog2:DeleteItem(item)
	self._event_scroll_screen:RemoveChild(item)
end

function ALittleIDE.IDEAttrEventDialog2:HandleEventConfirm(event)
	local content_list = {}
	for index, child in ___ipairs(self._event_scroll_screen.childs) do
		local text = child:GetContent()
		if text ~= nil then
			ALittle.List_Push(content_list, text)
		end
	end
	local content = ALittle.String_Join(content_list, "\r\n")
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
		g_AUITool:ShowNotice("警告", "事件编辑有错误，请检查")
		return
	end
	self._dialog.visible = false
	if event_data == nil then
		return
	end
	self._target_panel["_" .. self._target_text].text = ALittle.String_JsonEncode(event_data)
	self._target_panel:TableDataSet(self._target_text, false)
end

function ALittleIDE.IDEAttrEventDialog2:ResetText()
	local info = self._target_panel.base[self._target_text]
	if info == nil then
		info = self._target_panel.default[self._target_text]
	end
	if info == nil then
		info = {}
	end
	for index, event_info in ___ipairs(info) do
		local item = ALittleIDE.g_Control:CreateControl("ide_event_item")
		item:Init(self, event_info.type, event_info.func)
		self._event_scroll_screen:AddChild(item)
	end
	self._revoke_list = ALittle.RevokeList()
end

function ALittleIDE.IDEAttrEventDialog2:HandleEventKeyDown(event)
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

ALittleIDE.g_IDEAttrEventDialog2 = ALittleIDE.IDEAttrEventDialog2()
end