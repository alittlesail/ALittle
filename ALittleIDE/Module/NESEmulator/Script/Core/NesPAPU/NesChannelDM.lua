-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesChannelDM = Lua.Class(nil, "NESEmulator.NesChannelDM")

function NESEmulator.NesChannelDM:Ctor(papu)
	___rawset(self, "MODE_NORMAL", 0)
	___rawset(self, "MODE_LOOP", 1)
	___rawset(self, "MODE_IRQ", 2)
	___rawset(self, "_papu", papu)
	___rawset(self, "_is_enabled", nil)
	___rawset(self, "_has_sample", nil)
	___rawset(self, "_irq_generated", false)
	___rawset(self, "_play_mode", nil)
	___rawset(self, "_dma_frequency", nil)
	___rawset(self, "_dma_counter", nil)
	___rawset(self, "_delta_counter", nil)
	___rawset(self, "_play_start_address", nil)
	___rawset(self, "_play_address", nil)
	___rawset(self, "_play_length", nil)
	___rawset(self, "_play_length_counter", nil)
	___rawset(self, "_shift_counter", nil)
	___rawset(self, "_reg4012", nil)
	___rawset(self, "_reg4013", nil)
	___rawset(self, "_sample", nil)
	___rawset(self, "_dac_lsb", nil)
	___rawset(self, "_data", nil)
	self:Reset()
end

function NESEmulator.NesChannelDM:Reset()
	self._is_enabled = false
	self._irq_generated = false
	self._play_mode = self.MODE_NORMAL
	self._dma_frequency = 0
	self._dma_counter = 0
	self._delta_counter = 0
	self._play_start_address = 0
	self._play_address = 0
	self._play_length = 0
	self._play_length_counter = 0
	self._sample = 0
	self._dac_lsb = 0
	self._shift_counter = 0
	self._reg4012 = 0
	self._reg4013 = 0
	self._data = 0
end

function NESEmulator.NesChannelDM:ClockDmc()
	if self._has_sample then
		if (self._data & 1) == 0 then
			if self._delta_counter > 0 then
				self._delta_counter = self._delta_counter - 1
			end
		else
			if self._delta_counter < 63 then
				self._delta_counter = self._delta_counter + 1
			end
		end
		self._sample = NESEmulator.ConditionExpr(self._is_enabled, (self._delta_counter << 1) + self._dac_lsb, 0)
		self._data = self._data >> 1
	end
	self._dma_counter = self._dma_counter - 1
	if self._dma_counter <= 0 then
		self._has_sample = false
		self:EndOfSample()
		self._dma_counter = 8
	end
	if self._irq_generated then
		self._papu._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL)
	end
end

function NESEmulator.NesChannelDM:EndOfSample()
	if self._play_length_counter == 0 and self._play_mode == self.MODE_LOOP then
		self._play_address = self._play_start_address
		self._play_length_counter = self._play_length
	end
	if self._play_length_counter > 0 then
		self:NextSample()
		if self._play_length_counter == 0 then
			if self._play_mode == self.MODE_IRQ then
				self._irq_generated = true
			end
		end
	end
end

function NESEmulator.NesChannelDM:NextSample()
	self._data = self._papu._nes._mmap:Load(self._play_address)
	self._papu._nes._cpu:HaltCycles(4)
	self._play_length_counter = self._play_length_counter - 1
	self._play_address = self._play_address + 1
	if self._play_address > 0xffff then
		self._play_address = 0x8000
	end
	self._has_sample = true
end

function NESEmulator.NesChannelDM:WriteReg(address, value)
	if address == 0x4010 then
		if value >> 6 == 0 then
			self._play_mode = self.MODE_NORMAL
		else
			if ((value >> 6) & 1) == 1 then
				self._play_mode = self.MODE_LOOP
			else
				if value >> 6 == 2 then
					self._play_mode = self.MODE_IRQ
				end
			end
		end
		if (value & 0x80) == 0 then
			self._irq_generated = false
		end
		self._dma_frequency = self._papu:GetDmcFrequency(value & 0xf)
	else
		if address == 0x4011 then
			self._delta_counter = (value >> 1) & 63
			self._dac_lsb = value & 1
			self._sample = (self._delta_counter << 1) + self._dac_lsb
		else
			if address == 0x4012 then
				self._play_start_address = (value << 6) | 0x0c000
				self._play_address = self._play_start_address
				self._reg4012 = value
			else
				if address == 0x4013 then
					self._play_length = (value << 4) + 1
					self._play_length_counter = self._play_length
					self._reg4013 = value
				else
					if address == 0x4015 then
						if ((value >> 4) & 1) == 0 then
							self._play_length_counter = 0
						else
							self._play_address = self._play_start_address
							self._play_length_counter = self._play_length
						end
						self._irq_generated = false
					end
				end
			end
		end
	end
end

function NESEmulator.NesChannelDM:SetEnabled(value)
	if not self._is_enabled and value then
		self._play_length_counter = self._play_length
	end
	self._is_enabled = value
end

function NESEmulator.NesChannelDM:GetLengthStatus()
	if self._play_length_counter == 0 or not self._is_enabled then
		return 0
	end
	return 1
end

function NESEmulator.NesChannelDM:GetIrqStatus()
	if self._irq_generated then
		return 1
	end
	return 0
end

end