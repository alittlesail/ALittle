{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};

ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name : "ALittle.QWebLogout", ns_name : "ALittle", rl_name : "QWebLogout", hash_code : 1598450085,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name : "ALittle.AWebLogout", ns_name : "ALittle", rl_name : "AWebLogout", hash_code : -344058063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name : "ALittle.QWebLogin", ns_name : "ALittle", rl_name : "QWebLogin", hash_code : 898014419,
name_list : ["device_id","client_platform","third_platform","account_name","account_pwd"],
type_list : ["string","string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name : "ALittle.AWebLogin", ns_name : "ALittle", rl_name : "AWebLogin", hash_code : -303211063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name : "ALittle.QWebChangePassword", ns_name : "ALittle", rl_name : "QWebChangePassword", hash_code : -1373673802,
name_list : ["old_password","new_password"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name : "ALittle.AWebChangePassword", ns_name : "ALittle", rl_name : "AWebChangePassword", hash_code : 1652964636,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1391512615, "ALittle.S2CWebForceLogout", {
name : "ALittle.S2CWebForceLogout", ns_name : "ALittle", rl_name : "S2CWebForceLogout", hash_code : 1391512615,
name_list : ["reason"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name : "ALittle.S2CWebSession", ns_name : "ALittle", rl_name : "S2CWebSession", hash_code : 1809602374,
name_list : ["session_id"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name : "ALittle.S2CWebAccountInfo", ns_name : "ALittle", rl_name : "S2CWebAccountInfo", hash_code : -417093574,
name_list : ["account_id","account_name","role_id","role_name","permission_map"],
type_list : ["string","string","string","string","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name : "ALittle.S2CWebServerInfo", ns_name : "ALittle", rl_name : "S2CWebServerInfo", hash_code : -300988017,
name_list : ["http_ip","http_port"],
type_list : ["string","int"],
option_map : {}
})

ALittleIDE.IDELoginManager = JavaScript.Class(undefined, {
	Ctor : function() {
		let config = ALittle.CreateConfigSystem(ALittleIDE.g_ModuleBasePath + "/Other/Server.cfg");
		this._logingate_ip = config.GetConfig("logingate_ip", "139.159.176.119");
		this._logingate_port = config.GetConfig("logingate_port", 1000);
		this._version_ip = config.GetConfig("version_ip", "139.159.176.119");
		this._version_port = config.GetConfig("version_port", 1011);
		this._msg_client = ALittle.CreateMsgSender(30, true);
		this._session_id = "";
		this._account_info = {};
		this._server_info = {};
		this._server_info.http_ip = "";
		this._server_info.http_port = 0;
		this._account_name = "";
		this._account_pwd = "";
		this._first_login = true;
		this._is_login = false;
	},
	get account_name() {
		return this._account_name;
	},
	Setup : function() {
		this._save_password = ALittleIDE.g_IDEConfig.GetConfig("save_password", false);
		this._auto_login = ALittleIDE.g_IDEConfig.GetConfig("auto_login", false);
		if (this._save_password) {
			this._account_name = ALittleIDE.g_IDEConfig.GetConfig("account_name", "");
			this._account_pwd = ALittle.String_DecryptPassword(this._account_name, ALittleIDE.g_IDEConfig.GetConfig("account_pwd", ""));
		}
		this.Connect();
	},
	Shutdown : function() {
		if (this._msg_client !== undefined) {
			this._msg_client.Close();
			this._msg_client = undefined;
		}
	},
	Connect : async function() {
		let param = {};
		param.route_type = 3;
		let client = ALittle.CreateHttpSender(this._logingate_ip, this._logingate_port);
		let [error, result] = await ALittle.IHttpSender.Invoke("GatewayServer.QRouteInfo", client, param);
		if (error !== undefined) {
			ALittle.Log(error);
			this._msg_client = undefined;
			this.OnConnectFailed();
			A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
			return;
		}
		this._msg_client = ALittle.CreateMsgSender(60, true, this.OnDisconnected.bind(this));
		error = await this._msg_client.Connect(result.client_ip, result.client_port);
		if (error !== undefined) {
			this._msg_client = undefined;
			this.OnConnectFailed();
			A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
			return;
		}
		this.OnConnectSucceed();
	},
	OnConnectFailed : function() {
		ALittleIDE.g_IDECenter.AccountInReConnect();
		this.HidePasswordDialog();
	},
	OnConnectSucceed : function() {
		if ((this._first_login && this._auto_login) || (this._login_button !== undefined && this._login_button.disabled) || this._is_login) {
			this.LoginImpl();
		} else {
			ALittleIDE.g_IDECenter.AccountInLogout();
		}
	},
	OnDisconnected : function() {
		ALittleIDE.g_IDECenter.AccountInReConnect();
		this.HidePasswordDialog();
		A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
	},
	ShowLoginDialog : function() {
		if (this._login_dialog === undefined) {
			this._login_dialog = ALittleIDE.g_Control.CreateControl("ide_account_login_dialog", this);
			ALittleIDE.g_IDECenter.dialog_layer.AddChild(this._login_dialog);
			this._login_account.text = this._account_name;
			this._login_password.text = "";
			this._save_password_check.selected = this._save_password;
			this._auto_login_check.selected = this._auto_login;
		}
		this._login_dialog.visible = true;
	},
	HideLoginDialog : function() {
		if (this._login_dialog === undefined) {
			return;
		}
		this._login_dialog.visible = false;
	},
	ShowPasswordDialog : function() {
		if (this._password_dialog === undefined) {
			this._password_dialog = ALittleIDE.g_Control.CreateControl("ide_account_password_dialog", this);
			ALittleIDE.g_IDECenter.dialog_layer.AddChild(this._password_dialog);
		}
		this._password_dialog.visible = true;
		this._pas_old_password.text = "";
		this._pas_new_password.text = "";
		this._pas_repeat_password.text = "";
	},
	HidePasswordDialog : function() {
		if (this._password_dialog === undefined) {
			return;
		}
		this._password_dialog.visible = false;
	},
	HandleLoginClick : function(event) {
		if (this._login_button.disabled) {
			return;
		}
		this._login_button.disabled = true;
		if (this._msg_client.IsConnected() === false) {
			return;
		}
		this._account_name = this._login_account.text;
		if (this._login_password.text !== "") {
			this._account_pwd = ALittle.String_MD5(this._login_password.text);
		}
		this._save_password = this._save_password_check.selected;
		this._auto_login = this._auto_login_check.selected;
		this.LoginImpl();
	},
	Logout : async function() {
		if (this._msg_client === undefined) {
			return;
		}
		let param = {};
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(1598450085, this._msg_client, param);
		if (error !== undefined) {
			ALittle.Error(error);
			return;
		}
		this._is_login = false;
		if (this._login_button !== undefined) {
			this._login_password.text = "";
			this._account_name = "";
			this._account_pwd = "";
		}
		if (this._change_pas_confirm !== undefined) {
			this._change_pas_confirm.disabled = false;
		}
		ALittleIDE.g_IDECenter.AccountInLogout();
	},
	HandleMsgNForceLogout : function() {
		this._is_login = false;
		ALittleIDE.g_IDETool.ShowNotice("提示", "您的账号在另一个地方登录");
		if (this._login_button !== undefined) {
			this._login_password.text = "";
			this._account_name = "";
			this._account_pwd = "";
		}
		if (this._change_pas_confirm !== undefined) {
			this._change_pas_confirm.disabled = false;
		}
		ALittleIDE.g_IDECenter.AccountInLogout();
	},
	HandleMsgNWebSession : function(msg) {
		this._session_id = msg.session_id;
	},
	HandleMsgNWebAccountInfo : function(msg) {
		this._account_info = msg;
	},
	HandleMsgNWebServerInfo : function(msg) {
		this._server_info = msg;
	},
	LoginImpl : async function() {
		if (this._msg_client === undefined) {
			return;
		}
		this._first_login = false;
		let param = {};
		param.device_id = "";
		param.third_platform = "account";
		param.client_platform = ALittle.System_GetPlatform();
		param.account_name = this._account_name;
		param.account_pwd = this._account_pwd;
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(898014419, this._msg_client, param);
		if (this._login_button !== undefined) {
			this._login_button.disabled = false;
		}
		this._is_login = (error === undefined);
		if (error !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", error);
			return;
		}
		if (this._save_password) {
			ALittleIDE.g_IDEConfig.SetConfig("account_name", this._account_name);
			ALittleIDE.g_IDEConfig.SetConfig("account_pwd", ALittle.String_CryptPassword(this._account_name, this._account_pwd));
		}
		ALittleIDE.g_IDEConfig.SetConfig("save_password", this._save_password);
		ALittleIDE.g_IDEConfig.SetConfig("auto_login", this._auto_login);
		this.HideLoginDialog();
		ALittleIDE.g_IDECenter.AccountInLogin();
	},
	HandlePasswordAlterClick : async function(event) {
		let old_password = this._pas_old_password.text;
		let new_password = this._pas_new_password.text;
		let repeat_password = this._pas_repeat_password.text;
		if (new_password !== repeat_password) {
			ALittleIDE.g_IDETool.ShowNotice("提示", "新密码和重复密码不一致");
			return;
		}
		this._change_pas_confirm.disabled = true;
		let param = {};
		param.old_password = ALittle.String_MD5(old_password);
		param.new_password = ALittle.String_MD5(new_password);
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(-1373673802, this._msg_client, param);
		this._change_pas_confirm.disabled = false;
		if (ALittleIDE.g_IDELoginManager._change_pas_confirm !== undefined) {
			ALittleIDE.g_IDELoginManager._change_pas_confirm.disabled = false;
		}
		if (error !== undefined) {
			ALittleIDE.g_IDETool.ShowNotice("提示", error);
			return;
		}
		ALittleIDE.g_IDETool.ShowNotice("提示", "密码修改成功");
		ALittleIDE.g_IDELoginManager.HidePasswordDialog();
	},
	HandlePasswordCancelClick : function(event) {
		this.HidePasswordDialog();
	},
	IsLogin : function() {
		return this._is_login;
	},
	get account_id() {
		return this._account_info.account_id;
	},
	get session_id() {
		return this._session_id;
	},
	get http_ip() {
		return this._server_info.http_ip;
	},
	get http_port() {
		return this._server_info.http_port;
	},
	get version_ip() {
		return this._version_ip;
	},
	get version_port() {
		return this._version_port;
	},
}, "ALittleIDE.IDELoginManager");

ALittleIDE.g_IDELoginManager = ALittle.NewObject(ALittleIDE.IDELoginManager);
ALittleIDE.HandleMsgNForceLogout = function(client, msg) {
	ALittleIDE.g_IDELoginManager.HandleMsgNForceLogout();
}

ALittle.RegMsgCallback(1391512615, ALittleIDE.HandleMsgNForceLogout)
ALittleIDE.HandleMsgNWebSession = function(client, msg) {
	ALittleIDE.g_IDELoginManager.HandleMsgNWebSession(msg);
}

ALittle.RegMsgCallback(1809602374, ALittleIDE.HandleMsgNWebSession)
ALittleIDE.HandleMsgNWebAccountInfo = function(client, msg) {
	ALittleIDE.g_IDELoginManager.HandleMsgNWebAccountInfo(msg);
}

ALittle.RegMsgCallback(-417093574, ALittleIDE.HandleMsgNWebAccountInfo)
ALittleIDE.HandleMsgNWebServerInfo = function(client, msg) {
	ALittleIDE.g_IDELoginManager.HandleMsgNWebServerInfo(msg);
}

ALittle.RegMsgCallback(-300988017, ALittleIDE.HandleMsgNWebServerInfo)
}