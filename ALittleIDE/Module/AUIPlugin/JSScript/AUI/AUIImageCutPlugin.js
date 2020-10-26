{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
AUIPlugin.AUIImageCutPlugin = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._is_circle = false;
		this._cut_size = 200;
		this._MAX_WIDTH = 200;
		this._MAX_HEIGHT = 200;
		this._cut_center_x = 0;
		this._cut_center_y = 0;
		this._cut_center_w = 0;
		this._cut_center_h = 0;
	},
	EditTexture : function(file_path, is_circle, cut_size) {
		this._is_circle = is_circle || false;
		if (cut_size === undefined) {
			cut_size = 200;
		}
		this._cut_size = cut_size;
		this._file_path = file_path;
		if (this._src_image !== undefined) {
			this._image_container.RemoveChild(this._src_image);
			this._src_image = undefined;
		}
		this._src_image = ALittle.NewObject(ALittle.Image, AUIPlugin.g_Control);
		this._image_container.AddChild(this._src_image);
		this._edit_container.visible = false;
		this._edit_container.x = 0;
		this._edit_container.y = 0;
		this._edit_container.width_type = 4;
		this._edit_container.width_value = 0;
		this._edit_container.height_type = 4;
		this._edit_container.height_value = 0;
		let max_width = ALittle.System_GetMaxTextureWidth();
		if (max_width > this._edit_container.width) {
			max_width = this._edit_container.width;
		}
		let max_height = ALittle.System_GetMaxTextureHeight();
		if (max_height > this._edit_container.height) {
			max_height = this._edit_container.height;
		}
		this._src_image.x_type = 3;
		this._src_image.y_type = 3;
		this._src_image.SetTextureCut(file_path, ALittle.Math_Floor(max_width), ALittle.Math_Floor(max_height), false, this.LoadTextureCallback.bind(this));
	},
	Clear : function() {
		if (this._src_image !== undefined) {
			this._image_container.RemoveChild(this._src_image);
			this._src_image = undefined;
		}
		this._edit_container.visible = false;
	},
	Cut : function(target_path) {
		if (this._cut_center_w <= 0) {
			return false;
		}
		if (this._cut_center_h <= 0) {
			return false;
		}
		if (target_path === undefined) {
			target_path = this._file_path;
		}
		let surface = carp.LoadCarpSurface(this._file_path);
		if (surface === undefined) {
			return false;
		}
		let width = carp.GetCarpSurfaceWidth(surface);
		let height = carp.GetCarpSurfaceHeight(surface);
		let rate_w = this._edit_container.width / width;
		let rate_h = this._edit_container.height / height;
		let cut_x = ALittle.Math_Floor(this._cut_center_x / rate_w);
		let cut_y = ALittle.Math_Floor(this._cut_center_y / rate_h);
		let cut_width = ALittle.Math_Ceil(this._cut_center_w / rate_w);
		let cut_height = ALittle.Math_Ceil(this._cut_center_h / rate_h);
		let new_width = cut_width;
		if (new_width > this._MAX_WIDTH) {
			new_width = this._MAX_WIDTH;
		}
		let new_height = cut_height;
		if (new_height > this._MAX_HEIGHT) {
			new_height = this._MAX_HEIGHT;
		}
		let new_surface = carp.CreateCarpSurface(ALittle.Math_Floor(new_width), ALittle.Math_Floor(new_height));
		carp.CutBlitCarpSurface(surface, new_surface, cut_x + "," + cut_y + "," + cut_width + "," + cut_height, "0,0," + new_width + "," + new_height);
		carp.FreeCarpSurface(surface);
		if (this._is_circle) {
			let new_center = new_width / 2;
			let gradual_len = ALittle.Math_Floor(new_center * 0.05);
			for (let row = 0; row <= new_height - 1; row += 1) {
				for (let col = 0; col <= new_width - 1; col += 1) {
					let x2 = (new_center - col) * (new_center - col);
					let y2 = (new_center - row) * (new_center - row);
					let distance = ALittle.Math_Sqrt(x2 + y2);
					if (distance > new_center) {
						carp.SetCarpSurfacePixel(new_surface, col, row, 0);
					} else if (gradual_len > 0 && new_center - distance < gradual_len) {
						let color = carp.GetCarpSurfacePixel(new_surface, col, row);
						let src_alpha = carp.GetPixelAlpha(color);
						let dst_alpha = ALittle.Math_Sin((3.14159625 / 2) * (new_center - distance) / gradual_len) * 255;
						if (src_alpha < dst_alpha) {
							dst_alpha = src_alpha;
						}
						color = carp.SetPixelAlpha(color, ALittle.Math_Ceil(dst_alpha));
						carp.SetCarpSurfacePixel(new_surface, col, row, color);
					}
				}
			}
		}
		let result = carp.SaveCarpSurface(new_surface, target_path);
		carp.FreeCarpSurface(new_surface);
		return result;
	},
	LoadTextureCallback : function(image, result) {
		if (result === false) {
			return;
		}
		if (this._src_image !== image) {
			return;
		}
		image.width = image.texture_width;
		image.height = image.texture_height;
		image.UpdateLayout();
		this._edit_container.visible = true;
		this._edit_container.x = image.x;
		this._edit_container.y = image.y;
		this._edit_container.width = image.width;
		this._edit_container.height = image.height;
		if (this._cut_size > image.width) {
			this._cut_size = image.width;
		}
		if (this._cut_size > image.height) {
			this._cut_size = image.height;
		}
		this._cut_center_x = (image.width - this._cut_size) / 2;
		this._cut_center_y = (image.height - this._cut_size) / 2;
		this._cut_center_w = this._cut_size;
		this._cut_center_h = this._cut_size;
		this.UpdateEditQuad(this._cut_center_x, this._cut_center_y, this._cut_center_w, this._cut_center_h);
	},
	UpdateEditQuad : function(x, y, w, h) {
		this._edit_grid9.top_size = y;
		this._edit_grid9.bottom_size = ALittle.Math_Ceil(this._edit_container.height - y - h);
		this._edit_grid9.left_size = x;
		this._edit_grid9.right_size = ALittle.Math_Ceil(this._edit_container.width - x - w);
		this._left_top_drag.x = x - this._left_top_drag.width / 2;
		this._left_top_drag.y = y - this._left_top_drag.height / 2;
		this._right_top_drag.x = x + w - this._right_top_drag.width / 2;
		this._right_top_drag.y = y - this._right_top_drag.height / 2;
		this._left_bottom_drag.x = x - this._left_bottom_drag.width / 2;
		this._left_bottom_drag.y = y + h - this._left_bottom_drag.height / 2;
		this._right_bottom_drag.x = x + w - this._right_bottom_drag.width / 2;
		this._right_bottom_drag.y = y + h - this._right_bottom_drag.height / 2;
	},
	HandleDrag : function(event) {
		if (event.target === this._left_top_drag) {
			let delta_x = event.delta_x;
			let delta_y = event.delta_y;
			if (this._is_circle) {
				if (ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)) {
					delta_y = delta_x;
				} else {
					delta_x = delta_y;
				}
			}
			this._cut_center_x = this._cut_center_x + delta_x;
			this._cut_center_y = this._cut_center_y + delta_y;
			this._cut_center_w = this._cut_center_w - delta_x;
			this._cut_center_h = this._cut_center_h - delta_y;
		} else if (event.target === this._right_top_drag) {
			let delta_x = event.delta_x;
			let delta_y = event.delta_y;
			if (this._is_circle) {
				if (ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)) {
					delta_y = -delta_x;
				} else {
					delta_x = -delta_y;
				}
			}
			this._cut_center_y = this._cut_center_y + delta_y;
			this._cut_center_w = this._cut_center_w + delta_x;
			this._cut_center_h = this._cut_center_h - delta_y;
		} else if (event.target === this._left_bottom_drag) {
			let delta_x = event.delta_x;
			let delta_y = event.delta_y;
			if (this._is_circle) {
				if (ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)) {
					delta_y = -delta_x;
				} else {
					delta_x = -delta_y;
				}
			}
			this._cut_center_x = this._cut_center_x + delta_x;
			this._cut_center_w = this._cut_center_w - delta_x;
			this._cut_center_h = this._cut_center_h + delta_y;
		} else if (event.target === this._right_bottom_drag) {
			let delta_x = event.delta_x;
			let delta_y = event.delta_y;
			if (this._is_circle) {
				if (ALittle.Math_Abs(delta_x) > ALittle.Math_Abs(delta_y)) {
					delta_y = delta_x;
				} else {
					delta_x = delta_y;
				}
			}
			this._cut_center_w = this._cut_center_w + delta_x;
			this._cut_center_h = this._cut_center_h + delta_y;
		} else if (event.target === this._center_drag) {
			this._cut_center_x = this._cut_center_x + event.delta_x;
			this._cut_center_y = this._cut_center_y + event.delta_y;
		}
		if (this._cut_center_x < 0) {
			this._cut_center_x = 0;
		}
		if (this._cut_center_x > this._edit_container.width) {
			this._cut_center_x = this._edit_container.width;
		}
		if (this._cut_center_y < 0) {
			this._cut_center_y = 0;
		}
		if (this._cut_center_y > this._edit_container.height) {
			this._cut_center_y = this._edit_container.height;
		}
		if (this._cut_center_x + this._cut_center_w > this._edit_container.width) {
			this._cut_center_w = this._edit_container.width - this._cut_center_x;
		}
		if (this._cut_center_w < 0) {
			this._cut_center_w = 0;
		}
		if (this._cut_center_y + this._cut_center_h > this._edit_container.height) {
			this._cut_center_h = this._edit_container.height - this._cut_center_y;
		}
		if (this._cut_center_h < 0) {
			this._cut_center_h = 0;
		}
		this.UpdateEditQuad(this._cut_center_x, this._cut_center_y, this._cut_center_w, this._cut_center_h);
	},
}, "AUIPlugin.AUIImageCutPlugin");

}