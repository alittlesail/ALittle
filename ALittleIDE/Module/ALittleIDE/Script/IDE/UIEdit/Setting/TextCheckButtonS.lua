-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.TextCheckButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TextCheckButtonS")

function ALittleIDE.TextCheckButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textcheckbutton")
end

function ALittleIDE.TextCheckButtonS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadEnumData("text_x_type", ALittleIDE.g_IDEEnum.xy_type)
	self:LoadValueData("text_x_value")
	self:LoadBoolData("selected", false, ALittleIDE.g_IDEEnum.yn_type)
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

function ALittleIDE.TextCheckButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
	self._tree_logic:UpdateDesc()
end

function ALittleIDE.TextCheckButtonS:HandleTextXTypeSELECT_CHANGE(event)
	local object = self._object
	local target_x = object.text_x_type
	local new_x = target_x
	local list = ALittleIDE.g_IDEEnum.xy_rtype
	local revoke_bind = ALittle.RevokeBind()
	self:TypeSelectChange("text_x_type", list, false, revoke_bind)
end

function ALittleIDE.TextCheckButtonS:HandleTextXValueFOCUSOUT(event)
	self._base.text_x_value = nil
	self:ValueNumInputChange("text_x_value", true)
end

function ALittleIDE.TextCheckButtonS:HandleSelectedSELECT_CHANGE(event)
	self:BoolSelectChange("selected", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.TextCheckButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowUpSelect(event)
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
ALittleIDE.TextCheckButtonS.HandleShowUpSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowUpSelect)

function ALittleIDE.TextCheckButtonS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowOverSelect(event)
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
ALittleIDE.TextCheckButtonS.HandleShowOverSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowOverSelect)

function ALittleIDE.TextCheckButtonS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDownSelect(event)
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
ALittleIDE.TextCheckButtonS.HandleShowDownSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowDownSelect)

function ALittleIDE.TextCheckButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDisabledSelect(event)
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
ALittleIDE.TextCheckButtonS.HandleShowDisabledSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowDisabledSelect)

function ALittleIDE.TextCheckButtonS:HandleShowSUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_up", self._show_selected_up.text, self._show_selected_up_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSUpSelect(event)
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
	self:ImagePathSelectCallback("show_selected_up", self.HandleShowSUpFOCUSOUT, nil, path, true)
end
ALittleIDE.TextCheckButtonS.HandleShowSUpSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowSUpSelect)

function ALittleIDE.TextCheckButtonS:HandleShowSOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_over", self._show_selected_over.text, self._show_selected_over_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSOverSelect(event)
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
	self:ImagePathSelectCallback("show_selected_over", self.HandleShowSOverFOCUSOUT, nil, path, true)
end
ALittleIDE.TextCheckButtonS.HandleShowSOverSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowSOverSelect)

function ALittleIDE.TextCheckButtonS:HandleShowSDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_down", self._show_selected_down.text, self._show_selected_down_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSDownSelect(event)
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
	self:ImagePathSelectCallback("show_selected_down", self.HandleShowSDownFOCUSOUT, nil, path, true)
end
ALittleIDE.TextCheckButtonS.HandleShowSDownSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowSDownSelect)

function ALittleIDE.TextCheckButtonS:HandleShowSDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_selected_disabled", self._show_selected_disabled.text, self._show_selected_disabled_grid9.selected, false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSDisabledSelect(event)
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
	self:ImagePathSelectCallback("show_selected_disabled", self.HandleShowSDisabledFOCUSOUT, nil, path, true)
end
ALittleIDE.TextCheckButtonS.HandleShowSDisabledSelect = Lua.CoWrap(ALittleIDE.TextCheckButtonS.HandleShowSDisabledSelect)

function ALittleIDE.TextCheckButtonS:HandleShowTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowOverTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_over_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDownTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_down_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDownTextClear(event)
	self:RemoverToNilShowSet("show_down_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDisabledTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_selected_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedTextClear(event)
	self:RemoverToNilShowSet("show_selected_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedOverTextClear(event)
	self:RemoverToNilShowSet("show_selected_over_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedOverTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_selected_over_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedOverTextClear(event)
	self:RemoverToNilShowSet("show_selected_over_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedDownTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_selected_down_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedDownTextClear(event)
	self:RemoverToNilShowSet("show_selected_down_text", "", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedDisabledTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_selected_disabled_text", false)
end

function ALittleIDE.TextCheckButtonS:HandleShowSelectedDisabledTextClear(event)
	self:RemoverToNilShowSet("show_selected_disabled_text", "", false)
end

end