{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesChannelDM = JavaScript.Class(undefined, {
	Ctor : function(papu) {
		this.MODE_NORMAL = 0;
		this.MODE_LOOP = 1;
		this.MODE_IRQ = 2;
		this._papu = papu;
		this._is_enabled = undefined;
		this._has_sample = undefined;
		this._irq_generated = false;
		this._play_mode = undefined;
		this._dma_frequency = undefined;
		this._dma_counter = undefined;
		this._delta_counter = undefined;
		this._play_start_address = undefined;
		this._play_address = undefined;
		this._play_length = undefined;
		this._play_length_counter = undefined;
		this._shift_counter = undefined;
		this._reg4012 = undefined;
		this._reg4013 = undefined;
		this._sample = undefined;
		this._dac_lsb = undefined;
		this._data = undefined;
		this.Reset();
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
			this._sample = NESEmulator.ConditionExpr(this._is_enabled, (this._delta_counter << 1) + this._dac_lsb, 0);
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
		if (this._play_length_counter === 0 && this._play_mode === this.MODE_LOOP) {
			this._play_address = this._play_start_address;
			this._play_length_counter = this._play_length;
		}
		if (this._play_length_counter > 0) {
			this.NextSample();
			if (this._play_length_counter === 0) {
				if (this._play_mode === this.MODE_IRQ) {
					this._irq_generated = true;
				}
			}
		}
	},
	NextSample : function() {
		this._data = this._papu._nes._mmap.Load(this._play_address);
		this._papu._nes._cpu.HaltCycles(4);
		-- this._play_length_counter;
		++ this._play_address;
		if (this._play_address > 0xffff) {
			this._play_address = 0x8000;
		}
		this._has_sample = true;
	},
	WriteReg : function(address, value) {
		if (address === 0x4010) {
			if (value >> 6 === 0) {
				this._play_mode = this.MODE_NORMAL;
			} else {
				if (((value >> 6) & 1) === 1) {
					this._play_mode = this.MODE_LOOP;
				} else {
					if (value >> 6 === 2) {
						this._play_mode = this.MODE_IRQ;
					}
				}
			}
			if ((value & 0x80) === 0) {
				this._irq_generated = false;
			}
			this._dma_frequency = this._papu.GetDmcFrequency(value & 0xf);
		} else {
			if (address === 0x4011) {
				this._delta_counter = (value >> 1) & 63;
				this._dac_lsb = value & 1;
				this._sample = (this._delta_counter << 1) + this._dac_lsb;
			} else {
				if (address === 0x4012) {
					this._play_start_address = (value << 6) | 0x0c000;
					this._play_address = this._play_start_address;
					this._reg4012 = value;
				} else {
					if (address === 0x4013) {
						this._play_length = (value << 4) + 1;
						this._play_length_counter = this._play_length;
						this._reg4013 = value;
					} else {
						if (address === 0x4015) {
							if (((value >> 4) & 1) === 0) {
								this._play_length_counter = 0;
							} else {
								this._play_address = this._play_start_address;
								this._play_length_counter = this._play_length;
							}
							this._irq_generated = false;
						}
					}
				}
			}
		}
	},
	SetEnabled : function(value) {
		if (!this._is_enabled && value) {
			this._play_length_counter = this._play_length;
		}
		this._is_enabled = value;
	},
	GetLengthStatus : function() {
		if (this._play_length_counter === 0 || !this._is_enabled) {
			return 0;
		}
		return 1;
	},
	GetIrqStatus : function() {
		if (this._irq_generated) {
			return 1;
		}
		return 0;
	},
}, "NESEmulator.NesChannelDM");

}