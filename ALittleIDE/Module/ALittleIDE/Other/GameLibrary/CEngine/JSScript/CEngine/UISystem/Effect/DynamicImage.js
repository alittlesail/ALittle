{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.DynamicImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._real_width = 0;
		this._real_height = 0;
		this._show = ALittle.NewObject(JavaScript.JImage);
	},
	GetSurface : function(redraw) {
		return this._texture.GetSurface(redraw);
	},
	SetRangeColor : function(buffer) {
		if (this._base_texture !== undefined) {
			let width = this._real_width;
			let height = this._real_height;
			for (let x = 0; x < width; x += 1) {
				for (let y = 0; y < height; y += 1) {
					let index = y * width + x;
					this._data[index - 1] = buffer.get(index);
				}
			}
			this._base_texture.update();
		}
	},
	SetSurfaceSize : function(width, height, color) {
		this._real_width = width;
		this._real_height = height;
		{
			if (this._texture !== undefined && (this._texture.GetWidth() !== width || this._texture.GetHeight() !== height)) {
				this._show.ClearTexture();
				this._texture = undefined;
			}
			let len = width * height;
			let buffer = new ArrayBuffer(len * 4);
			let array = new Uint32Array(buffer);
			this._data = array;
			for (let i = 0; i < len; i += 1) {
				this._data[i - 1] = color;
			}
			let res_options = {};
			res_options.width = width;
			res_options.height = height;
			let resource = new PIXI.BufferResource(new Uint8Array(buffer), res_options);
			let tex_options = {};
			tex_options.width = width;
			tex_options.height = height;
			tex_options.scaleMode = 0;
			this._base_texture = new PIXI.BaseTexture(resource, tex_options);
			let texture = new PIXI.Texture(this._base_texture);
			this._texture = ALittle.NewObject(JavaScript.JTexture, texture, width, height);
			this._show.SetTexture(this._texture);
		}
	},
	SetRenderMode : function(mode) {
		this._texture.SetRenderMode(mode);
	},
	Clear : function() {
		if (this._texture === undefined) {
			return;
		}
		this._texture.Clear();
	},
}, "ALittle.DynamicImage");

}