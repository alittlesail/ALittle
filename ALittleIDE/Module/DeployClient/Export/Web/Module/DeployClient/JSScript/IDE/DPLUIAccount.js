{
if (typeof DeployClient === "undefined") window.DeployClient = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1848509213, "AUIPlugin.AUIWebAccountLogoutEvent", {
name : "AUIPlugin.AUIWebAccountLogoutEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountLogoutEvent", hash_code : -1848509213,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-420010531, "AUIPlugin.AUIWebAccountLoginEvent", {
name : "AUIPlugin.AUIWebAccountLoginEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountLoginEvent", hash_code : -420010531,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-262794256, "AUIPlugin.AUIWebAccountReconnectEvent", {
name : "AUIPlugin.AUIWebAccountReconnectEvent", ns_name : "AUIPlugin", rl_name : "AUIWebAccountReconnectEvent", hash_code : -262794256,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

DeployClient.g_DPLWebLoginManager = undefined;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
DeployClient.DPLUIAccount = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		let client_ip = DeployClient.g_DPLServerConfig.GetConfig("client_ip", "139.159.176.119");
		let client_port = DeployClient.g_DPLServerConfig.GetConfig("client_port", 1800);
		DeployClient.g_DPLWebLoginManager = ALittle.NewObject(AUIPlugin.AUIWebLoginManager);
		DeployClient.g_DPLWebLoginManager.AddEventListener(___all_struct.get(-262794256), this, this.HandleAccountInReconnect);
		DeployClient.g_DPLWebLoginManager.AddEventListener(___all_struct.get(-1848509213), this, this.HandleAccountInLogout);
		DeployClient.g_DPLWebLoginManager.AddEventListener(___all_struct.get(-420010531), this, this.HandleAccountInLogin);
		DeployClient.g_DPLWebLoginManager.Setup(client_ip, client_port, false, DeployClient.g_DPLConfig);
	},
	Shutdown : function() {
		DeployClient.g_DPLWebLoginManager.Shutdown();
	},
	HandleAccountLoginLB : function(event) {
		DeployClient.g_DPLWebLoginManager.ShowLoginDialog();
	},
	HandleAccountInLogin : function(event) {
		this._account_login.visible = false;
		this._account_dropdown.visible = true;
		let data_list = [];
		data_list[1 - 1] = "修改密码";
		data_list[2 - 1] = "登出";
		this._account_dropdown.data_list = data_list;
		this._account_dropdown.text = DeployClient.g_DPLWebLoginManager.account_name;
		this._account_icon.x_value = this._account_dropdown.x_value + this._account_dropdown.width + 5;
	},
	HandleAccountInLogout : function(event) {
		this._account_login.text = "请登录";
		this._account_login.underline = true;
		this._account_login.visible = true;
		this._account_login.disabled = false;
		this._account_dropdown.visible = false;
		this._account_icon.x_value = this._account_login.x_value + this._account_login.width + 5;
	},
	HandleAccountInReconnect : function(event) {
		this._account_login.text = "正在重连";
		this._account_login.underline = false;
		this._account_login.visible = true;
		this._account_login.disabled = true;
		this._account_dropdown.visible = false;
		this._account_icon.x_value = this._account_login.x_value + this._account_login.width + 5;
	},
	HandleAccountDropdownChange : function(event) {
		if (event.target.text === "登出") {
			DeployClient.g_DPLWebLoginManager.Logout();
		} else if (event.target.text === "修改密码") {
			DeployClient.g_DPLWebLoginManager.ShowPasswordDialog();
		}
		this._account_dropdown.text = DeployClient.g_DPLWebLoginManager.account_name;
	},
}, "DeployClient.DPLUIAccount");

}