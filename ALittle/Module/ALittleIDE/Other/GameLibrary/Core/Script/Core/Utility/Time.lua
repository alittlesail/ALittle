-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.Time_GetCurTime()
	return os.time()
end

function ALittle.Time_GetCurDate(time)
	return os.date("%Y-%m-%d-%H-%M-%S", time)
end

function ALittle.Time_GetCurYMD(time)
	return os.date("%Y-%m-%d", time)
end

end