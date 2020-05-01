-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
DialogS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.DialogS")

function DialogS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_dialog")
end

function DialogS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("head_size")
	self:LoadDefaultNilString("title")
	self:LoadShowTypeDataForImage("show_background")
	self:LoadShowTypeDataForImage("show_head_drag")
	self:LoadShowTypeDataForExtends("show_close_button")
	self:LoadShowTypeNoNilData("show_title")
end

function DialogS:HandleHeadSizeFOCUSOUT(event)
	self:ValueNumInputChange("head_size", false)
end

function DialogS:HandleTitleFOCUSOUT(event)
	self:DefaultNoStringInputChange("title", false)
end

function DialogS:HandleShowBackgroundFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_background", self._show_background.text, self._show_background_grid9.selected, false)
end

function DialogS:HandleShowBackgroundSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_background", self.HandleShowBackgroundFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function DialogS:HandleShowHeadDragFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_head_drag", self._show_head_drag.text, self._show_head_drag_grid9.selected, false)
end

function DialogS:HandleShowHeadDragSelect(event)
	local func = Lua.Bind(self.ImagePathSelectCallback, self, "show_head_drag", self.HandleShowHeadDragFOCUSOUT, nil)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function DialogS:HandleShowCloseButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("show_close_button", self._show_close_button.text, false)
end

function DialogS:HandleShowTitleFOCUSOUT(event)
	g_IDEAttrTextDialog:ShowDialog(self, "show_title", false)
end

function DialogS:HandleShowTitleClear(event)
	self:RemoverToNilShowSet("show_title", "", true)
end

