{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
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

ALittleIDE.g_IDEWebLoginManager = undefined;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittleIDE.IDEUIAccount = JavaScript.Class(ALittle.DisplayLayout, {
	TCtor : function() {
		let logingate_ip = ALittleIDE.g_IDEServerConfig.GetConfig("logingate_ip", "139.159.176.119");
		let logingate_port = ALittleIDE.g_IDEServerConfig.GetConfig("logingate_port", 1000);
		ALittleIDE.g_IDEWebLoginManager = ALittle.NewObject(AUIPlugin.AUIWebLoginManager);
		ALittleIDE.g_IDEWebLoginManager.AddEventListener(___all_struct.get(-262794256), this, this.HandleAccountInReconnect);
		ALittleIDE.g_IDEWebLoginManager.AddEventListener(___all_struct.get(-1848509213), this, this.HandleAccountInLogout);
		ALittleIDE.g_IDEWebLoginManager.AddEventListener(___all_struct.get(-420010531), this, this.HandleAccountInLogin);
		ALittleIDE.g_IDEWebLoginManager.Setup(logingate_ip, logingate_port, true, ALittleIDE.g_IDEConfig);
	},
	Shutdown : function() {
		ALittleIDE.g_IDEWebLoginManager.Shutdown();
	},
	HandleAccountLoginLB : function(event) {
		ALittleIDE.g_IDEWebLoginManager.ShowLoginDialog();
	},
	HandleAccountInLogin : function(event) {
		this._account_login.visible = false;
		this._account_dropdown.visible = true;
		let data_list = [];
		data_list[1 - 1] = "修改密码";
		data_list[2 - 1] = "登出";
		this._account_dropdown.data_list = data_list;
		this._account_dropdown.text = ALittleIDE.g_IDEWebLoginManager.account_name;
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
			ALittleIDE.g_IDEWebLoginManager.Logout();
		} else if (event.target.text === "修改密码") {
			ALittleIDE.g_IDEWebLoginManager.ShowPasswordDialog();
		}
		this._account_dropdown.text = ALittleIDE.g_IDEWebLoginManager.account_name;
	},
}, "ALittleIDE.IDEUIAccount");

}