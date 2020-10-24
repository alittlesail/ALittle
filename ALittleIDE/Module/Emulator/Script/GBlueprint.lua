-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1971745271, "ALittle.DialogDragBeginEvent", {
name = "ALittle.DialogDragBeginEvent", ns_name = "ALittle", rl_name = "DialogDragBeginEvent", hash_code = 1971745271,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1613357887, "Emulator.RobotStepReceiveLogInfo", {
name = "Emulator.RobotStepReceiveLogInfo", ns_name = "Emulator", rl_name = "RobotStepReceiveLogInfo", hash_code = -1613357887,
name_list = {"dst_field"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(1517533145, "ALittle.DialogDragEvent", {
name = "ALittle.DialogDragEvent", ns_name = "ALittle", rl_name = "DialogDragEvent", hash_code = 1517533145,
name_list = {"target","delta_x","delta_y"},
type_list = {"ALittle.DisplayObject","double","double"},
option_map = {}
})
ALittle.RegStruct(1512397058, "Emulator.RobotStepReceiveLogLinkInfo", {
name = "Emulator.RobotStepReceiveLogLinkInfo", ns_name = "Emulator", rl_name = "RobotStepReceiveLogLinkInfo", hash_code = 1512397058,
name_list = {"item","log","_delete_button","_dst_field_input"},
type_list = {"ALittle.DisplayObject","Emulator.RobotStepReceiveLogInfo","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1489330622, "Emulator.RobotStepCmdLinkInfo", {
name = "Emulator.RobotStepCmdLinkInfo", ns_name = "Emulator", rl_name = "RobotStepCmdLinkInfo", hash_code = 1489330622,
name_list = {"item","cmd","_delete_button","_dst_field_input","_src_id_input","_src_field_input"},
type_list = {"ALittle.DisplayObject","Emulator.RobotStepCmdInfo","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"},
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
name_list = {"info","dialog","_left_step_image","_right_step_image","_unique_id_input","_line_tri","pre_link","next_link"},
type_list = {"Emulator.RobotStepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Map<int,Emulator.RobotStepLinkInfo>","Emulator.RobotStepLinkInfo"},
option_map = {}
})
ALittle.RegStruct(1122498850, "Emulator.RobotStepLogLinkInfo", {
name = "Emulator.RobotStepLogLinkInfo", ns_name = "Emulator", rl_name = "RobotStepLogLinkInfo", hash_code = 1122498850,
name_list = {"info","dialog","_left_step_image","_right_step_image","_unique_id_input","_line_tri","pre_link","next_link","_log_input"},
type_list = {"Emulator.RobotStepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Map<int,Emulator.RobotStepLinkInfo>","Emulator.RobotStepLinkInfo","ALittle.DisplayObject"},
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
name_list = {"max_id","step_map","start_step"},
type_list = {"int","Map<int,Emulator.RobotStepInfo>","Emulator.RobotStepInfo"},
option_map = {}
})
ALittle.RegStruct(465286149, "Emulator.RobotStepCmdInfo", {
name = "Emulator.RobotStepCmdInfo", ns_name = "Emulator", rl_name = "RobotStepCmdInfo", hash_code = 465286149,
name_list = {"dst_field","src_id","src_field"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-312899494, "Emulator.RobotStepReceiveMessageLinkInfo", {
name = "Emulator.RobotStepReceiveMessageLinkInfo", ns_name = "Emulator", rl_name = "RobotStepReceiveMessageLinkInfo", hash_code = -312899494,
name_list = {"info","dialog","_left_step_image","_right_step_image","_unique_id_input","_line_tri","pre_link","next_link","_full_name_input","_log_edit"},
type_list = {"Emulator.RobotStepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Map<int,Emulator.RobotStepLinkInfo>","Emulator.RobotStepLinkInfo","ALittle.DisplayObject","Emulator.RobotStepReceiveLogEdit"},
option_map = {}
})
ALittle.RegStruct(210013886, "Emulator.RobotStepInfo", {
name = "Emulator.RobotStepInfo", ns_name = "Emulator", rl_name = "RobotStepInfo", hash_code = 210013886,
name_list = {"x","y","unique_id","id","type","next_id","pre_type","next_type","full_name","message_json","cmd_list","receive_log_list","delay_ms","log"},
type_list = {"double","double","string","int","int","int","int","int","string","string","List<Emulator.RobotStepCmdInfo>","List<Emulator.RobotStepReceiveLogInfo>","int","string"},
option_map = {}
})
ALittle.RegStruct(162621669, "Emulator.RobotStepDelayLinkInfo", {
name = "Emulator.RobotStepDelayLinkInfo", ns_name = "Emulator", rl_name = "RobotStepDelayLinkInfo", hash_code = 162621669,
name_list = {"info","dialog","_left_step_image","_right_step_image","_unique_id_input","_line_tri","pre_link","next_link","_delay_input"},
type_list = {"Emulator.RobotStepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Map<int,Emulator.RobotStepLinkInfo>","Emulator.RobotStepLinkInfo","ALittle.DisplayObject"},
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
name_list = {"info","dialog","_left_step_image","_right_step_image","_unique_id_input","_line_tri","pre_link","next_link","_full_name_input","_message_edit_btn","_cmd_edit","message"},
type_list = {"Emulator.RobotStepInfo","ALittle.Dialog","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.Triangle","Map<int,Emulator.RobotStepLinkInfo>","Emulator.RobotStepLinkInfo","ALittle.DisplayObject","ALittle.DisplayObject","Emulator.RobotStepCmdEdit","lua.protobuf_message"},
option_map = {}
})

Emulator.RobotStepType = {
	RST_RECEIVE_MESSAGE = 1,
	RST_SEND_MESSAGE = 2,
	RST_DELAY = 3,
	RST_START = 4,
	RST_LOG = 5,
}

Emulator.RobotStepLineType = {
	RSLT_LEFT = 1,
	RSLT_RIGHT = 2,
}

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.RobotStepCmdEdit = Lua.Class(ALittle.DisplayLayout, "Emulator.RobotStepCmdEdit")

function Emulator.RobotStepCmdEdit:TCtor()
	self._add_cmd_btn:AddEventListener(___all_struct[-449066808], self, self.HandleAddClick)
end

function Emulator.RobotStepCmdEdit:Init(cmd_list)
	self._cmd_list = cmd_list
	for index, cmd in ___ipairs(cmd_list) do
		self:CreateCmdItem(cmd)
	end
	self:UpdateHeight()
end

function Emulator.RobotStepCmdEdit:HandleDstFieldChanged(event)
	event.target._user_data.dst_field = event.target.text
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepCmdEdit:HandleSrcIdChanged(event)
	event.target._user_data.src_id = event.target.text
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepCmdEdit:HandleSrcFieldChanged(event)
	event.target._user_data.src_field = event.target.text
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepCmdEdit:UpdateHeight()
	local src_y = self._cmd_screen.y
	if self._cmd_screen.child_count == 0 then
		self._cmd_screen.height = 0
	elseif self._cmd_screen.child_count < 5 then
		self._cmd_screen.height = self._cmd_screen.child_count * self._cmd_screen.childs[1].height
	else
		self._cmd_screen.height = 5 * self._cmd_screen.childs[1].height
	end
	self.height = src_y + self._cmd_screen.height
	self:DispatchEvent(___all_struct[-431205740], {})
end

function Emulator.RobotStepCmdEdit:HandleDeleteClick(event)
	local link_info = event.target._user_data
	self._cmd_screen:RemoveChild(link_info.item)
	self:UpdateHeight()
	local index = ALittle.List_IndexOf(self._cmd_list, link_info.cmd)
	if index ~= nil then
		ALittle.List_Remove(self._cmd_list, index)
	end
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepCmdEdit:HandleAddClick(event)
	local cmd = {}
	self:CreateCmdItem(cmd)
	ALittle.List_Push(self._cmd_list, cmd)
	self:UpdateHeight()
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepCmdEdit:CreateCmdItem(cmd)
	if cmd.dst_field == nil then
		cmd.dst_field = ""
	end
	if cmd.src_id == nil then
		cmd.src_id = ""
	end
	if cmd.src_field == nil then
		cmd.src_field = ""
	end
	local link_info = {}
	local item = Emulator.g_Control:CreateControl("robot_step_cmd_item", link_info)
	link_info._delete_button:AddEventListener(___all_struct[-449066808], self, self.HandleDeleteClick)
	link_info._dst_field_input.text = cmd.dst_field
	link_info._dst_field_input:AddEventListener(___all_struct[958494922], self, self.HandleDstFieldChanged)
	link_info._dst_field_input._user_data = cmd
	link_info._src_id_input.text = cmd.src_id
	link_info._src_id_input:AddEventListener(___all_struct[958494922], self, self.HandleSrcIdChanged)
	link_info._src_id_input._user_data = cmd
	link_info._src_field_input.text = cmd.src_field
	link_info._src_field_input:AddEventListener(___all_struct[958494922], self, self.HandleSrcFieldChanged)
	link_info._src_field_input._user_data = cmd
	self._cmd_screen:AddChild(item)
	link_info.item = item
	link_info.cmd = cmd
	link_info._delete_button._user_data = link_info
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.RobotStepReceiveLogEdit = Lua.Class(ALittle.DisplayLayout, "Emulator.RobotStepReceiveLogEdit")

function Emulator.RobotStepReceiveLogEdit:TCtor()
	self._add_cmd_btn:AddEventListener(___all_struct[-449066808], self, self.HandleAddClick)
end

function Emulator.RobotStepReceiveLogEdit:Init(log_list)
	self._log_list = log_list
	for index, log in ___ipairs(log_list) do
		self:CreateLogItem(log)
	end
	self:UpdateHeight()
end

function Emulator.RobotStepReceiveLogEdit:HandleDstFieldChanged(event)
	event.target._user_data.dst_field = event.target.text
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepReceiveLogEdit:UpdateHeight()
	local src_y = self._log_screen.y
	if self._log_screen.child_count == 0 then
		self._log_screen.height = 0
	elseif self._log_screen.child_count < 5 then
		self._log_screen.height = self._log_screen.child_count * self._log_screen.childs[1].height
	else
		self._log_screen.height = 5 * self._log_screen.childs[1].height
	end
	self.height = src_y + self._log_screen.height
	self:DispatchEvent(___all_struct[-431205740], {})
end

function Emulator.RobotStepReceiveLogEdit:HandleDeleteClick(event)
	local link_info = event.target._user_data
	self._log_screen:RemoveChild(link_info.item)
	self:UpdateHeight()
	local index = ALittle.List_IndexOf(self._log_list, link_info.log)
	if index ~= nil then
		ALittle.List_Remove(self._log_list, index)
	end
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepReceiveLogEdit:HandleAddClick(event)
	local log = {}
	self:CreateLogItem(log)
	ALittle.List_Push(self._log_list, log)
	self:UpdateHeight()
	g_GCenter._grobot._gblueprint:Save(false)
end

function Emulator.RobotStepReceiveLogEdit:CreateLogItem(log)
	if log.dst_field == nil then
		log.dst_field = ""
	end
	local link_info = {}
	local item = Emulator.g_Control:CreateControl("robot_step_receive_log_item", link_info)
	link_info._delete_button:AddEventListener(___all_struct[-449066808], self, self.HandleDeleteClick)
	link_info._dst_field_input.text = log.dst_field
	link_info._dst_field_input:AddEventListener(___all_struct[958494922], self, self.HandleDstFieldChanged)
	link_info._dst_field_input._user_data = log
	self._log_screen:AddChild(item)
	link_info.item = item
	link_info.log = log
	link_info._delete_button._user_data = link_info
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.GBlueprint = Lua.Class(ALittle.DisplayLayout, "Emulator.GBlueprint")

function Emulator.GBlueprint:Setup()
	self._message_edit_dialog = Emulator.g_Control:CreateControl("robot_step_message_edit_dialog", self)
	A_LayerManager:AddToModal(self._message_edit_dialog)
	self._message_edit_dialog.close_callback = Lua.Bind(self.HandleMessageEditDialogClose, self)
	self._robot_step_send_node:AddEventListener(___all_struct[1301789264], self, self.HandleNodeDragBegin)
	self._robot_step_send_node:AddEventListener(___all_struct[1337289812], self, self.HandleNodeDrag)
	self._robot_step_send_node:AddEventListener(___all_struct[150587926], self, self.HandleNodeDragEnd)
	self._robot_step_receive_node:AddEventListener(___all_struct[1301789264], self, self.HandleNodeDragBegin)
	self._robot_step_receive_node:AddEventListener(___all_struct[1337289812], self, self.HandleNodeDrag)
	self._robot_step_receive_node:AddEventListener(___all_struct[150587926], self, self.HandleNodeDragEnd)
	self._robot_step_delay_node:AddEventListener(___all_struct[1301789264], self, self.HandleNodeDragBegin)
	self._robot_step_delay_node:AddEventListener(___all_struct[1337289812], self, self.HandleNodeDrag)
	self._robot_step_delay_node:AddEventListener(___all_struct[150587926], self, self.HandleNodeDragEnd)
	self._robot_step_log_node:AddEventListener(___all_struct[1301789264], self, self.HandleNodeDragBegin)
	self._robot_step_log_node:AddEventListener(___all_struct[1337289812], self, self.HandleNodeDrag)
	self._robot_step_log_node:AddEventListener(___all_struct[150587926], self, self.HandleNodeDragEnd)
	self.visible = false
	self._detail_dialog_layer = ALittle.DisplayGroup(Emulator.g_Control)
	self._detail_line_layer = ALittle.DisplayGroup(Emulator.g_Control)
	self._detail_scroll_screen:AddChild(self._detail_dialog_layer)
	self._detail_scroll_screen:AddChild(self._detail_line_layer)
end

function Emulator.GBlueprint.__getter:step_file()
	return self._step_file
end

function Emulator.GBlueprint:Clear()
	self._file_path = nil
	self._save = true
	self._file_title.text = ""
	self._step_file = nil
	self._link_map = {}
	self._cur_line = nil
	self._detail_dialog_layer:RemoveAllChild()
	self._detail_line_layer:RemoveAllChild()
end

function Emulator.GBlueprint:CreateRobotManager(player_id, socket, trace)
	return Emulator.RobotStepManager(player_id, socket, self._step_file, trace)
end

function Emulator.GBlueprint:HandleNodeDragBegin(event)
	self._cur_node_ui = nil
	A_LayerManager:RemoveFromTip(self._cur_drag_image)
	self._cur_drag_image = nil
	if event.target == self._robot_step_send_node then
		self._cur_node_ui = "robot_step_send_message"
		self._cur_drag_type = Emulator.RobotStepType.RST_SEND_MESSAGE
	elseif event.target == self._robot_step_receive_node then
		self._cur_node_ui = "robot_step_receive_message"
		self._cur_drag_type = Emulator.RobotStepType.RST_RECEIVE_MESSAGE
	elseif event.target == self._robot_step_delay_node then
		self._cur_node_ui = "robot_step_delay"
		self._cur_drag_type = Emulator.RobotStepType.RST_DELAY
	elseif event.target == self._robot_step_log_node then
		self._cur_node_ui = "robot_step_log"
		self._cur_drag_type = Emulator.RobotStepType.RST_LOG
	end
	if self._cur_node_ui == nil then
		return
	end
	local dialog = Emulator.g_Control:CreateControl(self._cur_node_ui)
	local effect = ALittle.EffectImage(Emulator.g_Control)
	effect:Action(dialog)
	self._cur_drag_image = effect
	A_LayerManager:AddToTip(self._cur_drag_image)
	self._cur_drag_image.x = A_UISystem.mouse_x
	self._cur_drag_image.y = A_UISystem.mouse_y
	self._cur_drag_image.alpha = 0.5
end

function Emulator.GBlueprint:HandleNodeDrag(event)
	if self._cur_drag_image == nil then
		return
	end
	self._cur_drag_image.x = A_UISystem.mouse_x - self._cur_drag_image.width / 2
	self._cur_drag_image.y = A_UISystem.mouse_y - self._cur_drag_image.height / 2
end

function Emulator.GBlueprint:HandleNodeDragEnd(event)
	if self._cur_node_ui == nil then
		return
	end
	local x, y = self._detail_scroll_screen.container:LocalToGlobal()
	x = A_UISystem.mouse_x - x - self._cur_drag_image.width / 2
	y = A_UISystem.mouse_y - y - self._cur_drag_image.height / 2
	if x < 0 then
		x = 0
	end
	if y < 0 then
		y = 0
	end
	if self._cur_drag_type == Emulator.RobotStepType.RST_RECEIVE_MESSAGE then
		self:HandleCreateRobotStepReceiveMessage(x, y)
	elseif self._cur_drag_type == Emulator.RobotStepType.RST_SEND_MESSAGE then
		self:HandleCreateRobotStepSendMessage(x, y)
	elseif self._cur_drag_type == Emulator.RobotStepType.RST_DELAY then
		self:HandleCreateRobotStepDelay(x, y)
	elseif self._cur_drag_type == Emulator.RobotStepType.RST_LOG then
		self:HandleCreateRobotStepLog(x, y)
	end
	self._cur_node_ui = nil
	self._cur_drag_type = nil
	A_LayerManager:RemoveFromTip(self._cur_drag_image)
	self._cur_drag_image = nil
end

function Emulator.GBlueprint:Save(value)
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

function Emulator.GBlueprint:HandleCreateRobotStepLog(x, y)
	local info = {}
	self._step_file.max_id = self._step_file.max_id + (1)
	info.id = self._step_file.max_id
	self._step_file.step_map[info.id] = info
	info.x = x
	info.y = y
	info.type = Emulator.RobotStepType.RST_LOG
	self:CreateRobotStepDialog(info)
	self:Save(false)
end

function Emulator.GBlueprint:HandleCreateRobotStepSendMessage(x, y)
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

function Emulator.GBlueprint:HandleRobotStepSendMessageChanged(event)
	local link_info = event.target._user_data
	link_info.info.full_name = link_info._full_name_input.text
	link_info.message = A_LuaProtobufSchedule:CreateMessage(link_info.info.full_name)
	link_info._message_edit_btn.disabled = link_info.message == nil
	if link_info.message == nil then
		link_info.dialog.title = "发送消息:协议不存在!"
	else
		link_info.dialog.title = "发送消息:" .. link_info.info.full_name
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleRobotStepSendMessageEditClick(event)
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

function Emulator.GBlueprint:HandleRobotStepCmdEditResize(event)
	local link_info = event.target._user_data
	link_info.dialog.height = link_info._cmd_edit.y + link_info._cmd_edit.height + 5 + link_info.dialog.head_size
end

function Emulator.GBlueprint:HandleRobotStepReceiveLogEditResize(event)
	local link_info = event.target._user_data
	link_info.dialog.height = link_info._log_edit.y + link_info._log_edit.height + 5 + link_info.dialog.head_size
end

function Emulator.GBlueprint:HandleCreateRobotStepReceiveMessage(x, y)
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

function Emulator.GBlueprint:HandleRobotStepReceiveMessageChanged(event)
	local link_info = event.target._user_data
	link_info.info.full_name = link_info._full_name_input.text
	if A_LuaProtobufSchedule:GetMessageInfo(link_info.info.full_name) == nil then
		link_info.dialog.title = "等待消息:协议不存在!"
	else
		link_info.dialog.title = "等待消息:" .. link_info.info.full_name
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleCreateRobotStepDelay(x, y)
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

function Emulator.GBlueprint:HandleRobotStepDelayChanged(event)
	local link_info = event.target._user_data
	link_info.info.delay_ms = ALittle.Math_ToInt(link_info._delay_input.text)
	if link_info.info.delay_ms == nil or link_info.info.delay_ms < 0 then
		link_info.info.delay_ms = 0
		link_info._delay_input.text = "0"
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleRobotStepLogChanged(event)
	local link_info = event.target._user_data
	link_info.info.log = link_info._log_input.text
	if link_info.info.log == "" then
		link_info.info.log = nil
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleRobotStepUniqueIdChanged(event)
	local link_info = event.target._user_data
	link_info.info.unique_id = link_info._unique_id_input.text
	if link_info.info.unique_id == "" then
		link_info.info.unique_id = nil
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleRobotStepQuadRButtonDown(event)
	if self._file_path == nil then
		return
	end
	local x = event.rel_x - self._detail_scroll_screen.container_x
	local y = event.rel_y - self._detail_scroll_screen.container_y
	if x < 0 then
		x = 0
	end
	if y < 0 then
		y = 0
	end
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("新建:发送消息", Lua.Bind(self.HandleCreateRobotStepSendMessage, self, x, y))
	menu:AddItem("新建:等待消息", Lua.Bind(self.HandleCreateRobotStepReceiveMessage, self, x, y))
	menu:AddItem("新建:延时", Lua.Bind(self.HandleCreateRobotStepDelay, self, x, y))
	menu:AddItem("新建:日志", Lua.Bind(self.HandleCreateRobotStepLog, self, x, y))
	menu:Show()
end

function Emulator.GBlueprint:HandleRobotStepLineDragBegin(event)
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
		link_info.info.next_id = nil
		link_info.info.pre_type = nil
		link_info.info.next_type = nil
		if link_info.next_link.pre_link ~= nil then
			link_info.next_link.pre_link[link_info.info.id] = nil
		end
		link_info.next_link = nil
		self._detail_line_layer:RemoveChild(link_info._line_tri)
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
	self:SetLinePosition(tri, pre_x + pre_image.width / 2, pre_y + pre_image.height / 2, cur_x, cur_y, pre_image.width / 2)
	self._detail_line_layer:AddChild(tri)
	self._cur_line = tri
end

function Emulator.GBlueprint:SetLinePosition(tri, pre_x, pre_y, next_x, next_y, r)
	local vx3 = next_x - pre_x
	local vy3 = next_y - pre_y
	local vx = 0.0
	local vy = 0.0
	if vx3 == 0 then
		vx = 1
		vy = 0
	elseif vy3 == 0 then
		vx = 0
		vy = 1
	else
		vx = 1
		vy = -vx3 / vy3
	end
	local vr = ALittle.Math_Sqrt(vx * vx + vy * vy)
	if vr == 0 then
		vx = 0
		vy = 0
	else
		vx = vx / vr
		vy = vy / vr
	end
	tri.x1 = vx * r + pre_x
	tri.y1 = vy * r + pre_y
	tri.x2 = -vx * r + pre_x
	tri.y2 = -vy * r + pre_y
	tri.x3 = next_x
	tri.y3 = next_y
end

function Emulator.GBlueprint:HandleRobotStepLineDrag(event)
	if self._cur_line == nil then
		return
	end
	local link_info = event.target._user_data
	local pre_image = event.target
	local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
	local cur_x = pre_x + event.rel_x
	local cur_y = pre_y + event.rel_y
	self:SetLinePosition(self._cur_line, pre_x + pre_image.width / 2, pre_y + pre_image.height / 2, cur_x, cur_y, pre_image.width / 2)
end

function Emulator.GBlueprint:HandleRobotStepLineDragEnd(event)
	if self._cur_line == nil then
		return
	end
	local tri = self._cur_line
	self._detail_line_layer:RemoveChild(tri)
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
	if next_link.pre_link ~= nil and next_link.pre_link[link_info.info.id] ~= nil then
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

function Emulator.GBlueprint:UpdateRobotStepDialogPosition(link_info, x, y)
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
		local next_image
		if link_info.next_link ~= nil then
			if link_info.info.next_type == Emulator.RobotStepLineType.RSLT_LEFT then
				next_image = link_info.next_link._left_step_image
			elseif link_info.info.next_type == Emulator.RobotStepLineType.RSLT_RIGHT then
				next_image = link_info.next_link._right_step_image
			end
		end
		if pre_image ~= nil and next_image ~= nil then
			local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
			local next_x, next_y = next_image:LocalToGlobal(self._detail_scroll_screen.container)
			local r = pre_image.width / 2
			self:SetLinePosition(tri, pre_x + r, pre_y + r, next_x + r, next_y + r, r)
		end
	end
	if link_info.pre_link ~= nil then
		for id, pre_link in ___pairs(link_info.pre_link) do
			local tri = pre_link._line_tri
			local pre_image
			if pre_link.info.pre_type == Emulator.RobotStepLineType.RSLT_LEFT then
				pre_image = pre_link._left_step_image
			elseif pre_link.info.pre_type == Emulator.RobotStepLineType.RSLT_RIGHT then
				pre_image = pre_link._right_step_image
			end
			local next_image
			if pre_link.info.next_type == Emulator.RobotStepLineType.RSLT_LEFT then
				next_image = link_info._left_step_image
			elseif pre_link.info.next_type == Emulator.RobotStepLineType.RSLT_RIGHT then
				next_image = link_info._right_step_image
			end
			if pre_image ~= nil and next_image ~= nil then
				local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
				local next_x, next_y = next_image:LocalToGlobal(self._detail_scroll_screen.container)
				local r = pre_image.width / 2
				self:SetLinePosition(tri, pre_x + r, pre_y + r, next_x + r, next_y + r, r)
			end
		end
	end
	self:Save(false)
end

function Emulator.GBlueprint:HandleRobotStepDragBegin(event)
	local link_info = event.target._user_data
	link_info.dialog:MoveToTop()
end

function Emulator.GBlueprint:HandleRobotStepDrag(event)
	local link_info = event.target._user_data
	self:UpdateRobotStepDialogPosition(link_info, event.target.x, event.target.y)
end

function Emulator.GBlueprint:HandleRobotStepDragEnd(event)
	local link_info = event.target._user_data
	if event.target.x < 0 then
		event.target.x = 0
	end
	if event.target.y < 0 then
		event.target.y = 0
	end
	self:UpdateRobotStepDialogPosition(link_info, event.target.x, event.target.y)
	self._detail_scroll_screen:AdjustScrollBar()
end

function Emulator.GBlueprint:HandleRobotStepDelete(dialog)
	self:AskRobotStepDelete(dialog)
	return false
end

function Emulator.GBlueprint:AskRobotStepDelete(dialog)
	local result = g_AUITool:DeleteNotice("删除", "确定删除当前步骤吗?")
	if result ~= "YES" then
		return
	end
	local link_info = dialog._user_data
	if link_info.info.type == Emulator.RobotStepType.RST_START then
		g_AUITool:ShowNotice("提示", "开始节点不能删除")
		return
	end
	self._detail_dialog_layer:RemoveChild(dialog)
	if link_info._line_tri ~= nil then
		self._detail_line_layer:RemoveChild(link_info._line_tri)
		link_info._line_tri = nil
		link_info.next_link.pre_link[link_info.info.id] = nil
		link_info.next_link = nil
	end
	if link_info.pre_link ~= nil then
		for id, pre_link in ___pairs(link_info.pre_link) do
			pre_link.next_link = nil
			pre_link.info.next_id = nil
			pre_link.info.next_type = nil
			pre_link.info.pre_type = nil
			self._detail_line_layer:RemoveChild(pre_link._line_tri)
		end
		link_info.pre_link = nil
	end
	self._step_file.step_map[link_info.info.id] = nil
	self._link_map[link_info.info.id] = nil
	self:Save(false)
end
Emulator.GBlueprint.AskRobotStepDelete = Lua.CoWrap(Emulator.GBlueprint.AskRobotStepDelete)

function Emulator.GBlueprint:HandleMessageEditDialogClose()
	local link_info = self._message_edit_dialog._user_data
	if link_info.message ~= nil then
		link_info.info.message_json = protobuf.message_jsonencode(link_info.message, true, false)
	end
	return true
end

function Emulator.GBlueprint:HandleFileTreeDeleteDir(event)
	if self._file_path == nil then
		return
	end
	if ALittle.File_GetFileAttr(self._file_path) ~= nil then
		return
	end
	self:Clear()
	self.visible = false
end

function Emulator.GBlueprint:HandleFileTreeDeleteFile(event)
	if event.path ~= self._file_path then
		return
	end
	self:Save(true)
	self:Clear()
	self.visible = false
end

function Emulator.GBlueprint:HandleFileTreeSelectFile(event)
	if event.path == self._file_path then
		return
	end
	self.visible = true
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
	if self._step_file.start_step == nil then
		self._step_file.start_step = {}
		self._step_file.start_step.type = Emulator.RobotStepType.RST_START
		self._step_file.max_id = self._step_file.max_id + (1)
		self._step_file.start_step.x = 0
		self._step_file.start_step.y = 0
		self._step_file.start_step.id = self._step_file.max_id
	end
	self._link_map = {}
	self._cur_line = nil
	self._detail_dialog_layer:RemoveAllChild()
	self._detail_line_layer:RemoveAllChild()
	self:CreateRobotStepDialog(self._step_file.start_step)
	for id, info in ___pairs(self._step_file.step_map) do
		self:CreateRobotStepDialog(info)
	end
	self:CreateRobotStepLine(self._step_file.start_step)
	for id, info in ___pairs(self._step_file.step_map) do
		self:CreateRobotStepLine(info)
	end
	self._detail_scroll_screen:AdjustScrollBar()
end

function Emulator.GBlueprint:CreateRobotStepDialog(info)
	if info.type == Emulator.RobotStepType.RST_START then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_start", link_info, info)
	elseif info.type == Emulator.RobotStepType.RST_RECEIVE_MESSAGE then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_receive_message", link_info, info)
		if A_LuaProtobufSchedule:GetMessageInfo(info.full_name) == nil then
			dialog.title = "等待消息:协议不存在!"
		else
			dialog.title = "等待消息:" .. info.full_name
		end
		link_info._full_name_input.text = info.full_name
		link_info._full_name_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepReceiveMessageChanged)
		link_info._full_name_input._user_data = link_info
		link_info._log_edit:AddEventListener(___all_struct[-431205740], self, self.HandleRobotStepReceiveLogEditResize)
		link_info._log_edit._user_data = link_info
		link_info._log_edit:Init(info.receive_log_list)
	elseif info.type == Emulator.RobotStepType.RST_SEND_MESSAGE then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_send_message", link_info, info)
		link_info._full_name_input.text = info.full_name
		link_info.message = A_LuaProtobufSchedule:CreateMessageByJson(info.full_name, info.message_json)
		if link_info.message == nil then
			dialog.title = "发送消息:协议不存在!"
		else
			dialog.title = "发送消息:" .. info.full_name
		end
		link_info._message_edit_btn.disabled = link_info.message == nil
		link_info._full_name_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepSendMessageChanged)
		link_info._full_name_input._user_data = link_info
		link_info._message_edit_btn:AddEventListener(___all_struct[-449066808], self, self.HandleRobotStepSendMessageEditClick)
		link_info._message_edit_btn._user_data = link_info
		link_info._cmd_edit:AddEventListener(___all_struct[-431205740], self, self.HandleRobotStepCmdEditResize)
		link_info._cmd_edit._user_data = link_info
		link_info._cmd_edit:Init(info.cmd_list)
	elseif info.type == Emulator.RobotStepType.RST_DELAY then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_delay", link_info, info)
		link_info._delay_input.text = info.delay_ms
		link_info._delay_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepDelayChanged)
		link_info._delay_input._user_data = link_info
	elseif info.type == Emulator.RobotStepType.RST_LOG then
		local link_info = {}
		local dialog = self:CreateCommonDialog("robot_step_log", link_info, info)
		link_info._log_input.text = info.log
		link_info._log_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepLogChanged)
		link_info._log_input._user_data = link_info
	end
end

function Emulator.GBlueprint:CreateRobotStepLine(info)
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
	if next_link.pre_link ~= nil and next_link.pre_link[link_info.info.id] ~= nil then
		return
	end
	local tri = Emulator.g_Control:CreateControl("robot_step_triangle")
	tri.disabled = true
	tri._user_data = next_link
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
	if next_link.pre_link == nil then
		next_link.pre_link = {}
	end
	next_link.pre_link[link_info.info.id] = link_info
	local pre_x, pre_y = pre_image:LocalToGlobal(self._detail_scroll_screen.container)
	local next_x, next_y = next_image:LocalToGlobal(self._detail_scroll_screen.container)
	local r = pre_image.width / 2
	self:SetLinePosition(tri, pre_x + r, pre_y + r, next_x + r, next_y + r, r)
	self._detail_line_layer:AddChild(tri)
end

function Emulator.GBlueprint:CreateCommonDialog(ui, link_info, info)
	if info.cmd_list == nil then
		info.cmd_list = {}
	end
	if info.receive_log_list == nil then
		info.receive_log_list = {}
	end
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
	if link_info._unique_id_input ~= nil then
		link_info._unique_id_input:AddEventListener(___all_struct[958494922], self, self.HandleRobotStepUniqueIdChanged)
		link_info._unique_id_input._user_data = link_info
		if info.unique_id ~= nil then
			link_info._unique_id_input.text = info.unique_id
		end
	end
	dialog.x = link_info.info.x
	dialog.y = link_info.info.y
	dialog:AddEventListener(___all_struct[1971745271], self, self.HandleRobotStepDragBegin)
	dialog:AddEventListener(___all_struct[1517533145], self, self.HandleRobotStepDrag)
	dialog:AddEventListener(___all_struct[-1482649531], self, self.HandleRobotStepDragEnd)
	dialog.close_callback = Lua.Bind(self.HandleRobotStepDelete, self, dialog)
	self._detail_dialog_layer:AddChild(dialog)
	self._link_map[info.id] = link_info
	return dialog
end

function Emulator.GBlueprint:HandleSettingChanged()
	self._link_map = {}
	self._file_title.text = ""
	self._file_path = nil
	self._step_file = nil
	self._save = true
	self._detail_dialog_layer:RemoveAllChild()
	self._detail_line_layer:RemoveAllChild()
end

end