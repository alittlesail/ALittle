{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelDM = JavaScript.Class(undefined, {
	Ctor : function(papu) {
		this.MODE_NORMAL = 0;
		this.MODE_LOOP = 1;
		this.MODE_IRQ = 2;
		this._papu = papu;
	},
	Reset : function() {
		this._is_enabled = false;
		this._irq_generated = false;
		this._play_mode = this.MODE_NORMAL;
		this._dma_frequency = 0;
		this._dma_counter = 0;
		this._delta_counter = 0;
		this._play_start_address = 0;
		this._play_address = 0;
		this._play_length = 0;
		this._play_length_counter = 0;
		this._sample = 0;
		this._dac_lsb = 0;
		this._shift_counter = 0;
		this._reg4012 = 0;
		this._reg4013 = 0;
		this._data = 0;
	},
	ClockDmc : function() {
		if (this._has_sample) {
			if ((this._data & 1) === 0) {
				if (this._delta_counter > 0) {
					-- this._delta_counter;
				}
			} else {
				if (this._delta_counter < 63) {
					++ this._delta_counter;
				}
			}
			this._sample = 0;
			if (this._is_enabled) {
				this._sample = (this._delta_counter << 1) + this._dac_lsb;
			}
			this._data = this._data >> 1;
		}
		-- this._dma_counter;
		if (this._dma_counter <= 0) {
			this._has_sample = false;
			this.EndOfSample();
			this._dma_counter = 8;
		}
		if (this._irq_generated) {
			this._papu._nes._cpu.RequestIrq(NESEmulator.NesCPUIRQ.IRQ_NORMAL);
		}
	},
	EndOfSample : function() {
}