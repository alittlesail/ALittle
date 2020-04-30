-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


local insert = table.insert
local remove = table.remove
local maxn = table.maxn
local sort = table.sort
function List_MaxN(list)
	return maxn(list)
end

function List_Push(list, object)
	insert(list, object)
end

function List_Insert(list, index, object)
	insert(list, index, object)
end

function List_Remove(list, index)
	remove(list, index)
end

function List_Sort(list, cmp)
	sort(list, cmp)
end

