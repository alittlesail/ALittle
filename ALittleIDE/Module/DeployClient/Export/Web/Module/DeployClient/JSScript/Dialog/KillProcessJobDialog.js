{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (DeployClient.CommonJobDialog === undefined) throw new Error(" extends class:DeployClient.CommonJobDialog is undefined");
DeployClient.KillProcessJobDialog = JavaScript.Class(DeployClient.CommonJobDialog, {
	get type() {
		return 7;
	},
	ShowDetail : function(detail) {
		if (detail !== undefined) {
			this._exe_path.text = ALittle.String_Join(detail.killprocess_exe_path, "\n");
		} else {
			this._exe_path.text = "";
		}
	},
	GetDetail : function() {
		let detail = {};
		detail.killprocess_exe_path = ALittle.String_SplitSepList(this._exe_path.text, ["\r", "\n"]);
		return detail;
	},
}, "DeployClient.KillProcessJobDialog");

}