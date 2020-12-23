-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
ALittle.VersionSystemWindows = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemWindows")

function ALittle.VersionSystemWindows:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.exe")
end

function ALittle.VersionSystemWindows.RefreshVersion()
end

function ALittle.VersionSystemWindows.InstallImpl(install_name)
	ALittle.System_InstallProgram(install_name .. " /silent /norestart")
	ALittle.System_ForceExit()
end

function ALittle.VersionSystemWindows:Install(install_name)
	if install_name == nil then
		install_name = ALittle.File_BaseFilePath() .. self._update_path .. self._install_name
	end
	local updater = ALittle.LoopFunction(Lua.Bind(ALittle.VersionSystemWindows.InstallImpl, install_name), 1, 0, 1)
	updater:Start()
end

end