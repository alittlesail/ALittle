-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1835920059, "lua.protobuf_reflection", {
name = "lua.protobuf_reflection", ns_name = "lua", rl_name = "protobuf_reflection", hash_code = 1835920059,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1628431371, "Lua.lua_socket_schedule_message_info", {
name = "Lua.lua_socket_schedule_message_info", ns_name = "Lua", rl_name = "lua_socket_schedule_message_info", hash_code = 1628431371,
name_list = {"descriptor","full_name","name"},
type_list = {"lua.protobuf_descriptor","string","string"},
option_map = {}
})
ALittle.RegStruct(1618605759, "Emulator.DetailInfo", {
name = "Emulator.DetailInfo", ns_name = "Emulator", rl_name = "DetailInfo", hash_code = 1618605759,
name_list = {"tree","message","reflection","info"},
type_list = {"Emulator.IDETreeLogic","lua.protobuf_message","lua.protobuf_reflection","Lua.lua_socket_schedule_message_info"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-888044440, "Emulator.LogItemUserData", {
name = "Emulator.LogItemUserData", ns_name = "Emulator", rl_name = "LogItemUserData", hash_code = -888044440,
name_list = {"msg","info","upper_name","json_content"},
type_list = {"lua.protobuf_message","Lua.lua_socket_schedule_message_info","string","string"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-628015380, "lua.protobuf_message", {
name = "lua.protobuf_message", ns_name = "lua", rl_name = "protobuf_message", hash_code = -628015380,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(398889456, "Emulator.RootInfo", {
name = "Emulator.RootInfo", ns_name = "Emulator", rl_name = "RootInfo", hash_code = 398889456,
name_list = {"detail_info","for_show"},
type_list = {"Emulator.DetailInfo","bool"},
option_map = {}
})
ALittle.RegStruct(-297098024, "lua.protobuf_descriptor", {
name = "lua.protobuf_descriptor", ns_name = "lua", rl_name = "protobuf_descriptor", hash_code = -297098024,
name_list = {},
type_list = {},
option_map = {}
})

Emulator.g_GConfig = nil
Emulator.g_GProtoCache = nil
Emulator.LoginStatus = {
	EMULATOR_IDLE = 0,
	EMULATOR_LOGINING = 1,
	EMULATOR_LOGINED = 2,
}

Emulator.GCenter = Lua.Class(nil, "Emulator.GCenter")

function Emulator.GCenter:Ctor()
	___rawset(self, "_proto_search_item_pool", {})
	___rawset(self, "_proto_search_group", {})
	___rawset(self, "_detail_tree_item_pool", {})
	___rawset(self, "_log_search_group", {})
	___rawset(self, "_log_item_list", {})
	___rawset(self, "_log_item_count", 0)
	___rawset(self, "_login_status", Emulator.LoginStatus.EMULATOR_IDLE)
end

function Emulator.GCenter:Setup()
	Emulator.g_GConfig = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath .. "/User.cfg")
	Emulator.g_GProtoCache = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath .. "/ProtoCache.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(Emulator.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	Emulator.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(Emulator.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	Emulator.g_LayerGroup:AddChild(self._dialog_layer, nil)
	Emulator.g_Control:CreateControl("main_scene", self, self._main_layer)
	self._main_tab:DisableAllCloseButton()
	self._main_tab.tab_index = 1
	self._setting_dialog = Emulator.g_Control:CreateControl("main_setting_dialog", self)
	A_LayerManager:AddToModal(self._setting_dialog)
	self._log_fliter_dialog = Emulator.g_Control:CreateControl("main_log_fliter_dialog", self)
	self._dialog_layer:AddChild(self._log_fliter_dialog)
	self._log_fliter_dialog.visible = false
	self._fliter_map = {}
	local fliter_list = Emulator.g_GConfig:GetConfig("fliter_list", {})
	for index, fliter in ___ipairs(fliter_list) do
		self._fliter_map[fliter] = true
	end
	local plugin_path = Emulator.g_GConfig:GetString("plugin_script", "")
	if ALittle.File_GetFileExtByPathAndUpper(plugin_path) == "LUA" then
		local plugin_script = ALittle.File_ReadTextFromStdFile(plugin_path)
		if plugin_script ~= nil then
			RunScript(plugin_script, plugin_path)
		else
			self:HandleShowSettingDialog(nil)
		end
	else
		self:HandleShowSettingDialog(nil)
	end
	local proto_root = Emulator.g_GConfig:GetString("proto_root", "")
	if proto_root ~= "" and ALittle.File_GetFileAttr(proto_root) ~= nil then
		local error = A_LuaProtobufSchedule:LoadProto(proto_root)
		if error == nil then
			local func = _G["__PLUGIN_ProtoRefresh"]
			if func ~= nil then
				error = Lua.TCall(func)
				if error ~= nil then
					ALittle.Log(error)
				end
			end
			self:RefreshProtoList()
		else
			self:HandleShowSettingDialog(nil)
		end
	end
	local login_proto = Emulator.g_GConfig:GetString("login_proto", "")
	local msg_info = A_LuaProtobufSchedule:GetMessageInfo(login_proto)
	if msg_info ~= nil then
		self._login_detail_info = Emulator.Utility_CreateTreeForEdit(msg_info)
		self._login_scroll_screen:SetContainer(self._login_detail_info.tree)
	end
	self._login_button.visible = true
	self._logout_button.visible = false
	self._login_ip_input.text = Emulator.g_GConfig:GetString("login_ip", "127.0.0.1")
	local data_list = Emulator.g_GConfig:GetConfig("login_ip_list", {})
	if ALittle.List_Find(data_list, self._login_ip_input.text) == nil then
		ALittle.List_Push(data_list, self._login_ip_input.text)
	end
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
	self._login_port_input.text = ALittle.String_ToString(Emulator.g_GConfig:GetInt("login_port", 0))
	self._right_grad3_ud.up_size = Emulator.g_GConfig:GetDouble("right_grid3_up_size", self._right_grad3_ud.up_size)
	self._main_grid3_lr.down_size = Emulator.g_GConfig:GetDouble("main_grid3_down_size", self._main_grid3_lr.down_size)
	self._send_button.disabled = true
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	self._frame_loop:Start()
	self._json_codeedit = AUIPlugin.AUICodeEdit.Create()
	self._json_codeedit.editable = false
	self._json_container:AddChild(self._json_codeedit)
end

function Emulator.GCenter:UpdateFrame(frame_time)
	A_LuaProtobufSchedule:RunInFrame()
end

function Emulator.GCenter:HandleIpSelectChanged(event)
	self._login_ip_input.text = self._ip_dropdown.text
	self._ip_dropdown.text = ""
end

function Emulator.GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
	self._proto_root_input.text = Emulator.g_GConfig:GetString("proto_root", "")
	self._login_proto_input.text = Emulator.g_GConfig:GetString("login_proto", "")
	self._plugin_file_input.text = Emulator.g_GConfig:GetString("plugin_script", "")
end

function Emulator.GCenter:HandleShowVersionDialog(event)
	Emulator.g_VersionManager:ShowDialog()
end

function Emulator.GCenter:HandleSettingSelectProtoRootClick(event)
	if event.path == nil then
		return
	end
	self._proto_root_input.text = event.path
end

function Emulator.GCenter:HandleSettingSelectPluginScriptClick(event)
	if event.path == nil then
		return
	end
	self._plugin_file_input.text = event.path
end

function Emulator.GCenter:HandleSettingGeneratePluginScriptClick(event)
	if event.path == nil then
		return
	end
	self._plugin_file_input.text = event.path .. "\\TemplatePlugin.lua"
	Emulator.g_GConfig:SetConfig("plugin_script", self._plugin_file_input.text)
	ALittle.File_CopyFile(Emulator.g_ModuleBasePath .. "Other/TemplatePlugin.lua", self._plugin_file_input.text)
end

function Emulator.GCenter:HandleSettingConfirmClick(event)
	local attr = ALittle.File_GetFileAttr(self._proto_root_input.text)
	if attr == nil or attr.directory ~= true then
		g_AUITool:ShowNotice("错误", "文件夹不存在")
		return
	end
	local error = A_LuaProtobufSchedule:LoadProto(self._proto_root_input.text)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	if ALittle.File_GetFileExtByPathAndUpper(self._plugin_file_input.text) == "LUA" then
		_G["__PLUGIN_ProtoRefresh"] = nil
		_G["__PLUGIN_StartLogin"] = nil
		_G["__SOCKET_ReadMessage"] = nil
		_G["__SOCKET_WriteMessage"] = nil
		_G["__SOCKET_HandleMessage"] = nil
		local plugin_script = ALittle.File_ReadTextFromStdFile(self._plugin_file_input.text)
		if plugin_script ~= nil then
			RunScript(plugin_script, self._plugin_file_input.text)
		end
	else
		g_AUITool:ShowNotice("错误", "插件脚本必须是lua脚本")
		return
	end
	self._setting_dialog.visible = false
	Emulator.g_GConfig:SetConfig("proto_root", self._proto_root_input.text)
	local func = _G["__PLUGIN_ProtoRefresh"]
	if func ~= nil then
		error = Lua.TCall(func)
		if error ~= nil then
			ALittle.Log(error)
		end
	end
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	self._protobuf_scroll_screen:RemoveAllChild()
	self._proto_search_item_pool = {}
	self._proto_search_group = {}
	self:RefreshProtoList()
	self._detail_scroll_screen:SetContainer(nil)
	self._detail_tree_item_pool = {}
	self._log_search_group = {}
	self._log_item_list = {}
	self._log_item_count = 0
	self._log_scroll_screen:RemoveAllChild()
	self:RefreshLogList()
	self._login_detail_info = nil
	local login_proto = self._login_proto_input.text
	local msg_info = A_LuaProtobufSchedule:GetMessageInfo(login_proto)
	if msg_info ~= nil then
		self._login_detail_info = Emulator.Utility_CreateTreeForEdit(msg_info)
		self._login_scroll_screen:SetContainer(self._login_detail_info.tree)
	else
		self._login_scroll_screen:SetContainer(nil)
	end
	Emulator.g_GConfig:SetConfig("login_proto", login_proto)
	Emulator.g_GConfig:SetConfig("plugin_script", self._plugin_file_input.text)
end

function Emulator.GCenter:HandleSettingCancelClick(event)
	self._setting_dialog.visible = false
end

function Emulator.GCenter:HandleProtoSearchClick(event)
	self:RefreshProtoList()
end

function Emulator.GCenter:RefreshProtoList()
	local key = self._proto_search_key.text
	key = ALittle.String_Upper(key)
	local key_list = ALittle.String_SplitSepList(key, {" ", "\t"})
	for index, child in ___ipairs(self._protobuf_scroll_screen.childs) do
		child.group = nil
	end
	self._protobuf_scroll_screen:RemoveAllChild()
	local list
	if ALittle.List_MaxN(key_list) == 0 then
		list = A_LuaProtobufSchedule:FindMessageByUpperKey("")
	else
		list = A_LuaProtobufSchedule:FindMessageByUpperKeyList(key_list)
	end
	for index, info in ___ipairs(list) do
		local item = self._proto_search_item_pool[info.name]
		if item == nil then
			item = Emulator.g_Control:CreateControl("item_radiobutton")
			item.text = info.name
			self._proto_search_item_pool[info.name] = item
			item.drag_trans_target = self._protobuf_scroll_screen
			item._user_data = info
			item:AddEventListener(___all_struct[958494922], self, self.HandleProtoItemSelected)
			item:AddEventListener(___all_struct[-641444818], self, self.HandleProtoItemRButtonDown)
		end
		local detail_info = self._detail_tree_item_pool[info.full_name]
		item.selected = detail_info ~= nil and detail_info.tree == self._detail_scroll_screen.container
		item.group = self._proto_search_group
		self._protobuf_scroll_screen:AddChild(item)
	end
	self._protobuf_scroll_screen:AdjustScrollBar()
end

function Emulator.GCenter:HandleProtoItemSelected(event)
	local info = event.target._user_data
	local detail_info = self._detail_tree_item_pool[info.full_name]
	if detail_info == nil then
		detail_info = Emulator.Utility_CreateTreeForEdit(info)
		if detail_info == nil then
			return
		end
		self._detail_tree_item_pool[info.full_name] = detail_info
	end
	self._detail_scroll_screen:SetContainer(detail_info.tree)
	self._detail_scroll_screen:AdjustScrollBar()
end

function Emulator.GCenter:HandleProtoItemRButtonDown(event)
	local info = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("复制名称", Lua.Bind(ALittle.System_SetClipboardText, info.name))
	menu:AddItem("复制全称", Lua.Bind(ALittle.System_SetClipboardText, info.full_name))
	menu:AddItem("过滤", Lua.Bind(self.AddFliter, self, info.full_name))
	menu:Show()
end

function Emulator.GCenter:HandleLogSearchClick(event)
	self:RefreshLogList()
end

function Emulator.GCenter:HandleLogClearClick(event)
	self._log_search_key.text = ""
	self._log_item_list = {}
	self._log_item_count = 0
	self._log_scroll_screen:RemoveAllChild()
	self._cur_item_user_data = nil
	self._json_codeedit:OnClose()
end

function Emulator.GCenter:HandleLogFliterClick(event)
	self._log_fliter_dialog.visible = true
	local fliter_list = Emulator.g_GConfig:GetConfig("fliter_list", {})
	self._log_fliter_edit.text = ALittle.String_Join(fliter_list, "\n")
	self._log_fliter_edit:DelayFocus()
end

function Emulator.GCenter:HandleLogFliterCancelClick(event)
	self._log_fliter_dialog.visible = false
end

function Emulator.GCenter:HandleLogFliterConfirmClick(event)
	self._log_fliter_dialog.visible = false
	local fliter_list = ALittle.String_SplitSepList(self._log_fliter_edit.text, {"\r", "\n"})
	Emulator.g_GConfig:SetConfig("fliter_list", fliter_list)
	self._fliter_map = {}
	for index, fliter in ___ipairs(fliter_list) do
		self._fliter_map[fliter] = true
	end
end

function Emulator.GCenter:RefreshLogList()
	local key = self._log_search_key.text
	key = ALittle.String_Upper(key)
	for index, child in ___ipairs(self._log_scroll_screen.childs) do
		child.group = nil
	end
	self._log_scroll_screen:RemoveAllChild()
	for index, button in ___ipairs(self._log_item_list) do
		local user_data = button._user_data
		if ALittle.String_Find(user_data.upper_name, key) ~= nil then
			button.group = self._log_search_group
			self._log_scroll_screen:AddChild(button)
		end
	end
	self._log_scroll_screen:AdjustScrollBar()
end

function Emulator.GCenter:AddLogMessage(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	local full_name = protobuf.messagedescriptor_fullname(descriptor)
	if self._fliter_map[full_name] ~= nil then
		return
	end
	if self._log_item_count > 500 then
		local item = self._log_item_list[1]
		local user_data = item._user_data
		if self._cur_item_user_data == user_data then
			self._json_codeedit:OnClose()
		end
		self._log_scroll_screen:RemoveChild(item)
		item.group = nil
		ALittle.List_Remove(self._log_item_list, 1)
	end
	local user_data = {}
	user_data.info = A_LuaProtobufSchedule:GetMessageInfoByMessage(msg)
	user_data.msg = protobuf.clonemessage(msg)
	user_data.upper_name = ALittle.String_Upper(user_data.info.name)
	local item = Emulator.g_Control:CreateControl("item_radiobutton")
	item.text = user_data.info.name
	item.drag_trans_target = self._log_scroll_screen
	item._user_data = user_data
	item:AddEventListener(___all_struct[958494922], self, self.HandleLogItemSelected)
	item:AddEventListener(___all_struct[-641444818], self, self.HandleProtoLogRButtonDown)
	self._log_item_count = self._log_item_count + 1
	self._log_item_list[self._log_item_count] = item
	local key = self._log_search_key.text
	key = ALittle.String_Upper(key)
	if ALittle.String_Find(user_data.upper_name, key) ~= nil then
		local bottom = self._log_scroll_screen.right_scrollbar.offset_rate >= 0.95 or self._log_scroll_screen.container.height < self._log_scroll_screen.view_height
		item.group = self._log_search_group
		self._log_scroll_screen:AddChild(item)
		if bottom then
			self._log_scroll_screen:ScrollToBottom()
		end
	end
end

function Emulator.GCenter:HandleLogItemSelected(event)
	self._show_search_key.text = ""
	self._cur_item_user_data = event.target._user_data
	if self._cur_item_user_data.json_content == nil then
		self._cur_item_user_data.json_content = protobuf.message_jsonencode(self._cur_item_user_data.msg, false)
	end
	self._json_codeedit:OnClose()
	self._json_codeedit:Load("temp.json", self._cur_item_user_data.json_content, nil)
end

function Emulator.GCenter:HandleProtoLogRButtonDown(event)
	local info = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("复制名称", Lua.Bind(ALittle.System_SetClipboardText, info.info.name))
	menu:AddItem("复制全称", Lua.Bind(ALittle.System_SetClipboardText, info.info.full_name))
	menu:AddItem("过滤", Lua.Bind(self.AddFliter, self, info.info.full_name))
	menu:Show()
end

function Emulator.GCenter:HandleShowSearchClick(event)
	if self._cur_item_user_data == nil then
		return
	end
	local key = self._show_search_key.text
	self._json_codeedit:FindNext(key)
end

function Emulator.GCenter:AddFliter(full_name)
	self._fliter_map[full_name] = true
	local list = {}
	for name, _ in ___pairs(self._fliter_map) do
		ALittle.List_Push(list, name)
	end
	Emulator.g_GConfig:SetConfig("fliter_list", list)
end

function Emulator.GCenter:HandleClientSocketDisconnected(socket)
	self._client_socket = nil
	self._send_button.disabled = true
	self._login_button.visible = true
	self._logout_button.visible = false
	if self._login_status == Emulator.LoginStatus.EMULATOR_LOGINED then
		local func = _G["__PLUGIN_HandleLogout"]
		if func ~= nil then
			local error = Lua.TCall(func)
			if error ~= nil then
				ALittle.Log(error)
			end
		end
	end
	self._login_status = Emulator.LoginStatus.EMULATOR_IDLE
end

function Emulator.GCenter:HandleSendClick(event)
	local tree = self._detail_scroll_screen.container
	if tree == nil then
		return
	end
	local detail_info = tree:GetDetailInfo()
	if self._client_socket ~= nil then
		self._client_socket:SendMessage(detail_info.message)
	end
end

function Emulator.GCenter:HandleLoginClick(event)
	local ip = self._login_ip_input.text
	local port = ALittle.Math_ToInt(self._login_port_input.text)
	if port == nil or port <= 0 then
		g_AUITool:ShowNotice("提示", "请使用正确的端口")
		return
	end
	if self._login_detail_info == nil then
		g_AUITool:ShowNotice("提示", "请设置登陆协议")
		return
	end
	if self._login_status == Emulator.LoginStatus.EMULATOR_LOGINING then
		g_AUITool:ShowNotice("提示", "当前正在登陆，请先断开")
		return
	end
	if self._login_status == Emulator.LoginStatus.EMULATOR_LOGINED then
		g_AUITool:ShowNotice("提示", "当前已登录，请先断开")
		return
	end
	Emulator.g_GConfig:SetConfig("login_ip", ip)
	Emulator.g_GConfig:SetConfig("login_port", port)
	local data_list = ALittle.List_Copy(Emulator.g_GConfig:GetConfig("login_ip_list", {}))
	if ALittle.List_Find(data_list, ip) == nil then
		ALittle.List_Push(data_list, ip)
	end
	Emulator.g_GConfig:SetConfig("login_ip_list", data_list)
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
	self._login_button.visible = false
	self._logout_button.visible = true
	self._login_status = Emulator.LoginStatus.EMULATOR_LOGINING
	local error = nil
	if self._client_socket ~= nil then
		self._client_socket:Close()
		self._client_socket = nil
	end
	local login_func = _G["__PLUGIN_StartLogin"]
	if login_func == nil then
		error = "还未加载插件"
	else
		local call_error = nil
		call_error, error, self._client_socket = Lua.TCall(login_func, ip, port, self._login_detail_info.message)
		if call_error ~= nil then
			error = call_error
		end
	end
	if error == nil then
		if self._client_socket ~= nil then
			self._client_socket.disconnect_callback = Lua.Bind(self.HandleClientSocketDisconnected, self)
			self._client_socket:ReceiveMessage()
		end
		self._login_status = Emulator.LoginStatus.EMULATOR_LOGINED
		self._send_button.disabled = false
	else
		g_AUITool:ShowNotice("提示", error)
		self._login_status = Emulator.LoginStatus.EMULATOR_IDLE
		self._login_button.visible = true
		self._logout_button.visible = false
	end
end
Emulator.GCenter.HandleLoginClick = Lua.CoWrap(Emulator.GCenter.HandleLoginClick)

function Emulator.GCenter:HandleLogoutClick(event)
	if self._client_socket ~= nil then
		self._client_socket:Close()
		self._client_socket = nil
	end
	self._send_button.disabled = true
	self._login_button.visible = true
	self._logout_button.visible = false
	if self._login_status == Emulator.LoginStatus.EMULATOR_LOGINED then
		local func = _G["__PLUGIN_HandleLogout"]
		if func ~= nil then
			local error = Lua.TCall(func)
			if error ~= nil then
				ALittle.Log(error)
			end
		end
	end
	self._login_status = Emulator.LoginStatus.EMULATOR_IDLE
end

function Emulator.GCenter:HandleDragRightQuadUD(event)
	self._right_grad3_ud.up_size = self._right_grad3_ud.up_size + (event.delta_y)
end

function Emulator.GCenter:HandleDragEndRightQuadUD(event)
	Emulator.g_GConfig:SetConfig("right_grid3_up_size", self._right_grad3_ud.up_size)
end

function Emulator.GCenter:HandleDragRightQuadLR(event)
	self._main_grid3_lr.down_size = self._main_grid3_lr.down_size - (event.delta_x)
end

function Emulator.GCenter:HandleDragEndRightQuadLR(event)
	Emulator.g_GConfig:SetConfig("main_grid3_down_size", self._main_grid3_lr.down_size)
end

function Emulator.GCenter:HandleSetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function Emulator.GCenter:HandleSetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function Emulator.GCenter:HandleSetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

function Emulator.GCenter:Shutdown()
	self._frame_loop:Stop()
end

_G.g_GCenter = Emulator.GCenter()
end