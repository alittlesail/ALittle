-- ALittle Generate Lua And Do Not Edit This Line!
module("GBRMaker", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function IDEUtility_CheckResourceName(name)
	local len = ALittle.String_Len(name)
	if len == 0 then
		return false, "命名只能支持字母数字下划线"
	end
	local i = 1
	while true do
		if not(i <= len) then break end
		local byte = ALittle.String_Byte(name, i)
		local check_all = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte >= 48 and byte <= 57 or byte == 95
		if check_all == false then
			return false, "命名只能支持字母数字下划线"
		end
		i = i+(1)
	end
	return true, nil
end

