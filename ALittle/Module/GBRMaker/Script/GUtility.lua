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

function IDECoordVirtual2Show(x, y, unit_real_width, unit_width, unit_real_height, unit_height)
	local show_x = y * unit_real_width / 2 + x * unit_real_width - unit_width / 2
	local show_y = y * unit_real_height * 3 / 4 - unit_height / 2
	return show_x, show_y
end

function IDECoordShow2Virtual(x, y, unit_real_width, unit_width, unit_real_height, unit_height)
	local yy = y / ALittle.Math_Cos(3.1415926 / 6)
	local offset_yy = yy + unit_real_width / 2
	local virutal_y = ALittle.Math_Floor(offset_yy / unit_real_width)
	local virtual_x = ALittle.Math_Floor(((x + unit_width / 2) - virutal_y * unit_real_width / 2) / unit_real_width)
	return virtual_x, virutal_y
end

