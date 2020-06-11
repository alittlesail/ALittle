-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

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
ALittle.RegStruct(-970735483, "AUIPlugin.AUIRightMenuInfo", {
name = "AUIPlugin.AUIRightMenuInfo", ns_name = "AUIPlugin", rl_name = "AUIRightMenuInfo", hash_code = -970735483,
name_list = {"name","disabled","callback"},
type_list = {"string","bool","Functor<()>"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

AUIRightMenu = Lua.Class(nil, "AUIPlugin.AUIRightMenu")

function AUIRightMenu:Ctor()
	___rawset(self, "_info_list", {})
end

function AUIRightMenu:AddItem(name, callback, disabled)
	if name == nil then
		name = ""
	end
	if disabled == nil then
		disabled = false
	end
	local info = {}
	info.name = name
	info.callback = callback
	info.disabled = disabled
	ALittle.List_Push(self._info_list, info)
end

function AUIRightMenu:Show(target)
	if self._menu == nil then
		self._menu = g_Control:CreateControl("ide_common_menu", self)
		local max_width = 0.0
		for index, info in ___ipairs(self._info_list) do
			local item = g_Control:CreateControl("ide_common_item_button")
			item.text = info.name
			if item.show_text ~= nil and item.show_text.width > max_width then
				max_width = item.show_text.width
			end
			item.disabled = info.disabled
			item._user_data = info
			item:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
			self._linear:AddChild(item)
		end
		self._menu.width = max_width + 50
		self._menu.height = self._linear.height + 10
	end
	if target ~= nil then
		local x, y = target:LocalToGlobal()
		self._menu.x = x
		self._menu.y = y + target.height
	else
		self._menu.x = A_UISystem.mouse_x
		self._menu.y = A_UISystem.mouse_y
	end
	A_LayerManager:ShowFromRight(self._menu)
end

function AUIRightMenu:Hide()
	if self._menu ~= nil then
		A_LayerManager:HideFromRight(self._menu)
	end
end

function AUIRightMenu:HandleItemClick(event)
	self:Hide()
	local info = event.target._user_data
	if info.callback ~= nil then
		info.callback()
	end
end

