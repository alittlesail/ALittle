-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
VersionSystemWindows = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemWindows")

function VersionSystemWindows:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.exe")
end

function VersionSystemWindows.RefreshVersion()
end

function VersionSystemWindows.InstallImpl(install_name)
	System_InstallProgram(install_name .. " /silent /norestart")
	System_ForceExit()
end

function VersionSystemWindows:Install(install_name)
	if install_name == nil then
		install_name = File_BaseFilePath() .. self._update_path .. self._install_name
	end
	local updater = LoopFunction(Lua.Bind(VersionSystemWindows.InstallImpl, install_name), 1, 0, 1)
	updater:Start()
end

