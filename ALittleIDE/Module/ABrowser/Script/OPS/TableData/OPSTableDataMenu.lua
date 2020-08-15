
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSTableDataMenuType = {
	SHOW_RIGHT = "OPS_OPSTableDataMenu_SHOW_RIGHT",
	SHOW_BOTTOM = "OPS_OPSTableDataMenu_SHOW_BOTTOM",
}

OPSTableDataMenu = ALittle.Class(nil, "OPSTableDataMenu")

function OPSTableDataMenu:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSTableDataMenu:Show(target)
	if self._right_linear == nil then
		self._right_linear = ALittle.Linear(g_Control)
		self._right_linear.type = ALittle.UIEnumTypes.TYPE_V
		self._right_linear.width = 100
	end
	self._right_linear:RemoveAllChild()
	local user_data = target._user_data
	local handle_config_list = user_data.single_handle_config_list
	if handle_config_list == nil then
		handle_config_list = user_data.multy_handle_config_list
	end
	if handle_config_list == nil then
		return
	end
	for index, handle_config in ___ipairs(handle_config_list) do
		local button = g_Control:CreateControl("ops_common_button")
		button:AddEventListener(ALittle.UIEventTypes.CLICK, self, self.HandleChildClick)
		button.text = handle_config.name
		self._right_linear:AddChild(button)
		local btn_user_data = {}
		button._user_data = btn_user_data
		btn_user_data.dialog_config = handle_config
		btn_user_data.data = user_data.data
		btn_user_data.table_data = user_data.table_data
		btn_user_data.batch = user_data.batch
	end
	local x, y = target:LocalToGlobal()
	if x < 0 then
		x = 0
	elseif x > A_UISystem.view_width then
		x = A_UISystem.view_width - target.width
	end
	if y < 0 then
		y = 0
	elseif y + self._right_linear.height > A_UISystem.view_height then
		y = A_UISystem.view_height - self._right_linear.height
	end
	if user_data.position == OPSTableDataMenuType.SHOW_BOTTOM then
		self._right_linear.x = x
		self._right_linear.y = y + target.height
	elseif user_data.position == OPSTableDataMenuType.SHOW_RIGHT then
		self._right_linear.x = x + target.width
		self._right_linear.y = y
	end
	A_LayerManager:ShowFromRight(self._right_linear)
end

function OPSTableDataMenu:HandleChildClick(event)
	A_LayerManager:HideFromRight(self._right_linear)
	self._center.dialog_logic:Show(event.target)
end

