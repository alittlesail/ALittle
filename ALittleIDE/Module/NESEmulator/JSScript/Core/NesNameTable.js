{
if (typeof NESEmulator === "undefined") window.NESEmulator = {};


NESEmulator.NesNameTable = JavaScript.Class(undefined, {
	Ctor : function(width, height, name) {
		this._width = width;
		this._height = height;
		this._name = name;
		this._tile = new Map();
		this._attrib = new Map();
		let size = this._width * this._height;
		for (let i = 0; i < size; i += 1) {
			this._tile.set(i, 0);
			this._attrib.set(i, 0);
		}
	},
	GetTileIndex : function(x, y) {
		return this._tile.get(y * this._width + x);
	},
	GetAttrib : function(x, y) {
		return this._attrib.get(y * this._width + x);
	},
	WriteAttrib : function(index, value) {
		let basex = (index % 8) * 4;
		let basey = ALittle.Math_Floor(index / 8) * 4;
		let add = 0;
		let tx = 0;
		let ty = 0;
		let attindex = 0;
		for (let sqy = 0; sqy < 2; sqy += 1) {
			for (let sqx = 0; sqx < 2; sqx += 1) {
				add = (value >> (2 * (sqy * 2 + sqx))) & 3;
				for (let y = 0; y < 2; y += 1) {
					for (let x = 0; x < 2; x += 1) {
						tx = basex + sqx * 2 + x;
						ty = basey + sqy * 2 + y;
						attindex = ty * this._width + tx;
						this._attrib.set(attindex, (add << 2) & 12);
					}
				}
			}
		}
	},
}, "NESEmulator.NesNameTable");

}