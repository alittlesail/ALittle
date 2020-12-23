-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.Grid3S, " extends class:ALittleIDE.Grid3S is nil")
ALittleIDE.ScrollBarS = Lua.Class(ALittleIDE.Grid3S, "ALittleIDE.ScrollBarS")

function ALittleIDE.ScrollBarS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrollbar")
end

function ALittleIDE.ScrollBarS:LoadNatureBase()
	ALittleIDE.Grid3S.LoadNatureBase(self)
	self:LoadValueData("total_size")
	self:LoadValueData("show_size")
	self:LoadValueData("offset_rate")
	self:LoadValueData("offset_step")
	self:LoadShowTypeDataForExtends("up_button")
	self:LoadShowTypeDataForExtends("down_button")
	self:LoadShowTypeDataForExtends("bar_button")
	self:LoadShowTypeDataForImage("bar_background")
end

function ALittleIDE.ScrollBarS:HandleTotleSizeFOCUSOUT(event)
	self:ValueNumInputChange("total_size", false)
end

function ALittleIDE.ScrollBarS:HandleShowSizeFOCUSOUT(event)
	self:ValueNumInputChange("show_size", false)
end

function ALittleIDE.ScrollBarS:HandleOffsetRateFOCUSOUT(event)
	self:Z2OValueInputChange("offset_rate", false)
end

function ALittleIDE.ScrollBarS:HandleOffsetStepFOCUSOUT(event)
	self:Z2OValueInputChange("offset_step", false)
end

function ALittleIDE.ScrollBarS:HandleUpButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("up_button", self._up_button.text, false)
end

function ALittleIDE.ScrollBarS:HandleDownButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("down_button", self._down_button.text, false)
end

function ALittleIDE.ScrollBarS:HandleBarButtonFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bar_button", self._bar_button.text, false)
end

function ALittleIDE.ScrollBarS:HandleBarBackFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForImage("bar_background", self._bar_background.text, self._bar_background_grid9.selected, false)
end

function ALittleIDE.ScrollBarS:HandleBarBackSelect(event)
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
	self:ImagePathSelectCallback("bar_background", self.HandleBarBackFOCUSOUT, nil, path, false)
end
ALittleIDE.ScrollBarS.HandleBarBackSelect = Lua.CoWrap(ALittleIDE.ScrollBarS.HandleBarBackSelect)

end