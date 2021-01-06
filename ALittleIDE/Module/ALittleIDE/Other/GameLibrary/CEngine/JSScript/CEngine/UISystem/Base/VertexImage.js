{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.VertexImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JVertexImage);
		this._u1 = 0;
		this._v1 = 0;
		this._u2 = 0;
		this._v2 = 0;
		this._u3 = 0;
		this._v3 = 0;
		this._u4 = 0;
		this._v4 = 0;
		this._x1 = 0;
		this._y1 = 0;
		this._x2 = 0;
		this._y2 = 0;
		this._x3 = 0;
		this._y3 = 0;
		this._x4 = 0;
		this._y4 = 0;
		this._texture_width = 0;
		this._texture_height = 0;
		this._auto_rejust = false;
	},
	Redraw : function() {
		this._show.ClearTexture();
		if (this._texture !== undefined) {
			this._texture.Clear();
			this._texture = undefined;
		}
		if (this._texture_name === undefined) {
			return;
		}
		if (this._texture_cut !== undefined) {
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, this._texture_cut.max_width, this._texture_cut.max_height, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = value;
		if (this._texture_name !== undefined) {
			this._texture_cut = undefined;
			this._ctrl_sys.SetTexture(this, value);
		}
	},
	SetTextureCut : function(texture_name, auto_rejust, max_width, max_height, cache, index) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = max_width;
			this._texture_cut.max_height = max_height;
			this._texture_cut.cache = cache;
			this._auto_rejust = auto_rejust || false;
			A_LoadTextureManager.SetTextureCut(this, texture_name, max_width, max_height, cache);
		}
	},
	set texture_cut(param) {
		this.SetTextureCut(param.texture_name, true, param.max_width, param.max_height, param.cache, undefined);
	},
	get texture_cut() {
		if (this._texture_cut === undefined) {
			return undefined;
		}
		let texture_cut = {};
		texture_cut.max_width = this._texture_cut.max_width;
		texture_cut.max_height = this._texture_cut.max_height;
		texture_cut.texture_name = this._texture_name;
		return texture_cut;
	},
	get texture_name() {
		return this._texture_name;
	},
	set texture(value) {
		this._show.SetTexture(value.GetTexture());
		this._texture_width = value.GetWidth();
		this._texture_height = value.GetHeight();
		this._texture = value;
		if (this._auto_rejust) {
			this.width = this._texture_width;
			this.height = this._texture_height;
		}
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._show.SetTextureCoord(t, b, l, r);
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	get u1() {
		return this._u1;
	},
	get v1() {
		return this._v1;
	},
	get u2() {
		return this._u2;
	},
	get v2() {
		return this._v2;
	},
	get u3() {
		return this._u3;
	},
	get v3() {
		return this._v3;
	},
	get u4() {
		return this._u4;
	},
	get v4() {
		return this._v4;
	},
	set u1(v) {
		this._u1 = v;
		this._show.SetTexUV(0, this._u1, this._v1);
	},
	set v1(v) {
		this._v1 = v;
		this._show.SetTexUV(0, this._u1, this._v1);
	},
	set u2(v) {
		this._u2 = v;
		this._show.SetTexUV(1, this._u2, this._v2);
	},
	set v2(v) {
		this._v2 = v;
		this._show.SetTexUV(1, this._u2, this._v2);
	},
	set u3(v) {
		this._u3 = v;
		this._show.SetTexUV(2, this._u3, this._v3);
	},
	set v3(v) {
		this._v3 = v;
		this._show.SetTexUV(2, this._u3, this._v3);
	},
	set u4(v) {
		this._u4 = v;
		this._show.SetTexUV(3, this._u4, this._v4);
	},
	set v4(v) {
		this._v4 = v;
		this._show.SetTexUV(3, this._u4, this._v4);
	},
	get x1() {
		return this._x1;
	},
	get y1() {
		return this._y1;
	},
	get x2() {
		return this._x2;
	},
	get y2() {
		return this._y2;
	},
	get x3() {
		return this._x3;
	},
	get y3() {
		return this._y3;
	},
	get x4() {
		return this._x4;
	},
	get y4() {
		return this._y4;
	},
	set x1(v) {
		this._x1 = v;
		this._show.SetPosXY(0, this._x1, this._y1);
	},
	set y1(v) {
		this._y1 = v;
		this._show.SetPosXY(0, this._x1, this._y1);
	},
	set x2(v) {
		this._x2 = v;
		this._show.SetPosXY(1, this._x2, this._y2);
	},
	set y2(v) {
		this._y2 = v;
		this._show.SetPosXY(1, this._x2, this._y2);
	},
	set x3(v) {
		this._x3 = v;
		this._show.SetPosXY(2, this._x3, this._y3);
	},
	set y3(v) {
		this._y3 = v;
		this._show.SetPosXY(2, this._x3, this._y3);
	},
	set x4(v) {
		this._x4 = v;
		this._show.SetPosXY(3, this._x4, this._y4);
	},
	set y4(v) {
		this._y4 = v;
		this._show.SetPosXY(3, this._x4, this._y4);
	},
	RejuseSize : function() {
		let max = this._x1;
		if (max < this._x2) {
			max = this._x2;
		}
		if (max < this._x3) {
			max = this._x3;
		}
		if (max < this._x4) {
			max = this._x4;
		}
		this.width = max;
		max = this._y1;
		if (max < this._y2) {
			max = this._y2;
		}
		if (max < this._y3) {
			max = this._y3;
		}
		if (max < this._y4) {
			max = this._y4;
		}
		this.height = max;
		this.UpdateLayout();
	},
}, "ALittle.VertexImage");

}