-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local error = error
function Lua.TCall(...)
	local out_list = {pcall(...)}
	if out_list[1] ~= true then
		if out_list[2] == nil then
			return "nil"
		end
		return out_list[2]
	end
	local l = table.maxn(out_list)
	out_list[1] = nil
	return unpack(out_list, 1, l)
end

function Lua.Throw(msg)
	error(msg)
end

function Lua.Assert(value, msg)
	if value ~= nil and value ~= false then
		return
	end
	if msg == nil then
		msg = "Assert failed"
	end
	error(msg)
end

end