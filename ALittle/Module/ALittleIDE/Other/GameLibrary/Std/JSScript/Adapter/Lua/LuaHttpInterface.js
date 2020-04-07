{
if (typeof JavaScript === "undefined") JavaScript = {};


let __LUAHTTP_MAXID = 0;
if (ALittle.IHttpSenderNative === undefined) throw new Error(" extends class:ALittle.IHttpSenderNative is undefined");
JavaScript.LuaHttpInterface = JavaScript.Class(ALittle.IHttpSenderNative, {
	Ctor : function() {
		++ __LUAHTTP_MAXID;
		this._id = __LUAHTTP_MAXID;
	},
	GetID : function() {
		return this._id;
	},
	SetURL : function(url, content) {
		this._url = url;
		this._content = content;
	},
	Start : function(failed_callback, succeed_callback) {
		this._failed_callback = failed_callback;
		this._succeed_callback = succeed_callback;
		this._net = lua.net.create();
		if (this._content === undefined) {
			lua.net.get(this._net, this._id, this._url);
		} else {
			lua.net.post(this._net, this._id, this._url, "application/json", this._content);
		}
	},
	Stop : function() {
		if (this._net !== undefined) {
			lua.net.stop(this._net, this._id);
		}
	},
	GetResponse : function() {
		return this._response;
	},
	HandleError : function(reason) {
		if (this._failed_callback !== undefined) {
			this._failed_callback(this, reason);
		}
	},
	HandleStartCompleted : function() {
		if (this._succeed_callback !== undefined) {
			this._succeed_callback(this);
		}
	},
}, "JavaScript.LuaHttpInterface");

}