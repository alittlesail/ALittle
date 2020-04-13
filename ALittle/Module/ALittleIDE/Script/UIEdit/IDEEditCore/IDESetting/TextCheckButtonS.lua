
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
TextCheckButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TextCheckButtonS")

function TextCheckButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textcheckbutton")
end

function TextCheckButtonS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadBoolData("selected", false, g_IDEEnum.yn_type)
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
	self:LoadShowTypeDataForImage("show_selected_up")
	self:LoadShowTypeDataForImage("show_selected_over")
	self:LoadShowTypeDataForImage("show_selected_down")
	self:LoadShowTypeDataForImage("show_selected_disabled")
	self:LoadShowTypeNoNilData("show_text")
	self:LoadShowTypeNoNilData("show_over_text")
	self:LoadShowTypeNoNilData("show_down_text")
	self:LoadShowTypeNoNilData("show_disabled_text")
	self:LoadShowTypeNoNilData("show_selected_text")
	self:LoadShowTypeNoNilData("show_selected_over_text")
	self:LoadShowTypeNoNilData("show_selected_down_text")
	self:LoadShowTypeNoNilData("show_selected_disabled_text")
end

function TextCheckButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
end

function TextCheckButtonS:HandleSelectedSELECT_CHANGE(event)
	self:BoolSelectChange("selected", false, g_IDEEnum.yn_type)
end

function TextCheckButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function TextCheckButtonS:HandleShowUpSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_up", self.HandleShowUpFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function TextCheckButtonS:HandleShowOverSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_over", self.HandleShowOverFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function TextCheckButtonS:HandleShowDownSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_down", self.HandleShowDownFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function TextCheckButtonS:HandleShowDisabledSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_disabled", self.HandleShowDisabledFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowSUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_up", self._show_selected_up.text, self._show_selected_up_grid9.selected, false)
end

function TextCheckButtonS:HandleShowSUpSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_selected_up", self.HandleShowSUpFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowSOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_over", self._show_selected_over.text, self._show_selected_over_grid9.selected, false)
end

function TextCheckButtonS:HandleShowSOverSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_selected_over", self.HandleShowSOverFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowSDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_down", self._show_selected_down.text, self._show_selected_down_grid9.selected, false)
end

function TextCheckButtonS:HandleShowSDownSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_selected_down", self.HandleShowSDownFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowSDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_disabled", self._show_selected_disabled.text, self._show_selected_disabled_grid9.selected, false)
end

function TextCheckButtonS:HandleShowSDisabledSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_selected_disabled", self.HandleShowSDisabledFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function TextCheckButtonS:HandleShowTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function TextCheckButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", false)
end

function TextCheckButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", false)
end

function TextCheckButtonS:HandleShowOverTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_over_text", false)
end

function TextCheckButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", false)
end

function TextCheckButtonS:HandleShowDownTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_down_text", false)
end

function TextCheckButtonS:HandleShowDownTextClear(event)
	self:RemoverToNilShowSet("show_down_text", "", false)
end

function TextCheckButtonS:HandleShowDisabledTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function TextCheckButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", false)
end

function TextCheckButtonS:HandleShowSelectedTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_selected_text", false)
end

function TextCheckButtonS:HandleShowSelectedTextClear(event)
	self:RemoverToNilShowSet("show_selected_text", "", false)
end

function TextCheckButtonS:HandleShowSelectedOverTextClear(event)
	self:RemoverToNilShowSet("show_selected_over_text", "", false)
end

function TextCheckButtonS:HandleShowSelectedOverTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_selected_over_text", false)
end

function TextCheckButtonS:HandleShowSelectedOverTextClear(event)
	self:RemoverToNilShowSet("show_selected_over_text", "", false)
end

function TextCheckButtonS:HandleShowSelectedDownTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_selected_down_text", false)
end

function TextCheckButtonS:HandleShowSelectedDownTextClear(event)
	self:RemoverToNilShowSet("show_selected_down_text", "", false)
end

function TextCheckButtonS:HandleShowSelectedDisabledTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_selected_disabled_text", false)
end

function TextCheckButtonS:HandleShowSelectedDisabledTextClear(event)
	self:RemoverToNilShowSet("show_selected_disabled_text", "", false)
end

