{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTP_MAXID = 0;
if (ALittle.IHttpSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpSenderNative is undefined");
JavaScript.JHttpInterface = JavaScript.Class(ALittle.IHttpSenderNative, {
	Ctor : function() {
		++ __JHTTP_MAXID;
		this._id = __JHTTP_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, content) {
		this._url = url;
		this._content = content;
	},
	Start : function() {
		this._request = new XMLHttpRequest();
		if (this._content === undefined) {
			this._request.open("GET", this._url, true);
		} else {
			this._request.open("POST", this._url, true);
		}
		let error_func = this.HandleError.bind(this);
		this._request.onerror = error_func;
		this._request.ontimeout = error_func;
		this._request.onload = this.HandleCompleted.bind(this);
		this._request.send(this._content);
	},
	Stop : function() {
		if (this._request !== undefined) {
			this._request.abort();
		}
	},
	GetResponse : function() {
		return this._request.responseText;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpClientFailed(this._id, this._request.statusText);
	},
	HandleCompleted : function() {
		ALittle.__ALITTLEAPI_HttpClientSucceed(this._id);
	},
}, "JavaScript.JHttpInterface");

}