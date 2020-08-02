-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local tonumber = tonumber
local floor = math.floor
local ceil = math.ceil
local random = math.random
local randomseed = math.randomseed
local abs = math.abs
local cos = math.cos
local sin = math.sin
local tan = math.tan
local sqrt = math.sqrt
function ALittle.Math_Min(x, y)
	if x < y then
		return x
	end
	return y
end

function ALittle.Math_Max(x, y)
	if x < y then
		return y
	end
	return x
end

function ALittle.Math_Sin(v)
	return sin(v)
end

function ALittle.Math_Tan(v)
	return tan(v)
end

function ALittle.Math_Cos(v)
	return cos(v)
end

function ALittle.Math_Abs(v)
	return abs(v)
end

function ALittle.Math_Floor(v)
	return floor(v)
end

function ALittle.Math_Ceil(v)
	return ceil(v)
end

function ALittle.Math_Sqrt(v)
	return sqrt(v)
end

function ALittle.Math_ToInt(s)
	local n = tonumber(s)
	if n == nil then
		return nil
	end
	return floor(n)
end

function ALittle.Math_ToIntOrZero(s)
	local value = ALittle.Math_ToInt(s)
	if value == nil then
		return 0
	end
	return value
end

function ALittle.Math_ToDouble(s)
	return tonumber(s)
end

function ALittle.Math_ToDoubleOrZero(s)
	local value = ALittle.Math_ToDouble(s)
	if value == nil then
		return 0
	end
	return value
end

function ALittle.Math_RandomSeed(seed)
	randomseed(seed)
end

function ALittle.Math_RandomInt(min, max)
	return random(min, max)
end

function ALittle.Math_RandomDouble(min, max)
	return random() * (max - min) + min
end

end