{
if (typeof FlappyBird === "undefined") window.FlappyBird = {};


FlappyBird.g_GConfig = undefined;
FlappyBird.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		FlappyBird.g_GConfig = ALittle.CreateConfigSystem(FlappyBird.g_ModuleBasePath + "/User.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(5, 2);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, FlappyBird.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		FlappyBird.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, FlappyBird.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		FlappyBird.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		this._main_scene = FlappyBird.g_Control.CreateControl("main_scene", this, this._main_layer);
		this._main_scene.visible = false;
		this._main_menu = FlappyBird.g_Control.CreateControl("main_menu", this, undefined);
		this._dialog_layer.AddChild(this._main_menu, undefined);
		this._main_menu.visible = true;
		this._game_over.visible = false;
		this._game_title.visible = true;
		this._max_score_text._user_data = FlappyBird.g_GConfig.GetConfig("max_score", 0);
		this._max_score_text.text = this._max_score_text._user_data;
		this._frame_anti = ALittle.NewObject(ALittle.LoopFrame, this.LoopGroundFrame.bind(this));
	},
	Restart : function() {
		this._ground_frame_acc = 0;
		this._next_pipe_gap = 0;
		this._next_pipe_up = 50;
		this._flying = false;
		this._dieing = false;
		this._bird.y = this._bg.height / 2;
		this._bird.x = 0;
		this._bird.angle = 0;
		this._bird.visible = true;
		this._bird.Play();
		this._game_over.visible = false;
		this._score_text.text = "0";
		this._score_text._user_data = 0;
		this._pipe_container.RemoveAllChild();
		this._frame_anti.Start();
	},
	LoopGroundFrame : function(frame_time) {
		let scale = 20;
		if (!this._dieing) {
			let cur_score = this._score_text._user_data + frame_time;
			this._score_text._user_data = cur_score;
			this._score_text.text = ALittle.Math_Floor(cur_score / 100);
		}
		let total_time = (this._ground.width - this._main_scene.width) * scale;
		this._ground_frame_acc = this._ground_frame_acc + (frame_time);
		if (this._ground_frame_acc > total_time) {
			this._ground_frame_acc = (this._ground_frame_acc % total_time);
		}
		this._ground.x = -this._ground_frame_acc / scale;
		if (this._bird.x + this._bird.width / 2 < this._bg.width / 2) {
			this._bird.x = this._bird.x + (frame_time / scale);
		} else {
			let create_pipe = false;
			if (this._pipe_container.child_count === 0) {
				create_pipe = true;
			} else {
				let pipe = this._pipe_container.childs[this._pipe_container.child_count - 1];
				let right = pipe.x + pipe.width;
				if (this._bg.width - right > this._next_pipe_gap) {
					create_pipe = true;
				}
				pipe = this._pipe_container.childs[1 - 1];
				if (pipe.x + pipe.width < 0) {
					this._pipe_container.RemoveChild(pipe);
				}
			}
			if (create_pipe) {
				let pipe = FlappyBird.g_Control.CreateControl("pipe");
				this._pipe_container.AddChild(pipe);
				let total_height = this._bg.height - this._ground.height;
				let half_height = total_height / 2;
				if (ALittle.Math_RandomInt(1, 100) <= this._next_pipe_up) {
					let min_y = ALittle.Math_Floor(-pipe.height + pipe.height / 4);
					let max_y = ALittle.Math_Floor(half_height - pipe.height);
					pipe.y = ALittle.Math_RandomInt(min_y, max_y);
					this._next_pipe_up = 30;
				} else {
					let min_y = ALittle.Math_Floor(half_height);
					let max_y = ALittle.Math_Floor(total_height - pipe.height / 4);
					pipe.y = ALittle.Math_RandomInt(min_y, max_y);
					this._next_pipe_up = 70;
				}
				pipe.x = this._bg.width;
				this._next_pipe_gap = ALittle.Math_RandomInt(50, 100);
			}
			let ___OBJECT_1 = this._pipe_container.childs;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let child = ___OBJECT_1[index - 1];
				if (child === undefined) break;
				child.x = child.x - (frame_time / scale);
			}
		}
		if (this._dieing) {
			this._bird.y = this._bird.y + (frame_time / scale) * 2;
			if (this._bird.y <= 0 || this._bird.y + this._bird.height >= this._bg.height - this._ground.height) {
				this.ShowGameOver();
			}
		} else {
			if (this._flying) {
				this._bird.y = this._bird.y - (frame_time / scale) * 2;
			} else {
				this._bird.y = this._bird.y + (frame_time / scale) * 1.5;
			}
			let ___OBJECT_2 = this._pipe_container.childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let child = ___OBJECT_2[index - 1];
				if (child === undefined) break;
				let left = this._bird.x + 5;
				let right = this._bird.x + this._bird.width - 5;
				let top = this._bird.y + 5;
				let bottom = this._bird.y + this._bird.height - 5;
				if ((left > child.x && left <= child.x + child.width || right > child.x && right <= child.x + child.width) && (top > child.y && top <= child.y + child.height || bottom > child.y && bottom <= child.y + child.height)) {
					this._dieing = true;
					break;
				}
			}
			if (this._bird.y <= 0 || this._bird.y + this._bird.height >= this._bg.height - this._ground.height) {
				this._dieing = true;
			}
			if (this._dieing) {
				this._bird.angle = -60;
				this._bird.Stop();
			}
		}
	},
	HandleStartClick : function(event) {
		this._main_menu.visible = false;
		this._main_scene.visible = true;
		this.Restart();
	},
	HandleLButtonDown : function(event) {
		this._tip_1.visible = false;
		this._tip_2.visible = false;
		this._flying = true;
	},
	HandleLButtonUp : function(event) {
		this._flying = false;
	},
	ShowGameOver : function() {
		this._main_menu.visible = true;
		this._main_scene.visible = false;
		this._game_over.visible = true;
		this._game_title.visible = false;
		this._bird.Stop();
		this._frame_anti.Stop();
		let cur_socre = ALittle.Math_Floor(this._score_text._user_data / 100);
		if (this._max_score_text._user_data < cur_socre) {
			this._max_score_text._user_data = cur_socre;
			this._max_score_text.text = this._max_score_text._user_data;
			FlappyBird.g_GConfig.SetConfig("max_score", cur_socre, undefined);
		}
		return true;
	},
	Shutdown : function() {
		this._bird.Stop();
		this._frame_anti.Stop();
	},
}, "FlappyBird.GCenter");

FlappyBird.g_GCenter = ALittle.NewObject(FlappyBird.GCenter);
}