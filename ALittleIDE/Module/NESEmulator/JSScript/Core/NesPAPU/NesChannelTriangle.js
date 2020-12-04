{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelTriangle = JavaScript.Class(undefined, {
	Ctor : function(papu) {
		this._papu = papu;
		this._is_enabled = undefined;
		this._sample_condition = undefined;
		this._length_counter_enable = undefined;
		this._lc_halt = undefined;
		this._lc_control = undefined;
		this._prog_timer_count = undefined;
		this._prog_timer_max = undefined;
		this._triangle_counter = undefined;
		this._length_counter = undefined;
		this._linear_counter = undefined;
		this._lc_load_value = undefined;
		this._sample_value = undefined;
		this._tmp = undefined;
		this.Reset();
	},
	Reset : function() {
		this._prog_timer_count = 0;
		this._prog_timer_max = 0;
		this._triangle_counter = 0;
		this._is_enabled = false;
		this._sample_condition = false;
		this._length_counter = 0;
		this._length_counter_enable = false;
		this._linear_counter = 0;
		this._lc_load_value = 0;
		this._lc_halt = true;
		this._lc_control = false;
		this._tmp = 0;
		this._sample_value = 0xf;
	},
	ClockLengthCounter : function() {
}