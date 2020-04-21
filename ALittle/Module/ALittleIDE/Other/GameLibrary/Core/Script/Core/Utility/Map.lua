
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function IsEmpty(object)
	return next(object) == nil
end

