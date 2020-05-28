-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

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
function Math_Sin(v)
	return sin(v)
end

function Math_Tan(v)
	return tan(v)
end

function Math_Cos(v)
	return cos(v)
end

function Math_Abs(v)
	return abs(v)
end

function Math_Floor(v)
	return floor(v)
end

function Math_Ceil(v)
	return ceil(v)
end

function Math_Sqrt(v)
	return sqrt(v)
end

function Math_ToInt(s)
	local n = tonumber(s)
	if n == nil then
		return nil
	end
	return floor(n)
end

function Math_ToIntOrZero(s)
	local value = Math_ToInt(s)
	if value == nil then
		return 0
	end
	return value
end

function Math_ToDouble(s)
	return tonumber(s)
end

function Math_ToDoubleOrZero(s)
	local value = Math_ToDouble(s)
	if value == nil then
		return 0
	end
	return value
end

function Math_RandomSeed(seed)
	randomseed(seed)
end

function Math_RandomInt(min, max)
	return random(min, max)
end

function Math_RandomDouble(min, max)
	return random() * (max - min) + min
end

