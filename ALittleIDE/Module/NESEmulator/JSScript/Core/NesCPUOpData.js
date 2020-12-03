{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesCPUInsType = {
	INS_ADC : 0,
	INS_AND : 1,
	INS_ASL : 2,
	INS_BCC : 3,
	INS_BCS : 4,
	INS_BEQ : 5,
	INS_BIT : 6,
	INS_BMI : 7,
	INS_BNE : 8,
	INS_BPL : 9,
	INS_BRK : 10,
	INS_BVC : 11,
	INS_BVS : 12,
	INS_CLC : 13,
	INS_CLD : 14,
	INS_CLI : 15,
	INS_CLV : 16,
	INS_CMP : 17,
	INS_CPX : 18,
	INS_CPY : 19,
	INS_DEC : 20,
	INS_DEX : 21,
	INS_DEY : 22,
	INS_EOR : 23,
	INS_INC : 24,
	INS_INX : 25,
	INS_INY : 26,
	INS_JMP : 27,
	INS_JSR : 28,
	INS_LDA : 29,
	INS_LDX : 30,
	INS_LDY : 31,
	INS_LSR : 32,
	INS_NOP : 33,
	INS_ORA : 34,
	INS_PHA : 35,
	INS_PHP : 36,
	INS_PLA : 37,
	INS_PLP : 38,
	INS_ROL : 39,
	INS_ROR : 40,
	INS_RTI : 41,
	INS_RTS : 42,
	INS_SBC : 43,
	INS_SEC : 44,
	INS_SED : 45,
	INS_SEI : 46,
	INS_STA : 47,
	INS_STX : 48,
	INS_STY : 49,
	INS_TAX : 50,
	INS_TAY : 51,
	INS_TSX : 52,
	INS_TXA : 53,
	INS_TXS : 54,
	INS_TYA : 55,
	INS_ALR : 56,
	INS_ANC : 57,
	INS_ARR : 58,
	INS_AXS : 59,
	INS_LAX : 60,
	INS_SAX : 61,
	INS_DCP : 62,
	INS_ISC : 63,
	INS_RLA : 64,
	INS_RRA : 65,
	INS_SLO : 66,
	INS_SRE : 67,
	INS_SKB : 68,
	INS_IGN : 69,
	INS_DUMMY : 70,
}

NESEmulator.NesCPUAddrType = {
	ADDR_ZP : 0,
	ADDR_REL : 1,
	ADDR_IMP : 2,
	ADDR_ABS : 3,
	ADDR_ACC : 4,
	ADDR_IMM : 5,
	ADDR_ZPX : 6,
	ADDR_ZPY : 7,
	ADDR_ABSX : 8,
	ADDR_ABSY : 9,
	ADDR_PREIDXIND : 10,
	ADDR_POSTIDXIND : 11,
	ADDR_INDABS : 12,
}

NESEmulator.NesCPUOpData = JavaScript.Class(undefined, {
	Ctor : function() {
		this._op_data = new Map();
		for (let i = 0; i < 256; i += 1) {
			this._op_data.set(i, 0xff);
		}
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x69, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x65, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x75, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x6d, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x7d, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x79, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x61, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ADC, 0x71, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x29, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x25, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x35, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x2d, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x3d, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x39, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x21, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AND, 0x31, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ASL, 0x0a, NESEmulator.NesCPUAddrType.ADDR_ACC, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ASL, 0x06, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ASL, 0x16, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ASL, 0x0e, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ASL, 0x1e, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BCC, 0x90, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BCS, 0xb0, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BEQ, 0xf0, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BIT, 0x24, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BIT, 0x2c, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BMI, 0x30, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BNE, 0xd0, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BPL, 0x10, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BRK, 0x00, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BVC, 0x50, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_BVS, 0x70, NESEmulator.NesCPUAddrType.ADDR_REL, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CLC, 0x18, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CLD, 0xd8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CLI, 0x58, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CLV, 0xb8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xc9, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xc5, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xd5, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xcd, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xdd, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xd9, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xc1, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CMP, 0xd1, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPX, 0xe0, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPX, 0xe4, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPX, 0xec, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPY, 0xc0, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPY, 0xc4, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_CPY, 0xcc, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEC, 0xc6, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEC, 0xd6, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEC, 0xce, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEC, 0xde, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEX, 0xca, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DEY, 0x88, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x49, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x45, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x55, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x4d, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x5d, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x59, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x41, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_EOR, 0x51, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INC, 0xe6, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INC, 0xf6, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INC, 0xee, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INC, 0xfe, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INX, 0xe8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_INY, 0xc8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_JMP, 0x4c, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_JMP, 0x6c, NESEmulator.NesCPUAddrType.ADDR_INDABS, 3, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_JSR, 0x20, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xa9, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xa5, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xb5, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xad, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xbd, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xb9, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xa1, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDA, 0xb1, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDX, 0xa2, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDX, 0xa6, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDX, 0xb6, NESEmulator.NesCPUAddrType.ADDR_ZPY, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDX, 0xae, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDX, 0xbe, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDY, 0xa0, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDY, 0xa4, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDY, 0xb4, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDY, 0xac, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LDY, 0xbc, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LSR, 0x4a, NESEmulator.NesCPUAddrType.ADDR_ACC, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LSR, 0x46, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LSR, 0x56, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LSR, 0x4e, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LSR, 0x5e, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0x1a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0x3a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0x5a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0x7a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0xda, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0xea, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_NOP, 0xfa, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x09, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x05, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x15, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x0d, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x1d, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x19, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x01, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ORA, 0x11, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_PHA, 0x48, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_PHP, 0x08, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_PLA, 0x68, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_PLP, 0x28, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROL, 0x2a, NESEmulator.NesCPUAddrType.ADDR_ACC, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROL, 0x26, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROL, 0x36, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROL, 0x2e, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROL, 0x3e, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROR, 0x6a, NESEmulator.NesCPUAddrType.ADDR_ACC, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROR, 0x66, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROR, 0x76, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROR, 0x6e, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ROR, 0x7e, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RTI, 0x40, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RTS, 0x60, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xe9, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xe5, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xf5, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xed, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xfd, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xf9, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xe1, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SBC, 0xf1, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SEC, 0x38, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SED, 0xf8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SEI, 0x78, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x85, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x95, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x8d, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x9d, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x99, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x81, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STA, 0x91, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STX, 0x86, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STX, 0x96, NESEmulator.NesCPUAddrType.ADDR_ZPY, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STX, 0x8e, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STY, 0x84, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STY, 0x94, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_STY, 0x8c, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TAX, 0xaa, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TAY, 0xa8, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TSX, 0xba, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TXA, 0x8a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TXS, 0x9a, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_TYA, 0x98, NESEmulator.NesCPUAddrType.ADDR_IMP, 1, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ALR, 0x4b, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ANC, 0x0b, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ANC, 0x2b, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ARR, 0x6b, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_AXS, 0xcb, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xa3, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xa7, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xaf, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xb3, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xb7, NESEmulator.NesCPUAddrType.ADDR_ZPY, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_LAX, 0xbf, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SAX, 0x83, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SAX, 0x87, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SAX, 0x8f, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SAX, 0x97, NESEmulator.NesCPUAddrType.ADDR_ZPY, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xc3, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xc7, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xcf, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xd3, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xd7, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xdb, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_DCP, 0xdf, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xe3, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xe7, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xef, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xf3, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xf7, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xfb, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_ISC, 0xff, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x23, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x27, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x2f, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x33, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x37, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x3b, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RLA, 0x3f, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x63, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x67, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x6f, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x73, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x77, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x7b, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_RRA, 0x7f, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x03, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x07, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x0f, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x13, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x17, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x1b, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SLO, 0x1f, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x43, NESEmulator.NesCPUAddrType.ADDR_PREIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x47, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 5);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x4f, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x53, NESEmulator.NesCPUAddrType.ADDR_POSTIDXIND, 2, 8);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x57, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 6);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x5b, NESEmulator.NesCPUAddrType.ADDR_ABSY, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SRE, 0x5f, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 7);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SKB, 0x80, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SKB, 0x82, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SKB, 0x89, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SKB, 0xc2, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_SKB, 0xe2, NESEmulator.NesCPUAddrType.ADDR_IMM, 2, 2);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x0c, NESEmulator.NesCPUAddrType.ADDR_ABS, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x1c, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x3c, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x5c, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x7c, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0xdc, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0xfc, NESEmulator.NesCPUAddrType.ADDR_ABSX, 3, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x04, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x44, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x64, NESEmulator.NesCPUAddrType.ADDR_ZP, 2, 3);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x14, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x34, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x54, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0x74, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0xd4, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
		this.SetOp(NESEmulator.NesCPUInsType.INS_IGN, 0xf4, NESEmulator.NesCPUAddrType.ADDR_ZPX, 2, 4);
	},
	SetOp : function(inst, op, addr, size, cycles) {
		this._op_data.set(op, (inst & 0xff) | ((addr & 0xff) << 8) | ((size & 0xff) << 16) | ((cycles & 0xff) << 24));
	},
}, "NESEmulator.NesCPUOpData");

}