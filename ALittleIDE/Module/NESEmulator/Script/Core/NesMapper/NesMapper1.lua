-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper0, " extends class:NESEmulator.NesMapper0 is nil")
NESEmulator.NesMapper1 = Lua.Class(NESEmulator.NesMapper0, "NESEmulator.NesMapper1")

function NESEmulator.NesMapper1:Reset()
	NESEmulator.NesMapper0.Reset(self)
	self._reg_buffer = 0
	self._reg_buffer_counter = 0
	self._mirroring = 0
	self._one_screen_mirroring = 0
	self._prg_switching_area = 1
	self._prg_switching_size = 1
	self._vrom_switching_size = 0
	self._rom_selection_reg_0 = 0
	self._rom_selection_reg_1 = 0
	self._rom_bank_select = 0
end

function NESEmulator.NesMapper1:Write(address, value)
	if address < 0x8000 then
		NESEmulator.NesMapper0.Write(self, address, value)
		return
	end
	if (value & 128) ~= 0 then
		self._reg_buffer_counter = 0
		self._reg_buffer = 0
		if self:GetRegNumber(address) == 0 then
			self._prg_switching_area = 1
			self._prg_switching_size = 1
		end
	else
		self._reg_buffer = (self._reg_buffer & (0xff - (1 << self._reg_buffer_counter))) | ((value & 1) << self._reg_buffer_counter)
		self._reg_buffer_counter = self._reg_buffer_counter + 1
		if self._reg_buffer_counter == 5 then
			self:SetReg(self:GetRegNumber(address), self._reg_buffer)
			self._reg_buffer = 0
			self._reg_buffer_counter = 0
		end
	end
end

function NESEmulator.NesMapper1:SetReg(reg, value)
	local tmp = 0
	if reg == 0 then
		tmp = value & 3
		if tmp ~= self._mirroring then
			self._mirroring = tmp
			if (self._mirroring & 2) == 0 then
				self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.SINGLESCREEN_MIRRORING)
			elseif (self._mirroring & 1) ~= 0 then
				self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.HORIZONTAL_MIRRORING)
			else
				self._nes._ppu:SetMirroring(NESEmulator.NESMirroringType.VERTICAL_MIRRORING)
			end
		end
		self._prg_switching_area = (value >> 2) & 1
		self._prg_switching_size = (value >> 3) & 1
		self._vrom_switching_size = (value >> 4) & 1
	elseif reg == 1 then
		self._rom_selection_reg_0 = (value >> 4) & 1
		if self._nes._rom._vrom_count > 0 then
			if self._vrom_switching_size == 0 then
				if self._rom_selection_reg_0 == 0 then
					self:Load8kVromBank(value & 0xf, 0x0000)
				else
					self:Load8kVromBank(ALittle.Math_Floor(self._nes._rom._vrom_count / 2) + (value & 0xf), 0x0000)
				end
			else
				if self._rom_selection_reg_0 == 0 then
					self:LoadVromBank(value & 0xf, 0x0000)
				else
					self:LoadVromBank(ALittle.Math_Floor(self._nes._rom._vrom_count / 2) + (value & 0xf), 0x0000)
				end
			end
		end
	elseif reg == 2 then
		self._rom_selection_reg_1 = (value >> 4) & 1
		if self._nes._rom._vrom_count > 0 then
			if self._vrom_switching_size == 1 then
				if self._rom_selection_reg_1 == 0 then
					self:LoadVromBank(value & 0xf, 0x1000)
				else
					self:LoadVromBank(ALittle.Math_Floor(self._nes._rom._vrom_count / 2) + (value & 0xf), 0x1000)
				end
			end
		end
	else
		tmp = value & 0xf
		local bank = 0
		local baseBank = 0
		if self._nes._rom._rom_count >= 32 then
			if self._vrom_switching_size == 0 then
				if self._rom_selection_reg_0 == 1 then
					baseBank = 16
				end
			else
				baseBank = (self._rom_selection_reg_0 | (self._rom_selection_reg_1 << 1)) << 3
			end
		else
			if self._nes._rom._rom_count >= 16 then
				if self._rom_selection_reg_0 == 1 then
					baseBank = 8
				end
			end
		end
		if self._prg_switching_size == 0 then
			bank = baseBank + (value & 0xf)
			self:Load32kRomBank(bank, 0x8000)
		else
			bank = baseBank * 2 + (value & 0xf)
			if self._prg_switching_area == 0 then
				self:LoadRomBank(bank, 0xc000)
			else
				self:LoadRomBank(bank, 0x8000)
			end
		end
	end
end

function NESEmulator.NesMapper1:GetRegNumber(address)
	if address >= 0x8000 and address <= 0x9fff then
		return 0
	else
		if address >= 0xa000 and address <= 0xbfff then
			return 1
		else
			if address >= 0xc000 and address <= 0xdfff then
				return 2
			else
				return 3
			end
		end
	end
end

function NESEmulator.NesMapper1:LoadROM()
	if not self._nes._rom._valid then
		return "MMC1: Invalid ROM! Unable to load."
	end
	self:LoadRomBank(0, 0x8000)
	self:LoadRomBank(self._nes._rom._rom_count - 1, 0xc000)
	self:LoadCHRROM()
	self:LoadBatteryRam()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

function NESEmulator.NesMapper1:switchLowHighPrgRom(old_setting)
end

function NESEmulator.NesMapper1:Switch16to32()
end

function NESEmulator.NesMapper1:Switch32to16()
end

end