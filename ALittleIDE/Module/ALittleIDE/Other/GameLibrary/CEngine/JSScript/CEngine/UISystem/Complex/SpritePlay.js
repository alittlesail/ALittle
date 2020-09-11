{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.Sprite === undefined) throw new Error(" extends class:ALittle.Sprite is undefined");
ALittle.SpritePlay = JavaScript.Class(ALittle.Sprite, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_index = 0;
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
		this._play_index = 0;
		this._row_index = 1;
		this._col_index = 1;
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
		let total_count = this._row_count * this._col_count;
		++ this._play_index;
		this._play_index = this._play_index % total_count;
		this.row_index = ALittle.Math_Floor(this._play_index / this._row_count) + 1;
		this.col_index = this._play_index % this._col_count + 1;
	},
}, "ALittle.SpritePlay");

}