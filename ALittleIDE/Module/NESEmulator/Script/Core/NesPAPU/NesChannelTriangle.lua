-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.NesChannelTriangle = Lua.Class(nil, "NESEmulator.NesChannelTriangle")

function NESEmulator.NesChannelTriangle:Ctor(papu)
	___rawset(self, "_papu", papu)
	___rawset(self, "_is_enabled", nil)
	___rawset(self, "_sample_condition", nil)
	___rawset(self, "_length_counter_enable", nil)
	___rawset(self, "_lc_halt", nil)
	___rawset(self, "_lc_control", nil)
	___rawset(self, "_prog_timer_count", nil)
	___rawset(self, "_prog_timer_max", nil)
	___rawset(self, "_triangle_counter", nil)
	___rawset(self, "_length_counter", nil)
	___rawset(self, "_linear_counter", nil)
	___rawset(self, "_lc_load_value", nil)
	___rawset(self, "_sample_value", nil)
	___rawset(self, "_tmp", nil)
	self:Reset()
end

function NESEmulator.NesChannelTriangle:Reset()
	self._prog_timer_count = 0
	self._prog_timer_max = 0
	self._triangle_counter = 0
	self._is_enabled = false
	self._sample_condition = false
	self._length_counter = 0
	self._length_counter_enable = false
	self._linear_counter = 0
	self._lc_load_value = 0
	self._lc_halt = true
	self._lc_control = false
	self._tmp = 0
	self._sample_value = 0xf
end

function NESEmulator.NesChannelTriangle:ClockLengthCounter()
	if self._length_counter_enable and self._length_counter > 0 then
		self._length_counter = self._length_counter - 1
		if self._length_counter == 0 then
			self:UpdateSampleCondition()
		end
	end
end

function NESEmulator.NesChannelTriangle:ClockLinearCounter()
	if self._lc_halt then
		self._linear_counter = self._lc_load_value
		self:UpdateSampleCondition()
	else
		if self._linear_counter > 0 then
			self._linear_counter = self._linear_counter - 1
			self:UpdateSampleCondition()
		end
	end
	if not self._lc_control then
		self._lc_halt = false
	end
end

function NESEmulator.NesChannelTriangle:GetLengthStatus()
	if self._length_counter == 0 or not self._is_enabled then
		return 0
	end
	return 1
end

function NESEmulator.NesChannelTriangle:ReadReg(address)
	return 0
end

function NESEmulator.NesChannelTriangle:WriteReg(address, value)
	if address == 0x4008 then
		self._lc_control = (value & 0x80) ~= 0
		self._lc_load_value = value & 0x7f
		self._length_counter_enable = not self._lc_control
	else
		if address == 0x400a then
			self._prog_timer_max = self._prog_timer_max & 0x700
			self._prog_timer_max = self._prog_timer_max | value
		else
			if address == 0x400b then
				self._prog_timer_max = self._prog_timer_max & 0xff
				self._prog_timer_max = self._prog_timer_max | ((value & 0x07) << 8)
				self._length_counter = self._papu:GetLengthMax(value & 0xf8)
				self._lc_halt = true
			end
		end
	end
	self:UpdateSampleCondition()
end

function NESEmulator.NesChannelTriangle:ClockProgrammableTimer(cycles)
	if self._prog_timer_max > 0 then
		self._prog_timer_count = self._prog_timer_count + (cycles)
		while self._prog_timer_max > 0 and self._prog_timer_count >= self._prog_timer_max do
			self._prog_timer_count = self._prog_timer_count - (self._prog_timer_max)
			if self._is_enabled and self._length_counter > 0 and self._linear_counter > 0 then
				self:ClockTriangleGenerator()
			end
		end
	end
end

function NESEmulator.NesChannelTriangle:ClockTriangleGenerator()
	self._triangle_counter = self._triangle_counter + 1
	self._triangle_counter = self._triangle_counter & 0x1f
end

function NESEmulator.NesChannelTriangle:SetEnabled(value)
	self._is_enabled = value
	if not value then
		self._length_counter = 0
	end
	self:UpdateSampleCondition()
end

function NESEmulator.NesChannelTriangle:UpdateSampleCondition()
	self._sample_condition = self._is_enabled and self._prog_timer_max > 7 and self._linear_counter > 0 and self._length_counter > 0
end

end