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
ALittleIDE.SpringTextButtonS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.SpringTextButtonS")

function ALittleIDE.SpringTextButtonS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_springtextbutton")
end

function ALittleIDE.SpringTextButtonS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("text")
	self:LoadShowTypeDataForImage("show_up")
	self:LoadShowTypeDataForImage("show_disabled")
	self:LoadShowTypeNoNilData("show_text")
	self:LoadShowTypeNoNilData("show_disabled_text")
	self:LoadBoolData("file_select", false, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.SpringTextButtonS:HandleMTextFOCUSOUT(event)
	self:DefaultNoStringInputChange("text", false)
end

function ALittleIDE.SpringTextButtonS:HandleShowUpFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_up", self._show_up.text, self._show_up_grid9.selected, false)
end

function ALittleIDE.SpringTextButtonS:HandleShowUpSelect(event)
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
ALittleIDE.SpringTextButtonS.HandleShowUpSelect = Lua.CoWrap(ALittleIDE.SpringTextButtonS.HandleShowUpSelect)

function ALittleIDE.SpringTextButtonS:HandleShowDisabledFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_disabled", self._show_disabled.text, self._show_disabled_grid9.selected, false)
end

function ALittleIDE.SpringTextButtonS:HandleShowDisabledSelect(event)
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
ALittleIDE.SpringTextButtonS.HandleShowDisabledSelect = Lua.CoWrap(ALittleIDE.SpringTextButtonS.HandleShowDisabledSelect)

function ALittleIDE.SpringTextButtonS:HandleShowTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_text", false)
end

function ALittleIDE.SpringTextButtonS:HandleShowTextClear(event)
	self:RemoverToNilShowSet("show_text", "", true)
end

function ALittleIDE.SpringTextButtonS:HandleShowDisabledTextFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_disabled_text", false)
end

function ALittleIDE.SpringTextButtonS:HandleShowDisabledTextClear(event)
	self:RemoverToNilShowSet("show_disabled_text", "", true)
end

function ALittleIDE.SpringTextButtonS:HandleHandFileSelectSELECT_CHANGE(event)
	self:BoolSelectChange("file_select", false, ALittleIDE.g_IDEEnum.yn_type)
end

end