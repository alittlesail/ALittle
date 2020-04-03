{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.DisplayView = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(lua.__CPPAPIDisplayView);
		this._pickup_rect = true;
		this._pickup_child = true;
	},
}, "ALittle.DisplayView");

}