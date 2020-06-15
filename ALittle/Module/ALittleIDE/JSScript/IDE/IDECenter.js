{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDECenter = JavaScript.Class(undefined, {
	Ctor : function() {
	},
	Setup : function() {
		return new Promise((function(___COROUTINE, ___) {
			ALittleIDE.g_Control.CreateControl("ide_main_scene", this, ALittleIDE.g_MainLayer);
			ALittleIDE.g_IDEProject.OpenLastProject();
			A_UISystem.keydown_callback = this.HandleShortcutKey.bind(this);
			___COROUTINE();
		}).bind(this));
	},
	Shutdown : function() {
		if (this._account !== undefined) {
			this._account.Shutdown();
		}
		if (this._main_menu !== undefined) {
			this._main_menu.Shutdown();
		}
	},
	get center() {
		return this._center;
	},
	RefreshProject : function() {
		if (ALittleIDE.g_IDEProject.project === undefined) {
			return;
		}
		let project_name = ALittleIDE.g_IDEProject.project.name;
		ALittleIDE.g_IDEProject.CloseProject();
		ALittleIDE.g_IDEProject.OpenProject(project_name);
	},
	HandleShortcutKey : function(mod, sym, scancode) {
		if (A_UISystem.sym_map.get(1073741886)) {
			ALittleIDE.g_IDEProject.RunProject();
			return;
		}
		if (this._center !== undefined) {
			this._center.HandleShortcutKey();
		}
	},
}, "ALittleIDE.IDECenter");

ALittleIDE.g_IDECenter = ALittle.NewObject(ALittleIDE.IDECenter);
}