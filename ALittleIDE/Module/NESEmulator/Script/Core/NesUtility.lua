-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function NESEmulator.ConditionExpr(value, a, b)
	if value then
		return a
	end
	return b
end

function NESEmulator.CopyArrayElements(src, srcPos, dest, destPos, length)
	local i = 0
	while true do
		if not(i < length) then break end
		dest[destPos + i] = src[srcPos + i]
		i = i+(1)
	end
end

end