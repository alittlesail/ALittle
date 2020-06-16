{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __JHTTPWX_MAXID = 0;
if (ALittle.IHttpSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpSenderNative is undefined");
JavaScript.JHttpWxInterface = JavaScript.Class(ALittle.IHttpSenderNative, {
	Ctor : function() {
		++ __JHTTPWX_MAXID;
		this._id = __JHTTPWX_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, content) {
		this._url = url;
		this._content = content;
	},
	Start : function() {
		let info = {};
		info.url = this._url;
		if (this._content === undefined) {
			info.method = "GET";
		} else {
			info.method = "POST";
		}
		if (this._content !== undefined) {
			info.data = this._content;
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
	GetResponse : function() {
		return this._response.data;
	},
	HandleError : function() {
		ALittle.__ALITTLEAPI_HttpClientFailed(this._id, "wx.request failed");
	},
	HandleCompleted : function(info) {
		this._response = info;
		ALittle.__ALITTLEAPI_HttpClientSucceed(this._id);
	},
}, "JavaScript.JHttpWxInterface");

}