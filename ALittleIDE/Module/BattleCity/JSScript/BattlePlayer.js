{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (BattleCity.BattleRole === undefined) throw new Error(" extends class:BattleCity.BattleRole is undefined");
BattleCity.BattlePlayer = JavaScript.Class(BattleCity.BattleRole, {
	Ctor : function() {
		this._walk_frame = 0;
	},
	StartBorn : function(row, col, level, dir, speed) {
		this._level = level;
		if (this._level >= 3) {
			this._bullet_total = 2;
		} else {
			this._bullet_total = 1;
		}
		this._fire_count = 0;
		if (this._level >= 2) {
			this._bullet_speed = 0.4;
		} else {
			this._bullet_speed = 0.2;
		}
		this._dir = dir;
		this._speed = speed;
		this.x = col * g_GCenter.battle_scene.cell_size;
		this.y = row * g_GCenter.battle_scene.cell_size;
		this._sprite.visible = false;
		this._effect_explosion.Stop();
		this._effect_explosion.visible = false;
		this._effect_born.visible = true;
		this._effect_born.Play();
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleBornEnd.bind(this), 1000);
		loop.Start();
		this.UpdateWalk(0);
	},
	HandleBornEnd : function() {
		this._sprite.visible = true;
		this._effect_born.visible = false;
		this.UpdateFrame(0);
		this.UpdateWalk(0);
		this.StartShield();
	},
	LevelUp : function() {
		if (this._level >= 4) {
			return;
		}
		this._level = this._level + (1);
		if (this._level >= 3) {
			this._bullet_total = 2;
		} else {
			this._bullet_total = 1;
		}
		if (this._level >= 2) {
			this._bullet_speed = 0.4;
		} else {
			this._bullet_speed = 0.2;
		}
		this.UpdateWalk(0);
	},
	get is_enemy() {
		return false;
	},
	BeAttack : function() {
		if (this._effect_shield.visible) {
			return false;
		}
		if (this._level <= 3) {
			this.StartExplosion();
			return true;
		}
		this._level = 3;
		return false;
	},
	UpdateWalk : function(frame_time) {
		if (this._dir === BattleCity.DirType.DT_UP) {
			this._sprite.row_index = 1;
		} else if (this._dir === BattleCity.DirType.DT_RIGHT) {
			this._sprite.row_index = 2;
		} else if (this._dir === BattleCity.DirType.DT_DOWN) {
			this._sprite.row_index = 3;
		} else if (this._dir === BattleCity.DirType.DT_LEFT) {
			this._sprite.row_index = 4;
		}
		this._walk_frame = this._walk_frame + (0.01 * frame_time);
		if (this._walk_frame > 2) {
			this._walk_frame = 0;
		}
		if (this._walk_frame <= 1) {
			this._sprite.col_index = (this._level - 1) * 2 + 1;
		} else {
			this._sprite.col_index = (this._level - 1) * 2 + 2;
		}
	},
}, "BattleCity.BattlePlayer");

}