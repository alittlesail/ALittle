{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Piechart = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._start_degree = 0;
		this._end_degree = 0;
		this._tri_list = [];
		for (let i = 1; i <= 5; i += 1) {
			let triangle = ALittle.NewObject(ALittle.Triangle, this._ctrl_sys);
			triangle.u2 = 0.5;
			triangle.v2 = 0.5;
			triangle.width_type = 4;
			triangle.width_value = 0;
			triangle.height_type = 4;
			triangle.height_value = 0;
			this._tri_list[i - 1] = triangle;
			ALittle.DisplayLayout.AddChild.call(this, triangle);
		}
		this._start_degree = 0;
		this._end_degree = 360;
		this.SetDegree(0, 360);
		this._pie_texture_name = undefined;
	},
	set start_degree(value) {
		let tmp = value % 360;
		if (tmp < 0) {
			tmp = tmp + (360);
		}
		if (tmp === 0 && value / 360 !== 0) {
			tmp = 360;
		}
		this._start_degree = tmp;
		this.SetDegree(tmp, this._end_degree);
	},
	get start_degree() {
		return this._start_degree;
	},
	set end_degree(value) {
		let tmp = value % 360;
		if (tmp < 0) {
			tmp = tmp + (360);
		}
		if (tmp === 0 && value / 360 !== 0) {
			tmp = 360;
		}
		this._end_degree = tmp;
		this.SetDegree(this._start_degree, tmp);
	},
	get end_degree() {
		return this._end_degree;
	},
	set red(value) {
		if (this.red === value) {
			return;
		}
		this.red = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].red = value;
		}
	},
	set green(value) {
		if (this.green === value) {
			return;
		}
		this.green = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].green = value;
		}
	},
	set blue(value) {
		if (this.blue === value) {
			return;
		}
		this.blue = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].blue = value;
		}
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === 1) {
			this._width_value = this._width;
		}
		let ___OBJECT_1 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			v.x1 = v.u1 * value;
			v.x2 = v.u2 * value;
			v.x3 = v.u3 * value;
			this.UpdateWidthLayout(v);
			this.UpdateXLayout(v);
		}
		this._show.SetWidth(value);
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === 1) {
			this._height_value = this._height;
		}
		let ___OBJECT_2 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			v.y1 = v.v1 * value;
			v.y2 = v.v2 * value;
			v.y3 = v.v3 * value;
			this.UpdateHeightLayout(v);
			this.UpdateYLayout(v);
		}
		this._show.SetHeight(value);
	},
	set texture_name(value) {
		if (this._pie_texture_name === value) {
			return;
		}
		this._pie_texture_name = value;
		let ___OBJECT_3 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_3.length; ++k) {
			let v = ___OBJECT_3[k - 1];
			if (v === undefined) break;
			v.texture_name = value;
		}
	},
	get texture_name() {
		return this._pie_texture_name;
	},
	SetDegree : function(start_c, end_c) {
		if (end_c <= start_c) {
			return;
		}
		let width = this.width;
		let height = this.height;
		let ___OBJECT_4 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let v = ___OBJECT_4[k - 1];
			if (v === undefined) break;
			v.visible = false;
		}
		let e_offset = 0.0;
		let s_offset = 0.0;
		if (end_c >= 0 && end_c <= 45) {
			s_offset = (45 - start_c) / 90;
			e_offset = (45 - end_c) / 90;
			this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, 1, s_offset);
			this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, width, s_offset * height);
		} else if (end_c <= 135) {
			e_offset = (135 - end_c) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], e_offset, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], e_offset * width, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
			} else {
				e_offset = (135 - end_c) / 90;
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], e_offset, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], e_offset * width, 0, s_offset * width, 0);
			}
		} else if (end_c <= 225) {
			e_offset = (end_c - 135) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, e_offset * height);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, e_offset * height);
			} else {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, e_offset * height);
			}
		} else if (end_c <= 315) {
			e_offset = (end_c - 225) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else if (start_c < 225) {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else {
				s_offset = (start_c - 225) / 90;
				this.SetTriangleUV(this._tri_list[4 - 1], s_offset, 1, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], s_offset * width, height, e_offset * width, height);
			}
		} else {
			e_offset = (405 - end_c) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[5 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[5 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 225) {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 315) {
				s_offset = (start_c - 225) / 90;
				this.SetTriangleUV(this._tri_list[4 - 1], s_offset, 1, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], s_offset * width, height, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else {
				s_offset = (405 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, width, s_offset * height);
			}
		}
	},
	SetTriangleXY : function(tri, x1, y1, x3, y3) {
		tri.x1 = x1;
		tri.y1 = y1;
		tri.x3 = x3;
		tri.y3 = y3;
		tri.visible = true;
	},
	SetTriangleUV : function(tri, u1, v1, u3, v3) {
		tri.u1 = u1;
		tri.v1 = v1;
		tri.u3 = u3;
		tri.v3 = v3;
	},
}, "ALittle.Piechart");

}