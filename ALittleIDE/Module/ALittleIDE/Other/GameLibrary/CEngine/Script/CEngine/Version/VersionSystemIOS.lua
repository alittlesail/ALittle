-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ALittle = ALittle
local ALittle = ALittle


assert(ALittle.VersionSystem, " extends class:ALittle.VersionSystem is nil")
ALittle.VersionSystemIOS = Lua.Class(ALittle.VersionSystem, "ALittle.VersionSystemIOS")

function ALittle.VersionSystemIOS:Ctor(account_name, module_name)
	___rawset(self, "_install_name", "Install.ipa")
end

function ALittle.VersionSystemIOS.RefreshVersion()
	ALittle.VersionSystemAndroid.RefreshVersion()
end

function ALittle.VersionSystemIOS:Install(install_name)
end

end