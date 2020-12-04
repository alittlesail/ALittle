-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesChannelSquare = Lua.Class(nil, "NESEmulator.NesChannelSquare")

function NESEmulator.NesChannelSquare:Ctor(papu, square1)
	___rawset(self, "_papu", papu)
	local values = {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1}
	for index, value in ___ipairs(values) do
		self._duty_lookup[index - 1] = value
	end
	values = {1, -1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0}
	for index, value in ___ipairs(values) do
		self._imp_lookup[index - 1] = value
	end
	___rawset(self, "_sqr1", square1)
	___rawset(self, "_is_enabled", nil)
	___rawset(self, "_length_counter_enable", nil)
	___rawset(self, "_sweep_active", nil)
	___rawset(self, "_env_decay_disable", nil)
	___rawset(self, "_env_decay_loop_enable", nil)
	___rawset(self, "_env_reset", nil)
	___rawset(self, "_sweep_carry", nil)
	___rawset(self, "_update_sweep_period", nil)
	___rawset(self, "_prog_timer_count", nil)
	___rawset(self, "_prog_timer_max", nil)
	___rawset(self, "_length_counter", nil)
	___rawset(self, "_square_counter", nil)
	___rawset(self, "_sweep_counter", nil)
	___rawset(self, "_sweep_counter_max", nil)
	___rawset(self, "_sweep_mode", nil)
	___rawset(self, "_sweep_shift_amount", nil)
	___rawset(self, "_env_decay_rate", nil)
	___rawset(self, "_env_decay_counter", nil)
	___rawset(self, "_env_volume", nil)
	___rawset(self, "_master_volume", nil)
	___rawset(self, "_duty_mode", nil)
	___rawset(self, "_sweep_result", nil)
	___rawset(self, "_sample_value", nil)
	___rawset(self, "_vol", nil)
	self:Reset()
end

function NESEmulator.NesChannelSquare:Reset()
	self._prog_timer_count = 0
	self._prog_timer_max = 0
	self._length_counter = 0
	self._square_counter = 0
	self._sweep_counter = 0
	self._sweep_counter_max = 0
	self._sweep_mode = 0
	self._sweep_shift_amount = 0
	self._env_decay_rate = 0
	self._env_decay_counter = 0
	self._env_volume = 0
	self._master_volume = 0
	self._duty_mode = 0
	self._vol = 0
	self._is_enabled = false
	self._length_counter_enable = false
	self._sweep_active = false
	self._sweep_carry = false
	self._env_decay_disable = false
	self._env_decay_loop_enable = false
end

function NESEmulator.NesChannelSquare:ClockLengthCounter()
	if self._length_counter_enable and self._length_counter > 0 then
		self._length_counter = self._length_counter - 1
		if self._length_counter == 0 then
			self:UpdateSampleValue()
		end
	end
end

function NESEmulator.NesChannelSquare:ClockEnvDecay()
	if self._env_reset then
		self._env_reset = false
		self._env_decay_counter = self._env_decay_rate + 1
		self._env_volume = 0xf
	else
		self._env_decay_counter = self._env_decay_counter - 1
		if self._env_decay_counter <= 0 then
			self._env_decay_counter = self._env_decay_rate + 1
			if self._env_volume > 0 then
				self._env_volume = self._env_volume - 1
			else
				self._env_volume = NESEmulator.ConditionExpr(self._env_decay_loop_enable, 0xf, 0)
			end
		end
	end
	if self._env_decay_disable then
		self._master_volume = self._env_decay_rate
	else
		self._master_volume = self._env_volume
	end
	self:UpdateSampleValue()
end

function NESEmulator.NesChannelSquare:ClockSweep()
	self._sweep_counter = self._sweep_counter - 1
	if self._sweep_counter <= 0 then
		self._sweep_counter = self._sweep_counter_max + 1
		if self._sweep_active and self._sweep_shift_amount > 0 and self._prog_timer_max > 7 then
			self._sweep_carry = false
			if self._sweep_mode == 0 then
				self._prog_timer_max = self._prog_timer_max + (self._prog_timer_max >> self._sweep_shift_amount)
				if self._prog_timer_max > 4095 then
					self._prog_timer_max = 4095
					self._sweep_carry = true
				end
			else
				self._prog_timer_max = self._prog_timer_max - ((self._prog_timer_max >> self._sweep_shift_amount) - NESEmulator.ConditionExpr(self._sqr1, 1, 0))
			end
		end
	end
	if self._update_sweep_period then
		self._update_sweep_period = false
		self._sweep_counter = self._sweep_counter_max + 1
	end
end

function NESEmulator.NesChannelSquare:UpdateSampleValue()
	if self._is_enabled and self._length_counter > 0 and self._prog_timer_max > 7 then
		if self._sweep_mode == 0 and self._prog_timer_max + (self._prog_timer_max >> self._sweep_shift_amount) > 4095 then
			self._sample_value = 0
		else
			self._sample_value = self._master_volume * self._duty_lookup[(self._duty_mode << 3) + self._square_counter]
		end
	else
		self._sample_value = 0
	end
end

function NESEmulator.NesChannelSquare:WriteReg(address, value)
	local addrAdd = 4
	if self._sqr1 then
		addrAdd = 0
	end
	if address == 0x4000 + addrAdd then
		self._env_decay_disable = (value & 0x10) ~= 0
		self._env_decay_rate = value & 0xf
		self._env_decay_loop_enable = (value & 0x20) ~= 0
		self._duty_mode = (value >> 6) & 0x3
		self._length_counter_enable = (value & 0x20) == 0
		if self._env_decay_disable then
			self._master_volume = self._env_decay_rate
		else
			self._master_volume = self._env_volume
		end
		self:UpdateSampleValue()
	else
		if address == 0x4001 + addrAdd then
			self._sweep_active = (value & 0x80) ~= 0
			self._sweep_counter_max = (value >> 4) & 7
			self._sweep_mode = (value >> 3) & 1
			self._sweep_shift_amount = value & 7
			self._update_sweep_period = true
		else
			if address == 0x4002 + addrAdd then
				self._prog_timer_max = self._prog_timer_max & 0x700
				self._prog_timer_max = self._prog_timer_max | value
			else
				if address == 0x4003 + addrAdd then
					self._prog_timer_max = self._prog_timer_max & 0xff
					self._prog_timer_max = self._prog_timer_max | ((value & 0x7) << 8)
					if self._is_enabled then
						self._length_counter = self._papu:GetLengthMax(value & 0xf8)
					end
					self._env_reset = true
				end
			end
		end
	end
end

function NESEmulator.NesChannelSquare:SetEnabled(value)
	self._is_enabled = value
	if not value then
		self._length_counter = 0
	end
	self:UpdateSampleValue()
end

function NESEmulator.NesChannelSquare:GetLengthStatus()
	if self._length_counter == 0 or not self._is_enabled then
		return 0
	end
	return 1
end

end