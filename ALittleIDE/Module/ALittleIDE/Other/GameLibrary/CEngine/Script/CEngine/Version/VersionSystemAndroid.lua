-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
ALittle.VersionSystemAndroid = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemAndroid")

function ALittle.VersionSystemAndroid:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.apk")
end

function ALittle.VersionSystemAndroid.RefreshVersion()
	if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. "Module") == nil then
		return
	end
	local folder_list = carp.GetFolderNameListInFolder(ALittle.File_BaseFilePath() .. "Module")
	for index, file in ___ipairs(folder_list) do
		local module_path = "Module/" .. file
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. module_path)
		if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. module_path .. "/CurVersion.db") ~= nil then
			local change = false
			local succeed = ALittle.File_CopyFileFromAsset(module_path .. "/CurVersion.db", ALittle.File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
			if succeed then
				local sqlite_out = sqlite3.open(ALittle.File_BaseFilePath() .. module_path .. "/CurVersion.db")
				if sqlite_out ~= nil then
					local sqlite_in = sqlite3.open(ALittle.File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
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
						local comp = ALittle.VersionSystem.UpdateTimeIndexComp(update_time_in, update_time_out)
						if comp > 0 then
							local stmt = sqlite_in:prepare("SELECT * FROM SmallVersion WHERE c_update_time>? OR (c_update_time=? AND c_update_index>?)")
							stmt:bind_values(update_time_out.c_update_time, update_time_out.c_update_time, update_time_out.c_update_index)
							for row in stmt:nrows() do
								ALittle.Log("安装包的版本比热更新版本高，删掉热更新文件:", ALittle.File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
								ALittle.File_DeleteFile(ALittle.File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
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
									ALittle.Log("删掉残留文件:", ALittle.File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
									ALittle.File_DeleteFile(ALittle.File_BaseFilePath() .. module_path .. "/" .. row.c_file_path)
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
				ALittle.File_DeleteFile(ALittle.File_BaseFilePath() .. module_path .. "/CurVersion.db")
				ALittle.File_RenameFile(ALittle.File_BaseFilePath() .. module_path .. "/CurVersionInstall.db", ALittle.File_BaseFilePath() .. module_path .. "/CurVersion.db")
			else
				ALittle.File_DeleteFile(ALittle.File_BaseFilePath() .. module_path .. "/CurVersionInstall.db")
			end
		end
	end
end

function ALittle.VersionSystemAndroid.InstallImpl(install_name)
	ALittle.System_InstallProgram(install_name)
	ALittle.System_ForceExit()
end

function ALittle.VersionSystemAndroid:Install(install_name)
	if install_name == nil then
		install_name = ALittle.File_BaseFilePath() .. self._update_path .. self._install_name
	end
	os.execute("chmod 777 " .. ALittle.File_BaseFilePath() .. "Update")
	os.execute("chmod 777 " .. ALittle.File_BaseFilePath() .. "Update/" .. self._module_name)
	os.execute("chmod 777 " .. ALittle.File_BaseFilePath() .. "Update/" .. self._module_name .. "/" .. self._install_name)
	local updater = ALittle.LoopFunction(Lua.Bind(ALittle.VersionSystemAndroid.InstallImpl, install_name), 1, 0, 1)
	updater:Start()
end

end