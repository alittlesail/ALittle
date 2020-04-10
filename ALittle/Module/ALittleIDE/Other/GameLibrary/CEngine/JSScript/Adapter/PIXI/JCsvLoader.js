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
		let base_url = ALittle.File_GetFilePathByPath(location.pathname) + "/";
		let path = base_url + this._file_path;
		ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
		let error = await ALittle.HttpDownloadRequest(host, port, path, path);
		if (error !== undefined) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let content = JavaScript.File_LoadFile(path);
		if (content === undefined) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let file = ALittle.NewObject(JavaScript.JCsvFile);
		if (!file.Load(content)) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		ALittle.File_DeleteFile(path);
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