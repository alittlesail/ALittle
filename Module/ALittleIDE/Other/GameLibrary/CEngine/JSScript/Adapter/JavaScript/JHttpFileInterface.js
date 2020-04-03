{
if (typeof JavaScript === "undefined") JavaScript = {};


let __JHTTPFILE_MAXID = 0;
if (ALittle.IHttpFileSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpFileSenderNative is undefined");
JavaScript.JHttpFileInterface = JavaScript.Class(ALittle.IHttpFileSenderNative, {
	Ctor : function() {
		this._cur_size = 0;
		this._total_size = 0;
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
		this._request = new XMLHttpRequest();
		if (this._download) {
			this._request.open("GET", this._url, true);
		} else {
			this._request.open("POST", this._url, true);
		}
		let error_func = this.HandleAjaxError.bind(this);
		this._request.onerror = error_func;
		this._request.ontimeout = error_func;
		this._request.onload = this.HandleStartCompleted.bind(this);
		this._request.onprogress = this.HandleOnProgress.bind(this);
		if (this._download) {
			this._request.send(undefined);
		} else {
			this._request.send(this._file_path);
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
	GetCurrentSize : function() {
		return this._cur_size;
	},
	GetTotalSize : function() {
		return this._total_size;
	},
	GetContent : function() {
		return this._request.responseText;
	},
	HandleAjaxError : function() {
		let func = window["__ALITTLEAPI_HttpFileFailed"];
		if (func === undefined) {
			return;
		}
		func(this, this._request.statusText);
	},
	HandleStartCompleted : function() {
		let func = window["__ALITTLEAPI_HttpFileSucceed"];
		if (func === undefined) {
			return;
		}
		func(this);
	},
	HandleOnProgress : function(event) {
		this._cur_size = event.loaded;
		this._total_size = event.total;
		let func = window["__ALITTLEAPI_HttpFileProcess"];
		if (func === undefined) {
			return;
		}
		func(this);
	},
}, "JavaScript.JHttpFileInterface");

}