-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


g_GConfig = nil
GCenter = Lua.Class(nil, "Emulator.GCenter")

function GCenter:Ctor()
	___rawset(self, "_proto_search_item_pool", {})
	___rawset(self, "_proto_search_group", {})
end

function GCenter:Setup()
	g_GConfig = ALittle.CreateConfigSystem(g_ModuleBasePath .. "/User.cfg")
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
		end
		item.group = self._proto_search_group
		self._protobuf_scroll_screen:AddChild(item)
	end
	self._protobuf_scroll_screen:RejustScrollBar()
end

function GCenter:Shutdown()
	self._frame_loop:Stop()
end

g_GCenter = GCenter()
