{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIStatLayout = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._point_size = 5;
		this._draw_width = 0;
		this._draw_height = 0;
		this._min_index = 0;
		this._max_index = 0;
		this._max_value = 0;
		this._sum_value = 0;
		this._loss_map = new Map();
		this._right_map = new Map();
	},
	TCtor : function() {
		this._image = ALittle.NewObject(ALittle.DynamicImage, this._ctrl_sys);
		this._image.width_type = 4;
		this._image.height_type = 4;
		this._image.SetRenderMode(1);
		this.AddChild(this._image);
	},
	Init : function(point_size, draw_width, draw_height) {
		this._point_size = point_size;
		if (this._point_size < 1) {
			this._point_size = 1;
		}
		this._draw_width = draw_width;
		if (this._draw_width < 0) {
			this._draw_width = 0;
		}
		this._draw_height = draw_height;
		if (this._draw_height < 0) {
			this._draw_height = 0;
		}
		this._min_index = 0;
		this._max_index = 0;
		this._sum_value = 0;
		this._loss_map = new Map();
		this._right_map = new Map();
		this._max_value = this.CalcMaxValue();
		this._image.SetSurfaceSize(this._draw_width, this._draw_height, 0xFF000000);
	},
	CalcMaxValue : function() {
		let value = this.GetAverageValue();
		if (value <= 0) {
			return 1;
		}
		let max_value = value;
		if (max_value < 1) {
			max_value = 1;
		}
		return max_value;
	},
	TryFreshMaxValue : function() {
		let value = this.GetAverageValue();
		let need_fresh = value <= this._max_value / 4 || value > this._max_value;
		if (!need_fresh) {
			return;
		}
		let target = value * 2;
		if (target < 1) {
			target = 1;
		}
		if (this._max_value === target) {
			return;
		}
		this._max_value = target;
		this._image.SetSurfaceSize(this._draw_width, this._draw_height, 0xFF000000);
		let min_index = this._min_index;
		let max_index = this._max_index;
		let loss_map = this._loss_map;
		let right_map = this._right_map;
		this._loss_map = new Map();
		this._right_map = new Map();
		this._min_index = 0;
		this._max_index = 0;
		this._sum_value = 0;
		for (let i = min_index + 1; i <= max_index; i += 1) {
			this.AddValue(loss_map.get(i), right_map.get(i), true);
		}
	},
	GetAverageValue : function() {
		let count = this._max_index - this._min_index;
		if (count <= 0) {
			return 0;
		}
		return this._sum_value / count;
	},
	AddValue : function(loss, right, not_refresh) {
		this._sum_value = this._sum_value + (loss);
		if (this._max_index - this._min_index + 1 < ALittle.Math_Floor(this._draw_width / this._point_size)) {
			this._max_index = this._max_index + (1);
		} else {
			if (this._min_index > 0) {
				this._sum_value = this._sum_value - (this._loss_map.get(this._min_index));
			}
			this._loss_map.delete(this._min_index);
			this._right_map.delete(this._min_index);
			this._min_index = this._min_index + (1);
			this._max_index = this._max_index + (1);
			let surface = this._image.GetSurface(true);
			carp.TransferCarpSurface(surface, "left", this._point_size);
		}
		this._loss_map.set(this._max_index, loss);
		this._right_map.set(this._max_index, right);
		let color = 0xFFFFFFFF;
		let x = (this._max_index - this._min_index) * this._point_size;
		if (x > this._draw_width - this._point_size) {
			x = this._draw_width - this._point_size;
		}
		let y = 0;
		if (this._max_value !== 0) {
			let rate = loss / this._max_value;
			if (rate > 1) {
				color = 0xFF0000FF;
			} else if (rate < 0.00001) {
				color = 0xFF00FFFF;
			}
			if (right) {
				color = 0xFF00FF00;
			}
			y = ALittle.Math_Floor(rate * this._draw_height);
			if (y > this._draw_height - this._point_size) {
				y = this._draw_height - this._point_size;
			}
		}
		y = this._draw_height - this._point_size - y;
		let surface = this._image.GetSurface(true);
		for (let col = x; col < x + this._point_size; col += 1) {
			for (let row = y; row < y + this._point_size; row += 1) {
				carp.SetCarpSurfacePixel(surface, col, row, color);
			}
		}
		if (!not_refresh) {
			this.TryFreshMaxValue();
		}
	},
	ClearContent : function() {
		this._sum_value = 0;
		this._min_index = 0;
		this._max_index = 0;
		this._loss_map = new Map();
		this._right_map = new Map();
		this._max_value = this.GetAverageValue();
		this._image.SetSurfaceSize(this._draw_width, this._draw_height, 0xFF000000);
	},
	get surface() {
		return this._image.GetSurface(false);
	},
}, "AUIPlugin.AUIStatLayout");

}