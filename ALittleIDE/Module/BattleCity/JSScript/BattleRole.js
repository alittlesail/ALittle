{
if (typeof BattleCity === "undefined") window.BattleCity = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
BattleCity.BattleRole = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._level = 1;
		this._dir = 1;
		this._bullet_total = 1;
		this._fire_count = 0;
		this._speed = 0;
		this._bullet_speed = 0.2;
	},
	TCtor : function() {
		this._sprite.visible = false;
		this._effect_born.visible = false;
		this._effect_shield.visible = false;
		this._effect_explosion.visible = false;
	},
	get is_enemy() {
		return false;
	},
	get alive() {
		if (this._effect_born.visible) {
			return false;
		}
		if (this._effect_explosion.visible) {
			return false;
		}
		return true;
	},
	get explosion() {
		return this._effect_explosion.visible;
	},
	get dir() {
		return this._dir;
	},
	get level() {
		return this._level;
	},
	StartExplosion : function() {
		this._sprite.visible = false;
		this._effect_explosion.visible = true;
		this._effect_explosion.Play();
		if (this._effect_explosion_loop !== undefined) {
			this._effect_explosion_loop.Stop();
		}
		this._effect_explosion_loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleExplosionEnd.bind(this), 1000);
		this._effect_explosion_loop.Start();
	},
	StartShield : function() {
		this._effect_shield.visible = true;
		this._effect_shield.Play();
		if (this._effect_shield_loop !== undefined) {
			this._effect_shield_loop.Stop();
		}
		this._effect_shield_loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleShieldStop.bind(this), 5000);
		this._effect_shield_loop.Start();
	},
	UpdateFrame : function(frame_time) {
	},
	UpdateWalk : function(frame_time) {
	},
	BeAttack : function() {
		return true;
	},
	Fire : function() {
		if (this._fire_count >= this._bullet_total) {
			return;
		}
		this._fire_count = this._fire_count + (1);
		g_GCenter.battle_scene.FireBullet(this, this._bullet_speed);
	},
	WalkImpl : function(dir, frame_time, adjust) {
		if (dir === BattleCity.DirType.DT_UP) {
			let col_min = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
			let col_max = ALittle.Math_Floor((this.x + this.width - 1) / g_GCenter.battle_scene.cell_size);
			let cur_row = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
			let y = this.y - frame_time * this._speed;
			if (y <= 0) {
				y = 0;
			}
			let next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size);
			let target = this.y;
			let break_row = cur_row;
			for (let row = cur_row; row >= next_row; row += -1) {
				let failed = false;
				for (let col = col_min; col <= col_max; col += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, col)) {
						break_row = row;
						failed = true;
						break;
					}
				}
				if (failed) {
					break;
				}
				target = row * g_GCenter.battle_scene.cell_size;
			}
			if (target < y) {
				target = y;
			}
			if (!g_GCenter.battle_scene.CanWalkByEntity(this, this.x, target, this.x + this.width, target + this.height)) {
				return false;
			}
			if (this.y === target) {
				if (!adjust) {
					return false;
				}
				for (let col = col_min + 1; col < col_max; col += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(break_row, col)) {
						return false;
					}
				}
				let left_check = g_GCenter.battle_scene.CanWalkByMap(break_row, col_min);
				let right_check = g_GCenter.battle_scene.CanWalkByMap(break_row, col_max);
				if (!left_check) {
					return this.WalkImpl(BattleCity.DirType.DT_RIGHT, frame_time, false);
				} else if (!right_check) {
					return this.WalkImpl(BattleCity.DirType.DT_LEFT, frame_time, false);
				}
				return false;
			}
			this.y = target;
			return true;
		}
		if (dir === BattleCity.DirType.DT_DOWN) {
			let col_min = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
			let col_max = ALittle.Math_Floor((this.x + this.width - 1) / g_GCenter.battle_scene.cell_size);
			let bottom = this.y + this.height;
			let cur_row = ALittle.Math_Floor(bottom / g_GCenter.battle_scene.cell_size);
			let y = bottom + frame_time * this._speed;
			if (y >= g_GCenter.battle_scene.map_size) {
				y = g_GCenter.battle_scene.map_size;
			}
			let next_row = ALittle.Math_Floor(y / g_GCenter.battle_scene.cell_size);
			let target = bottom;
			let break_row = cur_row;
			for (let row = cur_row; row <= next_row; row += 1) {
				let failed = false;
				for (let col = col_min; col <= col_max; col += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, col)) {
						break_row = row;
						failed = true;
						break;
					}
				}
				if (failed) {
					break;
				}
				target = (row + 1) * g_GCenter.battle_scene.cell_size;
			}
			if (target > y) {
				target = y;
			}
			if (!g_GCenter.battle_scene.CanWalkByEntity(this, this.x, target - this.height, this.x + this.width, target)) {
				return false;
			}
			if (this.y === target - this.height) {
				if (!adjust) {
					return false;
				}
				for (let col = col_min + 1; col < col_max; col += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(break_row, col)) {
						return false;
					}
				}
				let left_check = g_GCenter.battle_scene.CanWalkByMap(break_row, col_min);
				let right_check = g_GCenter.battle_scene.CanWalkByMap(break_row, col_max);
				if (!left_check) {
					return this.WalkImpl(BattleCity.DirType.DT_RIGHT, frame_time, false);
				} else if (!right_check) {
					return this.WalkImpl(BattleCity.DirType.DT_LEFT, frame_time, false);
				}
				return false;
			}
			this.y = target - this.height;
			return true;
		}
		if (dir === BattleCity.DirType.DT_LEFT) {
			let row_min = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
			let row_max = ALittle.Math_Floor((this.y + this.height - 1) / g_GCenter.battle_scene.cell_size);
			let cur_col = ALittle.Math_Floor(this.x / g_GCenter.battle_scene.cell_size);
			let x = this.x - frame_time * this._speed;
			if (x <= 0) {
				x = 0;
			}
			let next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size);
			let target = this.x;
			let break_col = cur_col;
			for (let col = cur_col; col >= next_col; col += -1) {
				let failed = false;
				for (let row = row_min; row <= row_max; row += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, col)) {
						break_col = col;
						failed = true;
						break;
					}
				}
				if (failed) {
					break;
				}
				target = col * g_GCenter.battle_scene.cell_size;
			}
			if (target < x) {
				target = x;
			}
			if (!g_GCenter.battle_scene.CanWalkByEntity(this, target, this.y, target + this.width, this.y + this.height)) {
				return false;
			}
			if (this.x === target) {
				if (!adjust) {
					return false;
				}
				for (let row = row_min + 1; row < row_max; row += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, break_col)) {
						return false;
					}
				}
				let up_check = g_GCenter.battle_scene.CanWalkByMap(row_min, break_col);
				let down_check = g_GCenter.battle_scene.CanWalkByMap(row_max, break_col);
				if (!up_check) {
					return this.WalkImpl(BattleCity.DirType.DT_DOWN, frame_time, false);
				} else if (!down_check) {
					return this.WalkImpl(BattleCity.DirType.DT_UP, frame_time, false);
				}
				return false;
			}
			this.x = target;
			return true;
		}
		if (dir === BattleCity.DirType.DT_RIGHT) {
			let row_min = ALittle.Math_Floor(this.y / g_GCenter.battle_scene.cell_size);
			let row_max = ALittle.Math_Floor((this.y + this.height - 1) / g_GCenter.battle_scene.cell_size);
			let right = this.x + this.width;
			let cur_col = ALittle.Math_Floor(right / g_GCenter.battle_scene.cell_size);
			let x = right + frame_time * this._speed;
			if (x >= g_GCenter.battle_scene.map_size) {
				x = g_GCenter.battle_scene.map_size;
			}
			let next_col = ALittle.Math_Floor(x / g_GCenter.battle_scene.cell_size);
			let target = right;
			let break_col = cur_col;
			for (let col = cur_col; col <= next_col; col += 1) {
				let failed = false;
				for (let row = row_min; row <= row_max; row += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, col)) {
						break_col = col;
						failed = true;
						break;
					}
				}
				if (failed) {
					break;
				}
				target = (col + 1) * g_GCenter.battle_scene.cell_size;
			}
			if (target > x) {
				target = x;
			}
			if (!g_GCenter.battle_scene.CanWalkByEntity(this, target - this.width, this.y, target, this.y + this.height)) {
				return false;
			}
			if (this.x === target - this.width) {
				if (!adjust) {
					return false;
				}
				for (let row = row_min + 1; row < row_max; row += 1) {
					if (!g_GCenter.battle_scene.CanWalkByMap(row, break_col)) {
						return false;
					}
				}
				let up_check = g_GCenter.battle_scene.CanWalkByMap(row_min, break_col);
				let down_check = g_GCenter.battle_scene.CanWalkByMap(row_max, break_col);
				if (!up_check) {
					return this.WalkImpl(BattleCity.DirType.DT_DOWN, frame_time, false);
				} else if (!down_check) {
					return this.WalkImpl(BattleCity.DirType.DT_UP, frame_time, false);
				}
				return false;
			}
			this.x = target - this.width;
			return true;
		}
		return false;
	},
	Walk : function(dir, frame_time) {
		this._dir = dir;
		this.UpdateWalk(frame_time);
		return this.WalkImpl(dir, frame_time, true);
	},
	HandleExplosionEnd : function() {
		let loop = ALittle.NewObject(ALittle.LoopTimer, g_GCenter.battle_scene.RoleDeath.bind(g_GCenter.battle_scene, this), 0);
		loop.Start();
	},
	HandleShieldStop : function() {
		this._effect_shield.visible = false;
		this._effect_shield.Stop();
	},
	AddBullet : function() {
		if (this._fire_count <= 0) {
			return;
		}
		this._fire_count = this._fire_count - (1);
	},
	Clear : function() {
		this._effect_born.Stop();
		this._effect_shield.Stop();
		this._effect_explosion.Stop();
	},
}, "BattleCity.BattleRole");

}