-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesCPUIRQ = {
	IRQ_NORMAL = 0,
	IRQ_NMI = 1,
	IRQ_RESET = 2,
}

NESEmulator.NesCPU = Lua.Class(nil, "NESEmulator.NesCPU")

function NESEmulator.NesCPU:Ctor(nes)
	___rawset(self, "_nes", nes)
end

function NESEmulator.NesCPU:Reset()
	self._mem = {}
	local i = 0
	while true do
		if not(i < 0x10000) then break end
		self._mem[i] = 0
		i = i+(1)
	end
	local i = 1
	while true do
		if not(i < 0x2000) then break end
		self._mem[i] = 0xff
		i = i+(1)
	end
end

end