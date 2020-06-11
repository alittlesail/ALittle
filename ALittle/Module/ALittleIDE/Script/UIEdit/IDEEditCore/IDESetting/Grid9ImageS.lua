-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.Grid9S, " extends class:ALittleIDE.Grid9S is nil")
Grid9ImageS = Lua.Class(ALittleIDE.Grid9S, "ALittleIDE.Grid9ImageS")

function Grid9ImageS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_grid9image")
end

function Grid9ImageS:LoadNatureBase()
	Grid9S.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadEnumData("flip", g_IDEEnum.flip_type)
end

function Grid9ImageS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
	self:HandleAutoCut(event)
end

function Grid9ImageS:HandleImageTextureNameSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, nil, path)
end
Grid9ImageS.HandleImageTextureNameSelect = Lua.CoWrap(Grid9ImageS.HandleImageTextureNameSelect)

function Grid9ImageS:HandleFlipSELECT_CHANGE(event)
	local list = g_IDEEnum.flip_rtype
	self:TypeSelectChange("flip", list, false)
end

function Grid9ImageS:HandleAutoCut(event)
	local image_path = self._texture_name.text
	local display_info = IDEUtility_GenerateGrid9ImageInfo(g_IDEProject.project.texture_path .. "/", image_path)
	if display_info == nil then
		return
	end
	local revoke_bind = IDERevokeBind()
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

