{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesTile = JavaScript.Class(undefined, {
	Ctor : function() {
		this._pix = new Map();
		this._init = false;
	},
	SetBuffer : function(scanline) {
		for (let y = 0; y < 8; y += 1) {
			this.SetScanline(y, scanline.get(y), scanline.get(y + 8));
		}
	},
	SetScanline : function(sline, b1, b2) {
		this._init = true;
		let t_index = sline << 3;
		for (let x = 0; x < 8; x += 1) {
			this._pix.set(t_index + x, ((b1 >> (7 - x)) & 1) + (((b2 >> (7 - x)) & 1) << 1));
			if (this._pix.get(t_index + x) === 0) {
				this._opaque.set(sline, false);
			}
		}
	},
	Render : function(buffer, src_x1, src_y1, src_x2, src_y2, dx, dy, pal_add, palette, flip_horizontal, flip_vertical, pri, pri_table) {
}