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

g_GConfig = nil
g_GProtoCache = nil
GCenter = Lua.Class(nil, "Emulator.GCenter")

function GCenter:Ctor()
	___rawset(self, "_proto_search_item_pool", {})
	___rawset(self, "_proto_search_group", {})
	___rawset(self, "_detail_tree_item_pool", {})
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
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	self._frame_loop:Start()
end

function GCenter:UpdateFrame(frame_time)
	A_LuaSocketSchedule:RunInFrame()
end

function GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
	self._proto_root_input.text = g_GConfig:GetString("proto_root", "")
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
	self._detail_scroll_screen:RemoveAllChild()
	for key, info in ___pairs(self._detail_tree_item_pool) do
		protobuf.freemessage(info.message)
	end
	self._detail_tree_item_pool = {}
	self:RefreshProtoList()
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
	self._detail_scroll_screen:RemoveAllChild()
	local detail_info = self._detail_tree_item_pool[info.full_name]
	if detail_info == nil then
		detail_info = Utility_CreateTree(info)
		if detail_info == nil then
			return
		end
		self._detail_tree_item_pool[info.full_name] = detail_info
	end
	self._detail_scroll_screen:AddChild(detail_info.tree)
	self._detail_scroll_screen:RejustScrollBar()
end

function GCenter:Shutdown()
	self._frame_loop:Stop()
	for key, info in ___pairs(self._detail_tree_item_pool) do
		protobuf.freemessage(info.message)
	end
	self._detail_tree_item_pool = {}
end

g_GCenter = GCenter()
