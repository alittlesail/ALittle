{
if (typeof DeployClient === "undefined") window.DeployClient = {};


if (DeployClient.CommonJobDialog === undefined) throw new Error(" extends class:DeployClient.CommonJobDialog is undefined");
DeployClient.CopyFileJobDialog = JavaScript.Class(DeployClient.CommonJobDialog, {
	get type() {
		return 3;
	},
	ShowDetail : function(detail) {
		if (detail !== undefined) {
			this._src_dir.text = detail.copyfile_src;
			this._dst_dir.text = detail.copyfile_dst;
			this._file_list.text = ALittle.String_Join(detail.copyfile_file, "\n");
		} else {
			this._src_dir.text = "";
			this._dst_dir.text = "";
			this._file_list.text = "";
		}
	},
	GetDetail : function() {
		let detail = {};
		detail.copyfile_src = this._src_dir.text;
		detail.copyfile_dst = this._dst_dir.text;
		detail.copyfile_file = ALittle.String_SplitSepList(this._file_list.text, ["\r", "\n"]);
		return detail;
	},
}, "DeployClient.CopyFileJobDialog");

}