{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.ImagePlay = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_index = 0;
	},
	set path_list(value) {
		this._path_list = value;
		this.RemoveAllChild();
		if (this._path_list === undefined) {
			if (this._play_loop !== undefined) {
				A_WeakLoopSystem.RemoveUpdater(this._play_loop);
				this._play_loop = undefined;
			}
			return;
		}
		let ___OBJECT_1 = this._path_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			image.width_type = 4;
			image.height_type = 4;
			image.texture_name = v;
			image.visible = false;
			this.AddChild(image);
		}
		this.Play();
	},
	get path_list() {
		return this._path_list;
	},
	set interval(value) {
		if (this._interval === value) {
			return;
		}
		this._interval = value;
		this.Play();
	},
	get interval() {
		return this._interval;
	},
	Play : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
		if (this._path_list === undefined) {
			return;
		}
		this._play_index = 0;
		let ___OBJECT_2 = this._childs;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			v.visible = false;
		}
		this._play_loop = ALittle.NewObject(ALittle.LoopFunction, this.PlayUpdate.bind(this), -1, this._interval, 0);
		A_WeakLoopSystem.AddUpdater(this._play_loop);
	},
	Stop : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
	},
	PlayUpdate : function() {
		if (this._child_count === 0) {
			return;
		}
		if (this._play_index > 0) {
			this._childs[this._play_index - 1].visible = false;
		}
		this._play_index = this._play_index + 1;
		if (this._play_index > this._child_count) {
			this._play_index = 1;
		}
		this._childs[this._play_index - 1].visible = true;
	},
}, "ALittle.ImagePlay");

}