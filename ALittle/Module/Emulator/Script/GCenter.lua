-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1618605759, "Emulator.DetailInfo", {
name = "Emulator.DetailInfo", ns_name = "Emulator", rl_name = "DetailInfo", hash_code = 1618605759,
name_list = {"tree","message","reflection","info"},
type_list = {"Emulator.IDETreeLogic","lua.protobuf_message","lua.protobuf_reflection","Lua.lua_socket_schedule_message_info"},
option_map = {}
})
ALittle.RegStruct(-628015380, "lua.protobuf_message", {
name = "lua.protobuf_message", ns_name = "lua", rl_name = "protobuf_message", hash_code = -628015380,
name_list = {},
type_list = {},
option_map = {}
})
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
ALittle.RegStruct(-297098024, "lua.protobuf_descriptor", {
name = "lua.protobuf_descriptor", ns_name = "lua", rl_name = "protobuf_descriptor", hash_code = -297098024,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(398889456, "Emulator.RootInfo", {
name = "Emulator.RootInfo", ns_name = "Emulator", rl_name = "RootInfo", hash_code = 398889456,
name_list = {"detail_info"},
type_list = {"Emulator.DetailInfo"},
option_map = {}
})
ALittle.RegStruct(-888044440, "Emulator.LogItemUserData", {
name = "Emulator.LogItemUserData", ns_name = "Emulator", rl_name = "LogItemUserData", hash_code = -888044440,
name_list = {"msg","descriptor","name"},
type_list = {"lua.protobuf_message","lua.protobuf_descriptor","string"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name = "ALittle.UISelectChangedEvent", ns_name = "ALittle", rl_name = "UISelectChangedEvent", hash_code = 444989011,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

g_GConfig = nil
g_GProtoCache = nil
LoginStatus = {
	EMULATOR_IDLE = 0,
	EMULATOR_LOGINING = 1,
	EMULATOR_LOGINED = 2,
}

GCenter = Lua.Class(nil, "Emulator.GCenter")

function GCenter:Ctor()
	___rawset(self, "_proto_search_item_pool", {})
	___rawset(self, "_proto_search_group", {})
	___rawset(self, "_detail_tree_item_pool", {})
	___rawset(self, "_log_search_group", {})
	___rawset(self, "_log_item_list", {})
	___rawset(self, "_log_item_count", 0)
	___rawset(self, "_login_status", LoginStatus.EMULATOR_IDLE)
end

function GCenter:Setup()
	g_GConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/User.cfg")
	g_GProtoCache = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/ProtoCache.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1, 2)
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	g_LayerGroup:AddChild(self._dialog_layer, nil)
	g_Control:CreateControl("main_scene", self, self._main_layer)
	self._setting_dialog = g_Control:CreateControl("main_setting_dialog", self)
	A_LayerManager:AddToModal(self._setting_dialog)
	A_LuaSocketSchedule:Setup()
	local proto_root = g_GConfig:GetString("proto_root", "")
	if proto_root ~= "" and ALittle.File_GetFileAttr(proto_root) ~= nil then
		local error = A_LuaSocketSchedule:LoadProto(proto_root)
		if error == nil then
			g_LWProtobuf:Refresh()
			self:RefreshProtoList()
		end
	end
	local login_proto = g_GConfig:GetString("login_proto", "")
	local msg_info = A_LuaSocketSchedule:GetMessageInfo(login_proto)
	if msg_info ~= nil then
		self._login_detail_info = Utility_CreateTree(msg_info)
		self._login_scroll_screen:SetContainer(self._login_detail_info.tree)
	end
	self._login_button.visible = true
	self._logout_button.visible = false
	self._login_ip_input.text = g_GConfig:GetString("login_ip", "127.0.0.1")
	self._login_port_input.text = ALittle.String_ToString(g_GConfig:GetInt("login_port", 0))
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	self._frame_loop:Start()
end

function GCenter:UpdateFrame(frame_time)
	A_LuaSocketSchedule:RunInFrame()
end

function GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
	self._proto_root_input.text = g_GConfig:GetString("proto_root", "")
	self._login_proto_input.text = g_GConfig:GetString("login_proto", "")
end

function GCenter:HandleSettingConfirmClick(event)
	local attr = ALittle.File_GetFileAttr(self._proto_root_input.text)
	if attr == nil or attr.mode ~= "directory" then
		g_IDETool:ShowNotice("错误", "文件夹不存在")
		return
	end
	self._setting_dialog.visible = false
	g_GConfig:SetConfig("proto_root", self._proto_root_input.text)
	g_LWProtobuf:Clear()
	local error = A_LuaSocketSchedule:LoadProto(self._proto_root_input.text)
	if error ~= nil then
		g_IDETool:ShowNotice("错误", error)
		return
	end
	g_LWProtobuf:Refresh()
	self._protobuf_scroll_screen:RemoveAllChild()
	self._proto_search_item_pool = {}
	self._proto_search_group = {}
	self:RefreshProtoList()
	self._detail_scroll_screen:SetContainer(nil)
	for key, info in ___pairs(self._detail_tree_item_pool) do
		protobuf.freemessage(info.message)
	end
	self._detail_tree_item_pool = {}
	self._log_search_group = {}
	for index, button in ___ipairs(self._log_item_list) do
		local user_data = button._user_data
		protobuf.freemessage(user_data.msg)
	end
	self._log_item_list = {}
	self._log_item_count = 0
	self._log_scroll_screen:RemoveAllChild()
	self:RefreshLogList()
	if self._login_detail_info ~= nil then
		protobuf.freemessage(self._login_detail_info.message)
		self._login_detail_info = nil
	end
	local login_proto = self._login_proto_input.text
	local msg_info = A_LuaSocketSchedule:GetMessageInfo(login_proto)
	if msg_info ~= nil then
		self._login_detail_info = Utility_CreateTree(msg_info)
		self._login_scroll_screen:SetContainer(self._login_detail_info.tree)
	else
		self._login_scroll_screen:SetContainer(nil)
	end
	g_GConfig:SetConfig("login_proto", login_proto)
end

function GCenter:HandleSettingCancelClick(event)
	self._setting_dialog.visible = false
end

function GCenter:HandleProtoSearchClick(event)
	self:RefreshProtoList()
end

function GCenter:RefreshProtoList()
	local key = self._proto_search_key.text
	key = ALittle.String_Upper(key)
	for index, child in ___ipairs(self._protobuf_scroll_screen.childs) do
		child.group = nil
	end
	self._protobuf_scroll_screen:RemoveAllChild()
	local list = A_LuaSocketSchedule:FindMessageByUpperKey(key)
	for index, info in ___ipairs(list) do
		local item = self._proto_search_item_pool[info.name]
		if item == nil then
			item = g_Control:CreateControl("emulator_common_item_radiobutton")
			item.text = info.name
			self._proto_search_item_pool[info.name] = item
			item.drag_trans_target = self._protobuf_scroll_screen
			item._user_data = info
			item:AddEventListener(___all_struct[958494922], self, self.HandleProtoItemSelected)
		end
		item.group = self._proto_search_group
		self._protobuf_scroll_screen:AddChild(item)
	end
	self._protobuf_scroll_screen:RejustScrollBar()
end

function GCenter:HandleProtoItemSelected(event)
	local info = event.target._user_data
	local detail_info = self._detail_tree_item_pool[info.full_name]
	if detail_info == nil then
		detail_info = Utility_CreateTree(info)
		if detail_info == nil then
			return
		end
		self._detail_tree_item_pool[info.full_name] = detail_info
	end
	self._detail_scroll_screen:SetContainer(detail_info.tree)
	self._detail_scroll_screen:RejustScrollBar()
end

function GCenter:HandleLogSearchClick(event)
	self:RefreshLogList()
end

function GCenter:RefreshLogList()
	local key = self._log_search_key.text
	key = ALittle.String_Upper(key)
	for index, child in ___ipairs(self._log_scroll_screen.childs) do
		child.group = nil
	end
	self._log_scroll_screen:RemoveAllChild()
	for index, button in ___ipairs(self._log_item_list) do
		local user_data = button._user_data
		button.group = self._proto_search_group
		self._protobuf_scroll_screen:AddChild(button)
	end
	self._protobuf_scroll_screen:RejustScrollBar()
end

function GCenter:AddLogMessage(msg)
	if self._log_item_count > 500 then
		local item = self._log_item_list[1]
		local user_data = item._user_data
		if self._cur_item_user_data == user_data then
			protobuf.freemessage(user_data.msg)
		end
		self._log_scroll_screen:RemoveChild(item)
		item.group = nil
		ALittle.List_Remove(self._log_item_list, 1)
	end
	local user_data = {}
	user_data.msg = protobuf.clonemessage(msg)
	user_data.descriptor = protobuf.message_getdescriptor(user_data.msg)
	user_data.name = protobuf.messagedescriptor_name(user_data.descriptor)
	local upper_name = ALittle.String_Upper(user_data.name)
	local item = g_Control:CreateControl("emulator_common_item_radiobutton")
	item.text = user_data.name
	item.drag_trans_target = self._protobuf_scroll_screen
	item._user_data = user_data
	item:AddEventListener(___all_struct[444989011], self, self.HandleLogItemSelected)
	self._log_item_count = self._log_item_count + 1
	self._log_item_list[self._log_item_count] = item
	local key = self._log_search_key.text
	key = ALittle.String_Upper(key)
	if ALittle.String_Find(upper_name, key) ~= nil then
		item.group = self._log_search_group
		self._log_scroll_screen:AddChild(item)
	end
end

function GCenter:HandleLogItemSelected(event)
end

function GCenter:HandleSocketDisconnected()
	self._login_button.text = "登陆"
	self._login_status = LoginStatus.EMULATOR_IDLE
end

function GCenter:HandleLoginClick(event)
	local ip = self._login_ip_input.text
	local port = ALittle.Math_ToInt(self._login_port_input.text)
	if port == nil or port <= 0 then
		g_IDETool:ShowNotice("提示", "请使用正确的端口")
		return
	end
	if self._login_detail_info == nil then
		g_IDETool:ShowNotice("提示", "请设置登陆协议")
		return
	end
	if self._login_status == LoginStatus.EMULATOR_LOGINING then
		g_IDETool:ShowNotice("提示", "当前正在登陆，请先断开")
		return
	end
	if self._login_status == LoginStatus.EMULATOR_LOGINED then
		g_IDETool:ShowNotice("提示", "当前已登录，请先断开")
		return
	end
	g_GConfig:SetConfig("login_ip", ip)
	g_GConfig:SetConfig("login_port", port)
	self._login_button.visible = false
	self._logout_button.visible = true
	self._login_status = LoginStatus.EMULATOR_LOGINING
	local error = g_LWProtobuf:StartLogin(ip, port, self._login_detail_info.message)
	if error == nil then
		self._login_status = LoginStatus.EMULATOR_LOGINED
		self._login_button.text = "登陆成功"
	else
		g_IDETool:ShowNotice("提示", error)
		self._login_status = LoginStatus.EMULATOR_IDLE
		self._login_button.text = "登陆"
		self._login_button.visible = true
		self._logout_button.visible = false
	end
end
GCenter.HandleLoginClick = Lua.CoWrap(GCenter.HandleLoginClick)

function GCenter:HandleLogoutClick(event)
	g_LWProtobuf:CloseConnect()
	self._login_button.visible = true
	self._logout_button.visible = false
end

function GCenter:Shutdown()
	self._frame_loop:Stop()
	self._detail_scroll_screen:SetContainer(nil)
	for key, info in ___pairs(self._detail_tree_item_pool) do
		protobuf.freemessage(info.message)
	end
	self._detail_tree_item_pool = {}
	if self._login_detail_info ~= nil then
		protobuf.freemessage(self._login_detail_info.message)
		self._login_detail_info = nil
	end
	self._cur_item_user_data = nil
end

g_GCenter = GCenter()
