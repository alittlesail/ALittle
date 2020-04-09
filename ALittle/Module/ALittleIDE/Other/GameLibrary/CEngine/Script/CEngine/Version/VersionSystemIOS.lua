
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
VersionSystemIOS = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemIOS")

function VersionSystemIOS:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.ipa")
end

function VersionSystemIOS.RefreshVersion()
	VersionSystemAndroid.RefreshVersion()
end

function VersionSystemIOS:Install(install_name)
end

