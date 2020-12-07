-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper5 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper5")

function NESEmulator.NesMapper5:Ctor()
	___rawset(self, "_nametable_type", {})
end

function NESEmulator.NesMapper5:Write(address, value)
	if address < 0x5000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	end
	if address == 0x5100 then
		self._prg_size = value & 3
	elseif address == 0x5101 then
		self._chr_size = value & 3
	elseif address == 0x5102 then
		self._sram_we_a = value & 3
	elseif address == 0x5103 then
		self._sram_we_b = value & 3
	elseif address == 0x5104 then
		self._graphic_mode = value & 3
	elseif address == 0x5105 then
		self._nametable_mode = value
		self._nametable_type[0] = value & 3
		self:Load1kVromBank(value & 3, 0x2000)
		value = value >> 2
		self._nametable_type[1] = value & 3
		self:Load1kVromBank(value & 3, 0x2400)
		value = value >> 2
		self._nametable_type[2] = value & 3
		self:Load1kVromBank(value & 3, 0x2800)
		value = value >> 2
		self._nametable_type[3] = value & 3
		self:Load1kVromBank(value & 3, 0x2c00)
	elseif address == 0x5106 then
		self._fill_chr = value
	elseif address == 0x5107 then
		self._fill_pal = value & 3
	elseif address == 0x5113 then
	elseif address == 0x5114 or address == 0x5115 or address == 0x5116 or address == 0x5117 then
	elseif address == 0x5120 or address == 0x5121 or address == 0x5122 or address == 0x5123 or address == 0x5124 or address == 0x5125 or address == 0x5126 or address == 0x5127 then
		self._chr_mode = 0
		self._chr_page[0][address & 7] = value
	elseif address == 0x5128 or address == 0x5129 or address == 0x512a or address == 0x512b then
		self._chr_mode = 1
		self._chr_page[1][(address & 3) + 0] = value
		self._chr_page[1][(address & 3) + 4] = value
	elseif address == 0x5200 then
		self._split_control = value
	elseif address == 0x5201 then
		self._split_scroll = value
	elseif address == 0x5202 then
		self._split_page = value & 0x3f
	elseif address == 0x5203 then
		self._irq_line = value
		self._nes._cpu:ClearIrq()
	elseif address == 0x5204 then
		self._irq_enable = value
		self._nes._cpu:ClearIrq()
	elseif address == 0x5205 then
		self._mult_a = value
	elseif address == 0x5206 then
		self._mult_b = value
	else
		if address >= 0x5000 and address <= 0x5015 then
		else
			if address >= 0x5c00 and address <= 0x5fff then
				if self._graphic_mode == 2 then
				else
					if self._graphic_mode ~= 3 then
						if self._irq_status & 0x40 ~= 0 then
						else
						end
					end
				end
			else
				if address >= 0x6000 and address <= 0x7fff then
					if self._sram_we_a == 2 and self._sram_we_b == 1 then
					end
				end
			end
		end
	end
end

function NESEmulator.NesMapper5:LoadROM()
	if not self._nes._rom._valid then
		return "UNROM: Invalid ROM! Unable to load."
	end
	self:Load8kRomBank(self._nes._rom._rom_count * 2 - 1, 0x8000)
	self:Load8kRomBank(self._nes._rom._rom_count * 2 - 1, 0xa000)
	self:Load8kRomBank(self._nes._rom._rom_count * 2 - 1, 0xc000)
	self:Load8kRomBank(self._nes._rom._rom_count * 2 - 1, 0xe000)
	self:LoadCHRROM()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

end