-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


assert(NESEmulator.NesMapper, " extends class:NESEmulator.NesMapper is nil")
NESEmulator.NesMapper0 = Lua.Class(NESEmulator.NesMapper, "NESEmulator.NesMapper0")

function NESEmulator.NesMapper0:Reset()
	self._joy1_strobe_state = 0
	self._joy2_strobe_state = 0
	self._joypad_strobe_state = 0
	NESEmulator.NesMapper.Reset(self)
end

function NESEmulator.NesMapper0:Write(address, value)
	if address < 0x2000 then
		self._nes._cpu._mem[address & 0x7ff] = value
	else
		if address > 0x4017 then
			self._nes._cpu._mem[address] = value
			if address >= 0x6000 and address < 0x8000 then
				self._nes:OnBatteryRamWrite(address, value)
			end
		else
			if address > 0x2007 and address < 0x4000 then
				self:RegWrite(0x2000 + (address & 0x7), value)
			else
				self:RegWrite(address, value)
			end
		end
	end
end

function NESEmulator.NesMapper0:Writelow(address, value)
	if address < 0x2000 then
		self._nes._cpu._mem[address & 0x7ff] = value
	else
		if address > 0x4017 then
			self._nes._cpu._mem[address] = value
		else
			if address > 0x2007 and address < 0x4000 then
				self:RegWrite(0x2000 + (address & 0x7), value)
			else
				self:RegWrite(address, value)
			end
		end
	end
end

function NESEmulator.NesMapper0:Load(address)
	address = address & 0xffff
	if address > 0x4017 then
		return self._nes._cpu._mem[address]
	else
		if address >= 0x2000 then
			return self:RegLoad(address)
		else
			return self._nes._cpu._mem[address & 0x7ff]
		end
	end
end

function NESEmulator.NesMapper0:RegLoad(address)
	local type = address >> 12
	if type == 0 or type == 1 then
	elseif type == 2 or type == 3 then
		local reg = address & 0x7
		if reg == 0x0 then
			return self._nes._cpu._mem[0x2000]
		elseif reg == 0x1 then
			return self._nes._cpu._mem[0x2001]
		elseif reg == 0x2 then
			return self._nes._ppu:ReadStatusRegister()
		elseif reg == 0x3 then
			return 0
		elseif reg == 0x4 then
			return self._nes._ppu:SramLoad()
		elseif reg == 0x5 then
			return 0
		elseif reg == 0x6 then
			return 0
		elseif reg == 0x7 then
			return self._nes._ppu:VramLoad()
		end
	elseif type == 4 then
		local reg = address - 0x4015
		if reg == 0 then
			return self._nes._papu:ReadReg(address)
		elseif reg == 1 then
			return self:Joy1Read()
		elseif reg == 2 then
			local w = 0
			if self._zapper_x ~= nil and self._zapper_y ~= nil and self._nes._ppu:IsPixelWhite(self._zapper_x, self._zapper_y) then
				w = 0
			else
				w = 0x1 << 3
			end
			if self._zapper_fired then
				w = w | 0x1 << 4
			end
			return (self:Joy2Read() | w) & 0xffff
		end
	end
	return 0
end

function NESEmulator.NesMapper0:RegWrite(address, value)
	if address == 0x2000 then
		self._nes._cpu._mem[address] = value
		self._nes._ppu:UpdateControlReg1(value)
	elseif address == 0x2001 then
		self._nes._cpu._mem[address] = value
		self._nes._ppu:UpdateControlReg2(value)
	elseif address == 0x2003 then
		self._nes._ppu:WriteSRAMAddress(value)
	elseif address == 0x2004 then
		self._nes._ppu:SramWrite(value)
	elseif address == 0x2005 then
		self._nes._ppu:ScrollWrite(value)
	elseif address == 0x2006 then
		self._nes._ppu:WriteVRAMAddress(value)
	elseif address == 0x2007 then
		self._nes._ppu:VramWrite(value)
	elseif address == 0x4014 then
		self._nes._ppu:SramDMA(value)
	elseif address == 0x4015 then
		self._nes._papu:WriteReg(address, value)
	elseif address == 0x4016 then
		if (value & 1) == 0 and (self._joypad_strobe_state & 1) == 1 then
			self._joy1_strobe_state = 0
			self._joy2_strobe_state = 0
		end
		self._joypad_strobe_state = value
	elseif address == 0x4017 then
		self._nes._papu:WriteReg(address, value)
	else
		if address >= 0x4000 and address <= 0x4017 then
			self._nes._papu:WriteReg(address, value)
		end
	end
end

function NESEmulator.NesMapper0:Joy1Read()
	local ret = 0
	if self._joy1_strobe_state >= 0 and self._joy1_strobe_state <= 7 then
		ret = self._nes._controllers[1]._state[self._joy1_strobe_state]
	elseif self._joy1_strobe_state >= 8 and self._joy1_strobe_state <= 18 then
		ret = 0
	elseif self._joy1_strobe_state == 19 then
		ret = 1
	else
		ret = 0
	end
	self._joy1_strobe_state = self._joy1_strobe_state + 1
	if self._joy1_strobe_state == 24 then
		self._joy1_strobe_state = 0
	end
	return ret
end

function NESEmulator.NesMapper0:Joy2Read()
	local ret = 0
	if self._joy2_strobe_state >= 0 and self._joy2_strobe_state <= 7 then
		ret = self._nes._controllers[2]._state[self._joy2_strobe_state]
	elseif self._joy2_strobe_state >= 8 and self._joy2_strobe_state <= 18 then
		ret = 0
	elseif self._joy2_strobe_state == 19 then
		ret = 1
	else
		ret = 0
	end
	self._joy2_strobe_state = self._joy2_strobe_state + 1
	if self._joy2_strobe_state == 24 then
		self._joy2_strobe_state = 0
	end
	return ret
end

function NESEmulator.NesMapper0:LoadROM()
	if not self._nes._rom._valid or self._nes._rom._rom_count < 1 then
		return "NoMapper: Invalid ROM! Unable to load."
	end
	self:LoadPRGROM()
	self:LoadCHRROM()
	self:LoadBatteryRam()
	self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_RESET)
	return nil
end

function NESEmulator.NesMapper0:LoadPRGROM()
	if self._nes._rom._rom_count > 1 then
		self:LoadRomBank(0, 0x8000)
		self:LoadRomBank(1, 0xc000)
	else
		self:LoadRomBank(0, 0x8000)
		self:LoadRomBank(0, 0xc000)
	end
end

function NESEmulator.NesMapper0:LoadCHRROM()
	if self._nes._rom._vrom_count > 0 then
		if self._nes._rom._vrom_count == 1 then
			self:LoadVromBank(0, 0x0000)
			self:LoadVromBank(0, 0x1000)
		else
			self:LoadVromBank(0, 0x0000)
			self:LoadVromBank(1, 0x1000)
		end
	else
	end
end

function NESEmulator.NesMapper0:LoadBatteryRam()
	if self._nes._rom._battery_ram ~= nil then
		local ram = self._nes._rom._battery_ram
		if ram ~= nil and self._nes._rom._battery_ram_len == 0x2000 then
			NESEmulator.CopyArrayElements(ram, 0, self._nes._cpu._mem, 0x6000, 0x2000)
		end
	end
end

function NESEmulator.NesMapper0:LoadRomBank(bank, address)
	bank = bank % (self._nes._rom._rom_count)
	NESEmulator.CopyArrayElements(self._nes._rom._rom[bank], 0, self._nes._cpu._mem, address, 16384)
end

function NESEmulator.NesMapper0:LoadVromBank(bank, address)
	if self._nes._rom._vrom_count == 0 then
		return
	end
	self._nes._ppu:TriggerRendering()
	NESEmulator.CopyArrayElements(self._nes._rom._vrom[bank % self._nes._rom._vrom_count], 0, self._nes._ppu._vram_mem, address, 4096)
	local vrom_tile = self._nes._rom._vrom_tile[bank % self._nes._rom._vrom_count]
	NESEmulator.CopyArrayElements(vrom_tile, 0, self._nes._ppu._pt_tile, address >> 4, 256)
end

function NESEmulator.NesMapper0:Load32kRomBank(bank, address)
	self:LoadRomBank((bank * 2) % self._nes._rom._rom_count, address)
	self:LoadRomBank((bank * 2 + 1) % self._nes._rom._rom_count, address + 16384)
end

function NESEmulator.NesMapper0:Load8kVromBank(bank4kStart, address)
	if self._nes._rom._vrom_count == 0 then
		return
	end
	self._nes._ppu:TriggerRendering()
	self:LoadVromBank(bank4kStart % self._nes._rom._vrom_count, address)
	self:LoadVromBank((bank4kStart + 1) % self._nes._rom._vrom_count, address + 4096)
end

function NESEmulator.NesMapper0:Load1kVromBank(bank1k, address)
	if self._nes._rom._vrom_count == 0 then
		return
	end
	self._nes._ppu:TriggerRendering()
	local bank4k = ALittle.Math_Floor(bank1k / 4) % self._nes._rom._vrom_count
	local bankoffset = (bank1k % 4) * 1024
	NESEmulator.CopyArrayElements(self._nes._rom._vrom[bank4k], bankoffset, self._nes._ppu._vram_mem, address, 1024)
	local vromTile = self._nes._rom._vrom_tile[bank4k]
	local baseIndex = address >> 4
	local i = 0
	while true do
		if not(i < 64) then break end
		self._nes._ppu._pt_tile[baseIndex + i] = vromTile[(bank1k % 4 << 6) + i]
		i = i+(1)
	end
end

function NESEmulator.NesMapper0:Load2kVromBank(bank2k, address)
	if self._nes._rom._vrom_count == 0 then
		return
	end
	self._nes._ppu:TriggerRendering()
	local bank4k = ALittle.Math_Floor(bank2k / 2) % self._nes._rom._vrom_count
	local bankoffset = (bank2k % 2) * 2048
	NESEmulator.CopyArrayElements(self._nes._rom._vrom[bank4k], bankoffset, self._nes._ppu._vram_mem, address, 2048)
	local vromTile = self._nes._rom._vrom_tile[bank4k]
	local baseIndex = address >> 4
	local i = 0
	while true do
		if not(i < 128) then break end
		self._nes._ppu._pt_tile[baseIndex + i] = vromTile[(bank2k % 2 << 7) + i]
		i = i+(1)
	end
end

function NESEmulator.NesMapper0:Load8kRomBank(bank8k, address)
	local bank16k = ALittle.Math_Floor(bank8k / 2) % self._nes._rom._rom_count
	local offset = (bank8k % 2) * 8192
	NESEmulator.CopyArrayElements(self._nes._rom._rom[bank16k], offset, self._nes._cpu._mem, address, 8192)
end

end