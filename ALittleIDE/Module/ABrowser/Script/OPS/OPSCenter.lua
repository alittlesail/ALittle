
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

g_OPSRequire = nil
OPSCenter = ALittle.Class(nil, "ABrowser.OPSCenter")

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

function OPSCenter:Start(layer, control, config_user, base_path, login_ip, login_port, module_name)
	OPSCenter.RequireScript()
	self._module_base_path = base_path
	self._module_base_pathex = ALittle.File_BaseFilePath() .. base_path
	self:ReloadConfig()
	self._config_user = config_user
	self._control = control
	self._layer = layer
	self._main_layer = ALittle.DisplayLayout(g_Control)
	self._main_layer.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._main_layer.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	layer:AddChild(self._main_layer)
	self._dialog_layer = ALittle.DisplayLayout(g_Control)
	self._dialog_layer.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._dialog_layer.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	layer:AddChild(self._dialog_layer)
	self._modal_layer = ALittle.DisplayLayout(g_Control)
	self._modal_layer.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._modal_layer.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
	layer:AddChild(self._modal_layer)
	self._tip_layer = ALittle.DisplayLayout(g_Control)
	self._tip_layer.width_type = ALittle.UIEnumTypes.SIZE_MARGIN
	self._tip_layer.height_type = ALittle.UIEnumTypes.SIZE_MARGIN
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

function OPSCenter.RequireScript()
	if g_OPSRequire == true then
		return
	end
	g_OPSRequire = true
	g_Script:Require("Script/OPS/OPSLogin")
	g_Script:Require("Script/OPS/OPSMain")
	g_Script:Require("Script/OPS/Tool/OPSWeakNotice")
	g_Script:Require("Script/OPS/Tool/OPSCenterWeakNotice")
	g_Script:Require("Script/OPS/Tool/OPSWeakNotice")
	g_Script:Require("Script/OPS/Tool/OPSTool")
	g_Script:Require("Script/OPS/Tool/OPSTree")
	g_Script:Require("Script/OPS/Tool/OPSLoading")
	g_Script:Require("Script/OPS/Tool/OPSDate")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPBase")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPDropDownSelect")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPSelectInput")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPStringEdit")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPStringInput")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPNumberInput")
	g_Script:Require("Script/OPS/Dialog/Control/OPSCOMPTimeSelect")
	g_Script:Require("Script/OPS/Dialog/OPSBaseDialog")
	g_Script:Require("Script/OPS/Dialog/OPSChoiceDialog")
	g_Script:Require("Script/OPS/Dialog/OPSCustomDialog")
	g_Script:Require("Script/OPS/Dialog/OPSRoleDialog")
	g_Script:Require("Script/OPS/Dialog/OPSRequestDialog")
	g_Script:Require("Script/OPS/Dialog/OPSDeleteDialog")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDBase")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDDropDownSelect")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDStringInput")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDNumberInput")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDStringOutput")
	g_Script:Require("Script/OPS/TableData/Control/OPSTDTimeSelect")
	g_Script:Require("Script/OPS/TableData/OPSTableDataMenu")
	g_Script:Require("Script/OPS/TableData/OPSTableDataRichGroup")
	g_Script:Require("Script/OPS/TableData/OPSTableDataOrderButton")
	g_Script:Require("Script/OPS/TableData/OPSTableData")
	g_Script:Require("Script/OPS/TableData/OPSTableDataHead")
	g_Script:Require("Script/OPS/TableData/OPSTableDataSearch")
	g_Script:Require("Script/OPS/TableData/OPSTableDataTail")
	g_Script:Require("Script/OPS/TableData/OPSTableDataQuery")
	g_Script:Require("Script/OPS/TableData/OPSTableDataSetData")
end

