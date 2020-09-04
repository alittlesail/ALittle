{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.FramePlay = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_child_index = 0;
		this._play_loop_count = 1;
		this._play_loop_index = 0;
		this._auto_play = false;
	},
	set base_y(value) {
		this._base_y = value;
	},
	get base_y() {
		if (this._base_y !== undefined) {
			return this._base_y;
		}
		return this.height;
	},
	set auto_play(value) {
		this._auto_play = value;
		if (value) {
			this.Play();
		}
	},
	get auto_play() {
		return this._auto_play;
	},
	AddChild : function(child, index) {
		if (ALittle.DisplayLayout.AddChild.call(this, child, index) === false) {
			return false;
		}
		child.visible = false;
		return true;
	},
	set interval(value) {
		if (this._interval === value) {
			return;
		}
		this._interval = value;
		if (this._play_loop !== undefined) {
			this.Play();
		}
	},
	get interval() {
		return this._interval;
	},
	set play_loop_count(value) {
		if (this._play_loop_count === value) {
			return;
		}
		this._play_loop_count = value;
		if (this._play_loop !== undefined) {
			this.Play();
		}
	},
	get play_loop_count() {
		return this._play_loop_count;
	},
	IsPlaying : function() {
		return this._play_loop !== undefined;
	},
	Play : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
		this._play_child_index = 0;
		this._play_loop_index = 0;
		this.HideAllChild();
		this._play_loop = ALittle.NewObject(ALittle.LoopFunction, this.PlayUpdateLoop.bind(this), -1, this._interval, 0);
		A_WeakLoopSystem.AddUpdater(this._play_loop);
	},
	Stop : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
	},
	HideAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.visible = false;
			if ((child).__class === ALittle.FramePlay) {
				child.HideAllChild();
			}
		}
	},
	ShowAllChild : function() {
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.visible = true;
			if ((child).__class === ALittle.FramePlay) {
				child.ShowAllChild();
			}
		}
	},
	PlayUpdateLoop : function() {
		this.PlayUpdate();
	},
	PlayUpdate : function() {
		if (this._child_count === 0 || (this._play_loop_count > 0 && this._play_loop_index > this._play_loop_count)) {
			if (this._play_loop !== undefined) {
				this._play_loop.SetCompleted();
				this._play_loop = undefined;
			}
			return false;
		}
		if (this._play_child_index > 0) {
			let child = this._childs[this._play_child_index - 1];
			if ((child).__class === ALittle.FramePlay) {
				if (child.PlayUpdate()) {
					return true;
				}
			}
			child = this._childs[this._play_child_index - 1];
			if (child !== undefined) {
				child.visible = false;
			}
		}
		++ this._play_child_index;
		if (this._play_child_index > this._child_count) {
			this._play_child_index = 1;
			if (this._play_loop_count > 0) {
				++ this._play_loop_index;
				if (this._play_loop_index >= this._play_loop_count) {
					if (this._play_loop !== undefined) {
						this._play_loop.SetCompleted();
						this._play_loop = undefined;
					}
					return false;
				}
			}
		}
		this._childs[this._play_child_index - 1].visible = true;
		let child = this._childs[this._play_child_index - 1];
		if ((child).__class === ALittle.FramePlay) {
			child._play_loop_index = 0;
			child._play_child_index = 0;
			if (child.PlayUpdate()) {
				return true;
			}
		}
		return true;
	},
}, "ALittle.FramePlay");

}