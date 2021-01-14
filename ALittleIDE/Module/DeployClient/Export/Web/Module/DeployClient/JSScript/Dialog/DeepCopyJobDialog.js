{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (DeployClient.CommonJobDialog === undefined) throw new Error(" extends class:DeployClient.CommonJobDialog is undefined");
DeployClient.DeepCopyJobDialog = JavaScript.Class(DeployClient.CommonJobDialog, {
	get type() {
		return 2;
	},
	ShowDetail : function(detail) {
		if (detail !== undefined) {
			this._src_dir.text = detail.deepcopy_src;
			this._dst_dir.text = detail.deepcopy_dst;
			this._ext.text = detail.deepcopy_ext;
		} else {
			this._src_dir.text = "";
			this._dst_dir.text = "";
			this._ext.text = "";
		}
	},
	GetDetail : function() {
		let detail = {};
		detail.deepcopy_src = this._src_dir.text;
		detail.deepcopy_dst = this._dst_dir.text;
		detail.deepcopy_ext = this._ext.text;
		return detail;
	},
}, "DeployClient.DeepCopyJobDialog");

}