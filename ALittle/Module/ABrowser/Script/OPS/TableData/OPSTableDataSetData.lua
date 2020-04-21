
module("ABrowser", package.seeall)

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
ALittle.RegStruct(-1554228019, "ABrowser.OPSTableDataSetDataOperateClickEvent", {
name = "ABrowser.OPSTableDataSetDataOperateClickEvent", ns_name = "ABrowser", rl_name = "OPSTableDataSetDataOperateClickEvent", hash_code = -1554228019,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1600012379, "ABrowser.OPSTableDataSetDataDataClickEvent", {
name = "ABrowser.OPSTableDataSetDataDataClickEvent", ns_name = "ABrowser", rl_name = "OPSTableDataSetDataDataClickEvent", hash_code = -1600012379,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(229010313, "ABrowser.OPSTableDataSetDataAllSelect", {
name = "ABrowser.OPSTableDataSetDataAllSelect", ns_name = "ABrowser", rl_name = "OPSTableDataSetDataAllSelect", hash_code = 229010313,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-377909197, "ABrowser.OPSTableDataSetDataNoAllSelect", {
name = "ABrowser.OPSTableDataSetDataNoAllSelect", ns_name = "ABrowser", rl_name = "OPSTableDataSetDataNoAllSelect", hash_code = -377909197,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1670240088, "ABrowser.OPSTableDataCheckButtonData", {
name = "ABrowser.OPSTableDataCheckButtonData", ns_name = "ABrowser", rl_name = "OPSTableDataCheckButtonData", hash_code = 1670240088,
name_list = {"data","index"},
type_list = {"Map<string,any>","int"},
option_map = {}
})
ALittle.RegStruct(415207888, "ABrowser.OPSTableDataSetDataInfo", {
name = "ABrowser.OPSTableDataSetDataInfo", ns_name = "ABrowser", rl_name = "OPSTableDataSetDataInfo", hash_code = 415207888,
name_list = {"tr_height","offset_y","handle_width","field_offset","tr_width"},
type_list = {"double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1027595218, "ABrowser.OPSTableDataChooseInfo", {
name = "ABrowser.OPSTableDataChooseInfo", ns_name = "ABrowser", rl_name = "OPSTableDataChooseInfo", hash_code = 1027595218,
name_list = {"count","list"},
type_list = {"int","List<Map<string,any>>"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
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
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
OPSTableDataSetData = Lua.Class(ALittle.DisplayObject, "ABrowser.OPSTableDataSetData")

function OPSTableDataSetData:Ctor(ctrl_sys, center, table_data_config, parent, set_param)
	___rawset(self, "_center", center)
	___rawset(self, "_table_data_config", table_data_config)
	___rawset(self, "_parent", parent)
	___rawset(self, "_set_param", set_param)
	___rawset(self, "_check_btn_map", {})
	___rawset(self, "_static_object_v", ALittle.DisplayLayout(g_Control))
end

function OPSTableDataSetData.__getter:static_object_v()
	return self._static_object_v
end

function OPSTableDataSetData:SetStaticObjectList(data_list)
	local tr_height = self._set_param.tr_height
	local offset_y = self._set_param.offset_y
	local handle_width = self._set_param.handle_width
	for k, data in ___ipairs(data_list) do
		local single_handle = self._table_data_config.single_handle
		local check_button = g_Control:CreateControl("ops_common_check")
		check_button.y = (tr_height - check_button.height) / 2 + offset_y + 2
		check_button.x = 2
		check_button:AddEventListener(___all_struct[958494922], self, self.HandleCheckBtnChange)
		self._static_object_v:AddChild(check_button)
		local map = {}
		map.data = data
		map.index = k
		self._check_btn_map[check_button] = map
		if single_handle ~= nil then
			local handle_menu = {}
			local handle_menu_count = 0
			for k, v in ___ipairs(single_handle) do
				local dialog = self._center.config.dialog[v.dialog]
				if dialog ~= nil then
					local result = self._center.login_logic:CheckPermission(dialog.permission)
					if result then
						handle_menu_count = handle_menu_count + 1
						handle_menu[handle_menu_count] = v
					end
				end
			end
			local handle_button = g_Control:CreateControl("ops_common_button")
			handle_button.height = 20
			handle_button.width = 80
			handle_button.x = (handle_width - handle_button.width) / 2 + check_button.x * 2 + check_button.width
			handle_button.y = (tr_height - handle_button.height) / 2 + offset_y
			handle_button.text = "操作"
			handle_button.hand_cursor = true
			handle_button:AddEventListener(___all_struct[-449066808], self, self.ShowOperateMenu)
			self._static_object_v:AddChild(handle_button)
			local user_data = {}
			user_data.single_handle_config_list = handle_menu
			user_data.data = data
			user_data.table_data = self._parent
			user_data.batch = false
			user_data.position = OPSTableDataMenuType.SHOW_RIGHT
			handle_button._user_data = user_data
		end
		if self._parent.select_mode then
			local select_button = g_Control:CreateControl("ops_common_button")
			select_button.height = 20
			select_button.width = 80
			select_button.x = (handle_width - select_button.width) / 2 + check_button.x * 2 + check_button.width
			select_button.y = (tr_height - select_button.height) / 2 + offset_y
			select_button.text = "选择"
			select_button:AddEventListener(___all_struct[-449066808], self, self.HandleClick)
			select_button._user_data = data
			self._static_object_v:AddChild(select_button)
		end
		offset_y = offset_y + tr_height
	end
	self._static_object_v.height = offset_y
end

function OPSTableDataSetData:ShowOperateMenu(event)
	self._parent:ShowOperateMenu(event.target)
end

function OPSTableDataSetData:SelectAll()
	for check_btn, v in ___pairs(self._check_btn_map) do
		check_btn.selected = true
	end
end

function OPSTableDataSetData:CancelSelectAll()
	for check_btn, v in ___pairs(self._check_btn_map) do
		check_btn.selected = false
	end
end

function OPSTableDataSetData:HandleCheckBtnChange(event)
	local object = event.target
	local selected = object.selected
	self._parent.choose_text = tostring(self:GetChooseResult().count)
	for check_btn, v in ___pairs(self._check_btn_map) do
		if check_btn.selected == false then
			self._parent.select_all = false
			return
		end
	end
	self._parent.select_all = true
end

function OPSTableDataSetData:GetChooseResult()
	local info_map = {}
	info_map.count = 0
	info_map.list = {}
	for check_btn, v in ___pairs(self._check_btn_map) do
		if check_btn.selected then
			info_map.count = info_map.count + 1
			info_map.list[info_map.count] = v.data
		end
	end
	return info_map
end

function OPSTableDataSetData:GetChooseTDIndex()
	local index_list = {}
	local index_list_count = 0
	for check_btn, v in ___pairs(self._check_btn_map) do
		if check_btn.selected then
			index_list_count = index_list_count + 1
			index_list[index_list_count] = v.index
		end
	end
	return index_list
end

function OPSTableDataSetData:SetConcreteList(data_list, container)
	local gray = true
	local offset_y = self._set_param.offset_y
	local field_offset = self._set_param.field_offset
	local tr_width = self._set_param.tr_width
	local tr_height = self._set_param.tr_height
	for k, data in ___ipairs(data_list) do
		local offset_x = field_offset
		local quad = ALittle.Quad(g_Control)
		quad.width = tr_width + field_offset
		quad.height = tr_height
		quad.y = offset_y
		if gray then
			quad.red = 0.90
			quad.green = 0.90
			quad.blue = 0.90
		end
		container:AddChild(quad)
		gray = not gray
		local quad_bkg = g_Control:CreateControl("abrowser_common_line_background")
		quad_bkg.disabled = true
		quad_bkg.visible = false
		quad_bkg.width = tr_width + field_offset
		quad_bkg.height = tr_height
		quad_bkg.y = offset_y
		container:AddChild(quad_bkg)
		local table_td = self._center.config.table[self._table_data_config.table].table_td
		for index, field_config in ___ipairs(table_td) do
			if field_config.hidden ~= true then
				local control = OPSTDStringOutput(g_Control, self._center, field_config, data)
				control:AddEventListener(___all_struct[-641444818], self, self.HandleFieldRightClick)
				control:AddEventListener(___all_struct[-1202439334], self, self.HandleMouseMoveIn)
				control:AddEventListener(___all_struct[544684311], self, self.HandleMouseMoveOut)
				container:AddChild(control)
				control.x = offset_x
				control.y = offset_y
				control.drag_trans_target = container
				control.height = tr_height
				control._user_data = quad_bkg
				offset_x = offset_x + field_config.width
			end
		end
		offset_y = offset_y + tr_height
	end
end

function OPSTableDataSetData:HandleFieldRightClick(event)
	local object = event.target
	self._center.tool_logic:ShowCopyCutPasteMenu(object:GetCopyString(), nil)
end

function OPSTableDataSetData:HandleMouseMoveIn(event)
	local quad_bkg = event.target._user_data
	quad_bkg.visible = true
end

function OPSTableDataSetData:HandleMouseMoveOut(event)
	local quad_bkg = event.target._user_data
	quad_bkg.visible = false
end

function OPSTableDataSetData:HandleClick(event)
	local e = {}
	e.target = event.target
	self:DispatchEvent(___all_struct[-1600012379], e)
end

