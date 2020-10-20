-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


Emulator.g_GConfig = nil
Emulator.GCenter = Lua.Class(nil, "Emulator.GCenter")

function Emulator.GCenter:Setup()
	Emulator.g_GConfig = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath .. "/User.cfg")
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
		else
			self:HandleShowSettingDialog(nil)
		end
	end
	self._gclient:Setup()
	self._frame_loop = ALittle.LoopFrame(Lua.Bind(self.UpdateFrame, self))
	self._frame_loop:Start()
end

function Emulator.GCenter:UpdateFrame(frame_time)
	A_LuaProtobufSchedule:RunInFrame()
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
	Emulator.g_GConfig:SetConfig("login_proto", self._login_proto_input.text)
	Emulator.g_GConfig:SetConfig("plugin_script", self._plugin_file_input.text)
	self._gclient:HandleSettingChanged()
end

function Emulator.GCenter:HandleSettingCancelClick(event)
	self._setting_dialog.visible = false
end

function Emulator.GCenter:Shutdown()
	self._frame_loop:Stop()
end

_G.g_GCenter = Emulator.GCenter()
end