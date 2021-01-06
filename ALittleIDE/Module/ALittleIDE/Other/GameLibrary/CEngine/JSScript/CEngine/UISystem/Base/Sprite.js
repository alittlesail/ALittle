{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Sprite = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JSprite);
		this._texture_width = 0;
		this._texture_height = 0;
		this._tex_coord_t = 0;
		this._tex_coord_b = 1;
		this._tex_coord_l = 0;
		this._tex_coord_r = 1;
		this._row_count = 1;
		this._col_count = 1;
		this._row_index = 1;
		this._col_index = 1;
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
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, 0, 0, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	CopyTextureRef : function(sprite) {
		if (sprite === undefined || sprite._texture === undefined) {
			return;
		}
		this._texture_name = sprite._texture_name;
		this._texture_cut = undefined;
		if (sprite._texture_cut !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = sprite._texture_cut.max_width;
			this._texture_cut.max_height = sprite._texture_cut.max_height;
			this._texture_cut.cache = sprite._texture_cut.cache;
		}
		this._texture = sprite._texture;
		this._show.SetTexture(sprite._texture.GetTexture());
		this.SetTextureCoord(sprite._tex_coord_t, sprite._tex_coord_b, sprite._tex_coord_l, sprite._tex_coord_r);
		this._texture_width = sprite._texture_width;
		this._texture_height = sprite._texture_height;
		this.row_count = sprite.row_count;
		this.col_count = sprite.col_count;
		this.row_index = sprite.row_index;
		this.col_index = sprite.col_index;
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
	SetTextureCut : function(texture_name, cache, index) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			this._texture_cut.cache = cache;
			A_LoadTextureManager.SetTextureCut(this, texture_name, 0, 0, cache);
		}
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
	set row_count(value) {
		this._row_count = value;
		this._show.SetRowColCount(this._row_count, this._col_count);
	},
	get row_count() {
		return this._row_count;
	},
	set col_count(value) {
		this._col_count = value;
		this._show.SetRowColCount(this._row_count, this._col_count);
	},
	get col_count() {
		return this._col_count;
	},
	set row_index(value) {
		this._row_index = value;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get row_index() {
		return this._row_index;
	},
	set col_index(value) {
		this._col_index = value;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get col_index() {
		return this._col_index;
	},
	SetRowCol : function(row, col) {
		this._row_index = row;
		this._col_index = col;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Sprite");

}