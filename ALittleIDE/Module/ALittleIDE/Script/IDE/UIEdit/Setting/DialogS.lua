-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.DialogS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.DialogS")

function ALittleIDE.DialogS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_dialog")
end

function ALittleIDE.DialogS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("head_size")
	self:LoadDefaultNilString("title")
	self:LoadShowTypeDataForImage("show_background")
	self:LoadShowTypeDataForImage("show_head_drag")
	self:LoadShowTypeDataForExtends("show_close_button")
	self:LoadShowTypeNoNilData("show_title")
end

function ALittleIDE.DialogS:HandleHeadSizeFOCUSOUT(event)
	self:ValueNumInputChange("head_size", false)
end

function ALittleIDE.DialogS:HandleTitleFOCUSOUT(event)
	self:DefaultNoStringInputChange("title", false)
end

function ALittleIDE.DialogS:HandleShowBackgroundFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_background", self._show_background.text, self._show_background_grid9.selected, false)
end

function ALittleIDE.DialogS:HandleShowBackgroundSelect(event)
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
	self:ImagePathSelectCallback("show_background", self.HandleShowBackgroundFOCUSOUT, nil, path)
end
ALittleIDE.DialogS.HandleShowBackgroundSelect = Lua.CoWrap(ALittleIDE.DialogS.HandleShowBackgroundSelect)

function ALittleIDE.DialogS:HandleShowHeadDragFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("show_head_drag", self._show_head_drag.text, self._show_head_drag_grid9.selected, false)
end

function ALittleIDE.DialogS:HandleShowHeadDragSelect(event)
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
	self:ImagePathSelectCallback("show_head_drag", self.HandleShowHeadDragFOCUSOUT, nil, path)
end
ALittleIDE.DialogS.HandleShowHeadDragSelect = Lua.CoWrap(ALittleIDE.DialogS.HandleShowHeadDragSelect)

function ALittleIDE.DialogS:HandleShowCloseButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("show_close_button", nil, self._show_close_button.text, false)
end

function ALittleIDE.DialogS:HandleShowTitleFOCUSOUT(event)
	ALittleIDE.g_IDEAttrTextDialog:ShowDialog(self, "show_title", false)
end

function ALittleIDE.DialogS:HandleShowTitleClear(event)
	self:RemoverToNilShowSet("show_title", "", true)
end

end