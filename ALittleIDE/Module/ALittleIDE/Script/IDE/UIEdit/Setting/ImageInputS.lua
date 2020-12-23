-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.TextInputS, " extends class:ALittleIDE.TextInputS is nil")
ALittleIDE.ImageInputS = Lua.Class(ALittleIDE.TextInputS, "ALittleIDE.ImageInputS")

function ALittleIDE.ImageInputS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_imageinput")
end

function ALittleIDE.ImageInputS:LoadNatureBase()
	ALittleIDE.TextInputS.LoadNatureBase(self)
	self:LoadValueData("margin_left")
	self:LoadValueData("margin_right")
	self:LoadValueData("margin_top")
	self:LoadValueData("margin_bottom")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
end

function ALittleIDE.ImageInputS:HandleMarginLeftFOCUSOUT(event)
	self:ValueNumInputChange("margin_left", false)
end

function ALittleIDE.ImageInputS:HandleMarginRightFOCUSOUT(event)
	self:ValueNumInputChange("margin_right", false)
end

function ALittleIDE.ImageInputS:HandleMarginTopFOCUSOUT(event)
	self:ValueNumInputChange("margin_top", false)
end

function ALittleIDE.ImageInputS:HandleMarginBottomFOCUSOUT(event)
	self:ValueNumInputChange("margin_bottom", false)
end

function ALittleIDE.ImageInputS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ALittleIDE.ImageInputS:HandleShowUpSelect(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_up", self.HandleShowUpFOCUSOUT, nil, path, true)
end
ALittleIDE.ImageInputS.HandleShowUpSelect = Lua.CoWrap(ALittleIDE.ImageInputS.HandleShowUpSelect)

function ALittleIDE.ImageInputS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function ALittleIDE.ImageInputS:HandleShowOverSelect(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_over", self.HandleShowOverFOCUSOUT, nil, path, true)
end
ALittleIDE.ImageInputS.HandleShowOverSelect = Lua.CoWrap(ALittleIDE.ImageInputS.HandleShowOverSelect)

function ALittleIDE.ImageInputS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function ALittleIDE.ImageInputS:HandleShowDownSelect(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_down", self.HandleShowDownFOCUSOUT, nil, path, true)
end
ALittleIDE.ImageInputS.HandleShowDownSelect = Lua.CoWrap(ALittleIDE.ImageInputS.HandleShowDownSelect)

function ALittleIDE.ImageInputS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ALittleIDE.ImageInputS:HandleShowDisabledSelect(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("show_disabled", self.HandleShowDisabledFOCUSOUT, nil, path, true)
end
ALittleIDE.ImageInputS.HandleShowDisabledSelect = Lua.CoWrap(ALittleIDE.ImageInputS.HandleShowDisabledSelect)

end