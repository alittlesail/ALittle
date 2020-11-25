{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name : "ALittle.UIButtonDragEvent", ns_name : "ALittle", rl_name : "UIButtonDragEvent", hash_code : 1337289812,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIDrawingBoard = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._pan_size = 5;
		this._pan_color = 0;
		this._draw_width = 0;
		this._draw_height = 0;
	},
	TCtor : function() {
		this._image = ALittle.NewObject(ALittle.DynamicImage, this._ctrl_sys);
		this._image.width_type = 4;
		this._image.height_type = 4;
		this._image.SetRenderMode(1);
		this.AddChild(this._image);
		this._image.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._image.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
	},
	SetPan : function(size, color) {
		this._pan_size = size;
		if (this._pan_size < 1) {
			this._pan_size = 1;
		}
		this._pan_color = color;
	},
	SetDrawSize : function(width, height, color) {
		this._draw_width = width;
		this._draw_height = height;
		if (this._draw_width < 0) {
			this._draw_width = 0;
		}
		if (this._draw_height < 0) {
			this._draw_height = 0;
		}
		this._image.SetSurfaceSize(this._draw_width, this._draw_height, color);
	},
	ClearContent : function(color) {
		this._image.SetSurfaceSize(this._draw_width, this._draw_height, color);
	},
	get surface() {
		return this._image.GetSurface(false);
	},
	HandleDrag : function(event) {
		let x_rate = event.rel_x / event.target.width;
		if (x_rate > 1) {
			x_rate = 1;
		}
		let y_rate = event.rel_y / event.target.height;
		if (y_rate > 1) {
			y_rate = 1;
		}
		let x = ALittle.Math_Floor(this._draw_width * x_rate);
		let y = ALittle.Math_Floor(this._draw_height * y_rate);
		let surface = this._image.GetSurface(true);
		let range = ALittle.Math_Floor((this._pan_size - 1) / 2);
		for (let col = x - range; col <= x + range; col += 1) {
			for (let row = y - range; row <= y + range; row += 1) {
				carp.SetCarpSurfacePixel(surface, col, row, this._pan_color);
			}
		}
	},
	HandleDragEnd : function(event) {
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
}, "AUIPlugin.AUIDrawingBoard");

}