{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


SuperMarioBros.LifeMushroomState = {
	LMS_BORN : 0,
	LMS_WALK : 1,
}

if (ALittle.Image === undefined) throw new Error(" extends class:ALittle.Image is undefined");
SuperMarioBros.BattleLifeMushroom = JavaScript.Class(ALittle.Image, {
	Ctor : function() {
		this._level = 1;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this._born_y = 0;
	},
	Born : function(row, col) {
		this._state = SuperMarioBros.LifeMushroomState.LMS_BORN;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this.x = col * SuperMarioBros.TILE_WIDTH;
		this.y = row * SuperMarioBros.TILE_HEIGHT;
		this._born_y = this.y - SuperMarioBros.TILE_HEIGHT;
	},
	UpdateFrame : function(frame_time) {
		this._vx = this._vx + (this._ax * frame_time);
		this._vy = this._vy + (this._ay * frame_time);
		if (this._state === SuperMarioBros.LifeMushroomState.LMS_BORN) {
			this.y = this.y - (0.03 * frame_time);
			if (this.y <= this._born_y) {
				this.y = this._born_y;
				this._state = SuperMarioBros.LifeMushroomState.LMS_WALK;
				this._vx = 1;
				this._ay = 0.01;
			}
		} else if (this._state === SuperMarioBros.LifeMushroomState.LMS_WALK) {
			this.y = this.y + (this._vy);
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (check_down) {
				this.y = down_y - this.height;
				this._vy = 0;
			}
			this.x = this.x + (this._vx);
			let [check_right, right_x] = g_GCenter.battle_scene.CheckRight(this);
			if (check_right) {
				this.x = right_x - this.width;
			}
			let [check_left, left_x] = g_GCenter.battle_scene.CheckLeft(this);
			if (check_left) {
				this.x = left_x;
			}
		}
	},
}, "SuperMarioBros.BattleLifeMushroom");

}