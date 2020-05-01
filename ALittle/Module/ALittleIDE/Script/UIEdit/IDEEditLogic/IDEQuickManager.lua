-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2082638860, "ALittleIDE.IDEQuickInfo", {
name = "ALittleIDE.IDEQuickInfo", ns_name = "ALittleIDE", rl_name = "IDEQuickInfo", hash_code = -2082638860,
name_list = {"scroll_list","item_map"},
type_list = {"ALittle.ScrollList","Map<string,ALittle.DisplayObject>"},
option_map = {}
})
ALittle.RegStruct(-57691431, "ALittleIDE.IDEQuickItemInfo", {
name = "ALittleIDE.IDEQuickItemInfo", ns_name = "ALittleIDE", rl_name = "IDEQuickItemInfo", hash_code = -57691431,
name_list = {"image","button","name","frame"},
type_list = {"ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(2079069064, "ALittleIDE.IDEQuickItemUserData", {
name = "ALittleIDE.IDEQuickItemUserData", ns_name = "ALittleIDE", rl_name = "IDEQuickItemUserData", hash_code = 2079069064,
name_list = {"path","flag_type","name","directory"},
type_list = {"string","string","string","bool"},
option_map = {}
})
ALittle.RegStruct(220740939, "ALittleIDE.IDEQuickLoadingInfo", {
name = "ALittleIDE.IDEQuickLoadingInfo", ns_name = "ALittleIDE", rl_name = "IDEQuickLoadingInfo", hash_code = 220740939,
name_list = {"map","loop"},
type_list = {"Map<ALittleIDE.IDEQuickItemInfo,bool>","int"},
option_map = {}
})
ALittle.RegStruct(884272790, "ALittleIDE.IDEQuickConfigInfo", {
name = "ALittleIDE.IDEQuickConfigInfo", ns_name = "ALittleIDE", rl_name = "IDEQuickConfigInfo", hash_code = 884272790,
name_list = {"name","time"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(2050097508, "ALittleIDE.IDEQuickSearchRunTime", {
name = "ALittleIDE.IDEQuickSearchRunTime", ns_name = "ALittleIDE", rl_name = "IDEQuickSearchRunTime", hash_code = 2050097508,
name_list = {"cur_count","total_count","item_count"},
type_list = {"int","int","int"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
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
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

IDEQuickManager = Lua.Class(nil, "ALittleIDE.IDEQuickManager")

function IDEQuickManager:Ctor()
	___rawset(self, "_flag_type_list", {"常用按钮", "常用图片", "常用文本", "其他常用"})
	___rawset(self, "_quick_map", {})
	for k, flag_type in ___ipairs(self._flag_type_list) do
		self._quick_map[flag_type] = {}
	end
	___rawset(self, "_first_tab", nil)
	___rawset(self, "_real_size", 80)
	___rawset(self, "_loading", {})
end

function IDEQuickManager:Setup(project_quick_tab)
	g_IDEProject:AddEventListener(___all_struct[1962591044], self, self.HandleDeleteControl)
	g_IDEProject:AddEventListener(___all_struct[374071006], self, self.HandleChangeControl)
	g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleOpenProject)
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleCloseProject)
	self._project_quick_tab = project_quick_tab
	self._first_tab = g_Control:CreateControl("ide_main_project_quick_search", self)
	self._project_quick_tab:AddChild(self._first_tab)
	self._project_quick_tab:SetChildText(self._first_tab, "控件选择器")
	for k, flag_type in ___ipairs(self._flag_type_list) do
		local item = g_Control:CreateControl("ide_common_scroll_list", self)
		self._project_quick_tab:AddChild(item)
		self._project_quick_tab:SetChildText(item, flag_type)
		self._quick_map[flag_type].scroll_list = item
	end
end

function IDEQuickManager:CreateItemDelay(control, abs_path)
	g_Control:SaveControlToFile(control, abs_path)
	local loading = self._loading[abs_path]
	if loading == nil then
		return
	end
	for info, v in ___pairs(loading.map) do
		info.image:SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
	end
end

function IDEQuickManager:CreateItem(control_info, flag_type)
	local info = {}
	local item = g_Control:CreateControl("ide_quick_select_item", info)
	info.name.text = control_info.name
	if ALittle.File_GetFileAttr(self._base_path) == nil then
		ALittle.File_MakeDeepDir(self._base_path)
	end
	local abs_path = self._base_path .. "/" .. control_info.name .. ".png"
	local width = nil
	local height = nil
	local surface = ALittle.System_LoadSurface(abs_path)
	if surface ~= nil then
		width = ALittle.System_GetSurfaceWidth(surface)
		height = ALittle.System_GetSurfaceHeight(surface)
		ALittle.System_FreeSurface(surface)
	end
	if width == nil then
		local control = g_IDEProject.project.control:CreateControl(control_info.name)
		if control == nil then
			return nil
		end
		width = control.width
		height = control.height
		if width <= 0 then
			control.width = g_IDEProject.project.config:GetConfig("default_show_width", 800)
			width = control.width
		end
		if height <= 0 then
			control.height = g_IDEProject.project.config:GetConfig("default_show_height", 800)
			height = control.height
		end
		local loading = self._loading[abs_path]
		if loading == nil then
			loading = {}
			loading.map = {}
			self._loading[abs_path] = loading
			loading.loop = A_LoopSystem:AddTimer(2000, Lua.Bind(self.CreateItemDelay, self, control, abs_path))
		end
		loading.map[info] = true
	else
		info.image:SetTextureCut(abs_path, ALittle.Math_Floor(info.frame.width), ALittle.Math_Floor(info.frame.height), true)
	end
	if width < height then
		local rate = width / height
		height = info.frame.height
		width = rate * height
	else
		local rate = height / width
		width = info.frame.width
		height = rate * width
	end
	info.image.width = width
	info.image.height = height
	info.image:UpdateLayout()
	info.button:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
	info.button:AddEventListener(___all_struct[-641444818], self, self.HandleItemRButtonDown)
	info.button:AddEventListener(___all_struct[544684311], self, self.HandleItemMoveIn)
	info.button:AddEventListener(___all_struct[-1202439334], self, self.HandleItemMoveOut)
	info.button:AddEventListener(___all_struct[-1001723540], self, self.HandleItemMouseMove)
	info.button:AddEventListener(___all_struct[1301789264], self, self.HandleItemDragBegin)
	info.button:AddEventListener(___all_struct[1337289812], self, self.HandleItemDrag)
	info.button:AddEventListener(___all_struct[150587926], self, self.HandleItemDragEnd)
	local user_data = {}
	user_data.path = abs_path
	user_data.flag_type = flag_type
	user_data.name = control_info.name
	user_data.directory = false
	info.button._user_data = user_data
	item._user_data = user_data
	return item
end

function IDEQuickManager:CreateItemAndAddToList(scroll_list, item_list)
	local col_count = ALittle.Math_Floor(scroll_list.width / self._real_size)
	local remain_count = 0
	local container = nil
	for index, item in ___ipairs(item_list) do
		if remain_count == 0 then
			container = ALittle.Linear(g_Control)
			container.type = 1
			container.height = item.height
			scroll_list:AddChild(container)
			container:AddChild(item)
			remain_count = col_count - 1
		else
			remain_count = remain_count - 1
			container:AddChild(item)
		end
	end
end

function IDEQuickManager:AddToList(scroll_list, item)
	local col_count = ALittle.Math_Floor(scroll_list.width / self._real_size)
	local container = scroll_list:GetChildByIndex(scroll_list.child_count)
	if container ~= nil and container.child_count >= col_count then
		container = nil
	end
	if container == nil then
		container = ALittle.Linear(g_Control)
		container.type = 1
		container.height = item.height
		scroll_list:AddChild(container)
	end
	container:AddChild(item)
end

function IDEQuickManager:RemoveFromList(scroll_list, item)
	local item_list = {}
	local item_count = 0
	local childs = scroll_list.childs
	for k, child in ___ipairs(childs) do
		for _, child_item in ___ipairs(child.childs) do
			if child_item ~= item then
				item_count = item_count + 1
				item_list[item_count] = child_item
			end
		end
	end
	scroll_list:RemoveAllChild()
	self:CreateItemAndAddToList(scroll_list, item_list)
end

function IDEQuickManager:SearchCollect(search_type, key, item_list, run_time)
	if item_list == nil then
		item_list = {}
	end
	if run_time == nil then
		run_time = {}
		run_time.cur_count = 0
		run_time.total_count = 100
		run_time.item_count = 0
	end
	if key == "" or key == nil then
		return item_list, run_time
	end
	local project = g_IDEProject.project
	if project == nil then
		g_IDETool:ShowNotice("提示", "当前没有打开的项目")
		return nil, nil
	end
	local control_map = project.control_map
	for control_name, control_info in ___pairs(control_map) do
		if search_type == "控件名|描述" then
			if key == "" or ALittle.String_Find(control_name, key) ~= nil or (control_info.info.description ~= nil and ALittle.String_Find(control_info.info.description, key) ~= nil) then
				local item = self:CreateItem(control_info, "控件选择器")
				if item ~= nil then
					run_time.item_count = run_time.item_count + 1
					item_list[run_time.item_count] = item
				end
			end
		elseif search_type == "插件名" then
			if IDEUtility_HasTargetClass(control_info.info, key) then
				local item = self:CreateItem(control_info, "控件选择器")
				if item ~= nil then
					run_time.item_count = run_time.item_count + 1
					item_list[run_time.item_count] = item
				end
			end
		elseif search_type == "事件设置" then
			if IDEUtility_HasEventCallback(control_info.info, key) then
				local item = self:CreateItem(control_info, "控件选择器")
				if item ~= nil then
					run_time.item_count = run_time.item_count + 1
					item_list[run_time.item_count] = item
				end
			end
		end
		if run_time.cur_count >= run_time.total_count then
			return item_list, run_time
		end
	end
	return item_list, run_time
end

function IDEQuickManager.SearchCmp(a, b)
	local a_user_data = a._user_data
	local b_user_data = b._user_data
	return a_user_data.path < b_user_data.path
end

function IDEQuickManager:Search(search_type, name)
	self._scroll_list:RemoveAllChild()
	local item_list, run_time = self:SearchCollect(search_type, name)
	local title = "控件选择器"
	if run_time.cur_count >= run_time.total_count then
		title = title .. "(筛选出来的数量太多，只显示前" .. run_time.total_count .. "个)"
	end
	ALittle.List_Sort(item_list, IDEQuickManager.SearchCmp)
	self._project_quick_tab:SetChildText(self._first_tab, title)
	self:CreateItemAndAddToList(self._scroll_list, item_list)
end

function IDEQuickManager:HandleSearchClick(event)
	self:Search(self._search_type.text, self._search_input.text)
end

function IDEQuickManager:HandleItemClick(event)
end

function IDEQuickManager:HandleItemRButtonDown(event)
	if self._quick_right_menu == nil then
		self._quick_right_menu = g_Control:CreateControl("ide_quick_right_menu", self)
	end
	A_LayerManager:ShowFromRight(self._quick_right_menu)
	self._quick_right_menu.x = A_UISystem.mouse_x
	self._quick_right_menu.y = A_UISystem.mouse_y
	if self._quick_right_menu.x + self._quick_right_menu.width > A_UISystem.view_width then
		self._quick_right_menu.x = A_UISystem.view_width - self._quick_right_menu.width
	end
	if self._quick_right_menu.y + self._quick_right_menu.height > A_UISystem.view_height then
		self._quick_right_menu.y = A_UISystem.view_height - self._quick_right_menu.height
	end
	self._quick_right_menu._user_data = event.target
end

function IDEQuickManager:HandleQuickRightMenuCopyName(event)
	A_LayerManager:HideFromRight(self._quick_right_menu)
	local target = self._quick_right_menu._user_data
	self._quick_right_menu._user_data = nil
	local user_data = target._user_data
	ALittle.System_SetClipboardText(user_data.name)
end

function IDEQuickManager:HandleQuickRightMenuCopyExtends(event)
	A_LayerManager:HideFromRight(self._quick_right_menu)
	local target = self._quick_right_menu._user_data
	self._quick_right_menu._user_data = nil
	local user_data = target._user_data
	local display_info = {}
	display_info.__extends = user_data.name
	local info = {}
	info.index = 1
	info.info = display_info
	local copy_list = {}
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function IDEQuickManager:HandleQuickRightMenuDelete(event)
	A_LayerManager:HideFromRight(self._quick_right_menu)
	local target = self._quick_right_menu._user_data
	self._quick_right_menu._user_data = nil
	local user_data = target._user_data
	local control_name = user_data.name
	local flag_type = user_data.flag_type
	local cfg_quick_map = g_IDEProject.project.config:GetConfig("quick_map", {})
	local cfg_info_map = cfg_quick_map[flag_type]
	if cfg_info_map == nil then
		return
	end
	if cfg_info_map[control_name] == nil then
		return
	end
	cfg_info_map[control_name] = nil
	g_IDEProject.project.config:SetConfig("quick_map", cfg_quick_map)
	local quick_info = self._quick_map[flag_type]
	if quick_info.item_map ~= nil then
		local item = quick_info.item_map[control_name]
		if item ~= nil then
			quick_info.item_map[control_name] = nil
			self:RemoveFromList(quick_info.scroll_list, item)
		end
	end
end

function IDEQuickManager:HandleItemDragBegin(event)
	self._drag_image = ALittle.Image(g_Control)
	local user_data = event.target._user_data
	self._drag_image._user_data = user_data
	A_LayerManager:AddToTip(self._drag_image)
	self._drag_image.alpha = 0.5
	self._drag_image:SetTextureCut(user_data.path, 0, 0, true, Lua.Bind(self.HandleItemDragViewCallback, self))
	if self._quick_pre_dialog ~= nil then
		A_LayerManager:RemoveFromTip(self._quick_pre_dialog)
	end
end

function IDEQuickManager:HandleItemDragViewCallback(image, result)
	image.width = image.texture_width
	image.height = image.texture_height
	image.x = A_UISystem.mouse_x - image.width / 2
	image.y = A_UISystem.mouse_y - image.height / 2
end

function IDEQuickManager:HandleItemDrag(event)
	self._drag_image.x = self._drag_image.x + event.delta_x
	self._drag_image.y = self._drag_image.y + event.delta_y
end

function IDEQuickManager:HandleItemDragEnd(event)
	A_LayerManager:RemoveFromTip(self._drag_image)
	local abs_x = self._drag_image.x
	local abs_y = self._drag_image.y
	self._drag_image = nil
	local user_data = event.target._user_data
	local cur_tab_child = g_IDETabManager.cur_tab_child
	if cur_tab_child == nil then
		return
	end
	cur_tab_child:QuickDragAddControl(abs_x, abs_y, user_data.name)
end

function IDEQuickManager:HandleItemMoveIn(event)
	if self._quick_pre_dialog == nil then
		self._quick_pre_dialog = g_Control:CreateControl("ide_quick_pre_dialog", self)
	end
	A_LayerManager:AddToTip(self._quick_pre_dialog)
	local user_data = event.target._user_data
	self._pre_image:SetTextureCut(user_data.path, 0, 0, true, Lua.Bind(self.HandleItemPreViewCallback, self))
	self:UpdateImagePreDialogPos()
end

function IDEQuickManager:HandleItemPreViewCallback(image, result)
	local width = image.texture_width
	image.width = width
	if width < 100 then
		width = 100
	end
	if width > A_UISystem.view_width then
		width = A_UISystem.view_width
		image.width = width
	end
	self._quick_pre_dialog.width = width
	image.x = (width - image.width) / 2
	local height = image.texture_height
	image.height = height
	if height < 50 then
		height = 50
	end
	if height > A_UISystem.view_height - self._quick_pre_dialog.head_size then
		height = A_UISystem.view_height - self._quick_pre_dialog.head_size
		image.height = height
	end
	image.y = (height - image.height) / 2
	self._quick_pre_dialog.height = self._quick_pre_dialog.head_size + height
end

function IDEQuickManager:HandleItemMoveOut(event)
	A_LayerManager:RemoveFromTip(self._quick_pre_dialog)
end

function IDEQuickManager:HandleItemMouseMove(event)
	self:UpdateImagePreDialogPos()
end

function IDEQuickManager:UpdateImagePreDialogPos()
	if self._quick_pre_dialog == nil then
		return
	end
	local x = A_UISystem.mouse_x + 20
	if x + self._quick_pre_dialog.width > A_UISystem.view_width then
		x = A_UISystem.view_width - self._quick_pre_dialog.width
	end
	local y = A_UISystem.mouse_y + 20
	if y + self._quick_pre_dialog.height > A_UISystem.view_height then
		y = A_UISystem.view_height - self._quick_pre_dialog.height
	end
	self._quick_pre_dialog.x = x
	self._quick_pre_dialog.y = y
end

function IDEQuickManager:HandleOpenProject(event)
	self._base_path = g_IDEProject.project.base_path .. "IDETemp/QuickManager"
	local control_map = g_IDEProject.project.control_map
	local cfg_quick_map = g_IDEProject.project.config:GetConfig("quick_map", {})
	for flag_type, cfg_map in ___pairs(cfg_quick_map) do
		local quick_info = self._quick_map[flag_type]
		if quick_info ~= nil then
			local item_list = {}
			local item_list_count = 0
			quick_info.item_map = {}
			for k, cfg_info in ___pairs(cfg_map) do
				local control_info = control_map[cfg_info.name]
				if control_info ~= nil then
					local item = self:CreateItem(control_info, flag_type)
					if item ~= nil then
						item_list_count = item_list_count + 1
						item_list[item_list_count] = item
						quick_info.item_map[cfg_info.name] = item
					end
				end
			end
			self:CreateItemAndAddToList(quick_info.scroll_list, item_list)
		end
	end
end

function IDEQuickManager:HandleCloseProject(event)
	for k, quick_info in ___pairs(self._quick_map) do
		quick_info.scroll_list:RemoveAllChild()
		quick_info.item_map = {}
	end
	self._scroll_list:RemoveAllChild()
end

function IDEQuickManager:HandleDeleteControl(event)
	local control_name = event.name
	local abs_path = g_IDEProject.project.base_path .. "IDETemp/QuickManager/" .. control_name .. ".png"
	ALittle.File_DeleteFile(abs_path)
	local loading = self._loading[abs_path]
	self._loading[abs_path] = nil
	if loading ~= nil then
		A_LoopSystem:RemoveTimer(loading.loop)
		loading.loop = nil
	end
	local cfg_quick_map = g_IDEProject.project.config:GetConfig("quick_map", {})
	local has_changed = false
	for flag_type, cfg_info_map in ___pairs(cfg_quick_map) do
		if cfg_info_map[control_name] ~= nil then
			cfg_info_map[control_name] = nil
			has_changed = true
		end
	end
	if has_changed then
		g_IDEProject.project.config:SetConfig("quick_map", cfg_quick_map)
	end
	for flag_type, quick_info in ___pairs(self._quick_map) do
		if quick_info.item_map ~= nil then
			local item = quick_info.item_map[control_name]
			if item ~= nil then
				quick_info.item_map[control_name] = nil
				self:RemoveFromList(quick_info.scroll_list, item)
			end
		end
	end
end

function IDEQuickManager:HandleChangeControl(event)
end

function IDEQuickManager:FlagImage(control_name)
	self:FlagImpl("常用图片", control_name)
end

function IDEQuickManager:FlagButton(control_name)
	self:FlagImpl("常用按钮", control_name)
end

function IDEQuickManager:FlagText(control_name)
	self:FlagImpl("常用文本", control_name)
end

function IDEQuickManager:FlagOther(control_name)
	self:FlagImpl("其他常用", control_name)
end

function IDEQuickManager:FlagImpl(flag_type, control_name)
	local control_map = g_IDEProject.project.control_map
	local control_info = control_map[control_name]
	if control_info == nil then
		return
	end
	local quick_info = self._quick_map[flag_type]
	if quick_info == nil then
		return
	end
	local cfg_quick_map = g_IDEProject.project.config:GetConfig("quick_map", {})
	local cfg_info_map = cfg_quick_map[flag_type]
	if cfg_info_map == nil then
		cfg_info_map = {}
		cfg_quick_map[flag_type] = cfg_info_map
	end
	if cfg_info_map[control_name] ~= nil then
		return
	end
	local item = self:CreateItem(control_info, flag_type)
	if item == nil then
		return
	end
	self:AddToList(quick_info.scroll_list, item)
	if quick_info.item_map == nil then
		quick_info.item_map = {}
	end
	quick_info.item_map[control_name] = item
	local info = {}
	info.name = control_name
	info.time = ALittle.Time_GetCurTime()
	cfg_info_map[control_name] = info
	g_IDEProject.project.config:SetConfig("quick_map", cfg_quick_map)
end

g_IDEQuickManager = IDEQuickManager()
