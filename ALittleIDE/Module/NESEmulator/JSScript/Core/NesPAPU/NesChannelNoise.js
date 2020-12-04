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
}