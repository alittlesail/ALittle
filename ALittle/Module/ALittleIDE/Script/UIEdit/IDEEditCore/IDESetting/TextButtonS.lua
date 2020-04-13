
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
TextButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TextButtonS")

function TextButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textbutton")
end

function TextButtonS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
	self:LoadShowTypeNoNilData("show_text")
	self:LoadShowTypeNoNilData("show_over_text")
	self:LoadShowTypeNoNilData("show_down_text")
	self:LoadShowTypeNoNilData("show_disabled_text")
	self:LoadBoolData("file_select", false, g_IDEEnum.yn_type)
end

function TextButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
end

function TextButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function TextButtonS:HandleShowUpSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_up", self.HandleShowUpFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextButtonS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function TextButtonS:HandleShowOverSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_over", self.HandleShowOverFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextButtonS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function TextButtonS:HandleShowDownSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_down", self.HandleShowDownFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function TextButtonS:HandleShowDisabledSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_disabled", self.HandleShowDisabledFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextButtonS:HandleShowTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function TextButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", true)
end

function TextButtonS:HandleShowOverTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_over_text", false)
end

function TextButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", true)
end

function TextButtonS:HandleShowDownTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_down_text", false)
end

function TextButtonS:HandleShowDownTextClear(event)
	self:RemoverToNilShowSet("show_down_text", "", true)
end

function TextButtonS:HandleShowDisabledTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function TextButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", true)
end

function TextButtonS:HandleHandFileSelectSELECT_CHANGE(event)
	self:BoolSelectChange("file_select", false, g_IDEEnum.yn_type)
end

