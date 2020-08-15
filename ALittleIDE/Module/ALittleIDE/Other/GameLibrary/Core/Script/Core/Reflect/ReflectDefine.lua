-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
ALittle.RegStruct(318154964, "ALittle.ClassInfo", {
name = "ALittle.ClassInfo", ns_name = "ALittle", rl_name = "ClassInfo", hash_code = 318154964,
name_list = {"__name","__super","__element","__child","__getter","__setter"},
type_list = {"string","ALittle.ClassInfo","List<ALittle.ClassInfo>","Map<string,ALittle.ClassInfo>","Map<string,Functor<(any):any>>","Map<string,Functor<(any,any)>>"},
option_map = {}
})

function ALittle.NewObject(clazz, ...)
	return clazz(...)
end

function ALittle.Cast(T, O, object)
	if object == nil then
		return nil
	end
	local o_info = (object).__class
	local t_info = T
	if o_info ~= t_info then
		return nil
	end
	return object
end

end