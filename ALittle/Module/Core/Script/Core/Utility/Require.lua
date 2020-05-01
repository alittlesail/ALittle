-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function Require(base_path, url)
local ___COROUTINE = coroutine.running()
	require(base_path .. url)
	return nil
end

