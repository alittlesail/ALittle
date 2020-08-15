-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
GBRMaker.MainTextureList = Lua.Class(ALittle.DisplayLayout, "GBRMaker.MainTextureList")

function GBRMaker.MainTextureList:Ctor()
	___rawset(self, "_real_size", 100)
end

function GBRMaker.MainTextureList.__getter:tex_name_base_path()
	return self._tex_name_base_path
end

function GBRMaker.MainTextureList.__getter:texture_base_path()
	return self._texture_base_path
end

function GBRMaker.MainTextureList:RefreshTexture()
	local setting_data = g_GCenter.setting_dialog.data
	local module_path = "Module/" .. setting_data.project_name
	self._tex_name_base_path = setting_data.texture_path .. "/"
	self._texture_base_path = module_path .. "/Texture/" .. setting_data.texture_path
	self._image_cache_list = {}
	self._texture_scroll_list:RemoveAllChild()
	if ALittle.File_GetFileAttr(self._texture_base_path) == nil then
		return
	end
	local file_list = ALittle.File_GetFileListByDir(self._texture_base_path)
	ALittle.List_Sort(file_list)
	for index, file_path in ___ipairs(file_list) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(self._texture_base_path) + 2)
		local texture_name = self._tex_name_base_path .. rel_path
		local info = {}
		info.item = GBRMaker.g_Control:CreateControl("ide_image_select_item", info)
		info.button._user_data = info
		info.image:SetTextureCut(file_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
		info.name.text = ALittle.File_GetJustFileNameByPath(rel_path)
		info.upper_file_name = ALittle.String_Upper(info.name.text)
		info.file_path = file_path
		info.button.drag_trans_target = self._texture_scroll_list
		info.button:AddEventListener(___all_struct[-449066808], self, self.HandleTextureSelectClick)
		self._image_cache_list[index] = info
	end
	self:HandleTextureSearchClick(nil)
end

function GBRMaker.MainTextureList:HandleTextureSearchClick(event)
	self._texture_scroll_list:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._texture_search_key.text)
	local col_count = ALittle.Math_Floor(self._texture_scroll_list.width / self._real_size)
	local remain_count = 0
	local container = nil
	for index, info in ___ipairs(self._image_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			if remain_count == 0 then
				container = ALittle.Linear(GBRMaker.g_Control)
				container.type = 1
				container.height = info.item.height
				self._texture_scroll_list:AddChild(container)
				container:AddChild(info.item)
				remain_count = col_count - 1
			else
				remain_count = remain_count - 1
				container:AddChild(info.item)
			end
		end
	end
end

function GBRMaker.MainTextureList:HandleTextureSelectClick(event)
	local ctrl = A_UISystem.sym_map[1073742048]
	local multi = ctrl ~= nil
	local image_info = event.target._user_data
	local rel_path = ALittle.String_Sub(image_info.file_path, ALittle.String_Len(self._texture_base_path) + 2)
	local texture_name = self._tex_name_base_path .. rel_path
	g_GCenter:SelectTexture(image_info, multi)
end

function GBRMaker.MainTextureList:HandleDragRightQuadUD(event)
	g_GCenter.right_grad3_ud.up_size = g_GCenter.right_grad3_ud.up_size + (event.delta_y)
end

function GBRMaker.MainTextureList:HandleDragEndRightQuadUD(event)
	GBRMaker.g_GConfig:SetConfig("right_grid3_up_size", g_GCenter.right_grad3_ud.up_size)
end

function GBRMaker.MainTextureList:HandleSetVDragCursor(event)
	ALittle.System_SetVDragCursor()
end

function GBRMaker.MainTextureList:HandleSetHDragCursor(event)
	ALittle.System_SetHDragCursor()
end

function GBRMaker.MainTextureList:HandleSetNormalCursor(event)
	ALittle.System_SetNormalCursor()
end

end