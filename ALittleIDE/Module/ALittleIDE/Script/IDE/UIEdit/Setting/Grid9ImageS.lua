-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.Grid9S, " extends class:ALittleIDE.Grid9S is nil")
ALittleIDE.Grid9ImageS = Lua.Class(ALittleIDE.Grid9S, "ALittleIDE.Grid9ImageS")

function ALittleIDE.Grid9ImageS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_grid9image")
end

function ALittleIDE.Grid9ImageS:LoadNatureBase()
	ALittleIDE.Grid9S.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadEnumData("flip", ALittleIDE.g_IDEEnum.flip_type)
end

function ALittleIDE.Grid9ImageS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
	self:HandleAutoCut(event)
end

function ALittleIDE.Grid9ImageS:HandleImageTextureNameSelect(event)
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
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, nil, path, true)
end
ALittleIDE.Grid9ImageS.HandleImageTextureNameSelect = Lua.CoWrap(ALittleIDE.Grid9ImageS.HandleImageTextureNameSelect)

function ALittleIDE.Grid9ImageS:HandleFlipSELECT_CHANGE(event)
	local list = ALittleIDE.g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

function ALittleIDE.Grid9ImageS:HandleAutoCut(event)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tree_logic.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. self._tree_logic.user_info.module)
		return
	end
	local image_path = self._texture_name.text
	local display_info = ALittleIDE.IDEUIUtility_GenerateGrid9ImageInfo(ui_manager.texture_path .. "/", image_path)
	if display_info == nil then
		return
	end
	local revoke_bind = ALittle.RevokeBind()
	self._left_size.text = display_info.left_size
	self:ValueNumInputChange("left_size", false, revoke_bind)
	self._right_size.text = display_info.right_size
	self:ValueNumInputChange("right_size", false, revoke_bind)
	self._top_size.text = display_info.top_size
	self:ValueNumInputChange("top_size", false, revoke_bind)
	self._bottom_size.text = display_info.bottom_size
	self:ValueNumInputChange("bottom_size", false, revoke_bind)
	self._tab_child.revoke_list:PushRevoke(revoke_bind)
end

end