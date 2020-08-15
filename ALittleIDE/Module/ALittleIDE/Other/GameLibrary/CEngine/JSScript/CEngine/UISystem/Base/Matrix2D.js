{
if (typeof ALittle === "undefined") window.ALittle = {};


let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
ALittle.Matrix2D = JavaScript.Class(undefined, {
	Ctor : function() {
		let m = new Map();
		m.set(0, new Map());
		m.set(1, new Map());
		m.set(2, new Map());
		this._m = m;
		this.SetIdentity();
	},
	SetIdentity : function() {
		let m = this._m;
		m.get(0).set(0, 1);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, 1);
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	SetRotate : function(rad) {
		let m = this._m;
		m.get(0).set(0, __cos(rad));
		m.get(0).set(1, __sin(rad));
		m.get(0).set(2, 0);
		m.get(1).set(0, -m.get(0).get(1));
		m.get(1).set(1, m.get(0).get(0));
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	Rotate : function(rad) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetRotate(rad);
		this.Multiply(m);
	},
	SetTranslation : function(x, y) {
		let m = this._m;
		m.get(0).set(0, 1);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, 1);
		m.get(1).set(2, 0);
		m.get(2).set(0, x);
		m.get(2).set(1, y);
		m.get(2).set(2, 1);
	},
	Translation : function(x, y) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetTranslation(x, y);
		this.Multiply(m);
	},
	SetScale : function(x, y) {
		let m = this._m;
		m.get(0).set(0, x);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, y);
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	Scale : function(x, y) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetScale(x, y);
		this.Multiply(m);
	},
	Multiply : function(right) {
		let r = new Map();
		let m = this._m;
		let rm = right._m;
		r.set(0, new Map());
		r.get(0).set(0, m.get(0).get(0) * rm.get(0).get(0) + m.get(0).get(1) * rm.get(1).get(0) + m.get(0).get(2) * rm.get(2).get(0));
		r.get(0).set(1, m.get(0).get(0) * rm.get(0).get(1) + m.get(0).get(1) * rm.get(1).get(1) + m.get(0).get(2) * rm.get(2).get(1));
		r.get(0).set(2, m.get(0).get(0) * rm.get(0).get(2) + m.get(0).get(1) * rm.get(1).get(2) + m.get(0).get(2) * rm.get(2).get(2));
		r.set(1, new Map());
		r.get(1).set(0, m.get(1).get(0) * rm.get(0).get(0) + m.get(1).get(1) * rm.get(1).get(0) + m.get(1).get(2) * rm.get(2).get(0));
		r.get(1).set(1, m.get(1).get(0) * rm.get(0).get(1) + m.get(1).get(1) * rm.get(1).get(1) + m.get(1).get(2) * rm.get(2).get(1));
		r.get(1).set(2, m.get(1).get(0) * rm.get(0).get(2) + m.get(1).get(1) * rm.get(1).get(2) + m.get(1).get(2) * rm.get(2).get(2));
		r.set(2, new Map());
		r.get(2).set(0, m.get(2).get(0) * rm.get(0).get(0) + m.get(2).get(1) * rm.get(1).get(0) + m.get(2).get(2) * rm.get(2).get(0));
		r.get(2).set(1, m.get(2).get(0) * rm.get(0).get(1) + m.get(2).get(1) * rm.get(1).get(1) + m.get(2).get(2) * rm.get(2).get(1));
		r.get(2).set(2, m.get(2).get(0) * rm.get(0).get(2) + m.get(2).get(1) * rm.get(1).get(2) + m.get(2).get(2) * rm.get(2).get(2));
		this._m = r;
	},
}, "ALittle.Matrix2D");

ALittle.Vector2D = JavaScript.Class(undefined, {
	Ctor : function(xx, yy) {
		this._x = xx;
		this._y = yy;
	},
	Multiply : function(right) {
		let rm = right._m;
		let xx = this._x * rm.get(0).get(0) + this._y * rm.get(1).get(0) + 1 * rm.get(2).get(0);
		let yy = this._x * rm.get(0).get(1) + this._y * rm.get(1).get(1) + 1 * rm.get(2).get(1);
		this._x = xx;
		this._y = yy;
	},
}, "ALittle.Vector2D");

}