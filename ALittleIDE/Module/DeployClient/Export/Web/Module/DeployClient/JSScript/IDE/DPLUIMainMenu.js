{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (ALittle.Linear === undefined) throw new Error(" extends class:ALittle.Linear is undefined");
DeployClient.DPLUIMainMenu = JavaScript.Class(ALittle.Linear, {
	TCtor : function() {
		let group = new Map();
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.group = group;
		}
		let version_ip = DeployClient.g_DPLServerConfig.GetConfig("version_ip", "139.159.176.119");
		let version_port = DeployClient.g_DPLServerConfig.GetConfig("version_port", 1100);
		this._version_manager = ALittle.NewObject(AUIPlugin.AUIVersionManager, version_ip, version_port, "alittle", "ALittleDeploy");
	},
	Shutdown : function() {
	},
	HandleMenuHide : function(button) {
		button.selected = false;
	},
	HandleHelpMenuClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.Show(event.target, this.HandleMenuHide.bind(this, event.target));
	},
}, "DeployClient.DPLUIMainMenu");

}