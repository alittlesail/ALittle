{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Image = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JImage);
		this._texture_width = 0;
		this._texture_height = 0;
		this._tex_coord_t = 0;
		this._tex_coord_b = 1;
		this._tex_coord_l = 0;
		this._tex_coord_r = 1;
		this._flip = 0;
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFLButtonUp);
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			c_event.count = event.count;
			this.DispatchEvent(___all_struct.get(-449066808), c_event);
		}
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), c_event);
		}
	},
	HandleFLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), c_event);
		}
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
	CopyTextureRef : function(image) {
		if (image === undefined || image._texture === undefined) {
			return;
		}
		this._texture_name = image._texture_name;
		this._texture_cut = undefined;
		if (image._texture_cut !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = image._texture_cut.max_width;
			this._texture_cut.max_height = image._texture_cut.max_height;
			this._texture_cut.cache = image._texture_cut.cache;
		}
		this._texture = image._texture;
		this._show.SetTexture(image._texture.GetTexture());
		this.SetTextureCoord(image._tex_coord_t, image._tex_coord_b, image._tex_coord_l, image._tex_coord_r);
		this._texture_width = image._texture_width;
		this._texture_height = image._texture_height;
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
	SetTextureCut : function(texture_name, max_width, max_height, cache, callback) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			if (max_width === undefined) {
				max_width = 0;
			}
			this._texture_cut.max_width = max_width;
			if (max_height === undefined) {
				max_height = 0;
			}
			this._texture_cut.max_height = max_height;
			this._texture_cut.cache = cache;
			A_LoadTextureManager.SetTextureCut(this, texture_name, max_width, max_height, cache, callback);
		}
	},
	set texture_cut(param) {
		this.SetTextureCut(param.texture_name, param.max_width, param.max_height, param.cache);
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
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._tex_coord_t = t;
		this._tex_coord_b = b;
		this._tex_coord_l = l;
		this._tex_coord_r = r;
		this._show.SetTextureCoord(t, b, l, r);
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Image");

}