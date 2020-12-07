-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper180 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper180")

function NESEmulator.NesMapper180:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	else
		self:LoadRomBank(value, 0xc000)
	end
end

function NESEmulator.NesMapper180:LoadROM()
	if not self._nes._rom._valid then
		return "Mapper 180: Invalid ROM! Unable to load."
	end
	self:LoadRomBank(0, 0x8000)
	self:LoadRomBank(self._nes._rom._rom_count - 1, 0xc000)
	self:LoadCHRROM()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

end