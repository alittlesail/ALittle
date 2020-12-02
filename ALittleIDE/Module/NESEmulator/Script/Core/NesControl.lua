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

NESEmulator.NesControl = Lua.Class(nil, "NESEmulator.NesControl")

function NESEmulator.NesControl:Ctor()
	___rawset(self, "_state", {})
end

function NESEmulator.NesControl:ButtonDown(key)
	self._state[key] = 0x41
end

function NESEmulator.NesControl:ButtonUp(key)
	self._state[key] = 0x40
end

end