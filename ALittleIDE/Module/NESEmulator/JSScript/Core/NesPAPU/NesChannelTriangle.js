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
		if (this._length_counter_enable && this._length_counter > 0) {
			-- this._length_counter;
			if (this._length_counter === 0) {
				this.UpdateSampleCondition();
			}
		}
	},
	ClockLinearCounter : function() {
		if (this._lc_halt) {
			this._linear_counter = this._lc_load_value;
			this.UpdateSampleCondition();
		} else {
			if (this._linear_counter > 0) {
				-- this._linear_counter;
				this.UpdateSampleCondition();
			}
		}
		if (!this._lc_control) {
			this._lc_halt = false;
		}
	},
	GetLengthStatus : function() {
		if (this._length_counter === 0 || !this._is_enabled) {
			return 0;
		}
		return 1;
	},
	ReadReg : function(address) {
		return 0;
	},
	WriteReg : function(address, value) {
		if (address === 0x4008) {
			this._lc_control = (value & 0x80) !== 0;
			this._lc_load_value = value & 0x7f;
			this._length_counter_enable = !this._lc_control;
		} else {
			if (address === 0x400a) {
				this._prog_timer_max = this._prog_timer_max & 0x700;
				this._prog_timer_max = this._prog_timer_max | value;
			} else {
				if (address === 0x400b) {
					this._prog_timer_max = this._prog_timer_max & 0xff;
					this._prog_timer_max = this._prog_timer_max | ((value & 0x07) << 8);
					this._length_counter = this._papu.GetLengthMax(value & 0xf8);
					this._lc_halt = true;
				}
			}
		}
		this.UpdateSampleCondition();
	},
	ClockProgrammableTimer : function(cycles) {
		if (this._prog_timer_max > 0) {
			this._prog_timer_count = this._prog_timer_count + (cycles);
			while (this._prog_timer_max > 0 && this._prog_timer_count >= this._prog_timer_max) {
				this._prog_timer_count = this._prog_timer_count - (this._prog_timer_max);
				if (this._is_enabled && this._length_counter > 0 && this._linear_counter > 0) {
					this.ClockTriangleGenerator();
				}
			}
		}
	},
	ClockTriangleGenerator : function() {
		++ this._triangle_counter;
		this._triangle_counter = this._triangle_counter & 0x1f;
	},
	SetEnabled : function(value) {
		this._is_enabled = value;
		if (!value) {
			this._length_counter = 0;
		}
		this.UpdateSampleCondition();
	},
	UpdateSampleCondition : function() {
		this._sample_condition = this._is_enabled && this._prog_timer_max > 7 && this._linear_counter > 0 && this._length_counter > 0;
	},
}, "NESEmulator.NesChannelTriangle");

}