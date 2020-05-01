-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ScrollButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.ScrollButtonS")

function ScrollButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrollbutton")
end

function ScrollButtonS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
end

function ScrollButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
end

function ScrollButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ScrollButtonS:HandleShowUpSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_up", self.HandleShowUpFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function ScrollButtonS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function ScrollButtonS:HandleShowOverSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_over", self.HandleShowOverFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function ScrollButtonS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function ScrollButtonS:HandleShowDownSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_down", self.HandleShowDownFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function ScrollButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ScrollButtonS:HandleShowDisabledSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_disabled", self.HandleShowDisabledFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function ScrollButtonS:HandleShowTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function ScrollButtonS:HandleShowOverTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_over_text", false)
end

function ScrollButtonS:HandleShowDownTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_down_text", false)
end

function ScrollButtonS:HandleShowDisabledTextFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

