{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgReceiverTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(client_id, remote_ip, remote_port) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._interface.SetID(client_id);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._is_connected = true;
		this._client_id = client_id;
		this._remote_ip = remote_ip;
		this._remote_port = remote_port;
		this._client_account_id = 0;
		this._client_logining = false;
		this._web_account_id = "";
		this._web_is_logining = false;
	},
	get remote_ip() {
		return this._remote_ip;
	},
	get remote_port() {
		return this._remote_port;
	},
	IsConnected : function() {
		return this._is_connected;
	},
	HandleConnected : function() {
		this._is_connected = true;
	},
	HandleDisconnected : function() {
		this._is_connected = false;
		this.ClearRPC("连接断开了");
	},
	Close : function(reason) {
		if (!this._is_connected) {
			return;
		}
		this._is_connected = false;
		if (reason === undefined) {
			reason = "主动关闭连接";
		}
		this.ClearRPC(reason);
		this._interface.Close();
	},
}, "ALittle.MsgReceiverTemplate");

}