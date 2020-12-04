-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


NESEmulator.CPU_MEM_LEN = 0x10000
NESEmulator.NesCPUIRQ = {
	IRQ_NORMAL = 0,
	IRQ_NMI = 1,
	IRQ_RESET = 2,
}

NESEmulator.NesCPU = Lua.Class(nil, "NESEmulator.NesCPU")

function NESEmulator.NesCPU:Ctor(nes)
	___rawset(self, "_cycles_to_halt", 0)
	___rawset(self, "_crash", false)
	___rawset(self, "_irq_requested", false)
	___rawset(self, "_nes", nes)
	self:Reset()
end

function NESEmulator.NesCPU:Reset()
	self._mem = {}
	local i = 0
	while true do
		if not(i < NESEmulator.CPU_MEM_LEN) then break end
		self._mem[i] = 0
		i = i+(1)
	end
	local i = 0
	while true do
		if not(i < 0x2000) then break end
		self._mem[i] = 0xff
		i = i+(1)
	end
	local p = 0
	while true do
		if not(p < 4) then break end
		local j = p * 0x800
		self._mem[j + 0x008] = 0xf7
		self._mem[j + 0x009] = 0xef
		self._mem[j + 0x00a] = 0xdf
		self._mem[j + 0x00f] = 0xbf
		p = p+(1)
	end
	local k = 0x2001
	while true do
		if not(k < NESEmulator.CPU_MEM_LEN) then break end
		self._mem[k] = 0
		k = k+(1)
	end
	self._reg_acc = 0
	self._reg_x = 0
	self._reg_y = 0
	self._reg_sp = 0x01ff
	self._reg_pc = 0x8000 - 1
	self._reg_pc_new = self._reg_pc
	self._reg_status = 0x28
	self:SetStatus(self._reg_status)
	self._f_carry = 0
	self._f_decimal = 0
	self._f_interrupt = 1
	self._f_interrupt_new = 1
	self._f_overflow = 0
	self._f_sign = 0
	self._f_zero = 1
	self._f_notused = 1
	self._f_notused_new = 1
	self._f_brk = 1
	self._f_brk_new = 1
	self._op_data = NESEmulator.NesCPUOpData()
	self._cycles_to_halt = 0
	self._crash = false
	self._irq_requested = false
	self._irq_type = nil
end

function NESEmulator.NesCPU:Emulate()
	local temp = nil
	local add = nil
	if self._irq_requested then
		temp = self._f_carry | (NESEmulator.ConditionExpr(self._f_zero == 0, 1, 0) << 1) | (self._f_interrupt << 2) | (self._f_decimal << 3) | (self._f_brk << 4) | (self._f_notused << 5) | (self._f_overflow << 6) | (self._f_sign << 7)
		self._reg_pc_new = self._reg_pc
		self._f_interrupt_new = self._f_interrupt
		if self._irq_type == NESEmulator.NesCPUIRQ.IRQ_NORMAL then
			if self._f_interrupt == 0 then
				self:DoIrq(temp)
			end
		elseif self._irq_type == NESEmulator.NesCPUIRQ.IRQ_NMI then
			self:DoNonMaskableInterrupt(temp)
		elseif self._irq_type == NESEmulator.NesCPUIRQ.IRQ_RESET then
			self:DoResetInterrupt()
		end
		self._reg_pc = self._reg_pc_new
		self._f_interrupt = self._f_interrupt_new
		self._f_brk = self._f_brk_new
		self._irq_requested = false
	end
	local op = self._nes._mmap:Load(self._reg_pc + 1)
	local op_info = self._op_data._op_data[op]
	local cycle_count = op_info >> 24
	local cycle_add = 0
	local addr_mode = (op_info >> 8) & 0xff
	local op_addr = self._reg_pc
	self._reg_pc = self._reg_pc + ((op_info >> 16) & 0xff)
	local addr = 0
	if addr_mode == 0 then
		addr = self:Load(op_addr + 2)
	elseif addr_mode == 1 then
		addr = self:Load(op_addr + 2)
		if addr < 0x80 then
			addr = addr + (self._reg_pc)
		else
			addr = addr + (self._reg_pc - 256)
		end
	elseif addr_mode == 2 then
	elseif addr_mode == 3 then
		addr = self:Load16bit(op_addr + 2)
	elseif addr_mode == 4 then
		addr = self._reg_acc
	elseif addr_mode == 5 then
		addr = self._reg_pc
	elseif addr_mode == 6 then
		addr = (self:Load(op_addr + 2) + self._reg_x) & 0xff
	elseif addr_mode == 7 then
		addr = (self:Load(op_addr + 2) + self._reg_y) & 0xff
	elseif addr_mode == 8 then
		addr = self:Load16bit(op_addr + 2)
		if (addr & 0xff00) ~= ((addr + self._reg_x) & 0xff00) then
			cycle_add = 1
		end
		addr = addr + (self._reg_x)
	elseif addr_mode == 9 then
		addr = self:Load16bit(op_addr + 2)
		if (addr & 0xff00) ~= ((addr + self._reg_y) & 0xff00) then
			cycle_add = 1
		end
		addr = addr + (self._reg_y)
	elseif addr_mode == 10 then
		addr = self:Load(op_addr + 2)
		if (addr & 0xff00) ~= ((addr + self._reg_x) & 0xff00) then
			cycle_add = 1
		end
		addr = addr + (self._reg_x)
		addr = addr & 0xff
		addr = self:Load16bit(addr)
	elseif addr_mode == 11 then
		addr = self:Load16bit(self:Load(op_addr + 2))
		if (addr & 0xff00) ~= ((addr + self._reg_y) & 0xff00) then
			cycle_add = 1
		end
		addr = addr + (self._reg_y)
	elseif addr_mode == 12 then
		addr = self:Load16bit(op_addr + 2)
		if addr < 0x1fff then
			addr = self._mem[addr] + (self._mem[(addr & 0xff00) | (((addr & 0xff) + 1) & 0xff)] << 8)
		else
			addr = self._nes._mmap:Load(addr) + (self._nes._mmap:Load((addr & 0xff00) | (((addr & 0xff) + 1) & 0xff)) << 8)
		end
	end
	addr = addr & 0xFFFF
	local op_type = op_info & 0xFF
	if op_type == 0 then
		temp = self._reg_acc + self:Load(addr) + self._f_carry
		if ((self._reg_acc ~ self:Load(addr)) & 0x80) == 0 and ((self._reg_acc ~ temp) & 0x80) ~= 0 then
			self._f_overflow = 1
		else
			self._f_overflow = 0
		end
		self._f_carry = NESEmulator.ConditionExpr(temp > 255, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		self._reg_acc = temp & 255
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 1 then
		self._reg_acc = self._reg_acc & self:Load(addr)
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 2 then
		if addr_mode == 4 then
			self._f_carry = (self._reg_acc >> 7) & 1
			self._reg_acc = (self._reg_acc << 1) & 255
			self._f_sign = (self._reg_acc >> 7) & 1
			self._f_zero = self._reg_acc
		else
			temp = self:Load(addr)
			self._f_carry = (temp >> 7) & 1
			temp = (temp << 1) & 255
			self._f_sign = (temp >> 7) & 1
			self._f_zero = temp
			self:Write(addr, temp)
		end
	elseif op_type == 3 then
		if self._f_carry == 0 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 4 then
		if self._f_carry == 1 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 5 then
		if self._f_zero == 0 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 6 then
		temp = self:Load(addr)
		self._f_sign = (temp >> 7) & 1
		self._f_overflow = (temp >> 6) & 1
		temp = temp & self._reg_acc
		self._f_zero = temp
	elseif op_type == 7 then
		if self._f_sign == 1 then
			cycle_count = cycle_count + 1
			self._reg_pc = addr
		end
	elseif op_type == 8 then
		if self._f_zero ~= 0 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 9 then
		if self._f_sign == 0 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 10 then
		self._reg_pc = self._reg_pc + (2)
		self:Push((self._reg_pc >> 8) & 255)
		self:Push(self._reg_pc & 255)
		self._f_brk = 1
		self:Push(self._f_carry | (NESEmulator.ConditionExpr(self._f_zero == 0, 1, 0) << 1) | (self._f_interrupt << 2) | (self._f_decimal << 3) | (self._f_brk << 4) | (self._f_notused << 5) | (self._f_overflow << 6) | (self._f_sign << 7))
		self._f_interrupt = 1
		self._reg_pc = self:Load16bit(0xfffe)
		self._reg_pc = self._reg_pc - 1
	elseif op_type == 11 then
		if self._f_overflow == 0 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 12 then
		if self._f_overflow == 1 then
			cycle_count = cycle_count + (NESEmulator.ConditionExpr((op_addr & 0xff00) ~= (addr & 0xff00), 2, 1))
			self._reg_pc = addr
		end
	elseif op_type == 13 then
		self._f_carry = 0
	elseif op_type == 14 then
		self._f_decimal = 0
	elseif op_type == 15 then
		self._f_interrupt = 0
	elseif op_type == 16 then
		self._f_overflow = 0
	elseif op_type == 17 then
		temp = self._reg_acc - self:Load(addr)
		self._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 18 then
		temp = self._reg_x - self:Load(addr)
		self._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
	elseif op_type == 19 then
		temp = self._reg_y - self:Load(addr)
		self._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
	elseif op_type == 20 then
		temp = (self:Load(addr) - 1) & 0xff
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp
		self:Write(addr, temp)
	elseif op_type == 21 then
		self._reg_x = (self._reg_x - 1) & 0xff
		self._f_sign = (self._reg_x >> 7) & 1
		self._f_zero = self._reg_x
	elseif op_type == 22 then
		self._reg_y = (self._reg_y - 1) & 0xff
		self._f_sign = (self._reg_y >> 7) & 1
		self._f_zero = self._reg_y
	elseif op_type == 23 then
		self._reg_acc = (self:Load(addr) ~ self._reg_acc) & 0xff
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 24 then
		temp = (self:Load(addr) + 1) & 0xff
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp
		self:Write(addr, temp & 0xff)
	elseif op_type == 25 then
		self._reg_x = (self._reg_x + 1) & 0xff
		self._f_sign = (self._reg_x >> 7) & 1
		self._f_zero = self._reg_x
	elseif op_type == 26 then
		self._reg_y = self._reg_y + 1
		self._reg_y = self._reg_y & 0xff
		self._f_sign = (self._reg_y >> 7) & 1
		self._f_zero = self._reg_y
	elseif op_type == 27 then
		self._reg_pc = addr - 1
	elseif op_type == 28 then
		self:Push((self._reg_pc >> 8) & 255)
		self:Push(self._reg_pc & 255)
		self._reg_pc = addr - 1
	elseif op_type == 29 then
		self._reg_acc = self:Load(addr)
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 30 then
		self._reg_x = self:Load(addr)
		self._f_sign = (self._reg_x >> 7) & 1
		self._f_zero = self._reg_x
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 31 then
		self._reg_y = self:Load(addr)
		self._f_sign = (self._reg_y >> 7) & 1
		self._f_zero = self._reg_y
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 32 then
		if addr_mode == 4 then
			temp = self._reg_acc & 0xff
			self._f_carry = temp & 1
			temp = temp >> 1
			self._reg_acc = temp
		else
			temp = self:Load(addr) & 0xff
			self._f_carry = temp & 1
			temp = temp >> 1
			self:Write(addr, temp)
		end
		self._f_sign = 0
		self._f_zero = temp
	elseif op_type == 33 then
	elseif op_type == 34 then
		temp = (self:Load(addr) | self._reg_acc) & 255
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp
		self._reg_acc = temp
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 35 then
		self:Push(self._reg_acc)
	elseif op_type == 36 then
		self._f_brk = 1
		self:Push(self._f_carry | (NESEmulator.ConditionExpr(self._f_zero == 0, 1, 0) << 1) | (self._f_interrupt << 2) | (self._f_decimal << 3) | (self._f_brk << 4) | (self._f_notused << 5) | (self._f_overflow << 6) | (self._f_sign << 7))
	elseif op_type == 37 then
		self._reg_acc = self:Pull()
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
	elseif op_type == 38 then
		temp = self:Pull()
		self._f_carry = temp & 1
		self._f_zero = NESEmulator.ConditionExpr(((temp >> 1) & 1) == 1, 0, 1)
		self._f_interrupt = (temp >> 2) & 1
		self._f_decimal = (temp >> 3) & 1
		self._f_brk = (temp >> 4) & 1
		self._f_notused = (temp >> 5) & 1
		self._f_overflow = (temp >> 6) & 1
		self._f_sign = (temp >> 7) & 1
		self._f_notused = 1
	elseif op_type == 39 then
		if addr_mode == 4 then
			temp = self._reg_acc
			add = self._f_carry
			self._f_carry = (temp >> 7) & 1
			temp = ((temp << 1) & 0xff) + add
			self._reg_acc = temp
		else
			temp = self:Load(addr)
			add = self._f_carry
			self._f_carry = (temp >> 7) & 1
			temp = ((temp << 1) & 0xff) + add
			self:Write(addr, temp)
		end
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp
	elseif op_type == 40 then
		if addr_mode == 4 then
			add = self._f_carry << 7
			self._f_carry = self._reg_acc & 1
			temp = (self._reg_acc >> 1) + add
			self._reg_acc = temp
		else
			temp = self:Load(addr)
			add = self._f_carry << 7
			self._f_carry = temp & 1
			temp = (temp >> 1) + add
			self:Write(addr, temp)
		end
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp
	elseif op_type == 41 then
		temp = self:Pull()
		self._f_carry = temp & 1
		self._f_zero = NESEmulator.ConditionExpr(((temp >> 1) & 1) == 0, 1, 0)
		self._f_interrupt = (temp >> 2) & 1
		self._f_decimal = (temp >> 3) & 1
		self._f_brk = (temp >> 4) & 1
		self._f_notused = (temp >> 5) & 1
		self._f_overflow = (temp >> 6) & 1
		self._f_sign = (temp >> 7) & 1
		self._reg_pc = self:Pull()
		self._reg_pc = self._reg_pc + (self:Pull() << 8)
		if self._reg_pc == 0xffff then
			return nil
		end
		self._reg_pc = self._reg_pc - 1
		self._f_notused = 1
	elseif op_type == 42 then
		self._reg_pc = self:Pull()
		self._reg_pc = self._reg_pc + (self:Pull() << 8)
		if self._reg_pc == 0xffff then
			return nil
		end
	elseif op_type == 43 then
		temp = self._reg_acc - self:Load(addr) - (1 - self._f_carry)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		if ((self._reg_acc ~ temp) & 0x80) ~= 0 and ((self._reg_acc ~ self:Load(addr)) & 0x80) ~= 0 then
			self._f_overflow = 1
		else
			self._f_overflow = 0
		end
		if temp < 0 then
			self._f_carry = 0
		else
			self._f_carry = 1
		end
		self._reg_acc = temp & 0xff
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 44 then
		self._f_carry = 1
	elseif op_type == 45 then
		self._f_decimal = 1
	elseif op_type == 46 then
		self._f_interrupt = 1
	elseif op_type == 47 then
		self:Write(addr, self._reg_acc)
	elseif op_type == 48 then
		self:Write(addr, self._reg_x)
	elseif op_type == 49 then
		self:Write(addr, self._reg_y)
	elseif op_type == 50 then
		self._reg_x = self._reg_acc
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
	elseif op_type == 51 then
		self._reg_y = self._reg_acc
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
	elseif op_type == 52 then
		self._reg_x = self._reg_sp - 0x0100
		self._f_sign = (self._reg_sp >> 7) & 1
		self._f_zero = self._reg_x
	elseif op_type == 53 then
		self._reg_acc = self._reg_x
		self._f_sign = (self._reg_x >> 7) & 1
		self._f_zero = self._reg_x
	elseif op_type == 54 then
		self._reg_sp = self._reg_x + 0x0100
		self:StackWrap()
	elseif op_type == 55 then
		self._reg_acc = self._reg_y
		self._f_sign = (self._reg_y >> 7) & 1
		self._f_zero = self._reg_y
	elseif op_type == 56 then
		temp = self._reg_acc & self:Load(addr)
		self._f_carry = temp & 1
		self._f_zero = temp >> 1
		self._reg_acc = self._f_zero
		self._f_sign = 0
	elseif op_type == 57 then
		self._f_zero = self._reg_acc & self:Load(addr)
		self._reg_acc = self._f_zero
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_carry = self._f_sign
	elseif op_type == 58 then
		temp = self._reg_acc & self:Load(addr)
		self._f_zero = (temp >> 1) + (self._f_carry << 7)
		self._reg_acc = self._f_zero
		self._f_sign = self._f_carry
		self._f_carry = (temp >> 7) & 1
		self._f_overflow = ((temp >> 7) ~ (temp >> 6)) & 1
	elseif op_type == 59 then
		temp = (self._reg_x & self._reg_acc) - self:Load(addr)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		if ((self._reg_x ~ temp) & 0x80) ~= 0 and ((self._reg_x ~ self:Load(addr)) & 0x80) ~= 0 then
			self._f_overflow = 1
		else
			self._f_overflow = 0
		end
		if temp < 0 then
			self._f_carry = 0
		else
			self._f_carry = 1
		end
		self._reg_x = temp & 0xff
	elseif op_type == 60 then
		self._f_zero = self:Load(addr)
		self._reg_x = self._f_zero
		self._reg_acc = self._reg_x
		self._f_sign = (self._reg_acc >> 7) & 1
		cycle_count = cycle_count + (cycle_add)
	elseif op_type == 61 then
		self:Write(addr, self._reg_acc & self._reg_x)
	elseif op_type == 62 then
		temp = (self:Load(addr) - 1) & 0xff
		self:Write(addr, temp)
		temp = self._reg_acc - temp
		self._f_carry = NESEmulator.ConditionExpr(temp >= 0, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 63 then
		temp = (self:Load(addr) + 1) & 0xff
		self:Write(addr, temp)
		temp = self._reg_acc - temp - (1 - self._f_carry)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		if ((self._reg_acc ~ temp) & 0x80) ~= 0 and ((self._reg_acc ~ self:Load(addr)) & 0x80) ~= 0 then
			self._f_overflow = 1
		else
			self._f_overflow = 0
		end
		self._f_carry = NESEmulator.ConditionExpr(temp < 0, 0, 1)
		self._reg_acc = temp & 0xff
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 64 then
		temp = self:Load(addr)
		add = self._f_carry
		self._f_carry = (temp >> 7) & 1
		temp = ((temp << 1) & 0xff) + add
		self:Write(addr, temp)
		self._reg_acc = self._reg_acc & temp
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 65 then
		temp = self:Load(addr)
		add = self._f_carry << 7
		self._f_carry = temp & 1
		temp = (temp >> 1) + add
		self:Write(addr, temp)
		temp = self._reg_acc + self:Load(addr) + self._f_carry
		if ((self._reg_acc ~ self:Load(addr)) & 0x80) == 0 and ((self._reg_acc ~ temp) & 0x80) ~= 0 then
			self._f_overflow = 1
		else
			self._f_overflow = 0
		end
		self._f_carry = NESEmulator.ConditionExpr(temp > 255, 1, 0)
		self._f_sign = (temp >> 7) & 1
		self._f_zero = temp & 0xff
		self._reg_acc = temp & 255
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 66 then
		temp = self:Load(addr)
		self._f_carry = (temp >> 7) & 1
		temp = (temp << 1) & 255
		self:Write(addr, temp)
		self._reg_acc = self._reg_acc | temp
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 67 then
		temp = self:Load(addr) & 0xff
		self._f_carry = temp & 1
		temp = temp >> 1
		self:Write(addr, temp)
		self._reg_acc = self._reg_acc ~ temp
		self._f_sign = (self._reg_acc >> 7) & 1
		self._f_zero = self._reg_acc
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	elseif op_type == 68 then
	elseif op_type == 69 then
		self:Load(addr)
		if addr_mode ~= 11 then
			cycle_count = cycle_count + (cycle_add)
		end
	else
		self._nes:Stop("Game crashed, invalid opcode at address $" .. op_addr)
	end
	return cycle_count
end

function NESEmulator.NesCPU:Load(addr)
	if addr < 0x2000 then
		return self._mem[addr & 0x7ff]
	else
		return self._nes._mmap:Load(addr)
	end
end

function NESEmulator.NesCPU:Load16bit(addr)
	if addr < 0x1fff then
		return self._mem[addr & 0x7ff] | (self._mem[(addr + 1) & 0x7ff] << 8)
	else
		return self._nes._mmap:Load(addr) | (self._nes._mmap:Load(addr + 1) << 8)
	end
end

function NESEmulator.NesCPU:Write(addr, value)
	if addr < 0x2000 then
		self._mem[addr & 0x7ff] = value
	else
		self._nes._mmap:Write(addr, value)
	end
end

function NESEmulator.NesCPU:RequestIrq(type)
	if self._irq_requested then
		if type == NESEmulator.NesCPUIRQ.IRQ_NORMAL then
			return
		end
	end
	self._irq_requested = true
	self._irq_type = type
end

function NESEmulator.NesCPU:Push(value)
	self._nes._mmap:Write(self._reg_sp, value)
	self._reg_sp = self._reg_sp - 1
	self._reg_sp = 0x0100 | (self._reg_sp & 0xff)
end

function NESEmulator.NesCPU:StackWrap()
	self._reg_sp = 0x0100 | (self._reg_sp & 0xff)
end

function NESEmulator.NesCPU:Pull()
	self._reg_sp = self._reg_sp + 1
	self._reg_sp = 0x0100 | (self._reg_sp & 0xff)
	return self._nes._mmap:Load(self._reg_sp)
end

function NESEmulator.NesCPU:PageCrossed(addr1, addr2)
	return (addr1 & 0xff00) ~= (addr2 & 0xff00)
end

function NESEmulator.NesCPU:HaltCycles(cycles)
	self._cycles_to_halt = self._cycles_to_halt + (cycles)
end

function NESEmulator.NesCPU:DoNonMaskableInterrupt(status)
	if (self._nes._mmap:Load(0x2000) & 128) ~= 0 then
		self._reg_pc_new = self._reg_pc_new + 1
		self:Push((self._reg_pc_new >> 8) & 0xff)
		self:Push(self._reg_pc_new & 0xff)
		self:Push(status)
		self._reg_pc_new = self._nes._mmap:Load(0xfffa) | (self._nes._mmap:Load(0xfffb) << 8)
		self._reg_pc_new = self._reg_pc_new - 1
	end
end

function NESEmulator.NesCPU:DoResetInterrupt()
	self._reg_pc_new = self._nes._mmap:Load(0xfffc) | (self._nes._mmap:Load(0xfffd) << 8)
	self._reg_pc_new = self._reg_pc_new - 1
end

function NESEmulator.NesCPU:DoIrq(status)
	self._reg_pc_new = self._reg_pc_new + 1
	self:Push((self._reg_pc_new >> 8) & 0xff)
	self:Push(self._reg_pc_new & 0xff)
	self:Push(status)
	self._f_interrupt_new = 1
	self._f_brk_new = 0
	self._reg_pc_new = self._nes._mmap:Load(0xfffe) | (self._nes._mmap:Load(0xffff) << 8)
	self._reg_pc_new = self._reg_pc_new - 1
end

function NESEmulator.NesCPU:GetStatus()
	return self._f_carry | (self._f_zero << 1) | (self._f_interrupt << 2) | (self._f_decimal << 3) | (self._f_brk << 4) | (self._f_notused << 5) | (self._f_overflow << 6) | (self._f_sign << 7)
end

function NESEmulator.NesCPU:SetStatus(st)
	self._f_carry = st & 1
	self._f_zero = (st >> 1) & 1
	self._f_interrupt = (st >> 2) & 1
	self._f_decimal = (st >> 3) & 1
	self._f_brk = (st >> 4) & 1
	self._f_notused = (st >> 5) & 1
	self._f_overflow = (st >> 6) & 1
	self._f_sign = (st >> 7) & 1
end

end