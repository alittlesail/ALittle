-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name = "AUIPlugin.AUIFileSelectFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileEvent", hash_code = 2117383637,
name_list = {"target","info"},
type_list = {"ALittle.DisplayObject","AUIPlugin.AUIFileTreeUserInfo"},
option_map = {}
})
ALittle.RegStruct(-1718818319, "AUIPlugin.AUIFileDeleteDirEvent", {
name = "AUIPlugin.AUIFileDeleteDirEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteDirEvent", hash_code = -1718818319,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(-1657066432, "ProtobufEmulator.PlayerInfo", {
name = "ProtobufEmulator.PlayerInfo", ns_name = "ProtobufEmulator", rl_name = "PlayerInfo", hash_code = -1657066432,
name_list = {"client","robot"},
type_list = {"Lua.ISocket","ProtobufEmulator.RobotStepManager"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name = "AUIPlugin.AUIFileTreeUserInfo", ns_name = "AUIPlugin", rl_name = "AUIFileTreeUserInfo", hash_code = -686652419,
name_list = {"path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"},
type_list = {"string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"},
option_map = {}
})
ALittle.RegStruct(-545221029, "AUIPlugin.AUIFileDeleteFileEvent", {
name = "AUIPlugin.AUIFileDeleteFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteFileEvent", hash_code = -545221029,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ProtobufEmulator.GRobot = Lua.Class(ALittle.DisplayLayout, "ProtobufEmulator.GRobot")

function ProtobufEmulator.GRobot:Setup()
	self._socket_map = {}
	self._start_button.visible = true
	self._stop_button.visible = false
	self._login_ip_input.text = ProtobufEmulator.g_GConfig:GetString("login_ip", "127.0.0.1")
	local data_list = ProtobufEmulator.g_GConfig:GetConfig("login_ip_list", {})
	if ALittle.List_Find(data_list, self._login_ip_input.text) == nil then
		ALittle.List_Push(data_list, self._login_ip_input.text)
	end
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
	self._login_port_input.text = ALittle.String_ToString(ProtobufEmulator.g_GConfig:GetInt("login_port", 0))
	self._min_player_id.text = ProtobufEmulator.g_GConfig:GetInt("min_player_id", 1)
	self._max_player_id.text = ProtobufEmulator.g_GConfig:GetInt("max_player_id", 1)
	self._blueprint_filetree:SetRoot(ProtobufEmulator.g_GConfig:GetString("blueprint_root", ""), Lua.Bind(self.HandleFileTreeRightMenu, self))
	self._blueprint_filetree:AddEventListener(___all_struct[2117383637], self._gblueprint, self._gblueprint.HandleFileTreeSelectFile)
	self._blueprint_filetree:AddEventListener(___all_struct[-545221029], self._gblueprint, self._gblueprint.HandleFileTreeDeleteFile)
	self._blueprint_filetree:AddEventListener(___all_struct[-1718818319], self._gblueprint, self._gblueprint.HandleFileTreeDeleteDir)
	self._blueprint_filetree:SetFold(1, true)
	self._gblueprint:Setup()
end

function ProtobufEmulator.GRobot:ClearAllPlayer()
	if self._player_map ~= nil then
		for id, info in ___pairs(self._player_map) do
			if info.client ~= nil then
				info.client:Close()
			end
			if info.robot ~= nil then
				info.robot:Clear()
			end
		end
		self._player_map = nil
	end
	self._cur_create_count = 0
	self._socket_map = {}
end

function ProtobufEmulator.GRobot:AddLog(log)
	local at_bottom = self._log_scroll_screen.container_y <= self._log_scroll_screen.container.height - self._log_scroll_screen.view_height + 5
	local item = nil
	if self._log_scroll_screen.child_count > 500 then
		item = self._log_scroll_screen.childs[1]
		self._log_scroll_screen:RemoveChild(item)
	else
		item = ProtobufEmulator.g_Control:CreateControl("usual_textarea_left_top", nil)
		item.width = self._log_scroll_screen.view_width
	end
	item.text = log
	item.height = item.real_height
	self._log_scroll_screen:AddChild(item)
	if at_bottom then
		self._log_scroll_screen:ScrollToBottom()
	end
end

function ProtobufEmulator.GRobot:HandleIpSelectChanged(event)
	self._login_ip_input.text = self._ip_dropdown.text
	self._ip_dropdown.text = ""
end

function ProtobufEmulator.GRobot:HandleClientSocketDisconnected(player_id, socket)
	local info = self._player_map[player_id]
	if info == nil then
		return
	end
	self._socket_map[info.client] = nil
	self:AddLog("disconnected:" .. player_id)
	info.client = nil
	self._player_map[player_id] = nil
end

function ProtobufEmulator.GRobot:CreatePlayer(ip, port, total_count, id, robot_login, login_func)
	local msg = robot_login(id)
	local call_error, error, client = Lua.TCall(login_func, ip, port, msg)
	if call_error ~= nil then
		error = call_error
	end
	if error ~= nil then
		self:AddLog(id .. ":" .. error)
	else
		local info = {}
		self._player_map[id] = info
		self._socket_map[client] = info
		info.client = client
		info.client.disconnect_callback = Lua.Bind(self.HandleClientSocketDisconnected, self, id)
		info.robot = self._gblueprint:CreateRobotManager(id, info.client, total_count == 1)
		info.robot:Start()
		info.client:ReceiveMessage()
		self:AddLog(id .. ":login succeed")
	end
	self:HandleCreatePlayerEnd(total_count, id)
end
ProtobufEmulator.GRobot.CreatePlayer = Lua.CoWrap(ProtobufEmulator.GRobot.CreatePlayer)

function ProtobufEmulator.GRobot:HandleCreatePlayerEnd(total_count, id)
	self._cur_create_count = self._cur_create_count + (1)
	if self._cur_create_count < total_count then
		return
	end
	self._start_button.disabled = false
	self._start_button.visible = false
	self._stop_button.visible = true
end

function ProtobufEmulator.GRobot:HandleStartClick(event)
	if self._gblueprint.step_file == nil then
		g_AUITool:ShowNotice("提示", "请先选择蓝图")
		return
	end
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
	local loop_list = ALittle.LoopList()
	local id = min_player_id
	while true do
		if not(id <= max_player_id) then break end
		loop_list:AddUpdater(ALittle.LoopTimer(Lua.Bind(self.CreatePlayer, self, ip, port, max_player_id - min_player_id + 1, id, robot_login, login_func), 50))
		id = id+(1)
	end
	loop_list:Start()
	ProtobufEmulator.g_GConfig:SetConfig("min_player_id", min_player_id)
	ProtobufEmulator.g_GConfig:SetConfig("max_player_id", max_player_id)
	ProtobufEmulator.g_GConfig:SetConfig("login_ip", ip)
	ProtobufEmulator.g_GConfig:SetConfig("login_port", port)
	local data_list = ALittle.List_Copy(ProtobufEmulator.g_GConfig:GetConfig("login_ip_list", {}))
	if ALittle.List_Find(data_list, ip) == nil then
		ALittle.List_Push(data_list, ip)
	end
	ProtobufEmulator.g_GConfig:SetConfig("login_ip_list", data_list)
	self._ip_dropdown.data_list = data_list
	self._ip_dropdown.text = ""
end

function ProtobufEmulator.GRobot:HandleStopClick(event)
	self:ClearAllPlayer()
	self._stop_button.visible = false
	self._start_button.visible = true
	self:AddLog("Stoped!")
end

function ProtobufEmulator.GRobot:Save(value)
	self._gblueprint:Save(value)
end

function ProtobufEmulator.GRobot:HandleFileTreeRightMenu(user_info, menu)
end

function ProtobufEmulator.GRobot:HandleMessage(socket, msg)
	local info = self._socket_map[socket]
	if info == nil then
		return
	end
	if info.robot == nil then
		return
	end
	info.robot:ReceiveMessage(msg)
end

function ProtobufEmulator.GRobot:HandleSettingChanged()
	self._blueprint_filetree:SetRoot(ProtobufEmulator.g_GConfig:GetString("blueprint_root", ""), Lua.Bind(self.HandleFileTreeRightMenu, self))
	self._gblueprint:HandleSettingChanged()
	self._log_scroll_screen:RemoveAllChild()
end

end