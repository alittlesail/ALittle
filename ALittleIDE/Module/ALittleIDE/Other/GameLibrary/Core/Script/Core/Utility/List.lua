-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


local insert = table.insert
local remove = table.remove
local maxn = table.maxn
local sort = table.sort
function ALittle.List_MaxN(list)
	return maxn(list)
end

function ALittle.List_Push(list, object)
	insert(list, object)
end

function ALittle.List_Shuffle(list)
	local len = ALittle.List_MaxN(list)
	local i = 1
	while true do
		if not(i <= len) then break end
		local index = ALittle.Math_RandomInt(i, len)
		local temp = list[index]
		list[index] = list[i]
		list[i] = temp
		i = i+(1)
	end
end

function ALittle.List_PushList(list, other_list)
	for index, other in ___ipairs(other_list) do
		ALittle.List_Push(list, other)
	end
end

function ALittle.List_Find(list, object)
	for index, o in ___ipairs(list) do
		if o == object then
			return index
		end
	end
	return nil
end

function ALittle.List_Copy(list)
	local new_list = {}
	for index, o in ___ipairs(list) do
		new_list[index] = o
	end
	return new_list
end

function ALittle.List_Insert(list, index, object)
	insert(list, index, object)
end

function ALittle.List_IndexOf(list, object)
	for index, o in ___ipairs(list) do
		if o == object then
			return index
		end
	end
	return nil
end

function ALittle.List_Remove(list, index)
	remove(list, index)
end

function ALittle.List_Splice(list, index, count)
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

function ALittle.List_Sort(list, cmp)
	sort(list, cmp)
end

end