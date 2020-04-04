
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


local tonumber = tonumber
local floor = math.floor
local random = math.random
local randomseed = math.randomseed
local abs = math.abs
local cos = math.cos
local sin = math.sin
function Math_Sin(v)
	return sin(v)
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

function Math_ToInt(s)
	return floor(tonumber(s))
end

function Math_ToDouble(s)
	return tonumber(s)
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

