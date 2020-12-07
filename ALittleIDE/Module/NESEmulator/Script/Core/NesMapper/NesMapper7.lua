-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper7 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper7")

function NESEmulator.NesMapper7:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
	else
		self:Load32kRomBank(value & 0x7, 0x8000)
		if value & 0x10 ~= 0 then
			self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING2)
		else
			self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING)
		end
	end
end

function NESEmulator.NesMapper7:LoadROM()
	if not self._nes._rom._valid then
		return "AOROM: Invalid ROM! Unable to load."
	end
	self:LoadPRGROM()
	self:LoadCHRROM()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

end