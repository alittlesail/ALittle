{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesPaletteTable = JavaScript.Class(undefined, {
	Reset : function() {
		this.SetEmphasis(0);
	},
	LoadNTSCPalette : function() {
		let values = [0x525252, 0xB40000, 0xA00000, 0xB1003D, 0x740069, 0x00005B, 0x00005F, 0x001840, 0x002F10, 0x084A08, 0x006700, 0x124200, 0x6D2800, 0x000000, 0x000000, 0x000000, 0xC4D5E7, 0xFF4000, 0xDC0E22, 0xFF476B, 0xD7009F, 0x680AD7, 0x0019BC, 0x0054B1, 0x006A5B, 0x008C03, 0x00AB00, 0x2C8800, 0xA47200, 0x000000, 0x000000, 0x000000, 0xF8F8F8, 0xFFAB3C, 0xFF7981, 0xFF5BC5, 0xFF48F2, 0xDF49FF, 0x476DFF, 0x00B4F7, 0x00E0FF, 0x00E375, 0x03F42B, 0x78B82E, 0xE5E218, 0x787878, 0x000000, 0x000000, 0xFFFFFF, 0xFFF2BE, 0xF8B8B8, 0xF8B8D8, 0xFFB6FF, 0xFFC3FF, 0xC7D1FF, 0x9ADAFF, 0x88EDF8, 0x83FFDD, 0xB8F8B8, 0xF5F8AC, 0xFFFFB0, 0xF8D8F8, 0x000000, 0x000000];
		let ___OBJECT_1 = values;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this._cur_table.set(index - 1, value);
		}
		this.MakeTables();
		this.SetEmphasis(0);
	},
	LoadPALPalette : function() {
		let values = [0x525252, 0xB40000, 0xA00000, 0xB1003D, 0x740069, 0x00005B, 0x00005F, 0x001840, 0x002F10, 0x084A08, 0x006700, 0x124200, 0x6D2800, 0x000000, 0x000000, 0x000000, 0xC4D5E7, 0xFF4000, 0xDC0E22, 0xFF476B, 0xD7009F, 0x680AD7, 0x0019BC, 0x0054B1, 0x006A5B, 0x008C03, 0x00AB00, 0x2C8800, 0xA47200, 0x000000, 0x000000, 0x000000, 0xF8F8F8, 0xFFAB3C, 0xFF7981, 0xFF5BC5, 0xFF48F2, 0xDF49FF, 0x476DFF, 0x00B4F7, 0x00E0FF, 0x00E375, 0x03F42B, 0x78B82E, 0xE5E218, 0x787878, 0x000000, 0x000000, 0xFFFFFF, 0xFFF2BE, 0xF8B8B8, 0xF8B8D8, 0xFFB6FF, 0xFFC3FF, 0xC7D1FF, 0x9ADAFF, 0x88EDF8, 0x83FFDD, 0xB8F8B8, 0xF5F8AC, 0xFFFFB0, 0xF8D8F8, 0x000000, 0x000000];
		let ___OBJECT_2 = values;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			this._cur_table.set(index - 1, value);
		}
		this.MakeTables();
		this.SetEmphasis(0);
	},
	MakeTables : function() {
		let r = 0;
		let g = 0;
		let b = 0;
		let col = 0;
		let rFactor = 0.0;
		let gFactor = 0.0;
		let bFactor = 0.0;
		for (let emph = 0; emph < 8; emph += 1) {
			rFactor = 1.0;
			gFactor = 1.0;
			bFactor = 1.0;
			if ((emph & 1) !== 0) {
				rFactor = 0.75;
				bFactor = 0.75;
			}
			if ((emph & 2) !== 0) {
				rFactor = 0.75;
				gFactor = 0.75;
			}
			if ((emph & 4) !== 0) {
				gFactor = 0.75;
				bFactor = 0.75;
			}
			this._emph_table.set(emph, new Map());
			for (let i = 0; i < 64; i += 1) {
				col = this._cur_table.get(i);
				r = ALittle.Math_Floor(this.GetRed(col) * rFactor);
				g = ALittle.Math_Floor(this.GetGreen(col) * gFactor);
				b = ALittle.Math_Floor(this.GetBlue(col) * bFactor);
				this._emph_table.get(emph).set(i, this.GetRgb(r, g, b));
			}
		}
	},
	SetEmphasis : function(emph) {
		if (emph !== this._current_emph) {
			this._current_emph = emph;
			for (let i = 0; i < 64; i += 1) {
				this._cur_table.set(i, this._emph_table.get(emph).get(i));
			}
		}
	},
	GetEntry : function(yiq) {
		return this._cur_table.get(yiq);
	},
	GetRed : function(rgb) {
		return (rgb >> 16) & 0xff;
	},
	GetGreen : function(rgb) {
		return (rgb >> 8) & 0xff;
	},
	GetBlue : function(rgb) {
		return rgb & 0xff;
	},
	GetRgb : function(r, g, b) {
		return (r << 16) | (g << 8) | b;
	},
	LoadDefaultPalette : function() {
		this._cur_table.set(0, this.GetRgb(117, 117, 117));
		this._cur_table.set(1, this.GetRgb(39, 27, 143));
		this._cur_table.set(2, this.GetRgb(0, 0, 171));
		this._cur_table.set(3, this.GetRgb(71, 0, 159));
		this._cur_table.set(4, this.GetRgb(143, 0, 119));
		this._cur_table.set(5, this.GetRgb(171, 0, 19));
		this._cur_table.set(6, this.GetRgb(167, 0, 0));
		this._cur_table.set(7, this.GetRgb(127, 11, 0));
		this._cur_table.set(8, this.GetRgb(67, 47, 0));
		this._cur_table.set(9, this.GetRgb(0, 71, 0));
		this._cur_table.set(10, this.GetRgb(0, 81, 0));
		this._cur_table.set(11, this.GetRgb(0, 63, 23));
		this._cur_table.set(12, this.GetRgb(27, 63, 95));
		this._cur_table.set(13, this.GetRgb(0, 0, 0));
		this._cur_table.set(14, this.GetRgb(0, 0, 0));
		this._cur_table.set(15, this.GetRgb(0, 0, 0));
		this._cur_table.set(16, this.GetRgb(188, 188, 188));
		this._cur_table.set(17, this.GetRgb(0, 115, 239));
		this._cur_table.set(18, this.GetRgb(35, 59, 239));
		this._cur_table.set(19, this.GetRgb(131, 0, 243));
		this._cur_table.set(20, this.GetRgb(191, 0, 191));
		this._cur_table.set(21, this.GetRgb(231, 0, 91));
		this._cur_table.set(22, this.GetRgb(219, 43, 0));
		this._cur_table.set(23, this.GetRgb(203, 79, 15));
		this._cur_table.set(24, this.GetRgb(139, 115, 0));
		this._cur_table.set(25, this.GetRgb(0, 151, 0));
		this._cur_table.set(26, this.GetRgb(0, 171, 0));
		this._cur_table.set(27, this.GetRgb(0, 147, 59));
		this._cur_table.set(28, this.GetRgb(0, 131, 139));
		this._cur_table.set(29, this.GetRgb(0, 0, 0));
		this._cur_table.set(30, this.GetRgb(0, 0, 0));
		this._cur_table.set(31, this.GetRgb(0, 0, 0));
		this._cur_table.set(32, this.GetRgb(255, 255, 255));
		this._cur_table.set(33, this.GetRgb(63, 191, 255));
		this._cur_table.set(34, this.GetRgb(95, 151, 255));
		this._cur_table.set(35, this.GetRgb(167, 139, 253));
		this._cur_table.set(36, this.GetRgb(247, 123, 255));
		this._cur_table.set(37, this.GetRgb(255, 119, 183));
		this._cur_table.set(38, this.GetRgb(255, 119, 99));
		this._cur_table.set(39, this.GetRgb(255, 155, 59));
		this._cur_table.set(40, this.GetRgb(243, 191, 63));
		this._cur_table.set(41, this.GetRgb(131, 211, 19));
		this._cur_table.set(42, this.GetRgb(79, 223, 75));
		this._cur_table.set(43, this.GetRgb(88, 248, 152));
		this._cur_table.set(44, this.GetRgb(0, 235, 219));
		this._cur_table.set(45, this.GetRgb(0, 0, 0));
		this._cur_table.set(46, this.GetRgb(0, 0, 0));
		this._cur_table.set(47, this.GetRgb(0, 0, 0));
		this._cur_table.set(48, this.GetRgb(255, 255, 255));
		this._cur_table.set(49, this.GetRgb(171, 231, 255));
		this._cur_table.set(50, this.GetRgb(199, 215, 255));
		this._cur_table.set(51, this.GetRgb(215, 203, 255));
		this._cur_table.set(52, this.GetRgb(255, 199, 255));
		this._cur_table.set(53, this.GetRgb(255, 199, 219));
		this._cur_table.set(54, this.GetRgb(255, 191, 179));
		this._cur_table.set(55, this.GetRgb(255, 219, 171));
		this._cur_table.set(56, this.GetRgb(255, 231, 163));
		this._cur_table.set(57, this.GetRgb(227, 255, 163));
		this._cur_table.set(58, this.GetRgb(171, 243, 191));
		this._cur_table.set(59, this.GetRgb(179, 255, 207));
		this._cur_table.set(60, this.GetRgb(159, 255, 243));
		this._cur_table.set(61, this.GetRgb(0, 0, 0));
		this._cur_table.set(62, this.GetRgb(0, 0, 0));
		this._cur_table.set(63, this.GetRgb(0, 0, 0));
		this.MakeTables();
		this.SetEmphasis(0);
	},
}, "NESEmulator.NesPaletteTable");

}