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
		this._extra_cycles = undefined;
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
		this._square_table_len = 32 * 16;
		this._tnd_table_len = 204 * 16;
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
		let frame_irq_enabled = 0;
		if (this._frame_irq_active && this._frame_irq_enabled) {
			frame_irq_enabled = 1;
		}
		tmp = tmp | (frame_irq_enabled << 6);
		tmp = tmp | (this._dmc.GetIrqStatus() << 7);
		this._frame_irq_active = false;
		this._dmc._irq_generated = false;
		return tmp & 0xffff;
	},
	WriteReg : function(address, value) {
}