{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDECenter = JavaScript.Class(undefined, {
	Setup : function() {
		return new Promise((function(___COROUTINE, ___) {
			ALittleIDE.g_Control.CreateControl("ide_main_scene", this, ALittleIDE.g_MainLayer);
			ALittleIDE.g_IDEProject.OpenLastProject();
			A_UISystem.keydown_callback = this.HandleShortcutKey.bind(this);
			A_UISystem.quit_callback = this.HandleQuit.bind(this);
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
	RefreshProject : async function() {
		if (!this._center.content_edit.IsSaveAll()) {
			let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
			if (result === "YES") {
				this._center.content_edit.SaveAllTab();
			}
		}
		ALittleIDE.g_IDEProject.RefreshProject();
	},
	HandleShortcutKey : function(mod, sym, scancode) {
		if (A_UISystem.sym_map.get(1073741886)) {
			if (ALittleIDE.g_IDEProject.IsDebug()) {
				ALittleIDE.g_IDEProject.ContinueDebug();
			} else {
				ALittleIDE.g_IDEProject.RunProject(true);
				ALittleIDE.g_IDEProject.StartDebugProject();
			}
			return;
		}
		if (A_UISystem.sym_map.get(1073741887)) {
			ALittleIDE.g_IDEProject.StopDebugProject();
			ALittleIDE.g_IDEProject.RunProject(false);
			return;
		}
		if (A_UISystem.sym_map.get(1073741891)) {
			if (ALittleIDE.g_IDEProject.IsDebug()) {
				ALittleIDE.g_IDEProject.NextLineDebug();
			}
			return;
		}
		if (this._center !== undefined) {
			this._center.HandleShortcutKey();
		}
	},
	HandleQuit : function() {
		if (this._center.content_edit.IsSaveAll()) {
			return true;
		}
		this.HandleQuitImpl();
		return false;
	},
	HandleQuitImpl : async function() {
		let result = await g_AUITool.SaveNotice("提示", "是否保存当前项目?");
		if (result === "YES") {
			this._center.content_edit.SaveAllTab();
		}
		ALittle.System_Exit();
	},
}, "ALittleIDE.IDECenter");

ALittleIDE.g_IDECenter = ALittle.NewObject(ALittleIDE.IDECenter);
}