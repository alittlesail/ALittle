-- ALittle Generate Lua
module("HelloWorld", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


require(___thispath.."../../../../../Std/Script/ALittle")
function Main()
	ALittle.Log("HelloWorld")
	A_Schedule:Run()
end

