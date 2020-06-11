-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextInputS, " extends class:ALittleIDE.TextInputS is nil")
ImageInputS = Lua.Class(ALittleIDE.TextInputS, "ALittleIDE.ImageInputS")

function ImageInputS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_imageinput")
end

function ImageInputS:LoadNatureBase()
	TextInputS.LoadNatureBase(self)
	self:LoadValueData("margin_left")
	self:LoadValueData("margin_right")
	self:LoadValueData("margin_top")
	self:LoadValueData("margin_bottom")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
end

function ImageInputS:HandleMarginLeftFOCUSOUT(event)
	self:ValueNumInputChange("margin_left", false)
end

function ImageInputS:HandleMarginRightFOCUSOUT(event)
	self:ValueNumInputChange("margin_right", false)
end

function ImageInputS:HandleMarginTopFOCUSOUT(event)
	self:ValueNumInputChange("margin_top", false)
end

function ImageInputS:HandleMarginBottomFOCUSOUT(event)
	self:ValueNumInputChange("margin_bottom", false)
end

function ImageInputS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ImageInputS:HandleShowUpSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_up", self.HandleShowUpFOCUSOUT, nil, path)
end
ImageInputS.HandleShowUpSelect = Lua.CoWrap(ImageInputS.HandleShowUpSelect)

function ImageInputS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function ImageInputS:HandleShowOverSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_over", self.HandleShowOverFOCUSOUT, nil, path)
end
ImageInputS.HandleShowOverSelect = Lua.CoWrap(ImageInputS.HandleShowOverSelect)

function ImageInputS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function ImageInputS:HandleShowDownSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_down", self.HandleShowDownFOCUSOUT, nil, path)
end
ImageInputS.HandleShowDownSelect = Lua.CoWrap(ImageInputS.HandleShowDownSelect)

function ImageInputS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ImageInputS:HandleShowDisabledSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_disabled", self.HandleShowDisabledFOCUSOUT, nil, path)
end
ImageInputS.HandleShowDisabledSelect = Lua.CoWrap(ImageInputS.HandleShowDisabledSelect)

