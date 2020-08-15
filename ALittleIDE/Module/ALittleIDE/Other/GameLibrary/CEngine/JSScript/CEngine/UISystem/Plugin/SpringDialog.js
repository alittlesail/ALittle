{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringDialog = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._is_show = false;
		this.visible = false;
	},
	get show() {
		return this._is_show;
	},
	set show(value) {
		if (this._is_show === value) {
			return;
		}
		this._is_show = value;
		if (this._anti_loop !== undefined) {
			this._anti_loop.SetCompleted();
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		if (value) {
			this.ShowAnti(1.1, 200, 200);
		} else {
			this.HideAnti(1.1, 200);
		}
	},
	ShowAnti : function(scale, scale_big_ms, scale_return_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this.visible = true;
		this.alpha = 0;
		this._show_dialog.scale_x = 1;
		this._show_dialog.scale_y = 1;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 1, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", 1, scale_return_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", 1, scale_return_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.Start();
	},
	HideAnti : function(scale, scale_big_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 0, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this, "visible", false, 1));
		this._anti_loop.Start();
	},
}, "ALittle.SpringDialog");

}