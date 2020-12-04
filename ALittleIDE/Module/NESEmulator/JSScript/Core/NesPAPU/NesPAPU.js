{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.CPU_FREQ_NTSC = 1789772.5;
NESEmulator.NesPAPU = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._nes = nes;
		this._square1 = ALittle.NewObject(NESEmulator.NesChannelSquare, this, true);
		this._square2 = ALittle.NewObject(NESEmulator.NesChannelSquare, this, false);
		this._triangle = ALittle.NewObject(NESEmulator.NesChannelTriangle, this);
		this._noise = ALittle.NewObject(NESEmulator.NesChannelNoise, this);
		this._dmc = ALittle.NewObject(NESEmulator.NesChannelDM, this);
		this._frame_irq_counter = undefined;
		this._frame_irq_counter_max = 4;
		this._init_counter = 2048;
		this._channel_enable_value = undefined;
		this._sample_rate = 44100;
		this._length_lookup = undefined;
		this._dmc_freq_lookup = undefined;
		this._noise_wavelength_lookup = undefined;
		this._square_table = undefined;
		this._tnd_table = undefined;
		this._square_table_len = 32 * 16;
		this._tnd_table_len = 204 * 16;
		this._frame_irq_enabled = false;
		this._frame_irq_active = undefined;
		this._frame_clock_now = undefined;
		this._started_playing = false;
		this._record_output = false;
		this._initing_hardware = false;
		this._master_frame_counter = undefined;
		this._derived_frame_counter = undefined;
		this._count_sequence = undefined;
		this._sample_timer = undefined;
		this._frame_time = undefined;
		this._sample_timer_max = undefined;
		this._sample_count = undefined;
		this._tri_value = 0;
		this._smp_square1 = undefined;
		this._smp_square2 = undefined;
		this._smp_triangle = undefined;
		this._smp_dmc = undefined;
		this._acc_count = undefined;
		this._prev_sample_l = 0;
		this._prev_sample_r = 0;
		this._smp_accum_l = 0;
		this._smp_accum_r = 0;
		this._dac_range = 0;
		this._dac_value = 0;
		this._master_volume = 256;
		this._stereo_pos_l_square1 = undefined;
		this._stereo_pos_l_square2 = undefined;
		this._stereo_pos_l_triangle = undefined;
		this._stereo_pos_l_noise = undefined;
		this._stereo_pos_l_dmc = undefined;
		this._stereo_pos_r_square1 = undefined;
		this._stereo_pos_r_square2 = undefined;
		this._stereo_pos_r_triangle = undefined;
		this._stereo_pos_r_noise = undefined;
		this._stereo_pos_r_dmc = undefined;
		this._extra_cycles = 0;
		this._max_sample = undefined;
		this._min_sample = undefined;
		let values = [80, 170, 100, 150, 128];
		this._panning = new Map();
		let ___OBJECT_1 = values;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this._panning.set(index - 1, value);
		}
		this.SetPanning(this._panning);
		this.InitLengthLookup();
		this.InitDmcFrequencyLookup();
		this.InitNoiseWavelengthLookup();
		this.InitDACtables();
		for (let i = 0; i < 0x14; i += 1) {
			if (i === 0x10) {
				this.WriteReg(0x4010, 0x10);
			} else {
				this.WriteReg(0x4000 + i, 0);
			}
		}
		this.Reset();
	},
	Reset : function() {
		this._sample_rate = this._nes._sample_rate;
		this._sample_timer_max = ALittle.Math_Floor((1024.0 * NESEmulator.CPU_FREQ_NTSC * this._nes._preferred_frame_rate) / (this._sample_rate * 60.0));
		this._frame_time = ALittle.Math_Floor((14915.0 * this._nes._preferred_frame_rate) / 60.0);
		this._sample_timer = 0;
		this.UpdateChannelEnable(0);
		this._master_frame_counter = 0;
		this._derived_frame_counter = 0;
		this._count_sequence = 0;
		this._sample_count = 0;
		this._init_counter = 2048;
		this._frame_irq_enabled = false;
		this._initing_hardware = false;
		this.ResetCounter();
		this._square1.Reset();
		this._square2.Reset();
		this._triangle.Reset();
		this._noise.Reset();
		this._dmc.Reset();
		this._acc_count = 0;
		this._smp_square1 = 0;
		this._smp_square2 = 0;
		this._smp_triangle = 0;
		this._smp_dmc = 0;
		this._frame_irq_enabled = false;
		this._frame_irq_counter_max = 4;
		this._channel_enable_value = 0xff;
		this._started_playing = false;
		this._prev_sample_l = 0;
		this._prev_sample_r = 0;
		this._smp_accum_l = 0;
		this._smp_accum_r = 0;
		this._max_sample = -500000;
		this._min_sample = 500000;
	},
	ReadReg : function(address) {
		let tmp = 0;
		tmp = tmp | this._square1.GetLengthStatus();
		tmp = tmp | (this._square2.GetLengthStatus() << 1);
		tmp = tmp | (this._triangle.GetLengthStatus() << 2);
		tmp = tmp | (this._noise.GetLengthStatus() << 3);
		tmp = tmp | (this._dmc.GetLengthStatus() << 4);
		tmp = tmp | (NESEmulator.ConditionExpr(this._frame_irq_active && this._frame_irq_enabled, 1, 0)) << 6;
		tmp = tmp | (this._dmc.GetIrqStatus() << 7);
		this._frame_irq_active = false;
		this._dmc._irq_generated = false;
		return tmp & 0xffff;
	},
	WriteReg : function(address, value) {
		if (address >= 0x4000 && address < 0x4004) {
			this._square1.WriteReg(address, value);
		} else {
			if (address >= 0x4004 && address < 0x4008) {
				this._square2.WriteReg(address, value);
			} else {
				if (address >= 0x4008 && address < 0x400c) {
					this._triangle.WriteReg(address, value);
				} else {
					if (address >= 0x400c && address <= 0x400f) {
						this._noise.WriteReg(address, value);
					} else {
						if (address === 0x4010) {
							this._dmc.WriteReg(address, value);
						} else {
							if (address === 0x4011) {
								this._dmc.WriteReg(address, value);
							} else {
								if (address === 0x4012) {
									this._dmc.WriteReg(address, value);
								} else {
									if (address === 0x4013) {
										this._dmc.WriteReg(address, value);
									} else {
										if (address === 0x4015) {
											this.UpdateChannelEnable(value);
											if (value !== 0 && this._init_counter > 0) {
												this._initing_hardware = true;
											}
											this._dmc.WriteReg(address, value);
										} else {
											if (address === 0x4017) {
												this._count_sequence = (value >> 7) & 1;
												this._master_frame_counter = 0;
												this._frame_irq_active = false;
												if (((value >> 6) & 0x1) === 0) {
													this._frame_irq_enabled = true;
												} else {
													this._frame_irq_enabled = false;
												}
												if (this._count_sequence === 0) {
													this._frame_irq_counter_max = 4;
													this._derived_frame_counter = 4;
												} else {
													this._frame_irq_counter_max = 5;
													this._derived_frame_counter = 0;
													this.FrameCounterTick();
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	},
	ResetCounter : function() {
		if (this._count_sequence === 0) {
			this._derived_frame_counter = 4;
		} else {
			this._derived_frame_counter = 0;
		}
	},
	UpdateChannelEnable : function(value) {
		this._channel_enable_value = value & 0xffff;
		this._square1.SetEnabled((value & 1) !== 0);
		this._square2.SetEnabled((value & 2) !== 0);
		this._triangle.SetEnabled((value & 4) !== 0);
		this._noise.SetEnabled((value & 8) !== 0);
		this._dmc.SetEnabled((value & 16) !== 0);
	},
	ClockFrameCounter : function(cycles) {
		if (this._init_counter > 0) {
			if (this._initing_hardware) {
				this._init_counter = this._init_counter - (cycles);
				if (this._init_counter <= 0) {
					this._initing_hardware = false;
				}
				return;
			}
		}
		cycles = cycles + (this._extra_cycles);
		let maxCycles = this._sample_timer_max - this._sample_timer;
		if (cycles << 10 > maxCycles) {
			this._extra_cycles = ((cycles << 10) - maxCycles) >> 10;
			cycles = cycles - (this._extra_cycles);
		} else {
			this._extra_cycles = 0;
		}
		let dmc = this._dmc;
		let triangle = this._triangle;
		let square1 = this._square1;
		let square2 = this._square2;
		let noise = this._noise;
		if (dmc._is_enabled) {
			dmc._shift_counter = dmc._shift_counter - (cycles << 3);
			while (dmc._shift_counter <= 0 && dmc._dma_frequency > 0) {
				dmc._shift_counter = dmc._shift_counter + (dmc._dma_frequency);
				dmc.ClockDmc();
			}
		}
		if (triangle._prog_timer_max > 0) {
			triangle._prog_timer_count = triangle._prog_timer_count - (cycles);
			while (triangle._prog_timer_count <= 0) {
				triangle._prog_timer_count = triangle._prog_timer_count + (triangle._prog_timer_max + 1);
				if (triangle._linear_counter > 0 && triangle._length_counter > 0) {
					++ triangle._triangle_counter;
					triangle._triangle_counter = triangle._triangle_counter & 0x1f;
					if (triangle._is_enabled) {
						if (triangle._triangle_counter >= 0x10) {
							triangle._sample_value = triangle._triangle_counter & 0xf;
						} else {
							triangle._sample_value = 0xf - (triangle._triangle_counter & 0xf);
						}
						triangle._sample_value = triangle._sample_value << 4;
					}
				}
			}
		}
		square1._prog_timer_count = square1._prog_timer_count - (cycles);
		if (square1._prog_timer_count <= 0) {
			square1._prog_timer_count = square1._prog_timer_count + ((square1._prog_timer_max + 1) << 1);
			++ square1._square_counter;
			square1._square_counter = square1._square_counter & 0x7;
			square1.UpdateSampleValue();
		}
		square2._prog_timer_count = square2._prog_timer_count - (cycles);
		if (square2._prog_timer_count <= 0) {
			square2._prog_timer_count = square2._prog_timer_count + ((square2._prog_timer_max + 1) << 1);
			++ square2._square_counter;
			square2._square_counter = square2._square_counter & 0x7;
			square2.UpdateSampleValue();
		}
		let acc_c = cycles;
		if (noise._prog_timer_count - acc_c > 0) {
			noise._prog_timer_count = noise._prog_timer_count - (acc_c);
			noise._acc_count = noise._acc_count + (acc_c);
			noise._acc_value = noise._acc_value + (acc_c * noise._sample_value);
		} else {
			while (acc_c > 0) {
				-- acc_c;
				-- noise._prog_timer_count;
				if (noise._prog_timer_count <= 0 && noise._prog_timer_max > 0) {
					noise._shift_reg = noise._shift_reg << 1;
					noise._tmp = ((noise._shift_reg << NESEmulator.ConditionExpr(noise._random_mode === 0, 1, 6)) ^ noise._shift_reg) & 0x8000;
					if (noise._tmp !== 0) {
						noise._shift_reg = noise._shift_reg | 0x01;
						noise._random_bit = 0;
						noise._sample_value = 0;
					} else {
						noise._random_bit = 1;
						if (noise._is_enabled && noise._length_counter > 0) {
							noise._sample_value = noise._master_volume;
						} else {
							noise._sample_value = 0;
						}
					}
					noise._prog_timer_count = noise._prog_timer_count + (noise._prog_timer_max);
				}
				noise._acc_value = noise._acc_value + (noise._sample_value);
				++ noise._acc_count;
			}
		}
		if (this._frame_irq_enabled && this._frame_irq_active) {
			this._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL);
		}
		this._master_frame_counter = this._master_frame_counter + (cycles << 1);
		if (this._master_frame_counter >= this._frame_time) {
			this._master_frame_counter = this._master_frame_counter - (this._frame_time);
			this.FrameCounterTick();
		}
		this.AccSample(cycles);
		this._sample_timer = this._sample_timer + (cycles << 10);
		if (this._sample_timer >= this._sample_timer_max) {
			this.Sample();
			this._sample_timer = this._sample_timer - (this._sample_timer_max);
		}
	},
	AccSample : function(cycles) {
		if (this._triangle._sample_condition) {
			this._tri_value = ALittle.Math_Floor((this._triangle._prog_timer_count << 4) / (this._triangle._prog_timer_max + 1));
			if (this._tri_value > 16) {
				this._tri_value = 16;
			}
			if (this._triangle._triangle_counter >= 16) {
				this._tri_value = 16 - this._tri_value;
			}
			this._tri_value = this._tri_value + (this._triangle._sample_value);
		}
		if (cycles === 2) {
			this._smp_triangle = this._smp_triangle + (this._tri_value << 1);
			this._smp_dmc = this._smp_dmc + (this._dmc._sample << 1);
			this._smp_square1 = this._smp_square1 + (this._square1._sample_value << 1);
			this._smp_square2 = this._smp_square2 + (this._square2._sample_value << 1);
			this._acc_count = this._acc_count + (2);
		} else {
			if (cycles === 4) {
				this._smp_triangle = this._smp_triangle + (this._tri_value << 2);
				this._smp_dmc = this._smp_dmc + (this._dmc._sample << 2);
				this._smp_square1 = this._smp_square1 + (this._square1._sample_value << 2);
				this._smp_square2 = this._smp_square2 + (this._square2._sample_value << 2);
				this._acc_count = this._acc_count + (4);
			} else {
				this._smp_triangle = this._smp_triangle + (cycles * this._tri_value);
				this._smp_dmc = this._smp_dmc + (cycles * this._dmc._sample);
				this._smp_square1 = this._smp_square1 + (cycles * this._square1._sample_value);
				this._smp_square2 = this._smp_square2 + (cycles * this._square2._sample_value);
				this._acc_count = this._acc_count + (cycles);
			}
		}
	},
	FrameCounterTick : function() {
		++ this._derived_frame_counter;
		if (this._derived_frame_counter >= this._frame_irq_counter_max) {
			this._derived_frame_counter = 0;
		}
		if (this._derived_frame_counter === 1 || this._derived_frame_counter === 3) {
			this._triangle.ClockLengthCounter();
			this._square1.ClockLengthCounter();
			this._square2.ClockLengthCounter();
			this._noise.ClockLengthCounter();
			this._square1.ClockSweep();
			this._square2.ClockSweep();
		}
		if (this._derived_frame_counter >= 0 && this._derived_frame_counter < 4) {
			this._square1.ClockEnvDecay();
			this._square2.ClockEnvDecay();
			this._noise.ClockEnvDecay();
			this._triangle.ClockLinearCounter();
		}
		if (this._derived_frame_counter === 3 && this._count_sequence === 0) {
			this._frame_irq_active = true;
		}
	},
	Sample : function() {
		if (this._acc_count > 0) {
			this._smp_square1 = this._smp_square1 << 4;
			this._smp_square1 = ALittle.Math_Floor(this._smp_square1 / this._acc_count);
			this._smp_square2 = this._smp_square2 << 4;
			this._smp_square2 = ALittle.Math_Floor(this._smp_square2 / this._acc_count);
			this._smp_triangle = ALittle.Math_Floor(this._smp_triangle / this._acc_count);
			this._smp_dmc = this._smp_dmc << 4;
			this._smp_dmc = ALittle.Math_Floor(this._smp_dmc / this._acc_count);
			this._acc_count = 0;
		} else {
			this._smp_square1 = this._square1._sample_value << 4;
			this._smp_square2 = this._square2._sample_value << 4;
			this._smp_triangle = this._triangle._sample_value;
			this._smp_dmc = this._dmc._sample << 4;
		}
		let smpNoise = ALittle.Math_Floor((this._noise._acc_value << 4) / this._noise._acc_count);
		this._noise._acc_value = smpNoise >> 4;
		this._noise._acc_count = 1;
		let sq_index = (this._smp_square1 * this._stereo_pos_l_square1 + this._smp_square2 * this._stereo_pos_l_square2) >> 8;
		let tnd_index = (3 * this._smp_triangle * this._stereo_pos_l_triangle + (smpNoise << 1) * this._stereo_pos_l_noise + this._smp_dmc * this._stereo_pos_l_dmc) >> 8;
		if (sq_index >= this._square_table_len) {
			sq_index = this._square_table_len - 1;
		}
		if (tnd_index >= this._tnd_table_len) {
			tnd_index = this._tnd_table_len - 1;
		}
		let sampleValueL = this._square_table.get(sq_index) + this._tnd_table.get(tnd_index) - this._dac_value;
		sq_index = (this._smp_square1 * this._stereo_pos_r_square1 + this._smp_square2 * this._stereo_pos_r_square2) >> 8;
		tnd_index = (3 * this._smp_triangle * this._stereo_pos_r_triangle + (smpNoise << 1) * this._stereo_pos_r_noise + this._smp_dmc * this._stereo_pos_r_dmc) >> 8;
		if (sq_index >= this._square_table_len) {
			sq_index = this._square_table_len - 1;
		}
		if (tnd_index >= this._tnd_table_len) {
			tnd_index = this._tnd_table_len - 1;
		}
		let sampleValueR = this._square_table.get(sq_index) + this._tnd_table.get(tnd_index) - this._dac_value;
		let smpDiffL = sampleValueL - this._prev_sample_l;
		this._prev_sample_l = this._prev_sample_l + (smpDiffL);
		this._smp_accum_l = this._smp_accum_l + (smpDiffL - (this._smp_accum_l >> 10));
		sampleValueL = this._smp_accum_l;
		let smpDiffR = sampleValueR - this._prev_sample_r;
		this._prev_sample_r = this._prev_sample_r + (smpDiffR);
		this._smp_accum_r = this._smp_accum_r + (smpDiffR - (this._smp_accum_r >> 10));
		sampleValueR = this._smp_accum_r;
		if (sampleValueL > this._max_sample) {
			this._max_sample = sampleValueL;
		}
		if (sampleValueL < this._min_sample) {
			this._min_sample = sampleValueL;
		}
		this._nes.OnAudioSample(sampleValueL / 32768, sampleValueR / 32768);
		this._smp_square1 = 0;
		this._smp_square2 = 0;
		this._smp_triangle = 0;
		this._smp_dmc = 0;
	},
	GetLengthMax : function(value) {
		return this._length_lookup.get(value >> 3);
	},
	GetDmcFrequency : function(value) {
		if (value >= 0 && value < 0x10) {
			return this._dmc_freq_lookup.get(value);
		}
		return 0;
	},
	GetNoiseWaveLength : function(value) {
		if (value >= 0 && value < 0x10) {
			return this._noise_wavelength_lookup.get(value);
		}
		return 0;
	},
	SetPanning : function(pos) {
		for (let i = 0; i < 5; i += 1) {
			this._panning.set(i, pos.get(i));
		}
		this.UpdateStereoPos();
	},
	SetMasterVolume : function(value) {
		if (value < 0) {
			value = 0;
		}
		if (value > 256) {
			value = 256;
		}
		this._master_volume = value;
		this.UpdateStereoPos();
	},
	UpdateStereoPos : function() {
		this._stereo_pos_l_square1 = (this._panning.get(0) * this._master_volume) >> 8;
		this._stereo_pos_l_square2 = (this._panning.get(1) * this._master_volume) >> 8;
		this._stereo_pos_l_triangle = (this._panning.get(2) * this._master_volume) >> 8;
		this._stereo_pos_l_noise = (this._panning.get(3) * this._master_volume) >> 8;
		this._stereo_pos_l_dmc = (this._panning.get(4) * this._master_volume) >> 8;
		this._stereo_pos_r_square1 = this._master_volume - this._stereo_pos_l_square1;
		this._stereo_pos_r_square2 = this._master_volume - this._stereo_pos_l_square2;
		this._stereo_pos_r_triangle = this._master_volume - this._stereo_pos_l_triangle;
		this._stereo_pos_r_noise = this._master_volume - this._stereo_pos_l_noise;
		this._stereo_pos_r_dmc = this._master_volume - this._stereo_pos_l_dmc;
	},
	InitLengthLookup : function() {
		let values = [0x0A, 0xFE, 0x14, 0x02, 0x28, 0x04, 0x50, 0x06, 0xA0, 0x08, 0x3C, 0x0A, 0x0E, 0x0C, 0x1A, 0x0E, 0x0C, 0x10, 0x18, 0x12, 0x30, 0x14, 0x60, 0x16, 0xC0, 0x18, 0x48, 0x1A, 0x10, 0x1C, 0x20, 0x1E];
		this._length_lookup = new Map();
		let ___OBJECT_2 = values;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			this._length_lookup.set(index - 1, value);
		}
	},
	InitDmcFrequencyLookup : function() {
		this._dmc_freq_lookup = new Map();
		this._dmc_freq_lookup.set(0x0, 0xd60);
		this._dmc_freq_lookup.set(0x1, 0xbe0);
		this._dmc_freq_lookup.set(0x2, 0xaa0);
		this._dmc_freq_lookup.set(0x3, 0xa00);
		this._dmc_freq_lookup.set(0x4, 0x8f0);
		this._dmc_freq_lookup.set(0x5, 0x7f0);
		this._dmc_freq_lookup.set(0x6, 0x710);
		this._dmc_freq_lookup.set(0x7, 0x6b0);
		this._dmc_freq_lookup.set(0x8, 0x5f0);
		this._dmc_freq_lookup.set(0x9, 0x500);
		this._dmc_freq_lookup.set(0xa, 0x470);
		this._dmc_freq_lookup.set(0xb, 0x400);
		this._dmc_freq_lookup.set(0xc, 0x350);
		this._dmc_freq_lookup.set(0xd, 0x2a0);
		this._dmc_freq_lookup.set(0xe, 0x240);
		this._dmc_freq_lookup.set(0xf, 0x1b0);
	},
	InitNoiseWavelengthLookup : function() {
		this._noise_wavelength_lookup = new Map();
		this._noise_wavelength_lookup.set(0x0, 0x004);
		this._noise_wavelength_lookup.set(0x1, 0x008);
		this._noise_wavelength_lookup.set(0x2, 0x010);
		this._noise_wavelength_lookup.set(0x3, 0x020);
		this._noise_wavelength_lookup.set(0x4, 0x040);
		this._noise_wavelength_lookup.set(0x5, 0x060);
		this._noise_wavelength_lookup.set(0x6, 0x080);
		this._noise_wavelength_lookup.set(0x7, 0x0a0);
		this._noise_wavelength_lookup.set(0x8, 0x0ca);
		this._noise_wavelength_lookup.set(0x9, 0x0fe);
		this._noise_wavelength_lookup.set(0xa, 0x17c);
		this._noise_wavelength_lookup.set(0xb, 0x1fc);
		this._noise_wavelength_lookup.set(0xc, 0x2fa);
		this._noise_wavelength_lookup.set(0xd, 0x3f8);
		this._noise_wavelength_lookup.set(0xe, 0x7f2);
		this._noise_wavelength_lookup.set(0xf, 0xfe4);
	},
	InitDACtables : function() {
		let max_sqr = 0;
		let max_tnd = 0;
		this._square_table = new Map();
		for (let i = 0; i < this._square_table_len; i += 1) {
			let value = 95.52 / (8128.0 / (i / 16.0) + 100.0);
			value = value * (0.98411);
			value = value * (50000.0);
			let ival = ALittle.Math_Floor(value);
			this._square_table.set(i, ival);
			if (ival > max_sqr) {
				max_sqr = ival;
			}
		}
		this._tnd_table = new Map();
		for (let i = 0; i < this._tnd_table_len; i += 1) {
			let value = 163.67 / (24329.0 / (i / 16.0) + 100.0);
			value = value * (0.98411);
			value = value * (50000.0);
			let ival = ALittle.Math_Floor(value);
			this._tnd_table.set(i, ival);
			if (ival > max_tnd) {
				max_tnd = ival;
			}
		}
		this._dac_range = max_sqr + max_tnd;
		this._dac_value = ALittle.Math_Floor(this._dac_range / 2);
	},
}, "NESEmulator.NesPAPU");

}