{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelNoise = JavaScript.Class(undefined, {
	Ctor : function(papu) {
		this._papu = papu;
		this._is_enabled = undefined;
		this._env_decay_disable = undefined;
		this._env_decay_loop_enable = undefined;
		this._length_counter_enable = undefined;
		this._env_reset = undefined;
		this._shift_now = undefined;
		this._length_counter = undefined;
		this._prog_timer_count = undefined;
		this._prog_timer_max = undefined;
		this._env_decay_rate = undefined;
		this._env_decay_counter = undefined;
		this._env_volume = undefined;
		this._master_volume = undefined;
		this._shift_reg = 1 << 14;
		this._random_bit = undefined;
		this._random_mode = undefined;
		this._sample_value = undefined;
		this._acc_value = 0;
		this._acc_count = 1;
		this._tmp = undefined;
		this.Reset();
	},
	Reset : function() {
		this._prog_timer_count = 0;
		this._prog_timer_max = 0;
		this._is_enabled = false;
		this._length_counter = 0;
		this._length_counter_enable = false;
		this._env_decay_disable = false;
		this._env_decay_loop_enable = false;
		this._shift_now = false;
		this._env_decay_rate = 0;
		this._env_decay_counter = 0;
		this._env_volume = 0;
		this._master_volume = 0;
		this._shift_reg = 1;
		this._random_bit = 0;
		this._random_mode = 0;
		this._sample_value = 0;
		this._tmp = 0;
	},
	ClockLengthCounter : function() {
		if (this._length_counter_enable && this._length_counter > 0) {
			-- this._length_counter;
			if (this._length_counter === 0) {
				this.UpdateSampleValue();
			}
		}
	},
	ClockEnvDecay : function() {
		if (this._env_reset) {
			this._env_reset = false;
			this._env_decay_counter = this._env_decay_rate + 1;
			this._env_volume = 0xf;
		} else {
			-- this._env_decay_counter;
			if (this._env_decay_counter <= 0) {
				this._env_decay_counter = this._env_decay_rate + 1;
				if (this._env_volume > 0) {
					-- this._env_volume;
				} else {
					this._env_volume = NESEmulator.ConditionExpr(this._env_decay_loop_enable, 0xf, 0);
				}
			}
		}
		if (this._env_decay_disable) {
			this._master_volume = this._env_decay_rate;
		} else {
			this._master_volume = this._env_volume;
		}
		this.UpdateSampleValue();
	},
	UpdateSampleValue : function() {
		if (this._is_enabled && this._length_counter > 0) {
			this._sample_value = this._random_bit * this._master_volume;
		}
	},
	WriteReg : function(address, value) {
		if (address === 0x400c) {
			this._env_decay_disable = (value & 0x10) !== 0;
			this._env_decay_rate = value & 0xf;
			this._env_decay_loop_enable = (value & 0x20) !== 0;
			this._length_counter_enable = (value & 0x20) === 0;
			if (this._env_decay_disable) {
				this._master_volume = this._env_decay_rate;
			} else {
				this._master_volume = this._env_volume;
			}
		} else {
			if (address === 0x400e) {
				this._prog_timer_max = this._papu.GetNoiseWaveLength(value & 0xf);
				this._random_mode = value >> 7;
			} else {
				if (address === 0x400f) {
					this._length_counter = this._papu.GetLengthMax(value & 248);
					this._env_reset = true;
				}
			}
		}
	},
	SetEnabled : function(value) {
		this._is_enabled = value;
		if (!value) {
			this._length_counter = 0;
		}
		this.UpdateSampleValue();
	},
	GetLengthStatus : function() {
		if (this._length_counter === 0 || !this._is_enabled) {
			return 0;
		}
		return 1;
	},
}, "NESEmulator.NesChannelNoise");

}