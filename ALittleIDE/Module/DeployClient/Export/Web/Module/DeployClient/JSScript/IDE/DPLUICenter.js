{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
DeployClient.DPLUICenter = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		this._main_tab.tab_index = 1;
		this._main_tab.DisableAllCloseButton();
	},
	get task_center() {
		return this._task_center;
	},
	HandleShortcutKey : function() {
	},
}, "DeployClient.DPLUICenter");

}