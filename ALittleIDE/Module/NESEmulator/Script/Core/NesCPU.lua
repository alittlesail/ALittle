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

end