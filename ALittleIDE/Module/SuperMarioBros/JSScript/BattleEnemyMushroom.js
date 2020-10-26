{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


SuperMarioBros.EnemyMushroomState = {
	EMS_IDLE : 0,
	EMS_WALK : 1,
	EMS_FALL : 2,
	EMS_DEATH : 3,
}

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.BattleEnemyMushroom = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this._walk_frame_change = 0.0;
		this._walk_frame = 1;
	},
	Init : function(row, col) {
		this._state = SuperMarioBros.EnemyMushroomState.EMS_IDLE;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this.x = col * SuperMarioBros.TILE_WIDTH;
		this.y = row * SuperMarioBros.TILE_HEIGHT;
	},
	get state() {
		return this._state;
	},
	Death : function() {
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_DEATH) {
			return;
		}
		this._state = SuperMarioBros.EnemyMushroomState.EMS_DEATH;
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._sprite, "height", 5, 100, 0));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._sprite, "y", this.height - 5, 100, 0));
		group.Start();
	},
	TryWalk : function() {
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_DEATH) {
			return;
		}
		if (this._state !== SuperMarioBros.EnemyMushroomState.EMS_IDLE) {
			return;
		}
		this._state = SuperMarioBros.EnemyMushroomState.EMS_WALK;
		this._vx = -1;
	},
	UpdateFrame : function(frame_time) {
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_DEATH) {
			return;
		}
		this._vx = this._vx + (this._ax * frame_time);
		this._vy = this._vy + (this._ay * frame_time);
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_IDLE) {
			this.x = this.x + (this._vx);
			this.y = this.y + (this._vy);
		} else if (this._state === SuperMarioBros.EnemyMushroomState.EMS_WALK) {
			this.x = this.x + (this._vx);
			let [check_right, right_x] = g_GCenter.battle_scene.CheckRight(this);
			if (check_right) {
				this.x = right_x - this.width;
				this._vx = -this._vx;
			}
			let [check_left, left_x] = g_GCenter.battle_scene.CheckLeft(this);
			if (check_left) {
				this.x = left_x;
				this._vx = -this._vx;
			}
			this.y = this.y + (this._vy);
		} else if (this._state === SuperMarioBros.EnemyMushroomState.EMS_FALL) {
			this.y = this.y + (this._vy);
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (check_down) {
				this._state = SuperMarioBros.EnemyMushroomState.EMS_WALK;
				this._vy = 0;
				this._ay = 0;
				this._vx = -1;
				this.y = down_y - this.height;
			}
			this.x = this.x + (this._vx);
			let [check_right, right_x] = g_GCenter.battle_scene.CheckRight(this);
			if (check_right) {
				this.x = right_x - this.width;
				this._vx = -this._vx;
			}
			let [check_left, left_x] = g_GCenter.battle_scene.CheckLeft(this);
			if (check_left) {
				this.x = left_x;
				this._vx = -this._vx;
			}
		} else {
			this.x = this.x + (this._vx);
			this.y = this.y + (this._vy);
		}
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_WALK || this._state === SuperMarioBros.EnemyMushroomState.EMS_IDLE) {
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (!check_down) {
				this._state = SuperMarioBros.EnemyMushroomState.EMS_FALL;
				this._vy = 0;
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE;
			}
		}
		if (this._state === SuperMarioBros.EnemyMushroomState.EMS_WALK) {
			this.WalkUpdateFrame(frame_time);
		}
	},
	WalkUpdateFrame : function(frame_time) {
		let rate = 0.003;
		this._walk_frame_change = this._walk_frame_change + (rate * frame_time * (1 + ALittle.Math_Abs(this._vx)));
		if (this._walk_frame_change >= 1) {
			this._walk_frame_change = 0.0;
			this._walk_frame = this._walk_frame + (1);
			if (this._walk_frame >= 3) {
				this._walk_frame = 1;
			}
			this._sprite.col_index = this._walk_frame;
		}
	},
}, "SuperMarioBros.BattleEnemyMushroom");

}