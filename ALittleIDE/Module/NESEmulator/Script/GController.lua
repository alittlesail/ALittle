-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
NESEmulator.GController = Lua.Class(ALittle.DisplayLayout, "NESEmulator.GController")

function NESEmulator.GController:Ctor()
	___rawset(self, "_margin_rate", 0)
end

function NESEmulator.GController:TCtor()
end

function NESEmulator.GController:UpdateDir(target, rel_x, rel_y)
	local width = target.width
	local height = target.height
	local w_margin = width / 2 - width / 2 * self._margin_rate
	local h_margin = height / 2 - height / 2 * self._margin_rate
	local h_key_delta = 0
	local h_key = nil
	do
		if rel_x < w_margin then
			h_key = NESEmulator.NesControlType.BUTTON_LEFT
			h_key_delta = w_margin - rel_x
		elseif rel_x > width - w_margin then
			h_key = NESEmulator.NesControlType.BUTTON_RIGHT
			h_key_delta = rel_x - (width - w_margin)
		end
	end
	local v_key_delta = 0
	local v_key = nil
	do
		if rel_y < h_margin then
			v_key = NESEmulator.NesControlType.BUTTON_UP
			v_key_delta = h_margin - rel_y
		elseif rel_y > height - h_margin then
			v_key = NESEmulator.NesControlType.BUTTON_DOWN
			v_key_delta = rel_y - (height - h_margin)
		end
	end
	local new_key
	if h_key == nil and v_key ~= nil then
		new_key = v_key
	elseif h_key ~= nil and v_key == nil then
		new_key = h_key
	elseif h_key ~= nil and v_key ~= nil then
		if h_key_delta > v_key_delta then
			new_key = h_key
		else
			new_key = v_key
		end
	end
	if self._key_type == new_key then
		return
	end
	if self._key_type ~= nil then
		g_GNes:ButtonUp(1, self._key_type)
	end
	self._key_type = new_key
	if self._key_type ~= nil then
		g_GNes:ButtonDown(1, self._key_type)
	end
end

function NESEmulator.GController:StopDir()
	if self._key_type ~= nil then
		g_GNes:ButtonUp(1, self._key_type)
	end
	self._key_type = nil
end

function NESEmulator.GController:HandleLButtonDown(event)
	self:UpdateDir(event.target, event.rel_x, event.rel_y)
end

function NESEmulator.GController:HandleLButtonUp(event)
	self:StopDir()
end

function NESEmulator.GController:HandleDragBegin(event)
end

function NESEmulator.GController:HandleDrag(event)
	self:UpdateDir(event.target, event.rel_x, event.rel_y)
end

function NESEmulator.GController:HandleDragEnd(event)
	self:StopDir()
end

function NESEmulator.GController:HandleSelectDown(event)
	g_GNes:ButtonDown(1, NESEmulator.NesControlType.BUTTON_SELECT)
end

function NESEmulator.GController:HandleSelectUp(event)
	g_GNes:ButtonUp(1, NESEmulator.NesControlType.BUTTON_SELECT)
end

function NESEmulator.GController:HandleStartDown(event)
	g_GNes:ButtonDown(1, NESEmulator.NesControlType.BUTTON_START)
end

function NESEmulator.GController:HandleStartUp(event)
	g_GNes:ButtonUp(1, NESEmulator.NesControlType.BUTTON_START)
end

function NESEmulator.GController:HandleBDown(event)
	g_GNes:ButtonDown(1, NESEmulator.NesControlType.BUTTON_B)
end

function NESEmulator.GController:HandleBUp(event)
	g_GNes:ButtonUp(1, NESEmulator.NesControlType.BUTTON_B)
end

function NESEmulator.GController:HandleADown(event)
	g_GNes:ButtonDown(1, NESEmulator.NesControlType.BUTTON_A)
end

function NESEmulator.GController:HandleAUp(event)
	g_GNes:ButtonUp(1, NESEmulator.NesControlType.BUTTON_A)
end

end