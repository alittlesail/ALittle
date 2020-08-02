-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-930447138, "ALittle.Thread", {
name = "ALittle.Thread", ns_name = "ALittle", rl_name = "Thread", hash_code = -930447138,
name_list = {},
type_list = {},
option_map = {}
})

ALittle.Coroutine = Lua.Class(nil, "ALittle.Coroutine")

function ALittle.Coroutine.Resume(thread, ...)
	return coroutine.resume(thread, ...)
end

end