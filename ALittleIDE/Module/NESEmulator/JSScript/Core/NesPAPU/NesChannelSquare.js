{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelSquare = JavaScript.Class(undefined, {
	Ctor : function(papu, square1) {
		this._papu = papu;
		let values = [0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1];
		let ___OBJECT_1 = values;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this._duty_lookup.set(index - 1, value);
		}
		values = [1, -1, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0];
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
}