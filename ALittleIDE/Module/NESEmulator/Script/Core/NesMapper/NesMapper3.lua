-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper3 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper3")

function NESEmulator.NesMapper3:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	else
		local bank = ALittle.Math_Floor((value % (self._nes._rom._vrom_count / 2)) * 2)
		self:LoadVromBank(bank, 0x0000)
		self:LoadVromBank(bank + 1, 0x1000)
		self:Load8kVromBank(value * 2, 0x0000)
	end
end

end