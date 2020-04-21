
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


g_OPSRequire = nil
OPSCenter = Lua.Class(nil, "ABrowser.OPSCenter")

function OPSCenter.RequireScript()
local ___COROUTINE = coroutine.running()
	if g_OPSRequire == true then
		return
	end
	g_OPSRequire = true
	Require(g_ScriptBasePath .. "OPS/OPSLogin")
	Require(g_ScriptBasePath .. "OPS/OPSMain")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSWeakNotice")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSCenterWeakNotice")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSWeakNotice")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSTool")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSTree")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSLoading")
	Require(g_ScriptBasePath .. "OPS/Tool/OPSDate")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPBase")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPDropDownSelect")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPSelectInput")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPStringEdit")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPStringInput")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPNumberInput")
	Require(g_ScriptBasePath .. "OPS/Dialog/Control/OPSCOMPTimeSelect")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSBaseDialog")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSChoiceDialog")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSCustomDialog")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSRoleDialog")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSRequestDialog")
	Require(g_ScriptBasePath .. "OPS/Dialog/OPSDeleteDialog")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDBase")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDDropDownSelect")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDStringInput")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDNumberInput")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDStringOutput")
	Require(g_ScriptBasePath .. "OPS/TableData/Control/OPSTDTimeSelect")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataMenu")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataRichGroup")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataOrderButton")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableData")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataHead")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataSearch")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataTail")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataQuery")
	Require(g_ScriptBasePath .. "OPS/TableData/OPSTableDataSetData")
end

function OPSCenter:Start(layer, control, config_user, base_path, login_ip, login_port, module_name)
local ___COROUTINE = coroutine.running()
	OPSCenter.RequireScript()
	self._module_base_path = base_path
	self._module_base_pathex = ALittle.File_BaseFilePath() .. base_path
	self:ReloadConfig()
	self._config_user = config_user
	self._control = control
	self._layer = layer
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	layer:AddChild(self._main_layer)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	layer:AddChild(self._dialog_layer)
	self._modal_layer = ALittle.DisplayLayout(g_Control)
	self._modal_layer.width_type = 4
	self._modal_layer.height_type = 4
	layer:AddChild(self._modal_layer)
	self._tip_layer = ALittle.DisplayLayout(g_Control)
	self._tip_layer.width_type = 4
	self._tip_layer.height_type = 4
	self._tip_layer.disabled = true
	layer:AddChild(self._tip_layer)
	self._dialog_logic = OPSBaseDialogManager(self)
	self._main_logic = OPSMain(self)
	self._tool_logic = OPSTool(self)
	self._login_logic = OPSLogin(self, login_ip, login_port, module_name)
	self._login_logic:ShowScene()
end

function OPSCenter:ReloadConfig()
	self._temp_path = self._module_base_pathex .. "/Temp/"
	if ALittle.File_GetFileAttr(self._temp_path) == nil then
		ALittle.File_MakeDeepDir(self._temp_path)
	end
	local config, error_msg = ALittle.File_ReadJsonFromFile(self.temp_path .. "Client.cfg")
	if config == nil then
		ALittle.Log("客户端配置Json解析失败:" .. self.temp_path .. "Client.cfg, " .. error_msg)
		return
	end
	self._config = config
end

function OPSCenter:Close()
	if self._login_logic ~= nil then
		self._login_logic:Close()
	end
	if self._dialog_logic ~= nil then
		self._dialog_logic:Close()
	end
	self._layer:AddChild(self._main_layer)
	self._layer:AddChild(self._dialog_layer)
	self._layer:AddChild(self._modal_layer)
	self._layer:AddChild(self._tip_layer)
end

function OPSCenter.__getter:main_layer()
	return self._main_layer
end

function OPSCenter.__getter:dialog_layer()
	return self._dialog_layer
end

function OPSCenter.__getter:modal_layer()
	return self._modal_layer
end

function OPSCenter.__getter:tip_layer()
	return self._tip_layer
end

function OPSCenter.__getter:control()
	return self._control
end

function OPSCenter.__getter:config()
	return self._config
end

function OPSCenter.__getter:config_user()
	return self._config_user
end

function OPSCenter.__getter:base_path()
	return self._module_base_path
end

function OPSCenter.__getter:base_pathex()
	return self._module_base_pathex
end

function OPSCenter.__getter:temp_path()
	return self._temp_path
end

function OPSCenter.__getter:tool_logic()
	return self._tool_logic
end

function OPSCenter.__getter:main_logic()
	return self._main_logic
end

function OPSCenter.__getter:login_logic()
	return self._login_logic
end

function OPSCenter.__getter:dialog_logic()
	return self._dialog_logic
end

