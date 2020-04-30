{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IMsgCommonTemplate === undefined) throw new Error(" extends class:ALittle.IMsgCommonTemplate is undefined");
ALittle.MsgSessionTemplate = JavaScript.Class(ALittle.IMsgCommonTemplate, {
	Ctor : function(connect_key, route_type, route_num) {
		this._interface = ALittle.NewObject(this.__class.__element[0]);
		this._interface.SetID(connect_key);
		this._write_factory = ALittle.NewObject(this.__class.__element[1]);
		this._is_connected = true;
		this._connect_key = connect_key;
		this._route_type = route_type;
		this._route_num = route_num;
	},
	get route_type() {
		return this._route_type;
	},
	get route_num() {
		return this._route_num;
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
}, "ALittle.MsgSessionTemplate");

}