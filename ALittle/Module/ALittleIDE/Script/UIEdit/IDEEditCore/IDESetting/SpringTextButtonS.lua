
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
SpringTextButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.SpringTextButtonS")

function SpringTextButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_springtextbutton")
end

function SpringTextButtonS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_disabled")
	self:LoadShowTypeNoNilData("show_text")
	self:LoadShowTypeNoNilData("show_disabled_text")
	self:LoadBoolData("file_select", false, g_IDEEnum.yn_type)
end

function SpringTextButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
end

function SpringTextButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function SpringTextButtonS:HandleShowUpSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_up", self.HandleShowUpFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function SpringTextButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function SpringTextButtonS:HandleShowDisabledSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_disabled", self.HandleShowDisabledFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function SpringTextButtonS:HandleShowTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function SpringTextButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", true)
end

function SpringTextButtonS:HandleShowDisabledTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function SpringTextButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", true)
end

function SpringTextButtonS:HandleHandFileSelectSELECT_CHANGE(event)
	self:BoolSelectChange("file_select", false, g_IDEEnum.yn_type)
end

