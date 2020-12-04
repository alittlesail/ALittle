{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.CPU_MEM_LEN = 0x10000;
NESEmulator.NesCPUIRQ = {
	IRQ_NORMAL : 0,
	IRQ_NMI : 1,
	IRQ_RESET : 2,
}

NESEmulator.NesCPU = JavaScript.Class(undefined, {
	Ctor : function(nes) {
		this._cycles_to_halt = 0;
		this._crash = false;
		this._irq_requested = false;
		this._nes = nes;
		this.Reset();
	},
	Reset : function() {
		this._mem = new Map();
		for (let i = 0; i < NESEmulator.CPU_MEM_LEN; i += 1) {
			this._mem.set(i, 0);
		}
		for (let i = 0; i < 0x2000; i += 1) {
			this._mem.set(i, 0xff);
		}
		for (let p = 0; p < 4; p += 1) {
			let j = p * 0x800;
			this._mem.set(j + 0x008, 0xf7);
			this._mem.set(j + 0x009, 0xef);
			this._mem.set(j + 0x00a, 0xdf);
			this._mem.set(j + 0x00f, 0xbf);
		}
		for (let k = 0x2001; k < NESEmulator.CPU_MEM_LEN; k += 1) {
			this._mem.set(k, 0);
		}
		this._reg_acc = 0;
		this._reg_x = 0;
		this._reg_y = 0;
		this._reg_sp = 0x01ff;
		this._reg_pc = 0x8000 - 1;
		this._reg_pc_new = this._reg_pc;
		this._reg_status = 0x28;
		this.SetStatus(this._reg_status);
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
		this._op_data = ALittle.NewObject(NESEmulator.NesCPUOpData);
		this._cycles_to_halt = 0;
		this._crash = false;
		this._irq_requested = false;
		this._irq_type = undefined;
	},
	Emulate : function() {
}