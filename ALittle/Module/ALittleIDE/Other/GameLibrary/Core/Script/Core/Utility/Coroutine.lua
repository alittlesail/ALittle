-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})

Coroutine = Lua.Class(nil, "ALittle.Coroutine")

function Coroutine.Resume(thread, ...)
	return coroutine.resume(thread, ...)
end

