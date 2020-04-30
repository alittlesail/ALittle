{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEAttributeManager = JavaScript.Class(undefined, {
	Setup : function(tab, control) {
		this._main_tab = tab;
		this._main_control = control;
	},
	SetTitle : function(title) {
		let text = "控件属性";
		if (title !== "") {
			text = "控件属性(" + title + ")";
		}
		this._main_tab.SetChildText(this._main_control, text);
	},
}, "ALittleIDE.IDEAttributeManager");

ALittleIDE.g_IDEAttributeManager = ALittle.NewObject(ALittleIDE.IDEAttributeManager);
}