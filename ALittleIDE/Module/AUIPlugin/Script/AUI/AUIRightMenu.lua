-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
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
name_list = {"name","disabled","auto_hide","callback"},
type_list = {"string","bool","bool","Functor<()>"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

AUIPlugin.AUIRightMenu = Lua.Class(nil, "AUIPlugin.AUIRightMenu")

function AUIPlugin.AUIRightMenu:Ctor()
	___rawset(self, "_info_list", {})
end

function AUIPlugin.AUIRightMenu:AddItem(name, callback, disabled, auto_hide)
	if name == nil then
		name = ""
	end
	if disabled == nil then
		disabled = false
	end
	if auto_hide == nil then
		auto_hide = true
	end
	local info = {}
	info.name = name
	info.callback = callback
	info.disabled = disabled
	info.auto_hide = auto_hide
	ALittle.List_Push(self._info_list, info)
end

function AUIPlugin.AUIRightMenu:Show(target, hide_callback)
	if self._menu == nil then
		self._menu = AUIPlugin.g_Control:CreateControl("aui_menu", self)
		local max_width = 0.0
		for index, info in ___ipairs(self._info_list) do
			local item = AUIPlugin.g_Control:CreateControl("aui_menu_item_button")
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
		self._menu:AddEventListener(___all_struct[348388800], self, self.HandleHideEvent)
	end
	if target ~= nil then
		local x, y = target:LocalToGlobal()
		self._menu.x = x - 5
		self._menu.y = y + target.height
	else
		self._menu.x = A_UISystem.mouse_x
		self._menu.y = A_UISystem.mouse_y
	end
	if self._menu.x + self._menu.width > A_UISystem.view_width then
		self._menu.x = A_UISystem.view_width - self._menu.width
	end
	if self._menu.y + self._menu.height > A_UISystem.view_height then
		self._menu.y = A_UISystem.view_height - self._menu.height
	end
	self._hide_callback = hide_callback
	A_LayerManager:ShowFromRight(self._menu)
end

function AUIPlugin.AUIRightMenu:Hide()
	if self._menu ~= nil then
		A_LayerManager:HideFromRight(self._menu)
	end
end

function AUIPlugin.AUIRightMenu:HandleHideEvent(event)
	if self._hide_callback ~= nil then
		local callback = self._hide_callback
		self._hide_callback = nil
		callback()
	end
end

function AUIPlugin.AUIRightMenu:HandleItemClick(event)
	local info = event.target._user_data
	if info.auto_hide then
		self:Hide()
	end
	if info.callback ~= nil then
		info.callback()
	end
end

end