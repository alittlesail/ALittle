-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper11 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper11")

function NESEmulator.NesMapper11:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	else
		local prgbank1 = ((value & 0xf) * 2) % self._nes._rom._rom_count
		local prgbank2 = ((value & 0xf) * 2 + 1) % self._nes._rom._rom_count
		self:LoadRomBank(prgbank1, 0x8000)
		self:LoadRomBank(prgbank2, 0xc000)
		if self._nes._rom._vrom_count > 0 then
			local bank = ((value >> 4) * 2) % self._nes._rom._vrom_count
			self:LoadVromBank(bank, 0x0000)
			self:LoadVromBank(bank + 1, 0x1000)
		end
	end
end

end