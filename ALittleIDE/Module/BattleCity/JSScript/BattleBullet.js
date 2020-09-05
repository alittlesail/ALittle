{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.BattleBullet = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._speed = 0.2;
	},
	TCtor : function() {
		this._effect_explosion.visible = false;
	},
	Init : function(dir, role, speed) {
		this._dir = dir;
		this._role = role;
		this._alive = true;
		this._speed = speed;
		if (this._dir === BattleCity.DirType.DT_UP) {
			this._bullet.col_index = 1;
		} else if (this._dir === BattleCity.DirType.DT_RIGHT) {
			this._bullet.col_index = 2;
		} else if (this._dir === BattleCity.DirType.DT_DOWN) {
			this._bullet.col_index = 3;
		} else {
			this._bullet.col_index = 4;
		}
	},
	get role() {
		return this._role;
	},
	get alive() {
		return this._alive;
	},
	UpdateFrame : function(frame_time) {
		let explosion = false;
		if (this._alive) {
			if (this._dir === BattleCity.DirType.DT_UP) {
				this.y = this.y - (this._speed * frame_time);
				let [check_collision, check_explosion] = g_GCenter.battle_scene.BulletCollisionByEntity(this, this.x, this.y, this.x + this.width, this.y + this.height);
				if (check_collision) {
					if (check_explosion) {
						explosion = true;
					} else {
						this.BulletEnd();
					}
				} else {
					let row = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
					let col_min = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
					let col_max = ALittle.Math_Floor((this.x + this.width - 1) / g_GCenter.battle_scene.cell_size);
					if (g_GCenter.battle_scene.BulletCollisionByMap(row, col_min, true, this._dir)) {
						explosion = true;
					}
					if (g_GCenter.battle_scene.BulletCollisionByMap(row, col_max, false, this._dir)) {
						explosion = true;
					}
					if (this.y <= 0) {
						explosion = true;
					}
				}
			} else if (this._dir === BattleCity.DirType.DT_RIGHT) {
				this.x = this.x + (this._speed * frame_time);
				let [check_collision, check_explosion] = g_GCenter.battle_scene.BulletCollisionByEntity(this, this.x, this.y, this.x + this.width, this.y + this.height);
				if (check_collision) {
					if (check_explosion) {
						explosion = true;
					} else {
						this.BulletEnd();
					}
				} else {
					let row_min = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
					let row_max = ALittle.Math_Floor((this.y + this.height - 1) / g_GCenter.battle_scene.cell_size);
					let col = ALittle.Math_Floor((this.x + this.width) / g_GCenter.battle_scene.cell_size);
					if (g_GCenter.battle_scene.BulletCollisionByMap(row_min, col, true, this._dir)) {
						explosion = true;
					}
					if (g_GCenter.battle_scene.BulletCollisionByMap(row_max, col, false, this._dir)) {
						explosion = true;
					}
					if (this.x + this.width >= g_GCenter.battle_scene.map_size) {
						explosion = true;
					}
				}
			} else if (this._dir === BattleCity.DirType.DT_DOWN) {
				this.y = this.y + (this._speed * frame_time);
				let [check_collision, check_explosion] = g_GCenter.battle_scene.BulletCollisionByEntity(this, this.x, this.y, this.x + this.width, this.y + this.height);
				if (check_collision) {
					if (check_explosion) {
						explosion = true;
					} else {
						this.BulletEnd();
					}
				} else {
					let row = ALittle.Math_Floor((this.y + this.height) / g_GCenter.battle_scene.cell_size);
					let col_min = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
					let col_max = ALittle.Math_Floor((this.x + this.width - 1) / g_GCenter.battle_scene.cell_size);
					if (g_GCenter.battle_scene.BulletCollisionByMap(row, col_min, true, this._dir)) {
						explosion = true;
					}
					if (g_GCenter.battle_scene.BulletCollisionByMap(row, col_max, false, this._dir)) {
						explosion = true;
					}
					if (this.y + this.height >= g_GCenter.battle_scene.map_size) {
						explosion = true;
					}
				}
			} else {
				this.x = this.x - (this._speed * frame_time);
				let [check_collision, check_explosion] = g_GCenter.battle_scene.BulletCollisionByEntity(this, this.x, this.y, this.x + this.width, this.y + this.height);
				if (check_collision) {
					if (check_explosion) {
						explosion = true;
					} else {
						this.BulletEnd();
					}
				} else {
					let row_min = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
					let row_max = ALittle.Math_Floor((this.y + this.height - 1) / g_GCenter.battle_scene.cell_size);
					let col = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
					if (g_GCenter.battle_scene.BulletCollisionByMap(row_min, col, true, this._dir)) {
						explosion = true;
					}
					if (g_GCenter.battle_scene.BulletCollisionByMap(row_max, col, false, this._dir)) {
						explosion = true;
					}
					if (this.x <= 0) {
						explosion = true;
					}
				}
			}
		} else {
			if (!this._effect_explosion.IsPlaying()) {
				this.BulletEnd();
			}
		}
		if (explosion) {
			this.BulletExpision();
		}
	},
	BulletExpision : function() {
		this._alive = false;
		this._bullet.visible = false;
		this._effect_explosion.visible = true;
		this._effect_explosion.Play();
	},
	BulletEnd : function() {
		this._alive = false;
		this._effect_explosion.Stop();
		this._effect_explosion.visible = false;
		let loop = ALittle.NewObject(ALittle.LoopTimer, g_GCenter.battle_scene.BulletDeath.bind(g_GCenter.battle_scene, this), 0);
		loop.Start();
	},
}, "BattleCity.BattleBullet");

}