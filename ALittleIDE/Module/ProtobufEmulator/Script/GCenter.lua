-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ProtobufEmulator.g_GConfig = nil
ProtobufEmulator.GCenter = Lua.Class(nil, "ProtobufEmulator.GCenter")

function ProtobufEmulator.GCenter:Setup()
	ProtobufEmulator.g_GConfig = ALittle.CreateConfigSystem(ProtobufEmulator.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(ProtobufEmulator.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	ProtobufEmulator.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(ProtobufEmulator.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	ProtobufEmulator.g_LayerGroup:AddChild(self._dialog_layer, nil)
	ProtobufEmulator.g_Control:CreateControl("main_scene", self, self._main_layer)
	self._main_tab:DisableAllCloseButton()
	self._main_tab.tab_index = 1
	self._setting_dialog = ProtobufEmulator.g_Control:CreateControl("main_setting_dialog", self)
	A_LayerManager:AddToModal(self._setting_dialog)
	local plugin_path = ProtobufEmulator.g_GConfig:GetString("plugin_script", "")
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
	local proto_root = ProtobufEmulator.g_GConfig:GetString("proto_root", "")
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
		else
			self:HandleShowSettingDialog(nil)
		end
	end
	self._gclient:Setup()
	self._grobot:Setup()
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	self._frame_loop:Start()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleKeyDown, self)
end

function ProtobufEmulator.GCenter:UpdateFrame(frame_time)
	A_LuaProtobufSchedule:RunInFrame()
end

function ProtobufEmulator.GCenter:HandleKeyDown(mod, sym, scancode)
	if sym == 115 and mod & 0x00c0 ~= 0 then
		self._grobot:Save(true)
	end
end

function ProtobufEmulator.GCenter:HandleShowSettingDialog(event)
	self._setting_dialog.visible = true
	self._proto_root_input.text = ProtobufEmulator.g_GConfig:GetString("proto_root", "")
	self._login_proto_input.text = ProtobufEmulator.g_GConfig:GetString("login_proto", "")
	self._plugin_file_input.text = ProtobufEmulator.g_GConfig:GetString("plugin_script", "")
	self._blueprint_root_input.text = ProtobufEmulator.g_GConfig:GetString("blueprint_root", "")
end

function ProtobufEmulator.GCenter:HandleShowVersionDialog(event)
	ProtobufEmulator.g_VersionManager:ShowDialog()
end

function ProtobufEmulator.GCenter:HandleSettingSelectProtoRootClick(event)
	if event.path == nil then
		return
	end
	self._proto_root_input.text = event.path
end

function ProtobufEmulator.GCenter:HandleSettingSelectBlueprintRootClick(event)
	if event.path == nil then
		return
	end
	self._blueprint_root_input.text = event.path
end

function ProtobufEmulator.GCenter:HandleSettingSelectPluginScriptClick(event)
	if event.path == nil then
		return
	end
	self._plugin_file_input.text = event.path
end

function ProtobufEmulator.GCenter:HandleSettingGeneratePluginScriptClick(event)
	if event.path == nil then
		return
	end
	self._plugin_file_input.text = event.path .. "\\TemplatePlugin.lua"
	ProtobufEmulator.g_GConfig:SetConfig("plugin_script", self._plugin_file_input.text)
	ALittle.File_CopyFile(ProtobufEmulator.g_ModuleBasePath .. "Other/TemplatePlugin.lua", self._plugin_file_input.text)
end

function ProtobufEmulator.GCenter:HandleSettingConfirmClick(event)
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
		_G["__PLUGIN_RobotLogin"] = nil
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
	ProtobufEmulator.g_GConfig:SetConfig("proto_root", self._proto_root_input.text)
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
	ProtobufEmulator.g_GConfig:SetConfig("login_proto", self._login_proto_input.text)
	ProtobufEmulator.g_GConfig:SetConfig("plugin_script", self._plugin_file_input.text)
	ProtobufEmulator.g_GConfig:SetConfig("blueprint_root", self._blueprint_root_input.text)
	self._gclient:HandleSettingChanged()
	self._grobot:HandleSettingChanged()
end

function ProtobufEmulator.GCenter:HandleSettingCancelClick(event)
	self._setting_dialog.visible = false
end

function ProtobufEmulator.GCenter:Shutdown()
	self._frame_loop:Stop()
end

_G.g_GCenter = ProtobufEmulator.GCenter()
end