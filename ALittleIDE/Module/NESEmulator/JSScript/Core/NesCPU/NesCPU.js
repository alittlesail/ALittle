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
		let temp = undefined;
		let add = undefined;
		if (this._irq_requested) {
			temp = this._f_carry | (NESEmulator.ConditionExpr(this._f_zero === 0, 1, 0) << 1) | (this._f_interrupt << 2) | (this._f_decimal << 3) | (this._f_brk << 4) | (this._f_notused << 5) | (this._f_overflow << 6) | (this._f_sign << 7);
			this._reg_pc_new = this._reg_pc;
			this._f_interrupt_new = this._f_interrupt;
			if (this._irq_type === NESEmulator.NesCPUIRQ.IRQ_NORMAL) {
				if (this._f_interrupt === 0) {
					this.DoIrq(temp);
				}
			} else if (this._irq_type === NESEmulator.NesCPUIRQ.IRQ_NMI) {
				this.DoNonMaskableInterrupt(temp);
			} else if (this._irq_type === NESEmulator.NesCPUIRQ.IRQ_RESET) {
				this.DoResetInterrupt();
			}
			this._reg_pc = this._reg_pc_new;
			this._f_interrupt = this._f_interrupt_new;
			this._f_brk = this._f_brk_new;
			this._irq_requested = false;
		}
		let op = this._nes._mmap.Load(this._reg_pc + 1);
		let op_info = this._op_data._op_data.get(op);
		let cycle_count = op_info >> 24;
		let cycle_add = 0;
		let addr_mode = (op_info >> 8) & 0xff;
		let op_addr = this._reg_pc;
		this._reg_pc = this._reg_pc + ((op_info >> 16) & 0xff);
		let addr = 0;
		if (addr_mode === 0) {
			addr = this.Load(op_addr + 2);
		} else if (addr_mode === 1) {
			addr = this.Load(op_addr + 2);
			if (addr < 0x80) {
				addr = addr + (this._reg_pc);
			} else {
				addr = addr + (this._reg_pc - 256);
			}
		} else if (addr_mode === 2) {
		} else if (addr_mode === 3) {
			addr = this.Load16bit(op_addr + 2);
		} else if (addr_mode === 4) {
			addr = this._reg_acc;
		} else if (addr_mode === 5) {
			addr = this._reg_pc;
		} else if (addr_mode === 6) {
			addr = (this.Load(op_addr + 2) + this._reg_x) & 0xff;
		} else if (addr_mode === 7) {
			addr = (this.Load(op_addr + 2) + this._reg_y) & 0xff;
		} else if (addr_mode === 8) {
			addr = this.Load16bit(op_addr + 2);
			if ((addr & 0xff00) !== ((addr + this._reg_x) & 0xff00)) {
				cycle_add = 1;
			}
			addr = addr + (this._reg_x);
		} else if (addr_mode === 9) {
			addr = this.Load16bit(op_addr + 2);
			if ((addr & 0xff00) !== ((addr + this._reg_y) & 0xff00)) {
				cycle_add = 1;
			}
			addr = addr + (this._reg_y);
		} else if (addr_mode === 10) {
			addr = this.Load(op_addr + 2);
			if ((addr & 0xff00) !== ((addr + this._reg_x) & 0xff00)) {
				cycle_add = 1;
			}
			addr = addr + (this._reg_x);
			addr = addr & 0xff;
			addr = this.Load16bit(addr);
		} else if (addr_mode === 11) {
			addr = this.Load16bit(this.Load(op_addr + 2));
			if ((addr & 0xff00) !== ((addr + this._reg_y) & 0xff00)) {
				cycle_add = 1;
			}
			addr = addr + (this._reg_y);
		} else if (addr_mode === 12) {
			addr = this.Load16bit(op_addr + 2);
			if (addr < 0x1fff) {
				addr = this._mem.get(addr) + (this._mem.get((addr & 0xff00) | (((addr & 0xff) + 1) & 0xff)) << 8);
			} else {
				addr = this._nes._mmap.Load(addr) + (this._nes._mmap.Load((addr & 0xff00) | (((addr & 0xff) + 1) & 0xff)) << 8);
			}
		}
		addr = addr & 0xFFFF;
		let op_type = op_info & 0xFF;
		if (op_type === 0) {
			temp = this._reg_acc + this.Load(addr) + this._f_carry;
			if (((this._reg_acc ^ this.Load(addr)) & 0x80) === 0 && ((this._reg_acc ^ temp) & 0x80) !== 0) {
				this._f_overflow = 1;
			} else {
				this._f_overflow = 0;
			}
			this._f_carry = NESEmulator.ConditionExpr(temp > 255, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			this._reg_acc = temp & 255;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 1) {
			this._reg_acc = this._reg_acc & this.Load(addr);
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 2) {
			if (addr_mode === 4) {
				this._f_carry = (this._reg_acc >> 7) & 1;
				this._reg_acc = (this._reg_acc << 1) & 255;
				this._f_sign = (this._reg_acc >> 7) & 1;
				this._f_zero = this._reg_acc;
			} else {
				temp = this.Load(addr);
				this._f_carry = (temp >> 7) & 1;
				temp = (temp << 1) & 255;
				this._f_sign = (temp >> 7) & 1;
				this._f_zero = temp;
				this.Write(addr, temp);
			}
		} else if (op_type === 3) {
			if (this._f_carry === 0) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 4) {
			if (this._f_carry === 1) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 5) {
			if (this._f_zero === 0) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 6) {
			temp = this.Load(addr);
			this._f_sign = (temp >> 7) & 1;
			this._f_overflow = (temp >> 6) & 1;
			temp = temp & this._reg_acc;
			this._f_zero = temp;
		} else if (op_type === 7) {
			if (this._f_sign === 1) {
				++ cycle_count;
				this._reg_pc = addr;
			}
		} else if (op_type === 8) {
			if (this._f_zero !== 0) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 9) {
			if (this._f_sign === 0) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 10) {
			this._reg_pc = this._reg_pc + (2);
			this.Push((this._reg_pc >> 8) & 255);
			this.Push(this._reg_pc & 255);
			this._f_brk = 1;
			this.Push(this._f_carry | (NESEmulator.ConditionExpr(this._f_zero === 0, 1, 0) << 1) | (this._f_interrupt << 2) | (this._f_decimal << 3) | (this._f_brk << 4) | (this._f_notused << 5) | (this._f_overflow << 6) | (this._f_sign << 7));
			this._f_interrupt = 1;
			this._reg_pc = this.Load16bit(0xfffe);
			-- this._reg_pc;
		} else if (op_type === 11) {
			if (this._f_overflow === 0) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 12) {
			if (this._f_overflow === 1) {
				cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) !== (addr & 0xff00), 2, 1));
				this._reg_pc = addr;
			}
		} else if (op_type === 13) {
			this._f_carry = 0;
		} else if (op_type === 14) {
			this._f_decimal = 0;
		} else if (op_type === 15) {
			this._f_interrupt = 0;
		} else if (op_type === 16) {
			this._f_overflow = 0;
		} else if (op_type === 17) {
			temp = this._reg_acc - this.Load(addr);
			this._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 18) {
			temp = this._reg_x - this.Load(addr);
			this._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
		} else if (op_type === 19) {
			temp = this._reg_y - this.Load(addr);
			this._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
		} else if (op_type === 20) {
			temp = (this.Load(addr) - 1) & 0xff;
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp;
			this.Write(addr, temp);
		} else if (op_type === 21) {
			this._reg_x = (this._reg_x - 1) & 0xff;
			this._f_sign = (this._reg_x >> 7) & 1;
			this._f_zero = this._reg_x;
		} else if (op_type === 22) {
			this._reg_y = (this._reg_y - 1) & 0xff;
			this._f_sign = (this._reg_y >> 7) & 1;
			this._f_zero = this._reg_y;
		} else if (op_type === 23) {
			this._reg_acc = (this.Load(addr) ^ this._reg_acc) & 0xff;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 24) {
			temp = (this.Load(addr) + 1) & 0xff;
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp;
			this.Write(addr, temp & 0xff);
		} else if (op_type === 25) {
			this._reg_x = (this._reg_x + 1) & 0xff;
			this._f_sign = (this._reg_x >> 7) & 1;
			this._f_zero = this._reg_x;
		} else if (op_type === 26) {
			++ this._reg_y;
			this._reg_y = this._reg_y & 0xff;
			this._f_sign = (this._reg_y >> 7) & 1;
			this._f_zero = this._reg_y;
		} else if (op_type === 27) {
			this._reg_pc = addr - 1;
		} else if (op_type === 28) {
			this.Push((this._reg_pc >> 8) & 255);
			this.Push(this._reg_pc & 255);
			this._reg_pc = addr - 1;
		} else if (op_type === 29) {
			this._reg_acc = this.Load(addr);
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 30) {
			this._reg_x = this.Load(addr);
			this._f_sign = (this._reg_x >> 7) & 1;
			this._f_zero = this._reg_x;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 31) {
			this._reg_y = this.Load(addr);
			this._f_sign = (this._reg_y >> 7) & 1;
			this._f_zero = this._reg_y;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 32) {
			if (addr_mode === 4) {
				temp = this._reg_acc & 0xff;
				this._f_carry = temp & 1;
				temp = temp >> 1;
				this._reg_acc = temp;
			} else {
				temp = this.Load(addr) & 0xff;
				this._f_carry = temp & 1;
				temp = temp >> 1;
				this.Write(addr, temp);
			}
			this._f_sign = 0;
			this._f_zero = temp;
		} else if (op_type === 33) {
		} else if (op_type === 34) {
			temp = (this.Load(addr) | this._reg_acc) & 255;
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp;
			this._reg_acc = temp;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 35) {
			this.Push(this._reg_acc);
		} else if (op_type === 36) {
			this._f_brk = 1;
			this.Push(this._f_carry | (NESEmulator.ConditionExpr(this._f_zero === 0, 1, 0) << 1) | (this._f_interrupt << 2) | (this._f_decimal << 3) | (this._f_brk << 4) | (this._f_notused << 5) | (this._f_overflow << 6) | (this._f_sign << 7));
		} else if (op_type === 37) {
			this._reg_acc = this.Pull();
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
		} else if (op_type === 38) {
			temp = this.Pull();
			this._f_carry = temp & 1;
			this._f_zero = NESEmulator.ConditionExpr(((temp >> 1) & 1) === 1, 0, 1);
			this._f_interrupt = (temp >> 2) & 1;
			this._f_decimal = (temp >> 3) & 1;
			this._f_brk = (temp >> 4) & 1;
			this._f_notused = (temp >> 5) & 1;
			this._f_overflow = (temp >> 6) & 1;
			this._f_sign = (temp >> 7) & 1;
			this._f_notused = 1;
		} else if (op_type === 39) {
			if (addr_mode === 4) {
				temp = this._reg_acc;
				add = this._f_carry;
				this._f_carry = (temp >> 7) & 1;
				temp = ((temp << 1) & 0xff) + add;
				this._reg_acc = temp;
			} else {
				temp = this.Load(addr);
				add = this._f_carry;
				this._f_carry = (temp >> 7) & 1;
				temp = ((temp << 1) & 0xff) + add;
				this.Write(addr, temp);
			}
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp;
		} else if (op_type === 40) {
			if (addr_mode === 4) {
				add = this._f_carry << 7;
				this._f_carry = this._reg_acc & 1;
				temp = (this._reg_acc >> 1) + add;
				this._reg_acc = temp;
			} else {
				temp = this.Load(addr);
				add = this._f_carry << 7;
				this._f_carry = temp & 1;
				temp = (temp >> 1) + add;
				this.Write(addr, temp);
			}
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp;
		} else if (op_type === 41) {
			temp = this.Pull();
			this._f_carry = temp & 1;
			this._f_zero = NESEmulator.ConditionExpr(((temp >> 1) & 1) === 0, 1, 0);
			this._f_interrupt = (temp >> 2) & 1;
			this._f_decimal = (temp >> 3) & 1;
			this._f_brk = (temp >> 4) & 1;
			this._f_notused = (temp >> 5) & 1;
			this._f_overflow = (temp >> 6) & 1;
			this._f_sign = (temp >> 7) & 1;
			this._reg_pc = this.Pull();
			this._reg_pc = this._reg_pc + (this.Pull() << 8);
			if (this._reg_pc === 0xffff) {
				return undefined;
			}
			-- this._reg_pc;
			this._f_notused = 1;
		} else if (op_type === 42) {
			this._reg_pc = this.Pull();
			this._reg_pc = this._reg_pc + (this.Pull() << 8);
			if (this._reg_pc === 0xffff) {
				return undefined;
			}
		} else if (op_type === 43) {
			temp = this._reg_acc - this.Load(addr) - (1 - this._f_carry);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			if (((this._reg_acc ^ temp) & 0x80) !== 0 && ((this._reg_acc ^ this.Load(addr)) & 0x80) !== 0) {
				this._f_overflow = 1;
			} else {
				this._f_overflow = 0;
			}
			if (temp < 0) {
				this._f_carry = 0;
			} else {
				this._f_carry = 1;
			}
			this._reg_acc = temp & 0xff;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 44) {
			this._f_carry = 1;
		} else if (op_type === 45) {
			this._f_decimal = 1;
		} else if (op_type === 46) {
			this._f_interrupt = 1;
		} else if (op_type === 47) {
			this.Write(addr, this._reg_acc);
		} else if (op_type === 48) {
			this.Write(addr, this._reg_x);
		} else if (op_type === 49) {
			this.Write(addr, this._reg_y);
		} else if (op_type === 50) {
			this._reg_x = this._reg_acc;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
		} else if (op_type === 51) {
			this._reg_y = this._reg_acc;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
		} else if (op_type === 52) {
			this._reg_x = this._reg_sp - 0x0100;
			this._f_sign = (this._reg_sp >> 7) & 1;
			this._f_zero = this._reg_x;
		} else if (op_type === 53) {
			this._reg_acc = this._reg_x;
			this._f_sign = (this._reg_x >> 7) & 1;
			this._f_zero = this._reg_x;
		} else if (op_type === 54) {
			this._reg_sp = this._reg_x + 0x0100;
			this.StackWrap();
		} else if (op_type === 55) {
			this._reg_acc = this._reg_y;
			this._f_sign = (this._reg_y >> 7) & 1;
			this._f_zero = this._reg_y;
		} else if (op_type === 56) {
			temp = this._reg_acc & this.Load(addr);
			this._f_carry = temp & 1;
			this._f_zero = temp >> 1;
			this._reg_acc = this._f_zero;
			this._f_sign = 0;
		} else if (op_type === 57) {
			this._f_zero = this._reg_acc & this.Load(addr);
			this._reg_acc = this._f_zero;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_carry = this._f_sign;
		} else if (op_type === 58) {
			temp = this._reg_acc & this.Load(addr);
			this._f_zero = (temp >> 1) + (this._f_carry << 7);
			this._reg_acc = this._f_zero;
			this._f_sign = this._f_carry;
			this._f_carry = (temp >> 7) & 1;
			this._f_overflow = ((temp >> 7) ^ (temp >> 6)) & 1;
		} else if (op_type === 59) {
			temp = (this._reg_x & this._reg_acc) - this.Load(addr);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			if (((this._reg_x ^ temp) & 0x80) !== 0 && ((this._reg_x ^ this.Load(addr)) & 0x80) !== 0) {
				this._f_overflow = 1;
			} else {
				this._f_overflow = 0;
			}
			if (temp < 0) {
				this._f_carry = 0;
			} else {
				this._f_carry = 1;
			}
			this._reg_x = temp & 0xff;
		} else if (op_type === 60) {
			this._f_zero = this.Load(addr);
			this._reg_x = this._f_zero;
			this._reg_acc = this._reg_x;
			this._f_sign = (this._reg_acc >> 7) & 1;
			cycle_count = cycle_count + (cycle_add);
		} else if (op_type === 61) {
			this.Write(addr, this._reg_acc & this._reg_x);
		} else if (op_type === 62) {
			temp = (this.Load(addr) - 1) & 0xff;
			this.Write(addr, temp);
			temp = this._reg_acc - temp;
			this._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 63) {
			temp = (this.Load(addr) + 1) & 0xff;
			this.Write(addr, temp);
			temp = this._reg_acc - temp - (1 - this._f_carry);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			if (((this._reg_acc ^ temp) & 0x80) !== 0 && ((this._reg_acc ^ this.Load(addr)) & 0x80) !== 0) {
				this._f_overflow = 1;
			} else {
				this._f_overflow = 0;
			}
			this._f_carry = NESEmulator.ConditionExpr(temp < 0, 0, 1);
			this._reg_acc = temp & 0xff;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 64) {
			temp = this.Load(addr);
			add = this._f_carry;
			this._f_carry = (temp >> 7) & 1;
			temp = ((temp << 1) & 0xff) + add;
			this.Write(addr, temp);
			this._reg_acc = this._reg_acc & temp;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 65) {
			temp = this.Load(addr);
			add = this._f_carry << 7;
			this._f_carry = temp & 1;
			temp = (temp >> 1) + add;
			this.Write(addr, temp);
			temp = this._reg_acc + this.Load(addr) + this._f_carry;
			if (((this._reg_acc ^ this.Load(addr)) & 0x80) === 0 && ((this._reg_acc ^ temp) & 0x80) !== 0) {
				this._f_overflow = 1;
			} else {
				this._f_overflow = 0;
			}
			this._f_carry = NESEmulator.ConditionExpr(temp > 255, 1, 0);
			this._f_sign = (temp >> 7) & 1;
			this._f_zero = temp & 0xff;
			this._reg_acc = temp & 255;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 66) {
			temp = this.Load(addr);
			this._f_carry = (temp >> 7) & 1;
			temp = (temp << 1) & 255;
			this.Write(addr, temp);
			this._reg_acc = this._reg_acc | temp;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 67) {
			temp = this.Load(addr) & 0xff;
			this._f_carry = temp & 1;
			temp = temp >> 1;
			this.Write(addr, temp);
			this._reg_acc = this._reg_acc ^ temp;
			this._f_sign = (this._reg_acc >> 7) & 1;
			this._f_zero = this._reg_acc;
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else if (op_type === 68) {
		} else if (op_type === 69) {
			this.Load(addr);
			if (addr_mode !== 11) {
				cycle_count = cycle_count + (cycle_add);
			}
		} else {
			this._nes.Stop("Game crashed, invalid opcode at address $" + op_addr);
		}
		return cycle_count;
	},
	Load : function(addr) {
		if (addr < 0x2000) {
			return this._mem.get(addr & 0x7ff);
		} else {
			return this._nes._mmap.Load(addr);
		}
	},
	Load16bit : function(addr) {
		if (addr < 0x1fff) {
			return this._mem.get(addr & 0x7ff) | (this._mem.get((addr + 1) & 0x7ff) << 8);
		} else {
			return this._nes._mmap.Load(addr) | (this._nes._mmap.Load(addr + 1) << 8);
		}
	},
	Write : function(addr, value) {
		if (addr < 0x2000) {
			this._mem.set(addr & 0x7ff, value);
		} else {
			this._nes._mmap.Write(addr, value);
		}
	},
	RequestIrq : function(type) {
		if (this._irq_requested) {
			if (type === NESEmulator.NesCPUIRQ.IRQ_NORMAL) {
				return;
			}
		}
		this._irq_requested = true;
		this._irq_type = type;
	},
	Push : function(value) {
		this._nes._mmap.Write(this._reg_sp, value);
		-- this._reg_sp;
		this._reg_sp = 0x0100 | (this._reg_sp & 0xff);
	},
	StackWrap : function() {
		this._reg_sp = 0x0100 | (this._reg_sp & 0xff);
	},
	Pull : function() {
		++ this._reg_sp;
		this._reg_sp = 0x0100 | (this._reg_sp & 0xff);
		return this._nes._mmap.Load(this._reg_sp);
	},
	PageCrossed : function(addr1, addr2) {
		return (addr1 & 0xff00) !== (addr2 & 0xff00);
	},
	HaltCycles : function(cycles) {
		this._cycles_to_halt = this._cycles_to_halt + (cycles);
	},
	DoNonMaskableInterrupt : function(status) {
		if ((this._nes._mmap.Load(0x2000) & 128) !== 0) {
			++ this._reg_pc_new;
			this.Push((this._reg_pc_new >> 8) & 0xff);
			this.Push(this._reg_pc_new & 0xff);
			this.Push(status);
			this._reg_pc_new = this._nes._mmap.Load(0xfffa) | (this._nes._mmap.Load(0xfffb) << 8);
			-- this._reg_pc_new;
		}
	},
	DoResetInterrupt : function() {
		this._reg_pc_new = this._nes._mmap.Load(0xfffc) | (this._nes._mmap.Load(0xfffd) << 8);
		-- this._reg_pc_new;
	},
	DoIrq : function(status) {
		++ this._reg_pc_new;
		this.Push((this._reg_pc_new >> 8) & 0xff);
		this.Push(this._reg_pc_new & 0xff);
		this.Push(status);
		this._f_interrupt_new = 1;
		this._f_brk_new = 0;
		this._reg_pc_new = this._nes._mmap.Load(0xfffe) | (this._nes._mmap.Load(0xffff) << 8);
		-- this._reg_pc_new;
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