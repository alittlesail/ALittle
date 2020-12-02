{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesCPUIRQ = {
	IRQ_NORMAL : 0,
	IRQ_NMI : 1,
	IRQ_RESET : 2,
}

NESEmulator.NesCPU = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._mem_len = 0x10000;
		this._nes = nes;
	},
	Reset : function() {
		this._mem = [];
		for (let i = 0; i < this._mem_len; i += 1) {
			this._mem[i /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0;
		}
		for (let i = 0; i < 0x2000; i += 1) {
			this._mem[i /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0xff;
		}
		for (let p = 0; p < 4; p += 1) {
			let j = p * 0x800;
			this._mem[j + 0x008 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0xf7;
			this._mem[j + 0x009 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0xef;
			this._mem[j + 0x00a /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0xdf;
			this._mem[j + 0x00f /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0xbf;
		}
		for (let k = 0x2001; k < this._mem_len; k += 1) {
			this._mem[k /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0;
		}
		this._reg_acc = 0;
		this._reg_x = 0;
		this._reg_y = 0;
		this._reg_sp = 0x01ff;
		this._reg_pc = 0x8000 - 1;
		this._reg_pc_new = 0x8000 - 1;
		this._reg_status = 0x28;
		this.SetStatus(0x28);
		this._f_carry = 0;
		this._f_decimal = 0;
		this._f_interrupt = 1;
		this._f_interrupt_new = 1;
		this._f_overflow = 0;
		this._f_sign = 0;
		this._f_zero = 1;
		this._f_notused = 1;
		this._f_notused_new = 1;
		this._f_brk = 1;
		this._f_brk_new = 1;
	},
	GetStatus : function() {
		return this._f_carry | (this._f_zero << 1) | (this._f_interrupt << 2) | (this._f_decimal << 3) | (this._f_brk << 4) | (this._f_notused << 5) | (this._f_overflow << 6) | (this._f_sign << 7);
	},
	SetStatus : function(st) {
		this._f_carry = st & 1;
		this._f_zero = (st >> 1) & 1;
		this._f_interrupt = (st >> 2) & 1;
		this._f_decimal = (st >> 3) & 1;
		this._f_brk = (st >> 4) & 1;
		this._f_notused = (st >> 5) & 1;
		this._f_overflow = (st >> 6) & 1;
		this._f_sign = (st >> 7) & 1;
	},
}, "NESEmulator.NesCPU");

}