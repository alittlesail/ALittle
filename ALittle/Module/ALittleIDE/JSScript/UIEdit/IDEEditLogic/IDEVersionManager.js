{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};


ALittleIDE.IDEVersionManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._version_system = ALittle.VersionSystem.CreateVersionSystem("alittle", "ALittleIDE");
	},
	Shutdown : function() {
		if (this._version_system === undefined) {
			return;
		}
		this._version_system.StopUpdate();
	},
	CreateDialog : function() {
		if (this._dialog === undefined) {
			this._dialog = ALittleIDE.g_Control.CreateControl("ide_version_dialog", this);
			A_LayerManager.AddToModal(this._dialog);
			this._notice_content.text = "";
			this._notice_content.visible = true;
			this._notice_edit.text = "";
			this._notice_edit.visible = false;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = false;
			this._install_btn.visible = false;
			this._restart_btn.visible = false;
		}
	},
	ShowDialog : function() {
		this.CreateDialog();
		this._dialog.visible = true;
		this.UpdateVersion(true);
	},
	HandleCheckClick : function(event) {
		this.UpdateVersion(true);
	},
	HandleUpdateClick : function(event) {
		this.UpdateVersion(false);
	},
	HandleNoUpdateClick : function(event) {
		this._dialog.visible = false;
	},
	HandleInstallClick : function(event) {
		this._version_system.Install(undefined);
	},
	HandleRestartClick : function(event) {
		ALittle.System_Restart();
	},
	CheckVersionUpdate : function() {
		let loop = ALittle.NewObject(ALittle.LoopFunction, this.CheckVersionUpdateImpl.bind(this), -1, 3600000, 0);
		loop.Start();
	},
	CheckVersionUpdateImpl : async function() {
		if (this._version_system.doing) {
			return;
		}
		let result = await this._version_system.UpdateVersion(ALittleIDE.g_IDELoginManager.version_ip, ALittleIDE.g_IDELoginManager.version_port, undefined, true);
		if (result === 2 || result === 3) {
			ALittleIDE.g_IDETool.ShowTipHelp("有最新版本，需要就更新~", 10000);
		}
	},
	UpdateVersion : async function(check) {
		this.CreateDialog();
		if (this._version_system.doing) {
			return;
		}
		if (check) {
			this._notice_content.text = "正在检查版本...";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = true;
			this._install_btn.visible = false;
		} else {
			this._notice_content.text = "正在更新版本...";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = false;
			this._install_btn.visible = false;
		}
		let result = await this._version_system.UpdateVersion(ALittleIDE.g_IDELoginManager.version_ip, ALittleIDE.g_IDELoginManager.version_port, this.HandleUpdateVersion.bind(this), check);
		if (result === 2 || result === 3) {
			let text = "有最新版本，您是否更新?";
			let [new_big_version, new_small_version, new_log_list] = this._version_system.GetNewVersion(5);
			if (new_log_list !== undefined) {
				text = text + "\n" + ALittle.String_Join(new_log_list, "\n");
			}
			this._notice_edit.text = text;
			this._notice_content.visible = false;
			this._notice_edit.visible = true;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = true;
			this._update_btn.visible = true;
			this._check_btn.visible = false;
			this._install_btn.visible = false;
			this._restart_btn.visible = false;
		} else if (result === 1) {
			this._notice_content.text = "您当前已经是最新版本";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = true;
			this._install_btn.visible = false;
			this._restart_btn.visible = false;
		} else if (result === 11) {
			this._notice_content.text = "版本更新失败";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = false;
			this._process_bar.visible = false;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = true;
			this._install_btn.visible = false;
			this._restart_btn.visible = false;
		} else if (result === 12) {
			this._notice_content.text = "版本更新成功，重启软件生效";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = true;
			this._process_bar.visible = true;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = false;
			this._install_btn.visible = false;
			this._restart_btn.visible = true;
		} else if (result === 13) {
			this._notice_content.text = "版本更新成功，需要重新安装";
			this._notice_content.visible = true;
			this._notice_edit.visible = false;
			this._process_bg.visible = true;
			this._process_bar.visible = true;
			this._noupdate_btn.visible = false;
			this._update_btn.visible = false;
			this._check_btn.visible = false;
			this._install_btn.visible = true;
			this._restart_btn.visible = false;
		}
	},
	HandleUpdateVersion : function(file_name, cur_size, total_size, cur_file_index, file_count) {
		this._notice_content.text = "版本正在更新..." + ALittle.Math_Floor(this._version_system.current_update_size / this._version_system.total_update_size * 100) + "%";
		this._notice_content.visible = true;
		this._notice_edit.visible = false;
		this._process_bg.visible = true;
		this._process_bar.visible = true;
		this._process_bar.x = this._process_bg.x;
		this._process_bar.width = (this._version_system.current_update_size / this._version_system.total_update_size) * this._process_bg.width;
		this._noupdate_btn.visible = false;
		this._update_btn.visible = false;
		this._check_btn.visible = false;
		this._install_btn.visible = false;
		this._restart_btn.visible = false;
	},
}, "ALittleIDE.IDEVersionManager");

ALittleIDE.g_IDEVersionManager = ALittle.NewObject(ALittleIDE.IDEVersionManager);
}