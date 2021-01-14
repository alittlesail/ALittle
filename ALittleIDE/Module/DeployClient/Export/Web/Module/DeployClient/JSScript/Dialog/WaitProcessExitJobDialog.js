{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (DeployClient.CommonJobDialog === undefined) throw new Error(" extends class:DeployClient.CommonJobDialog is undefined");
DeployClient.WaitProcessExitJobDialog = JavaScript.Class(DeployClient.CommonJobDialog, {
	get type() {
		return 5;
	},
	ShowDetail : function(detail) {
		if (detail !== undefined) {
			this._exe_path.text = ALittle.String_Join(detail.wait_p_exit_exe_path, "\n");
			this._max_time.text = detail.wait_p_exit_max_time;
		} else {
			this._exe_path.text = "";
			this._max_time.text = "";
		}
	},
	GetDetail : function() {
		let detail = {};
		detail.wait_p_exit_exe_path = ALittle.String_SplitSepList(this._exe_path.text, ["\r", "\n"]);
		detail.wait_p_exit_max_time = ALittle.Math_ToIntOrZero(this._max_time.text);
		return detail;
	},
}, "DeployClient.WaitProcessExitJobDialog");

}