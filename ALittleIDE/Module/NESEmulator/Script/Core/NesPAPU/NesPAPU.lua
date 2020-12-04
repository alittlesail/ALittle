-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.CPU_FREQ_NTSC = 1789772.5
NESEmulator.NesPAPU = Lua.Class(nil, "NESEmulator.NesPAPU")

function NESEmulator.NesPAPU:Ctor(nes)
	___rawset(self, "_nes", nes)
	___rawset(self, "_square1", NESEmulator.NesChannelSquare(self, true))
	___rawset(self, "_square2", NESEmulator.NesChannelSquare(self, false))
	___rawset(self, "_triangle", NESEmulator.NesChannelTriangle(self))
	___rawset(self, "_noise", NESEmulator.NesChannelNoise(self))
	___rawset(self, "_dmc", NESEmulator.NesChannelDM(self))
	___rawset(self, "_frame_irq_counter", nil)
	___rawset(self, "_frame_irq_counter_max", 4)
	___rawset(self, "_init_counter", 2048)
	___rawset(self, "_channel_enable_value", nil)
	___rawset(self, "_sample_rate", 44100)
	___rawset(self, "_length_lookup", nil)
	___rawset(self, "_dmc_freq_lookup", nil)
	___rawset(self, "_noise_wavelength_lookup", nil)
	___rawset(self, "_square_table", nil)
	___rawset(self, "_tnd_table", nil)
	___rawset(self, "_frame_irq_enabled", false)
	___rawset(self, "_frame_irq_active", nil)
	___rawset(self, "_frame_clock_now", nil)
	___rawset(self, "_started_playing", false)
	___rawset(self, "_record_output", false)
	___rawset(self, "_initing_hardware", false)
	___rawset(self, "_master_frame_counter", nil)
	___rawset(self, "_derived_frame_counter", nil)
	___rawset(self, "_count_sequence", nil)
	___rawset(self, "_sample_timer", nil)
	___rawset(self, "_frame_time", nil)
	___rawset(self, "_sample_timer_max", nil)
	___rawset(self, "_sample_count", nil)
	___rawset(self, "_tri_value", 0)
	___rawset(self, "_smp_square1", nil)
	___rawset(self, "_smp_square2", nil)
	___rawset(self, "_smp_triangle", nil)
	___rawset(self, "_smp_dmc", nil)
	___rawset(self, "_acc_count", nil)
	___rawset(self, "_prev_sample_l", 0)
	___rawset(self, "_prev_sample_r", 0)
	___rawset(self, "_smp_accum_l", 0)
	___rawset(self, "_smp_accum_r", 0)
	___rawset(self, "_dac_range", 0)
	___rawset(self, "_dac_value", 0)
	___rawset(self, "_master_volume", 256)
	___rawset(self, "_stereo_pos_l_square1", nil)
	___rawset(self, "_stereo_pos_l_square2", nil)
	___rawset(self, "_stereo_pos_l_triangle", nil)
	___rawset(self, "_stereo_pos_l_noise", nil)
	___rawset(self, "_stereo_pos_l_dmc", nil)
	___rawset(self, "_stereo_pos_r_square1", nil)
	___rawset(self, "_stereo_pos_r_square2", nil)
	___rawset(self, "_stereo_pos_r_triangle", nil)
	___rawset(self, "_stereo_pos_r_noise", nil)
	___rawset(self, "_stereo_pos_r_dmc", nil)
	___rawset(self, "_extra_cycles", nil)
	___rawset(self, "_max_sample", nil)
	___rawset(self, "_min_sample", nil)
	local values = {80, 170, 100, 150, 128}
	___rawset(self, "_panning", {})
	for index, value in ___ipairs(values) do
		self._panning[index - 1] = value
	end
	self:SetPanning(self._panning)
	self:InitLengthLookup()
	self:InitDmcFrequencyLookup()
	self:InitNoiseWavelengthLookup()
	self:InitDACtables()
	local i = 0
	while true do
		if not(i < 0x14) then break end
		if i == 0x10 then
			self:WriteReg(0x4010, 0x10)
		else
			self:WriteReg(0x4000 + i, 0)
		end
		i = i+(1)
	end
	___rawset(self, "_square_table_len", 32 * 16)
	___rawset(self, "_tnd_table_len", 204 * 16)
	self:Reset()
end

function NESEmulator.NesPAPU:Reset()
	self._sample_rate = self._nes._sample_rate
	self._sample_timer_max = ALittle.Math_Floor((1024.0 * NESEmulator.CPU_FREQ_NTSC * self._nes._preferred_frame_rate) / (self._sample_rate * 60.0))
	self._frame_time = ALittle.Math_Floor((14915.0 * self._nes._preferred_frame_rate) / 60.0)
	self._sample_timer = 0
	self:UpdateChannelEnable(0)
	self._master_frame_counter = 0
	self._derived_frame_counter = 0
	self._count_sequence = 0
	self._sample_count = 0
	self._init_counter = 2048
	self._frame_irq_enabled = false
	self._initing_hardware = false
	self:ResetCounter()
	self._square1:Reset()
	self._square2:Reset()
	self._triangle:Reset()
	self._noise:Reset()
	self._dmc:Reset()
	self._acc_count = 0
	self._smp_square1 = 0
	self._smp_square2 = 0
	self._smp_triangle = 0
	self._smp_dmc = 0
	self._frame_irq_enabled = false
	self._frame_irq_counter_max = 4
	self._channel_enable_value = 0xff
	self._started_playing = false
	self._prev_sample_l = 0
	self._prev_sample_r = 0
	self._smp_accum_l = 0
	self._smp_accum_r = 0
	self._max_sample = -500000
	self._min_sample = 500000
end

function NESEmulator.NesPAPU:ReadReg(address)
	local tmp = 0
	tmp = tmp | self._square1:GetLengthStatus()
	tmp = tmp | (self._square2:GetLengthStatus() << 1)
	tmp = tmp | (self._triangle:GetLengthStatus() << 2)
	tmp = tmp | (self._noise:GetLengthStatus() << 3)
	tmp = tmp | (self._dmc:GetLengthStatus() << 4)
	tmp = tmp | (NESEmulator.ConditionExpr(self._frame_irq_active and self._frame_irq_enabled, 1, 0)) << 6
	tmp = tmp | (self._dmc:GetIrqStatus() << 7)
	self._frame_irq_active = false
	self._dmc._irq_generated = false
	return tmp & 0xffff
end

function NESEmulator.NesPAPU:WriteReg(address, value)
	if address >= 0x4000 and address < 0x4004 then
		self._square1:WriteReg(address, value)
	else
		if address >= 0x4004 and address < 0x4008 then
			self._square2:WriteReg(address, value)
		else
			if address >= 0x4008 and address < 0x400c then
				self._triangle:WriteReg(address, value)
			else
				if address >= 0x400c and address <= 0x400f then
					self._noise:WriteReg(address, value)
				else
					if address == 0x4010 then
						self._dmc:WriteReg(address, value)
					else
						if address == 0x4011 then
							self._dmc:WriteReg(address, value)
						else
							if address == 0x4012 then
								self._dmc:WriteReg(address, value)
							else
								if address == 0x4013 then
									self._dmc:WriteReg(address, value)
								else
									if address == 0x4015 then
										self:UpdateChannelEnable(value)
										if value ~= 0 and self._init_counter > 0 then
											self._initing_hardware = true
										end
										self._dmc:WriteReg(address, value)
									else
										if address == 0x4017 then
											self._count_sequence = (value >> 7) & 1
											self._master_frame_counter = 0
											self._frame_irq_active = false
											if ((value >> 6) & 0x1) == 0 then
												self._frame_irq_enabled = true
											else
												self._frame_irq_enabled = false
											end
											if self._count_sequence == 0 then
												self._frame_irq_counter_max = 4
												self._derived_frame_counter = 4
											else
												self._frame_irq_counter_max = 5
												self._derived_frame_counter = 0
												self:FrameCounterTick()
											end
										end
									end
								end
							end
						end
					end
				end
			end
		end
	end
end

function NESEmulator.NesPAPU:ResetCounter()
	if self._count_sequence == 0 then
		self._derived_frame_counter = 4
	else
		self._derived_frame_counter = 0
	end
end

function NESEmulator.NesPAPU:UpdateChannelEnable(value)
	self._channel_enable_value = value & 0xffff
	self._square1:SetEnabled((value & 1) ~= 0)
	self._square2:SetEnabled((value & 2) ~= 0)
	self._triangle:SetEnabled((value & 4) ~= 0)
	self._noise:SetEnabled((value & 8) ~= 0)
	self._dmc:SetEnabled((value & 16) ~= 0)
end

function NESEmulator.NesPAPU:ClockFrameCounter(cycles)
	if self._init_counter > 0 then
		if self._initing_hardware then
			self._init_counter = self._init_counter - (cycles)
			if self._init_counter <= 0 then
				self._initing_hardware = false
			end
			return
		end
	end
	cycles = cycles + (self._extra_cycles)
	local maxCycles = self._sample_timer_max - self._sample_timer
	if cycles << 10 > maxCycles then
		self._extra_cycles = ((cycles << 10) - maxCycles) >> 10
		cycles = cycles - (self._extra_cycles)
	else
		self._extra_cycles = 0
	end
	local dmc = self._dmc
	local triangle = self._triangle
	local square1 = self._square1
	local square2 = self._square2
	local noise = self._noise
	if dmc._is_enabled then
		dmc._shift_counter = dmc._shift_counter - (cycles << 3)
		while dmc._shift_counter <= 0 and dmc._dma_frequency > 0 do
			dmc._shift_counter = dmc._shift_counter + (dmc._dma_frequency)
			dmc:ClockDmc()
		end
	end
	if triangle._prog_timer_max > 0 then
		triangle._prog_timer_count = triangle._prog_timer_count - (cycles)
		while triangle._prog_timer_count <= 0 do
			triangle._prog_timer_count = triangle._prog_timer_count + (triangle._prog_timer_max + 1)
			if triangle._linear_counter > 0 and triangle._length_counter > 0 then
				triangle._triangle_counter = triangle._triangle_counter + 1
				triangle._triangle_counter = triangle._triangle_counter & 0x1f
				if triangle._is_enabled then
					if triangle._triangle_counter >= 0x10 then
						triangle._sample_value = triangle._triangle_counter & 0xf
					else
						triangle._sample_value = 0xf - (triangle._triangle_counter & 0xf)
					end
					triangle._sample_value = triangle._sample_value << 4
				end
			end
		end
	end
	square1._prog_timer_count = square1._prog_timer_count - (cycles)
	if square1._prog_timer_count <= 0 then
		square1._prog_timer_count = square1._prog_timer_count + ((square1._prog_timer_max + 1) << 1)
		square1._square_counter = square1._square_counter + 1
		square1._square_counter = square1._square_counter & 0x7
		square1:UpdateSampleValue()
	end
	square2._prog_timer_count = square2._prog_timer_count - (cycles)
	if square2._prog_timer_count <= 0 then
		square2._prog_timer_count = square2._prog_timer_count + ((square2._prog_timer_max + 1) << 1)
		square2._square_counter = square2._square_counter + 1
		square2._square_counter = square2._square_counter & 0x7
		square2:UpdateSampleValue()
	end
	local acc_c = cycles
	if noise._prog_timer_count - acc_c > 0 then
		noise._prog_timer_count = noise._prog_timer_count - (acc_c)
		noise._acc_count = noise._acc_count + (acc_c)
		noise._acc_value = noise._acc_value + (acc_c * noise._sample_value)
	else
		while acc_c > 0 do
			acc_c = acc_c - 1
			noise._prog_timer_count = noise._prog_timer_count - 1
			if noise._prog_timer_count <= 0 and noise._prog_timer_max > 0 then
				noise._shift_reg = noise._shift_reg << 1
				noise._tmp = ((noise._shift_reg << NESEmulator.ConditionExpr(noise._random_mode == 0, 1, 6)) ~ noise._shift_reg) & 0x8000
				if noise._tmp ~= 0 then
					noise._shift_reg = noise._shift_reg | 0x01
					noise._random_bit = 0
					noise._sample_value = 0
				else
					noise._random_bit = 1
					if noise._is_enabled and noise._length_counter > 0 then
						noise._sample_value = noise._master_volume
					else
						noise._sample_value = 0
					end
				end
				noise._prog_timer_count = noise._prog_timer_count + (noise._prog_timer_max)
			end
			noise._acc_value = noise._acc_value + (noise._sample_value)
			noise._acc_count = noise._acc_count + 1
		end
	end
	if self._frame_irq_enabled and self._frame_irq_active then
		self._nes._cpu:RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL)
	end
	self._master_frame_counter = self._master_frame_counter + (cycles << 1)
	if self._master_frame_counter >= self._frame_time then
		self._master_frame_counter = self._master_frame_counter - (self._frame_time)
		self:FrameCounterTick()
	end
	self:AccSample(cycles)
	self._sample_timer = self._sample_timer + (cycles << 10)
	if self._sample_timer >= self._sample_timer_max then
		self:Sample()
		self._sample_timer = self._sample_timer - (self._sample_timer_max)
	end
end

function NESEmulator.NesPAPU:AccSample(cycles)
	if self._triangle._sample_condition then
		self._tri_value = ALittle.Math_Floor((self._triangle._prog_timer_count << 4) / (self._triangle._prog_timer_max + 1))
		if self._tri_value > 16 then
			self._tri_value = 16
		end
		if self._triangle._triangle_counter >= 16 then
			self._tri_value = 16 - self._tri_value
		end
		self._tri_value = self._tri_value + (self._triangle._sample_value)
	end
	if cycles == 2 then
		self._smp_triangle = self._smp_triangle + (self._tri_value << 1)
		self._smp_dmc = self._smp_dmc + (self._dmc._sample << 1)
		self._smp_square1 = self._smp_square1 + (self._square1._sample_value << 1)
		self._smp_square2 = self._smp_square2 + (self._square2._sample_value << 1)
		self._acc_count = self._acc_count + (2)
	else
		if cycles == 4 then
			self._smp_triangle = self._smp_triangle + (self._tri_value << 2)
			self._smp_dmc = self._smp_dmc + (self._dmc._sample << 2)
			self._smp_square1 = self._smp_square1 + (self._square1._sample_value << 2)
			self._smp_square2 = self._smp_square2 + (self._square2._sample_value << 2)
			self._acc_count = self._acc_count + (4)
		else
			self._smp_triangle = self._smp_triangle + (cycles * self._tri_value)
			self._smp_dmc = self._smp_dmc + (cycles * self._dmc._sample)
			self._smp_square1 = self._smp_square1 + (cycles * self._square1._sample_value)
			self._smp_square2 = self._smp_square2 + (cycles * self._square2._sample_value)
			self._acc_count = self._acc_count + (cycles)
		end
	end
end

function NESEmulator.NesPAPU:FrameCounterTick()
	self._derived_frame_counter = self._derived_frame_counter + 1
	if self._derived_frame_counter >= self._frame_irq_counter_max then
		self._derived_frame_counter = 0
	end
	if self._derived_frame_counter == 1 or self._derived_frame_counter == 3 then
		self._triangle:ClockLengthCounter()
		self._square1:ClockLengthCounter()
		self._square2:ClockLengthCounter()
		self._noise:ClockLengthCounter()
		self._square1:ClockSweep()
		self._square2:ClockSweep()
	end
	if self._derived_frame_counter >= 0 and self._derived_frame_counter < 4 then
		self._square1:ClockEnvDecay()
		self._square2:ClockEnvDecay()
		self._noise:ClockEnvDecay()
		self._triangle:ClockLinearCounter()
	end
	if self._derived_frame_counter == 3 and self._count_sequence == 0 then
		self._frame_irq_active = true
	end
end

function NESEmulator.NesPAPU:Sample()
	if self._acc_count > 0 then
		self._smp_square1 = self._smp_square1 << 4
		self._smp_square1 = ALittle.Math_Floor(self._smp_square1 / self._acc_count)
		self._smp_square2 = self._smp_square2 << 4
		self._smp_square2 = ALittle.Math_Floor(self._smp_square2 / self._acc_count)
		self._smp_triangle = ALittle.Math_Floor(self._smp_triangle / self._acc_count)
		self._smp_dmc = self._smp_dmc << 4
		self._smp_dmc = ALittle.Math_Floor(self._smp_dmc / self._acc_count)
		self._acc_count = 0
	else
		self._smp_square1 = self._square1._sample_value << 4
		self._smp_square2 = self._square2._sample_value << 4
		self._smp_triangle = self._triangle._sample_value
		self._smp_dmc = self._dmc._sample << 4
	end
	local smpNoise = ALittle.Math_Floor((self._noise._acc_value << 4) / self._noise._acc_count)
	self._noise._acc_value = smpNoise >> 4
	self._noise._acc_count = 1
	local sq_index = (self._smp_square1 * self._stereo_pos_l_square1 + self._smp_square2 * self._stereo_pos_l_square2) >> 8
	local tnd_index = (3 * self._smp_triangle * self._stereo_pos_l_triangle + (smpNoise << 1) * self._stereo_pos_l_noise + self._smp_dmc * self._stereo_pos_l_dmc) >> 8
	if sq_index >= self._square_table_len then
		sq_index = self._square_table_len - 1
	end
	if tnd_index >= self._tnd_table_len then
		tnd_index = self._tnd_table_len - 1
	end
	local sampleValueL = self._square_table[sq_index] + self._tnd_table[tnd_index] - self._dac_value
	sq_index = (self._smp_square1 * self._stereo_pos_r_square1 + self._smp_square2 * self._stereo_pos_r_square2) >> 8
	tnd_index = (3 * self._smp_triangle * self._stereo_pos_r_triangle + (smpNoise << 1) * self._stereo_pos_r_noise + self._smp_dmc * self._stereo_pos_r_dmc) >> 8
	if sq_index >= self._square_table_len then
		sq_index = self._square_table_len - 1
	end
	if tnd_index >= self._tnd_table_len then
		tnd_index = self._tnd_table_len - 1
	end
	local sampleValueR = self._square_table[sq_index] + self._tnd_table[tnd_index] - self._dac_value
	local smpDiffL = sampleValueL - self._prev_sample_l
	self._prev_sample_l = self._prev_sample_l + (smpDiffL)
	self._smp_accum_l = self._smp_accum_l + (smpDiffL - (self._smp_accum_l >> 10))
	sampleValueL = self._smp_accum_l
	local smpDiffR = sampleValueR - self._prev_sample_r
	self._prev_sample_r = self._prev_sample_r + (smpDiffR)
	self._smp_accum_r = self._smp_accum_r + (smpDiffR - (self._smp_accum_r >> 10))
	sampleValueR = self._smp_accum_r
	if sampleValueL > self._max_sample then
		self._max_sample = sampleValueL
	end
	if sampleValueL < self._min_sample then
		self._min_sample = sampleValueL
	end
	self._nes:OnAudioSample(sampleValueL / 32768, sampleValueR / 32768)
	self._smp_square1 = 0
	self._smp_square2 = 0
	self._smp_triangle = 0
	self._smp_dmc = 0
end

function NESEmulator.NesPAPU:GetLengthMax(value)
	return self._length_lookup[value >> 3]
end

function NESEmulator.NesPAPU:GetDmcFrequency(value)
	if value >= 0 and value < 0x10 then
		return self._dmc_freq_lookup[value]
	end
	return 0
end

function NESEmulator.NesPAPU:GetNoiseWaveLength(value)
	if value >= 0 and value < 0x10 then
		return self._noise_wavelength_lookup[value]
	end
	return 0
end

function NESEmulator.NesPAPU:SetPanning(pos)
	local i = 0
	while true do
		if not(i < 5) then break end
		self._panning[i] = pos[i]
		i = i+(1)
	end
	self:UpdateStereoPos()
end

function NESEmulator.NesPAPU:SetMasterVolume(value)
	if value < 0 then
		value = 0
	end
	if value > 256 then
		value = 256
	end
	self._master_volume = value
	self:UpdateStereoPos()
end

function NESEmulator.NesPAPU:UpdateStereoPos()
	self._stereo_pos_l_square1 = (self._panning[0] * self._master_volume) >> 8
	self._stereo_pos_l_square2 = (self._panning[1] * self._master_volume) >> 8
	self._stereo_pos_l_triangle = (self._panning[2] * self._master_volume) >> 8
	self._stereo_pos_l_noise = (self._panning[3] * self._master_volume) >> 8
	self._stereo_pos_l_dmc = (self._panning[4] * self._master_volume) >> 8
	self._stereo_pos_r_square1 = self._master_volume - self._stereo_pos_l_square1
	self._stereo_pos_r_square2 = self._master_volume - self._stereo_pos_l_square2
	self._stereo_pos_r_triangle = self._master_volume - self._stereo_pos_l_triangle
	self._stereo_pos_r_noise = self._master_volume - self._stereo_pos_l_noise
	self._stereo_pos_r_dmc = self._master_volume - self._stereo_pos_l_dmc
end

function NESEmulator.NesPAPU:InitLengthLookup()
	local values = {0x0A, 0xFE, 0x14, 0x02, 0x28, 0x04, 0x50, 0x06, 0xA0, 0x08, 0x3C, 0x0A, 0x0E, 0x0C, 0x1A, 0x0E, 0x0C, 0x10, 0x18, 0x12, 0x30, 0x14, 0x60, 0x16, 0xC0, 0x18, 0x48, 0x1A, 0x10, 0x1C, 0x20, 0x1E}
	self._length_lookup = {}
	for index, value in ___ipairs(values) do
		self._length_lookup[index - 1] = value
	end
end

function NESEmulator.NesPAPU:InitDmcFrequencyLookup()
	self._dmc_freq_lookup = {}
	self._dmc_freq_lookup[0x0] = 0xd60
	self._dmc_freq_lookup[0x1] = 0xbe0
	self._dmc_freq_lookup[0x2] = 0xaa0
	self._dmc_freq_lookup[0x3] = 0xa00
	self._dmc_freq_lookup[0x4] = 0x8f0
	self._dmc_freq_lookup[0x5] = 0x7f0
	self._dmc_freq_lookup[0x6] = 0x710
	self._dmc_freq_lookup[0x7] = 0x6b0
	self._dmc_freq_lookup[0x8] = 0x5f0
	self._dmc_freq_lookup[0x9] = 0x500
	self._dmc_freq_lookup[0xa] = 0x470
	self._dmc_freq_lookup[0xb] = 0x400
	self._dmc_freq_lookup[0xc] = 0x350
	self._dmc_freq_lookup[0xd] = 0x2a0
	self._dmc_freq_lookup[0xe] = 0x240
	self._dmc_freq_lookup[0xf] = 0x1b0
end

function NESEmulator.NesPAPU:InitNoiseWavelengthLookup()
	self._noise_wavelength_lookup = {}
	self._noise_wavelength_lookup[0x0] = 0x004
	self._noise_wavelength_lookup[0x1] = 0x008
	self._noise_wavelength_lookup[0x2] = 0x010
	self._noise_wavelength_lookup[0x3] = 0x020
	self._noise_wavelength_lookup[0x4] = 0x040
	self._noise_wavelength_lookup[0x5] = 0x060
	self._noise_wavelength_lookup[0x6] = 0x080
	self._noise_wavelength_lookup[0x7] = 0x0a0
	self._noise_wavelength_lookup[0x8] = 0x0ca
	self._noise_wavelength_lookup[0x9] = 0x0fe
	self._noise_wavelength_lookup[0xa] = 0x17c
	self._noise_wavelength_lookup[0xb] = 0x1fc
	self._noise_wavelength_lookup[0xc] = 0x2fa
	self._noise_wavelength_lookup[0xd] = 0x3f8
	self._noise_wavelength_lookup[0xe] = 0x7f2
	self._noise_wavelength_lookup[0xf] = 0xfe4
end

function NESEmulator.NesPAPU:InitDACtables()
	local max_sqr = 0
	local max_tnd = 0
	self._square_table = {}
	local i = 0
	while true do
		if not(i < self._square_table_len) then break end
		local value = 95.52 / (8128.0 / (i / 16.0) + 100.0)
		value = value * (0.98411)
		value = value * (50000.0)
		local ival = ALittle.Math_Floor(value)
		self._square_table[i] = ival
		if ival > max_sqr then
			max_sqr = ival
		end
		i = i+(1)
	end
	self._tnd_table = {}
	local i = 0
	while true do
		if not(i < self._tnd_table_len) then break end
		local value = 163.67 / (24329.0 / (i / 16.0) + 100.0)
		value = value * (0.98411)
		value = value * (50000.0)
		local ival = ALittle.Math_Floor(value)
		self._tnd_table[i] = ival
		if ival > max_tnd then
			max_tnd = ival
		end
		i = i+(1)
	end
	self._dac_range = max_sqr + max_tnd
	self._dac_value = ALittle.Math_Floor(self._dac_range / 2)
end

end