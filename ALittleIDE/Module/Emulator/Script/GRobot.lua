-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name = "AUIPlugin.AUIFileSelectFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileEvent", hash_code = 2117383637,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(1517533145, "ALittle.DialogDragEvent", {
name = "ALittle.DialogDragEvent", ns_name = "ALittle", rl_name = "DialogDragEvent", hash_code = 1517533145,
name_list = {"target","delta_x","delta_y"},
type_list = {"ALittle.DisplayObject","double","double"},
option_map = {}
})
ALittle.RegStruct(-1482649531, "ALittle.DialogDragEndEvent", {
name = "ALittle.DialogDragEndEvent", ns_name = "ALittle", rl_name = "DialogDragEndEvent", hash_code = -1482649531,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1419189128, "Emulator.StepInfo", {
name = "Emulator.StepInfo", ns_name = "Emulator", rl_name = "StepInfo", hash_code = 1419189128,
name_list = {"x","y","id","type","next_id","pre_type","next_type","full_name","message_json","delay_ms"},
type_list = {"double","double","int","int","int","int","int","string","string","int"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1161411352, "Emulator.RobotStepLinkInfo", {
name = "Emulator.RobotStepLinkInfo", ns_name = "Emulator", rl_name = "RobotStepLinkInfo", hash_code = 1161411352,
name_list = {"info","dialog","_left_step_image","_right_step_image","_line_tri","pre_link","next_link"},
type_list = {"Emulator.StepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Emulator.RobotStepLinkInfo","Emulator.RobotStepLinkInfo"},
option_map = {}
})
ALittle.RegStruct(-1010534958, "Emulator.PlayerInfo", {
name = "Emulator.PlayerInfo", ns_name = "Emulator", rl_name = "PlayerInfo", hash_code = -1010534958,
name_list = {"client","step_list"},
type_list = {"Lua.ISocket","List<Emulator.RobotStep>"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-628015380, "lua.protobuf_message", {
name = "lua.protobuf_message", ns_name = "lua", rl_name = "protobuf_message", hash_code = -628015380,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-491178481, "Emulator.RobotStepFile", {
name = "Emulator.RobotStepFile", ns_name = "Emulator", rl_name = "RobotStepFile", hash_code = -491178481,
name_list = {"max_id","step_map"},
type_list = {"int","Map<int,Emulator.StepInfo>"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-312899494, "Emulator.RobotStepReceiveMessageLinkInfo", {
name = "Emulator.RobotStepReceiveMessageLinkInfo", ns_name = "Emulator", rl_name = "RobotStepReceiveMessageLinkInfo", hash_code = -312899494,
name_list = {"info","dialog","_left_step_image","_right_step_image","_line_tri","pre_link","next_link","_full_name_input"},
type_list = {"Emulator.StepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Emulator.RobotStepLinkInfo","Emulator.RobotStepLinkInfo","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(162621669, "Emulator.RobotStepDelayLinkInfo", {
name = "Emulator.RobotStepDelayLinkInfo", ns_name = "Emulator", rl_name = "RobotStepDelayLinkInfo", hash_code = 162621669,
name_list = {"info","dialog","_left_step_image","_right_step_image","_line_tri","pre_link","next_link","_delay_input"},
type_list = {"Emulator.StepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Emulator.RobotStepLinkInfo","Emulator.RobotStepLinkInfo","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-81484788, "Emulator.RobotStepSendMessageLinkInfo", {
name = "Emulator.RobotStepSendMessageLinkInfo", ns_name = "Emulator", rl_name = "RobotStepSendMessageLinkInfo", hash_code = -81484788,
name_list = {"info","dialog","_left_step_image","_right_step_image","_line_tri","pre_link","next_link","_full_name_input","_message_edit_btn","message"},
type_list = {"Emulator.StepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Emulator.RobotStepLinkInfo","Emulator.RobotStepLinkInfo","ALittle.DisplayObject","ALittle.DisplayObject","lua.protobuf_message"},
option_map = {}
})

Emulator.RobotStepType = {
	RST_RECEIVE_MESSAGE = 1,
	RST_SEND_MESSAGE = 2,
	RST_DELAY = 3,
}

Emulator.RobotStepLineType = {
	RSLT_LEFT = 1,
	RSLT_RIGHT = 2,
}

Emulator.RobotStep = Lua.Class(nil, "Emulator.RobotStep")

Emulator.RobotStepReceiveMessage = Lua.Class(nil, "Emulator.RobotStepReceiveMessage")

function Emulator.RobotStepReceiveMessage:Ctor(full_name)
	___rawset(self, "_full_name", full_name)
end

function Emulator.RobotStepReceiveMessage:Execute(msg)
	local descriptor = protobuf.message_getdescriptor(msg)
	if descriptor == nil then
		return false
	end
	local full_name = protobuf.messagedescriptor_fullname(descriptor)
	if full_name ~= self._full_name then
		return false
	end
	self._message = msg
	return true
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.GRobot = Lua.Class(ALittle.DisplayLayout, "Emulator.GRobot")

function Emulator.GRobot:Setup()
	self._start_button.visible = true
	self._stop_button.visible = false
	self._login_ip_input.text = Emulator.g_GConfig:GetString("login_ip", "127.0.0.1")
	local data_list = Emulator.g_GConfig:GetConfig("login_ip_list", {})
	if ALittle.List_Find(data_list, self._login_ip_input.text) == nil then
		ALittle.List_Push(data_list, self._login_ip_input.text)
	end
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
	self._login_port_input.text = ALittle.String_ToString(Emulator.g_GConfig:GetInt("login_port", 0))
	self._min_player_id.text = Emulator.g_GConfig:GetInt("min_player_id", 1)
	self._max_player_id.text = Emulator.g_GConfig:GetInt("max_player_id", 1)
	self._blueprint_filetree:SetRoot(Emulator.g_GConfig:GetString("blueprint_root", ""), Lua.Bind(self.HandleFileTreeRightMenu, self))
	self._blueprint_filetree:AddEventListener(___all_struct[2117383637], self, self.HandleFileTreeSelectFile)
	self._blueprint_filetree:SetFold(1, true)
	self._message_edit_dialog = Emulator.g_Control:CreateControl("robot_step_message_edit_dialog", self)
	A_LayerManager:AddToModal(self._message_edit_dialog)
	self._message_edit_dialog.close_callback = Lua.Bind(self.HandleMessageEditDialogClose, self)
end

function Emulator.GRobot:ClearAllPlayer()
	if self._player_map ~= nil then
		for id, info in ___pairs(self._player_map) do
			if info.client ~= nil then
				info.client:Close()
			end
		end
		self._player_map = nil
	end
	self._socket_map = nil
end

function Emulator.GRobot:AddLog(log)
	local at_bottom = self._log_scroll_screen.container_y <= self._log_scroll_screen.container.height - self._log_scroll_screen.view_height + 5
	local item = nil
	if self._log_scroll_screen.child_count > 1000 then
		item = self._log_scroll_screen.childs[1]
		self._log_scroll_screen:RemoveChild(item)
	else
		local container = ALittle.DisplayLayout(Emulator.g_Control)
		container.width_type = 4
		container.height = 20
		local text = Emulator.g_Control:CreateControl("usual_label", nil, container)
		text.x = 5
		text.y_type = 3
		self._log_scroll_screen:AddChild(container)
		container._user_data = text
		item = container
	end
	item._user_data.text = log
	if at_bottom then
		self._log_scroll_screen:ScrollToBottom()
	end
end

function Emulator.GRobot:HandleIpSelectChanged(event)
	self._login_ip_input.text = self._ip_dropdown.text
	self._ip_dropdown.text = ""
end

function Emulator.GRobot:HandleClientSocketDisconnected(player_id, socket)
	local info = self._player_map[player_id]
	if info == nil then
		return
	end
	self._socket_map[info.client] = nil
	self:AddLog("disconnected:" .. player_id)
	info.client = nil
	self._player_map[player_id] = nil
end

function Emulator.GRobot:HandleStartClick(event)
	self:ClearAllPlayer()
	local ip = self._login_ip_input.text
	local port = ALittle.Math_ToInt(self._login_port_input.text)
	if port == nil or port <= 0 then
		g_AUITool:ShowNotice("提示", "请使用正确的端口")
		return
	end
	local min_player_id = ALittle.Math_ToInt(self._min_player_id.text)
	if min_player_id == nil or min_player_id <= 0 then
		g_AUITool:ShowNotice("提示", "玩家ID请填写正整数")
		return
	end
	local max_player_id = ALittle.Math_ToInt(self._max_player_id.text)
	if max_player_id == nil or max_player_id <= 0 then
		g_AUITool:ShowNotice("提示", "玩家ID请填写正整数")
		return
	end
	if min_player_id > max_player_id then
		local temp = min_player_id
		min_player_id = max_player_id
		max_player_id = temp
	end
	local robot_login = _G["__PLUGIN_RobotLogin"]
	if robot_login == nil then
		g_AUITool:ShowNotice("提示", "插件代码中没有定义__PLUGIN_RobotLogin函数")
		return
	end
	local login_func = _G["__PLUGIN_StartLogin"]
	if login_func == nil then
		g_AUITool:ShowNotice("提示", "插件代码中没有定义__PLUGIN_StartLogin函数")
		return
	end
	self._start_button.disabled = true
	self:AddLog("Started!")
	self._player_map = {}
	local id = min_player_id
	while true do
		if not(id <= max_player_id) then break end
		local msg = robot_login(id)
		local call_error, error, client = Lua.TCall(login_func, ip, port, msg)
		if call_error ~= nil then
			error = call_error
		end
		if call_error ~= nil then
			self:AddLog(call_error)
		else
			local info = {}
			self._player_map[id] = info
			self._socket_map[client] = info
			info.client = client
			info.client.disconnect_callback = Lua.Bind(self.HandleClientSocketDisconnected, self, id)
			info.client:ReceiveMessage()
			self:AddLog("login succeed:" .. id)
		end
		id = id+(1)
	end
	self._start_button.disabled = false
	self._start_button.visible = false
	self._stop_button.visible = true
	Emulator.g_GConfig:SetConfig("min_player_id", min_player_id)
	Emulator.g_GConfig:SetConfig("max_player_id", max_player_id)
	Emulator.g_GConfig:SetConfig("login_ip", ip)
	Emulator.g_GConfig:SetConfig("login_port", port)
	local data_list = ALittle.List_Copy(Emulator.g_GConfig:GetConfig("login_ip_list", {}))
	if ALittle.List_Find(data_list, ip) == nil then
		ALittle.List_Push(data_list, ip)
	end
	Emulator.g_GConfig:SetConfig("login_ip_list", data_list)
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
end
Emulator.GRobot.HandleStartClick = Lua.CoWrap(Emulator.GRobot.HandleStartClick)

function Emulator.GRobot:HandleStopClick(event)
	self:ClearAllPlayer()
	self._stop_button.visible = false
	self._start_button.visible = true
	self:AddLog("Stoped!")
end

function Emulator.GRobot:Save(value)
	if self._file_path == nil then
		return
	end
	if self._save == value then
		return
	end
	self._save = value
	if value ~= true then
		self._file_title.text = self._file_path .. "*"
		return
	end
	self._file_title.text = self._file_path
	ALittle.File_SaveFile(self._file_path, ajson.encode(self._step_file), -1)
end

function Emulator.GRobot:HandleCreateRobotStepSendMessage(x, y)
	local info = {}
	self._step_file.max_id = self._step_file.max_id + (1)
	info.id = self._step_file.max_id
	self._step_file.step_map[info.id] = info
	info.x = x
	info.y = y
	info.type = Emulator.RobotStepType.RST_SEND_MESSAGE
	info.full_name = ""
	info.message_json = "{}"
	self:CreateRobotStepDialog(info)
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepSendMessageChanged(event)
	local link_info = event.target._user_data
	link_info.info.full_name = link_info._full_name_input.text
	link_info.message = A_LuaProtobufSchedule:CreateMessage(link_info.info.full_name)
	link_info._message_edit_btn.disabled = link_info.message == nil
	link_info.dialog.title = "发送消息:" .. link_info.info.full_name
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepSendMessageEditClick(event)
	local link_info = event.target._user_data
	if link_info.message == nil then
		g_AUITool:ShowNotice("提示", "消息不存在无法编辑")
		return
	end
	local root = {}
	root.for_show = false
	local tree = Emulator.UtilityCreateTreeMessage(root, link_info.message, "")
	tree.fold = true
	root.detail_info = tree:GetDetailInfo()
	if root.detail_info == nil then
		return
	end
	self._edit_scroll_screen:SetContainer(root.detail_info.tree)
	self._edit_scroll_screen:AdjustScrollBar()
	self._message_edit_dialog.visible = true
	self._message_edit_dialog._user_data = link_info
	self:Save(false)
end

function Emulator.GRobot:HandleCreateRobotStepReceiveMessage(x, y)
	local info = {}
	self._step_file.max_id = self._step_file.max_id + (1)
	info.id = self._step_file.max_id
	self._step_file.step_map[info.id] = info
	info.x = x
	info.y = y
	info.type = Emulator.RobotStepType.RST_RECEIVE_MESSAGE
	info.full_name = ""
	self:CreateRobotStepDialog(info)
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepReceiveMessageChanged(event)
	local link_info = event.target._user_data
	link_info.info.full_name = link_info._full_name_input.text
	link_info.dialog.title = "等待消息:" .. link_info.info.full_name
	self:Save(false)
end

function Emulator.GRobot:HandleCreateRobotStepDelay(x, y)
	local info = {}
	self._step_file.max_id = self._step_file.max_id + (1)
	info.id = self._step_file.max_id
	self._step_file.step_map[info.id] = info
	info.x = x
	info.y = y
	info.type = Emulator.RobotStepType.RST_DELAY
	info.full_name = ""
	info.delay_ms = 0
	self:CreateRobotStepDialog(info)
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepDelayChanged(event)
	local link_info = event.target._user_data
	link_info.info.delay_ms = ALittle.Math_ToInt(link_info._delay_input.text)
	if link_info.info.delay_ms == nil or link_info.info.delay_ms < 0 then
		link_info.info.delay_ms = 0
		link_info._delay_input.text = "0"
	end
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepQuadRButtonDown(event)
	if self._file_path == nil then
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建:发送消息", Lua.Bind(self.HandleCreateRobotStepSendMessage, self, event.rel_x, event.rel_y))
	menu:AddItem("新建:等待消息", Lua.Bind(self.HandleCreateRobotStepReceiveMessage, self, event.rel_x, event.rel_y))
	menu:AddItem("新建:延时", Lua.Bind(self.HandleCreateRobotStepDelay, self, event.rel_x, event.rel_y))
	menu:Show()
end

function Emulator.GRobot:HandleFileTreeRightMenu(user_info, menu)
end

function Emulator.GRobot:HandleRobotStepLineDragBegin(event)
	local link_info = event.target._user_data
	local type = nil
	if link_info._left_step_image == event.target then
		type = Emulator.RobotStepLineType.RSLT_LEFT
	elseif link_info._right_step_image == event.target then
		type = Emulator.RobotStepLineType.RSLT_RIGHT
	end
	if type == nil then
		return
	end
	if link_info.info.next_id ~= nil then
		if link_info.info.pre_type ~= nil and link_info.info.pre_type ~= type then
			return
		end
		self:Save(false)
		if link_info.info.next_type == Emulator.RobotStepLineType.RSLT_LEFT then
			link_info.next_link._left_step_image.disabled = false
		elseif link_info.info.next_type == Emulator.RobotStepLineType.RSLT_RIGHT then
			link_info.next_link._right_step_image.disabled = false
		end
		link_info.info.next_id = nil
		link_info.info.pre_type = nil
		link_info.info.next_type = nil
		link_info.next_link.pre_link = nil
		link_info.next_link = nil
		self._detail_scroll_screen:RemoveChild(link_info._line_tri)
		link_info._line_tri = nil
	end
	self:Save(false)
	local pre_image = event.target
	local tri = Emulator.g_Control:CreateControl("robot_step_triangle")
	tri.disabled = true
	link_info.info.pre_type = type
	local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
	local cur_x = pre_x + event.rel_x
	local cur_y = pre_y + event.rel_y
	tri.x1 = pre_x
	tri.y1 = pre_y + pre_image.height / 2
	tri.x2 = pre_x + pre_image.width
	tri.y2 = pre_y + pre_image.height / 2
	tri.x3 = cur_x
	tri.y3 = cur_y
	self._detail_scroll_screen:AddChild(tri)
	self._cur_line = tri
end

function Emulator.GRobot:HandleRobotStepLineDrag(event)
	if self._cur_line == nil then
		return
	end
	local link_info = event.target._user_data
	self._cur_line.x3 = self._cur_line.x3 + (event.delta_x)
	self._cur_line.y3 = self._cur_line.y3 + (event.delta_y)
end

function Emulator.GRobot:HandleRobotStepLineDragEnd(event)
	if self._cur_line == nil then
		return
	end
	local tri = self._cur_line
	self._detail_scroll_screen:RemoveChild(tri)
	self._cur_line = nil
	local link_info = event.target._user_data
	local pre_type = link_info.info.pre_type
	link_info.info.pre_type = nil
	local image, rel_x, rel_y = A_LayerManager:PickUp(A_UISystem.mouse_x, A_UISystem.mouse_y)
	if image == nil then
		return
	end
	local next_link = image._user_data
	if next_link == nil then
		return
	end
	if next_link.pre_link ~= nil then
		return
	end
	local next_type = nil
	if next_link._left_step_image == image then
		next_type = Emulator.RobotStepLineType.RSLT_LEFT
	elseif next_link._right_step_image == image then
		next_type = Emulator.RobotStepLineType.RSLT_RIGHT
	else
		return
	end
	link_info.info.pre_type = pre_type
	link_info.info.next_id = next_link.info.id
	link_info.info.next_type = next_type
	self:CreateRobotStepLine(link_info.info)
end

function Emulator.GRobot:UpdateRobotStepDialogPosition(link_info, x, y)
	link_info.info.x = x
	link_info.info.y = y
	if link_info._line_tri ~= nil then
		local tri = link_info._line_tri
		local pre_image
		if link_info.info.pre_type == Emulator.RobotStepLineType.RSLT_LEFT then
			pre_image = link_info._left_step_image
		elseif link_info.info.pre_type == Emulator.RobotStepLineType.RSLT_RIGHT then
			pre_image = link_info._right_step_image
		end
		if pre_image ~= nil then
			local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
			tri.x1 = pre_x
			tri.y1 = pre_y + pre_image.height / 2
			tri.x2 = pre_x + pre_image.width
			tri.y2 = pre_y + pre_image.height / 2
		end
	end
	if link_info.pre_link ~= nil then
		local tri = link_info.pre_link._line_tri
		local next_image
		if link_info.pre_link.info.next_type == Emulator.RobotStepLineType.RSLT_LEFT then
			next_image = link_info._left_step_image
		elseif link_info.pre_link.info.next_type == Emulator.RobotStepLineType.RSLT_RIGHT then
			next_image = link_info._right_step_image
		end
		if next_image ~= nil then
			local next_x, next_y = next_image:LocalToGlobal(self._detail_scroll_screen.container)
			tri.x3 = next_x + next_image.width / 2
			tri.y3 = next_y + next_image.height / 2
		end
	end
	self:Save(false)
end

function Emulator.GRobot:HandleRobotStepDrag(event)
	local link_info = event.target._user_data
	self:UpdateRobotStepDialogPosition(link_info, event.target.x, event.target.y)
end

function Emulator.GRobot:HandleRobotStepDragEnd(event)
	local link_info = event.target._user_data
	if event.target.x < 0 then
		event.target.x = 0
	end
	if event.target.y < 0 then
		event.target.y = 0
	end
	self:UpdateRobotStepDialogPosition(link_info, event.target.x, event.target.y)
end

function Emulator.GRobot:HandleRobotStepDelete(dialog)
	self:AskRobotStepDelete(dialog)
	return false
end

function Emulator.GRobot:AskRobotStepDelete(dialog)
	local result = g_AUITool:DeleteNotice("删除", "确定删除当前步骤吗?")
	if result ~= "YES" then
		return
	end
	self._detail_scroll_screen:RemoveChild(dialog)
	local link_info = dialog._user_data
	self._step_file.step_map[link_info.info.id] = nil
	self._link_map[link_info.info.id] = nil
	self:Save(false)
end
Emulator.GRobot.AskRobotStepDelete = Lua.CoWrap(Emulator.GRobot.AskRobotStepDelete)

function Emulator.GRobot:HandleMessageEditDialogClose()
	local link_info = self._message_edit_dialog._user_data
	if link_info.message ~= nil then
		link_info.info.message_json = protobuf.message_jsonencode(link_info.message, true)
	end
	return true
end

function Emulator.GRobot:HandleFileTreeSelectFile(event)
	if event.path == self._file_path then
		return
	end
	self:Save(true)
	self._file_path = event.path
	self._save = true
	self._file_title.text = self._file_path
	local step_file = {}
	local content = ALittle.File_ReadTextFromFile(event.path)
	if content ~= "" then
		local error, json = Lua.TCall(ajson.decode, content)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", "json解析失败!")
			return
		end
		step_file = json
	end
	self._step_file = step_file
	if self._step_file.max_id == nil then
		self._step_file.max_id = 0
	end
	if self._step_file.step_map == nil then
		self._step_file.step_map = {}
	end
	self._link_map = {}
	self._cur_line = nil
	self._detail_scroll_screen:RemoveAllChild()
	for id, info in ___pairs(self._step_file.step_map) do
		self:CreateRobotStepDialog(info)
	end
	for id, info in ___pairs(self._step_file.step_map) do
		self:CreateRobotStepLine(info)
	end
end

function Emulator.GRobot:CreateRobotStepDialog(info)
	if info.type == Emulator.RobotStepType.RST_RECEIVE_MESSAGE then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_receive_message", link_info, info)
		dialog.title = "等待消息:" .. info.full_name
		link_info._full_name_input.text = info.full_name
		link_info._full_name_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepReceiveMessageChanged)
		link_info._full_name_input._user_data = link_info
	elseif info.type == Emulator.RobotStepType.RST_SEND_MESSAGE then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_send_message", link_info, info)
		dialog.title = "发送消息:" .. info.full_name
		link_info._full_name_input.text = info.full_name
		link_info.message = A_LuaProtobufSchedule:CreateMessageByJson(info.full_name, info.message_json)
		link_info._full_name_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepSendMessageChanged)
		link_info._full_name_input._user_data = link_info
		link_info._message_edit_btn:AddEventListener(___all_struct[-449066808], self, self.HandleRobotStepSendMessageEditClick)
		link_info._message_edit_btn._user_data = link_info
	elseif info.type == Emulator.RobotStepType.RST_DELAY then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_delay", link_info, info)
		link_info._delay_input.text = info.delay_ms
	end
end

function Emulator.GRobot:CreateRobotStepLine(info)
	if info.next_id == nil then
		return
	end
	local link_info = self._link_map[info.id]
	if link_info == nil then
		return
	end
	if link_info.next_link ~= nil then
		return
	end
	local next_link = self._link_map[info.next_id]
	if next_link == nil then
		return
	end
	if next_link.pre_link ~= nil then
		return
	end
	local tri = Emulator.g_Control:CreateControl("robot_step_triangle")
	tri._user_data = next_link
	tri.disabled = true
	link_info._line_tri = tri
	local pre_image
	if link_info.info.pre_type == Emulator.RobotStepLineType.RSLT_LEFT then
		pre_image = link_info._left_step_image
	elseif link_info.info.pre_type == Emulator.RobotStepLineType.RSLT_RIGHT then
		pre_image = link_info._right_step_image
	end
	local next_image
	if link_info.info.next_type == Emulator.RobotStepLineType.RSLT_LEFT then
		next_image = next_link._left_step_image
	elseif link_info.info.next_type == Emulator.RobotStepLineType.RSLT_RIGHT then
		next_image = next_link._right_step_image
	end
	if pre_image == nil or next_image == nil then
		return
	end
	link_info.next_link = next_link
	next_link.pre_link = link_info
	local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
	local next_x, next_y = next_image:LocalToGlobal(self._detail_scroll_screen.container)
	tri.x1 = pre_x
	tri.y1 = pre_y + pre_image.height / 2
	tri.x2 = pre_x + pre_image.width
	tri.y2 = pre_y + pre_image.height / 2
	tri.x3 = next_x + next_image.width / 2
	tri.y3 = next_y + next_image.height / 2
	next_image.disabled = true
	self._detail_scroll_screen:AddChild(tri)
end

function Emulator.GRobot:CreateCommonDialog(ui, link_info, info)
	local dialog = Emulator.g_Control:CreateControl(ui, link_info)
	dialog._user_data = link_info
	link_info.dialog = dialog
	link_info.info = info
	link_info._left_step_image._user_data = link_info
	link_info._left_step_image:AddEventListener(___all_struct[1301789264], self, self.HandleRobotStepLineDragBegin)
	link_info._left_step_image:AddEventListener(___all_struct[1337289812], self, self.HandleRobotStepLineDrag)
	link_info._left_step_image:AddEventListener(___all_struct[150587926], self, self.HandleRobotStepLineDragEnd)
	link_info._right_step_image._user_data = link_info
	link_info._right_step_image:AddEventListener(___all_struct[1301789264], self, self.HandleRobotStepLineDragBegin)
	link_info._right_step_image:AddEventListener(___all_struct[1337289812], self, self.HandleRobotStepLineDrag)
	link_info._right_step_image:AddEventListener(___all_struct[150587926], self, self.HandleRobotStepLineDragEnd)
	dialog.x = link_info.info.x
	dialog.y = link_info.info.y
	dialog:AddEventListener(___all_struct[1517533145], self, self.HandleRobotStepDrag)
	dialog:AddEventListener(___all_struct[-1482649531], self, self.HandleRobotStepDragEnd)
	dialog.close_callback = Lua.Bind(self.HandleRobotStepDelete, self, dialog)
	self._detail_scroll_screen:AddChild(dialog, 1)
	self._link_map[info.id] = link_info
	return dialog
end

function Emulator.GRobot:HandleMessage(socket, msg)
	local info = self._socket_map[socket]
	if info == nil then
		return
	end
end

function Emulator.GRobot:HandleSettingChanged()
	self._blueprint_filetree:SetRoot(Emulator.g_GConfig:GetString("blueprint_root", ""), Lua.Bind(self.HandleFileTreeRightMenu, self))
	self._detail_scroll_screen:SetContainer(nil)
	self._log_scroll_screen:RemoveAllChild()
end

end