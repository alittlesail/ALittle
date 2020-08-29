-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
GBRMaker.MainFileList = Lua.Class(ALittle.DisplayLayout, "GBRMaker.MainFileList")

function GBRMaker.MainFileList:HandleFileNewClick(event)
	local x, y = event.target:LocalToGlobal()
	local file_name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if file_name == "" or file_name == nil then
		return
	end
	local check, error = GBRMaker.IDEUtility_CheckResourceName(file_name)
	if not check then
		g_AUITool:ShowNotice("提示", error)
		return
	end
	local file_path = self._file_base_path .. "/" .. file_name .. ".map"
	if ALittle.File_GetFileAttr(file_path) ~= nil then
		g_AUITool:ShowNotice("提示", "文件已存在")
		return
	end
	ALittle.File_WriteTextToFile("", file_path)
	self:RefreshFile()
end
GBRMaker.MainFileList.HandleFileNewClick = Lua.CoWrap(GBRMaker.MainFileList.HandleFileNewClick)

function GBRMaker.MainFileList:HandleSelectFile(event)
	if not event.target.selected then
		return
	end
	g_GCenter:SaveCurEdit(true)
	local info = event.target._user_data
	if info.map_data == nil then
		local rflct = ___all_struct[-1481607580]
		local factory = __CPPAPIMessageReadFactory()
		if not factory:ReadFromStdFile(info.file_path) then
			return
		end
		local invoke_info = ALittle.CreateMessageInfo(rflct.name)
		if invoke_info == nil then
			return
		end
		info.map_data = ALittle.PS_ReadMessage(factory, invoke_info, nil, factory:GetDataSize())
		info.map_info = {}
		info.map_info.tex_map = {}
		info.map_info.tex_max_id = 0
		for id, path in ___pairs(info.map_data.tex_map) do
			info.map_info.tex_map[path] = id
			if info.map_info.tex_max_id < id then
				info.map_info.tex_max_id = id
			end
		end
		info.map_info.floor_list = {}
		for index, floor_data in ___ipairs(info.map_data.floor_list) do
			local floor_info = {}
			floor_info.floor_data = floor_data
			floor_info.file_info = info
			floor_info.visible = true
			floor_info.child_map = {}
			ALittle.List_Push(info.map_info.floor_list, floor_info)
		end
	end
	g_GCenter:StartEdit(info)
end

function GBRMaker.MainFileList:RefreshFile()
	local setting_data = g_GCenter.setting_dialog.data
	self._file_base_path = "Module/" .. setting_data.project_name .. "/Other/" .. setting_data.data_path
	self._file_cache_list = {}
	self._file_radio_group = {}
	self._file_scroll_screen:RemoveAllChild()
	if ALittle.File_GetFileAttr(self._file_base_path) == nil then
		return
	end
	local file_list = ALittle.File_GetFileListByDir(self._file_base_path)
	ALittle.List_Sort(file_list)
	for index, file_path in ___ipairs(file_list) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(self._file_base_path) + 2)
		local info = {}
		info.item = GBRMaker.g_Control:CreateControl("ide_common_item_radiobutton", info)
		info.item._user_data = info
		info.item.group = self._file_radio_group
		info.item.text = ALittle.File_GetJustFileNameByPath(rel_path)
		info.upper_file_name = ALittle.String_Upper(info.item.text)
		info.file_path = file_path
		info.save = true
		info.item:AddEventListener(___all_struct[958494922], self, self.HandleSelectFile)
		info.item.drag_trans_target = self._file_scroll_screen
		self._file_cache_list[index] = info
	end
	self:HandleFileSearchClick(nil)
end

function GBRMaker.MainFileList:HandleFileSearchClick(event)
	self._file_scroll_screen:RemoveAllChild()
	local upper_key = ALittle.String_Upper(self._file_search_key.text)
	for index, info in ___ipairs(self._file_cache_list) do
		if ALittle.String_Find(info.upper_file_name, upper_key) ~= nil then
			self._file_scroll_screen:AddChild(info.item)
		end
	end
end

end