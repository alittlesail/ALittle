{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPWXFILE_MAXID = 0;
if (ALittle.IHttpFileSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpFileSenderNative is undefined");
JavaScript.JHttpFileWxInterface = JavaScript.Class(ALittle.IHttpFileSenderNative, {
	Ctor : function() {
		++ __JHTTPWXFILE_MAXID;
		this._id = __JHTTPWXFILE_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, file_path, download, start_size, array_buffer) {
		this._url = url;
		this._file_path = file_path;
		this._download = download;
		this._array_buffer = array_buffer;
	},
	Start : function() {
		let content = undefined;
		let buffer = undefined;
		if (!this._download) {
			[content, buffer] = JavaScript.File_LoadFile(this._file_path);
			if (content === undefined && buffer === undefined) {
				ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file is not exist:" + this._file_path);
				return;
			}
		}
		let info = {};
		info.url = this._url;
		if (this._download) {
			info.method = "GET";
		} else {
			info.method = "POST";
		}
		if (content !== undefined) {
			info.dataType = "text";
			info.data = content;
		} else if (buffer !== undefined) {
			info.dataType = "arraybuffer";
			info.data = buffer;
		}
		if (this._array_buffer === true) {
			info.responseType = "arraybuffer";
		}
		info.success = this.HandleCompleted.bind(this);
		info.fail = this.HandleError.bind(this);
		this._request = window.wx.request(info);
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
		return this._response.data;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "wx.request failed");
	},
	HandleCompleted : function(info) {
		let content = undefined;
		let buffer = undefined;
		if (this._array_buffer) {
			buffer = info.data;
		} else {
			content = info.data;
		}
		if (this._download && !JavaScript.File_SaveFile(this._file_path, content, buffer)) {
			ALittle.__ALITTLEAPI_HttpFileFailed(this._id, "file save failed:" + this._file_path);
			return;
		}
		this._response = info;
		ALittle.__ALITTLEAPI_HttpFileSucceed(this._id);
	},
	HandleOnProgress : function(event) {
		ALittle.__ALITTLEAPI_HttpFileProcess(this._id, event.loaded, event.total);
	},
}, "JavaScript.JHttpFileWxInterface");

}