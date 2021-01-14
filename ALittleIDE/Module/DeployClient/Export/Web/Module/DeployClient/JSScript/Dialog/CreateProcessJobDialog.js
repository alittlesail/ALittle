{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (DeployClient.CommonJobDialog === undefined) throw new Error(" extends class:DeployClient.CommonJobDialog is undefined");
DeployClient.CreateProcessJobDialog = JavaScript.Class(DeployClient.CommonJobDialog, {
	get type() {
		return 6;
	},
	ShowDetail : function(detail) {
		if (detail !== undefined) {
			this._dir.text = detail.createprocess_dir;
			this._cmd.text = detail.createprocess_cmd;
			this._param.text = detail.createprocess_param;
		} else {
			this._dir.text = "";
			this._cmd.text = "";
			this._param.text = "";
		}
	},
	GetDetail : function() {
		let detail = {};
		detail.createprocess_dir = this._dir.text;
		detail.createprocess_cmd = this._cmd.text;
		detail.createprocess_param = this._param.text;
		return detail;
	},
}, "DeployClient.CreateProcessJobDialog");

}