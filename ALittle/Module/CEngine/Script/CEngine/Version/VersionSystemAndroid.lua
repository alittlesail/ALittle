-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
VersionSystemAndroid = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemAndroid")

function VersionSystemAndroid:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.apk")
end

function VersionSystemAndroid.RefreshVersion()
	if File_GetFileAttr(File_BaseFilePath() .. "Module") == nil then
		return
	end
	for file in lfs.dir(File_BaseFilePath() .. "Module") do
		if file ~= "." and file ~= ".." then
			local module_path = "Module/" .. file
			File_MakeDir(File_BaseFilePath() .. module_path)
			if File_GetFileAttr(File_BaseFilePath() .. module_path .. "/CurVersion.db") ~= nil then
				local change = false
				local succeed = File_CopyFileFromAsset(module_path .. "/CurVersion.db", File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
				if succeed then
					local sqlite_out = sqlite3.open(File_BaseFilePath() .. module_path .. "/CurVersion.db")
					if sqlite_out ~= nil then
						local sqlite_in = sqlite3.open(File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
						if sqlite_in ~= nil then
							local sql = "SELECT c_update_time,c_update_index FROM SmallVersion ORDER BY c_update_time DESC,c_update_index DESC LIMIT 1"
							local stmt_in = sqlite_in:prepare(sql)
							local update_time_in = nil
							for row in stmt_in:nrows() do
								update_time_in = row
							end
							stmt_in:reset()
							local stmt_out = sqlite_out:prepare(sql)
							local update_time_out = nil
							for row in stmt_out:nrows() do
								update_time_out = row
							end
							stmt_out:reset()
							local comp = VersionSystem.UpdateTimeIndexComp(update_time_in, update_time_out)
							if comp > 0 then
								local stmt = sqlite_in:prepare("SELECT * FROM SmallVersion WHERE c_update_time>? OR (c_update_time=? AND c_update_index>?)")
								stmt:bind_values(update_time_out.c_update_time, update_time_out.c_update_time, update_time_out.c_update_index)
								for row in stmt:nrows() do
									Log("安装包的版本比热更新版本高，删掉热更新文件:", File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
									File_DeleteFile(File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
									change = true
								end
								stmt:reset()
							end
							sql = "SELECT * FROM BigVersion"
							stmt_in = sqlite_in:prepare(sql)
							local big_version_in = nil
							for row in stmt_in:nrows() do
								big_version_in = row
							end
							stmt_in:reset()
							stmt_out = sqlite_out:prepare(sql)
							local big_version_out = nil
							for row in stmt_out:nrows() do
								big_version_out = row
							end
							stmt_out:reset()
							if big_version_in ~= nil and big_version_out ~= nil and big_version_in.c_db_version > big_version_out.c_db_version then
								change = true
							end
							if big_version_in ~= nil and big_version_out ~= nil and big_version_in.c_db_version ~= big_version_out.c_db_version then
								change = true
								stmt_out = sqlite_out:prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0")
								stmt_in = sqlite_in:prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0 AND c_file_path=?")
								for row in stmt_out:nrows() do
									stmt_in:bind_values(row.c_file_path)
									local has = false
									for _ in stmt_in:nrows() do
										has = true
										break
									end
									stmt_in:reset()
									if has == false then
										Log("删掉残留文件:", File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
										File_DeleteFile(File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
									end
								end
								stmt_out:reset()
							end
							sqlite_in:close()
						end
						sqlite_out:close()
					end
				end
				if change == true then
					File_DeleteFile(File_BaseFilePath() .. module_path .. "/CurVersion.db")
					File_RenameFile(File_BaseFilePath() .. module_path .. "/CurVersionInstall.db", File_BaseFilePath() .. module_path .. "/CurVersion.db")
				else
					File_DeleteFile(File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
				end
			end
		end
	end
end

function VersionSystemAndroid.InstallImpl(install_name)
	System_InstallProgram(install_name)
	System_ForceExit()
end

function VersionSystemAndroid:Install(install_name)
	if install_name == nil then
		install_name = File_BaseFilePath() .. self._update_path .. self._install_name
	end
	os.execute("chmod 777 " .. File_BaseFilePath() .. "Update")
	os.execute("chmod 777 " .. File_BaseFilePath() .. "Update/" .. self._module_name)
	os.execute("chmod 777 " .. File_BaseFilePath() .. "Update/" .. self._module_name .. "/" .. self._install_name)
	local updater = LoopFunction(Lua.Bind(VersionSystemAndroid.InstallImpl, install_name), 1, 0, 1)
	updater:Start()
end

