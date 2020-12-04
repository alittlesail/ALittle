-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesControlType = {
	BUTTON_A = 0,
	BUTTON_B = 1,
	BUTTON_SELECT = 2,
	BUTTON_START = 3,
	BUTTON_UP = 4,
	BUTTON_DOWN = 5,
	BUTTON_LEFT = 6,
	BUTTON_RIGHT = 7,
}

NESEmulator.NesController = Lua.Class(nil, "NESEmulator.NesController")

function NESEmulator.NesController:Ctor()
	___rawset(self, "_state", {})
	local i = 0
	while true do
		if not(i < 8) then break end
		self._state[i] = 0x40
		i = i+(1)
	end
end

function NESEmulator.NesController:ButtonDown(key)
	self._state[key] = 0x41
end

function NESEmulator.NesController:ButtonUp(key)
	self._state[key] = 0x40
end

end