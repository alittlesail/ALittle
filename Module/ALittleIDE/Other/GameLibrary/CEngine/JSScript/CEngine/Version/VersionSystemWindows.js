{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.VersionSystem === undefined) throw new Error(" extends class:ALittle.VersionSystem is undefined");
ALittle.VersionSystemWindows = JavaScript.Class(ALittle.VersionSystem, {
	Ctor : function(account_name, module_name) {
		this._install_name = "Install.exe";
	},
	RefreshVersion : function() {
	},
	InstallImpl : function(install_name) {
		ALittle.System_InstallProgram(install_name + " /silent /norestart");
		ALittle.System_ForceExit();
	},
	Install : function(install_name) {
		if (install_name === undefined) {
			install_name = ALittle.File_BaseFilePath() + this._update_path + this._install_name;
		}
		let updater = ALittle.NewObject(ALittle.LoopFunction, ALittle.VersionSystemWindows.InstallImpl.bind(undefined, install_name), 1, 0, 1);
		updater.Start();
	},
}, "ALittle.VersionSystemWindows");

}