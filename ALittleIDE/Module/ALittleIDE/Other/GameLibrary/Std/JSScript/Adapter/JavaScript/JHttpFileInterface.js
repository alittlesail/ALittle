{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPFILE_MAXID = 0;
if (ALittle.IHttpFileSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpFileSenderNative is undefined");
JavaScript.JHttpFileInterface = JavaScript.Class(ALittle.IHttpFileSenderNative, {
	Ctor : function() {
		++ __JHTTPFILE_MAXID;
		this._id = __JHTTPFILE_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, file_path, download, start_size) {
		this._url = url;
		this._file_path = file_path;
		this._download = download;
	},
	Start : function() {
		let content = undefined;
		if (!this._download) {
			content = JavaScript.File_LoadFile(this._file_path);
			if (content === undefined) {
				ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file is not exist:" + this._file_path);
				return;
			}
		}
		this._request = new XMLHttpRequest();
		if (this._download) {
			this._request.open("GET", this._url, true);
		} else {
			this._request.open("POST", this._url, true);
		}
		let error_func = this.HandleError.bind(this);
		this._request.onerror = error_func;
		this._request.ontimeout = error_func;
		this._request.onload = this.HandleCompleted.bind(this);
		this._request.onprogress = this.HandleOnProgress.bind(this);
		if (this._download) {
			this._request.send(undefined);
		} else {
			this._request.send(content);
		}
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetPath : function() {
		return this._file_path;
	},
	GetContent : function() {
		return this._request.responseText;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpFileFailed(this._id, this._request.statusText);
	},
	HandleCompleted : function() {
		if (this._download && !JavaScript.File_SaveFile(this._file_path, this._request.responseText)) {
			ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file save failed:" + this._file_path);
			return;
		}
		ALittle.__ALITTLEAPI_HttpFileSucceed(this._id);
	},
	HandleOnProgress : function(event) {
		ALittle.__ALITTLEAPI_HttpFileProcess(this._id, event.loaded, event.total);
	},
}, "JavaScript.JHttpFileInterface");

}