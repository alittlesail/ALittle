-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

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

function List_PushList(list, other_list)
	for index, other in ___ipairs(other_list) do
		List_Push(list, other)
	end
end

function List_Insert(list, index, object)
	insert(list, index, object)
end

function List_IndexOf(list, object)
	for index, o in ___ipairs(list) do
		if o == object then
			return index
		end
	end
	return nil
end

function List_Remove(list, index)
	remove(list, index)
end

function List_Splice(list, index, count)
	do
		local endi = index + count
		while list[endi] ~= nil do
			list[index] = list[endi]
			index = index + 1
			endi = endi + 1
		end
		while count > 0 do
			list[endi - 1] = nil
			endi = endi - 1
			count = count - 1
		end
	end
end

function List_Sort(list, cmp)
	sort(list, cmp)
end

