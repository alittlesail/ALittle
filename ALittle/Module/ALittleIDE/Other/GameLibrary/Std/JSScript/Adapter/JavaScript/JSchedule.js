{
if (typeof JavaScript === "undefined") window.JavaScript = {};


if (ALittle.ISchedule === undefined) throw new Error(" extends class:ALittle.ISchedule is undefined");
JavaScript.JSchedule = JavaScript.Class(ALittle.ISchedule, {
	Ctor : function() {
		let global = window;
		this._requestAnimationFrame = global["requestAnimationFrame"];
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["mozRequestAnimationFrame"];
		}
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["webkitRequestAnimationFrame"];
		}
		if (this._requestAnimationFrame === undefined) {
			this._requestAnimationFrame = global["msRequestAnimationFrame"];
		}
		this._callback = this.MainLoop.bind(this);
		this._run = false;
	},
	Run : function() {
		this.RunInFrame();
	},
	RunInFrame : function() {
		if (this._run) {
			return;
		}
		this._run = true;
		if (this._requestAnimationFrame !== undefined) {
			this._requestAnimationFrame.call(window, this._callback);
		} else {
			ALittle.Error("current browser is not support requestAnimationFrame");
		}
	},
	MainLoop : function(cur_time) {
		if (this._last_time === undefined) {
			this._last_time = cur_time;
			return;
		}
		A_JLoopSystem.Update(cur_time - this._last_time);
		this._last_time = cur_time;
		this._requestAnimationFrame.call(window, this._callback);
	},
}, "JavaScript.JSchedule");

window.A_JSchedule = ALittle.NewObject(JavaScript.JSchedule);
}