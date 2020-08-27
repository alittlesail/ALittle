-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function GBRMaker.IDEUtility_CheckResourceName(name)
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

GBRMaker.WIDTH_RATE = ALittle.Math_Sqrt(3)
GBRMaker.HEIGHT_RATE = 2
function GBRMaker.IDECoordVirtual2Show(x, y, unit_length)
	local unit_width = unit_length * GBRMaker.WIDTH_RATE
	local show_x = x * unit_width + y * unit_width / 2
	local show_y = y * unit_length * 3 / 2
	return show_x, show_y
end

function GBRMaker.IDECoordShow2Virtual(x, y, unit_length)
	local unit_width = unit_length * GBRMaker.WIDTH_RATE
	local yy = y / ALittle.Math_Cos(3.1415926 / 6)
	local virtual_y = ALittle.Math_Floor((yy + unit_width / 2) / unit_width)
	local xx = x - virtual_y * unit_width / 2
	local virtual_x = ALittle.Math_Floor((xx + unit_width / 2) / unit_width)
	return virtual_x, virtual_y
end

end