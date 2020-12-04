{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelSquare = JavaScript.Class(undefined, {
	Ctor : function(papu, square1) {
		this._papu = papu;
		let values = [0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1];
		this._duty_lookup = new Map();
		let ___OBJECT_1 = values;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this._duty_lookup.set(index - 1, value);
		}
		values = [1, -1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0];
		this._imp_lookup = new Map();
		let ___OBJECT_2 = values;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			this._imp_lookup.set(index - 1, value);
		}
		this._sqr1 = square1;
		this._is_enabled = undefined;
		this._length_counter_enable = undefined;
		this._sweep_active = undefined;
		this._env_decay_disable = undefined;
		this._env_decay_loop_enable = undefined;
		this._env_reset = undefined;
		this._sweep_carry = undefined;
		this._update_sweep_period = undefined;
		this._prog_timer_count = undefined;
		this._prog_timer_max = undefined;
		this._length_counter = undefined;
		this._square_counter = undefined;
		this._sweep_counter = undefined;
		this._sweep_counter_max = undefined;
		this._sweep_mode = undefined;
		this._sweep_shift_amount = undefined;
		this._env_decay_rate = undefined;
		this._env_decay_counter = undefined;
		this._env_volume = undefined;
		this._master_volume = undefined;
		this._duty_mode = undefined;
		this._sweep_result = undefined;
		this._sample_value = undefined;
		this._vol = undefined;
		this.Reset();
	},
	Reset : function() {
		this._prog_timer_count = 0;
		this._prog_timer_max = 0;
		this._length_counter = 0;
		this._square_counter = 0;
		this._sweep_counter = 0;
		this._sweep_counter_max = 0;
		this._sweep_mode = 0;
		this._sweep_shift_amount = 0;
		this._env_decay_rate = 0;
		this._env_decay_counter = 0;
		this._env_volume = 0;
		this._master_volume = 0;
		this._duty_mode = 0;
		this._vol = 0;
		this._is_enabled = false;
		this._length_counter_enable = false;
		this._sweep_active = false;
		this._sweep_carry = false;
		this._env_decay_disable = false;
		this._env_decay_loop_enable = false;
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
	ClockSweep : function() {
		-- this._sweep_counter;
		if (this._sweep_counter <= 0) {
			this._sweep_counter = this._sweep_counter_max + 1;
			if (this._sweep_active && this._sweep_shift_amount > 0 && this._prog_timer_max > 7) {
				this._sweep_carry = false;
				if (this._sweep_mode === 0) {
					this._prog_timer_max = this._prog_timer_max + (this._prog_timer_max >> this._sweep_shift_amount);
					if (this._prog_timer_max > 4095) {
						this._prog_timer_max = 4095;
						this._sweep_carry = true;
					}
				} else {
					this._prog_timer_max = this._prog_timer_max - ((this._prog_timer_max >> this._sweep_shift_amount) - NESEmulator.ConditionExpr(this._sqr1, 1, 0));
				}
			}
		}
		if (this._update_sweep_period) {
			this._update_sweep_period = false;
			this._sweep_counter = this._sweep_counter_max + 1;
		}
	},
	UpdateSampleValue : function() {
		if (this._is_enabled && this._length_counter > 0 && this._prog_timer_max > 7) {
			if (this._sweep_mode === 0 && this._prog_timer_max + (this._prog_timer_max >> this._sweep_shift_amount) > 4095) {
				this._sample_value = 0;
			} else {
				this._sample_value = this._master_volume * this._duty_lookup.get((this._duty_mode << 3) + this._square_counter);
			}
		} else {
			this._sample_value = 0;
		}
	},
	WriteReg : function(address, value) {
		let addrAdd = 4;
		if (this._sqr1) {
			addrAdd = 0;
		}
		if (address === 0x4000 + addrAdd) {
			this._env_decay_disable = (value & 0x10) !== 0;
			this._env_decay_rate = value & 0xf;
			this._env_decay_loop_enable = (value & 0x20) !== 0;
			this._duty_mode = (value >> 6) & 0x3;
			this._length_counter_enable = (value & 0x20) === 0;
			if (this._env_decay_disable) {
				this._master_volume = this._env_decay_rate;
			} else {
				this._master_volume = this._env_volume;
			}
			this.UpdateSampleValue();
		} else {
			if (address === 0x4001 + addrAdd) {
				this._sweep_active = (value & 0x80) !== 0;
				this._sweep_counter_max = (value >> 4) & 7;
				this._sweep_mode = (value >> 3) & 1;
				this._sweep_shift_amount = value & 7;
				this._update_sweep_period = true;
			} else {
				if (address === 0x4002 + addrAdd) {
					this._prog_timer_max = this._prog_timer_max & 0x700;
					this._prog_timer_max = this._prog_timer_max | value;
				} else {
					if (address === 0x4003 + addrAdd) {
						this._prog_timer_max = this._prog_timer_max & 0xff;
						this._prog_timer_max = this._prog_timer_max | ((value & 0x7) << 8);
						if (this._is_enabled) {
							this._length_counter = this._papu.GetLengthMax(value & 0xf8);
						}
						this._env_reset = true;
					}
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
}, "NESEmulator.NesChannelSquare");

}