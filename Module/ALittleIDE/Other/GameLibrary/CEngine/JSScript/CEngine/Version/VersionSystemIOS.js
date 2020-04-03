{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.VersionSystem === undefined) throw new Error(" extends class:ALittle.VersionSystem is undefined");
ALittle.VersionSystemIOS = JavaScript.Class(ALittle.VersionSystem, {
	Ctor : function(account_name, module_name) {
		this._install_name = "Install.ipa";
	},
	RefreshVersion : function() {
		ALittle.VersionSystemAndroid.RefreshVersion();
	},
	Install : function(install_name) {
	},
}, "ALittle.VersionSystemIOS");

}