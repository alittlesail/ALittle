{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1848509213, "AUIPlugin.AUIWebAccountLogoutEvent", {
name : "AUIPlugin.AUIWebAccountLogoutEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountLogoutEvent", hash_code : -1848509213,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1809602374, "ALittle.S2CWebSession", {
name : "ALittle.S2CWebSession", ns_name : "ALittle", rl_name : "S2CWebSession", hash_code : 1809602374,
name_list : ["session_id"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1652964636, "ALittle.AWebChangePassword", {
name : "ALittle.AWebChangePassword", ns_name : "ALittle", rl_name : "AWebChangePassword", hash_code : 1652964636,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1598450085, "ALittle.QWebLogout", {
name : "ALittle.QWebLogout", ns_name : "ALittle", rl_name : "QWebLogout", hash_code : 1598450085,
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
ALittle.RegStruct(-1373673802, "ALittle.QWebChangePassword", {
name : "ALittle.QWebChangePassword", ns_name : "ALittle", rl_name : "QWebChangePassword", hash_code : -1373673802,
name_list : ["old_password","new_password"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(898014419, "ALittle.QWebLogin", {
name : "ALittle.QWebLogin", ns_name : "ALittle", rl_name : "QWebLogin", hash_code : 898014419,
name_list : ["device_id","client_platform","third_platform","account_name","account_pwd"],
type_list : ["string","string","string","string","string"],
option_map : {}
})
ALittle.RegStruct(-420010531, "AUIPlugin.AUIWebAccountLoginEvent", {
name : "AUIPlugin.AUIWebAccountLoginEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountLoginEvent", hash_code : -420010531,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-417093574, "ALittle.S2CWebAccountInfo", {
name : "ALittle.S2CWebAccountInfo", ns_name : "ALittle", rl_name : "S2CWebAccountInfo", hash_code : -417093574,
name_list : ["account_id","account_name","role_id","role_name","permission_map"],
type_list : ["string","string","string","string","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(-344058063, "ALittle.AWebLogout", {
name : "ALittle.AWebLogout", ns_name : "ALittle", rl_name : "AWebLogout", hash_code : -344058063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-303211063, "ALittle.AWebLogin", {
name : "ALittle.AWebLogin", ns_name : "ALittle", rl_name : "AWebLogin", hash_code : -303211063,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-300988017, "ALittle.S2CWebServerInfo", {
name : "ALittle.S2CWebServerInfo", ns_name : "ALittle", rl_name : "S2CWebServerInfo", hash_code : -300988017,
name_list : ["http_ip","http_port"],
type_list : ["string","int"],
option_map : {}
})
ALittle.RegStruct(-262794256, "AUIPlugin.AUIWebAccountReconnectEvent", {
name : "AUIPlugin.AUIWebAccountReconnectEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountReconnectEvent", hash_code : -262794256,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
AUIPlugin.AUIWebLoginManager = JavaScript.Class(ALittle.EventDispatcher, {
	get msg_client() {
		return this._msg_client;
	},
	Setup : function(ip, port, is_logingate, config) {
		this._logingate_ip = ip;
		this._logingate_port = port;
		this._is_logingate = is_logingate;
		this._config = config;
		this._session_id = "";
		this._account_info = {};
		this._server_info = {};
		this._server_info.http_ip = "";
		this._server_info.http_port = 0;
		this._account_name = "";
		this._account_pwd = "";
		this._first_login = true;
		this._is_login = false;
		this._save_password = config.GetConfig("save_password", false);
		this._auto_login = config.GetConfig("auto_login", false);
		if (this._save_password) {
			this._account_name = config.GetConfig("account_name", "");
			this._account_pwd = ALittle.String_DecryptPassword(this._account_name, config.GetConfig("account_pwd", ""));
		}
		this.Connect();
	},
	Shutdown : function() {
		if (this._msg_client !== undefined) {
			this._msg_client.Close();
			this._msg_client = undefined;
		}
		if (this._login_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._login_dialog);
			this._login_dialog = undefined;
		}
		if (this._password_dialog !== undefined) {
			A_LayerManager.RemoveFromModal(this._password_dialog);
			this._password_dialog = undefined;
		}
	},
	Connect : async function() {
		let client_ip = this._logingate_ip;
		let client_port = this._logingate_port;
		if (this._is_logingate) {
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
			if (result.client_ip === undefined || result.client_ip === "" || result.client_port === undefined) {
				this._msg_client = undefined;
				this.OnConnectFailed();
				A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
				return;
			}
			client_ip = result.client_ip;
			client_port = result.client_port;
		}
		this._msg_client = ALittle.CreateMsgSender(60, true, this.OnDisconnected.bind(this));
		this._msg_client._user_data = this;
		let error = await this._msg_client.Connect(client_ip, client_port);
		if (error !== undefined) {
			this._msg_client = undefined;
			this.OnConnectFailed();
			A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
			return;
		}
		this.OnConnectSucceed();
	},
	OnConnectFailed : function() {
		this.DispatchEvent(___all_struct.get(-262794256), {});
		this.HidePasswordDialog();
	},
	OnConnectSucceed : function() {
		if ((this._first_login && this._auto_login) || (this._login_button !== undefined && this._login_button.disabled) || this._is_login) {
			this.LoginImpl();
		} else {
			this.DispatchEvent(___all_struct.get(-1848509213), {});
		}
	},
	OnDisconnected : function() {
		this.DispatchEvent(___all_struct.get(-262794256), {});
		this.HidePasswordDialog();
		A_LoopSystem.AddTimer(5000, this.Connect.bind(this));
	},
	ShowLoginDialog : function() {
		if (this._login_dialog === undefined) {
			this._login_dialog = AUIPlugin.g_Control.CreateControl("account_login_dialog", this);
			A_LayerManager.AddToModal(this._login_dialog);
			this._login_account.text = this._account_name;
			this._login_password.text = "";
			this._save_password_check.selected = this._save_password;
			this._auto_login_check.selected = this._auto_login;
		}
		this._login_dialog.visible = true;
		this._login_account.DelayFocus();
	},
	HideLoginDialog : function() {
		if (this._login_dialog === undefined) {
			return;
		}
		this._login_dialog.visible = false;
	},
	ShowPasswordDialog : function() {
		if (this._password_dialog === undefined) {
			this._password_dialog = AUIPlugin.g_Control.CreateControl("account_password_dialog", this);
			A_LayerManager.AddToModal(this._password_dialog);
		}
		this._password_dialog.visible = true;
		this._pas_old_password.focus = true;
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
			this._account_pwd = ALittle.String_Md5(this._login_password.text);
		}
		this._save_password = this._save_password_check.selected;
		this._auto_login = this._auto_login_check.selected;
		this.LoginImpl();
	},
	HandleLoginAccountTabKey : function(event) {
		this._login_password.focus = true;
	},
	HandleLoginPasswordTabKey : function(event) {
		this._login_account.focus = true;
	},
	HandleOldPasswordTabKey : function(event) {
		this._pas_new_password.focus = true;
	},
	HandleNewPasswordTabKey : function(event) {
		this._pas_repeat_password.focus = true;
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
		this.DispatchEvent(___all_struct.get(-1848509213), {});
	},
	HandleMsgNForceLogout : function() {
		this._is_login = false;
		g_AUITool.ShowNotice("提示", "您的账号在另一个地方登录");
		if (this._login_button !== undefined) {
			this._login_password.text = "";
			this._account_name = "";
			this._account_pwd = "";
		}
		if (this._change_pas_confirm !== undefined) {
			this._change_pas_confirm.disabled = false;
		}
		this.DispatchEvent(___all_struct.get(-1848509213), {});
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
			g_AUITool.ShowNotice("提示", error);
			return;
		}
		if (this._save_password) {
			this._config.SetConfig("account_name", this._account_name);
			this._config.SetConfig("account_pwd", ALittle.String_CryptPassword(this._account_name, this._account_pwd));
		}
		this._config.SetConfig("save_password", this._save_password);
		this._config.SetConfig("auto_login", this._auto_login);
		this.HideLoginDialog();
		this.DispatchEvent(___all_struct.get(-420010531), {});
	},
	HandlePasswordAlterClick : async function(event) {
		let old_password = this._pas_old_password.text;
		let new_password = this._pas_new_password.text;
		let repeat_password = this._pas_repeat_password.text;
		if (new_password !== repeat_password) {
			g_AUITool.ShowNotice("提示", "新密码和重复密码不一致");
			return;
		}
		this._change_pas_confirm.disabled = true;
		let param = {};
		param.old_password = ALittle.String_Md5(old_password);
		param.new_password = ALittle.String_Md5(new_password);
		let [error, result] = await ALittle.IMsgCommon.InvokeRPC(-1373673802, this._msg_client, param);
		this._change_pas_confirm.disabled = false;
		if (this._change_pas_confirm !== undefined) {
			this._change_pas_confirm.disabled = false;
		}
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
			return;
		}
		g_AUITool.ShowNotice("提示", "密码修改成功");
		this.HidePasswordDialog();
	},
	HandlePasswordCancelClick : function(event) {
		this.HidePasswordDialog();
	},
	IsLogin : function() {
		return this._is_login;
	},
	get account_name() {
		return this._account_name;
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
}, "AUIPlugin.AUIWebLoginManager");

AUIPlugin.HandleMsgNForceLogout = function(client, msg) {
	let manager = client._user_data;
	if (manager === undefined) {
		return;
	}
	manager.HandleMsgNForceLogout();
}

ALittle.RegMsgCallback(1391512615, AUIPlugin.HandleMsgNForceLogout)
AUIPlugin.HandleMsgNWebSession = function(client, msg) {
	let manager = client._user_data;
	if (manager === undefined) {
		return;
	}
	manager.HandleMsgNWebSession(msg);
}

ALittle.RegMsgCallback(1809602374, AUIPlugin.HandleMsgNWebSession)
AUIPlugin.HandleMsgNWebAccountInfo = function(client, msg) {
	let manager = client._user_data;
	if (manager === undefined) {
		return;
	}
	manager.HandleMsgNWebAccountInfo(msg);
}

ALittle.RegMsgCallback(-417093574, AUIPlugin.HandleMsgNWebAccountInfo)
AUIPlugin.HandleMsgNWebServerInfo = function(client, msg) {
	let manager = client._user_data;
	if (manager === undefined) {
		return;
	}
	manager.HandleMsgNWebServerInfo(msg);
}

ALittle.RegMsgCallback(-300988017, AUIPlugin.HandleMsgNWebServerInfo)
}