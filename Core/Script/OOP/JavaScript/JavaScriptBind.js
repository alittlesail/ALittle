
if (typeof JavaScript == "undefined") JavaScript = {};

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


function Bind(func)
	ALittle.Assert(func, "func == null")
	if arguments[1] == nil then
		return func
	end
	return func:apply(nil, Array.prototype.slice:call(arguments, 1))
end

