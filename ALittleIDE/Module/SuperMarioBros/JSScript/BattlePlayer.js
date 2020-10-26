{
if (typeof SuperMarioBros === "undefined") window.SuperMarioBros = {};


SuperMarioBros.PlayerState = {
	PS_IDLE : 0,
	PS_WALK : 1,
	PS_JUMP : 2,
	PS_FALL : 3,
	PS_SQUAT : 4,
	PS_DEATH : 5,
	PS_FLAG : 6,
}

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
SuperMarioBros.BattlePlayer = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._level = 1;
		this._right = true;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this._win = false;
		this._walk_frame_change = 0.0;
		this._walk_frame = 1;
	},
	TCtor : function() {
		this._level_1_sprite_right.visible = false;
		this._level_1_sprite_left.visible = false;
		this._level_2_sprite_right.visible = false;
		this._level_2_sprite_left.visible = false;
		this._level_3_sprite_right.visible = false;
		this._level_3_sprite_left.visible = false;
	},
	Init : function(row, col, level) {
		this._level_1_sprite_right.visible = false;
		this._level_1_sprite_left.visible = false;
		this._level_2_sprite_right.visible = false;
		this._level_2_sprite_left.visible = false;
		this._level_3_sprite_right.visible = false;
		this._level_3_sprite_left.visible = false;
		this.visible = true;
		this._state = SuperMarioBros.PlayerState.PS_IDLE;
		this._win = false;
		this._right = true;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this._level = level;
		if (this._level === 1) {
			this._level_1_sprite_right.visible = true;
			this.height = this._level_1_sprite_right.height;
			this._level_1_sprite_right.col_index = 1;
			this._level_1_sprite_right.row_index = 1;
			this.x = col * SuperMarioBros.TILE_WIDTH;
			this.y = row * SuperMarioBros.TILE_HEIGHT - this._level_1_sprite_right.height;
		} else if (this._level === 2) {
			this._level_2_sprite_right.visible = true;
			this.height = this._level_2_sprite_right.height;
			this._level_2_sprite_right.col_index = 2;
			this.x = col * SuperMarioBros.TILE_WIDTH;
			this.y = row * SuperMarioBros.TILE_HEIGHT - this._level_2_sprite_right.height;
		} else if (this._level === 3) {
			this._level_3_sprite_right.visible = true;
			this.height = this._level_3_sprite_right.height;
			this._level_3_sprite_right.col_index = 2;
			this.x = col * SuperMarioBros.TILE_WIDTH;
			this.y = row * SuperMarioBros.TILE_HEIGHT - this._level_3_sprite_right.height;
		}
	},
	Fire : function() {
	},
	SmallJump : function() {
		this._state = SuperMarioBros.PlayerState.PS_JUMP;
		this._vy = -3;
	},
	Flag : function() {
		if (this._state === SuperMarioBros.PlayerState.PS_DEATH) {
			return;
		}
		if (this._state === SuperMarioBros.PlayerState.PS_FLAG) {
			return;
		}
		this._state = SuperMarioBros.PlayerState.PS_FLAG;
		this._vx = 0;
		this._vy = 3;
		this._ax = 0;
		this._ay = 0;
		this.UpdateFlag();
	},
	get win() {
		return this._win;
	},
	set win(value) {
		this._win = value;
	},
	Death : function() {
		if (this._state === SuperMarioBros.PlayerState.PS_DEATH) {
			return;
		}
		this._state = SuperMarioBros.PlayerState.PS_DEATH;
		this._level_1_sprite_right.visible = false;
		this._level_1_sprite_left.visible = false;
		this._level_2_sprite_right.visible = false;
		this._level_2_sprite_left.visible = false;
		this._level_3_sprite_right.visible = false;
		this._level_3_sprite_left.visible = false;
		this._level_1_sprite_right.visible = true;
		this.height = this._level_1_sprite_right.height;
		this._level_1_sprite_right.col_index = 2;
		this._level_1_sprite_right.row_index = 1;
		let loop = ALittle.NewObject(ALittle.LoopList);
		loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "y", this.y - SuperMarioBros.TILE_HEIGHT * 5, 500, 0));
		loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "y", A_UISystem.view_height, 200, 500));
		loop.AddUpdater(ALittle.NewObject(ALittle.LoopTimer, g_GCenter.battle_scene.Restart.bind(g_GCenter.battle_scene), 100));
		loop.Start();
	},
	get state() {
		return this._state;
	},
	get right() {
		return this._right;
	},
	Idle : function() {
		this._state = SuperMarioBros.PlayerState.PS_IDLE;
		this._vx = 0;
		this._vy = 0;
		this._ax = 0;
		this._ay = 0;
		this.UpdateIdle();
	},
	UpdateFrame : function(frame_time) {
		if (this._state === SuperMarioBros.PlayerState.PS_DEATH) {
			return;
		}
		this._vx = this._vx + (this._ax * frame_time);
		let walk_speedup = A_UISystem.sym_map.get(106) !== undefined && this._state === SuperMarioBros.PlayerState.PS_WALK;
		if (walk_speedup) {
			if (this._vx > SuperMarioBros.PLAYER_MAX_WALK_SPEED_2) {
				this._vx = SuperMarioBros.PLAYER_MAX_WALK_SPEED_2;
			} else if (this._vx < -SuperMarioBros.PLAYER_MAX_WALK_SPEED_2) {
				this._vx = -SuperMarioBros.PLAYER_MAX_WALK_SPEED_2;
			}
		} else {
			if (this._vx > SuperMarioBros.PLAYER_MAX_WALK_SPEED_1) {
				this._vx = SuperMarioBros.PLAYER_MAX_WALK_SPEED_1;
			} else if (this._vx < -SuperMarioBros.PLAYER_MAX_WALK_SPEED_1) {
				this._vx = -SuperMarioBros.PLAYER_MAX_WALK_SPEED_1;
			}
		}
		this._vy = this._vy + (this._ay * frame_time);
		let walk_left = A_UISystem.sym_map.get(97) !== undefined;
		let walk_right = A_UISystem.sym_map.get(100) !== undefined;
		let squat_down = A_UISystem.sym_map.get(115) !== undefined;
		let jump = A_UISystem.sym_map.get(107) !== undefined;
		if (this._win) {
			walk_left = false;
			walk_right = true;
			squat_down = false;
			jump = false;
		}
		if (this._state === SuperMarioBros.PlayerState.PS_IDLE) {
			this.x = this.x + (this._vx);
			this.y = this.y + (this._vy);
			if (walk_left) {
				this._state = SuperMarioBros.PlayerState.PS_WALK;
				this._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
				this._right = false;
				this.UpdateIdle();
			} else if (walk_right) {
				this._state = SuperMarioBros.PlayerState.PS_WALK;
				this._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
				this._right = true;
				this.UpdateIdle();
			}
			if (jump) {
				this._state = SuperMarioBros.PlayerState.PS_JUMP;
				this._vy = -SuperMarioBros.PLAYER_INIT_JUMP_SPEED;
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE;
				this.UpdateJump();
			} else if (squat_down) {
				this._state = SuperMarioBros.PlayerState.PS_SQUAT;
			}
		} else if (this._state === SuperMarioBros.PlayerState.PS_WALK) {
			if (walk_left) {
				this._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
				if (this._right) {
					this._right = false;
					this.UpdateLeftRight();
				}
			} else if (walk_right) {
				this._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
				if (!this._right) {
					this._right = true;
					this.UpdateLeftRight();
				}
			} else {
				if (this._vx !== 0) {
					this._ax = 0;
					this._vx = this._vx * (0.1);
					if (this._vx < 0.001) {
						this._vx = 0;
					}
				} else {
					this._state = SuperMarioBros.PlayerState.PS_IDLE;
					this.UpdateIdle();
				}
			}
			if (jump) {
				this._state = SuperMarioBros.PlayerState.PS_JUMP;
				this._vy = -SuperMarioBros.PLAYER_INIT_JUMP_SPEED;
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE;
				this.UpdateJump();
			} else if (squat_down) {
				this._state = SuperMarioBros.PlayerState.PS_SQUAT;
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
			this.y = this.y + (this._vy);
		} else if (this._state === SuperMarioBros.PlayerState.PS_JUMP) {
			if (walk_left) {
				this._ax = -SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
			} else if (walk_right) {
				this._ax = SuperMarioBros.PLAYER_INIT_X_SPEED_RATE;
			} else {
				if (this._vx !== 0) {
					this._ax = 0;
					if (this._vx < 0.001) {
						this._vx = 0;
					}
				}
			}
			if (jump && this._vy < 0) {
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE / 3;
			} else {
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE;
			}
			this.y = this.y + (this._vy);
			if (this._vy < 0) {
				let [check_up, up_y] = g_GCenter.battle_scene.CheckUp(this);
				if (check_up) {
					this._vy = -this._vy;
					this.y = up_y;
				}
			}
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (check_down) {
				this._state = SuperMarioBros.PlayerState.PS_WALK;
				this._vy = 0;
				this._ay = 0;
				this.y = down_y - this.height;
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
		} else if (this._state === SuperMarioBros.PlayerState.PS_FALL) {
			this.y = this.y + (this._vy);
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (check_down) {
				this._state = SuperMarioBros.PlayerState.PS_WALK;
				this._vy = 0;
				this._ay = 0;
				this.y = down_y - this.height;
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
		} else if (this._state === SuperMarioBros.PlayerState.PS_SQUAT) {
			if (walk_left) {
				this._ax = 0;
				if (this._right) {
					this._right = false;
					this.UpdateLeftRight();
				}
			} else if (walk_right) {
				this._ax = 0;
				if (!this._right) {
					this._right = true;
					this.UpdateLeftRight();
				}
			} else {
				if (this._vx !== 0) {
					this._ax = 0;
					this._vx = this._vx * (0.1);
					if (this._vx < 0.001) {
						this._vx = 0;
					}
				}
			}
			if (!squat_down) {
				this._state = SuperMarioBros.PlayerState.PS_WALK;
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
			this.y = this.y + (this._vy);
		} else {
			this.x = this.x + (this._vx);
			this.y = this.y + (this._vy);
		}
		if (this._state === SuperMarioBros.PlayerState.PS_WALK || this._state === SuperMarioBros.PlayerState.PS_IDLE) {
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (!check_down) {
				this._state = SuperMarioBros.PlayerState.PS_FALL;
				this._vy = 0;
				this._vx = this._vx / (2);
				this._ay = SuperMarioBros.PLAYER_INIT_Y_SPEED_RATE;
			}
		}
		if (this._state === SuperMarioBros.PlayerState.PS_FLAG) {
			let [check_down, down_y] = g_GCenter.battle_scene.CheckDown(this);
			if (check_down) {
				this._win = true;
				this._state = SuperMarioBros.PlayerState.PS_WALK;
				this._vy = 0;
				this._ay = 0;
				this.y = down_y - this.height;
			}
		}
		if (this._state === SuperMarioBros.PlayerState.PS_WALK) {
			this.WalkUpdateFrame(frame_time);
		} else if (this._state === SuperMarioBros.PlayerState.PS_SQUAT) {
			this.UpdateSquat();
		} else if (this._state === SuperMarioBros.PlayerState.PS_FLAG) {
			this.UpdateFlag();
		}
	},
	UpdateFlag : function() {
		this.UpdateLeftRight();
		if (this._level === 1) {
			this._level_1_sprite_right.col_index = 1;
			this._level_1_sprite_right.row_index = 2;
			this._level_1_sprite_left.col_index = 7;
			this._level_1_sprite_left.row_index = 2;
		} else if (this._level === 2) {
			this._level_2_sprite_right.col_index = 1;
			this._level_2_sprite_right.row_index = 2;
			this._level_2_sprite_left.col_index = 7;
			this._level_2_sprite_left.row_index = 2;
		} else if (this._level === 3) {
			this._level_3_sprite_right.col_index = 1;
			this._level_3_sprite_right.row_index = 2;
			this._level_3_sprite_left.col_index = 7;
			this._level_3_sprite_left.row_index = 2;
		}
	},
	UpdateJump : function() {
		this.UpdateLeftRight();
		if (this._level === 1) {
			this._level_1_sprite_right.col_index = 7;
			this._level_1_sprite_right.row_index = 1;
			this._level_1_sprite_left.col_index = 1;
			this._level_1_sprite_left.row_index = 1;
		} else if (this._level === 2) {
			this._level_2_sprite_right.col_index = 7;
			this._level_2_sprite_right.row_index = 1;
			this._level_2_sprite_left.col_index = 1;
			this._level_2_sprite_left.row_index = 1;
		} else if (this._level === 3) {
			this._level_3_sprite_right.col_index = 7;
			this._level_3_sprite_right.row_index = 1;
			this._level_3_sprite_left.col_index = 1;
			this._level_3_sprite_left.row_index = 1;
		}
	},
	UpdateSquat : function() {
		this.UpdateLeftRight();
		if (this._level === 2) {
			this._level_2_sprite_right.col_index = 1;
			this._level_2_sprite_right.row_index = 1;
			this._level_2_sprite_left.col_index = 7;
			this._level_2_sprite_left.row_index = 1;
		} else if (this._level === 3) {
			this._level_3_sprite_right.col_index = 1;
			this._level_3_sprite_right.row_index = 1;
			this._level_3_sprite_left.col_index = 7;
			this._level_3_sprite_left.row_index = 1;
		}
	},
	UpdateIdle : function() {
		this.UpdateLeftRight();
		if (this._level === 1) {
			this._level_1_sprite_right.col_index = 1;
			this._level_1_sprite_right.row_index = 1;
			this._level_1_sprite_left.col_index = 7;
			this._level_1_sprite_left.row_index = 1;
		} else if (this._level === 2) {
			this._level_2_sprite_right.col_index = 2;
			this._level_2_sprite_right.row_index = 1;
			this._level_2_sprite_left.col_index = 6;
			this._level_2_sprite_left.row_index = 1;
		} else if (this._level === 3) {
			this._level_3_sprite_right.col_index = 2;
			this._level_3_sprite_right.row_index = 1;
			this._level_3_sprite_left.col_index = 6;
			this._level_3_sprite_left.row_index = 1;
		}
	},
	UpdateLeftRight : function() {
		if (this._level === 1) {
			this._level_1_sprite_right.visible = this._right;
			this._level_1_sprite_left.visible = !this._right;
		} else if (this._level === 2) {
			this._level_2_sprite_right.visible = this._right;
			this._level_2_sprite_left.visible = !this._right;
		} else if (this._level === 3) {
			this._level_3_sprite_right.visible = this._right;
			this._level_3_sprite_left.visible = !this._right;
		}
	},
	WalkUpdateFrame : function(frame_time) {
		let rate = 0.006;
		if (this._level !== 1) {
			rate = 0.004;
		}
		this._walk_frame_change = this._walk_frame_change + (rate * frame_time * (1 + ALittle.Math_Abs(this._vx)));
		if (this._walk_frame_change >= 1) {
			this._walk_frame_change = 0.0;
			this._walk_frame = this._walk_frame + (1);
			if (this._ax > 0 && this._vx < 0) {
				if (this._level === 1) {
					this._walk_frame = 1;
					this._level_1_sprite_right.row_index = 1;
					this._level_1_sprite_right.col_index = 3;
				} else if (this._level === 2) {
					this._walk_frame = 1;
					this._level_2_sprite_right.row_index = 1;
					this._level_2_sprite_right.col_index = 3;
				} else if (this._level === 3) {
					this._walk_frame = 1;
					this._level_3_sprite_right.row_index = 1;
					this._level_3_sprite_right.col_index = 3;
				}
			} else if (this._ax < 0 && this._vx > 0) {
				if (this._level === 1) {
					this._walk_frame = 1;
					this._level_1_sprite_left.row_index = 1;
					this._level_1_sprite_left.col_index = 5;
				} else if (this._level === 2) {
					this._walk_frame = 1;
					this._level_2_sprite_left.row_index = 1;
					this._level_2_sprite_left.col_index = 5;
				} else if (this._level === 3) {
					this._walk_frame = 1;
					this._level_3_sprite_left.row_index = 1;
					this._level_3_sprite_left.col_index = 5;
				}
			} else if (this._right) {
				if (this._level === 1) {
					this._level_1_sprite_right.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_1_sprite_right.col_index = 5;
					} else if (this._walk_frame === 3) {
						this._level_1_sprite_right.col_index = 6;
					} else {
						this._walk_frame = 1;
						this._level_1_sprite_right.col_index = 4;
					}
				} else if (this._level === 2) {
					this._level_2_sprite_right.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_2_sprite_right.col_index = 5;
					} else if (this._walk_frame === 3) {
						this._level_2_sprite_right.col_index = 6;
					} else {
						this._walk_frame = 1;
						this._level_2_sprite_right.col_index = 4;
					}
				} else if (this._level === 3) {
					this._level_3_sprite_right.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_3_sprite_right.col_index = 5;
					} else if (this._walk_frame === 3) {
						this._level_3_sprite_right.col_index = 6;
					} else {
						this._walk_frame = 1;
						this._level_3_sprite_right.col_index = 4;
					}
				}
			} else {
				if (this._level === 1) {
					this._level_1_sprite_left.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_1_sprite_left.col_index = 4;
					} else if (this._walk_frame === 3) {
						this._level_1_sprite_left.col_index = 3;
					} else {
						this._walk_frame = 1;
						this._level_1_sprite_left.col_index = 2;
					}
				} else if (this._level === 2) {
					this._level_2_sprite_left.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_2_sprite_left.col_index = 4;
					} else if (this._walk_frame === 3) {
						this._level_2_sprite_left.col_index = 3;
					} else {
						this._walk_frame = 1;
						this._level_2_sprite_left.col_index = 2;
					}
				} else if (this._level === 3) {
					this._level_3_sprite_left.row_index = 1;
					if (this._walk_frame === 2) {
						this._level_3_sprite_left.col_index = 4;
					} else if (this._walk_frame === 3) {
						this._level_3_sprite_left.col_index = 3;
					} else {
						this._walk_frame = 1;
						this._level_3_sprite_left.col_index = 2;
					}
				}
			}
		}
	},
}, "SuperMarioBros.BattlePlayer");

}