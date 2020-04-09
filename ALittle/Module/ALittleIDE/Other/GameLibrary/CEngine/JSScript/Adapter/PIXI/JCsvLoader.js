{
if (typeof JavaScript === "undefined") JavaScript = {};


let __CSVFILE_MAXID = 0;
if (ALittle.ICsvFileLoader === undefined) throw new Error(" extends class:ALittle.ICsvFileLoader is undefined");
JavaScript.JCsvFileLoader = JavaScript.Class(ALittle.ICsvFileLoader, {
	Ctor : function() {
		++ __CSVFILE_MAXID;
		this._id = __CSVFILE_MAXID;
	},
	Start : function() {
		this.StartImpl();
	},
	StartImpl : async function() {
		let host = location.host;
		let port = ALittle.Math_ToInt(location.port);
		let [error, content] = await ALittle.HttpDownloadRequest(host, port, this._file_path);
		if (error !== undefined) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let file = ALittle.NewObject(JavaScript.JCsvFile);
		if (!file.Load(this._file_path)) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let func = window["__ALITTLEAPI_CsvFileLoadSucceed"];
		if (func !== undefined) {
			func(this, file);
		}
	},
	SetPath : function(file_path, only_from_asset) {
		this._file_path = file_path;
	},
	GetPath : function() {
		return this._file_path;
	},
	GetID : function() {
		return this._id;
	},
}, "JavaScript.JCsvFileLoader");

}