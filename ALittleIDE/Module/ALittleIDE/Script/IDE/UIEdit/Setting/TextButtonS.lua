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
ALittleIDE.TextButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.TextButtonS")

function ALittleIDE.TextButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_textbutton")
end

function ALittleIDE.TextButtonS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadEnumData("text_x_type", ALittleIDE.g_IDEEnum.xy_type)
	self:LoadValueData("text_x_value")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_over")
	self:LoadShowTypeDataForImage("show_down")
	self:LoadShowTypeDataForImage("show_disabled")
	self:LoadShowTypeNoNilData("show_text")
	self:LoadShowTypeNoNilData("show_over_text")
	self:LoadShowTypeNoNilData("show_down_text")
	self:LoadShowTypeNoNilData("show_disabled_text")
	self:LoadEnumData("file_select", ALittleIDE.g_IDEEnum.select_type)
end

function ALittleIDE.TextButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
	self._tree_logic:UpdateDesc()
end

function ALittleIDE.TextButtonS:HandleTextXTypeSELECT_CHANGE(event)
	local object = self._object
	local target_x = object.text_x_type
	local new_x = target_x
	local list = ALittleIDE.g_IDEEnum.xy_rtype
	local revoke_bind = ALittle.RevokeBind()
	self:TypeSelectChange("text_x_type", list, false, revoke_bind)
end

function ALittleIDE.TextButtonS:HandleTextXValueFOCUSOUT(event)
	self._base.text_x_value = nil
	self:ValueNumInputChange("text_x_value", true)
end

function ALittleIDE.TextButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ALittleIDE.TextButtonS:HandleShowUpSelect(event)
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
ALittleIDE.TextButtonS.HandleShowUpSelect = Lua.CoWrap(ALittleIDE.TextButtonS.HandleShowUpSelect)

function ALittleIDE.TextButtonS:HandleShowOverFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_over", self._show_over.text, self._show_over_grid9.selected, false)
end

function ALittleIDE.TextButtonS:HandleShowOverSelect(event)
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
ALittleIDE.TextButtonS.HandleShowOverSelect = Lua.CoWrap(ALittleIDE.TextButtonS.HandleShowOverSelect)

function ALittleIDE.TextButtonS:HandleShowDownFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_down", self._show_down.text, self._show_down_grid9.selected, false)
end

function ALittleIDE.TextButtonS:HandleShowDownSelect(event)
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
ALittleIDE.TextButtonS.HandleShowDownSelect = Lua.CoWrap(ALittleIDE.TextButtonS.HandleShowDownSelect)

function ALittleIDE.TextButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ALittleIDE.TextButtonS:HandleShowDisabledSelect(event)
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
ALittleIDE.TextButtonS.HandleShowDisabledSelect = Lua.CoWrap(ALittleIDE.TextButtonS.HandleShowDisabledSelect)

function ALittleIDE.TextButtonS:HandleShowTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function ALittleIDE.TextButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", true)
end

function ALittleIDE.TextButtonS:HandleShowOverTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_over_text", false)
end

function ALittleIDE.TextButtonS:HandleShowOverTextClear(event)
	self:RemoverToNilShowSet("show_over_text", "", true)
end

function ALittleIDE.TextButtonS:HandleShowDownTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_down_text", false)
end

function ALittleIDE.TextButtonS:HandleShowDownTextClear(event)
	self:RemoverToNilShowSet("show_down_text", "", true)
end

function ALittleIDE.TextButtonS:HandleShowDisabledTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function ALittleIDE.TextButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", true)
end

function ALittleIDE.TextButtonS:HandleHandFileSelectSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.select_rtype
	local revoke_bind = ALittle.RevokeBind()
	self:TypeSelectChange("file_select", list, false, revoke_bind)
end

end