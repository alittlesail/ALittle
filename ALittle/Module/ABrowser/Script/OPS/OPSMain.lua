
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSMain = ALittle.Class(nil, "ABrowser.OPSMain")

function OPSMain:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSMain:HideScene()
	if self._scene ~= nil then
		self._scene.visible = false
	end
end

function OPSMain:ShowScene()
	if self._scene == nil then
		self._scene = g_Control:CreateControl("ops_main", self)
		self._center.main_layer:AddChild(self._scene)
		if self._center.config.base ~= nil then
			local icon_path = self._center.config.base.icon_path
			local icon = ALittle.Image(self._center.control)
			icon.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
			icon.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER
			icon.texture_name = self._center.config.base.icon_path
			icon.width = 72
			icon.height = 72
			self._icon_container:AddChild(icon)
		end
		local ops_name = self._center.config.base.ops_name
		if ops_name ~= nil then
			self._ops_name.text = ops_name
		end
		self._g3_init_up_size = self._g3.up_size
		self._tree_container.clip_atonce = false
		self:CreateModuleList()
		self._tree_container.clip_atonce = true
	else
		self._tab_container:RemoveAllChild()
		self._tree_container:RemoveAllChild()
		self._tree_container.clip_atonce = false
		self:CreateModuleList()
		self._tree_container.clip_atonce = true
	end
	self._scene.visible = true
end

function OPSMain:CreateModuleList()
	local menu = self._center.config.menu
	if menu == nil then
		return
	end
	local group_name = A_TextRadioButtonManager:CreateGroupName()
	for k, v in ___ipairs(menu) do
		self:CreateTreeMain(v, group_name)
	end
end

function OPSMain:CreateTreeMain(config, group_name)
	local childs = config.childs
	if childs == nil then
		return
	end
	local tree = g_Control:CreateControl("ops_tree")
	tree.text = config.name
	local has_child = false
	for k, info in ___ipairs(childs) do
		local table_config = self._center.config.table[info.table]
		if self._center.login_logic:CheckPermission(table_config.permission) then
			has_child = true
			local item = g_Control:CreateControl("ops_tree_body", self)
			item.drag_trans_target = self._tree_container
			tree:AddItem(item)
			item.text = info.name
			item.group_name = group_name
			local user_data = {}
			user_data.table_data_config = info
			user_data.tab = nil
			item._user_data = user_data
		end
	end
	if has_child then
		self._tree_container:AddChild(tree)
	end
end

function OPSMain:HandleTreeResize(event)
	self._tree_container:DeepLayout()
end

function OPSMain:HandleItemClick(event)
	local user_data = event.target._user_data
	if user_data.tab == nil then
		user_data.tab = OPSTableData(self._center, user_data.table_data_config)
	end
	self._tab = user_data.tab
	self._tab_container:AddChild(self._tab)
	self._tab_container:SetChildText(self._tab, user_data.table_data_config.name)
	self._tab_container.tab = self._tab
	self._tab._user_data = user_data
	self:ShowTab()
end

function OPSMain:ShowTab()
	local tab_index = self._tab_container.tab_index
	local view = self._tab_container.view
	local view_linear = self._tab_container.view_linear
	local child = view_linear:GetChildByIndex(tab_index)
	if child == nil then
		return
	end
	local right = view_linear.x + child.x + child.width
	if right > view.width then
		view_linear.x = view_linear.x - (right - view.width)
	end
	local left = view_linear.x + child.x
	if left < 0 then
		view_linear.x = view_linear.x - left
	end
end

function OPSMain:HandleTabHeadRightClick()
	if self._tab_anti ~= nil and self._tab_anti:IsCompleted() == false then
		self._tab_anti:SetCompleted()
		A_LoopSystem:RemoveUpdater(self._tab_anti)
		self._tab_anti = nil
	end
	local view = self._tab_container.view
	local view_linear = self._tab_container.view_linear
	if view_linear.x + view_linear.width < view.width then
		return
	end
	local x = view_linear.x - view.width
	if x + view_linear.width < view.width then
		x = view.width - view_linear.width
	end
	local delta = math.abs(view_linear.x - x) / 4
	self._tab_anti = ALittle.LoopLinear(view_linear, "x", x, math.floor(delta), 1)
	A_LoopSystem:AddUpdater(self._tab_anti)
end

function OPSMain:HandleTabHeadLeftClick()
	if self._tab_anti ~= nil and self._tab_anti:IsCompleted() == false then
		self._tab_anti:SetCompleted()
		A_LoopSystem:RemoveUpdater(self._tab_anti)
		self._tab_anti = nil
	end
	local view = self._tab_container.view
	local view_linear = self._tab_container.view_linear
	if view_linear.x >= 0 then
		return
	end
	local x = view_linear.x + view.width
	if x > 0 then
		x = 0
	end
	local delta = math.abs(view_linear.x - x) / 4
	self._tab_anti = ALittle.LoopLinear(view_linear, "x", x, math.floor(delta), 1)
	A_LoopSystem:AddUpdater(self._tab_anti)
end

function OPSMain:HandleCloseHandleClick(event)
	local object = event.target
	if self._tab_close_menu == nil then
		self._tab_close_menu = g_Control:CreateControl("ops_tab_menu", self)
	end
	local x, y = object:LocalToGlobal()
	y = y + object.height
	x = x + object.width
	x = x - self._tab_close_menu.width
	self._tab_close_menu.x = x
	self._tab_close_menu.y = y + 2
	A_LayerManager:ShowFromRight(self._tab_close_menu)
end

function OPSMain:HandleShowCurTabClick(event)
	A_LayerManager:HideFromRight(self._tab_close_menu)
	self:ShowTab()
end

function OPSMain:HandleTabCloseCallBack(child)
	local user_data = child._user_data
	local parent = user_data.parent
	if parent == nil then
		return
	end
	user_data = parent._user_data
	user_data.tab = nil
	parent.selected = false
end

function OPSMain:HandleCloseAllTab(event)
	A_LayerManager:HideFromRight(self._tab_close_menu)
	local childs = self._tab_container.childs
	for k, v in ___ipairs(childs) do
		self:HandleTabCloseCallBack(v)
	end
	self._tab_container:RemoveAllChild()
end

function OPSMain:HandleCloseOtherTab(event)
	A_LayerManager:HideFromRight(self._tab_close_menu)
	local tab_index = self._tab_container.tab_index
	local child = self._tab_container:GetChildByIndex(tab_index)
	if child == nil then
		return
	end
	local child_list = {}
	local child_list_count = 0
	for k, v in ___ipairs(self._tab_container.childs) do
		if v ~= child then
			child_list_count = child_list_count + 1
			child_list[child_list_count] = v
		end
	end
	for k, v in ___ipairs(child_list) do
		self:HandleTabCloseCallBack(v)
		self._tab_container:RemoveChild(v)
	end
end

function OPSMain:HandleLogout(event)
	self._center.login_logic:Logout()
end

function OPSMain:Clear()
	self:HideScene()
	self:HandleCloseAllTab(nil)
	self._tree_container:RemoveAllChild()
	self._tab_container:RemoveAllChild()
	self._center.login_logic:ShowScene()
end

function OPSMain:HandleDefaultDragBegin(event)
	self._drag_h_or_v = (math.abs(event.delta_x) > math.abs(event.delta_y))
end

function OPSMain:HandleDefaultDrag(event)
	if self._drag_h_or_v == false then
		return
	end
	self._g3.up_size = self._g3.up_size + event.delta_x
	if self._g3.up_size > self._g3_init_up_size then
		self._g3.up_size = self._g3_init_up_size
	end
	if self._g3.up_size < 0 then
		self._g3.up_size = 0
	end
end

function OPSMain:HandleDefaultDragEnd(event)
	if self._g3.up_size > self._g3_init_up_size / 2 then
		A_LoopSystem:AddUpdater(ALittle.LoopLinear(self._g3, "up_size", self._g3_init_up_size, 200, 1))
	else
		A_LoopSystem:AddUpdater(ALittle.LoopLinear(self._g3, "up_size", 0, 200, 1))
	end
	self._tree_container:Layout(1)
end

