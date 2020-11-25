{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.DynamicImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(lua.__CPPAPIImage);
		this._texture = ALittle.NewObject(lua.__CPPAPIDynamicTexture);
		this._show.SetTexture(this._texture);
	},
	GetSurface : function(redraw) {
		return this._texture.GetSurface(redraw);
	},
	SetSurfaceSize : function(width, height, color) {
		this._texture.SetSurfaceSize(width, height, color);
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