
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(550649122, "ALittle.UITransTarget", {
name = "ALittle.UITransTarget", ns_name = "ALittle", rl_name = "UITransTarget", hash_code = 550649122,
name_list = {"event","drag"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(292776509, "ALittle.UIFocusOutEvent", {
name = "ALittle.UIFocusOutEvent", ns_name = "ALittle", rl_name = "UIFocusOutEvent", hash_code = 292776509,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-644464135, "ALittle.UIFocusInEvent", {
name = "ALittle.UIFocusInEvent", ns_name = "ALittle", rl_name = "UIFocusInEvent", hash_code = -644464135,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name = "ALittle.UIMoveOutEvent", ns_name = "ALittle", rl_name = "UIMoveOutEvent", hash_code = -1202439334,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(544684311, "ALittle.UIMoveInEvent", {
name = "ALittle.UIMoveInEvent", ns_name = "ALittle", rl_name = "UIMoveInEvent", hash_code = 544684311,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(1862557463, "ALittle.UIShowEvent", {
name = "ALittle.UIShowEvent", ns_name = "ALittle", rl_name = "UIShowEvent", hash_code = 1862557463,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(1309977874, "ALittle.UIChangedEndEvent", {
name = "ALittle.UIChangedEndEvent", ns_name = "ALittle", rl_name = "UIChangedEndEvent", hash_code = 1309977874,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name = "ALittle.UISelectChangedEvent", ns_name = "ALittle", rl_name = "UISelectChangedEvent", hash_code = 444989011,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(2024735182, "ALittle.UITabKeyEvent", {
name = "ALittle.UITabKeyEvent", ns_name = "ALittle", rl_name = "UITabKeyEvent", hash_code = 2024735182,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(776398171, "ALittle.UIEnterKeyEvent", {
name = "ALittle.UIEnterKeyEvent", ns_name = "ALittle", rl_name = "UIEnterKeyEvent", hash_code = 776398171,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(1816229739, "ALittle.UIAtKeyEvent", {
name = "ALittle.UIAtKeyEvent", ns_name = "ALittle", rl_name = "UIAtKeyEvent", hash_code = 1816229739,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(809518110, "ALittle.UIDragUpEvent", {
name = "ALittle.UIDragUpEvent", ns_name = "ALittle", rl_name = "UIDragUpEvent", hash_code = 809518110,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(1848466169, "ALittle.UIDragDownEvent", {
name = "ALittle.UIDragDownEvent", ns_name = "ALittle", rl_name = "UIDragDownEvent", hash_code = 1848466169,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-567702959, "ALittle.UIDragLeftEvent", {
name = "ALittle.UIDragLeftEvent", ns_name = "ALittle", rl_name = "UIDragLeftEvent", hash_code = -567702959,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-839083637, "ALittle.UIDragRightEvent", {
name = "ALittle.UIDragRightEvent", ns_name = "ALittle", rl_name = "UIDragRightEvent", hash_code = -839083637,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
RegStruct(-51419723, "ALittle.UIFingerDragEvent", {
name = "ALittle.UIFingerDragEvent", ns_name = "ALittle", rl_name = "UIFingerDragEvent", hash_code = -51419723,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double","string","bool"},
option_map = {}
})
RegStruct(1598008698, "ALittle.UIFingerDragBeginEvent", {
name = "ALittle.UIFingerDragBeginEvent", ns_name = "ALittle", rl_name = "UIFingerDragBeginEvent", hash_code = 1598008698,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double","string","bool"},
option_map = {}
})
RegStruct(-2050069067, "ALittle.UIFingerDragEndEvent", {
name = "ALittle.UIFingerDragEndEvent", ns_name = "ALittle", rl_name = "UIFingerDragEndEvent", hash_code = -2050069067,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double","string","bool"},
option_map = {}
})
RegStruct(1354499457, "ALittle.UIDropEvent", {
name = "ALittle.UIDropEvent", ns_name = "ALittle", rl_name = "UIDropEvent", hash_code = 1354499457,
name_list = {"target","drop_target"},
type_list = {"ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(-439548260, "ALittle.UILongButtonDownEvent", {
name = "ALittle.UILongButtonDownEvent", ns_name = "ALittle", rl_name = "UILongButtonDownEvent", hash_code = -439548260,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name = "ALittle.UILButtonDownEvent", ns_name = "ALittle", rl_name = "UILButtonDownEvent", hash_code = 1883782801,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(40651933, "ALittle.UILButtonUpEvent", {
name = "ALittle.UILButtonUpEvent", ns_name = "ALittle", rl_name = "UILButtonUpEvent", hash_code = 40651933,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(349963892, "ALittle.UIMButtonDownEvent", {
name = "ALittle.UIMButtonDownEvent", ns_name = "ALittle", rl_name = "UIMButtonDownEvent", hash_code = 349963892,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(683647260, "ALittle.UIMButtonUpEvent", {
name = "ALittle.UIMButtonUpEvent", ns_name = "ALittle", rl_name = "UIMButtonUpEvent", hash_code = 683647260,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(-569321214, "ALittle.UIRButtonUpEvent", {
name = "ALittle.UIRButtonUpEvent", ns_name = "ALittle", rl_name = "UIRButtonUpEvent", hash_code = -569321214,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
RegStruct(-1737121315, "ALittle.UIMButtonWheelEvent", {
name = "ALittle.UIMButtonWheelEvent", ns_name = "ALittle", rl_name = "UIMButtonWheelEvent", hash_code = -1737121315,
name_list = {"target","delta_x","delta_y"},
type_list = {"ALittle.DisplayObject","double","double"},
option_map = {}
})
RegStruct(-525850898, "ALittle.UIFingerEvent", {
name = "ALittle.UIFingerEvent", ns_name = "ALittle", rl_name = "UIFingerEvent", hash_code = -525850898,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","string","bool","bool"},
option_map = {}
})
RegStruct(-1233353463, "ALittle.UIFingerDownEvent", {
name = "ALittle.UIFingerDownEvent", ns_name = "ALittle", rl_name = "UIFingerDownEvent", hash_code = -1233353463,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","string","bool","bool"},
option_map = {}
})
RegStruct(734860930, "ALittle.UIFingerUpEvent", {
name = "ALittle.UIFingerUpEvent", ns_name = "ALittle", rl_name = "UIFingerUpEvent", hash_code = 734860930,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","string","bool","bool"},
option_map = {}
})
RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
RegStruct(-1330840, "ALittle.UIMClickEvent", {
name = "ALittle.UIMClickEvent", ns_name = "ALittle", rl_name = "UIMClickEvent", hash_code = -1330840,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
RegStruct(286797479, "ALittle.UIFClickEvent", {
name = "ALittle.UIFClickEvent", ns_name = "ALittle", rl_name = "UIFClickEvent", hash_code = 286797479,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
RegStruct(-1234078962, "ALittle.UITextInputEvent", {
name = "ALittle.UITextInputEvent", ns_name = "ALittle", rl_name = "UITextInputEvent", hash_code = -1234078962,
name_list = {"target","text","custom"},
type_list = {"ALittle.DisplayObject","string","bool"},
option_map = {}
})
RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name = "ALittle.UIKeyDownEvent", ns_name = "ALittle", rl_name = "UIKeyDownEvent", hash_code = -1604617962,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
RegStruct(1213009422, "ALittle.UIKeyUpEvent", {
name = "ALittle.UIKeyUpEvent", ns_name = "ALittle", rl_name = "UIKeyUpEvent", hash_code = 1213009422,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name = "ALittle.UIMouseMoveEvent", ns_name = "ALittle", rl_name = "UIMouseMoveEvent", hash_code = -1001723540,
name_list = {"target","abs_x","abs_y","rel_x","rel_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double"},
option_map = {}
})
RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name = "ALittle.UIDropFileEvent", ns_name = "ALittle", rl_name = "UIDropFileEvent", hash_code = -338112738,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
RegStruct(124598654, "ALittle.UISystemSelectFileEvent", {
name = "ALittle.UISystemSelectFileEvent", ns_name = "ALittle", rl_name = "UISystemSelectFileEvent", hash_code = 124598654,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
RegStruct(-1676610185, "ALittle.UISystemSaveFileEvent", {
name = "ALittle.UISystemSaveFileEvent", ns_name = "ALittle", rl_name = "UISystemSaveFileEvent", hash_code = -1676610185,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

UIEventListener = Lua.Class(nil, "ALittle.UIEventListener")

function UIEventListener:Ctor()
end

function UIEventListener:RemoveFromDispatcher()
	if self._event_map ~= nil then
		for d, v in ___pairs(self._event_map) do
			d._trans_target.event = nil
		end
		self._event_map = nil
	end
	if self._drag_map ~= nil then
		for d, v in ___pairs(self._drag_map) do
			d._trans_target.drag = nil
		end
		self._drag_map = nil
	end
	if self._ref_map ~= nil then
		for d, t in ___pairs(self._ref_map) do
			for name, vb in ___pairs(t) do
				local callback_table = d._listeners[name]
				if callback_table ~= nil then
					callback_table[self] = nil
				end
			end
		end
		self._ref_map = nil
	end
end

assert(ALittle.UIEventListener, " extends class:ALittle.UIEventListener is nil")
UIEventDispatcher = Lua.Class(ALittle.UIEventListener, "ALittle.UIEventDispatcher")

function UIEventDispatcher:Ctor()
	___rawset(self, "_trans_target", {})
	___rawset(self, "_listeners", {})
	___rawset(self, "_abs_disabled", false)
end

function UIEventDispatcher.__getter:event_trans_target()
	return self._trans_target.event
end

function UIEventDispatcher.__setter:event_trans_target(value)
	local old_value = self._trans_target.event
	if old_value == value then
		return
	end
	if old_value ~= nil and old_value._event_map ~= nil then
		old_value._event_map[self] = nil
	end
	self._trans_target.event = value
	if value ~= nil then
		if value._event_map == nil then
			value._event_map = {}
		end
		value._event_map[self] = true
	end
end

function UIEventDispatcher.__getter:drag_trans_target()
	return self._trans_target.drag
end

function UIEventDispatcher.__setter:drag_trans_target(value)
	local old_value = self._trans_target.drag
	if old_value == value then
		return
	end
	if old_value ~= nil and old_value._drag_map ~= nil then
		old_value._drag_map[self] = nil
	end
	self._trans_target.drag = value
	if value ~= nil then
		if value._drag_map == nil then
			value._drag_map = {}
		end
		value._drag_map[self] = true
	end
end

function UIEventDispatcher.__getter:abs_disabled()
	return self._abs_disabled
end

function UIEventDispatcher.__setter:abs_disabled(value)
	self._abs_disabled = value
end

function UIEventDispatcher:AddEventListener(T, object, callback)
	local rflt = T
	return self:AddEventListenerImpl(rflt.name, object, callback)
end

function UIEventDispatcher:AddEventListenerImpl(event_type, object, callback)
	if object == nil then
		return false
	end
	if callback == nil then
		return false
	end
	local callback_table = self._listeners[event_type]
	if callback_table == nil then
		callback_table = {}
		self._listeners[event_type] = callback_table
	end
	local callback_value = callback_table[object]
	if callback_value == nil then
		callback_value = {}
		callback_table[object] = callback_value
	end
	callback_value[callback] = true
	local ref_map = object._ref_map
	if ref_map == nil then
		ref_map = {}
		object._ref_map = ref_map
	end
	local ref_value = ref_map[self]
	if ref_value == nil then
		ref_value = {}
		ref_map[self] = ref_value
	end
	ref_value[event_type] = true
	return true
end

function UIEventDispatcher:RemoveEventListener(T, object, callback)
	local rflt = T
	local callback_table = self._listeners[rflt.name]
	if callback_table == nil then
		return
	end
	if object == nil then
		self._listeners[rflt.name] = {}
		return
	end
	if callback == nil then
		object._ref_map[self] = nil
		callback_table[object] = nil
	else
		local callback_value = callback_table[object]
		if callback_value == nil then
			return
		end
		callback_value[callback] = nil
		object._ref_map[self][rflt.name] = nil
	end
end

function UIEventDispatcher:ClearEventListener()
	for name, callback_table in ___pairs(self._listeners) do
		for listener, callback_value in ___pairs(callback_table) do
			listener._ref_map[self] = nil
		end
	end
	self._listeners = {}
end

function UIEventDispatcher:DispatchEvent(T, event)
	local rflt = T
	if event.target == nil then
		event.target = self
	end
	local event_target = self
	if self._trans_target.event ~= nil then
		event_target = self._trans_target.event
	elseif self._trans_target.drag ~= nil then
		if rflt.name == "ALittle.UIButtonDragEvent" or rflt.name == "ALittle.UIButtonDragBeginEvent" then
			event_target = self._trans_target.drag
		elseif rflt.name == "ALittle.UIButtonDragEndEvent" then
			A_UISystem.focus = self._trans_target.drag
		end
	end
	if event_target._abs_disabled then
		return
	end
	local callback_table = event_target._listeners[rflt.name]
	if callback_table == nil then
		return
	end
	for object, callback_value in ___pairs(callback_table) do
		for func, _ in ___pairs(callback_value) do
			func(object, event)
		end
	end
end
