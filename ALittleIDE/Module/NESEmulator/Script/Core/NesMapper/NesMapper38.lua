-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper38 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper38")

function NESEmulator.NesMapper38:Write(address, value)
	if address < 0x7000 or address > 0x7fff then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	else
		self:Load32kRomBank(value & 3, 0x8000)
		self:Load8kVromBank(((value >> 2) & 3) * 2, 0x0000)
	end
end

end