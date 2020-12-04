-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesChannelNoise = Lua.Class(nil, "NESEmulator.NesChannelNoise")

function NESEmulator.NesChannelNoise:Ctor(papu)
	___rawset(self, "_papu", papu)
	___rawset(self, "_is_enabled", nil)
	___rawset(self, "_env_decay_disable", nil)
	___rawset(self, "_env_decay_loop_enable", nil)
	___rawset(self, "_length_counter_enable", nil)
	___rawset(self, "_env_reset", nil)
	___rawset(self, "_shift_now", nil)
	___rawset(self, "_length_counter", nil)
	___rawset(self, "_prog_timer_count", nil)
	___rawset(self, "_prog_timer_max", nil)
	___rawset(self, "_env_decay_rate", nil)
	___rawset(self, "_env_decay_counter", nil)
	___rawset(self, "_env_volume", nil)
	___rawset(self, "_master_volume", nil)
	___rawset(self, "_shift_reg", 1 << 14)
	___rawset(self, "_random_bit", nil)
	___rawset(self, "_random_mode", nil)
	___rawset(self, "_sample_value", nil)
	___rawset(self, "_acc_value", 0)
	___rawset(self, "_acc_count", 1)
	___rawset(self, "_tmp", nil)
	self:Reset()
end

function NESEmulator.NesChannelNoise:Reset()
	self._prog_timer_count = 0
	self._prog_timer_max = 0
	self._is_enabled = false
	self._length_counter = 0
	self._length_counter_enable = false
	self._env_decay_disable = false
	self._env_decay_loop_enable = false
	self._shift_now = false
	self._env_decay_rate = 0
	self._env_decay_counter = 0
	self._env_volume = 0
	self._master_volume = 0
	self._shift_reg = 1
	self._random_bit = 0
	self._random_mode = 0
	self._sample_value = 0
	self._tmp = 0
end

function NESEmulator.NesChannelNoise:ClockLengthCounter()
	if self._length_counter_enable and self._length_counter > 0 then
		self._length_counter = self._length_counter - 1
		if self._length_counter == 0 then
			self:UpdateSampleValue()
		end
	end
end

function NESEmulator.NesChannelNoise:ClockEnvDecay()
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

function NESEmulator.NesChannelNoise:UpdateSampleValue()
	if self._is_enabled and self._length_counter > 0 then
		self._sample_value = self._random_bit * self._master_volume
	end
end

function NESEmulator.NesChannelNoise:WriteReg(address, value)
	if address == 0x400c then
		self._env_decay_disable = (value & 0x10) ~= 0
		self._env_decay_rate = value & 0xf
		self._env_decay_loop_enable = (value & 0x20) ~= 0
		self._length_counter_enable = (value & 0x20) == 0
		if self._env_decay_disable then
			self._master_volume = self._env_decay_rate
		else
			self._master_volume = self._env_volume
		end
	else
		if address == 0x400e then
			self._prog_timer_max = self._papu:GetNoiseWaveLength(value & 0xf)
			self._random_mode = value >> 7
		else
			if address == 0x400f then
				self._length_counter = self._papu:GetLengthMax(value & 248)
				self._env_reset = true
			end
		end
	end
end

function NESEmulator.NesChannelNoise:SetEnabled(value)
	self._is_enabled = value
	if not value then
		self._length_counter = 0
	end
	self:UpdateSampleValue()
end

function NESEmulator.NesChannelNoise:GetLengthStatus()
	if self._length_counter == 0 or not self._is_enabled then
		return 0
	end
	return 1
end

end