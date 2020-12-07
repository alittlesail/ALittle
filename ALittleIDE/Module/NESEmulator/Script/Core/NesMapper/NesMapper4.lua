-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper4 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper4")

function NESEmulator.NesMapper4:Ctor(nes)
	___rawset(self, "CMD_SEL_2_1K_VROM_0000", 0)
	___rawset(self, "CMD_SEL_2_1K_VROM_0800", 1)
	___rawset(self, "CMD_SEL_1K_VROM_1000", 2)
	___rawset(self, "CMD_SEL_1K_VROM_1400", 3)
	___rawset(self, "CMD_SEL_1K_VROM_1800", 4)
	___rawset(self, "CMD_SEL_1K_VROM_1C00", 5)
	___rawset(self, "CMD_SEL_ROM_PAGE1", 6)
	___rawset(self, "CMD_SEL_ROM_PAGE2", 7)
	___rawset(self, "_command", nil)
	___rawset(self, "_prg_address_select", nil)
	___rawset(self, "_chr_address_select", nil)
	___rawset(self, "_page_number", nil)
	___rawset(self, "_irq_counter", nil)
	___rawset(self, "_irq_latch_value", nil)
	___rawset(self, "_irq_enable", nil)
	___rawset(self, "_prg_address_changed", false)
end

function NESEmulator.NesMapper4:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	end
	if address == 0x8000 then
		self._command = value & 7
		local tmp = (value >> 6) & 1
		if tmp ~= self._prg_address_select then
			self._prg_address_changed = true
		end
		self._prg_address_select = tmp
		self._chr_address_select = (value >> 7) & 1
	elseif address == 0x8001 then
		self:ExecuteCommand(self._command, value)
	elseif address == 0xa000 then
		if (value & 1) ~= 0 then
			self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING)
		else
			self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.VERTICAL_MIRRORING)
		end
	elseif address == 0xa001 then
	elseif address == 0xc000 then
		self._irq_counter = value
	elseif address == 0xc001 then
		self._irq_latch_value = value
	elseif address == 0xe000 then
		self._irq_enable = 0
	elseif address == 0xe001 then
		self._irq_enable = 1
	else
	end
end

function NESEmulator.NesMapper4:ExecuteCommand(cmd, arg)
	if cmd == self.CMD_SEL_2_1K_VROM_0000 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x0000)
			self:Load1kVromBank(arg + 1, 0x0400)
		else
			self:Load1kVromBank(arg, 0x1000)
			self:Load1kVromBank(arg + 1, 0x1400)
		end
	elseif cmd == self.CMD_SEL_2_1K_VROM_0800 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x0800)
			self:Load1kVromBank(arg + 1, 0x0c00)
		else
			self:Load1kVromBank(arg, 0x1800)
			self:Load1kVromBank(arg + 1, 0x1c00)
		end
	elseif cmd == self.CMD_SEL_1K_VROM_1000 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x1000)
		else
			self:Load1kVromBank(arg, 0x0000)
		end
	elseif cmd == self.CMD_SEL_1K_VROM_1400 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x1400)
		else
			self:Load1kVromBank(arg, 0x0400)
		end
	elseif cmd == self.CMD_SEL_1K_VROM_1800 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x1800)
		else
			self:Load1kVromBank(arg, 0x0800)
		end
	elseif cmd == self.CMD_SEL_1K_VROM_1C00 then
		if self._chr_address_select == 0 then
			self:Load1kVromBank(arg, 0x1c00)
		else
			self:Load1kVromBank(arg, 0x0c00)
		end
	elseif cmd == self.CMD_SEL_ROM_PAGE1 then
		if self._prg_address_changed then
			if self._prg_address_select == 0 then
				self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2, 0xc000)
			else
				self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2, 0x8000)
			end
			self._prg_address_changed = false
		end
		if self._prg_address_select == 0 then
			self:Load8kRomBank(arg, 0x8000)
		else
			self:Load8kRomBank(arg, 0xc000)
		end
	elseif cmd == self.CMD_SEL_ROM_PAGE2 then
		self:Load8kRomBank(arg, 0xa000)
		if self._prg_address_changed then
			if self._prg_address_select == 0 then
				self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2, 0xc000)
			else
				self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2, 0x8000)
			end
			self._prg_address_changed = false
		end
	end
end

function NESEmulator.NesMapper4:LoadROM()
	if not self._nes._rom._valid then
		return "MMC3: Invalid ROM! Unable to load."
	end
	self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2, 0xc000)
	self:Load8kRomBank((self._nes._rom._rom_count - 1) * 2 + 1, 0xe000)
	self:Load8kRomBank(0, 0x8000)
	self:Load8kRomBank(1, 0xa000)
	self:LoadCHRROM()
	self:LoadBatteryRam()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

function NESEmulator.NesMapper4:ClockIrqCounter()
	if self._irq_enable == 1 then
		self._irq_counter = self._irq_counter - 1
		if self._irq_counter < 0 then
			self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL)
			self._irq_counter = self._irq_latch_value
		end
	end
end

end