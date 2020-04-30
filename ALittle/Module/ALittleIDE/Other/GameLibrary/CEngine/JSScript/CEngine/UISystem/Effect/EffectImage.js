{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.EffectImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
	},
	Action : function(control) {
		if (control === undefined) {
			return;
		}
		this._show = ALittle.NewObject(lua.__CPPAPIImage);
		this._texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		this.x = control.x;
		this.y = control.y;
		this.width = control.width;
		this.height = control.height;
		control._show.SetX(0);
		control._show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = this._texture.Draw(control._show, lua.math.floor(this.width), lua.math.floor(this.height), 1);
		control._show.SetX(this._x);
		control._show.SetY(this._y);
		if (result) {
			this._show.SetTexture(this._texture);
		}
		this._show.SetTextureCoord(0, 1, 0, 1);
		this.disabled = true;
	},
	Clear : function() {
		if (this._texture === undefined) {
			return;
		}
		this._texture.Clear();
	},
}, "ALittle.EffectImage");

}