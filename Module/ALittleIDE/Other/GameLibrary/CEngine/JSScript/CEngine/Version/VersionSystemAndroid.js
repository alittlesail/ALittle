{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.VersionSystem === undefined) throw new Error(" extends class:ALittle.VersionSystem is undefined");
ALittle.VersionSystemAndroid = JavaScript.Class(ALittle.VersionSystem, {
	Ctor : function(account_name, module_name) {
		this._install_name = "Install.apk";
	},
	RefreshVersion : function() {
		if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + "Module") === undefined) {
			return;
		}
		for (let file of ALittle.File_IteratorDir(ALittle.File_BaseFilePath() + "Module")) {
			if (file !== "." && file !== "..") {
				let module_path = "Module/" + file;
				ALittle.File_MakeDir(ALittle.File_BaseFilePath() + module_path);
				if (ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() + module_path + "/CurVersion.db") !== undefined) {
					let change = false;
					let succeed = ALittle.File_CopyFileFromAsset(module_path + "/CurVersion.db", ALittle.File_BaseFilePath() + module_path + "/CurVersionInstall.db");
					if (succeed) {
						let sqlite_out = lua.sqlite3.open(ALittle.File_BaseFilePath() + module_path + "/CurVersion.db");
						if (sqlite_out !== undefined) {
							let sqlite_in = lua.sqlite3.open(ALittle.File_BaseFilePath() + module_path + "/CurVersionInstall.db");
							if (sqlite_in !== undefined) {
								let sql = "SELECT c_update_time,c_update_index FROM SmallVersion ORDER BY c_update_time DESC,c_update_index DESC LIMIT 1";
								let stmt_in = sqlite_in.prepare(sql);
								let update_time_in = undefined;
								for (let row of stmt_in.nrows()) {
									update_time_in = row;
								}
								stmt_in.reset();
								let stmt_out = sqlite_out.prepare(sql);
								let update_time_out = undefined;
								for (let row of stmt_out.nrows()) {
									update_time_out = row;
								}
								stmt_out.reset();
								let comp = ALittle.VersionSystem.UpdateTimeIndexComp(update_time_in, update_time_out);
								if (comp > 0) {
									let stmt = sqlite_in.prepare("SELECT * FROM SmallVersion WHERE c_update_time>? OR (c_update_time=? AND c_update_index>?)");
									stmt.bind_values(update_time_out.c_update_time, update_time_out.c_update_time, update_time_out.c_update_index);
									for (let row of stmt.nrows()) {
										ALittle.Log("安装包的版本比热更新版本高，删掉热更新文件:", ALittle.File_BaseFilePath() + module_path + "/" + row.c_file_path);
										ALittle.File_DeleteFile(ALittle.File_BaseFilePath() + module_path + "/" + row.c_file_path);
										change = true;
									}
									stmt.reset();
								}
								sql = "SELECT * FROM BigVersion";
								stmt_in = sqlite_in.prepare(sql);
								let big_version_in = undefined;
								for (let row of stmt_in.nrows()) {
									big_version_in = row;
								}
								stmt_in.reset();
								stmt_out = sqlite_out.prepare(sql);
								let big_version_out = undefined;
								for (let row of stmt_out.nrows()) {
									big_version_out = row;
								}
								stmt_out.reset();
								if (big_version_in !== undefined && big_version_out !== undefined && big_version_in.c_db_version > big_version_out.c_db_version) {
									change = true;
								}
								if (big_version_in !== undefined && big_version_out !== undefined && big_version_in.c_db_version !== big_version_out.c_db_version) {
									change = true;
									stmt_out = sqlite_out.prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0");
									stmt_in = sqlite_in.prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0 AND c_file_path=?");
									for (let row of stmt_out.nrows()) {
										stmt_in.bind_values(row.c_file_path);
										let has = false;
										for (let _ of stmt_in.nrows()) {
											has = true;
											break;
										}
										stmt_in.reset();
										if (has === false) {
											ALittle.Log("删掉残留文件:", ALittle.File_BaseFilePath() + module_path + "/" + row.c_file_path);
											ALittle.File_DeleteFile(ALittle.File_BaseFilePath() + module_path + "/" + row.c_file_path);
										}
									}
									stmt_out.reset();
								}
								sqlite_in.close();
							}
							sqlite_out.close();
						}
					}
					if (change === true) {
						ALittle.File_DeleteFile(ALittle.File_BaseFilePath() + module_path + "/CurVersion.db");
						ALittle.File_RenameFile(ALittle.File_BaseFilePath() + module_path + "/CurVersionInstall.db", ALittle.File_BaseFilePath() + module_path + "/CurVersion.db");
					} else {
						ALittle.File_DeleteFile(ALittle.File_BaseFilePath() + module_path + "/CurVersionInstall.db");
					}
				}
			}
		}
	},
	InstallImpl : function(install_name) {
		ALittle.System_InstallProgram(install_name);
		ALittle.System_ForceExit();
	},
	Install : function(install_name) {
		if (install_name === undefined) {
			install_name = ALittle.File_BaseFilePath() + this._update_path + this._install_name;
		}
		lua.os.execute("chmod 777 " + ALittle.File_BaseFilePath() + "Update");
		lua.os.execute("chmod 777 " + ALittle.File_BaseFilePath() + "Update/" + this._module_name);
		lua.os.execute("chmod 777 " + ALittle.File_BaseFilePath() + "Update/" + this._module_name + "/" + this._install_name);
		let updater = ALittle.NewObject(ALittle.LoopFunction, ALittle.VersionSystemAndroid.InstallImpl.bind(undefined, install_name), 1, 0, 1);
		updater.Start();
	},
}, "ALittle.VersionSystemAndroid");

}